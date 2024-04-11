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
 * An interface for any of our gloves that can track hand motion and/or send
 * force / vibrotactile feedback.
 */


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Platform.hpp"
#include "SGDevice.hpp"
#include "Tracking.hpp"

namespace SGCore
{
    /// <summary> All of the locations supported by the SenseGlove API </summary>
    enum class SGCORE_API EHapticLocation : uint8_t
    {
        /// <summary> Unknown location. Calling haptic function(s) with this parameter will not play anything </summary>
        Unknown,
        /// <summary> Fingertip of the Thumb </summary>
        ThumbTip,
        /// <summary> Fingertip of the Index Finger </summary>
        IndexTip,
        /// <summary> Fingertip of the Middle Finger </summary>
        MiddleTip,
        /// <summary> Fingertip of the Ring Finger </summary>
        RingTip,
        /// <summary> Fingertip of the Pinky Finger </summary>
        PinkyTip,
        /// <summary> Vibration on the hand palm, close to the index finger. </summary>
        PalmIndexSide,
        /// <summary> Vibration on the hand palm close to the pinky finger. </summary>
        PalmPinkySide,
        /// <summary> Play this Haptic Effect on the whole hand. For General Hand Feedback. </summary>
        WholeHand
    };

    /// <summary> The Calibration State of this Glove. </summary>
    enum class SGCORE_API EHapticGloveCalibrationState : uint8_t
    {
        /// <summary> No idea what the calibrationState of this glove is... </summary>
        Unknown,
        /// <summary> One or more sensors still need to move... </summary>
        MoveFingers,
        /// <summary> All sensors have moved.  </summary>
        AllSensorsMoved,
        /// <summary> Calibration is locked in. Done collecting Data. </summary>
        CalibrationLocked
    };

    /// <summary> A single vibration pulse for Nova Gloves </summary>
    class SGCORE_API CustomWaveform;

    namespace Kinematics
    {
        class BasicHandModel;

        class Quat;

        class Vect3D;
    };// namespace Kinematics

    class HandPose;

    /// <summary> A glove developed by SenseGlove, that has hand tracking and/or haptic feedback functionality.
    /// </summary>
    class SGCORE_API HapticGlove;
};// namespace SGCore

/// <summary> A glove developed by SenseGlove, that has hand tracking and/or haptic feedback functionality. </summary>
class SGCORE_API SGCore::HapticGlove : public SGDevice
{
    //--------------------------------------------------------------------------------------
    // DeviceList Integration

public:
    /// <summary> Get all Haptic Gloves detected on this system..</summary>
    /// <returns></returns>
    static std::vector<std::shared_ptr<HapticGlove>> GetHapticGloves(bool bConnectedOnly = true);

    /// <summary> Get the first Haptic Glove detected on this system. </summary>
    /// <param name="out_glove"></param>
    /// <returns></returns>
    static bool GetGlove(std::shared_ptr<HapticGlove>& out_glove);

    /// <summary> Get the first left/right Haptic Glove detected on this system. </summary>
    /// <param name="out_glove"></param>
    /// <returns></returns>
    static bool GetGlove(bool bRightHanded, std::shared_ptr<HapticGlove>& out_glove);

    //---------------------------------------------------------------------------------

public:
    SG_NODISCARD static std::string ToString(EHapticGloveCalibrationState state);

    SG_NODISCARD static std::string ToString(EHapticLocation location);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

    //---------------------------------------------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    /// <summary> The default constructor. </summary>
    HapticGlove();

    /**
     * The copy constructor.
     */
    HapticGlove(const HapticGlove& rhs);

