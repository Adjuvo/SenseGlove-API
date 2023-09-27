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
 * Contains the famcy algorithms to process CV_HandOutput into CV_DataPoints
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace CV
    {
        /// <summary> CV Data processed into joint angles and wrist location. </summary>
        class SGCORE_API CVProcessedHandData;

        /// <summary> Unprocessed data received from CV Device(s), used as input for processing. </summary>
        class SGCORE_API CVHandTrackingData;

        /// <summary> Unprocessed data received from CV Device(s), used as input for processing. </summary>
        class SGCORE_API CVKinematics;
    }

    namespace Kinematics
    {
        class Vect3D;
        class Quat;
    } // namespace Kinematics
}// namespace SGCore


/// <summary> Unprocessed data received from CV Device(s), used as input for processing. </summary>
class SGCORE_API SGCore::CV::CVKinematics
{
    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    CVKinematics() = delete;
    virtual ~CVKinematics() = delete;

    //---------------------------------------------------------------------------------------------------------------------------------------------------------
	// Conversion

public:

	/// <summary> Converts CV output (21 joint positions + handed-ness) into a handDataPoint. Returns true if the calculation is succesful. </summary>
	/// <param name="pose"></param>
	/// <param name="dataPoint"></param>
	/// <param name="naturalLimits">If true, joint angles are clamped within their natural limits. </param>
	/// <returns></returns>
    static bool CalculateTrackingData(const CVHandTrackingData& pose, CVProcessedHandData& out_dataPoint, const bool naturalLimits = true);

	/// <summary> Calculates the  wrist location and hand angles and based on the 21 keypoints + handedness in our CV Output. </summary>
	/// <param name="pose"></param>
	/// <param name="wristWorldPos"></param>
	/// <param name="wristWorldRot"></param>
	/// <param name="handAngles"></param>
	/// <param name="naturalLimits"></param>
	/// <returns></returns>
    static bool CalculateHandPoseData(const CVHandTrackingData& pose, Kinematics::Vect3D& out_wristWorldPos, Kinematics::Quat& out_wristWorldRot,
        std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles, const bool naturalLimits = true);


	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	// Wrist Calculations


	/// <summary> Calculate the wrist position and -rotation from a set of keypoints that describe the finger. </summary>
	/// <param name="pose"></param>
	/// <param name="wristWorldPos"></param>
	/// <param name="wristWorldRot"></param>
    static bool CalculateWristLocation(const CVHandTrackingData& pose, Kinematics::Vect3D& out_wristWorldPos, Kinematics::Quat& out_wristWorldRot);


	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	// Finger Calculations

	/// <summary> Calculates the most likely Abduction (z) angle. All of these positons must be relative to the first joint (CMC or MCP), in the thumb/finger coordinate system. </summary>
	/// <param name="medialJoint"></param>
	/// <param name="distalJoint"></param>
	/// <param name="fingerTip"></param>
	/// <returns></returns>
    static float EstimateAbd(const Kinematics::Vect3D& medialJoint, const Kinematics::Vect3D& distalJoint, const Kinematics::Vect3D& fingerTip);

	/// <summary> Calculates the flexion of the last joint, based on  </summary>
	/// <param name="j0Flex"></param>
	/// <param name="j1Flex"></param>
	/// <param name="tipRelToj0"></param>
	/// <param name="j2RelToj0"></param>
	/// <returns></returns>
    static float CalculateLastFlexion(float j0Flex, float j1Flex, const Kinematics::Vect3D& tipRelToj0, const Kinematics::Vect3D& j2RelToj0);



	/// <summary> The actual hand angle calculations. First we define a "working plane"; joint start rotation + abduction. j0 flexion is calculated using aTan2, j1 flexion using vector.anglebetween.
	/// finally, j2 flexion is calculated using aTan2 again, using j0's reference frame. </summary>
	/// <param name="pose"></param>
	/// <param name="wristWorldRot"></param>
	/// <param name="naturalLimits"></param>
	/// <returns></returns>
    static void CalculateHandAngles(const CVHandTrackingData& pose, const Kinematics::Quat& wristWorldRot, std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles, const bool naturalLimits = true);


};
