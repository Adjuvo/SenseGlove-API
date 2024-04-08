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
 * An interface for the Sense Glove exoskeleton glove.
 * Contains methods for Kinematics, Haptics and Serialization.
 */


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "HapticGlove.hpp"
#include "Platform.hpp"
#include "SenseGloveThumperCommand.hpp"

namespace SGCore
{
    namespace Haptics
    {
        class FingerCommand;

        class ThumperCommand;
    };// namespace Haptics

    namespace Kinematics
    {
        class Quat;

        class Vect3D;

        class HandInterpolator;
    };// namespace Kinematics

    namespace SG
    {
        /// <summary> How this Sense Glove converts sensor data into a HandPose. </summary>
        enum class SGCORE_API EFingerSolver : uint8_t
        {
            /// <summary> Hand angles are interpolated based on the total flexion / abduction of the exoskeleton.
            /// </summary>
            Interpolation = 0,// default.
        };

        /// <summary> How this Sense Glove converts sensor data into a HandPose. </summary>
        enum class SGCORE_API EThumbSolver : uint8_t
        {
            /// <summary> Hand angles are interpolated based on the total flexion / abduction of the exoskeleton.
            /// </summary>
            Interpolation = 0,// default.
        };

        /// <summary> Interface for the Sense Glove; and exoskeleton Force-Feedback glove. </summary>
        class SGCORE_API SenseGlove;

        class SenseGloveInfo;

        class SenseGlovePose;

        class SenseGloveHandProfile;

        class SenseGloveSensorData;

        class SenseGloveSensorNormalizer;
    }// namespace SG

    class HandPose;
}// namespace SGCore

/// <summary> Interface for the Sense Glove; and exoskeleton Force-Feedback glove. </summary>
class SGCORE_API SGCore::SG::SenseGlove : public SGCore::HapticGlove
{
    //--------------------------------------------------------------------------------------
    // DeviceList Integration

public:
    /// <summary> Deserializes a Sense Glove from its ConstantsString. Returns a nullptr if unsuccessful. </summary>
    static std::shared_ptr<SGDevice> Parse(const std::string& constantsString);

    /// <summary> Retrieve all Sense Gloves connected to this system. </summary>
    static std::vector<SenseGlove> GetSenseGloves(bool bOnlyConnected = true);

    /// <summary> Retrieve the first connected Sense Glove there is. </summary>
    static bool GetSenseGlove(SenseGlove& out_glove);

    /// <summary> Retrieve the first (connected) right or left handed sense glove. </summary>
    static bool GetSenseGlove(bool bRightHanded, SenseGlove& out_glove);

    //---------------------------------------------------------------------------------------------------------
    // HapticGlove Implementation

public:
    // 6DoF Position Tracking

    /// <summary> Retrieve the location of the glove origin, based on a reference location without requiring an object
    /// reference. </summary>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin.</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin.</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="bRightHanded">Whether or not this is a left or right handed glove.</param>
    /// <param name="mountedOn">Which finger module the hardware is mounted on. Default is Middle finger.</param>
    /// <param name="out_glovePosition">The 3D Position of the glove, in mm, relative to your origin.</param>
    /// <param name="out_gloveRotation">The 3D Rotation of the glove, relative to your origin.</param>
    static void CalculateGloveLocation(const Kinematics::Vect3D& referencePosition,
                                       const Kinematics::Quat& referenceRotation,
                                       EPositionalTrackingHardware trackingHardware,
                                       bool bRightHanded, EFinger mountedOn,
                                       Kinematics::Vect3D& out_glovePosition, Kinematics::Quat& out_gloveRotation);

    /// <summary> Calculates the full wrist location. </summary>
    /// <param name="referencePosition"></param>
    /// <param name="referenceRotation"></param>
    /// <param name="trackingHardware"></param>
    /// <param name="bRightHanded"></param>
    /// <param name="mountedOn"></param>
    /// <param name="gloveWristPositionOffset"></param>
    /// <param name="gloveWristRotationOffset"></param>
    /// <param name="out_wristPosition"></param>
    /// <param name="out_wristRotation"></param>
    static void CalculateWristLocation(const Kinematics::Vect3D& referencePosition,
                                       const Kinematics::Quat& referenceRotation,
                                       EPositionalTrackingHardware trackingHardware,
                                       bool bRightHanded, EFinger mountedOn,
                                       const Kinematics::Vect3D& gloveWristPositionOffset,
                                       const Kinematics::Quat& gloveWristRotationOffset,
                                       Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation);

