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
 * Utility class to Serialize / Deserialize various variables. Re-used
 * throughout methods.
 */


#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;
        class Vect3D;
    }// namespace Kinematics

    namespace Util
    {
        /// <summary> Utility class to serialize / deserialize classes. </summary>
        class SGCORE_API Serializer;
    }// namespace Util
}// namespace SGCore

/// <summary> Utility class to serialize / deserialize classes. </summary>
class SGCORE_API SGCore::Util::Serializer
{
public:
    /// <summary> Filters spaces from a a string. </summary>
    static std::string FilterSpaces(const std::string& input);

    /// <summary> Filter opening / closing characters at the beginning and end of a string, if they exist. </summary>
    /// <param name="serialized"></param>
    static void FilterBrackets(std::string& out_serialized);

    /// <summary> Split a serialized string by its top level blocks </summary>
    static std::vector<std::string> SplitBlocks(const std::string& fullSerialized, bool bFilterSpaces = false);

    /// <summary> Enclose a string with our opening / closing characters. </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    static std::string Enclose(const std::string& str);

    /// <summary> Serialize a floating point array/vector </summary>
    static std::string Serialize(const std::vector<float>& floatArray, bool bEnclosed = true);

    /// <summary> Serialize a 2D floating point array/vector </summary>
    static std::string Serialize(const std::vector<std::vector<float>>& floatArray, bool bEnclosed = true);

    /// <summary> Serialize a Quaternion </summary>
    static std::string Serialize(const Kinematics::Quat& quat, bool bEnclosed = true);

    /// <summary> Serialize a Quaternion array/vector </summary>
    static std::string Serialize(const std::vector<Kinematics::Quat>& quatArray, bool bEnclosed = true);

    /// <summary> Serialize a 2D Quaternion array/vector </summary>
    static std::string Serialize(const std::vector<std::vector<Kinematics::Quat>>& quatArray, bool bEnclosed = true);

    /// <summary> Serialize a Vector </summary>
    static std::string Serialize(const Kinematics::Vect3D& vect, bool bEnclosed = true);

    /// <summary> Serialize a Vector array/vector </summary>
    static std::string Serialize(const std::vector<Kinematics::Vect3D>& vectArray, bool bEnclosed = true);

    /// <summary> Serialize a 2d Vector array/vector </summary>
    static std::string Serialize(const std::vector<std::vector<Kinematics::Vect3D>>& vectArray, bool bEnclosed = true);

    /// <summary> Serialize a boolean array/vector </summary>
    static std::string Serialize(const std::vector<bool>& boolArray, bool bEnclosed = true);

    /// <summary> Convert a serialized string back into an array of floating points  </summary>
    static std::vector<float> DeserializeFloats(const std::string& serialized);

    /// <summary> Convert a serialized string back into a 2D array of floating points  </summary>
    static std::vector<std::vector<float>> DeserializeFloats2D(const std::string& serialized);

    /// <summary> Convert a serialized string back into a Quaternion  </summary>
    static Kinematics::Quat DeserializeQuat(const std::string& serialized);

    /// <summary> Convert a serialized string back into an array of Quaternions  </summary>
    static std::vector<Kinematics::Quat> DeserializeQuats(const std::string& serialized);

    /// <summary> Convert a serialized string back into a 2D array of Quaternions </summary>
    static std::vector<std::vector<Kinematics::Quat>> DeserializeQuats2D(const std::string& serialized);

    /// <summary> Convert a serialized string back into a Vector  </summary>
    static Kinematics::Vect3D DeserializeVect(const std::string& serialized);

    /// <summary> Convert a serialized string back into an array of Vectors </summary>
    static std::vector<Kinematics::Vect3D> DeserializeVects(const std::string& serialized);

    /// <summary> Convert a serialized string back into a 2D array of Vectors </summary>
    static std::vector<std::vector<Kinematics::Vect3D>> DeserializeVects2D(const std::string& serialized);

    /// <summary> Convert a serialized string back into an array of booleans </summary>
    static std::vector<bool> DeserializeBools(const std::string& serialized);

private:
    struct Impl;

public:
    Serializer() = delete;
    virtual ~Serializer() = delete;
};