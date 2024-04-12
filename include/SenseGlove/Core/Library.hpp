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
 * Information about the SGCore C++ Library.
 */


#pragma once

#include <cstdint>
#include <string>

#include "Platform.hpp"

namespace SGCore
{
    enum SGCORE_API EBackendType : uint32_t
    {
        /// <summary> Backend info comes from shared memory on the device. </summary>
        SharedMemory,
        /// <summary> Back-end Data comes from an Android Library </summary>
        AndroidStrings,
    };

    /// <summary> Provides information about this C++ Library. </summary>
    class SGCORE_API Library;
}

/// <summary> Provides information about this C++ Library. </summary>
class SGCORE_API SGCore::Library
{
public:
    /// <summary> The version of this C++ Library in string representation. </summary>
    /// <returns></returns>
    static std::string Version();

    /// <summary> Check what back-end connections are used for this version of SGConnect. </summary>
    /// <returns></returns>
    static EBackendType GetBackendType();

    /// <summary> Back-End version in string notation </summary>
    /// <returns></returns>
    static std::string BackendVersion();

    /// <summary> If possible, check what version of SGConnect is paired with this API. </summary>
    /// <returns></returns>
    static std::string SGConnectVersion();

public:
    Library() = delete;
    virtual ~Library() = delete;
};