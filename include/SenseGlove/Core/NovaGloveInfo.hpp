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
 * Contains information on Nova's hardware, extracted from the device.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;
    }// namespace Kinematics

    namespace Nova
    {
        /// <summary> Device information extracted from a Nova Glove. </summary>
        class SGCORE_API NovaGloveInfo;
    }// namespace Nova
}// namespace SGCore

/// <summary> Device information extracted from a Nova Glove. </summary>
class SGCORE_API SGCore::Nova::NovaGloveInfo
{
public:
    /// <summary> Parse a constants string into a NovaGloveInfo class. </summary>
    /// <param name="constantsString"></param>
    /// <param name="out_novaGloveInfo"></param>
    /// <returns></returns>
    static bool Parse(const std::string& constantsString, NovaGloveInfo& out_novaGloveInfo);

    /// <summary> Convert a string representation back into a NovaGloveInfo class. </summary>
    /// <param name="serializedString"></param>
    /// <returns></returns>
    SG_NODISCARD static NovaGloveInfo Deserialize(const std::string& serializedString);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The default constructor. </summary>
    /// <returns></returns>
    NovaGloveInfo();

    /// <summary> Create a new instance of a NovaGloveInfo. </summary>
    /// <param name="deviceId"></param>
    /// <param name="hardwareVersion"></param>
    /// <param name="firmwareVersion"></param>
    /// <param name="subFirmwareVersion"></param>
    /// <param name="bRightHanded"></param>
    /// <param name="imuCorrection"></param>
    /// <param name="numberOfSensors"></param>
    /// <returns></returns>
    NovaGloveInfo(const std::string& deviceId,
                  const std::string& hardwareVersion, int32_t firmwareVersion, int32_t subFirmwareVersion,
                  bool bRightHanded, const Kinematics::Quat& imuCorrection, int32_t numberOfSensors);

    /**
     * The copy constructor.
     */
    NovaGloveInfo(const NovaGloveInfo& rhs);

    /**
     * The move constructor.
     */
    NovaGloveInfo(NovaGloveInfo&& rhs) noexcept;

    virtual ~NovaGloveInfo();

public:
    /**
     * The copy assignment operator.
     */
    NovaGloveInfo& operator=(const NovaGloveInfo& rhs);

    /**
     * The move assignment operator.
     */
    NovaGloveInfo& operator=(NovaGloveInfo&& rhs) noexcept;

public:
    /// <summary> Unique identifier of this device. </summary>
    SG_NODISCARD const std::string& GetDeviceId() const;

    /// <summary> Hardware (sub) version of this Sense Glove Device. </summary>
    SG_NODISCARD const std::string& GetHardwareVersion() const;

    /// <summary> Firmware version running on the device's MicroController. (as v4.12, this is the 4). </summary>
    SG_NODISCARD int32_t GetFirmwareVersion() const;

    /// <summary> Sub firmware version running on the device's microcontroller (as v4.12, this is the .12). </summary>
    SG_NODISCARD int32_t GetSubFirmwareVersion() const;

    /// <summary> Determines if this is a right-handed Nova. </summary>
    SG_NODISCARD bool IsRight() const;

    /// <summary> The IMU correction of this Nova. </summary>
    SG_NODISCARD const Kinematics::Quat& GetImuCorrection() const;

    /// <summary> The number of sensors in this device. </summary>
    SG_NODISCARD int32_t GetNumberOfSensors() const;

public:
    /// <summary> Returns true if this glove's firmware is newer than certain version. </summary>
    /// <param name="firmwareMain"></param>
    /// <param name="firmwareSub"></param>
    /// <param name="bInclusive"></param>
    /// <returns></returns>
    SG_NODISCARD bool FirmwareNewerThan(int32_t firmwareMain, int32_t firmwareSub, bool bInclusive) const;

    /// <summary> Returns true if this glove's firmware is older than certain version. </summary>
    /// <param name="firmwareMain"></param>
    /// <param name="firmwareSub"></param>
    /// <param name="bInclusive"></param>
    /// <returns></returns>
    SG_NODISCARD bool FirmwareOlderThan(int32_t firmwareMain, int32_t firmwareSub, bool bInclusive) const;

public:
    /// <summary> Returns true if this GloveInfo contains the same information as another. </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    SG_NODISCARD bool Equals(const NovaGloveInfo& novaGloveInfo) const;

public:
    /// <summary> Create a string representation of this Glove Info. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string ToString() const;

    /// <summary> Convert this class into a string representation so it can be unpacked later. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string Serialize() const;
};