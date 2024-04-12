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
 * An interface for the "Nova" - a soft glove.
 * Contains methods for Kinematics, Haptics and Serialization.
*/


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "HapticGlove.hpp"
#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;

        class Vect3D;

        class HandInterpolator;
    };// namespace Kinematics

    namespace Haptics
    {
        class SGCORE_API ThresholdCommand;

        class SGCORE_API CustomWaveform;
    };// namespace Haptics

    namespace Util
    {
        class SGCORE_API SensorNormalization;
    }
    namespace Nova
    {
        /// <summary> Which vibration motors to send vibrations to. </summary>
        enum class SGCORE_API ENovaVibroMotor : uint8_t
        {
            /// <summary> Not sure which motor to send this to. </summary>
            Unknown = 0,

            /// <summary> Vibration motor located at the back of the hand. A.k.a. "The Thumper". </summary>
            BackOfHand = 1,

            /// <summary> Vibration motor located at the tip of the thumb. </summary>
            ThumbTip = 2,

            /// <summary> Vibration motor located at the tip of the index finger. </summary>
            IndexFingertip = 3,
        };

        class NovaGloveInfo;

        class NovaGloveSensorData;

        /// <summary> A soft glove with Force- and Vibrotactile Feedback and limited tracking. </summary>
        class SGCORE_API NovaGlove;
    }// namespace Nova
}// namespace SGCore


/// <summary> A soft glove with Force- and Vibrotactile Feedback and limited tracking. </summary>
class SGCORE_API SGCore::Nova::NovaGlove : public HapticGlove
{
    //--------------------------------------------------------------------------------------
    // DeviceList Integration

public:
    /// <summary> Deserializes a Nova from its ConstantsString. Returns a nullptr if unsuccessful. </summary>
    /// <param name="constantsString"></param>
    /// <returns></returns>
    static std::shared_ptr<SGDevice> Parse(const std::string& constantsString);

    /// <summary> Retrieve all Nova's. </summary>
    static std::vector<NovaGlove> GetNovaGloves();

    /// <summary> Retrieve the first connected Nova there is. </summary>
    static bool GetNovaGlove(NovaGlove& out_glove);

    /// <summary> Retrieve the first (connected) right or left handed Nova. </summary>
    static bool GetNovaGlove(bool bRightHanded, NovaGlove& out_glove);

    //---------------------------------------------------------------------------------------------------------
    // HapticGlove Implementation

public:
    // 6DoF Position Tracking

    /// <summary> Retrieve the location of the glove origin, based on a reference location without requiring an object
    /// reference. </summary>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin.</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin.</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="bRightHanded">Whether this is a left or right-handed glove.</param>
    /// <param name="out_glovePosition">The 3D Position of the glove, in mm, relative to your origin.</param>
    /// <param name="out_gloveRotation">The 3D Rotation of the glove, relative to your origin.</param>
    static void CalculateGloveLocation(const Kinematics::Vect3D& refPosition, const Kinematics::Quat& refRotation,
                                       EPositionalTrackingHardware trackingHardware, bool bRightHanded,
                                       Kinematics::Vect3D& out_glovePosition, Kinematics::Quat& out_gloveRotation);

    /// <summary> Retrieve the location of the wrist, based on a reference location and default glove-hand offsets,
    /// without needing an object reference. </summary>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin.</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin.</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="bRightHanded">Whether this is right or left hand.</param>
    /// <param name="out_wristPosition">The 3D Position of the wrist, in mm, relative to your origin.</param>
    /// <param name="out_wristRotation">The 3D Rotation of the wrist, relative to your origin.</param>
    /// <remarks> The simplest interface, using default offsets. </remarks>
    static void CalculateWristLocation(const Kinematics::Vect3D& refPosition, const Kinematics::Quat& refRotation,
                                       EPositionalTrackingHardware trackingHardware, bool bRightHanded,
                                       Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation);

    //---------------------------------------------------------------------------------
    // Nova 1.0 Accessors

public:
    /// <summary> Byte indicating a new Nova haptic command. </summary>
    SG_NODISCARD static char GetHapticsByte();

    /// <summary> Byte indicating a new Nova thresholds command. </summary>
    SG_NODISCARD static char GetThresholdsByte();

    /// <summary> Byte to ignore Thresholds. </summary>
    SG_NODISCARD static char GetIgnoreThresholdsByte();

    /// <summary> Ranges before a Nova 1.0 Sensor is allowed to move. </summary>
    SG_NODISCARD static const std::vector<float>& GetNovaSensorRanges();

    //---------------------------------------------------------------------------------
    // Nova 1.0 Sensor Data Functions

public:
    /// <summary> Converts Nova Sensor Data into floating point inputs for normalization. </summary>
    /// <param name="sensorData"></param>
    /// <returns></returns>
    static std::vector<float> ToNormalizedValues(const NovaGloveSensorData& sensorData);

