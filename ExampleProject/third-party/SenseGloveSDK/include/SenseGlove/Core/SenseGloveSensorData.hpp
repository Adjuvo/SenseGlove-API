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
 * Parsed sensor data coming form a Sense Glove.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Fingers.hpp"
#include <SenseGlove/Common/Platform.hpp>

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
    [[nodiscard]] static SenseGloveSensorData Empty();

    /// <summary> Deserialize Sense Glove sensor data from a raw char[] received through IPC. </summary>
    static SenseGloveSensorData Parse(const std::string& rawData, const SenseGloveInfo& gloveInfo);

    /// <summary> Deserialize a HandProfile back into usable values. </summary>
    [[nodiscard]] static SenseGloveSensorData Deserialize(const std::string& serializedString);

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
    [[nodiscard]] const std::vector<std::vector<float>>& GetSensorAngles() const;

    /// <summary> Get the glove angles of a specific finger segment. </summary>
    [[nodiscard]] std::vector<float> GetSensorAngles(EFinger finger) const;

    /// <summary> Returns all glove angles in a sequence, without splitting them per finger. </summary>
    [[nodiscard]] std::vector<float> GetAngleSequence() const;

    [[nodiscard]] const Kinematics::Quat& GetImuRotation() const;

    /// <summary> Check how many values have been parsed from the Sensor String. </summary>
    [[nodiscard]] int32_t GetParsedValues() const;

public:
    /// <summary> Check if the IMU was properly parsed. </summary>
    [[nodiscard]] bool IsImuParsed() const;

protected:
    void SetImuParsed(bool bImuParsed);

public:
    /// <summary> Returns true if the values of both data are equal. </summary>
    [[nodiscard]] bool Equals(const SenseGloveSensorData& senseGloveSensorData) const;

public:
    /// <summary> Retrieve a simple representation of this sensor data for debugging purposes. </summary>
    [[nodiscard]] std::string ToString() const;

    /// <summary> Serialize this HandProfile into a string representation. </summary>
    [[nodiscard]] std::string Serialize() const;
};