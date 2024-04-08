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
 * Diagnostics class used to send messages to developers from the Sense Glove
 * API.
 */


#pragma once

#include <cstdint>
#include <iostream>
#include <string>

#include "Platform.hpp"

namespace SGCore
{
    namespace Diagnostics
    {
        /// <summary> Used to manage incoming debug levels </summary>
        enum class SGCORE_API EDebugLevel : uint8_t
        {
            /// <summary> No debug messages will be sent. </summary>
            Disabled = 0,

            /// <summary> Send only messages if errors are caught. </summary>
            ErrorsOnly,

            /// <summary> Send messages from calibration algorithms </summary>
            CallibrationMessages,

            /// <summary> Send messages from device Parsing. </summary>
            DeviceParsing,

            /// <summary> Send messages related to backed communications. Mostly relevant when using
            /// Ports / Android Strings. </summary>
            BackendCommunication,

            /// <summary> Which haptics are eventually sent to the glove </summary>
            Haptics_Sent,

            /// <summary> Which haptics are added into our queue. </summary>
            Haptics_Queue,

            /// <summary> For those we have no place for yet. </summary>
            All,
        };

        /// <summary> Used to send Debug Messages to the developer (and user). </summary>
        class Debugger;
    }// namespace Diagnostics
}// namespace SGCore

/// <summary> Used to send Debug Messages to the developer (and user). </summary>
class SGCORE_API SGCore::Diagnostics::Debugger
{
public:
    /// <summary> The Default debug level for any application. </summary>
    static EDebugLevel GetDefaultLevel();// defined separately so we can say debugLevel = default

    /// <summary> The current debug level of the Debugger. </summary>
    static EDebugLevel GetDebugLevel();

    static void SetDebugLevel(EDebugLevel level);

    /// <summary> Print a single message with an end-line to the console. </summary>
    static void Log(const std::string& msg, EDebugLevel level);

private:
    struct Impl;

public:
    Debugger() = delete;
    virtual ~Debugger() = delete;
};