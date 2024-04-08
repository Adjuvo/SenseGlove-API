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
 * Parsed sensor data coming form a Sense Glove.
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
    }// namespace Kinematics

    namespace SG
    {
        class SenseGloveInfo;

        /// <summary> Sense Glove Sensor Data, parsed from a sensor string. </summary>
        class SGCORE_API SenseGloveSensorData;
    }// namespace SG
}// namespace SGCore

/// <summary> Sense Glove Sensor Data, parsed from a sensor string. </summary>
class SGCORE_API SGCore::SG::SenseGloveSensorData
{
public:
    /// <summary> Returns sensor data with no values. </summary>
    SG_NODISCARD static SenseGloveSensorData Empty();

    /// <summary> Deserialize Sense Glove sensor data from a raw char[] received through IPC. </summary>
    static SenseGloveSensorData Parse(const std::string& rawData, const SenseGloveInfo& gloveInfo);

    /// <summary> Deserialize a HandProfile back into usable values. </summary>
    SG_NODISCARD static SenseGloveSensorData Deserialize(const std::string& serializedString);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The basic constructor. </summary>
    SenseGloveSensorData();

    /// <summary> Create a new instance of a Sense Glove Sensor Data class. </summary>
    SenseGloveSensorData(const std::vector<std::vector<float>>& sensorAngles,
                         const Kinematics::Quat& imuRotation,
                         int32_t parsedValues, bool bImuParsed);

    /**
     * The copy constructor.
     */
    SenseGloveSensorData(const SenseGloveSensorData& rhs);

    /**
     * The move constructor.
     */
    SenseGloveSensorData(SenseGloveSensorData&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~SenseGloveSensorData();

public:
    /**
     * The copy assignment operator.
     */
    SenseGloveSensorData& operator=(const SenseGloveSensorData& rhs);

    /**
     * The move assignment operator.
     */
    SenseGloveSensorData& operator=(SenseGloveSensorData&& rhs) noexcept;

public:
    /// <summary> Glove angles in radians, sorted by finger, from proximal to distal. </summary>
    SG_NODISCARD const std::vector<std::vector<float>>& GetSensorAngles() const;

    /// <summary> Get the glove angles of a specific finger segment. </summary>
    SG_NODISCARD std::vector<float> GetSensorAngles(EFinger finger) const;

    /// <summary> Returns all glove angles in a sequence, without splitting them per finger. </summary>
    SG_NODISCARD std::vector<float> GetAngleSequence() const;

    SG_NODISCARD const Kinematics::Quat& GetImuRotation() const;

    /// <summary> Check how many values have been parsed from the Sensor String. </summary>
    SG_NODISCARD int32_t GetParsedValues() const;

public:
    /// <summary> Check if the IMU was properly parsed. </summary>
    SG_NODISCARD bool IsImuParsed() const;

protected:
    void SetImuParsed(bool bImuParsed);

public:
    /// <summary> Returns true if the values of both data are equal. </summary>
    SG_NODISCARD bool Equals(const SenseGloveSensorData& senseGloveSensorData) const;

public:
    /// <summary> Retrieve a simple representation of this sensor data for debugging purposes. </summary>
    SG_NODISCARD std::string ToString() const;

    /// <summary> Serialize this HandProfile into a string representation. </summary>
    SG_NODISCARD std::string Serialize() const;
};