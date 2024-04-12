/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2024 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Enum indicating effects that can be played by the thumper, and its
 * corresponding byte.
 *
 * Note: effect selected by Michelle Corten.
 */


#pragma once

#include <cstdint>

#include "Platform.hpp"

namespace SGCore
{
    namespace Haptics
    {
        /// <summary> A command to activate the Sense Glove Thumper Module, which is responsible for wrist feedback.
        /// </summary>
        enum class SGCORE_API ESenseGloveThumperCommand : uint8_t
        {
            None = 126,

            /// <summary> Turn off the thumper effects. </summary>
            TurnOff = 124,

            /// <summary> A 5-seconds long, constant vibration. </summary>
            CueGameOver = 118,

            /// <summary> A double-click at 100% intensity. </summary>
            ButtonDouble100 = 10,

            /// <summary> A double click at 60% intensity. </summary>
            ButtonDouble60 = 11,

            /// <summary> Simulates an impact of the hand at 100% intensity. </summary>
            ImpactThump100 = 1,

            /// <summary> Simulates an impact of the hand at 30% intensity. </summary>
            ImpactThump30 = 3,

            /// <summary> Simulates an sharp impact of the hand at 40% intensity. </summary>
            ImpactThump10 = 6,

            /// <summary> A light vibration to cue the user that an object it picked up. 100% intensity. </summary>
            ObjectGrasp100 = 7,

            /// <summary> A light vibration to cue the user that an object it picked up. 60% intensity. </summary>
            ObjectGrasp60 = 8,

            /// <summary> A light vibration to cue the user that an object it picked up. 30% intensity. </summary>
            ObjectGrasp30 = 9,
        };
    }// namespace Haptics
}// namespace SGCore