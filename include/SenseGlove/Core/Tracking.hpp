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
 *
 */


#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Fingers.hpp"
#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;
        class Vect3D;
    }// namespace Kinematics

    /// <summary> Tracking Hardware used for positional tracking. </summary>
    enum class SGCORE_API EPositionalTrackingHardware : uint8_t
    {
        /// <summary> Custom tracking hardware, we don't apply any offsets. </summary>
        Custom = 0,

        /// <summary> HTC Vive Tracker (v1.0 or v2.0). </summary>
        ViveTracker,

        /// <summary> Oculus Touch controller (left or right) for Rift S and Quest 1. </summary>
        OculusTouch,

        /// <summary> Touch controller for Oculus Quest 2. </summary>
        Quest2Controller,

        /// <summary> Pico Neo 2 Controller(s). </summary>
        PicoNeo2,

        /// <summary> Pico Neo 3 Controller(s). </summary>
        PicoNeo3,

        /// <summary> Wrist tracker for the Vive Focus 3. </summary>
        ViveFocus3WristTracker,

        /// <summary> Oculus Touch Controller that comes with the Meta Quest Pro. </summary>
        QuestProController,

        /// <summary> Oculus Quest 3 Controller. </summary>
        Quest3Controller,
    };

    class SGCORE_API Tracking;
}// namespace SGCore

class SGCORE_API SGCore::Tracking
{
public:
    //---------------------------------------------------------------------------
    // Generic Methods

    /// <summary> Knowing a position & rotation in 3D space, calculate a relative location based on offsets. </summary>
    /// <param name="trackedPosition"></param>
    /// <param name="trackedRotation"></param>
    /// <param name="positionOffset"></param>
    /// <param name="rotationOffset"></param>
    /// <param name="out_newPosition"></param>
    /// <param name="out_newRotation"></param>
    static void CalculateLocation(
            const Kinematics::Vect3D& trackedPosition, const Kinematics::Quat& trackedRotation,
            const Kinematics::Vect3D& positionOffset, const Kinematics::Quat& rotationOffset,
            Kinematics::Vect3D& out_newPosition, Kinematics::Quat& out_newRotation);

    //---------------------------------------------------------------------------
    // SenseGlove DK1 Related

    //TrackingMount -> SG Glove

    /// <summary> Positional offset from each finger to the glove origin. </summary>
    static const std::vector<Kinematics::Vect3D>& GetSenseGloveFingerToGlovePositionOrigin();

    /// <summary>  </summary>
    static const std::vector<Kinematics::Quat>& GetSenseGloveFingerToGloveRotationOrigin();

    //SG Glove -> Hand

    /// <summary> Default position offset from glove origin to wrist location, in mm. </summary>
    static const Kinematics::Vect3D& GetSenseGloveWristPositionOffset();

    /// <summary> Default rotation offset from glove origin to wrist location. </summary>
    static const Kinematics::Quat& GetSenseGloveWristRotationOffset();

    /// <summary> Get the position and rotation offsets to go from the glove origin to the mounted position. </summary>
    /// <remarks> Based on CAD. needs to be inverted when going from tracker to glove origin. </remarks>
    /// <param name="bRightHanded"></param>
    /// <param name="toFinger"></param>
    /// <param name="out_iPosition"></param>
    /// <param name="out_iRotation"></param>
    static void GetSenseGloveMountOffset(bool bRightHanded, EFinger toFinger,
                                         Kinematics::Vect3D& out_iPosition, Kinematics::Quat& out_iRotation);

    /// <summary> Get the offset to get from the TrackedHardware to a SenseGlove mounting location. Combined with
    /// Glove-Mount offset to get the glove location. </summary>
    /// <param name="hardware"></param>
    /// <param name="bRightHanded"></param>
    /// <param name="out_positionOffset"></param>
    /// <param name="out_rotationOffset"></param>
    static void GetSenseGloveTrackerMountOffset(EPositionalTrackingHardware hardware, bool bRightHanded,
                                                Kinematics::Vect3D& out_positionOffset,
                                                Kinematics::Quat& out_rotationOffset);

