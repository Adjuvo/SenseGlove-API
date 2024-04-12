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
 * Unprocessed data received from CV Device(s), used as input for processing.
 * Used as a separate class so the format is ensured.
 */


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "DeviceTypes.hpp"
#include "Platform.hpp"

namespace SGCore
{
    namespace CV
    {
        //----------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // Tracking Depth Enum

        /// <summary> How much of the CV tracking is being used. Used by other APIs. </summary>
        enum class SGCORE_API ECVTrackingDepth : uint8_t
        {
            /// <summary> No computer-vision is enabled. </summary>
            Disabled = 0,

            /// <summary> Use CV only for the wrist position/rotation. </summary>
            WristOnly,

            /// <summary> Use CV for both the wrist location and Hand Position. </summary>
            WristAndHandPose,
        };

        //----------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // Position Enum

        /// <summary> Used to access specific positions from the CV output, which is an array of Vect3D positions.
        /// </summary>
        /// <remarks> Declared in CVHandOutput.cs because these enums are used to index the jointPositions array in
        /// that class. </remarks>
        enum class SGCORE_API ECVHandPoints : uint8_t
        {
            /// <summary> The position of the Wrist as determined by the CV Model. </summary>
            Wrist = 0,

            /// <summary> The position of the Thumb CMC Joint as determined by the CV Model. </summary>
            ThumbCmc,
            /// <summary> The position of the Thumb MCP Joint as determined by the CV Model. </summary>
            ThumbMcp,
            /// <summary> The position of the Thumb IP Joint as determined by the CV Model. </summary>
            ThumbIp,
            /// <summary> The position of the Thumb tip as determined by the CV Model. </summary>
            ThumbTip,

            /// <summary> The position of the Index MCP Joint as determined by the CV Model. </summary>
            IndexMcp,
            /// <summary> The position of the Index PIP Joint as determined by the CV Model. </summary>
            IndexPip,
            /// <summary> The position of the Index DIP Joint as determined by the CV Model. </summary>
            IndexDip,
            /// <summary> The position of the Index fingertip as determined by the CV Model. </summary>
            IndexTip,

            /// <summary> The position of the Middle MCP Joint as determined by the CV Model. </summary>
            MiddleMcp,
            /// <summary> The position of the Middle PIP Joint as determined by the CV Model. </summary>
            MiddlePip,
            /// <summary> The position of the Middle DIP Joint as determined by the CV Model. </summary>
            MiddleDip,
            /// <summary> The position of the Middle fingertip as determined by the CV Model. </summary>
            MiddleTip,

            /// <summary> The position of the Ring MCP Joint as determined by the CV Model. </summary>
            RingMcp,
            /// <summary> The position of the Ring PIP Joint as determined by the CV Model. </summary>
            RingPip,
            /// <summary> The position of the Ring DIP Joint as determined by the CV Model. </summary>
            RingDip,
            /// <summary> The position of the Ring fingertip as determined by the CV Model. </summary>
            RingTip,

            /// <summary> The position of the Pinky MCP Joint as determined by the CV Model. </summary>
            PinkyMcp,
            /// <summary> The position of the Pinky PIP Joint as determined by the CV Model. </summary>
            PinkyPip,
            /// <summary> The position of the Pinky DIP Joint as determined by the CV Model. </summary>
            PinkyDip,
            /// <summary> The position of the Pinky fingertip as determined by the CV Model. </summary>
            PinkyTip,

            /// <summary> Utility enumerator to check if an array contains enough values. </summary>
            All,
        };

        /// <summary> Unprocessed data received from CV Device(s), used as input for processing. </summary>
        class SGCORE_API CVHandTrackingData;
    }// namespace CV

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
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /**
     * The default constructor.
     */
    CVHandTrackingData();

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    /// <summary> Creates a new instance of HandTrackingData. Time is takes from the internal system </summary>
    CVHandTrackingData(const std::vector<Kinematics::Vect3D>& CVHandPoints, float certainty, bool bRightHanded,
                       SGCore::EDeviceType forDeviceType, const std::string& subHardwareVersion);

    /// <summary> Creates a new instance of HandTrackingData. </summary>
    CVHandTrackingData(const std::vector<Kinematics::Vect3D>& CVHandPoints, float certainty, bool bRightHanded,
                       SGCore::EDeviceType forDeviceType, const std::string& subHardwareVersion, float time);

    /**
     * The copy constructor.
     */
    CVHandTrackingData(const CVHandTrackingData& rhs);

    /**
     * The move constructor.
     */
    CVHandTrackingData(CVHandTrackingData&& rhs) noexcept;

    virtual ~CVHandTrackingData();

public:
    /**
     * The copy assignment operator.
     */
    CVHandTrackingData& operator=(const CVHandTrackingData& rhs);

    /**
     * The move assignment operator.
     */
    CVHandTrackingData& operator=(CVHandTrackingData&& rhs) noexcept;

public:
    /// <summary> Simulation time When this Data was received. Used for data smoothing. </summary>
    SG_NODISCARD float GetTimeStamp() const;
    void SetTimeStamp(float timestamp);

    /// <summary> 21 positions, representing the wrist and finger positions in 3D (world)space. </summary>
    SG_NODISCARD std::vector<Kinematics::Vect3D> GetJointPositions() const;
    void SetJointPositions(const std::vector<Kinematics::Vect3D>& positions);

    /// <summary> Left/Right handedness. </summary>
    SG_NODISCARD bool IsRight() const;
    void SetRight(bool bRight);

    /// <summary> How certain is it that this is an actual hand that we're tracking.  </summary>
    SG_NODISCARD float GetCertaintyFactor() const;
    void SetCertaintyFactor(float factor);

    /// <summary> Which Device this data has been generated for </summary>
    SG_NODISCARD SGCore::EDeviceType GetForDevice() const;
    void SetForDevice(SGCore::EDeviceType type);

    /// <summary> (sub)hardware version that this data has been generated for. </summary>
    SG_NODISCARD std::string GetForHwVersion() const;
    void SetHwVersion(const std::string& version);

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
    /// <param name="bRight"></param>
    /// <param name="type"></param>
    /// <param name="hardwareVersion"></param>
    /// <returns></returns>
    SG_NODISCARD bool MatchesDevice(bool bRight, SGCore::EDeviceType type, const std::string& hardwareVersion);

    /// <summary> Returns true if this pose was made for the same device as another pose. </summary>
    /// <param name="otherPose"></param>
    /// <returns></returns>
    SG_NODISCARD bool MatchesDevice(const CVHandTrackingData& otherPose);

    /// <summary> Get a simple notation of this CV_HandTrackingData. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string ToString() const;

    /// <summary> Prints all of the joint positions within this CV_HandTrackingData. </summary>
    /// <param name="delimiter"></param>
    /// <returns></returns>
    SG_NODISCARD std::string PrintKeyPoints(const std::string& delimiter = ", ");
};