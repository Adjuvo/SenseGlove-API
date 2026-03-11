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
 * Interface for SenseCom, allows the retrieval of Devices and Data, but only
 * as.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include <SenseGlove/Common/Platform.hpp>
#include "DeviceTypes.hpp"
#include "SGDevice.hpp"

namespace SGCore
{
    namespace Nova
    {
        class Nova2Glove;
        class NovaGlove;
    }

    namespace SG
    {
        class SenseGlove;
    }

    class BetaDevice;

    /// <summary> Interface for SenseCom, allows the retrieval of Devices and Data. </summary>
    class SGCORE_API DeviceList;
}// namespace SGCore

/// <summary> Interface for SenseCom, allows the retrieval of Devices and Data. </summary>
class SGCORE_API SGCore::DeviceList
{
public:
    //--------------------------------------------------------------------------------------
    // Accessors

    /// <summary> Retrieve the number of devices that have been detected by the SenseCom executable. </summary>
    static std::size_t ActiveDevices();

    /// <summary> Returns true if the SenseCom program is running. </summary>
    static bool SenseComRunning();

    /// <summary> Clear the device list, and block any further attempt to add to it until ReInitialize is called.
    /// </summary>
    /// <remarks> Useful if your IDE has troubles unloading dlls (cough, Unity, Cough). </remarks>
    /// <returns></returns>
    static void Dispose();

    /// <summary> When you've accidentally disposed of the list before you meant to. </summary>
    /// <returns></returns>
    static void Reinitialize();

    //--------------------------------------------------------------------------------------
    // Device Access Methods

    /// <summary> Retrieve all Sense Glove Devices connected to this system. </summary>
    static std::vector<std::shared_ptr<SGDevice>> GetDevices();

    /// <summary> Retrieve a list of SGDevices of a specific class. </summary>
    template<class T>
    static std::vector<std::shared_ptr<T>> GetDevices()
    {
        SGCore::EDeviceType targetType = SGCore::EDeviceType::Unknown;

        if constexpr (std::is_same_v<T, SGCore::Nova::Nova2Glove>) {
            targetType = SGCore::EDeviceType::Nova2;
        } else if constexpr (std::is_same_v<T, SGCore::Nova::NovaGlove>) {
            targetType = SGCore::EDeviceType::Nova;
        } else if constexpr (std::is_same_v<T, SGCore::SG::SenseGlove>) {
            targetType = SGCore::EDeviceType::SenseGlove;
        } else if constexpr (std::is_same_v<T, SGCore::BetaDevice>) {
            targetType = SGCore::EDeviceType::BetaDevice;
        } else {
            SG_ASSERT(false, "Unsupported device type in DeviceList::GetDevices<T>()");
        }

        std::size_t currentDevices = DeviceList::ActiveDevices();
        std::vector<std::shared_ptr<T>> res;
        for (std::size_t i = 0; i < currentDevices; ++i) {
            const std::shared_ptr<SGDevice>& device{GetSGDevices()[i]};
            if (device && device->GetDeviceType() == targetType) {
                res.emplace_back(std::static_pointer_cast<T>(GetSGDevices()[i]));//emplace_back is valid here, as we
                                                                                  // don't know how many devices are of the same type.
            }
        }
        return res;
    }

    //--------------------------------------------------------------------------------------
    // Device Communication Methods

    /// <summary> Retrieve the latest (raw) sensor data from a specific device in our list. </summary>
    static bool GetSensorDataString(int32_t ipcIndex, const std::string& ipcAddress, std::string& out_sensorData);

    /// <summary> Send a (raw) command to a specific device in the list. </summary>
    static bool SendHaptics(int32_t ipcIndex, const std::string& ipcAddress, int32_t channelIndex, const std::string& commands);

    static std::string GetDeviceStringAt(int32_t ipcIndex, const std::string& ipcAddress, int32_t index);

    /// <summary> Retrieve Device Address. </summary>
    static std::string GetAddress(int32_t ipcIndex, const std::string& ipcAddress);

    /// <summary> Retrieve this device's connectionType. </summary>
    static SGDevice::EConnectionType GetConnectionType(int32_t ipcIndex, const std::string& ipcAddress);

    /// <summary> Returns true if the device at  this connection side is properly connected. </summary>
    static bool IsConnected(int32_t ipcIndex, const std::string& ipcAddress);

    /// <summary> Retrieve the device's Packets per Second Variable. </summary>
    /// <returns></returns>
    static int32_t PacketsPerSecondReceived(int32_t ipcIndex, const std::string& ipcAddress);

    /// <summary> Retrieve the device's Packets per Second sent Variable. </summary>
    /// <returns></returns>
    static int32_t PacketsPerSecondSent(int32_t ipcIndex, const std::string& ipcAddress);

private:
    /// <summary> A list of all devices that have been detected via the SenseCom executable. </summary>
    static const std::vector<std::shared_ptr<SGDevice>>& GetSGDevices();

private:
    struct Impl;

public:
    DeviceList() = delete;
    virtual ~DeviceList() = delete;
};
