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

#include "HapticGloveCalibrationSequence.hpp"
#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    namespace Calibration
    {
        class SGCORE_API HapticGloveQuickCalibration;
    }// namespace Calibration

    class HandProfile;
}// namespace SGCore

class SGCORE_API SGCore::Calibration::HapticGloveQuickCalibration : public HapticGloveCalibrationSequence
{
#if SG_PLATFORM_ANDROID
private:
    friend class SGCore::HapticGlove;
#endif  /* SG_PLATFORM_ANDROID */

public:
    /// <summary> Default time in seconds, to end this sequence. 15 seconds is very quick for some people. </summary>
    static float GetDefaultAutoEndTimeout();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
public:
#else   /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
private:
#endif  /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    HapticGloveQuickCalibration();

public:
    /// <summary> Create a new instance of a QuickCalibration for Haptic Gloves. </summary>
    /// <param name="gloveToCalibrate"></param>
    /// <param name="autoEndTimeout"></param>
    explicit HapticGloveQuickCalibration(std::shared_ptr<SGCore::HapticGlove> gloveToCalibrate,
                                float autoEndTimeout = GetDefaultAutoEndTimeout());

    /**
     * The copy constructor.
     */
    HapticGloveQuickCalibration(const HapticGloveQuickCalibration& rhs);

    /**
     * The move constructor.
     */
    HapticGloveQuickCalibration(HapticGloveQuickCalibration&& rhs) noexcept;

    virtual ~HapticGloveQuickCalibration() override;

public:
    /**
     * The copy assignment operator.
     */
    HapticGloveQuickCalibration& operator=(const HapticGloveQuickCalibration& rhs);

    /**
     * The move assignment operator.
     */
    HapticGloveQuickCalibration& operator=(HapticGloveQuickCalibration&& rhs) noexcept;

public:
    /// <summary> Time, in seconds, after which this sequence stops gathering data. Based on the deltaSeconds variable passed in the Update() function. </summary>
    [[nodiscard]] float GetAutoEndTimeout() const;

    /// <summary> When compiling the final profile, we use a Weighted Moving Average filter with this period to filer out some outliers. </summary>
    [[nodiscard]] int32_t GetSmoothingSamples() const;

    /// <summary> The min/max values recorded during this calibration sequence. </summary>
    [[nodiscard]] const SensorRange& GetSensorRange() const;

    /// <summary> A temporary profile to apply the sensorRange to. Used to generate a 'preview' HandPose. </summary>
    [[nodiscard]] SGCore::HandProfile& GetTemporaryProfile() const;

    /// <summary> Determines if the user has moved enough so that we can animate. </summary>
    [[nodiscard]] bool CanAnimate() const;

protected:
    [[nodiscard]] float GetMovedTime() const;

    [[nodiscard]] bool IsNewProfile() const;

public:
    /// <summary> This sequence autocompletes after its autoEndTime has elapsed. </summary>
    [[nodiscard]] virtual bool AutoCompleted() const override;

public:
    //--------------------------------------------------------------------------------------
    // Sequence Functions

    /// <summary> Resets data points, min/max ranges and profile. </summary>
    virtual void Reset() override;

    /// <summary> Update this calibration sequence with new data. We use deltaSeconds to check for things like stability. </summary>
    /// <param name="deltaSeconds"></param>
    virtual void Update(float deltaSeconds) override;

    /// <summary> Add a new datapoint to this sequence's collection. Updates the range and profile used to generate a preview. </summary>
    /// <param name="calibrationData"></param>
    virtual void AddDataPoint(const std::vector<Kinematics::Vect3D>& calibrationData) override;

    /// <summary> After we confirm the current step, we're basically done. </summary>
    virtual void ConfirmCurrentStep() override;

    //--------------------------------------------------------------------------------------
    // Profile Functions

    /// <summary> Compile a sensor range from the data points collected while the sequence was running. Smoothed by a Moving Average Filter. </summary>
    /// <param name="out_sensorRange"></param>
    /// <returns></returns>
    virtual bool CompileRange(SensorRange& out_sensorRange) const override;

    //--------------------------------------------------------------------------------------
    // Utility Functions

    /// <summary> Returns a 'preview' of what a HandPose with this sequence's current settings would look like. </summary>
    /// <param name="bRightHand"></param>
    /// <param name="out_currentHandPose"></param>
    /// <returns></returns>
    virtual bool GetHandPose(bool bRightHanded, SGCore::HandPose& out_currentHandPose) const override;

    /// <summary> Retrieve instructions on what to do during the current step. </summary>
    /// <param name="nextStepKey"></param>
    /// <returns></returns>
    virtual std::string GetCurrentInstruction(const std::string& nextStepKey = std::string{""}) const override;
};