    /// <summary> Convert Sensor Data into a series of normalized values. </summary>
    /// <param name="sensorData"></param>
    /// <param name="out_sensorNormalizer"></param>
    /// <returns></returns>
    static std::vector<float> ToNormalizedValues(
            const NovaGloveSensorData& sensorData, Util::SensorNormalization& out_sensorNormalizer);

    //---------------------------------------------------------------------------------
    // Nova 1.0 HandPose Calculations

public:
    /// <summary> Calculate Hand Angles for a Nova Glove, based on normalized input. </summary>
    /// <param name="normalizedValues"></param>
    /// <param name="interpolator"></param>
    /// <returns></returns>
    static std::vector<std::vector<Kinematics::Vect3D>> CalculateHandAngles(
            const std::vector<float>& normalizedValues, const Kinematics::HandInterpolator& interpolator);

    //---------------------------------------------------------------------------------
    // Nova 1.0 Haptic Functions

public:
    // Threshold Commands

    /// <summary> Converts a Threshold command into a Nova Glove command. </summary>
    /// <param name="thresholds"></param>
    /// <returns></returns>
    static std::string ToNovaCommandAsFlexion(const SGCore::Haptics::ThresholdCommand& thresholds);

    /// <summary> Converts a Threshold command into a Nova Glove command. </summary>
    /// <param name="thresholds"></param>
    /// <param name="interpolator"></param>
    /// <returns></returns>
    static std::string ToNovaCommandAsRaw(
            const SGCore::Haptics::ThresholdCommand& thresholds, const Util::SensorNormalization& interpolator);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

    //---------------------------------------------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    /// <summary> The default constructor. </summary>
    /// <returns></returns>
    NovaGlove();

    //---------------------------------------------------------------------------------------------------------------------
    // Actual C++ Constructor

    /// <summary> Creates a new instance of a Nova Glove. </summary>
    /// <param name="deviceInfo"></param>
    /// <returns></returns>
    explicit NovaGlove(const NovaGloveInfo& deviceInfo);

    /**
     * The copy constructor.
     */
    NovaGlove(const NovaGlove& rhs);

    /**
     * The move constructor.
     */
    NovaGlove(NovaGlove&& rhs) noexcept;

    virtual ~NovaGlove() override;

public:
    /**
     * The copy assignment operator.
     */
    NovaGlove& operator=(const NovaGlove& rhs);

    /**
     * The move assignment operator.
     */
    NovaGlove& operator=(NovaGlove&& rhs) noexcept;

    //---------------------------------------------------------------------------------------------------------
    // SGDevice Implementation

public:
    /// <summary> Return the DeviceType of this Nova. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual EDeviceType GetDeviceType() const override;

    /// <summary> Returns this device's unique identifier. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual const std::string& GetDeviceId() const override;

    /// <summary> Access this device's hardware designation. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual const std::string& GetHardwareVersion() const override;

    /// <summary> Access this device's main firmware version. (ex: v3.2 -> 3). </summary>
    /// <returns></returns>
    SG_NODISCARD virtual int32_t GetFirmwareVersion() const override;

    /// <summary> Access this device's sub-firmware version. (ex: v3.2 -> 2). </summary>
    /// <returns></returns>
    SG_NODISCARD virtual int32_t GetSubFirmwareVersion() const override;

    /// <summary> Change this device's index within the SenseCom. Warning: Can cause errors. </summary>
    virtual void SetDeviceIndex(int32_t newIndex) override;

    /// <summary> Returns true if this device operates on a battery. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual bool HasBattery() const override;

    /// <summary> Returns true if this device is currently charging. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual bool IsCharging() override;

    /// <summary> Returns the device's battery level, as a value between 0 (empty) and 1 (full). </summary>
    /// <param name="batteryLevel"></param>
    /// <returns></returns>
    SG_NODISCARD virtual bool GetBatteryLevel(float& out_batteryLevel) override;

    //---------------------------------------------------------------------------------------------------------
    // HapticGlove Implementation

public:
    // Tracking

    /// <summary> Returns true if this glove is meant for right hands. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual bool IsRight() const override;

    /// <summary> Retrieve Nova rotation. </summary>
    /// <param name="out_imu"></param>
    /// <returns></returns>
    virtual bool GetImuRotation(Kinematics::Quat& out_imu) override;

    /// <summary> Calculate a HandPose from this glove's latest Sensor Data. </summary>
    /// <param name="handGeometry"></param>
    /// <param name="out_handPose"></param>
    /// <returns></returns>
    virtual bool GetHandPose(const Kinematics::BasicHandModel& handGeometry, HandPose& out_handPose) const override;