    // Vive Tracker

    /// <summary> Vive Tracker origin to Finger rotational offset. </summary>
    static const Kinematics::Vect3D& GetSenseGloveViveToAttachPosition();

    /// <summary> Vive Tracker origin to Finger rotational offset. </summary>
    static const Kinematics::Quat& GetSenseGloveViveToAttachRotation();

    //Quest 1 / Rift S

    /// <summary> Oculus Touch origin to Finger rotational offset. </summary>
    static const Kinematics::Vect3D& GetSenseGloveOculusTouchToAttachPosition();

    /// <summary> Oculus Touch origin to Finger rotational offset. </summary>
    static const Kinematics::Quat& GetSenseGloveOculusTouchToAttachRotation();

    //---------------------------------------------------------------------------
    // Nova 1.0 Related

    // Hub -> Wrist

    /// <summary> Positional offset between Nova Glove Origin and Wrist. </summary>
    static const Kinematics::Vect3D& GetNovaToWristPositionOffset();

    /// <summary> Rotational offset between Nova Glove Origin and Wrist. </summary>
    static const Kinematics::Quat& GetNovaToWristRotationOffset();

    // Vive Trackers (Vive Pro, Valve Index)

    static const Kinematics::Vect3D& GetRightNovaViveToAttachPosition();
    static const Kinematics::Quat& GetRightNovaViveToAttachRotation();

    static const Kinematics::Vect3D& GetLeftNovaViveToAttachPosition();
    static const Kinematics::Quat& GetLeftNovaViveToAttachRotation();

    // Quest 2 Controllers a.k.a. Oculus Touch v3

    static const Kinematics::Vect3D& GetRightNovaQuest2ToAttachPosition();
    static const Kinematics::Quat& GetRightNovaQuest2ToAttachRotation();

    static const Kinematics::Vect3D& GetLeftNovaQuest2ToAttachPosition();
    static const Kinematics::Quat& GetLeftNovaQuest2ToAttachRotation();

    // Pico Neo 2 - Obsolete / Deprecated.

    static const Kinematics::Vect3D& GetRightNovaPico2ToAttachPosition();// left is a mirror, so we only need R pos.
    static const Kinematics::Quat& GetRightNovaPico2ToAttachRotation();
    static const Kinematics::Quat& GetLeftNovaPico2ToAttachRotation();

    // Quest Pro Controllers a.k.a. Oculus Touch v4??

    static const Kinematics::Vect3D& GetRightNovaQuestProToAttachPosition();
    static const Kinematics::Quat& GetRightNovaQuestProToAttachRotation();

    static const Kinematics::Vect3D& GetLeftNovaQuestProToAttachPosition();
    static const Kinematics::Quat& GetLeftNovaQuestProToAttachRotation();

    // Vive Focus 3 Tracker (also works with XR Elite)

    static const Kinematics::Vect3D& GetRightNovaViveFocus3ToAttachPosition();
    static const Kinematics::Quat& GetRightNovaViveFocus3ToAttachRotation();

    static const Kinematics::Vect3D& GetLeftNovaViveFocus3ToAttachPosition();
    static const Kinematics::Quat& GetLeftNovaViveFocus3ToAttachRotation();

    // Quest 3 Controller (a.k.a. Quest Touch Plus)

    static const Kinematics::Vect3D& GetRightNovaQuest3ToAttachPosition();
    static const Kinematics::Quat& GetRightNovaQuest3ToAttachRotation();

    static const Kinematics::Vect3D& GetLeftNovaQuest3ToAttachPosition();
    static const Kinematics::Quat& GetLeftNovaQuest3ToAttachRotation();



    /// <summary> Returns the Offsets that will bring us from the Nova origin to the wrist position. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="out_positionOffset"></param>
    /// <param name="out_rotationOffset"></param>
    static void GetNovaGloveWristOffset(bool bRightHanded,
                                        Kinematics::Vect3D& out_positionOffset, Kinematics::Quat& out_rotationOffset);

