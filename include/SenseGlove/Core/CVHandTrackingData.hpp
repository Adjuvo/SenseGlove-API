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
 * Unprocessed data received from CV Device(s), used as input for processing. Used as a separate class so the format is ensured.
 */


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Platform.hpp"
#include "DeviceTypes.hpp"

namespace SGCore
{
    namespace CV
    {
        //----------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // Tracking Depth Enum

        /// <summary> How much of the CV tracking is being used. Used by other APIs. </summary>
        enum class SGCORE_API ECVTracking_Depth : uint8_t
        {
            /// <summary> No computer-vision is enabled. </summary>
            Disabled = 0,
            /// <summary> Use CV only for the wrist position / rotation </summary>
            WristOnly,
            /// <summary> Use CV for both the wirst location and Hand Position  </summary>
            WristAndHandPose
        };

        //----------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // Position Enum

        /// <summary> Used to access specific positions from the CV output, which is an array of Vect3D positions. </summary>
        /// <remarks> Declared in CVHandOutput.cs because these enums are used to index the jointPositions array in that class. </remarks>
        enum class SGCORE_API ECVHandPoints : uint8_t
        {
            /// <summary> The position of the wrist as determined by the CV Model. </summary>
            CV_WRIST = 0,
            /// <summary> The position of the Thumb CMC Joint as determined by the CV Model. </summary>
            CV_THUMB_CMC,
            /// <summary> The position of the Thumb MCP Joint as determined by the CV Model. </summary>
            CV_THUMB_MCP,
            /// <summary> The position of the Thumb IP Joint as determined by the CV Model. </summary>
            CV_THUMB_IP,
            /// <summary> The position of the Thumb tip as determined by the CV Model. </summary>
            CV_THUMB_TIP,

            /// <summary> The position of the Index MCP Joint as determined by the CV Model. </summary>
            CV_INDEX_MCP,
            /// <summary> The position of the Index PIP Joint as determined by the CV Model. </summary>
            CV_INDEX_PIP,
            /// <summary> The position of the Index DIP Joint as determined by the CV Model. </summary>
            CV_INDEX_DIP,
            /// <summary> The position of the Index fingertip as determined by the CV Model. </summary>
            CV_INDEX_TIP,

            /// <summary> The position of the Middle MCP Joint as determined by the CV Model. </summary>
            CV_MIDDLE_MCP,
            /// <summary> The position of the Middle PIP Joint as determined by the CV Model. </summary>
            CV_MIDDLE_PIP,
            /// <summary> The position of the Middle DIP Joint as determined by the CV Model. </summary>
            CV_MIDDLE_DIP,
            /// <summary> The position of the Middle fingertip as determined by the CV Model. </summary>
            CV_MIDDLE_TIP,

            /// <summary> The position of the Ring MCP Joint as determined by the CV Model. </summary>
            CV_RING_MCP,
            /// <summary> The position of the Ring PIP Joint as determined by the CV Model. </summary>
            CV_RING_PIP,
            /// <summary> The position of the Ring DIP Joint as determined by the CV Model. </summary>
            CV_RING_DIP,
            /// <summary> The position of the Ring fingertip as determined by the CV Model. </summary>
            CV_RING_TIP,

            /// <summary> The position of the Pinky MCP Joint as determined by the CV Model. </summary>
            CV_PINKY_MCP,
            /// <summary> The position of the Pinky PIP Joint as determined by the CV Model. </summary>
            CV_PINKY_PIP,
            /// <summary> The position of the Pinky DIP Joint as determined by the CV Model. </summary>
            CV_PINKY_DIP,
            /// <summary> The position of the Pinky fingertip as determined by the CV Model. </summary>
            CV_PINKY_TIP,

            /// <summary> Utility enumerator to check if an array contains enough values. </summary>
            CV_All
        };

        /// <summary> Unprocessed data received from CV Device(s), used as input for processing. </summary>
        class SGCORE_API CVHandTrackingData;
    } // namespace CV

    namespace Kinematics
    {
        class Vect3D;
        class Quat;
    }// namespace Kinematics

}// namespace SGCore


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CV Output Class

