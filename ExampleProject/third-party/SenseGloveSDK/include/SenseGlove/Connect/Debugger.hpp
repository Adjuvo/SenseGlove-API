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
 * Diagnostics class used to send messages to developers from the Sense Glove
 * API.
 */

//#define NO_TIMESTAMPS //if defined, we do not add TimeStamps to our Debug Logs. (Saves on calculation speed, I'm sure).

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <SenseGlove/Common/Platform.hpp>

namespace SGConnect
{
    class Debugger;
}// namespace SGConnect

class SGCONNECT_API SGConnect::Debugger
{
public:
    static void SetDebugQueue(bool bActive);

    static void ClearQueue();

    static void GetMessages(std::vector<std::string>& out_messages);

    static bool KeepsQueue();

    static void LogExternal(const std::string& msg);

    /// <summary> Set the current system time as the startup time... </summary>
    static void LogStartTime();
    /// <summary> Returns the local time since startup for this process. Useful only for debugging for now... </summary>
    /// <returns></returns>
    static float ElapsedTime_ms();

private:
    struct Impl;

public:
    Debugger() = delete;
    virtual ~Debugger() = delete;
};