    /// <summary> Returns the Hand Angles calculated by this Nova Glove. Used for input for HandPoses, but can be used
    /// in and of itself. </summary>
    /// <param name="out_handAngles"></param>
    /// <returns></returns>
    virtual bool GetHandAngles(std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles) const override;

    // Calibration

    /// <summary> Retrieve the calibration status of this Nova Glove. </summary>
    /// <returns></returns>
    virtual EHapticGloveCalibrationState GetCalibrationState() const override;

    /// <summary> Completes sensor Normalization on the Nova's end. </summary>
    virtual void EndCalibration() override;

    /// <summary>  Completes sensor Normalization on the Nova's end. </summary>
    virtual void ResetCalibration() override;

    /// <summary> Attempt to load a HapticGlove Profile from disk, if one exists. </summary>
    virtual void TryLoadProfile() override;

    // Basic haptics

    /// <summary> Stop all haptic feedback effects playing on this device. </summary>
    virtual void StopHaptics() override;

    /// <summary> Stop only all vibrotactile feedback. </summary>
    virtual void StopVibrations() override;

    /// <summary> Take all active commands in the device queue, compile them into one and send them to the device.
    /// </summary>
    /// <returns> Returns true if the message was successfully sent to SenseCom. Returns false if no changes to commands
    /// were detected. </returns>
    /// <remarks> Generic function across any Haptic Interface in SGCore. </remarks>
    virtual bool SendHaptics() override;

    // Custom Waveforms

    /// <summary> Returns true if this Glove supports the chosen haptic location. </summary>
    /// <param name="atLocation"></param>
    /// <returns></returns>
    SG_NODISCARD virtual bool SupportsCustomWaveform(EHapticLocation atLocation) const override;

    /// <summary> Send a custom waveform to the Nova. </summary>
    /// <param name="out_waveform"></param>
    /// <param name="location"></param>
    /// <returns></returns>
    virtual bool SendCustomWaveform(CustomWaveform& out_waveform, EHapticLocation location) override;

    // Force-Feedback

    /// <summary> Queue a list of force-feedback levels, between 0.0 and 1.0. Your list should be sorted from thumb to
    /// pinky. </summary>
    /// <param name="levels01"> Array containing the Force-Feedback levels, from 0.0 (no FFB) to 1.0. A value < 0.0f
    /// will be ignored. </param>
    /// <remarks> Devices that 'only' have on/off FFB will treat any value > 0.0 as 1.0. </remarks>
    /// <returns></returns>
    virtual bool QueueForceFeedbackLevels(const std::vector<float>& levels01) override;

    /// <summary> Set the Force-Feedback value of a particular finger to a specific level. </summary>
    /// <param name="finger"> The finger to which to send the command. </param>
    /// <param name="level01"> Value will be clamped between [0...1], where 0.0 means no Force-Feedback, and 1.0 means
    /// full force-feedback. </param>
    /// <returns></returns>
    virtual bool QueueForceFeedbackLevel(int32_t finger, float level01) override;

    // Vibration

    /// <summary> Queue a vibrotactile level for each finger. </summary>
    /// <param name="levels01"></param>
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
    /// <param name="trackingHardware">The hardware mounted on the Nova.</param>
    /// <param name="out_glovePosition">The 3D Position of the glove, in mm, relative to your origin.</param>
    /// <param name="out_gloveRotation">The 3D Rotation of the glove, relative to your origin.</param>
    virtual void GetGloveLocation(const Kinematics::Vect3D& referencePosition,
                                  const Kinematics::Quat& referenceRotation,
                                  EPositionalTrackingHardware trackingHardware,
                                  Kinematics::Vect3D& out_glovePosition,
                                  Kinematics::Quat& out_gloveRotation) const override;

    /// <summary> Retrieve the location of the wrist, based on a reference location and default glove-hand offsets.
    /// </summary>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin.</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin.</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="out_wristPosition">The 3D Position of the wrist, in mm, relative to your origin.</param>
    /// <param name="out_wristRotation">The 3D Rotation of the wrist, relative to your origin.</param>
    /// <remarks> The simplest interface, using default offsets. </remarks>
    virtual void GetWristLocation(const Kinematics::Vect3D& referencePosition,
                                  const Kinematics::Quat& referenceRotation,
                                  EPositionalTrackingHardware trackingHardware,
                                  Kinematics::Vect3D& out_wristPosition,
                                  Kinematics::Quat& out_wristRotation) const override;

    //---------------------------------------------------------------------------------
    // Nova 1.0 Accessors

public:
    /// <summary> Access all sorts of device info specific to this Nova. </summary>
    /// <returns></returns>
    SG_NODISCARD const NovaGloveInfo& GetGloveInfo() const;