    /// <summary> Retrieves Offsets for a particular device. </summary>
    /// <param name="hardware"></param>
    /// <param name="bRightHanded"></param>
    /// <param name="out_positionOffset"></param>
    /// <param name="out_rotationOffset"></param>
    static void GetNovaGloveTrackerOffset(EPositionalTrackingHardware hardware, bool bRightHanded,
                                          Kinematics::Vect3D& out_positionOffset,
                                          Kinematics::Quat& out_rotationOffset);

    //---------------------------------------------------------------------------
    // Nova 2.0 Related

    // Nova Hub Origin (Middle of USB port) to Wrist

    static const Kinematics::Vect3D& GetRightNova2ToWristPositionOffset();
    static const Kinematics::Quat& GetRightNova2ToWristRotationOffset();

    static const Kinematics::Vect3D& GetLeftNova2ToWristPositionOffset();
    static const Kinematics::Quat& GetLeftNova2ToWristRotationOffset();

    // Quest 2 Tracker Offsets

    static const Kinematics::Vect3D& GetRightNova2Quest2ToAttachPosition();
    static const Kinematics::Quat& GetRightNova2Quest2ToAttachRotation();

    static const Kinematics::Vect3D& GetLeftNova2Quest2ToAttachPosition();
    static const Kinematics::Quat& GetLeftNova2Quest2ToAttachRotation();

    // Quest Pro Tracker Offsets - We don't have the actual physical hardware for this, and might never make one.

    static const Kinematics::Vect3D& GetRightNova2QuestProToAttachPosition();
    static const Kinematics::Quat& GetRightNova2QuestProToAttachRotation();

    static const Kinematics::Vect3D& GetLeftNova2QuestProToAttachPosition();
    static const Kinematics::Quat& GetLeftNova2QuestProToAttachRotation();

     // Vive Trackers (Vive Pro, Valve Index)

    static const Kinematics::Vect3D& GetRightNova2ViveTrackerToAttachPosition();
    static const Kinematics::Quat& GetRightNova2ViveTrackerToAttachRotation();

    static const Kinematics::Vect3D& GetLeftNova2ViveTrackerToAttachPosition();
    static const Kinematics::Quat& GetLeftNova2ViveTrackerToAttachRotation();

    // Vive Focus 3 Tracker (also works with XR Elite)

    static const Kinematics::Vect3D& GetRightNova2ViveWristTrackerToAttachPosition();
    static const Kinematics::Quat& GetRightNova2ViveWristTrackerToAttachRotation();

    static const Kinematics::Vect3D& GetLeftNova2ViveWristTrackerToAttachPosition();
    static const Kinematics::Quat& GetLeftNova2ViveWristTrackerToAttachRotation();

     // Quest 3 Controller (a.k.a. Quest Touch Plus)

    static const Kinematics::Vect3D& GetRightNova2Quest3ToAttachPosition();
    static const Kinematics::Quat& GetRightNova2Quest3ToAttachRotation();

    static const Kinematics::Vect3D& GetLeftNova2Quest3ToAttachPosition();
    static const Kinematics::Quat& GetLeftNova2Quest3ToAttachRotation();

    /// <summary> Returns the Offsets that will bring us from the Nova origin to the wrist position. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="out_positionOffset"></param>
    /// <param name="out_rotationOffset"></param>
    static void GetNova2GloveWristOffset(bool bRightHanded, const std::string& hardwareVersion,
                                         Kinematics::Vect3D& out_positionOffset, Kinematics::Quat& out_rotationOffset);

    /// <summary> Retrieves Offsets for a particular device. </summary>
    /// <param name="hardware"></param>
    /// <param name="bRightHanded"></param>
    /// <param name="out_positionOffset"></param>
    /// <param name="out_rotationOffset"></param>
    static void GetNova2GloveTrackerOffset(EPositionalTrackingHardware hardware, bool bRightHanded,
                                           const std::string& hardwareVersion,
                                           Kinematics::Vect3D& out_positionOffset,
                                           Kinematics::Quat& out_rotationOffset);

    //---------------------------------------------------------------------------

    static std::string ToString(EPositionalTrackingHardware hardware);

public:
    Tracking() = delete;
    virtual ~Tracking() = delete;
};