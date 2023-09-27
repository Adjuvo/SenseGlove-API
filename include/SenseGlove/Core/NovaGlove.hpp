/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2023 SenseGlove
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
    };

    namespace Util
    {
        class SGCORE_API SensorNormalization;
    }
    namespace Nova
    {
        /// <summary> Which vibration motors to send vibrations to </summary>
        enum class SGCORE_API ENovaVibroMotors : int8_t
        {
            /// <summary> Not sure which motor to send this to. </summary>
            Unknown = 0,

            /// <summary> Vibration motor located at the back of the hand. A.k.a. "The Thumper" </summary>
            BackOfHand = 1,
            /// <summary> Vibration motor located at the tip of the thumb </summary>
            ThumbTip = 2,
            /// <summary> Vibration motor located at the tip of the index finger </summary>
            IndexFingerTip = 3
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
    //---------------------------------------------------------------------------------------------------------------------
    // C++ Constructor Voodoo
    
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:

    /// <summary> The default constructor. </summary>
    /// <returns></returns>
    NovaGlove();

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



    //---------------------------------------------------------------------------------------------------------------------
    // Actual C++ Constructor

public:

    /// <summary> Creates a new instance of a Nova Glove. </summary>
    /// <param name="deviceInfo"></param>
    /// <returns></returns>
    explicit NovaGlove(const NovaGloveInfo& deviceInfo);


    //---------------------------------------------------------------------------------
    // Nova 1.0 Accessors

public:

    /// <summary> Byte indicating a new Nova haptic command. </summary>
    static char GetHapticsByte();
    /// <summary> Byte indicating a new Nova thresholds command. </summary>
    static char GetThresholdsByte();
    /// <summary> Byte to ignore Thresholds </summary>
    static char GetIgnoreThresholdsByte();

    /// <summary> Ranges before a Nova 1.0 Sensor is allowed to move. </summary>
    SG_NODISCARD static std::vector<float> GetNovaSensorRanges(); 

    /// <summary> Access all sorts of device info specific to this Nova. </summary>
    /// <returns></returns>
    SG_NODISCARD const NovaGloveInfo& GetGloveInfo() const;

    /// <summary> Create a string representation of this device for reporting purposes. </summary>
    SG_NODISCARD virtual std::string ToString() const override;

    /// <summary> If true, this Nova Glove supports sending special firmware commands to lock brakes at specific sensor values. </summary>
    bool GetSupportsThresholds();

    /// <summary> If true, this Nova Glove supports sending custom 'fire-and-forget' waveforms, </summary>
    bool GetSupportsCustomWaveforms();

    /// <summary> If true, this glove's sesnor calibration runs on board the device. </summary>
    bool GetOnBoardNormalization();

    //---------------------------------------------------------------------------------------------------------
    // SGDevice Implementation

    /// <summary> Return the DeviceType of this Nova. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual EDeviceType GetDeviceType() const override;

    /// <summary> Returns this device's unique identifier. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual std::string GetDeviceId() const override;

    /// <summary> Access this device's hardware designation. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual std::string GetHardwareVersion() const override;

    /// <summary> Access this device's main firmware version. (ex: v3.2 -> 3). </summary>
    /// <returns></returns>
    SG_NODISCARD virtual int32_t GetFirmwareVersion() const override;

    /// <summary> Access this device's sub-firmware version. (ex: v3.2 -> 2). </summary>
    /// <returns></returns>
    SG_NODISCARD virtual int32_t GetSubFirmwareVersion() const override;

public:
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

    /// <summary> Change this device's index within the SenseCom. Warning: Can cause errors. </summary>
    virtual void SetDeviceIndex(int32_t newIndex) override;

public:

    //---------------------------------------------------------------------------------------------------------
    // HapticGlove Implementation

    // Tracking

    /// <summary> Returns true if this glove is meant for right hands. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual bool IsRight() const override;

    /// <summary> Retrieve Nova rotation. </summary>
    /// <param name="IMU"></param>
    /// <returns></returns>
    virtual bool GetImuRotation(Kinematics::Quat& out_imu) override;
    
    /// <summary> Returns the Hand Angles calculated by this Nova 2 Glove. Used for input for HandPoses, but can be used in and of itself. </summary>
    /// <param name="handAngles"></param>
    /// <returns></returns>
    virtual bool GetHandAngles(std::vector<std::vector<Kinematics::Vect3D>>& out_handAngles) override;

    /// <summary> Calculate a HandPose from this glove's latest Sensor Data </summary>
    /// <param name="handGeometry"></param>
    /// <param name="handPose"></param>
    /// <returns></returns>
    virtual bool GetHandPose(const Kinematics::BasicHandModel& handGeometry, HandPose& out_handPose) override;

    // Calibration

    /// <summary> Retrieve the calilbration status of this Nova 2.0 Glove. </summary>
    /// <returns></returns>
    virtual EHapticGloveCalibrationState GetCalibrationState() override;

    /// <summary> Completes sensor Normalization on the Nova 2.0's end. </summary>
    virtual void EndCalibration() override;

    /// <summary>  Completes sensor Normalization on the Nova 2.0's end. </summary>
    void ResetCalibration() override;

    // Basic haptics

    /// <summary> Take all active commands in the device queue, compile them into one and send them to the device. </summary>
    /// <returns> Returns true if the message was sucessfully sent to SenseCom. Returns false if no changes to commands were detected. </returns>
    /// <remarks> Generic function across any Haptic Interface in SGCore </remarks>
    virtual bool SendHaptics() override;

    /// <summary> Stop all haptic feedback effects playing on this device </summary>
    virtual void StopHaptics() override;

    /// <summary> Stop only all vibrotactile feedback </summary>
    virtual void StopVibrations() override;

    // Custom Waveforms

    /// <summary> Returns true if this Glove supports the chosen haptic location. </summary>
    /// <param name="atLocation"></param>
    /// <returns></returns>
    bool SupportsCustomWaveform(EHapticLocation atLocation) override;

    /// <summary> Send a custom waveform to the Nova 2.0 </summary>
    /// <param name="waveform"></param>
    /// <param name="location"></param>
    /// <returns></returns>
    virtual bool SendCustomWaveform(CustomWaveform& waveform, EHapticLocation location) override;

    // Force-Feedback

    /// <summary> Queue a list of force-feedback levels, between 0.0 and 1.0. Your list should be sorted from thumb to pinky. </summary>
    /// <param name="levels01"> Array containing the Force-Feedback levels, from 0.0 (no FFB) to 1.0. A value < 0.0f will be ignored. </param>
    /// <remarks> devices that 'only' have on/off FFB will treat any value > 0.0 as 1.0. </remarks>
    /// <returns></returns>
    bool QueueFFBLevels(std::vector<float> levels01) override;

    /// <summary> Set the Force-Feedback value of a particular finger to a specific level </summary>
    /// <param name="level01"> Value will be clamped between [0...1], where 0.0 means no Force-Feedback, and 1.0 means full force-feedback. </param>
    /// <param name="finger"> The finger to which to send the command. </param>
    /// <returns></returns>
    bool QueueFFBLevel(int32_t finger, float level01) override;


    // 6DoF Position Tracking


    /// <summary> Retrieve the location of the glove origin, based on a reference location. </summary>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin</param>
    /// <param name="trackingHardware">The hardware mounted on the Nova.</param>
    /// <param name="out_glovePosition">The 3D Position of the glove, in mm, relative to your origin</param>
    /// <param name="out_gloveRotation">The 3D Rotation of the glove, relative to your origin</param>
    virtual void GetGloveLocation(const Kinematics::Vect3D& refPosition, const Kinematics::Quat& refRotation,
                                  EPositionalTrackingHardware trackingHardware,
                                  Kinematics::Vect3D& out_glovePosition,
                                  Kinematics::Quat& out_gloveRotation) const override;

    /// <summary> Retrieve the location of the glove origin, based on a reference location without requiring an object reference. </summary>
    /// <param name="refPosition">Position of the tracked object, in mm, relative to your origin</param>
    /// <param name="refRotation">Rotation of the tracked object relative to your origin</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="bRightHanded">Whether this is a left or right-handed glove.</param>
    /// <param name="out_glovePosition">The 3D Position of the glove, in mm, relative to your origin</param>
    /// <param name="out_gloveRotation">The 3D Rotation of the glove, relative to your origin</param>
    static void CalculateGloveLocation(const Kinematics::Vect3D& refPosition, const Kinematics::Quat& refRotation,
                                       EPositionalTrackingHardware trackingHardware, bool bRightHanded,
                                       Kinematics::Vect3D& out_glovePosition, Kinematics::Quat& out_gloveRotation);


    /// <summary> Retrieve the location of the wrist, based on a reference location and default glove-hand offsets. </summary>
    /// <remarks> The simplest interface, using default offsets </remarks>
    /// <param name="referencePosition">Position of the tracked object, in mm, relative to your origin</param>
    /// <param name="referenceRotation">Rotation of the tracked object relative to your origin</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="out_wristPosition">The 3D Position of the wrist, in mm, relative to your origin</param>
    /// <param name="out_wristRotation">The 3D Rotation of the wrist, relative to your origin</param>
    virtual void GetWristLocation(const Kinematics::Vect3D& referencePosition,
                                  const Kinematics::Quat& referenceRotation,
                                  EPositionalTrackingHardware trackingHardware,
                                  Kinematics::Vect3D& out_wristPosition,
                                  Kinematics::Quat& out_wristRotation) const override;

    /// <summary> Retrieve the location of the wrist, based on a reference location and default glove-hand offsets, without needing an object reference. </summary>
    /// <remarks> The simplest interface, using default offsets </remarks>
    /// <param name="refPosition">Position of the tracked object, in mm, relative to your origin</param>
    /// <param name="refRotation">Rotation of the tracked object relative to your origin</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="bRightHanded">Whether this is right or left hand</param>
    /// <param name="out_wristPosition">The 3D Position of the wrist, in mm, relative to your origin</param>
    /// <param name="out_wristRotation">The 3D Rotation of the wrist, relative to your origin</param>
    static void CalculateWristLocation(const Kinematics::Vect3D& refPosition, const Kinematics::Quat& refRotation,
                                       EPositionalTrackingHardware trackingHardware, bool bRightHanded,
                                       Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation);

    //--------------------------------------------------------------------------------------
    // DeviceList Integration

    ///<summary> Deserializes a Nova from its ConstantsString. Returns a nullptr if unsuccessful. </summary>
    /// <param name="constantsString"></param>
    /// <returns></returns>
    static std::shared_ptr<SGDevice> Parse(const std::string& constantsString);

    /// <summary> Retrieve all Nova's. </summary>
    static std::vector<NovaGlove> GetNovaGloves();

    /// <summary> Retrieve the first connected Nova there is. </summary>
    static bool GetNovaGlove(NovaGlove& out_glove);

    /// <summary> Retrieve the first (connected) right or left handed Nova. </summary>
    static bool GetNovaGlove(bool bRightHanded, NovaGlove& out_glove);


    //---------------------------------------------------------------------------------
    // Nova 1.0 Sensor Data Functions

    /// <summary> Get the latest Sensor Data from this Sense Glove. </summary>
    /// <returns></returns>
    bool GetSensorData(NovaGloveSensorData& out_sensorData);

    /// <summary> Convert Sensor Data into a series of normalized values. </summary>
    /// <param name="sData"></param>
    /// <param name="sensorNormalizer"></param>
    /// <returns></returns>
    static std::vector<float> ToNormalizedValues(const NovaGloveSensorData& sData, Util::SensorNormalization& sensorNormalizer);

    /// <summary> Converts Nova_Sensor Data into floating point inputs for normalization. </summary>
    /// <param name="sensorData"></param>
    /// <returns></returns>
    static std::vector<float> ToNormalizedValues(const NovaGloveSensorData& sensorData);

    /// <summary> Returns the normalized Sensor Data of this Nova Glove. If no normalization is running on the glove(s), then it's done on the PC side. </summary>
    /// <param name="normalizedValues"></param>
    /// <returns></returns>
    bool GetNormalizedInput(std::vector<float>& out_normalizedValues);


    //---------------------------------------------------------------------------------
    // Nova 1.0 HandPose Calculations

    /// <summary> Calculate Hand Angles for a Nova 2.0 Glove, based on normalized input. </summary>
    /// <param name="normalizedValues"></param>
    /// <param name="interpolator"></param>
    /// <returns></returns>
    static std::vector<std::vector<Kinematics::Vect3D>> CalculateHandAngles(const std::vector<float>& normalizedValues, Kinematics::HandInterpolator& interpolator);


    //---------------------------------------------------------------------------------
    // Nova 1.0 Haptic Functions

    /// <summary> Converts a set of commands into a series of bytes (string) this glove can understand. </summary>
    /// <param name="ffbLevels">Force-Feedback levels for each finger</param>
    /// <param name="buzzLevels">Vibration levels for each finger</param>
    /// <param name="wristLevel">Value between 0 and 1 for the wirst amplitude to set</param>
    /// <returns></returns>
    virtual std::string ToNovaCommand(const std::vector<float>& ffbLevels, const std::vector<float>& buzzLevels, float wristLevel);


    // Setting Vibration Levels Directly

    /// <summary> Queue a vibrotactile level for each finger. </summary>
    /// <param name="amplitudes"></param>
    /// <returns></returns>
    virtual bool QueueVibroLevels(std::vector<float> amplitudes);

    /// <summary> Queue a vibrotactle level for a specific finger </summary>
    /// <param name="finger"></param>
    /// <param name="amplitude"></param>
    /// <returns></returns>
    virtual bool QueueVibroLevel(int32_t finger, float amplitude);


    /// <summary> Queue a command to the vibration amplitude of a general wrist actuator to a set level.  </summary>
    /// <param name="amplitude"> The amplitude of the wrist vibration, where 0.0 means no vibration, and 1.0 means full vibration. </param>
    /// <returns> Returns true if the wrist command has been sucesfully queued. If false, the device might not support direct wrist control or have the appropriate firmware.  </returns>
    /// <remarks> This one isn't contained in an interface as it's not used outside of the NovaGlove class. </remarks>
    virtual bool QueueWristLevel(float amplitude);


    // Custom Waveforms

    /// <summary> Convert a HapticLocation into a Nova 2.0 Motor location </summary>
    /// <param name="location"></param>
    /// <returns></returns>
    virtual ENovaVibroMotors ToNovaMotor(EHapticLocation location);

    /// <summary> Returns the channel index for a particular motor. Can make this as complex as I want for the Nova GLove(s). </summary>
    /// <param name="motor"></param>
    /// <returns></returns>
    virtual int32_t ChannelIndex(ENovaVibroMotors motor);

    /// <summary> Ensures the waveform that is to be sent to this Nova Glove has the appropriate parameters. </summary>
    /// <param name="waveform"></param>
    /// <param name="motor"></param>
    virtual void ValidateWaveform(CustomWaveform& waveform, ENovaVibroMotors motor);

    /// <summary> Directly sends a custom waveform to the Nova Glove motors, as opposed to specifying a Haptic Location. </summary>
    /// <param name="waveform"></param>
    /// <param name="motor"></param>
    /// <param name="validateWaveform"></param>
    /// <returns></returns>
    virtual bool SendCustomWaveform_Nova(CustomWaveform& waveform, ENovaVibroMotors motor, bool validateWaveform = true);


    // Threshold Commands

    /// <summary> Stops the glove when flexing pas this point. </summary>
    /// <param name="finger"></param>
    /// <param name="flexionThreshold"></param>
    /// <returns></returns>
    bool QueueThresholdCmd_Flexion(int32_t finger, float flexionThreshold);

    /// <summary> Queue a command to clear the threshold for a specific finger. </summary>
    /// <param name="finger"></param>
    /// <returns> Returns true if the command was queued. If false, the device does not have the required firmware for these commands. </returns>
    virtual bool QueueClearThreshold(int32_t finger);

    /// <summary> Converts a Threshold command into a Nova Glove command. </summary>
    /// <param name="thresholds"></param>
    /// <returns></returns>
    static std::string ToNovaCommandAsFlexion(SGCore::Haptics::ThresholdCommand& thresholds);

    /// <summary> Converts a Threshold command into a Nova Glove command. </summary>
    /// <param name="thresholds"></param>
    /// <returns></returns>
    static std::string ToNovaCommandAsRaw(SGCore::Haptics::ThresholdCommand& thresholds, const Util::SensorNormalization& interpolator);

};
