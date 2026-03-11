/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2026 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Input for Sense Glove kinematics to calculate a HandPose.
 * Output of calibration algorithms.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    namespace Kinematics
    {
        class HandInterpolator;
        class Vect3D;
    }// namespace Kinematics

    namespace SG
    {
        ///<summary> How this Sense Glove converts sensor data into a HandPose. </summary>
        enum class SGCORE_API EFingerSolver : uint8_t
        {
            /// <summary> Hand angles are interpolated based on the total flexion / abduction of the exoskeleton </summary>
            Interpolation = 0,// default.
        };

        ///<summary> How this Sense Glove converts sensor data into a HandPose. </summary>
        enum class SGCORE_API EThumbSolver : uint8_t
        {
            /// <summary> Hand angles are interpolated based on the total flexion / abduction of the exoskeleton </summary>
            Interpolation = 0,// default.
        };

        /// <summary> Contains everything a Sense Glove needs to calculate a HandPose. </summary>
        class SGCORE_API SenseGloveHandProfile;
    }// namespace SG
}// namespace SGCore

/// <summary> Contains everything a Sense Glove needs to calculate a HandPose. </summary>
class SGCORE_API SGCore::SG::SenseGloveHandProfile
{
public:
    ///<summary> Retrieve a 'new' profile, for either a left or right hand. </summary>
    [[nodiscard]] static SenseGloveHandProfile Default(bool bRightHanded);

    ///<summary> Deserialize a HandProfile back into usable values. </summary>
    [[nodiscard]] static SenseGloveHandProfile Deserialize(const std::string& serializedString);

public:
    /// <summary> Default offset from thimble to fingertip. </summary>
    [[nodiscard]] static const Kinematics::Vect3D& GetDefaultThimbleOffset();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    ///<summary> The basic constructor. </summary>
    SenseGloveHandProfile();

    /// <summary> Create a new Hand Profile for the Sense Glove. </summary>
    SenseGloveHandProfile(bool bRightHanded, const Kinematics::HandInterpolator& interpolator,
                  EThumbSolver thumbSolver, EFingerSolver fingerSolver,
                  const std::vector<Kinematics::Vect3D>& fingerThimbleOffset);

    /**
     * The copy constructor.
     */
    SenseGloveHandProfile(const SenseGloveHandProfile& rhs);

    /**
     * The move constructor.
     */
    SenseGloveHandProfile(SenseGloveHandProfile&& rhs) noexcept;

    ///<summary> The basic destructor. </summary>
    virtual ~SenseGloveHandProfile();

public:
    /**
     * The copy assignment operator.
     */
    SenseGloveHandProfile& operator=(const SenseGloveHandProfile& rhs);

    /**
     * The move assignment operator.
     */
    SenseGloveHandProfile& operator=(SenseGloveHandProfile&& rhs) noexcept;

public:
    /// <summary> Check whether this profile has been created for a right hand (true) or left hand (false). </summary>
    [[nodiscard]] bool IsRight() const;

    /// <summary> Interpolation set to estimate joint angles. </summary>
    [[nodiscard]] Kinematics::HandInterpolator& GetInterpolationSet() const;

    /// <summary> Solver property that determines _how_ HandPoses are calculated. </summary>
    [[nodiscard]] EThumbSolver GetThumbSolver() const;

    /// <summary> Solver property that determines _how_ finger poses are calculated. </summary>
    [[nodiscard]] EFingerSolver GetFingerSolver() const;

    /// <summary> Offset from thimble to fingertip, used for Inverse Kinematics. </summary>
    [[nodiscard]] const std::vector<Kinematics::Vect3D>& GetFingerThimbleOffset() const;

public:
    [[nodiscard]] bool Equals(const SenseGloveHandProfile& senseGloveHandProfile) const;

    /// <summary> Reset calibration on this profile. </summary>
    void Reset();

public:
    ///<summary> Serialize this HandProfile into a string representation. </summary>
    [[nodiscard]] std::string Serialize() const;
};
