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
 * Data class containing all variables to draw or analyze a virtual hand in
 * different formats.
 */


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "BasicHandModel.hpp"
#include "Fingers.hpp"
#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;
        class Vect3D;
    }// namespace Kinematics

    /// <summary> Contains all variables required to draw or analyze a virtual hand. </summary>
    class SGCORE_API HandPose;
}// namespace SGCore

/// <summary> Contains all variables required to draw or analyze a virtual hand. </summary>
class SGCORE_API SGCore::HandPose
{
public:
    /// <summary> Deserialize a HandPose back into usable values. </summary>
    static HandPose Deserialize(const std::string& serializedString);

    //---------------------------------------------------------------------------------------------------------------------
    // Generating Poses

    /// <summary> Generate a HandPose based on articulation angles (handAngles). </summary>
    /// <param name="handAngles"></param>
    /// <param name="bRightHanded"></param>
    /// <param name="handDimensions"></param>
    /// <returns></returns>
    static HandPose FromHandAngles(const std::vector<std::vector<Kinematics::Vect3D>>& handAngles, bool bRightHanded,
                                   const Kinematics::BasicHandModel& handDimensions);

    /// <summary> Generate a HandPose based on articulation angles (handAngles), with a default HandModel. </summary>
    /// <param name="handAngles"></param>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static HandPose FromHandAngles(const std::vector<std::vector<Kinematics::Vect3D>>& handAngles, bool bRightHanded);

    /// <summary> Create a new instance of a left or right handed Pose that is "idle"; in a neutral position. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="handDimensions"></param>
    /// <returns></returns>
    static HandPose DefaultIdle(bool bRightHanded, const Kinematics::BasicHandModel& handDimensions);

    /// <summary> Create a new instance of a left or right handed Pose that is "idle"; in a neutral position. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static HandPose DefaultIdle(bool bRightHanded);

    /// <summary> Generates a HandPose representing an 'open hand', used in calibration to determine finger extension.
    /// </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="handDimensions"></param>
    /// <returns></returns>
    static HandPose FlatHand(bool bRightHanded, const Kinematics::BasicHandModel& handDimensions);

    /// <summary> Generates a HandPose representing an 'open hand', used in calibration to determine finger extension.
    /// </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static HandPose FlatHand(bool bRightHanded);

    /// <summary> Generates a HandPose representing a 'thumbs up', used in calibration to determine finger flexion,
    /// thumb extension and adduction. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="handDimensions"></param>
    /// <returns></returns>
    static HandPose ThumbsUp(bool bRightHanded, const Kinematics::BasicHandModel& handDimensions);

    /// <summary> Generates a HandPose representing a 'thumbs up', used in calibration to determine finger flexion,
    /// thumb extension and adduction. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static HandPose ThumbsUp(bool bRightHanded);

    /// <summary> Generates a HandPose representing a 'fist', used in calibration to determine, thumb flexion and
    /// abduction. </summary>
    /// <param name="bRightHanded"></param>
    /// <param name="handDimensions"></param>
    /// <returns></returns>
    static HandPose Fist(bool bRightHanded, const Kinematics::BasicHandModel& handDimensions);

    /// <summary> Generates a HandPose representing a 'fist', used in calibration to determine, thumb flexion and
    /// abduction. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static HandPose Fist(bool bRightHanded);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The default constructor. </summary>
    HandPose();

    /// <summary> Create a new instance of HandPose. </summary>
    HandPose(bool bRightHanded, const std::vector<std::vector<Kinematics::Vect3D>>& jointPositions,
             const std::vector<std::vector<Kinematics::Quat>>& jointRotations,
             const std::vector<std::vector<Kinematics::Vect3D>>& handAngles);

    /**
     * The copy constructor.
     */
    HandPose(const HandPose& rhs);

    /**
     * The move constructor.
     */
    HandPose(HandPose&& rhs) noexcept;

    /// <summary> Default Destructor. </summary>
    virtual ~HandPose();

public:
    /**
     * The copy assignment operator.
     */
    HandPose& operator=(const HandPose& rhs);

    /**
     * The move assignment operator.
     */
    HandPose& operator=(HandPose&& rhs) noexcept;

public:
    /// <summary> Whether this HandPose was created to be a right- or left hand. </summary>
    SG_NODISCARD bool IsRight() const;

    /// <summary> Positions of all hand joints relative to the Sense Glove origin. From thumb to pinky, proximal to
    /// distal. </summary>
    SG_NODISCARD const std::vector<std::vector<Kinematics::Vect3D>>& GetJointPositions() const;

    /// <summary> Quaternion rotations of all hand joints. From thumb to pinky, proximal to distal. </summary>
    SG_NODISCARD const std::vector<std::vector<Kinematics::Quat>>& GetJointRotations() const;

    /// <summary> Euler representations of all possible hand angles. From thumb to pinky, proximal to distal. </summary>
    SG_NODISCARD const std::vector<std::vector<Kinematics::Vect3D>>& GetHandAngles() const;

public:
    /// <summary> Returns true of these two hand poses are roughly equal. </summary>
    SG_NODISCARD bool Equals(const HandPose& handPose) const;

    //---------------------------------------------------------------------------------------------------------------------
    // Formats

    //GetFormat (animator), GetFormat (MoCap), etc?

    /// <summary> Returns the total flexion of a specific finger as a value between 0 (fully extended) and 1
    /// (fully flexed). </summary>
    /// <remarks> Useful for animation or for detecting gestures. </remarks>
    SG_NODISCARD float GetNormalizedFlexion(EFinger finger, bool bClamp01 = true) const;

    /// <summary> Returns the total flexion the fingers as a value between 0 (fully extended) and 1 (fully flexed).
    /// </summary>
    /// <remarks> Useful for animation or for detecting gestures. </remarks>
    SG_NODISCARD std::vector<float> GetNormalizedFlexion(bool bClamp01 = true) const;

protected:
    /// <summary> Returns the total flexion of a specific finger as a value between 0 (fully extended) and
    /// 1 (fully flexed). </summary>
    /// <remarks> Separate function because we use it multiple times, protected because we don't want indexOutOfRange
    /// exceptions. </remarks>
    SG_NODISCARD float GetNormalizedFlexion(int32_t finger, bool bClamp01 = true) const;

public:
    SG_NODISCARD std::string ToString(bool bShortFormat = false) const;

    /// <summary> Serialize this HandPose into a string representation. </summary>
    SG_NODISCARD std::string Serialize() const;
};