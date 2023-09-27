/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2023 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Sensor Data comong off the Nova 2.0 Glove.
 * Has certain features the Nova 1.0 Glove does not have, such as multiple flexion sensors, normalization states and Active Strap info.
 * 
 */


#pragma once

#include <memory>
#include <vector>
#include <cstdint>

#include "Platform.hpp"
#include "NormalizationState.hpp"
#include "Fingers.hpp"

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
    //---------------------------------------------------------------------------------
    // Sensor Location Enum

public:

    /// <summary> Used to access a sensor Movement of the Nova_SensorData class. </summary>
    enum class ESensorLocation : int8_t
    {
        /// <summary> Sideways motion; finger splay, movind the thumb away from the hand palm </summary>
        Abduction,
        /// <summary> Flexion of any sensor close to the thumb. </summary>
        Flexion_Proximal,
        /// <summary> flexion of any sensor further from the hub. </summary>
        Flexion_Distal
    };
    
    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
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


    /**
     * The copy assignment operator.
     */
    Nova2GloveSensorData& operator=(const Nova2GloveSensorData& rhs);

    /**
     * The move assignment operator.
     */
    Nova2GloveSensorData& operator=(Nova2GloveSensorData&& rhs) noexcept;

public:

    Nova2GloveSensorData();

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    Nova2GloveSensorData(ENormalizationState normState, std::vector<std::vector<Kinematics::Vect3D>> values, int32_t numberOfVals,
        Kinematics::Quat imuRot, bool imuComplete, float battLvl, bool charging);

    //---------------------------------------------------------------------------------
    // Accessors

public:

    /// <summary> Sensor Data State based on the internal data... </summary>
    SG_NODISCARD ENormalizationState GetSensorState();
    void SetSensorState(ENormalizationState value);

    /// <summary> Pronation/Supination, Flexion/Extension and Abduction/Adduction values for each finger. </summary>
    SG_NODISCARD std::vector<std::vector<Kinematics::Vect3D>> GetSensorValues();
    void SetSensorValues(std::vector<std::vector<Kinematics::Vect3D>> value);

    /// <summary> Quaternion rotation relative to magnetic north. </summary>
    SG_NODISCARD Kinematics::Quat GetIMURotation();
    void SetIMURotation(Kinematics::Quat value);

    /// <summary> Returns true if this NovaGlove is connected to a power source </summary>
    SG_NODISCARD bool GetIsCharging();
    void SetIsCharging(bool value);

    /// <summary> A value between 0..1 that represents the battery level of this Nova Glove (0 .. 100%). Returns -1 if the value wasn't received. </summary>
    SG_NODISCARD float GetBatteryLevel();
    void SetBatteryLevel(float value);

    /// <summary> The number of values that were parsed from the sensor string. </summary>
    SG_NODISCARD int32_t GetParsedValues();
    void SetParsedValues(int32_t value);

    /// <summary> Whether or not the IMU values were all succesfully parsed. </summary>
    SG_NODISCARD bool GetIMUParsed();
    void SetIMUParsed(bool value);


    //---------------------------------------------------------------------------------
    // Member Functions

public:

    /// <summary> Create a readable string representation of this Sensor Data </summary>
    /// <returns></returns>
    SG_NODISCARD std::string ToString() const;

    /// <summary> Returns true if this sensor data contains the same values as another. </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    SG_NODISCARD bool Equals(const Nova2GloveSensorData& other);


    /// <summary> Returns the sensor movement of a specific finger. </summary>
    /// <param name="finger"></param>
    /// <param name="location"> If a Nova glove has only one flexion sensor, it will return the same value for Flexion_Proximal and Flexion_Distal.</param>
    SG_NODISCARD float GetSensorValue(SGCore::EFinger finger, Nova2GloveSensorData::ESensorLocation location);


    //--------------------------------------------------------------------------------------
    // Serialization / Deserialization

    /// <summary> Parse the bytes as they come in from the device into useable values. </summary>
    /// <param name="rawData"></param>
    /// <param name="gloveInfo"></param>
    /// <returns></returns>
    SG_NODISCARD static Nova2GloveSensorData Parse(const std::string& rawData, NovaGloveInfo& gloveInfo);



};
