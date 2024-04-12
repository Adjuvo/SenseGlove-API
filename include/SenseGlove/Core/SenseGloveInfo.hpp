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
 * Glove information taken from the Sense Glove.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Fingers.hpp"
#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;
        class Vect3D;
    }// namespace Kinematics

    namespace SG
    {
        /// <summary> Glove Information taken from a SenseGlove. Contains everything from unique ID, firmware version,
        /// etc. </summary>
        class SGCORE_API SenseGloveInfo;
    }// namespace SG
}// namespace SGCore

/// <summary> Glove Information taken from a SenseGlove. Contains everything from unique ID, firmware version, etc.
/// </summary>
class SGCORE_API SGCore::SG::SenseGloveInfo
{
public:
    /// <summary> Create an instance of the SGModel from its string representation. </summary>
    static bool Parse(const std::string& constantsString, SenseGloveInfo& out_gloveInfo, bool bUpdateOldModels = true);

    /// <summary> Deserialize a HandProfile back into usable values. </summary>
    static SenseGloveInfo Deserialize(const std::string& serializedString);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The default constructor. </summary>
    SenseGloveInfo();

    /// <summary> Create a new Sense Glove device model. </summary>
    SenseGloveInfo(const std::string& deviceId,
                const std::string& hardwareVersion, int32_t firmwareVersion, int32_t subFirmwareVersion,
                bool bRightHanded, int32_t numberOfSensors,
                const Kinematics::Quat& imuCorrection,
                const std::vector<Kinematics::Vect3D>& startPositions,
                const std::vector<Kinematics::Quat>& startRotations,
                const std::vector<std::vector<Kinematics::Vect3D>>& gloveLengths,
                const std::vector<bool>& functions);

    /**
     * The copy constructor.
     */
    SenseGloveInfo(const SenseGloveInfo& rhs);

    /**
     * The move constructor.
     */
    SenseGloveInfo(SenseGloveInfo&& rhs) noexcept;

    /// <summary> Default Destructor. </summary>
    virtual ~SenseGloveInfo();

public:
    /**
     * The copy assignment operator.
     */
    SenseGloveInfo& operator=(const SenseGloveInfo& rhs);

    /**
     * The move assignment operator.
     */
    SenseGloveInfo& operator=(SenseGloveInfo&& rhs) noexcept;

public:
    /// <summary> Unique identifier of this device. </summary>
    SG_NODISCARD const std::string& GetDeviceId() const;

    /// <summary> Hardware (sub) version of this Sense Glove Device. </summary>
    SG_NODISCARD const std::string& GetHardwareVersion() const;

    /// <summary> Firmware version running on the device's MicroController. </summary>
    SG_NODISCARD int32_t GetFirmwareVersion() const;

    /// <summary> Sub-Firmware version running on the device's MicroController. </summary>
    SG_NODISCARD int32_t GetSubFirmwareVersion() const;

    /// <summary> Check if this Sense Glove belongs to a left or right hand. </summary>
    SG_NODISCARD bool IsRight() const;

    /// <summary> The number of Sensors in this SenseGlove. </summary>
    SG_NODISCARD int32_t GetNumberOfSensors() const;

    /// <summary> The IMU correction of this Sense Glove. </summary>
    SG_NODISCARD const Kinematics::Quat& GetImuCorrection() const;

    /// <summary> The starting positions of each Sense Glove finger, relative to the glove origin. </summary>
    SG_NODISCARD const std::vector<Kinematics::Vect3D>& GetStartPositions() const;

    /// <summary> The starting rotations of each Sense Glove finger, relative to the glove origin. </summary>
    SG_NODISCARD const std::vector<Kinematics::Quat>& GetStartRotations() const;

    /// <summary> The lengths of each Sense Glove finger section, in mm. </summary>
    SG_NODISCARD const std::vector<std::vector<Kinematics::Vect3D>>& GetGloveLengths() const;

    /// <summary> Whether this device has a specific function (T/F). </summary>
    SG_NODISCARD const std::vector<bool>& GetFunctions() const;

public:
    /// <summary> The starting position of one Sense Glove finger, relative to the glove origin. </summary>
    SG_NODISCARD const Kinematics::Vect3D& GetStartPosition(SGCore::EFinger finger) const;

    /// <summary> The starting rotation of one Sense Glove finger, relative to the glove origin. </summary>
    SG_NODISCARD const Kinematics::Quat& GetStartRotation(SGCore::EFinger finger) const;

    /// <summary> The lengths of one Sense Glove finger's sections, in mm. </summary>
    SG_NODISCARD const std::vector<Kinematics::Vect3D>& GetGloveLengths(SGCore::EFinger finger) const;

public:
    /// <summary> Place incoming sensor data into the right format, according to this glove's model. </summary>
    SG_NODISCARD std::vector<std::vector<Kinematics::Vect3D>> ToGloveAngles(
            const std::vector<std::vector<float>>& sensorAngles) const;

    /// <summary> Returns true if this SG_Model has the same values as another. </summary>
    SG_NODISCARD bool Equals(const SenseGloveInfo& senseGloveGloveInfo, bool bGeometryOnly = false) const;

public:
    /// <summary> Create a string representation for logging. If shortNotation is false, all values are reported.
    /// </summary>
    SG_NODISCARD std::string ToString(bool bShortNotation) const;

    /// <summary> Create a string representation for fast logging. </summary>
    SG_NODISCARD std::string ToString() const;

    /// <summary> Serialize this HandProfile into a string representation. </summary>
    SG_NODISCARD std::string Serialize() const;
};