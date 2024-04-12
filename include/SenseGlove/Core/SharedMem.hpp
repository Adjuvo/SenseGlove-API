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
 * Utility Class used to write and read to/from IPC.
 * a.k.a. The (only) one with access to Boost::Interprocess.
 */


#pragma once

#include <cstdint>
#include <string>

#include "Platform.hpp"

namespace SGCore
{
    /// <summary> Utility Class used to write and read to/from IPC. </summary>
    class SGCORE_API SharedMem;
};// namespace SGCore

/// <summary> Utility Class used to write and read to/from IPC. </summary>
class SGCORE_API SGCore::SharedMem
{
public:
    /// <summary> Shared Memory block containing number of devices and deviceInfo from each device. </summary>
    static const std::string& GetDevices();

    /// <summary> Shared Memory block containing haptic commands from each device. </summary>
    static const std::string& GetHaptics();

    /// <summary>  Shared Memory block containing sensor data from each device. </summary>
    static const std::string& GetData();

    /// <summary> Shared Memory block containing commands to be sent to the devices. </summary>
    static const std::string& GetInCommands();

    /// <summary> Shared Memory block containing commands/responses from the devices. </summary>
    static const std::string& GetOutCommands();

    /// <summary> Address in devices where the number of devices is stored. </summary>
    static const std::string& GetNumDevices();

    /// <summary> Address in devices where the scanner's processing id is stored. </summary>
    static const std::string& GetScanActive();

    /// <summary> Address in devices where the scanner's processing id is stored. </summary>
    static long GetMaxTimeTick();

    /// <summary> Delimiter to split data in Shared Memory. </summary>
    static char GetListDelimiter();

    /// <summary> Standard size of Shared Memory. It works with this but could probably use a lower value. </summary>
    static uint32_t GetStandardSize();

public:
    /// <summary> Write a string to Shared Memory at block-address. Returns true if successful. </summary>
    static bool WriteTo(const std::string& block, const std::string& address, const std::string& value,
                        uint32_t size = GetStandardSize());

    /// <summary> Retrieve value from Shared Memory at block-address. Returns true if successful. </summary>
    static bool ReadFrom(const std::string& block, const std::string& address, std::string& out_value);

    /// <summary> Dispose of a shared memory block so it no longer takes up space on the PC. Returns true if successful. </summary>
    static bool Dispose(const std::string& block);

    /// <summary> Access the time since the last update from SGConnect. </summary>
    static bool ScanningActive();

public:
    SharedMem() = delete;
    virtual ~SharedMem() = delete;
};