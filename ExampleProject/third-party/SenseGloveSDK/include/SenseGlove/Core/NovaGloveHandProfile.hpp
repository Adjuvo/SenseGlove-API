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
 * Input for Nova kinematics to calculate a HandPose.
 * Output of calibration algorithms.
 */


#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    namespace Kinematics
    {
        class HandInterpolator;
    }// namespace Kinematics

    namespace Nova
    {
        /// <summary> Contains user-specific data for the Nova to convert sensor data into a hand pose. </summary>
        class SGCORE_API NovaGloveHandProfile;
    }// namespace Nova
}// namespace SGCore

/// <summary> Contains user-specific data for the Nova to convert sensor data into a hand pose. </summary>
class SGCORE_API SGCore::Nova::NovaGloveHandProfile
{
public:
    /// <summary> Creates a default Nova Profile for a left or right hand. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    [[nodiscard]] static NovaGloveHandProfile Default(bool bRightHanded);

    /// <summary> Convert a string notation of a NovaGloveHandProfile into a new instance. </summary>
    /// <param name="serializedString"></param>
    /// <returns></returns>
    [[nodiscard]] static NovaGloveHandProfile Deserialize(const std::string& serializedString);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The default constructor. </summary>
    /// <returns></returns>
    NovaGloveHandProfile();

    /// <summary> Create a new instance of a Nova-Profile. </summary>
    /// <param name="right"></param>
    /// <param name="interpolator"></param>
    /// <returns></returns>
    NovaGloveHandProfile(bool bRightHanded, const Kinematics::HandInterpolator& interpolator);

    /**
     * The copy constructor.
     */
    NovaGloveHandProfile(const NovaGloveHandProfile& rhs);

    /**
     * The move constructor.
     */
    NovaGloveHandProfile(NovaGloveHandProfile&& rhs) noexcept;

    virtual ~NovaGloveHandProfile();

public:
    /**
     * The copy assignment operator.
     */
    NovaGloveHandProfile& operator=(const NovaGloveHandProfile& rhs);

    /**
     * The move assignment operator.
     */
    NovaGloveHandProfile& operator=(NovaGloveHandProfile&& rhs) noexcept;

public:
    /// <summary> Whether this profile was created for a right- or left hand. </summary>
    [[nodiscard]] bool IsRight() const;

    /// <summary> Interpolation sets to convert sensor data into a hand pose. </summary>
    [[nodiscard]] Kinematics::HandInterpolator& GetInterpolationSet() const;

public:
    /// <summary>  </summary>
    /// <param name="novaProfile"></param>
    /// <returns></returns>
    [[nodiscard]] bool Equals(const NovaGloveHandProfile& novaProfile) const;

public:
    void Reset();

public:
    /// <summary> Convert this NovaGloveHandProfile into a string notation so it can be stored on disk. </summary>
    /// <returns></returns>
    [[nodiscard]] std::string Serialize() const;
};
