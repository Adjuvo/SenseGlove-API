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
 * Contains position and rotation data of a SenseGlove's exoskeleton, along
 * with accessors for relevant variables.
 */


#pragma once

#include <cstdint>
#include <memory>
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

    namespace SG
    {
        class SenseGloveInfo;

        /// <summary> Represents a pose of a Sense Glove exoskeleton. </summary>
        class SGCORE_API SenseGlovePose;
    }// namespace SG
}// namespace SGCore

/// <summary> Represents a pose of a Sense Glove exoskeleton. </summary>
class SGCORE_API SGCore::SG::SenseGlovePose
{
public:
    /// <summary> Returns an idle pose for the Sense Glove if no data can be found. </summary>
    static SenseGlovePose IdlePose(const SenseGloveInfo& gloveInfo);

    /// <summary> Deserialize a GlovePose back into usable values. </summary>
    static SenseGlovePose Deserialize(const std::string& serializedString);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The basic constructor. </summary>
    SenseGlovePose();

    /// <summary> Creates a new instance of a SenseGlovePose. </summary>
    SenseGlovePose(bool bRightHanded,
                   const std::vector<std::vector<Kinematics::Vect3D>>& jointPositions,
                   const std::vector<std::vector<Kinematics::Quat>>& jointRotations,
                   const std::vector<std::vector<Kinematics::Vect3D>>& gloveAngles);

    /**
     * The copy constructor.
     */
    SenseGlovePose(const SenseGlovePose& rhs);

    /**
     * The move constructor.
     */
    SenseGlovePose(SenseGlovePose&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~SenseGlovePose();

public:
    /**
     * The copy assignment operator.
     */
    SenseGlovePose& operator=(const SenseGlovePose& rhs);

    /**
     * The move assignment operator.
     */
    SenseGlovePose& operator=(SenseGlovePose&& rhs) noexcept;

public:
    /// <summary> Whether this Glove Pose was created for be a right- or left hand, or not. </summary>
    SG_NODISCARD bool IsRight() const;

    /// <summary> Positions of each glove joint, relative to the Glove's Origin. </summary>
    SG_NODISCARD const std::vector<std::vector<Kinematics::Vect3D>>& GetJointPositions() const;

    /// <summary> Quaternion rotation of each glove joint, relative to the Glove Origin. </summary>
    SG_NODISCARD const std::vector<std::vector<Kinematics::Quat>>& GetJointRotations() const;

    /// <summary> Glove joint angles in euler notation, relative to the last segment. </summary>
    /// <remarks> Essentially sensor angles, though placed in their proper xyz notation. </remarks>
    SG_NODISCARD const std::vector<std::vector<Kinematics::Vect3D>>& GetGloveAngles() const;

public:
    /// <summary> The position of the tip of the 'thimbles', the furthest link on each glove link. </summary>
    SG_NODISCARD std::vector<Kinematics::Vect3D> GetThimblePositions() const;

    /// <summary> The (quaternion) rotation of the 'thimbles', the furthest link on each link. </summary>
    SG_NODISCARD std::vector<Kinematics::Quat> GetThimbleRotations() const;

    /// <summary> Sum of the Sensor angles in each (xyz) direction. "Total Pronation / Flexion / Abduction". </summary>
    SG_NODISCARD std::vector<Kinematics::Vect3D> GetTotalGloveAngles() const;

    /// <summary> Calculate fingertip positions, knowing the offset between thimble and fingertips. </summary>
    SG_NODISCARD std::vector<Kinematics::Vect3D> CalculateFingertips(
            const std::vector<Kinematics::Vect3D>& fingerOffsets) const;

    /// <summary> Returns true if this glove pose equals another. </summary>
    SG_NODISCARD bool Equals(const SenseGlovePose& senseGloveGlovePose) const;

public:
    /// <summary> Returns a user-friendly string representation of this GlovePose for reporting. </summary>
    SG_NODISCARD std::string ToString(bool bShortFormat = true) const;

    /// <summary> Serialize this GlovePose into a string representation. </summary>
    SG_NODISCARD std::string Serialize() const;
};