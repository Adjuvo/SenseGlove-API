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
 * A way to access all sorts of Hand Tracking and -Haptics without needing to cache any device instances.
 * Use this layer if you don't care where a HandPose is coming from, and are fine with calling generic haptic functions.
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"
#include "DeviceTypes.hpp"
#include "HapticGlove.hpp"
#include "Tracking.hpp"
#include "CustomWaveform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Vect3D;
        class Quat;
    }// namespace Kinematics

    /// <summary> A single vibration pulse for Nova Gloves </summary>
    class SGCORE_API CustomWaveform;

    /// <summary> A glove developed by SenseGlove, that has hand tracking and/or haptic feedback functionality. </summary>
    class SGCORE_API HapticGlove;

     /// <summary> A way to access all sorts of Hand Tracking and -Haptics without needing to cache any device instances. </summary>
    class SGCORE_API HandPose;

    /// <summary> A way to access all sorts of Hand Tracking and -Haptics without needing to cache any device instances. </summary>
    class SGCORE_API HandLayer;

}// namespace SGCore



/// <summary> A way to access all sorts of Hand Tracking and -Haptics without needing to cache any device instances. </summary>
class SGCORE_API SGCore::HandLayer
{
    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    HandLayer() = delete;
    virtual ~HandLayer() = delete;


    //--------------------------------------------------------------------------------------
    // Generic Interface for ease-of-use:

public:

    /// <summary> Returns true if there is a HapticGlove Device connected that corresponds to the chosen hand. </summary>
    /// <param name="rightHand"></param>
    /// <returns></returns>
    static bool DeviceConnected(bool rightHand);


    /// <summary> Returns the Device Type of the right / left hand. </summary>
    /// <param name="rightHand"></param>
    /// <returns></returns>
    static EDeviceType GetDeviceType(bool rightHand);


    /// <summary> Returns the handedness of the first device you can find; true for right, false for left. Use this for testing a ginle glove. </summary>
    /// <returns></returns>
    static bool GetFirstGloveHandedness();

    /// <summary> Returns the number of Haptic Gloves connected to the system </summary>
    /// <returns></returns>
    static int32_t GlovesConnected();


    /// <summary> Retireve a Glove Instance for the right- or left hand to do more cmplixated, device-sepecific stuff. </summary>
    /// <param name="rightHand"></param>
    /// <param name="glove"></param>
    /// <returns></returns>
    static bool GetGloveInstance(bool rightHand, std::shared_ptr<HapticGlove>& out_glove);


    //--------------------------------------------------------------------------------------
    // Tracking


    /// <summary> Retruns the calibration state of the chosen hand. </summary>
    /// <param name="rightHand"></param>
    /// <returns></returns>
    static EHapticGloveCalibrationState GetCalibrationState(bool rightHand);


    /// <summary> Attempt to get the HandPose through any of our gloves. You don't care which one is on the other side, as long as you get one. </summary>
    /// <param name="rightHand"></param>
    /// <param name="handPose"></param>
    /// <returns></returns>
    static bool GetHandPose(bool rightHand, HandPose& out_handPose);


    /// <summary> Calculate the Wirst Location of the chosen hand, based on a reference location and tracking hardware. </summary>
    /// <param name="rightHand"></param>
    /// <param name="referencePosition"></param>
    /// <param name="referenceRotation"></param>
    /// <param name="trackingHardware"></param>
    /// <param name="wristPosition"></param>
    /// <param name="wristRotation"></param>
    static void GetWristLocation(bool rightHand, const SGCore::Kinematics::Vect3D& referencePosition, const Kinematics::Quat& referenceRotation,
        EPositionalTrackingHardware trackingHardware, Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation);


    //--------------------------------------------------------------------------------------
    // Haptics

    /// <summary> Sends all haptics in the queue for the Left / Right hand. </summary>
    /// <param name="rightHand"></param>
    static bool SendHaptics(bool rightHand);

    /// <summary> Stopa all haptics on the chosen hand. </summary>
    /// <param name="rightHand"></param>
    /// <returns></returns>
    static void StopAllHaptics(bool rightHand);

    /// <summary> Tell a specific hand to hold the force-feedback at a certain level. </summary>
    /// <param name="rightHand"></param>
    /// <param name="finger"></param>
    /// <param name="level01"></param>
    /// <param name="sendImmediate"></param>
    static bool QueueCmd_FFBLevel(bool rightHand, int32_t finger, float level01, bool sendImmediate);

    /// <summary> Queue Force Feedback for multiple fingers. Up to 5. Make sure the value is not NULL. </summary>
    /// <param name="rightHand"></param>
    /// <param name="levels01"></param>
    /// <param name="sendImmediate"></param>
    /// <returns></returns>
    static bool QueueCmd_FFBLevels(bool rightHand, std::vector<float> levels01, bool sendImmediate);


    /// <summary> Queue a command to set the vibration level(s) of a Haptic Glove's finger. Note: This is only for Nova 1.0 and DK1.0. </summary>
    /// <param name="rightHand"></param>
    /// <param name="finger"></param>
    /// <param name="level01"></param>
    /// <param name="sendImmediate"></param>
    /// <returns></returns>
    static bool QueueCmd_SetVibroLevel(bool rightHand, int32_t finger, float level01, bool sendImmediate);


    /// <summary> Queue a command to set the vibration level(s) of a Haptic Glove's finger. Note: This is only for Nova 1.0 and DK1.0. </summary>
    /// <param name="rightHand"></param>
    /// <param name="levels01"></param>
    /// <param name="sendImmediate"></param>
    /// <returns></returns>
    static bool QueueCmd_SetVibroLevels(bool rightHand, std::vector<float> levels01, bool sendImmediate);




    /// <summary> Returns true if the glove for this hand supports a custom waveform vibration on said location. </summary>
    /// <param name="rightHand"></param>
    /// <param name="atLocation"></param>
    /// <returns></returns>
    static bool SupportsCustomWaveforms(bool rightHand, EHapticLocation atLocation);

    /// <summary> Send a Custom Waveform to a glove at a specific location </summary>
    /// <param name="rightHand"></param>
    /// <param name="waveform"></param>
    /// <param name="location"></param>
    /// <returns></returns>
    static bool SendCustomWaveform(bool rightHand, CustomWaveform& waveform, EHapticLocation location);


    /// <summary> Retruns tru if the chosen glove supports active contact feedback on the Wrist </summary>
    /// <param name="rightHand"></param>
    /// <returns></returns>
    static bool SupportsWristSqueeze(bool rightHand);


    /// <summary> Queue a command to set a squeeze level on the wrist, and optionally send it right away. </summary>
    /// <param name="rightHand"></param>
    /// <param name="squeezelvl01"></param>
    /// <param name="sendImmediate"></param>
    /// <returns></returns>
    static bool QueueCmd_WristSqueeze(bool rightHand, float squeezelvl01, bool sendImmediate);




    /// <summary> Returns true is the chosen hand supports flexion locking; automatic locking of FFB when flexed beyond a specific point. </summary>
    /// <param name="rightHand"></param>
    /// <returns></returns>
    static bool SupportsFlexionLocks(bool rightHand);

    /// <summary> If the flexion exceeds a particular value, turn on the Force-Feedback </summary>
    /// <returns></returns>
    static bool QueueCmd_FlexionLock(bool rightHand, int32_t finger, float flexion01, bool sendImmediate);

    /// <summary> Stop any Flexion Threshold active on the chosen finger </summary>
    /// <returns></returns>
    static bool QueueCmd_ClearFlexionLock(bool rightHand, int32_t finger, bool sendImmediate);


};
