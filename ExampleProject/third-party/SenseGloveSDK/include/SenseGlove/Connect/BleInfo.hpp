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
 * 
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <SenseGlove/Common/Platform.hpp>

namespace SGConnect
{
    class BleInfo;
}

/// <summary> The processed ID Response of a Sense Glove Device, which we use to identify it. </summary>
class SGCONNECT_API SGConnect::BleInfo
{
public:
    
    static BleInfo Parse(const std::string& json);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Create a new instance of an invalid IdResponse </summary>
    BleInfo();

    /// <summary> Create a new instance of a processed IdResponse </summary>
    BleInfo(int32_t deviceType, const std::string& deviceId);

    /**
     * The copy constructor.
     */
    BleInfo(const BleInfo& rhs);

    /**
     * The move constructor.
     */
    BleInfo(BleInfo&& rhs) noexcept;

    virtual ~BleInfo();

public:
    /**
     * The copy assignment operator.
     */
    BleInfo& operator=(const BleInfo& rhs);

    /**
     * The move assignment operator.
     */
    BleInfo& operator=(BleInfo&& rhs) noexcept;

public:
    /// <summary> The type of device. If < -2, it is not one of Sense Glove, if -1, it's a Beta Device. If anything
    /// else, its one of ours. </summary>
    [[nodiscard]] int32_t GetDeviceType() const;// SenseCom does not care which exact type this device is, only if it
                                               // adheres to our communications protocol.

    /// <summary> The unique Serial Number of this device. </summary>
    [[nodiscard]] const std::string& GetLocalName() const;


public:
    /// <summary> Check if this IdResponse matches that of otherDevice. </summary>
    [[nodiscard]] bool SameDevice(const BleInfo& otherDevice) const;

    /// <summary> Returns true if this is a Valid Sense Glove Device. </summary>
    [[nodiscard]] bool IsValid() const;
};
