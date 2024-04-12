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
 * List of DeviceTypes that is included in multiple classes.
 * Adding new Devices here will allow them to be detected by DeviceList,
 * provided they have a class interface and Parse function in
 * DeviceList.Deserialize.
 */


#pragma once

#include <cstdint>

#include "Platform.hpp"

namespace SGCore
{
    /// <summary> Specific devices within the SGCore library </summary>
    enum class SGCORE_API EDeviceType : int8_t
    {
        /// <summary> This device is not recognized by the Sense Glove API. </summary>
        Unknown = -2,

        /// <summary> A Device that is in development, with direct access to sensor data and commands. </summary>
        BetaDevice = -1,

        /// <summary> An exoskeleton glove that provides force- and haptic feedback. </summary>
        SenseGlove = 0,

        /// <summary> A soft glove with basic tracking, as well as force- and Haptic Feedback. </summary>
        Nova = 2,

        /// <summary> An advanced version of the Nova Glove, with force-, vibrotactile, and squeeze feedback. </summary>
        Nova2 = 3
    };
}// namespace SGCore