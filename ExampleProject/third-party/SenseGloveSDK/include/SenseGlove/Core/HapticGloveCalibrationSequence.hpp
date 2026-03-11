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
    namespace Calibration
    {
        class CalibrationDataPoint;

        /// <summary> A sequence which collects data points until specific criteria have been met. It must be 'fed' an Update command from your program in order to work. </summary>
        class SGCORE_API HapticGloveCalibrationSequence;

        class SensorRange;
    }// namespace Calibration

    namespace Kinematics
    {
        class BasicHandModel;

        class Vect3D;
    }// namespace Kinematics

    class HandPose;

    class HandProfile;

    class HapticGlove;
}// namespace SGCore

/// <summary> A sequence which collects data points until specific criteria have been met. It must be 'fed' an Update command from your program in order to work. </summary>
class SGCORE_API SGCore::Calibration::HapticGloveCalibrationSequence
{
public:
    /// <summary> The maximum buffer size for calibration points. Once calibrationPoints exceeds this value, the </summary>
    static int32_t GetMaxDataPoints();

public:
    //--------------------------------------------------------------------------------------
    // Profile Generation

    /// <summary> Converts a calibration range taken from a Calibration sequence, and converts it into a profile. Use this if you're not actually using the sequence. </summary>
    /// <param name="sensorRange"></param>
    /// <param name="forDevice"></param>
    /// <param name="bRightHand"></param>
    /// <param name="out_profile"></param>
    /// <returns></returns>
    static bool CompileProfile(const SensorRange& sensorRange, SGCore::EDeviceType forDevice, bool bRightHanded,
                               SGCore::HandProfile& out_profile);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
public:
#else   /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
protected:
#endif  /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    HapticGloveCalibrationSequence();

public:
    /// <summary> Create a new instance of a base HapitcGlove Calibration Sequence. </summary>
    /// <param name="gloveToCalibrate"></param>
    explicit HapticGloveCalibrationSequence(std::shared_ptr<SGCore::HapticGlove> linkedGlove);

    /**
     * The copy constructor.
     */
    HapticGloveCalibrationSequence(const HapticGloveCalibrationSequence& rhs);

    /**
     * The move constructor.
     */
    HapticGloveCalibrationSequence(HapticGloveCalibrationSequence&& rhs) noexcept;

    virtual ~HapticGloveCalibrationSequence();

public:
    /**
     * The copy assignment operator.
     */
    HapticGloveCalibrationSequence& operator=(const HapticGloveCalibrationSequence& rhs);

    /**
     * The move assignment operator.
     */
    HapticGloveCalibrationSequence& operator=(HapticGloveCalibrationSequence&& rhs) noexcept;

public:
    /// <summary> Glove linked to this calibration sequence. Will attempt to grab data from this glove evey time Update() is called. </summary>
    [[nodiscard]] std::shared_ptr<HapticGlove> GetLinkedGlove() const;

    void SetLinkedGlove(std::shared_ptr<SGCore::HapticGlove> linkedGlove);

    /// <summary> Calibration points collected during this calibration process. One is added every time the "Update()" function is called.
    /// Used to create a profile after the calibration finishes. </summary>
    [[nodiscard]] std::vector<CalibrationDataPoint>& GetCalibrationPoints() const;

    /// <summary> How much time has elapsed during this calibration sequence. Useful for logging or for automated functions. </summary>
    [[nodiscard]] float GetElapsedTime() const;

    /// <summary> Used to determine if the user has manually ended the sequence, to prevent us from adding any more calibration points. </summary>
    [[nodiscard]] bool IsManuallyCompleted() const;

protected:
    void SetManuallyCompleted(bool bManuallyCompleted);

protected:
    [[nodiscard]] bool NeedsHandModel() const;

    /// <summary> Kinematic information to generate a calibration preview pose. </summary>
    [[nodiscard]] const Kinematics::BasicHandModel& GetHandModel() const;

    void SetHandModel(const Kinematics::BasicHandModel& handModel);

public:
    /// <summary> If a sequence consists of multiple stages, this integer will show you which one is currently active. </summary>
    [[nodiscard]] virtual int32_t GetCurrentStage() const;

    /// <summary> Returns the amount of calibration points collected so far. </summary>
    [[nodiscard]] std::size_t GetCalibrationPointsCount() const;

    /// <summary> Whether or not this sequence was completed as per its own rules. </summary>
    /// <returns></returns>
    [[nodiscard]] virtual bool AutoCompleted() const;

    /// <summary> Returns true if this sequence is marked as 'complete' and can begin compiling a profile. </summary>
    [[nodiscard]] virtual bool Completed() const;

public:
    //--------------------------------------------------------------------------------------
    // Sequence Functions

    /// <summary> Resets this calibration sequence's data, but not it's LinkedGlove. </summary>
    virtual void Reset();

    virtual void AddDataPoint(const std::vector<Kinematics::Vect3D>& calibrationPoints);

    /// <summary> Update this calibration sequence with new data. We use deltaSeconds to check for things like stability. </summary>
    /// <param name="deltaSeconds"></param>
    virtual void Update(float deltaSeconds);

    /// <summary> Manual confirmation of whatever step we're supposed to making at the moment. </summary>
    virtual void ConfirmCurrentStep();

public:
    //--------------------------------------------------------------------------------------
    // Profile Generation

    /// <summary> Compile a min/max range from the data points collected by this sequence. Returns true if it's actually possible. </summary>
    /// <param name="out_sensorRange"></param>
    /// <returns></returns>
    virtual bool CompileRange(SensorRange& out_sensorRange) const;

    /// <summary> Compile a profile from the data points collected by this sequence. Returns true if it's actually possible. </summary>
    /// <param name="forDevice"></param>
    /// <param name="bRightHanded"></param>
    /// <param name="profile"></param>
    /// <returns></returns>
    virtual bool CompileProfile(SGCore::EDeviceType forDevice, bool bRightHanded,
                                SGCore::HandProfile& out_profile) const;

    //--------------------------------------------------------------------------------------
    // Utility Functions

    /// <summary> Returns the current HandPose; either the one we should be making, or what it would look like at the moment. </summary>
    /// <param name="out_currentHandPose"></param>
    /// <returns></returns>
    bool GetHandPose(SGCore::HandPose& out_currentHandPose) const;

    /// <summary> Returns the current HandPose; either the one we should be making, or what it would look like at the moment. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="out_currentHandPose"></param>
    /// <returns></returns>
    virtual bool GetHandPose(bool bRightHanded, SGCore::HandPose& out_currentHandPose) const;

    /// <summary> Retrieve instructions on what to do during the current step. </summary>
    /// <returns></returns>
    [[nodiscard]] virtual std::string GetCurrentInstruction(const std::string& nextStepKey = std::string{""}) const;
};