    //---------------------------------------------------------------------------------------------------------------------
    // SenseGlove DK1 Accessors

public:
    /// <summary> Byte indicating a new Sense Glove haptic command. </summary>
    SG_NODISCARD static char GetHapticsByte();

    /// <summary> Byte indicating a new Thumper command. </summary>
    SG_NODISCARD static char GetThumperByte();

    /// <summary> Default offset from thimble to fingertip. </summary>
    SG_NODISCARD static const Kinematics::Vect3D& GetDefaultThimbleOffset();

    //---------------------------------------------------------------------------------
    // SenseGlove DK1 Sensor Data Functions

public:
    /// <summary> Calculates a GlovePose based on sensor angles and a glove model. </summary>
    /// <remarks> Use this when you already have gloveAngles collected. </remarks>
    static SenseGlovePose CalculateGlovePose(const SenseGloveSensorData& sensorData, const SenseGloveInfo& gloveModel);

    /// <summary> Calculates a GlovePose based on gloveAngles and a glove model. </summary>
    /// <remarks> Use this when you already have gloveAngles collected. </remarks>
    static SenseGlovePose CalculateGlovePose(const std::vector<std::vector<Kinematics::Vect3D>>& gloveAngles,
                                             const SenseGloveInfo& gloveModel);

    /// <summary> Returns normalized flexions and abductions. </summary>
    /// <param name="sumAngles"></param>
    /// <param name="normalizer"></param>
    /// <param name="out_flexions"></param>
    /// <param name="out_abductions"></param>
    static void NormalizeValues(const std::vector<Kinematics::Vect3D>& sumAngles,
                                const SenseGloveSensorNormalizer& normalizer,
                                std::vector<float>& out_flexions, std::vector<float>& out_abductions);

    //---------------------------------------------------------------------------------
    // SenseGlove DK1 HandPose Calculations

public:
    /// <summary> Calculate Hand Angles from a GlovePose and relevant normalizers. </summary>
    /// <param name="glovePose"></param>
    /// <param name="normalizer"></param>
    /// <param name="normalizedToAngles"></param>
    /// <param name="out_handAngles"></param>
    static void CalculateHandAngles(
            const SenseGlovePose& glovePose,
            const SenseGloveSensorNormalizer& normalizer, const Kinematics::HandInterpolator& normalizedToAngles,
            std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles);

    /// <summary> Calculate a HandPose based on a glovePose and a solver. </summary>
    /// <remarks> Use this when you already have a GlovePose. </remarks>
    /// <param name="glovePose"></param>
    /// <param name="handModel"></param>
    /// <param name="normalizer"></param>
    /// <param name="normalizedToAngles"></param>
    /// <param name="out_handPose"></param>
    /// <returns></returns>
    static void CalculateHandPose(
            const SenseGlovePose& glovePose, const Kinematics::BasicHandModel& handModel,
            const SenseGloveSensorNormalizer& normalizer, const Kinematics::HandInterpolator& normalizedToAngles,
            HandPose& out_handPose);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

    //---------------------------------------------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    /**
     * The default constructor.
     */
    SenseGlove();

    //---------------------------------------------------------------------------------------------------------------------
    // Actual C++ Constructor

    /// <summary> Create a new instance of a Sense Glove. </summary>
    explicit SenseGlove(const SenseGloveInfo& model);

    /**
     * The copy constructor.
     */
    SenseGlove(const SenseGlove& rhs);

    /**
     * The move constructor.
     */
    SenseGlove(SenseGlove&& rhs) noexcept;

    virtual ~SenseGlove() override;

public:
    /**
     * The copy assignment operator.
     */
    SenseGlove& operator=(const SenseGlove& rhs);

    /**
     * The move assignment operator.
     */
    SenseGlove& operator=(SenseGlove&& rhs) noexcept;

    //---------------------------------------------------------------------------------------------------------
    // SGDevice Implementation

public:
    /// <summary> Get the DeviceType enumerator of this SenseGlove, used in DeviceList enumeration. </summary>
    SG_NODISCARD virtual EDeviceType GetDeviceType() const override;

    /// <summary> Retrieve this Sense Glove's unique identifier. </summary>
    SG_NODISCARD virtual const std::string& GetDeviceId() const override;

    /// <summary> Retrieve this glove's hardware (sub) version. </summary>
    SG_NODISCARD virtual const std::string& GetHardwareVersion() const override;

    /// <summary> Retrieve this device's firmware version. </summary>
    SG_NODISCARD virtual int32_t GetFirmwareVersion() const override;

