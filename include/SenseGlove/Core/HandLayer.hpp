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
 * A way to access all sorts of Hand Tracking and -Haptics without needing to
 * cache any device instances.
 * Use this layer if you don't care where a HandPose is coming from, and are
 * fine with calling generic haptic functions.
 */


#pragma once

#include <memory>
#include <vector>

#include "CustomWaveform.hpp"
#include "DeviceTypes.hpp"
#include "HapticGlove.hpp"
#include "Platform.hpp"
#include "Tracking.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Vect3D;
        class Quat;
    }// namespace Kinematics

    /// <summary> A single vibration pulse for Nova Gloves </summary>
    class SGCORE_API CustomWaveform;

    /// <summary> A glove developed by SenseGlove, that has hand tracking and/or haptic feedback functionality.
    /// </summary>
    class SGCORE_API HapticGlove;

    /// <summary> A way to access all sorts of Hand Tracking and -Haptics without needing to cache any device instances.
    /// </summary>
    class SGCORE_API HandPose;

    /// <summary> A way to access all sorts of Hand Tracking and -Haptics without needing to cache any device instances.
    /// </summary>
    class SGCORE_API HandLayer;

}// namespace SGCore

/// <summary> A way to access all sorts of Hand Tracking and -Haptics without needing to cache any device instances.
/// </summary>
class SGCORE_API SGCore::HandLayer
{
    //--------------------------------------------------------------------------------------
    // Generic Interface for ease-of-use:

public:
    /// <summary> Returns true if there is a HapticGlove Device connected that corresponds to the chosen hand.
    /// </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static bool DeviceConnected(bool bRightHanded);

    /// <summary> Returns the Device Type of the right / left hand. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static EDeviceType GetDeviceType(bool bRightHanded);

    /// <summary> Returns the handedness of the first device you can find; true for right, false for left. Use this for
    /// testing a single glove. </summary>
    /// <returns></returns>
    static bool GetFirstGloveHandedness();

    /// <summary> Returns the number of Haptic Gloves connected to the system. </summary>
    /// <returns></returns>
    static int32_t GlovesConnected();

    /// <summary> Retrieve a Glove Instance for the right- or left hand to do more complicated, device-specific stuff.
    /// </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="out_glove"></param>
    /// <returns></returns>
    static bool GetGloveInstance(bool bRightHanded, std::shared_ptr<HapticGlove>& out_glove);

    //--------------------------------------------------------------------------------------
    // Calibration

    /// <summary> Returns the calibration state of the chosen hand. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static EHapticGloveCalibrationState GetCalibrationState(bool bRightHanded);

    /// <summary> Returns the Calibration Instructions for the chosen hand. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static std::string GetCalibrationInstructions(bool bRightHanded);

    /// <summary> Reset the calibration of the left/right hand. </summary>
    /// <param name="bRightHanded"></param>
    static void ResetCalibration(bool bRightHanded);

    /// <summary> Reset the calibration of the left/right hand. </summary>
    /// <param name="bRightHanded"></param>
    static void EndCalibration(bool bRightHanded);

    /// <summary> Windows-only. If calibration is available (via SenseCom, for instance) we can use this to (re)load it. This step happens autmagically at the start of your runtime. </summary>
    static void LoadCalibrationFromDisk();

    /// <summary> Clears profiles on disk if any exist. </summary>
    static void ClearProfilesOnDisk();

    //--------------------------------------------------------------------------------------
    // Tracking

    /// <summary> Attempt to get the HandPose through any of our gloves. You don't care which one is on the other side,
    /// as long as you get one. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="out_handPose"></param>
    /// <returns></returns>
    static bool GetHandPose(bool bRightHanded, HandPose& out_handPose);

    /// <summary> Calculate the Wrist Location of the chosen hand, based on a reference location and tracking hardware.
    /// </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="referencePosition"></param>
    /// <param name="referenceRotation"></param>
    /// <param name="trackingHardware"></param>
    /// <param name="out_wristPosition"></param>
    /// <param name="out_wristRotation"></param>
    static void GetWristLocation(
            bool bRightHanded,
            const SGCore::Kinematics::Vect3D& referencePosition, const Kinematics::Quat& referenceRotation,
            EPositionalTrackingHardware trackingHardware,
            Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation);

