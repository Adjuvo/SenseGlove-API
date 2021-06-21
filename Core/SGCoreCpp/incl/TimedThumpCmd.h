#pragma once

#include "SGCore.h"
#include "ThumperCmd.h"
#include <string>

namespace SGCore
{
	namespace Haptics
	{
		class SGCORE_API TimedThumpCmd
		{
        protected:

            /// <summary> Internal, empty, for extended classes. </summary>
            TimedThumpCmd();

        public: 

            /// <summary> Magnitude in % </summary>
            int magnitude;

            /// <summary> duration in seconds </summary>
            float duration;

            /// <summary> The elapsed time so far. </summary>
            float elapsedTime;

            /// <summary> Returns true if the timed command has elapsed. </summary>
            bool Elapsed();


            /// <summary> Create a new Timed Thumper Command. </summary>
            /// <param name="amplitude">Value between 0 .. 1 representing the magnitude of the system.</param>
            /// <param name="duration_seconds"></param>
            /// <param name="startTime_seconds"></param>
            TimedThumpCmd(int amplitude, float duration_seconds, float startTime_seconds = 0);

            std::string ToString();

            /// <summary> Create a new Timed Thumper Command. </summary>
            /// <param name="baseCmd"></param>
            /// <param name="duration_seconds"></param>
            /// <param name="startTime_seconds"></param>
            TimedThumpCmd(ThumperCmd baseCmd, float duration_seconds, float startTime_seconds = 0);

            /// <summary> Update the timing on this Thumper Command </summary>
            /// <param name="dT_seconds"></param>
            virtual void Update(float dT_seconds);

            virtual bool Equals(ThumperCmd baseCmd);

            /// <summary> Copy the parameters of this ThumperCommand into another instance. </summary>
            /// <returns></returns>
            virtual TimedThumpCmd Copy(bool copyElapsed = true);
		};
	}
}
