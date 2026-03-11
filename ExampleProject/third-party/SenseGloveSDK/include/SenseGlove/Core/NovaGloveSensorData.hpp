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
 * Nova SensorData, parsed from rae string representations.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Fingers.hpp"
#include "NormalizationState.hpp"
#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;

        class Vect3D;
    }// namespace Kinematics

    namespace Nova
    {
        /// <summary> Enumerators for Nova Data position in the parseable string. </summary>
        enum class SGCORE_API ENovaData : uint8_t
        {
            Sensors,
            Imu,
            Battery,
            All,
        };

        class NovaGloveInfo;

        /// <summary> Sensor Data coming from a Nova, converted into useful values. </summary>
        class SGCORE_API NovaGloveSensorData;
    }// namespace Nova
}// namespace SGCore

/// <summary> Sensor Data coming from a Nova, converted into useful values. </summary>
class SGCORE_API SGCore::Nova::NovaGloveSensorData
{
public:
    /// <summary> Used to access a sensor Movement of the Nova_SensorData class. </summary>
    enum class SGCORE_API ESensorLocation : uint8_t
    {
        /// <summary> Sideways motion; finger splay, moving the thumb away from the hand palm. </summary>
        Abduction,
        /// <summary> Flexion of any sensor. </summary>
        Flexion
    };

public:
    /// <summary> Returns a NovaGloveSensorData without any values. </summary>
    /// <returns></returns>
    [[nodiscard]] static const NovaGloveSensorData& Empty();

    /// <summary> Parse the bytes as they come in from the device into usable values. </summary>
    /// <param name="rawData"></param>
    /// <param name="gloveInfo"></param>
    /// <returns></returns>
    [[nodiscard]] static NovaGloveSensorData Parse(const std::string& rawData,
                                                  const SGCore::Nova::NovaGloveInfo& gloveInfo);

    /// <summary> Convert this sensor data into ta string representation. </summary>
    /// <param name="serializedString"></param>
    /// <returns></returns>
    [[nodiscard]] static NovaGloveSensorData Deserialize(const std::string& serializedString);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Default constructor for NovaGloveSensorData. </summary>
    /// <returns></returns>
    NovaGloveSensorData();

    /// <summary> Create a new instance of a NovaGloveSensorData. </summary>
    /// <param name="values"></param>
    /// <param name="parsedValues"></param>
    /// <param name="imuRotation"></param>
    /// <param name="batteryLevel"></param>
    /// <param name="bCharging"></param>
    /// <returns></returns>
    NovaGloveSensorData(const std::vector<Kinematics::Vect3D>& values, int32_t parsedValues,
                        const Kinematics::Quat& imuRotation, bool bImuParsed, float batteryLevel, bool bCharging);

    /**
     * The copy constructor.
     */
    NovaGloveSensorData(const NovaGloveSensorData& rhs);

    /**
     * The move constructor.
     */
    NovaGloveSensorData(NovaGloveSensorData&& rhs) noexcept;

    virtual ~NovaGloveSensorData();

public:
    /**
     * The copy assignment operator.
     */
    NovaGloveSensorData& operator=(const NovaGloveSensorData& rhs);

    /**
     * The move assignment operator.
     */
    NovaGloveSensorData& operator=(NovaGloveSensorData&& rhs) noexcept;

public:
    /// <summary> Sensor Data State based on the internal data... </summary>
    [[nodiscard]] ENormalizationState GetSensorState() const;

protected:
    void SetSensorState(ENormalizationState state);

public:
    /// <summary> Pronation/Supination, Flexion/Extension and Abduction/Adduction values for each finger. </summary>
    [[nodiscard]] const std::vector<Kinematics::Vect3D>& GetSensorValues() const;

    /// <summary> Returns the sensor movement of a specific finger. </summary>
    /// <param name="finger"></param>
    /// <param name="location"> If a Nova glove has only one flexion sensor, it will return the same value for
    /// FlexionProximal and FlexionDistal.</param>
    [[nodiscard]] float GetSensorValue(EFinger finger, NovaGloveSensorData::ESensorLocation location) const;

    /// <summary> The number of values that were parsed from the sensor string. </summary>
    [[nodiscard]] int32_t GetParsedValues() const;

public:
    /// <summary> Quaternion rotation relative to magnetic north. </summary>
    [[nodiscard]] const Kinematics::Quat& GetImuRotation() const;

    /// <summary> Whether the IMU values were all successfully parsed, or not. </summary>
    [[nodiscard]] bool IsImuParsed() const;

protected:
    void SetImuParsed(bool bImuParsed);

public:
    /// <summary> A value between 0..1 that represents the battery level of this Nova Glove (0 .. 100%). Returns -1
    /// if the value wasn't received. </summary>
    [[nodiscard]] float GetBatteryLevel() const;

    /// <summary> Returns true if this NovaGlove is connected to a power source. </summary>
    [[nodiscard]] bool IsCharging() const;

public:
    /// <summary> Returns true if this sensor data contains the same values as another. </summary>
    /// <param name="novaSensorData"></param>
    /// <returns></returns>
    [[nodiscard]] bool Equals(const NovaGloveSensorData& novaSensorData) const;

public:
    /// <summary> Create a readable string representation of this Sensor Data. </summary>
    /// <returns></returns>
    [[nodiscard]] std::string ToString() const;

    /// <summary> Convert this sensor data into a string so it can be stored on disk. </summary>
    /// <returns></returns>
    [[nodiscard]] std::string Serialize() const;
};