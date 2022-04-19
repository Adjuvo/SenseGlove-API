#pragma once

#include "SGCore.h"
#include "Vect3D.h"
#include "Quat.h"
#include "Fingers.h"
#include <vector>


#include "Values.h"

namespace SGCore
{
    /// <summary> Tracking Hardware used for positional tracking. </summary>
    enum SGCORE_API PosTrackingHardware
    {
        /// <summary> Custom tracking hardware, we don't apply any offsets </summary>
        Custom = 0,
        /// <summary> HTC Vive Tracker (v1.0 or v2.0). </summary>
        ViveTracker,
        /// <summary> Oculus Touch controller (left or right) for Rift S and Quest 1 </summary>
        OculusTouch,
        /// <summary> Touch controller for Oculus Quest 2 </summary>
        Quest2Controller,
        /// <summary> Pico Neo 2 Controller(s) </summary>
        PicoNeo2,
        /// <summary> Pico Neo 3 Controller(s) </summary>
        PicoNeo3,
    };

	class SGCORE_API Tracking
	{
    public:

        //---------------------------------------------------------------------------
        // Generic Methods

        /// <summary> Knowing a position & rotation in 3D space, calculate a relative location based on offsets. </summary>
        /// <param name="trackedPos"></param>
        /// <param name="trackedRot"></param>
        /// <param name="posOffset"></param>
        /// <param name="rotOffset"></param>
        /// <param name="newPos"></param>
        /// <param name="newRot"></param>
        static void CalculateLocation(Kinematics::Vect3D trackedPos, Kinematics::Quat trackedRot, Kinematics::Vect3D posOffset, Kinematics::Quat rotOffset, Kinematics::Vect3D& newPos, Kinematics::Quat& newRot)
        {
            newRot = trackedRot * rotOffset;
            newPos = trackedPos + (trackedRot * posOffset);
        }

        //---------------------------------------------------------------------------
        // SenseGlove Related

        //TrackingMount -> SG Glove

        /// <summary> Positional offset from each finger to the glove origin </summary>
        const static std::vector<Kinematics::Vect3D> sg_fingerToGloveOrigin_Pos;

        /// <summary>  </summary>
        const static std::vector<Kinematics::Quat> sg_fingerToGloveOrigin_Rot;

        //SG Glove -> Hand

        /// <summary> Default position offset from glove origin to wrist location, in mm. </summary>
        const static Kinematics::Vect3D sg_gloveWristOffsetPos;
        /// <summary> Default rotation offset from glove origin to wrist location. </summary>
        const static Kinematics::Quat sg_gloveWristOffsetRot;

        /// <summary> Get the position and rotation offsets to go from the glove origin to the mounted position </summary>
        /// <remarks> Based on CAD. needs to be inverted when going from tracker to glove origin. </remarks>
        /// <param name="rightHand"></param>
        /// <param name="toFinger"></param>
        /// <param name="iPos"></param>
        /// <param name="iRot"></param>
        static void GetSenseGloveOffset_Glove_Mount(bool rightHand, Finger toFinger, Kinematics::Vect3D& iPos, Kinematics::Quat& iRot);

        /// <summary> Get the offset to get from the TrackedHardware to a SenseGlove mounting location. Combined with Glove-Mount offset to get the glove location. </summary>
        /// <param name="hardware"></param>
        /// <param name="rightHand"></param>
        /// <param name="posOffset"></param>
        /// <param name="rotOffset"></param>
        static void GetSenseGloveOffset_Tracker_Mount(PosTrackingHardware hardware, bool rightHand, Kinematics::Vect3D& posOffset, Kinematics::Quat& rotOffset);


        // Vive Tracker

         /// <summary> Vive Tracker origin to Finger rotational offset </summary>
        const static Kinematics::Vect3D sg_viveToAttach_Pos;
        /// <summary> Vive Tracker origin to Finger rotational offset </summary>
        const static Kinematics::Quat sg_viveToAttach_Rot;

        //Quest 1 / Rift S

        /// <summary> Oculus Touch origin to Finger rotational offset </summary>
        const static Kinematics::Vect3D sg_ocTouchToAttach_Pos;
        /// <summary> Oculus Touch origin to Finger rotational offset </summary>
        const static Kinematics::Quat sg_ocTouchToAttach_Rot;


        //---------------------------------------------------------------------------
        // Nova Related

        /// <summary> Positional offset between Nova Glove Origin and Wrist. </summary>
        const static Kinematics::Vect3D nova_o_to_Wrist_Pos;
        /// <summary> Rotational offset between Nova Glove Origin and Wrist. </summary>
        const static Kinematics::Quat nova_o_to_Wrist_Rot;

        /// <summary> Returns the Offsets that will bring us from the Nova origin to the wrist position </summary>
        /// <param name="rightHand"></param>
        /// <param name="posOffset"></param>
        /// <param name="rotOffset"></param>
        static void GetNovaOffset_Glove_Wrist(bool rightHand, Kinematics::Vect3D& posOffset, Kinematics::Quat& rotOffset);


        const static Kinematics::Vect3D nova_viveToAttach_Pos_R;
        const static Kinematics::Quat nova_viveToAttach_Rot_R;

        const static Kinematics::Vect3D nova_viveToAttach_Pos_L;
        const static Kinematics::Quat nova_viveToAttach_Rot_L;

        const static Kinematics::Vect3D nova_quest2ToAttach_Pos_R;
        const static Kinematics::Quat nova_quest2ToAttach_Rot_R;

        const static Kinematics::Vect3D nova_quest2ToAttach_Pos_L;
        const static Kinematics::Quat nova_quest2ToAttach_Rot_L;

        const static Kinematics::Vect3D nova_pico2ToAttach_Pos_R; //left is a mirror, so we only need R pos.
        const static Kinematics::Quat nova_pico2ToAttach_Rot_R;
        const static Kinematics::Quat nova_pico2ToAttach_Rot_L;


        /// <summary> Retrieves Offsets for a particular device. </summary>
        /// <param name="hardware"></param>
        /// <param name="rightHand"></param>
        /// <param name="posOffset"></param>
        /// <param name="rotOffset"></param>
        static void GetNovaOffset_Tracker_Glove(PosTrackingHardware hardware, bool rightHand, Kinematics::Vect3D& posOffset, Kinematics::Quat& rotOffset);


        static std::string ToString(PosTrackingHardware hardware);
	};
}