    /// <summary> Retrieve this device's sub-firmware version. </summary>
    SG_NODISCARD virtual int32_t GetSubFirmwareVersion() const override;

    //---------------------------------------------------------------------------------------------------------
    // HapticGlove Implementation

    // Tracking

    /// <summary> Check if this Sense Glove is right handed. </summary>
    /// <remarks> While the variable is stored in SG_GloveModel, added direct access here since its frequently used.
    /// </remarks>
    SG_NODISCARD virtual bool IsRight() const override;

    virtual bool GetImuRotation(Kinematics::Quat& out_imu) override;

    /// <summary> Calculate a HandPose from this glove's latest Sensor Data. </summary>
    /// <param name="handGeometry"></param>
    /// <param name="out_handPose"></param>
    /// <returns></returns>
    virtual bool GetHandPose(const Kinematics::BasicHandModel& handGeometry, HandPose& out_handPose) const override;

    /// <summary> Returns the Hand Angles calculated by this Sense Glove. Used for input for HandPoses, but can be
    /// used in and of itself. </summary>
    /// <param name="out_handAngles"></param>
    /// <returns></returns>
    virtual bool GetHandAngles(std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles) const override;

    // Calibration

    /// <summary> Retrieve the calibration status of this Sense Glove. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual EHapticGloveCalibrationState GetCalibrationState() const override;

    /// <summary> Completes sensor Normalization on the Glove's end. </summary>
    virtual void EndCalibration() override;

    /// <summary>  Completes sensor Normalization on the Glove's end. </summary>
    virtual void ResetCalibration() override;

    // Basic haptics

    /// <summary> Stop all haptic feedback effects playing on this device. </summary>
    virtual void StopHaptics() override;

    /// <summary> Stop only all vibrotactile feedback. </summary>
    virtual void StopVibrations() override;

    /// <summary> Flush all streaming haptic effects on the different fingers to the Glove. </summary>
    /// <returns></returns>
    virtual bool SendHaptics() override;

    // Force-Feedback

    /// <summary> Queue a list of force-feedback levels, between 0.0 and 1.0. Your list should be sorted from thumb to
    /// pinky. </summary>
    /// <param name="levels01"> Array containing the Force-Feedback levels, from 0.0 (no FFB) to 1.0. A value < 0.0f
    /// will be ignored. </param>
    /// <remarks> Devices that 'only' have on/off FFB will treat any value > 0.0 as 1.0. </remarks>
    /// <returns></returns>
    virtual bool QueueForceFeedbackLevels(const std::vector<float>& levels01) override;

    /// <summary> Set the Force-Feedback value of a particular finger to a specific level. </summary>
    /// <param name="level01"> Value will be clamped between [0...1], where 0.0 means no Force-Feedback, and 1.0 means
    /// full force-feedback. </param>
    /// <param name="finger"> The finger to which to send the command. </param>
    /// <returns></returns>
    virtual bool QueueForceFeedbackLevel(int32_t finger, float level01) override;

    // Vibration

    /// <summary> Queue a vibrotactile level for each finger. </summary>
    /// <param name="amplitudes"></param>
    /// <returns></returns>
    virtual bool QueueVibroLevels(const std::vector<float>& levels01) override;

    /// <summary> Queue a command to set the (continuous) vibration level at a specific location to a set amplitude.
    /// </summary>
    /// <param name="location"></param>
    /// <param name="level01">Value will be clamped between [0...1], where 0.0f means no vibration, and 1.0 means
    /// full vibration.</param>
    /// <returns></returns>
    virtual bool QueueVibroLevel(EHapticLocation location, float level01) override;

    // 6DoF Position Tracking

    /// <summary> Retrieve the location of the glove origin, based on a reference location. </summary>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin.</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin.</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="out_glovePosition">The 3D Position of the glove, in mm, relative to your origin.</param>
    /// <param name="out_gloveRotation">The 3D Rotation of the glove, relative to your origin.</param>
    virtual void GetGloveLocation(
            const Kinematics::Vect3D& referencePosition, const Kinematics::Quat& referenceRotation,
            EPositionalTrackingHardware trackingHardware,
            Kinematics::Vect3D& out_glovePosition, Kinematics::Quat& out_gloveRotation) const override;

    /// <summary> Retrieve the location of the glove origin, based on a reference location. </summary>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin.</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin.</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="mountedOn">Which finger module the hardware is mounted on.</param>
    /// <param name="out_glovePosition">The 3D Position of the glove, in mm, relative to your origin.</param>
    /// <param name="out_gloveRotation">The 3D Rotation of the glove, relative to your origin.</param>
    void GetGloveLocation(const Kinematics::Vect3D& referencePosition, const Kinematics::Quat& referenceRotation,
                          EPositionalTrackingHardware trackingHardware, EFinger mountedOn,
                          Kinematics::Vect3D& out_glovePosition, Kinematics::Quat& out_gloveRotation) const;

