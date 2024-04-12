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
 * Contains enumerators and classes to aid in Nova Deserialization.
 */


#pragma once

#include <cstdint>

#include "Platform.hpp"

namespace SGCore
{
    namespace Nova
    {
        namespace Parsing
        {
            /// <summary> Order of values as they come in from the Nova. </summary>
            enum class ENovaCVar : uint8_t
            {
                ConstOpen = 0,
                Id,
                GloveVersion,
                FirmwareVersion,
                LeftRight,
                Functions,
                ImuCorrection,

                /// <summary> Utility value used in iteration / checking lengths </summary>
                AllC,
            };

            /// <summary> Sensor data blocks </summary>
            enum class ENovaData : uint8_t
            {
                Sensors,
                Imu,
                All,
            };
        }// namespace Parsing
    }// namespace Nova
}// namespace SGCore