    /// <summary> If true, this Nova Glove supports sending special firmware commands to lock brakes at specific sensor
    /// values. </summary>
    SG_NODISCARD bool SupportsThresholds() const;

    /// <summary> If true, this Nova Glove supports sending custom 'fire-and-forget' waveforms. </summary>
    SG_NODISCARD bool SupportsCustomWaveforms() const;

    /// <summary> If true, this glove's sensor calibration runs on board the device. </summary>
    SG_NODISCARD bool SupportsOnBoardNormalization() const;

public:
    //---------------------------------------------------------------------------------
    // Nova 1.0 Sensor Data Functions

    /// <summary> Get the latest Sensor Data from this Glove. </summary>
    /// <returns></returns>
    bool GetSensorData(NovaGloveSensorData& out_sensorData) const;

    /// <summary> Returns the normalized Sensor Data of this Nova Glove. If no normalization is running on the glove(s),
    /// then it's done on the PC side. </summary>
    /// <param name="out_normalizedValues"></param>
    /// <returns></returns>
    bool GetNormalizedInput(std::vector<float>& out_normalizedValues) const;

    //---------------------------------------------------------------------------------
    // Nova 1.0 Haptic Functions

    /// <summary> Converts a set of commands into a series of bytes (string) this glove can understand. </summary>
    /// <param name="forceFeedbackLevels">Force-Feedback levels for each finger.</param>
    /// <param name="buzzLevels">Vibration levels for each finger.</param>
    /// <param name="wristLevel">Value between 0 and 1 for the wrist amplitude to set.</param>
    /// <returns></returns>
    virtual std::string ToNovaCommand(
            const std::vector<float>& forceFeedbackLevels, const std::vector<float>& buzzLevels, float wristLevel) const;

    // Setting Vibration Levels Directly

    /// <summary> Queue a vibrotactle level for a specific finger. </summary>
    /// <param name="finger"></param>
    /// <param name="amplitude"></param>
    /// <returns></returns>
    virtual bool QueueVibroLevel(int32_t finger, float amplitude);

    /// <summary> Queue a command to the vibration amplitude of a general wrist actuator to a set level. </summary>
    /// <param name="amplitude"> The amplitude of the wrist vibration, where 0.0 means no vibration, and 1.0 means full
    /// vibration. </param>
    /// <returns> Returns true if the wrist command has been successfully queued. If false, the device might not support
    /// direct wrist control or have the appropriate firmware. </returns>
    /// <remarks> This one isn't contained in an interface as it's not used outside of the NovaGlove class. </remarks>
    virtual bool QueueWristLevel(float amplitude);

    // Custom Waveforms

    /// <summary> Convert a HapticLocation into a Nova Motor location. </summary>
    /// <param name="location"></param>
    /// <returns></returns>
    SG_NODISCARD virtual ENovaVibroMotor ToNovaMotor(EHapticLocation location) const;

    /// <summary> Returns the channel index for a particular motor. Can make this as complex as I want for the Nova
    /// GLove(s). </summary>
    /// <param name="motor"></param>
    /// <returns></returns>
    SG_NODISCARD virtual int32_t ChannelIndex(ENovaVibroMotor motor) const;

    /// <summary> Ensures the waveform that is to be sent to this Nova Glove has the appropriate parameters. </summary>
    /// <param name="out_waveform"></param>
    /// <param name="motor"></param>
    virtual void ValidateWaveform(CustomWaveform& out_waveform, ENovaVibroMotor motor) const;

    /// <summary> Directly sends a custom waveform to the Nova Glove motors, as opposed to specifying a Haptic Location.
    /// </summary>
    /// <param name="out_waveform"></param>
    /// <param name="motor"></param>
    /// <param name="bValidateWaveform"></param>
    /// <returns></returns>
    virtual bool SendCustomWaveform_Nova(CustomWaveform& out_waveform, ENovaVibroMotor motor,
                                         bool bValidateWaveform = true);

    // Threshold Commands

    /// <summary> Stops the glove when flexing pas this point. </summary>
    /// <param name="finger"></param>
    /// <param name="flexionThreshold"></param>
    /// <returns></returns>
    bool QueueThresholdCommand_Flexion(int32_t finger, float flexionThreshold);

    /// <summary> Queue a command to clear the threshold for a specific finger. </summary>
    /// <param name="finger"></param>
    /// <returns> Returns true if the command was queued. If false, the device does not have the required firmware for
    /// these commands. </returns>
    virtual bool QueueClearThreshold(int32_t finger);

    //--------------------------------------------------------------------------------------

public:
    /// <summary> Create a string representation of this device for reporting purposes. </summary>
    SG_NODISCARD virtual std::string ToString() const override;
};