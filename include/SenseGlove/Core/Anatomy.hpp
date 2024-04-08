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
 * Hard-Coded Database that is used in calibration and in solving.
 * Values herein are used to limit outputs within 'natural' ranges.
 */


#pragma once

#include <cstdint>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        /// <summary> "Database" of anatomical values, such as joint limits. </summary>
        class SGCORE_API Anatomy;

        class Vect3D;
    }// namespace Kinematics
}// namespace SGCore

/// <summary> "Database" of anatomical values, such as joint limits. </summary>
class SGCORE_API SGCore::Kinematics::Anatomy
{
public:
    /// <summary> Total sum of all finger flexion that would be considered "total flexion". </summary>
    static float GetTotalFingerFlexion();

    /// <summary> Total sum of all finger flexion that would be considered "total extension". </summary>
    static float GetTotalFingerExtension();

    /// <summary> Total sum of all thumb flexion that would be considered "total flexion". </summary>
    static float GetTotalThumbFlexion();

    /// <summary> Total sum of all thumb flexion that would be considered "total extension". </summary>
    static float GetTotalThumbExtension();

public:
    /// <summary> Retrieve one of the limits of a finger joint's movement. </summary>
    static float GetFingerJointLimit(bool bRightHanded, int32_t joint, int32_t movement, bool bMax);

    /// <summary> Retrieve one of the limits of a thumb joint's movement. </summary>
    static float GetThumbJointLimit(bool bRightHanded, int32_t joint, int32_t movement, bool bMax);

    /// <summary> Limit a value between specific joint angles. </summary>
    static float ClampJointAngle(float value, int32_t finger, bool bRightHanded, int32_t joint, int32_t movement);

    /// <summary> Convert a total finger flexion in radians into a 0..1 representation. </summary>
    /// <param name="flexionInRadians"></param>
    /// <returns></returns>
    static float NormalizeFingerFlexion(float flexionInRadians);

    /// <summary> Convert a total thumb flexion in radians into a 0..1 representation. </summary>
    /// <param name="flexionInRadians"></param>
    /// <returns></returns>
    static float NormalizeThumbFlexion(float flexionInRadians);

public:
    //-----------------------------------------------------------------------------------------------------------------------------------------
    // Hand Angles for Poses Etc

    /// <summary> Get Hand Angles that would make a Default (Idle) Pose. </summary>
    static std::vector<std::vector<Vect3D>> GetDefaultHandAngles(bool bRightHanded);

    /// <summary> Get Hand Angles that would make a flat hand. </summary>
    static std::vector<std::vector<Vect3D>> GetFlatHandAngles(bool bRightHanded);

    /// <summary> Get hand angles that would make a thumbs up. </summary>
    static std::vector<std::vector<Vect3D>> GetThumbsUpHandAngles(bool bRightHanded);

    /// <summary> Get Hand Angles that would make a fist. </summary>
    static std::vector<std::vector<Vect3D>> GetFistHandAngles(bool bRightHanded);

private:
    struct Impl;

public:
    Anatomy() = delete;
    virtual ~Anatomy() = delete;
};