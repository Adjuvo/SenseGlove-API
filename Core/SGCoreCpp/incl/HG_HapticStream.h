#pragma once

#include "SGCore.h"
#include <vector>

#include "SG_FFBCmd.h"
#include "SG_TimedBuzzCmd.h"
#include "TimedThumpCmd.h"

namespace SGCore
{
	namespace Haptics
	{
		class SGCORE_API HG_HapticStream
		{

		protected:

            //---------------------------------------------------------------------------------------------------------------------
            // Member Variables

            /// <summary> All FFB Commands that have been received this 'frame'. Will be flattened into a single command during FlushHapitcs. </summary>
            std::vector<SGCore::Haptics::SG_FFBCmd> ffbQueue;
            /// <summary> All timed Buzz Commands that have been received this 'frame'. Will be flattened into a single command during FlushHapitcs. </summary>
            std::vector<SGCore::Haptics::SG_TimedBuzzCmd> buzzQueue;
            /// <summary> All FFB Commands that have been received this 'frame'. Will be flattened into a single command during FlushHapitcs. </summary>
            std::vector<SGCore::Haptics::TimedThumpCmd> thumperQueue;

        public:

            /// <summary> The base maximum amount of Force-Feedback Commands that can be in a queue. </summary>
            const static int maxFFBCmds = 50;
            /// <summary> The base maximum amount of Vibrotactile Commands that can be in a queue. </summary>
            const static int maxBuzzCmds = 50;
            /// <summary> The base maximum amount of Thumper Commands that can be in a queue. </summary>
            const static int maxThumpCmds = 50;


            //---------------------------------------------------------------------------------------------------------------------
            // Construction

            /// <summary> Create a new HapticsStream for a Haptic Glove. </summary>
            HG_HapticStream();


            //---------------------------------------------------------------------------------------------------------------------
            // Queue Functions

            /// <summary> Clears only the Force-Feedback Queue. </summary>
            void ClearFFB();

            /// <summary> Clears all vibrations in the queue(s) </summary>
            void ClearVibrations();

            /// <summary> Clear all ongaoing effects to this stream. </summary>
            void Clear();

            /// <summary> Add a new Force-Feedback command to the queue. Does not actually send it. </summary>
            /// <param name="ffbCmd"></param>
            void AddCmd(SG_FFBCmd ffbCmd);

            /// <summary> Add a new vibrotactile command to the queue. Does not actually send it. </summary>
            /// <param name="buzzCmd"></param>
            void AddCmd(SG_TimedBuzzCmd buzzCmd);

            /// <summary> Add a new Thumper command to the queue. Does not actually send it. Does not work with SenseGlove, only for Nova's </summary>
            /// <param name="thumpCmd"></param>
            void AddCmd(TimedThumpCmd thumpCmd);


            /// <summary> Update the active commands, using a deltaTime since last update, in seconds. Any timedCommands that are elapsed will be removed from the list. </summary>
            /// <param name="dT_seconds"></param>
            void UpdateTimedCommands(float dT_seconds);

            //---------------------------------------------------------------------------------------------------------------------
            // Compilation Functions

            /// <summary> Compiles all FFB Levels in the queue into a single one. Does not clear the queue. Returns lastFFBCmd if no FFB commands are given. </summary>
            /// <param name="lastFFB"></param>
            /// <returns></returns>
            SG_FFBCmd TotalFFBLevels(SG_FFBCmd lastFFB);

            /// <summary> Compiles all FFB Levels in the queue into a single one. Does not clear the queue. </summary>
            /// <returns></returns>
            SG_FFBCmd TotalFFBLevels();


            /// <summary> Compiles all active vibrotactile in the queue into a single list of levels. Does not clear the queue. </summary>
            SG_BuzzCmd TotalBuzzLevels();


            /// <summary> Compiles all active vibrotactile in the queue into a single list of levels. Does not clear the queue. </summary>
            ThumperCmd TotalThumperLevels();


            // Flushing commands

            /// <summary> Compile all commands in the queue(s) into a single set of commands that can be sent to the glove. Only clears the FFB queue, and only if you want it to. </summary>
            /// <param name="lastBrakeLvl"></param>
            /// <param name="ffbCmd"></param>
            /// <param name="buzzCmd"></param>
            /// <param name="thumperCmd"></param>
            /// <param name="clearFFBqueue"></param>
            /// <returns></returns>
            void FlushHaptics(SG_FFBCmd lastBrakeLvl, SG_FFBCmd& ffbCmd, SG_BuzzCmd& buzzCmd, ThumperCmd& thumperCmd, bool clearFFBqueue = true);

            /// <summary> Compile all commands in the queue(s) into a single set of commands that can be sent to the glove. Also updates & clears all queues. </summary>
            /// <param name="dT_seconds"></param>
            /// <param name="lastBrakeLvl"></param>
            /// <param name="ffbCmd"></param>
            /// <param name="buzzCmd"></param>
            /// <param name="thumperCmd"></param>
            void FlushHaptics(float dT_seconds, SG_FFBCmd lastBrakeLvl, SG_FFBCmd& ffbCmd, SG_BuzzCmd& buzzCmd, ThumperCmd& thumperCmd);


		};
	}
}

