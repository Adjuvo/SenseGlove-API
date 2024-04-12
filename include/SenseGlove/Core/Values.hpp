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
 * Utility class to process and convert values in different formats.
 */


#pragma once

#include <cstdint>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;

        /// <summary> Utility class to convert values into various formats. </summary>
        class SGCORE_API Values;

        class Vect3D;
    }// namespace Kinematics
}// namespace SGCore

/// <summary> Utility class to convert values into various formats. </summary>
class SGCORE_API SGCore::Kinematics::Values
{
public:
    /// <summary> Converts degrees into radians. </summary>
    static float DegreesToRadians();

    /// <summary> Converts radians into degrees. </summary>
    static float RadiansToDegrees();

    /// <summary> 2*PI is used frequently in angle normalization. </summary>
    static float Get2PI();

public:
    /// <summary> Convert a vector of degrees angles into radians. </summary>
    static Vect3D Radians(const Vect3D& degrees);

    /// <summary> Convert a vector of radian angles into degrees. </summary>
    static Vect3D Degrees(const Vect3D& radians);

    /// <summary> Ensure that a single angle is within the [-Pi...Pi] range. </summary>
    static float NormalizeAngle(float angle, float minAngle, float maxAngle);

    /// <summary> Normalize and angle between a variable range. </summary>
    static float NormalizeAngle(float angle);

    /// <summary> Normalize a set of angles in radians. </summary>
    static Vect3D NormalizeAngles(const Vect3D& angles);

    /// <summary> Ensure that a value remains within the [min...max] range. </summary>
    static float Clamp(float value, float min, float max);

    /// <summary> Ensure that an integer value remains within the [min...max] range. </summary>
    static int32_t Clamp(int32_t value, int32_t min, int32_t max);

    /// <summary> Map a value from one range [from1...from2] to another range [to1 .. to2] </summary>
    static float Map(float value, float from1, float from2, float to1, float to2);

    /// <summary> Map a value from one range [from1...from2] to another range [to1 .. to2] </summary>
    static float Map(float value, float from1, float from2, float to1, float to2, bool clampOutput);

    /// <summary> Map a value from one range [from1...from2] to another range [to1 .. to2],
    /// while ensuring it stays within the [min...max] range. </summary>
    static float Map(float value, float from1, float from2, float to1, float to2, float min, float max);

    /// <summary> Check if two floating points are roughly equal, taking into account the minor differences. </summary>
    static bool FloatEquals(float valueA, float valueB);

    /// <summary> Check if two arrays contain equal values. </summary>
    static bool Equal(const std::vector<Vect3D>& arrayA, const std::vector<Vect3D>& arrayB);

    /// <summary> Check if two arrays contain equal values. </summary>
    static bool Equal(const std::vector<std::vector<Vect3D>>& arrayA, const std::vector<std::vector<Vect3D>>& arrayB);

    /// <summary> Check if two arrays contain equal values. </summary>
    static bool Equal(const std::vector<Quat>& arrayA, const std::vector<Quat>& arrayB);

    /// <summary> Check if two arrays contain equal values. </summary>
    static bool Equal(const std::vector<std::vector<Quat>>& arrayA, const std::vector<std::vector<Quat>>& arrayB);

    /// <summary> Returns an array of Vect3D's, all at 0, 0, 0. Used for quick generation and to avoid NullRefs.
    /// </summary>
    /// <param name="length"></param>
    /// <returns></returns>
    static std::vector<Vect3D> FillZero(int32_t length);

    /// <summary> Returns a 2D of Vect3D's [Length, Width] all at 0, 0, 0. Used for quick generation and to avoid
    /// NullRefs. </summary>
    /// <param name="length"></param>
    /// <param name="width"></param>
    /// <returns></returns>
    static std::vector<std::vector<Vect3D>> FillZero(int32_t length, int32_t width);

    /// <summary> Evaluate x on a curve with points [0.0, 0.0], [0.5, 1.0], [1.0, 0.0] with a smooth transition. Is 0
    /// elsewhere. </summary>
    /// <param name="x"></param>
    static float EvalueSmoothHill(float x);

    //--------------------------------------------------------------------------------------------------------
    // Interpolation Functions

public:
    /// <summary> Interpolate a single Vector </summary>
    static Vect3D InterpolateVector(float t, float t0, float t1, const Vect3D& v0, const Vect3D& v1, bool bClamp);

    /// <summary> Interpolate an array of Vectors </summary>
    static std::vector<Vect3D> InterpolateVectors(
            float t, float t0, float t1,
            const std::vector<Vect3D>& v0, const std::vector<Vect3D>& v1, bool bClamp);

    /// <summary> Interpolate a 2D array of Vectors </summary>
    static std::vector<std::vector<Vect3D>> InterpolateVectors(
            float t, float t0, float t1,
            const std::vector<std::vector<Vect3D>>& v0, const std::vector<std::vector<Vect3D>>& v1, bool bClamp);

    /// <summary> Interpolate a Quaternion Rotaion </summary>
    static Quat InterpolateQuaternion(float t, float t0, float t1, const Quat& q0, const Quat& q1, bool bClamp);

    /// <summary> Allows up to pass clamping, but still takes into account the joint angle limits. </summary>
    static std::vector<std::vector<Vect3D>> InterpolateHandAngles_WithJointAngles(
            float t, float t0, float t1,
            const std::vector<std::vector<Vect3D>>& v0, const std::vector<std::vector<Vect3D>>& v1,
            bool bRightHanded, bool bClamp);

public:
    Values() = delete;
    virtual ~Values() = delete;
};