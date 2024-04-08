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
 * Enumerators to allow access to specific anatomical joints or movements of
 * the finger through the right index.
 */


#pragma once

#include <cstdint>

#include "Platform.hpp"

namespace SGCore
{
    //--------------------------------------------------------------------------------------
    // Appendages

    /// <summary> One of the fingers on the hand </summary>
    enum class SGCORE_API EFinger : uint8_t
    {
        /// <summary> Responsible for our evolutionary success! </summary>
        Thumb,

        /// <summary> Used to point at what you want </summary>
        Index,

        /// <summary> On its own, this one is used to indicate frustration. </summary>
        Middle,

        /// <summary> If you like it then you should have put a ___ on it </summary>
        Ring,

        /// <summary> The little finger. </summary>
        Pinky,
    };

    namespace Kinematics// One layer down since it will be mostly used in this namespace.
    {
        //--------------------------------------------------------------------------------------
        // Movements

        /// <summary> Anatomical movements of the thumb joints. </summary>
        enum class SGCORE_API EThumbMovement : uint8_t
        {
            /// <summary> Pronation/Supination of the first finger joint. </summary>
            CmcTwist = 0,

            /// <summary> Flexion of the first finger joint. </summary>
            CmcFlexion,

            /// <summary> Abduction of the first finger joint. </summary>
            CmcAbduction,

            /// <summary> Flexion of the second thumb joint. </summary>
            McpFlexion,

            /// <summary> Flexion of the third thumb joint. </summary>
            IpFlexion,
        };

        /// <summary> Anatomical movements of the finger joints. </summary>
        enum class SGCORE_API EFingerMovement : uint8_t
        {
            /// <summary> Flexion of the first finger joint. </summary>
            McpFlexion = 0,

            /// <summary> Abduction of the first finger joint. </summary>
            McpAbduction,

            /// <summary> Flexion of the second finger joint. </summary>
            PipFlexion,

            /// <summary> Flexion of the third finger joint. </summary>
            DipFlexion,
        };
    }// namespace Kinematics
}// namespace SGCore