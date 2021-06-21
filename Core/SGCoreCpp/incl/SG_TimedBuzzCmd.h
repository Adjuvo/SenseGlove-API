// ----------------------------------------------------------------------------------
// Buzz Motor with timing parameters.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include "SG_BuzzCmd.h"
#include <string>

namespace SGCore
{
	namespace Haptics
	{
		/// <summary> Buzz motor commands that is meant to stop after a few miliseconds. </summary>
		/// <remarks> Intended use; this.levels indicates the actual command </remarks>
		class SGCORE_API SG_TimedBuzzCmd : public SG_BuzzCmd
		{

        protected:

            //--------------------------------------------------------------------------------
            // Properties

            /// <summary> The Buzz Motor command used to create the timing. </summary>
            SG_BuzzCmd baseCmd;

            /// <summary> Empty constructor for inheritance. </summary>
            SG_TimedBuzzCmd() { }

        public:

            /// <summary> The total time [millisecons] each buzz motor should be vibrating for. </summary>
            float duration = 0;

            /// <summary> The time elapsed since the command was sent [millisecons]. </summary>
            float elapsedTime = 0;


            //--------------------------------------------------------------------------------
            // Construction

            /// <summary> Create a new TimeBuzzCommand for a single finger. </summary>
            /// <param name="finger"></param>
            /// <param name="magnitude"></param>
            /// <param name="duration_seconds"></param>
            /// <param name="startTime_seconds"></param>
            SG_TimedBuzzCmd(Finger finger, int magnitude, float duration_seconds, float startTime_seconds = 0);

            /// <summary>
            /// Create a new buzz motor command that expires after timing_ms
            /// </summary>
            /// <param name="command"></param>
            /// <param name="duration_seconds"></param>
            /// <param name="startTime_seconds">Optional, starts the effect at a certain time</param>
            SG_TimedBuzzCmd(SG_BuzzCmd command, float duration_seconds, float startTime_seconds = 0);

            //--------------------------------------------------------------------------------
            // Accessors

            /// <summary> Access the base command, which indicates the buzz levels to keep untill time elapses. </summary>
            /// <returns></returns>
            virtual SG_BuzzCmd GetBaseCommand();

            /// <summary> Check if this timed command's timing has elapsed </summary>
            /// <returns></returns>
            virtual bool TimeElapsed();

            /// <summary> Represents how far this effect is in its playtime; [0...1], where 0 means at the start, and 1 means at the end </summary>
            /// <param name="clamp01">Optional parameter; ensures this value is always between 0 and 1.</param>
            virtual float NormalizedTime(bool clamp01 = true);

            //--------------------------------------------------------------------------------
            // Class Methods

            std::string ToString() override;

            /// <summary> Copy this Buzz Command's values into a new object. </summary>
            /// <returns></returns>
            SG_BuzzCmd Copy() override;

            /// <summary> Merges this basecommand with another command </summary>
            /// <param name="other"></param>
            /// <returns></returns>
            SG_BuzzCmd Merge(SG_BuzzCmd other) override;

            /// <summary> Reset the timings of this BuzzCmd, allowing us to re-use it. </summary>
            virtual void ResetTiming();

            /// <summary> Update the elapsed time to check if the buzz motors should stop. </summary>
            /// <param name="dT_seconds"></param>
            virtual void UpdateTiming(float dT_seconds);

		};
	}
}

