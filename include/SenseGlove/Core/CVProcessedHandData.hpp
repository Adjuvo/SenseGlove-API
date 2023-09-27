/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2023 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Internal data block: CV Data processed into joint angles and wrist location. Need to keep track of multiple of these for smoothing / prediciton.
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
    } // namespace CV
    namespace Kinematics
    {
        class SGCORE_API Vect3D;
        class SGCORE_API Quat;
        class SGCORE_API BasicHandModel;
    } // namespace Kinematics
    class SGCORE_API HandPose;
}// namespace SGCore

/// <summary> CV Data processed into joint angles and wrist location. </summary>
class SGCORE_API SGCore::CV::CVProcessedHandData
{
    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /**
     * The copy constructor.
     */
    CVProcessedHandData(const CVProcessedHandData& rhs);

    /**
     * The move constructor.
     */
    CVProcessedHandData(CVProcessedHandData&& rhs)
    noexcept;

    virtual ~CVProcessedHandData();


    /**
     * The copy assignment operator.
     */
    CVProcessedHandData& operator=(const CVProcessedHandData& rhs);

    /**
     * The move assignment operator.
     */
    CVProcessedHandData& operator=(CVProcessedHandData&& rhs) noexcept;

public:
//#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
    CVProcessedHandData();
//#endif /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

public:

    /// <summary> Creates a new instance of a CVProcessedHandData block. </summary>
    /// <param name="isRight"></param>
    /// <param name="wristPos"></param>
    /// <param name="wristRot"></param>
    /// <param name="fingerAngles"></param>
    /// <param name="globalCert"></param>
    /// <param name="time"></param>
    CVProcessedHandData(const bool isRight, const Kinematics::Vect3D wristPos, const Kinematics::Quat wristRot,
        const std::vector<std::vector<Kinematics::Vect3D>>& fingerAngles, const float globalCert, const float time);


    //---------------------------------------------------------------------------------
    // Accessors

    /// <summary> The data point's timestamp, used for smoothing </summary>
    SG_NODISCARD float GetTimestamp() const;
    void SetTimestamp(float value);

    /// <summary> The HandAngles caluclated at ttimeStamp  </summary>
    SG_NODISCARD std::vector<std::vector<Kinematics::Vect3D>> GetHandAngles() const;
    void SetHandAngles(std::vector<std::vector<Kinematics::Vect3D>> value);

    /// <summary> The wrist position calculated at timeStamp </summary>
    SG_NODISCARD Kinematics::Vect3D GetWristWorldPostion() const;
    void SetWristWorldPostion(Kinematics::Vect3D value);

    /// <summary> The wrist rotation calculated at timeStamp </summary>
    SG_NODISCARD Kinematics::Quat GetWristWorldRotation() const;
    void SetWristWorldRotation(Kinematics::Quat value);

    /// <summary> Whether or not this data point was generated for a left- or right hand </summary>
    SG_NODISCARD bool GetRightHand() const;
    void SetRightHand(bool value);

    /// <summary> Certainty of the whole hand tracking </summary>
    SG_NODISCARD float GetGlobalCertainty() const;
    void SetGlobalCertainty(float value);


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
    bool ToHandPose(const Kinematics::BasicHandModel& handDimensions, HandPose& out_handPose, Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation);

    //---------------------------------------------------------------------------------
    // Static Functions

public:

    /// <summary> Interpolate beween two HandDataPoints to generate a new one </summary>
    /// <param name="p0"></param>
    /// <param name="p1"></param>
    /// <param name="t"></param>
    /// <param name="clampOutput"></param>
    /// <returns></returns>
    SG_NODISCARD static CVProcessedHandData InterpolateData(const float t, const CVProcessedHandData& p0, const CVProcessedHandData& p1, const bool clampOutput);

    /// <summary> Interpolate all Hand Data between two points. </summary>
    /// <param name="t"></param>
    /// <param name="p0"></param>
    /// <param name="p1"></param>
    /// <param name="clampOutput"></param>
    /// <param name="out_wristPos"></param>
    /// <param name="out_wristRot"></param>
    /// <param name="out_handAngles"></param>
    /// <returns></returns>
    static void InterpolateData(const float t, const CVProcessedHandData& p0, const CVProcessedHandData& p1, const bool clampOutput,
        Kinematics::Vect3D& out_wristPos, Kinematics::Quat& out_wristRot, std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles);

};
