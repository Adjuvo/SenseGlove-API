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
 * A parsed version of an {I} response from a Sense Glove Device, with utility
 * functions.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <SenseGlove/Common/Platform.hpp>

namespace SGConnect
{
    class IdResponse;
}

/// <summary> The processed ID Response of a Sense Glove Device, which we use to identify it. </summary>
class SGCONNECT_API SGConnect::IdResponse
{
public:
    /// <summary> Parse a raw IdResponse, as received from a possible SGDevice, into useful data. </summary>
    static IdResponse Parse(const std::string& rawCommand);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Create a new instance of an invalid IdResponse </summary>
    IdResponse();

    /// <summary> Create a new instance of a processed IdResponse </summary>
    IdResponse(int32_t deviceType, const std::string& deviceId);

public:
    /**
     * The copy constructor.
     */
    IdResponse(const IdResponse& rhs);

    /**
     * The move constructor.
     */
    IdResponse(IdResponse&& rhs) noexcept;

public:
    virtual ~IdResponse();

public:
    /**
     * The copy assignment operator.
     */
    IdResponse& operator=(const IdResponse& rhs);

    /**
     * The move assignment operator.
     */
    IdResponse& operator=(IdResponse&& rhs) noexcept;

public:
    /// <summary> The type of device. If < -2, it is not one of Sense Glove, if -1, it's a Beta Device. If anything
    /// else, its one of ours. </summary>
    [[nodiscard]] int32_t GetDeviceType() const;// SenseCom does not care which exact type this device is, only if it
                                               // adheres to our communications protocol.

    /// <summary> The unique Serial Number of this device. </summary>
    [[nodiscard]] const std::string& GetSerialNumber() const;

public:
    /// <summary> Check if this IdResponse matches that of otherDevice. </summary>
    [[nodiscard]] bool SameDevice(const IdResponse& otherDevice) const;

    /// <summary> Returns true if this is a Valid Sense Glove Device. </summary>
    [[nodiscard]] bool IsValid() const;
};
