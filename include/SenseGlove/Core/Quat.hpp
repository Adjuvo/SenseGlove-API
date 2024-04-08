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
 * A Quaternion is a representation of a rotation in 3D space without the
 * problem of Gimbal Lock that exists in Euler representations.
 */


#pragma once

#include <memory>
#include <string>

#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        /// <summary> A rotation in 3D space that can be applied to a 3D vector or converted into Euler Angles.
        /// </summary>
        class SGCORE_API Quat;

        class Vect3D;
    }// namespace Kinematics
}// namespace SGCore

/// <summary> A rotation in 3D space that can be applied to a 3D vector or converted into Euler Angles. </summary>
class SGCORE_API SGCore::Kinematics::Quat
{
public:
    /// <summary> Quaternion representing no rotation (0.0f, 0.0f, 0.0f, 1.0f) </summary>
    static const Quat& Identity();

    /// <summary> Parse a Quaternion from a string. </summary>
    static bool Deserialize(const std::string& str, Quat& out_result, char delimiter = ',');

    /// <summary> Create a new Quaternion Rotation from its euler angle representation. </summary>
    static Quat FromEuler(float xAngle, float yAngle, float zAngle);

    /// <summary> Create a new Quaternion Rotation from its euler angle representation. </summary>
    static Quat FromEuler(const Vect3D& euler);

    /// <summary> Create a new Quaternion Rotation from an angle-axis representation. </summary>
    static Quat FromAngleAxis(float angle, float xAxis, float yAxis, float zAxis);

    /// <summary> Create a new Quaternion Rotation from an angle-axis representation. </summary>
    static Quat FromAngleAxis(float angle, const Vect3D& axis);

    /// <summary> Returns the inverse if q (a.k.a. a rotation in the other direction) </summary>
    static Quat Invert(const Quat& quat);// -x-y-z w

    /// <summary> Normalizes a quaternion to have a length of 1. </summary>
    /// <returns></returns>
    static Quat Normalize(const Quat& quat);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Create a new Quaternion rotation of 0, 0, 0, 1. </summary>
    Quat();

    /// <summary> Create a new Quaternion rotation. </summary>
    Quat(float x, float y, float z, float w);

    /**
     * The copy constructor.
     */
    Quat(const Quat& rhs);

    /**
     * The move constructor.
     */
    Quat(Quat&& rhs) noexcept;

    /// <summary> Default Destructor. </summary>
    virtual ~Quat();

public:
    /**
     * The copy assignment operator.
     */
    Quat& operator=(const Quat& rhs);

    /**
     * The move assignment operator.
     */
    Quat& operator=(Quat&& rhs) noexcept;

public:
    /// <summary>
    /// Add two quaternions together Using a Hamilton product.
    /// NOTE: Q2 is applies first, followed by Q1, as per multiplication order of quaternions!
    /// </summary>
    /// <remarks>
    /// A rotation by Q1 followed by one of Q2 requires to operation Q2*Q1, using the Hamilton Multiplication.
    /// https://en.wikipedia.org/wiki/Quaternion
    /// </remarks>
    // multiply this quaternion by another Quat - by quaternion law, that is the first rotation, followed by this.
    Quat operator*(const Quat& quat) const;

    //multiply this quaternion with a Vect3D, a.k.a. rotate it.
    Vect3D operator*(const Vect3D& vect3D) const;

public:
    SG_NODISCARD float GetX() const;
    void SetX(float x);

    SG_NODISCARD float GetY() const;
    void SetY(float y);

    SG_NODISCARD float GetZ() const;
    void SetZ(float z);

    SG_NODISCARD float GetW() const;
    void SetW(float w);

public:
    /// <summary> Retrieve this Quaternion's euler angle notation. </summary>
    SG_NODISCARD Vect3D ToEuler() const;

    /// <summary> Rotate Vect3D by this quaternion rotation. </summary>
    SG_NODISCARD Vect3D Rotate(const Vect3D& vect3D) const;

    /// <summary> Check if two quaternions have equal values. </summary>
    SG_NODISCARD bool Equals(const Quat& quat) const;

    /// <summary> Check if this Quaternion is the identity quaternion (meaning it does not rotate anything.) </summary>
    SG_NODISCARD bool IsIdentity() const;

    /// <summary> Returns the magnitude of this Quaternion. Used in normalization. </summary>
    /// <returns></returns>
    SG_NODISCARD float Magnitude() const;

    /// <summary> Create a string representation of the Quaternion rotation. </summary>
    SG_NODISCARD std::string ToString() const;

    /// <summary> Normalize a Quaternion to ensure it is Unit Length </summary>
    SG_NODISCARD Quat Normalized() const;

    /// <summary>  Calculate the Quaternion that, when applied to (1, 0, 0), (0, 1, 0) and (0, 0, 1) will result in the
    /// vectors X, Y, Z. </summary>
    /// <param name="X">In Orignal function - Side, calculated from Cross Up(input)-FWD, Unity (2D) Left/Right</param>
    /// <param name="Y">In Orignal function - UP, re-calculated from Cross SIDE-FWD, Unity (2D) Up/Down</param>
    /// <param name="Z">In Orignal function - Forward, Unity Z (towards screen)</param>
    /// <remarks> Based on the implementation at https://gist.github.com/aeroson/043001ca12fe29ee911e or
    /// https://answers.unity.com/questions/467614/what-is-the-source-code-of-quaternionlookrotation.html,
    /// refactored somewhat to make it more readable, and added comments that reflect my own hand solved variables
    /// based on the sources from Quat.Rotate. </remarks>
    /// <returns></returns>
    SG_NODISCARD static Quat LookRotation_XYZ(const Vect3D X, const Vect3D Y,
                                              const Vect3D Z); //assumes all are known, of unit length and properly calculated. Makes the matrix (v0, v1, v2). SHOULD BE UNIT LEGTH AND ORTHAGONAL!

public:
    SG_NODISCARD std::string Serialize(const char delimiter = ',') const;
};