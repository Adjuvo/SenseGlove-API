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
 * Since our BLE library can only be included ONCE or cause issues, I'll just add it here...
 */


#pragma once

#include <SenseGlove/Common/Platform.hpp>

#include <memory>
#include <string>
#include <vector>

namespace SGConnect
{
    class BleUtil;
    class SGDevice;
}// namespace SGConnect

class SGCONNECT_API SGConnect::BleUtil
{

public:
    static bool InitializeBLE();
    static bool TerminateBLE();

    static bool CreateInstance(std::shared_ptr<SGDevice>& device);

    static bool ReadSensorData(int32_t bleIndex, std::string& sensorData);

private:
    struct Impl;

private:
    BleUtil() = delete;
    virtual ~BleUtil() = delete;
};