/// <summary> Unprocessed data received from CV Device(s), used as input for processing. </summary>
class SGCORE_API SGCore::CV::CVHandTrackingData
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
    CVHandTrackingData(const CVHandTrackingData& rhs);

    /**
     * The move constructor.
     */
    CVHandTrackingData(CVHandTrackingData&& rhs)
    noexcept;

    virtual ~CVHandTrackingData();


    /**
     * The copy assignment operator.
     */
    CVHandTrackingData& operator=(const CVHandTrackingData& rhs);

    /**
     * The move assignment operator.
     */
    CVHandTrackingData& operator=(CVHandTrackingData&& rhs) noexcept;

public:
//#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
    CVHandTrackingData();
//#endif /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    /// <summary> Creates a new instance of HandTrackingData. Time is takes from the internal system </summary>
    CVHandTrackingData(std::vector<Kinematics::Vect3D>& CVHandPoints, float certainty, bool rightHanded, SGCore::EDeviceType forDeviceType, std::string subHwVersion);

    /// <summary> Creates a new instance of HandTrackingData. </summary>
    CVHandTrackingData(std::vector<Kinematics::Vect3D>& CVHandPoints, float certainty, bool rightHanded, SGCore::EDeviceType forDeviceType, std::string subHwVersion, float time);


    //---------------------------------------------------------------------------------
    // Accessors

public:

    /// <summary> Simulation time When this Data was received. Used for data smoothing. </summary>
    SG_NODISCARD float GetTimeStamp() const;
    void SetTimeStamp(float value);

    /// <summary> 21 positions, representing the wrist and finger positions in 3D (world)space. </summary>
    SG_NODISCARD std::vector<Kinematics::Vect3D> GetJointPositions() const;
    void SetJointPositions(std::vector<Kinematics::Vect3D> value);
    
	/// <summary> Left/Right handedness. </summary>
    SG_NODISCARD bool GetIsRight() const;
    void SetIsRight(bool value);

	/// <summary> How certain is it that this is an actual hand that we're tracking.  </summary>
    SG_NODISCARD float GetCertaintyFactor() const;
    void SetCertaintyFactor(float value);

	/// <summary> Which Device this data has been generated for </summary>
    SG_NODISCARD SGCore::EDeviceType GetForDevice() const;
    void SetForDevice(SGCore::EDeviceType value);

	/// <summary> (sub)hardware version that this data has been generated for. </summary>
    SG_NODISCARD std::string GetForHwVersion() const;
    void SetHwVersion(std::string value);



    //---------------------------------------------------------------------------------
    // Member Functions


public:

    /// <summary> Safely retrieve the location of a specific joint. </summary>
    /// <param name="location"></param>
    /// <returns></returns>
    SG_NODISCARD Kinematics::Vect3D GetPosition(ECVHandPoints location) const;

    /// <summary> Safely retrieve the location of a specific joint. </summary>
    /// <param name="location"></param>
    /// <returns></returns>
    SG_NODISCARD Kinematics::Vect3D GetPositionByIndex(int32_t location) const;

    /// <summary> Returns true if this pose was made for a specific hand, device, and sub-hw version. </summary>
    /// <param name="isRight"></param>
    /// <param name="type"></param>
    /// <param name="hwVer"></param>
    /// <returns></returns>
    SG_NODISCARD bool MatchesDevice(bool isRight, SGCore::EDeviceType type, std::string hwVer);

    /// <summary> Returns true if this pose was made for the same device as another pose. </summary>
    /// <param name="otherPose"></param>
    /// <returns></returns>
    SG_NODISCARD bool MatchesDevice(const CVHandTrackingData otherPose);

    /// <summary> Get a simple notation of this CV_HandTrackingData. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string ToString();

    /// <summary> Prints all of the joint positions within this CV_HandTrackingData. </summary>
    /// <param name="delim"></param>
    /// <returns></returns>
    SG_NODISCARD std::string PrintKeyPoints(std::string delim = ", ");


};
