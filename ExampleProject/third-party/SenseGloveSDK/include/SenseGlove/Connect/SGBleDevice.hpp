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
 */


#pragma once

#include <SenseGlove/Common/Platform.hpp>

#include "SGDevice.hpp"


namespace SGConnect
{
    class IdResponse;
    class SGBleDevice;

}// namespace SGConnect


class SGCONNECT_API SGConnect::SGBleDevice : public SGConnect::SGDevice
{

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    SGBleDevice(const IdResponse& idInfo, const std::string& constantsResponse,
                std::string& out_hapticsResponse, int32_t deviceIndex);

public:
    /**
     * The copy constructor.
     */
    SGBleDevice(const SGBleDevice& rhs) = delete;

    /**
     * The move constructor.
     */
    SGBleDevice(SGBleDevice&& rhs) noexcept;

public:
    virtual ~SGBleDevice();

public:
    /**
     * The copy assignment operator.
     */
    SGBleDevice& operator=(const SGBleDevice& rhs) = delete;

    /**
     * The move assignment operator.
     */
    SGBleDevice& operator=(SGBleDevice&& rhs) noexcept;

public:
    virtual void StopUpdating() override;

    /// <summary> Retrieve the IPC string for deviceInfo. </summary>
    virtual std::string GetDeviceString() const override;

    [[nodiscard]] virtual bool IsConnected() const override;
};