    /// <summary> Retrieve the location of the wrist, based on a reference location and default glove-hand offsets.
    /// </summary>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin.</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin.</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="out_wristPosition">The 3D Position of the wrist, in mm, relative to your origin.</param>
    /// <param name="out_wristRotation">The 3D Rotation of the wrist, relative to your origin.</param>
    /// <remarks> The simplest interface, using default offsets. </remarks>
    virtual void GetWristLocation(
            const Kinematics::Vect3D& referencePosition, const Kinematics::Quat& referenceRotation,
            EPositionalTrackingHardware trackingHardware,
            Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation) const override;

    /// <summary> Retrieve the location of the wrist, based on a reference location and default glove-hand offsets.
    /// </summary>
    /// <param name="referencePosition"></param>
    /// <param name="referenceRotation"></param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="gloveWristPositionOffset">Position offset, in mm, from the glove origin to wrist
    /// (default = 0,0,-30 mm).</param>
    /// <param name="gloveWristRotationOff">Rotation offset from the glove origin to wrist (default = 0,-5,0 degrees).
    /// </param>
    /// <param name="out_wristPosition">The 3D Position of the wrist, in mm, relative to your origin.</param>
    /// <param name="out_wristRotation">The 3D Rotation of the wrist, relative to your origin.</param>
    void GetWristLocation(const Kinematics::Vect3D& referencePosition, const Kinematics::Quat& referenceRotation,
                          EPositionalTrackingHardware trackingHardware,
                          const Kinematics::Vect3D& gloveWristPositionOffset,
                          const Kinematics::Quat& gloveWristRotationOffset,
                          Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation) const;

    //---------------------------------------------------------------------------------------------------------------------
    // SenseGlove DK1 Accessors

public:
    /// <summary> Retrieve this glove's hardware model, which contains its hardware data. </summary>
    SG_NODISCARD const SenseGloveInfo& GetGloveInfo() const;

    /// <summary> Offset from thimble to fingertip, used for Inverse Kinematics. </summary>
    SG_NODISCARD const std::vector<Kinematics::Vect3D>& GetFingerThimbleOffsets() const;

    void SetFingerThimbleOffset(int32_t finger, const Kinematics::Vect3D& offset);

    SG_NODISCARD bool SupportsWristActuator() const;

    //---------------------------------------------------------------------------------
    // SenseGlove DK1 Sensor Data Functions

public:
    /// <summary> Get the latest Sensor Data from this Sense Glove. </summary>
    bool GetSensorData(SenseGloveSensorData& out_sensorData) const;

    /// <summary> Get the pose of this Sense Glove's hardware, based on its latest Sensor Data. </summary>
    bool GetGlovePose(SenseGlovePose& out_glovePose) const;

    /// <summary> Get the pose of this Sense Glove's hardware based on a set of Sensor Data. </summary>
    bool GetGlovePose(const SenseGloveSensorData& sensorData, SenseGlovePose& out_glovePose) const;

    //---------------------------------------------------------------------------------
    // SenseGlove DK1 Haptic Functions

public:
    /// <summary> Queue a vibrotactle level for a specific finger. </summary>
    /// <param name="finger"></param>
    /// <param name="amplitude"></param>
    /// <returns></returns>
    virtual bool QueueVibroLevel(int32_t finger, float amplitude);

    /// <summary> Queue a command for the SenseGlove Thumper actuator. </summary>
    /// <param name="command"></param>
    /// <returns></returns>
    virtual bool QueueThumperCommand(Haptics::ESenseGloveThumperCommand command);

protected:
    /// <summary> Convert amplitudes into a SenseGlove command. </summary>
    /// <param name="forceFeedbackLevels"></param>
    /// <param name="buzzLevels"></param>
    /// <param name="thumperCommand"></param>
    /// <returns></returns>
    SG_NODISCARD std::string ToSenseGloveCommand(
            const std::vector<float>& forceFeedbackLevels, const std::vector<float>& buzzLevels,
            Haptics::ESenseGloveThumperCommand thumperCommand) const;

    //--------------------------------------------------------------------------------------

public:
    /// <summary> Create a string representation of this device for reporting purposes. </summary>
    SG_NODISCARD virtual std::string ToString() const override;
};