    /**
     * The move constructor.
     */
    HapticGlove(HapticGlove&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~HapticGlove() override;

public:
    /**
     * The copy assignment operator.
     */
    HapticGlove& operator=(const HapticGlove& rhs);

    /**
     * The move assignment operator.
     */
    HapticGlove& operator=(HapticGlove&& rhs) noexcept;

public:
    //--------------------------------------------------------------------------------------
    // Accessors

    //--------------------------------------------------------------------------------------
    // SGDevice Methods

    /// <summary> Get the DeviceType enumerator of this device; used to check if its a SenseGlove/Nova/etc. </summary>
    SG_NODISCARD virtual EDeviceType GetDeviceType() const override;

    /// <summary> Retrieve this glove's unique identifier. </summary>
    SG_NODISCARD virtual const std::string& GetDeviceId() const override;

    /// <summary> Retrieve this glove's hardware (sub) version. "DK1", "DK2", etc. </summary>
    SG_NODISCARD virtual const std::string& GetHardwareVersion() const override;

    /// <summary> Retrieve this device's main firmware version. v4.12 returns 4. </summary>
    SG_NODISCARD virtual int32_t GetFirmwareVersion() const override;

    /// <summary> Retrieve this device's sub firmware version. v4.12 returns 12. </summary>
    SG_NODISCARD virtual int32_t GetSubFirmwareVersion() const override;

public:
    //--------------------------------------------------------------------------------------
    // Tracking Methods

    /// <summary> Returns true if this glove is made for a right hand. If false, it's a left hand. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual bool IsRight() const
#if !SENSEGLOVE_UNREAL_ENGINE_PLUGIN
    = 0
#endif  /* ! SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    ;

    /// <summary> Retrieve this glove's IMU rotation, if if has any. </summary>
    /// <param name="IMU"></param>
    /// <returns></returns>
    virtual bool GetImuRotation(Kinematics::Quat& out_imu);

    /// <summary> Retrieve a HandPose based on the latest profile, but with a specific hand geometry. </summary>
    /// <param name="handGeometry"></param>
    /// <param name="out_handPose"></param>
    /// <returns></returns>
    virtual bool GetHandPose(const Kinematics::BasicHandModel& handGeometry, HandPose& out_handPose) const;

    /// <summary> Retrieve a HandPose based on the latest profile and default hand Geometry. </summary>
    /// <param name="handGeometry"></param>
    /// <param name="out_handPose"></param>
    /// <returns></returns>
    virtual bool GetHandPose(HandPose& out_handPose);

    /// <summary> Returns the Hand Angles calculated by this Nova 2 Glove. Used for input for HandPoses, but can be
    /// used in and of itself. </summary>
    /// <param name="out_handAngles"></param>
    /// <returns></returns>
    virtual bool GetHandAngles(std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles) const;

    const Kinematics::BasicHandModel& GetHandGeometry();
    void SetHandGeometry(const Kinematics::BasicHandModel& handGeometry);

    //--------------------------------------------------------------------------------------
    // Calibration Methods

public:
    /// <summary> Returns the HapticGlove's state of calibration for its on-board sensors. </summary>
    SG_NODISCARD virtual EHapticGloveCalibrationState GetCalibrationState() const;

    /// <summary> Resets internal calibration of the Haptic Glove. </summary>
    virtual void EndCalibration();

    /// <summary> Force-End any form of calibration manually, if any is still running. </summary>
    virtual void ResetCalibration();

    /// <summary> Retrieve the current calibration instruction. </summary>
    SG_NODISCARD virtual std::string GetCalibrationInstruction() const;

    /// <summary> Attempt to load a HapticGlove Profile from disk, if one exists. </summary>
    virtual void TryLoadProfile();

public:
    //--------------------------------------------------------------------------------------
    // Haptics Methods.

    /// <summary> Stops all Haptic effects if any are currently playing. Useful at the end of simulations or when
    /// resetting. </summary>
    virtual void StopHaptics();

    /// <summary> Stops only vibrations. </summary>
    virtual void StopVibrations();

    /// <summary> Take all active commands in the device queue, compile them into one and send them to the device.
    /// </summary>
    /// <returns> Returns true if the message was successfully sent to SenseCom. </returns>
    virtual bool SendHaptics();

    /// <summary> Returns true if the HapticGlove supports vibration feedback on the specified location. </summary>
    /// <param name="atLocation"></param>
    /// <returns></returns>
    SG_NODISCARD virtual bool SupportsCustomWaveform(EHapticLocation atLocation) const;

    /// <summary> Sends a custom waveform to the location specified, provided that the glove has a motor there, and can
    /// support custom waveforms. </summary>
    /// <param name="out_waveform"></param>
    /// <param name="location"></param>
    /// <returns></returns>
    virtual bool SendCustomWaveform(CustomWaveform& out_waveform, EHapticLocation location);

    /// <summary> Queue a list of force-feedback levels, between 0.0 and 1.0. Your list should be sorted from thumb to
    /// pinky. </summary>
    /// <param name="levels01"> Array containing the Force-Feedback levels, from 0.0 (no FFB) to 1.0. A value < 0.0f
    /// will be ignored. </param>
    /// <remarks> Devices that 'only' have on/off FFB will treat any value > 0.0 as 1.0. </remarks>
    /// <returns></returns>
    virtual bool QueueForceFeedbackLevels(const std::vector<float>& levels01);

    /// <summary> Set the Force-Feedback value of a particular finger to a specific level. </summary>
    /// <param name="level01"> Value will be clamped between [0...1], where 0.0f means no Force-Feedback, and 1.0 means
    /// full force-feedback. </param>
    /// <param name="finger"> The finger to which to send the command. </param>
    /// <returns></returns>
    virtual bool QueueForceFeedbackLevel(int32_t finger, float level01);

    /// <summary> Queue a list of vibration levels, between 0.0 and 1.0. Your list should be sorted from thumb to
    /// pinky. </summary>
    /// <param name="levels01"> Array containing the vibration levels, from 0.0 (no vibration) to 1.0. A value < 0.0f
    /// will be ignored. </param>
    /// <remarks> Devices that 'only' have on/off FFB will treat any value > 0.0 as 1.0. </remarks>
    /// <returns></returns>
    virtual bool QueueVibroLevels(const std::vector<float>& levels01);

    /// <summary> Queue a command to set the (continuous) vibration level at a specific location to a set amplitude.
    /// </summary>
    /// <param name="location"></param>
    /// <param name="level01">Value will be clamped between [0...1], where 0.0f means no vibration, and 1.0 means
    /// full vibration.</param>
    /// <returns></returns>
    virtual bool QueueVibroLevel(EHapticLocation location, float level01);

public:
    //--------------------------------------------------------------------------------------
    // 6DoF Position Tracking

    /// <summary> Retrieve the location of the wrist, based on a reference location and default glove-hand offsets.
    /// </summary>
    /// <remarks> The simplest interface, using default offsets. </remarks>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin.</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin.</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="out_wristPosition">The 3D Position of the wrist, in mm, relative to your origin.</param>
    /// <param name="out_wristRotation">The 3D Rotation of the wrist, relative to your origin.</param>
    virtual void GetWristLocation(const Kinematics::Vect3D& referencePosition,
                                  const Kinematics::Quat& referenceRotation,
                                  EPositionalTrackingHardware trackingHardware,
                                  Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation) const;

    /// <summary> Retrieve the location of the glove origin, based on a reference location. </summary>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin.</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin.</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="out_glovePosition">The 3D Position of the glove, in mm, relative to your origin.</param>
    /// <param name="out_gloveRotation">The 3D Rotation of the glove, relative to your origin.</param>
    virtual void GetGloveLocation(const Kinematics::Vect3D& referencePosition,
                                  const Kinematics::Quat& referenceRotation,
                                  EPositionalTrackingHardware trackingHardware,
                                  Kinematics::Vect3D& out_glovePosition, Kinematics::Quat& out_gloveRotation) const;

    //--------------------------------------------------------------------------------------

public:
    /// <summary> Create a String Representation of this Haptic Glove. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual std::string ToString() const override;
};