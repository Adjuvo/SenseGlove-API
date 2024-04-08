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
 * Contains interpolation sets for all hand joint movements that can be
 * calculated using the Sense Glove.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Fingers.hpp"
#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        /// <summary> Contains interpolation sets of all joint movements that can be calculated into a HandPose.
        /// </summary>
        class SGCORE_API HandInterpolator;

        class InterpolationSet;

        class Quat;

        class Vect3D;
    }// namespace Kinematics
}// namespace SGCore

/// <summary> Contains interpolation sets of all joint movements that can be calculated into a HandPose. </summary>
class SGCORE_API SGCore::Kinematics::HandInterpolator
{
public:
    /// <summary> Convert a serialized HandInterpolator back into a class representation. </summary>
    /// <param name="serializedString"></param>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static HandInterpolator Deserialize(const std::string& serializedString, bool bRightHanded = true);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    /**
     * The default constructor.
     */
    HandInterpolator();

    explicit HandInterpolator(bool bRightHanded);

    //---------------------------------------------------------------------------------
    // Angle Interpolation

    /**
     * The copy constructor.
     */
    HandInterpolator(const HandInterpolator& rhs);

    /**
     * The move constructor.
     */
    HandInterpolator(HandInterpolator&& rhs) noexcept;

    virtual ~HandInterpolator();

    /**
     * The copy assignment operator.
     */
    HandInterpolator& operator=(const HandInterpolator& rhs);

    /**
     * The move assignment operator.
     */
    HandInterpolator& operator=(HandInterpolator&& rhs) noexcept;

public:
    /// <summary> Calculate a finger movement's rotation, using an input value. </summary>
    SG_NODISCARD float CalculateAngle(EFingerMovement movement, float value, bool bApplyLimits = true) const;

    /// <summary> Calculate a thumb movement's rotation, using an input value. </summary>
    SG_NODISCARD float CalculateAngle(EThumbMovement movement, float value, bool bApplyLimits = true) const;

    /// <summary> Calculate all hand angles based on an interpolator and normalized input. </summary>
    std::vector<std::vector<Vect3D>> InterpolateHandAngles(
            const std::vector<std::vector<float>>& flexions, const std::vector<float>& abductions,
            float cmcTwist) const;

    //--------------------------------------------------------------------------------------
    // Util Methods

public:
    /// <summary> Check if this handInterpolator matches another. </summary>
    /// <param name="handInterpolator"></param>
    /// <returns></returns>
    SG_NODISCARD bool Equals(const HandInterpolator& handInterpolator) const;

public:
    /// <summary> Serialize this HandInterpolator into a string representation. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string Serialize() const;
};