/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2026 SenseGlove
 *
 * @section DESCRIPTION
 *
 * An abstract parent class for communication lines with Sense Glove Devices.
 * We use this to allow us to add more forms of communication to the Sense Glove
 * later on.
 */


#pragma once

#include <cstdint>

#include <SenseGlove/Common/Platform.hpp>

namespace SGConnect
{
    /// <summary> How the communications will send data back and forth. </summary>
    enum class SGCONNECT_API ETransmissionMode : uint8_t
    {
        /// <summary> Synchronized communication, where we send haptics and receive sensor data. Default </summary>
        PingPong = 0,

        /// <summary> Original asynchronous communication. Should only be applicable to SenseGloves running old
        /// firmware. </summary>
        Async,
    };
}