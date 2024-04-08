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
 * Sensor Data coming off the Nova 2.0 Glove.
 * Has certain features the Nova 1.0 Glove does not have, such as multiple
 * flexion sensors, normalization states and Active Strap info.
 */


#pragma once

#include <memory>
#include <vector>
#include <cstdint>

#include "Fingers.hpp"
#include "NormalizationState.hpp"
#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;

        class Vect3D;
    };// namespace Kinematics

    namespace Nova
    {
        /// <summary> Device information extracted from a Nova Glove. </summary>
        class SGCORE_API NovaGloveInfo;

        /// <summary> Nova Glove 2.0 Sensor data, which had additional feedback and calibration parameters. </summary>
        class SGCORE_API Nova2GloveSensorData;
    } // namespace Nova
}// namespace SGCore


/// <summary> Nova Glove 2.0 Sensor data, which had additional feedback and calibration parameters. </summary>
class SGCORE_API SGCore::Nova::Nova2GloveSensorData
{
public:
    /// <summary> Used to access a sensor Movement of the Nova_SensorData class. </summary>
    enum class ESensorLocation : uint8_t
    {
        /// <summary> Sideways motion; finger splay, moving the thumb away from the hand palm. </summary>
        Abduction,

        /// <summary> Flexion of any sensor close to the thumb. </summary>
        FlexionProximal,

        /// <summary> flexion of any sensor further from the hub. </summary>
        FlexionDistal
    };

public:
    /// <summary> Parse the bytes as they come in from the device into usable values. </summary>
    /// <param name="rawData"></param>
    /// <param name="gloveInfo"></param>
    /// <returns></returns>
    SG_NODISCARD static Nova2GloveSensorData Parse(const std::string& rawData, const NovaGloveInfo& gloveInfo);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /**
     * The default constructor.
     */
    Nova2GloveSensorData();

    Nova2GloveSensorData(ENormalizationState normalizationState,
                         const std::vector<std::vector<Kinematics::Vect3D>>& values, int32_t parsedValues,
                         const Kinematics::Quat& imuRotation, bool bImuParsed, float batteryLevel, bool bCharging);

    /**
     * The copy constructor.
     */
    Nova2GloveSensorData(const Nova2GloveSensorData& rhs);

    /*
     * The move constructor.
     */
    Nova2GloveSensorData(Nova2GloveSensorData&& rhs)
    noexcept;

    virtual ~Nova2GloveSensorData();

public:
    /**
     * The copy assignment operator.
     */
    Nova2GloveSensorData& operator=(const Nova2GloveSensorData& rhs);

    /**
     * The move assignment operator.
     */
    Nova2GloveSensorData& operator=(Nova2GloveSensorData&& rhs) noexcept;

public:
    /// <summary> Sensor Data State based on the internal data. </summary>
    SG_NODISCARD ENormalizationState GetSensorState() const;

protected:
    void SetSensorState(ENormalizationState state);

public:
    /// <summary> Pronation/Supination, Flexion/Extension and Abduction/Adduction values for each finger. </summary>
    SG_NODISCARD const std::vector<std::vector<Kinematics::Vect3D>>& GetSensorValues() const;

protected:
    void SetSensorValues(const std::vector<std::vector<Kinematics::Vect3D>>& values);

public:
    /// <summary> Returns the sensor movement of a specific finger. </summary>
    /// <param name="finger"></param>
    /// <param name="location"> If a Nova glove has only one flexion sensor, it will return the same value for
    /// FlexionProximal and FlexionDistal.</param>
    SG_NODISCARD float GetSensorValue(SGCore::EFinger finger, Nova2GloveSensorData::ESensorLocation location) const;

    /// <summary> The number of values that were parsed from the sensor string. </summary>
    SG_NODISCARD int32_t GetParsedValues() const;

protected:
    void SetParsedValues(int32_t values);

public:
    /// <summary> Quaternion rotation relative to magnetic north. </summary>
    SG_NODISCARD Kinematics::Quat GetImuRotation() const;

protected:
    void SetImuRotation(const Kinematics::Quat& rotation);

public:
    /// <summary> Whether or not the IMU values were all successfully parsed. </summary>
    SG_NODISCARD bool IsImuParsed() const;

protected:
    void SetImuParsed(bool bParsed);

public:
    /// <summary> A value between 0..1 that represents the battery level of this Nova Glove (0 .. 100%). Returns -1 if
    /// the value wasn't received. </summary>
    SG_NODISCARD float GetBatteryLevel() const;

protected:
    void SetBatteryLevel(float level);

public:
    /// <summary> Returns true if this NovaGlove is connected to a power source. </summary>
    SG_NODISCARD bool IsCharging() const;

protected:
    void SetCharging(bool bCharging);

public:
    /// <summary> Returns true if this sensor data contains the same values as another. </summary>
    /// <param name="nova2GloveSensorData"></param>
    /// <returns></returns>
    SG_NODISCARD bool Equals(const Nova2GloveSensorData& nova2GloveSensorData) const;

public:
    /// <summary> Create a readable string representation of this Sensor Dataa. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string ToString() const;
};