    //--------------------------------------------------------------------------------------
    // Haptics

    /// <summary> Stop all haptics on the chosen hand. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static void StopAllHaptics(bool bRightHanded);

    /// <summary> Sends all haptics in the queue for the Left / Right hand. </summary>
    /// <param name="bRightHanded"></param>
    static bool SendHaptics(bool bRightHanded);

    /// <summary> Returns true if the glove for this hand supports a custom waveform vibration on said location.
    /// </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="atLocation"></param>
    /// <returns></returns>
    static bool SupportsCustomWaveform(bool bRightHanded, EHapticLocation atLocation);

    /// <summary> Send a Custom Waveform to a glove at a specific location. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="out_waveform"></param>
    /// <param name="location"></param>
    /// <returns></returns>
    static bool SendCustomWaveform(bool bRightHanded, CustomWaveform& out_waveform, EHapticLocation location);

    /// <summary> Tell a specific hand to hold the force-feedback at a certain level. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="finger"></param>
    /// <param name="level01"></param>
    /// <param name="bSendImmediate"></param>
    static bool QueueCommand_ForceFeedbackLevel(bool bRightHanded, int32_t finger, float level01, bool bSendImmediate);

    /// <summary> Queue Force Feedback for multiple fingers. Up to 5. Make sure the value is not NULL. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="levels01"></param>
    /// <param name="bSendImmediate"></param>
    /// <returns></returns>
    static bool QueueCommand_ForceFeedbackLevels(bool bRightHanded, const std::vector<float>& levels01, bool bSendImmediate);

    /// <summary> Queue a command to set the vibration level(s) of a Haptic Glove's finger. Note: This is only for
    /// Nova 1.0 and DK1.0. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="levels01"></param>
    /// <param name="bSendImmediate"></param>
    /// <returns></returns>
    static bool QueueCommand_VibroLevels(bool bRightHanded, const std::vector<float>& levels01, bool bSendImmediate);

    /// <summary> Queue a command to set the vibration level(s) of a Haptic Glove's finger. Note: This is only for
    /// Nova 1.0 and DK1.0. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="finger"></param>
    /// <param name="level01"></param>
    /// <param name="bSendImmediate"></param>
    /// <returns></returns>
    static bool QueueCommand_VibroLevel(bool bRightHanded, int32_t finger, float level01, bool bSendImmediate);

    /// <summary> Queue a vibration level command for a specific HapticLocation. If the gloves has this vibration motor
    /// installed. Cross-compatible with Nova 2.0. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="finger"></param>
    /// <param name="level01"></param>
    /// <param name="bSendImmediate"></param>
    /// <returns></returns>
    static bool QueueCommand_VibroLevel(
            bool bRightHanded, EHapticLocation atLocation, float level01, bool bSendImmediate);

    /// <summary> Returns true if the chosen glove supports active contact feedback on the Wrist. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static bool SupportsWristSqueeze(bool bRightHanded);

    /// <summary> Queue a command to set a squeeze level on the wrist, and optionally send it right away. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="squeezeLevel01"></param>
    /// <param name="bSendImmediate"></param>
    /// <returns></returns>
    static bool QueueCommand_WristSqueeze(bool bRightHanded, float squeezeLevel01, bool bSendImmediate);

    /// <summary> Returns true is the chosen hand supports flexion locking; automatic locking of FFB when flexed beyond
    /// a specific point. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static bool SupportsFlexionLocks(bool bRightHanded);

    /// <summary> If the flexion exceeds a particular value, turn on the Force-Feedback. </summary>
    /// <returns></returns>
    static bool QueueCommand_FlexionLock(bool bRightHanded, int32_t finger, float flexion01, bool bSendImmediate);

    /// <summary> Stop any Flexion Threshold active on the chosen finger. </summary>
    /// <returns></returns>
    static bool QueueCommand_ClearFlexionLock(bool bRightHanded, int32_t finger, bool bSendImmediate);

public:
    HandLayer() = delete;
    virtual ~HandLayer() = delete;
};