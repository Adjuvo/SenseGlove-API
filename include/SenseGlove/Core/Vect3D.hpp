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
 * Represents a position or rotation in 3D Space.
 */


#pragma once

#include <memory>
#include <string>

#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        /// <summary> Represents a vector with x,y,z coordinates. </summary>
        class SGCORE_API Vect3D;
    }// namespace Kinematics
}// namespace SGCore

/// <summary> Represents a vector with x,y,z coordinates. </summary>
class SGCORE_API SGCore::Kinematics::Vect3D
{
public:
    /// <summary> Represents a vector with coordinates (0.0f, 0.0f, 0.0f). </summary>
    static const Vect3D& Zero();

    /// <summary> Deserialize a Vect3D into a string representation </summary>
    static bool Deserialize(const std::string& str, Vect3D& out_result, char delimiter);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Creates an empty vector (0, 0, 0) for internal use </summary>
    Vect3D();

    /// <summary> Create a new instance of a 3D vector. </summary>
    Vect3D(float x, float y, float z);

    /**
     * The copy constructor.
     */
    Vect3D(const Vect3D& rhs);

    /**
     * The move constructor.
     */
    Vect3D(Vect3D&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~Vect3D();

public:
    /**
     * The copy assignment operator.
     */
    Vect3D& operator=(const Vect3D& rhs);

    /**
     * The move assignment operator.
     */
    Vect3D& operator=(Vect3D&& rhs) noexcept;

public:
    // Overload + operator to add two Vect3 objects.
    Vect3D operator+(const Vect3D& vect3D) const;

    // Overload - operator to subtract two Vect3 objects.
    Vect3D operator-(const Vect3D& vect3D) const;

    // Overload - operator to scale a vector3 by a float
    Vect3D operator*(float scaleFactor) const;

public:
    SG_NODISCARD float GetX() const;
    void SetX(float x);

    SG_NODISCARD float GetY() const;
    void SetY(float y);

    SG_NODISCARD float GetZ() const;
    void SetZ(float z);

public:
    /// <summary> Calculate the magnitude or 'length' of this Vector </summary>
    SG_NODISCARD float Magnitude() const;

    /// <summary> Returns this vector normalized to have a Magnitude on 1. </summary>
    Vect3D Normalized() const;

    /// <summary> Scale all elements of this vector by a certain factor. </summary>
    void Scale(float factor);

    /// <summary> Calculate the distance between this Vector and another one. </summary>
    SG_NODISCARD float DistTo(const Vect3D& vect3D) const;

    /// <summary> Check if this Vector is roughly equal to another. </summary>
    SG_NODISCARD bool Equals(const Vect3D& vect3D) const;

    /// <summary> Create a string representation of this Vector. </summary>
    SG_NODISCARD std::string ToString() const;



    /// <summary> Calculate the dot product between two vectors. If they're at 90 degree angles, the DP is 0. </summary>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    SG_NODISCARD static float DotProduct(const Vect3D& a, const Vect3D& b);


    /// <summary> Caluculate the Croos product between two vectors. THe result is an orthagonal vector. </summary>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    SG_NODISCARD static Vect3D CrossProduct(const Vect3D& a, const Vect3D& b);


    /// <summary>   </summary>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    /// <returns></returns>
    SG_NODISCARD static float AngleBetween(const Vect3D& v1, const Vect3D& v2);


public:
    /// <summary> Convert a serialized Vect3D back into its class representation. </summary>
    /// <param name="delim"></param>
    /// <returns></returns>
    SG_NODISCARD std::string Serialize(char delimiter) const;
};