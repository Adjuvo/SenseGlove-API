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
 * A data class containing the minimum required data for a hand's forward
 * kinematics.
 * Used in both kinematics and calibration.
 */


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Fingers.hpp"
#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        /// <summary> Represents data of a user's hand required for forward kinematics. </summary>
        class SGCORE_API BasicHandModel;

        class Quat;
        class Vect3D;
    }// namespace Kinematics
}// namespace SGCore

/// <summary> Represents data of a user's hand required for forward kinematics. </summary>
class SGCORE_API SGCore::Kinematics::BasicHandModel
{
public:
    /// <summary> Retrieve a default left or right hand model. </summary>
    SG_NODISCARD static BasicHandModel Default(bool bRightHanded);

    /// <summary> Convert a serialized HandModel back into its class representation. </summary>
    SG_NODISCARD static BasicHandModel Deserialize(const std::string& serializedString);

public:
    /// <summary> Default finger lengths (based on right hand). </summary>
    /// <remarks> Any missing fingers are replaced with their respective value. </remarks>
    SG_NODISCARD static const std::vector<std::vector<float>>& GetBaseFingerLengths();

    /// <summary> Default joint positions (based on right hand). </summary>
    /// <remarks> Any missing positions are replaced with their respective value. </remarks>
    SG_NODISCARD static const std::vector<Vect3D>& GetBaseJointPositions();

    /// <summary> Default joint angles (based on right hand). </summary>
    /// <remarks> Any missing angles are replaced with their respective value. </remarks>
    SG_NODISCARD static const std::vector<Vect3D>& GetBaseJointAngles();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The basic class constructor. </summary>
    BasicHandModel();

    /// <summary> Create a new BasicHandModel with no starting rotations. </summary>
    BasicHandModel(bool bRightHanded, const std::vector<std::vector<float>>& lengths,
                   const std::vector<Vect3D>& startPositions);

    /// <summary> Create a new BasicHandModel. </summary>
    BasicHandModel(bool bRightHanded, const std::vector<std::vector<float>>& lengths,
                   const std::vector<Vect3D>& startPositions, const std::vector<Quat>& startRotations);

    /**
     * The copy constructor.
     */
    BasicHandModel(const BasicHandModel& rhs);

    /**
     * The move constructor.
     */
    BasicHandModel(BasicHandModel&& rhs) noexcept;

    /// <summary> The basic class destructor. </summary>
    virtual ~BasicHandModel();

public:
    /**
     * The copy assignment operator.
     */
    BasicHandModel& operator=(const BasicHandModel& rhs);

    /**
     * The move assignment operator.
     */
    BasicHandModel& operator=(BasicHandModel&& rhs) noexcept;

public:
    /// <summary> Whether or not this BasicHandModel was created for a left- or right hand. Used for validation.
    /// </summary>
    SG_NODISCARD bool IsRight() const;

public:
    /// <summary> The length of individual finger phalangers in mm, sorted per finger. Generally 5x3. </summary>
    SG_NODISCARD const std::vector<std::vector<float>>& GetFingerLengths() const;

    /// <summary> Retrieve the finger lengths of a specific finger in mm. </summary>
    SG_NODISCARD const std::vector<float>& GetFingerLengths(EFinger finger) const;

    /// <summary> Set the finger lengths of a specific finger in mm. </summary>
    void SetFingerLengths(EFinger finger, const std::vector<float>& lengths);

    /// <summary> Set the finger lengths of a specific finger in mm. </summary>
    void SetFingerLengths(uint8_t finger, const std::vector<float>& lengths);

    /// <summary> Get the finger ratios of all fingers. </summary>
    SG_NODISCARD const std::vector<std::vector<float>>& GetFingerRatios() const;

protected:
    /// <summary> Calculated Finger ratios [0..1]. </summary>
    void SetFingerRatios(const std::vector<std::vector<float>>& ratios);

public:
    /// <summary> Get the finger ratios of a specific finger.  </summary>
    SG_NODISCARD const std::vector<float>& GetFingerRatios(EFinger finger) const;

    /// <summary> Starting joint positions relative to the device Origin. </summary>
    SG_NODISCARD const std::vector<Vect3D>& GetStartJointPositions() const;

    void SetStartJointPosition(EFinger finger, const Vect3D& position);
    void SetStartJointPosition(uint8_t finger, const Vect3D& position);

    /// <summary> Starting joint rotations relative to the device Origin. </summary>
    SG_NODISCARD const std::vector<Quat>& GetStartJointRotations() const;

    /// <summary> Retrieve the start position of a specific finger. </summary>
    SG_NODISCARD const Vect3D& GetJointPosition(EFinger finger) const;

    /// <summary> Set the start position of a specific finger. </summary>
    void SetJointPosition(const Vect3D& newPosition, EFinger finger);

    /// <summary> Retrieve the start rotation of a specific finger. </summary>
    SG_NODISCARD const Quat& GetJointRotation(EFinger finger) const;

    /// <summary> Set the start rotation of a specific finger. </summary>
    void SetJointRotation(const Quat& newRotation, EFinger finger);

    /// <summary> Get the total lengths of fingers, in mm. </summary>
    SG_NODISCARD const std::vector<float>& GetTotalLengths() const;

    /// <summary> Get the total length of a specific finger, in mm. </summary>
    SG_NODISCARD float GetTotalLength(EFinger finger) const;

protected:
    /// <summary> Calculated Total finger lengths. </summary>
    void SetTotalLengths(const std::vector<float>& lengths);

public:
    /// <summary> Retrieve the lengths of a specific finger, as BasicHandModel representation (L, 0, 0). </summary>
    /// <remarks> Used for forwards kinematics. </remarks>
    SG_NODISCARD std::vector<Vect3D> Get3DLengths(EFinger finger) const;

public:
    /// <summary> Check if this BasicHandModel has the same values as another BasicHandModel. </summary>
    /// <param name="basicHandModel"></param>
    /// <returns></returns>
    SG_NODISCARD bool Equals(const BasicHandModel& basicHandModel) const;

protected:
    /// <summary> Test if the input has enough values. if not, add the appropriate values to compensate. </summary>
    virtual void Validate();

    /// <summary> Calculate hand variables (finger lengths, ratios) based on current values. </summary>
    void CalculateVariables();

public:
    /// <summary> Convert this handModel into a string notation, readable for humans. Does not include starting
    /// positions / rotations. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string ToString() const;

    /// <summary> Convert this handModel into a string notation, readable for humans. Optionally includes starting
    /// positions / rotations. </summary>
    /// <param name="bLengthsOnly"></param>
    /// <returns></returns>
    SG_NODISCARD std::string ToString(bool bLengthsOnly) const;

    /// <summary> Serialize this HandModel into a string representation. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string Serialize() const;
};