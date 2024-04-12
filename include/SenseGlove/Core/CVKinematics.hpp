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
 * Contains the fancy algorithms to process CV_HandOutput into CV_DataPoints.
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
    }// namespace CV

    namespace Kinematics
    {
        class Vect3D;
        class Quat;
    }// namespace Kinematics
}// namespace SGCore


/// <summary> Unprocessed data received from CV Device(s), used as input for processing. </summary>
class SGCORE_API SGCore::CV::CVKinematics
{
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    // Conversions

public:
    /// <summary> Converts CV output (21 joint positions + handed-ness) into a handDataPoint. Returns true if the
    /// calculation is successful. </summary>
    /// <param name="pose"></param>
    /// <param name="dataPoint"></param>
    /// <param name="naturalLimits">If true, joint angles are clamped within their natural limits. </param>
    /// <returns></returns>
    static bool CalculateTrackingData(const CVHandTrackingData& pose, CVProcessedHandData& out_dataPoint,
                                      bool bNaturalLimits = true);

    /// <summary> Calculates the  wrist location and hand angles and based on the 21 key points + handedness in our
    /// CV Output. </summary>
    /// <param name="pose"></param>
    /// <param name="wristWorldPosition"></param>
    /// <param name="wristWorldRotation"></param>
    /// <param name="handAngles"></param>
    /// <param name="naturalLimits"></param>
    /// <returns></returns>
    static bool CalculateHandPoseData(const CVHandTrackingData& pose,
                                      Kinematics::Vect3D& out_wristWorldPosition,
                                      Kinematics::Quat& out_wristWorldRotation,
                                      std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles,
                                      bool bNaturalLimits = true);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    // Wrist Calculations

    /// <summary> Calculate the wrist position and -rotation from a set of keypoints that describe the finger.
    /// </summary>
    /// <param name="pose"></param>
    /// <param name="wristWorldPosition"></param>
    /// <param name="wristWorldRotation"></param>
    static bool CalculateWristLocation(const CVHandTrackingData& pose,
                                       Kinematics::Vect3D& out_wristWorldPosition,
                                       Kinematics::Quat& out_wristWorldRotation);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    // Finger Calculations

    /// <summary> Calculates the most likely Abduction (z) angle. All of these positions must be relative to the first
    /// joint (CMC or MCP), in the thumb/finger coordinate system. </summary>
    /// <param name="medialJoint"></param>
    /// <param name="distalJoint"></param>
    /// <param name="fingerTip"></param>
    /// <returns></returns>
    static float EstimateAbd(const Kinematics::Vect3D& medialJoint,
                             const Kinematics::Vect3D& distalJoint,
                             const Kinematics::Vect3D& fingerTip);

    /// <summary> Calculates the flexion of the last joint, based on  </summary>
    /// <param name="j0Flex"></param>
    /// <param name="j1Flex"></param>
    /// <param name="tipRelativeToJ0"></param>
    /// <param name="j2RelativeToJ0"></param>
    /// <returns></returns>
    static float CalculateLastFlexion(float j0Flex, float j1Flex,
                                      const Kinematics::Vect3D& tipRelativeToJ0,
                                      const Kinematics::Vect3D& j2RelativeToJ0);

    /// <summary> The actual hand angle calculations. First we define a "working plane";
    /// joint start rotation + abduction. j0 flexion is calculated using aTan2, j1 flexion using vector.anglebetween.
    /// finally, j2 flexion is calculated using aTan2 again, using j0's reference frame. </summary>
    /// <param name="pose"></param>
    /// <param name="wristWorldRotation"></param>
    /// <param name="naturalLimits"></param>
    /// <returns></returns>
    static void CalculateHandAngles(
            const CVHandTrackingData& pose,
            const Kinematics::Quat& wristWorldRotation, std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles,
            bool bNaturalLimits = true);

    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    CVKinematics() = delete;
    virtual ~CVKinematics() = delete;
};