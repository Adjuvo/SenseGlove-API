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
 * Internal data block: CV Data processed into joint angles and wrist location.
 * Need to keep track of multiple of these for smoothing/prediction.
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace CV
    {
        /// <summary> CV Data processed into joint angles and wrist location. </summary>
        class SGCORE_API CVProcessedHandData;
    }// namespace CV

    namespace Kinematics
    {
        class SGCORE_API Vect3D;
        class SGCORE_API Quat;
        class SGCORE_API BasicHandModel;
    }// namespace Kinematics

    class SGCORE_API HandPose;
}// namespace SGCore

/// <summary> CV Data processed into joint angles and wrist location. </summary>
class SGCORE_API SGCore::CV::CVProcessedHandData
{
    //---------------------------------------------------------------------------------
    // Static Functions

public:
    /// <summary> Interpolate beween two HandDataPoints to generate a new one </summary>
    /// <param name="t"></param>
    /// <param name="p0"></param>
    /// <param name="p1"></param>
    /// <param name="clampOutput"></param>
    /// <returns></returns>
    SG_NODISCARD static CVProcessedHandData InterpolateData(
            float t, const CVProcessedHandData& p0, const CVProcessedHandData& p1, bool bClampOutput);

    /// <summary> Interpolate all Hand Data between two points. </summary>
    /// <param name="t"></param>
    /// <param name="p0"></param>
    /// <param name="p1"></param>
    /// <param name="clampOutput"></param>
    /// <param name="out_wristPosition"></param>
    /// <param name="out_wristRotation"></param>
    /// <param name="out_handAngles"></param>
    /// <returns></returns>
    static void InterpolateData(
            float t, const CVProcessedHandData& p0, const CVProcessedHandData& p1, bool bClampOutput,
            Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation,
            std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    /**
     * The default constructor.
     */
    CVProcessedHandData();

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    /// <summary> Creates a new instance of a CVProcessedHandData block. </summary>
    /// <param name="bRight"></param>
    /// <param name="wristPosition"></param>
    /// <param name="wristRotation"></param>
    /// <param name="fingerAngles"></param>
    /// <param name="globalCertainty"></param>
    /// <param name="time"></param>
    CVProcessedHandData(bool bRightHanded,
                        const Kinematics::Vect3D& wristPosition, const Kinematics::Quat& wristRotation,
                        const std::vector<std::vector<Kinematics::Vect3D>>& fingerAngles,
                        float globalCertainty, float time);

    /**
     * The copy constructor.
     */
    CVProcessedHandData(const CVProcessedHandData& rhs);

    /**
     * The move constructor.
     */
    CVProcessedHandData(CVProcessedHandData&& rhs) noexcept;

    virtual ~CVProcessedHandData();

public:
    /**
     * The copy assignment operator.
     */
    CVProcessedHandData& operator=(const CVProcessedHandData& rhs);

    /**
     * The move assignment operator.
     */
    CVProcessedHandData& operator=(CVProcessedHandData&& rhs) noexcept;

    //---------------------------------------------------------------------------------
    // Accessors

public:
    /// <summary> Whether or not this data point was generated for a left- or right hand </summary>
    SG_NODISCARD bool IsRight() const;
    void SetRight(bool bRight);

    /// <summary> The data point's timestamp, used for smoothing </summary>
    SG_NODISCARD float GetTimestamp() const;
    void SetTimestamp(float timestamp);

    /// <summary> The HandAngles caluclated at ttimeStamp  </summary>
    SG_NODISCARD const std::vector<std::vector<Kinematics::Vect3D>>& GetHandAngles() const;
    void SetHandAngles(const std::vector<std::vector<Kinematics::Vect3D>>& angles);

    /// <summary> The wrist position calculated at timeStamp </summary>
    SG_NODISCARD const Kinematics::Vect3D& GetWristWorldPosition() const;
    void SetWristWorldPosition(const Kinematics::Vect3D& position);

    /// <summary> The wrist rotation calculated at timeStamp </summary>
    SG_NODISCARD const Kinematics::Quat& GetWristWorldRotation() const;
    void SetWristWorldRotation(const Kinematics::Quat& rotation);

    /// <summary> Certainty of the whole hand tracking </summary>
    SG_NODISCARD float GetGlobalCertainty() const;
    void SetGlobalCertainty(float certainty);

    //---------------------------------------------------------------------------------
    // Member Functions

public:
    /// <summary> Prints the tracking data of this HandDataPoint </summary>
    /// <returns></returns>
    SG_NODISCARD std::string ToString() const;

    /// <summary> Convert the handAngles etc of this HandDataPoint into an acual HandPose </summary>
    /// <param name="handDimensions"></param>
    /// <param name="out_handPose"></param>
    /// <returns></returns>
    bool ToHandPose(const Kinematics::BasicHandModel& handDimensions, HandPose& out_handPose);

    /// <summary> Convert the handAngles etc of this HandDataPoint into an acual HandPose </summary>
    /// <param name="handDimensions"></param>
    /// <param name="out_handPose"></param>
    /// <param name="out_wristPosition"></param>
    /// <param name="out_wristRotation"></param>
    /// <returns></returns>
    bool ToHandPose(const Kinematics::BasicHandModel& handDimensions,
                    HandPose& out_handPose, Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation);
};