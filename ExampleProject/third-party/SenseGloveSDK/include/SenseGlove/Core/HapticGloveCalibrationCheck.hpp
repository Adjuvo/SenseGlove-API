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
*
*/


#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "DeviceTypes.hpp"
#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    /// <summary> Startup Stage used to indicate where of not a glove must be recalibrated. </summary>
    enum class SGCORE_API ECalibrationStage : uint8_t
    {
        /// <summary> We've only just started up. User needs to move their hands so we know if we're still in the same sensor range. </summary>
        MoveFingers,

        /// <summary> After moving, we've determined that a calibration must happen for proper hand tracking to happen. </summary>
        CalibrationNeeded,

        /// <summary> After moving, we've determined that a calibration must happen for proper hand tracking to happen. </summary>
        Calibrating,

        /// <summary> We've determined that this needs no (more) calibration to function as intended. </summary>
        Done,
    };

    namespace Calibration
    {
        /// <summary> An algorithm that checks whether or not our current user is running in the same calibration range as last time. </summary>
        class SGCORE_API HapticGloveCalibrationCheck;

        class SensorRange;
    }// namespace Calibration

    namespace Kinematics
    {
        class Vect3D;
    }// namespace Kinematics
}// namespace SGCore

/// <summary> An algorithm that checks whether or not our current user is running in the same calibration range as last time. </summary>
class SGCORE_API SGCore::Calibration::HapticGloveCalibrationCheck
{
public:
    /// <summary> SenseGlove: How far from the threshold one can be where we would still call it 'the same as before'. </summary>
    static float GetSenseGloveThreshold();

    /// <summary> Nova: How far from the threshold one can be where we would still call it 'the same as before'. </summary>
    static float GetNovaGloveThreshold();

    /// <summary> SenseGlove: The minimum amount of sensor flexion movement before we start testing for a smaller hand. </summary>
    static float GetSenseGloveMinFlexion();

    /// <summary> Nova: The minimum amount of sensor flexion movement before we start testing for a smaller hand. </summary>
    static float GetNovaGloveMinFlexion();

    /// <summary> SenseGlove: The minimum amount of sensor movement on the thumb abduction before we start testing for a smaller hand. </summary>
    static float GetSenseGloveMinAbduction();

    /// <summary> Nova: The minimum amount of sensor movement on the thumb abduction before we start testing for a smaller hand. </summary>
    static float GetNovaGloveMinAbduction();

public:
    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Static Checker Functions

    /// <summary> Returns true if this DeviceType requires a calibration check. </summary>
    /// <param name="deviceType"></param>
    /// <returns></returns>
    static bool NeedsCheck(SGCore::EDeviceType deviceType);

    /// <summary> Checks if current values are operating out of the previous range. Returns -1 if all is fine. 0...4 to indicate which finger is out of bounds. </summary>
    /// <param name="previousRange"></param>
    /// <param name="currentValues"></param>
    /// <param name="type"></param>
    /// <returns></returns>
    static int32_t OutOfBounds(const SensorRange& previousRange,
                               const std::vector<Kinematics::Vect3D>& currentValues,
                               SGCore::EDeviceType deviceType);

    /// <summary> Returns true if the user has moved enough in both flexion and thumb abduction movement to be considered 'active'. </summary>
    /// <param name="currentRange"></param>
    /// <param name="type"></param>
    /// <returns></returns>
    static bool MovedMinimum(const std::vector<Kinematics::Vect3D>& currentRange, SGCore::EDeviceType deviceType);

    /// <summary> Returns true if the current sensor values have moved roughly as much as last time. </summary>
    /// <param name="currentRange"></param>
    /// <param name="lastRange"></param>
    /// <param name="type"></param>
    /// <returns></returns>
    static bool MatchesLast(const std::vector<Kinematics::Vect3D>& currentRange,
                            const std::vector<Kinematics::Vect3D>& lastRange,
                            SGCore::EDeviceType deviceType);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The last calibration range can be null, at which point you definitely need calibration. </summary>
    HapticGloveCalibrationCheck();

    /// <summary> The last calibration range can be null, at which point you definitely need calibration. </summary>
    /// <param name="lastCalibrationRange"></param>
    explicit HapticGloveCalibrationCheck(const SGCore::Calibration::SensorRange& lastCalibrationRange);

    /**
     * The copy constructor.
     */
    HapticGloveCalibrationCheck(const HapticGloveCalibrationCheck& rhs);

    /**
     * The move constructor.
     */
    HapticGloveCalibrationCheck(HapticGloveCalibrationCheck&& rhs) noexcept;

    virtual ~HapticGloveCalibrationCheck();

public:
    /**
     * The copy assignment operator.
     */
    HapticGloveCalibrationCheck& operator=(const HapticGloveCalibrationCheck& rhs);

    /**
     * The move assignment operator.
     */
    HapticGloveCalibrationCheck& operator=(HapticGloveCalibrationCheck&& rhs) noexcept;

public:
    [[nodiscard]] ECalibrationStage GetCalibrationStage() const;

    /// <summary> Whether this algorithm has determined if calibration is required, or not. </summary>
    [[nodiscard]] bool ReachedConclusion() const;

public:
    /// <summary> Reset the calibration check. so it may be used again. This does not reset the last range. </summary>
    void Reset();

    /// <summary> Using the currently received Sensor Values, check if calibration is required. This function will have to be called until a conclusion can be reached. </summary>
    /// <param name="currentValues"></param>
    /// <param name="deltaSeconds"></param>
    /// <param name="deviceType"></param>
    void CheckRange(const std::vector<Kinematics::Vect3D>& currentValues, float deltaSeconds, EDeviceType deviceType);
};
