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
 * Interface for Nova 2.0 Gloves.  A soft glove with detachable force-feedback and sensor module, and active contact feedback in the front strap.
 * Since the Nova 2.0 is significantly different from the Nova 1 Glove, it gets its own separate device interface.
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"
#include "HapticGlove.hpp"
#include "Tracking.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;

        class Vect3D;

        class HandInterpolator;
    };// namespace Kinematics

    namespace Util
    {
        /// <summary> Interface for Nova 2.0 Gloves.  A soft glove with detachable force-feedback and sensor module, and active contact feedback in the front strap. </summary>
        class SGCORE_API SensorNormalization;
    } //namespace Util

    namespace Nova
    {
        /// <summary> Which vibration motors to send vibrations to </summary>
        enum class SGCORE_API ENova2VibroMotors : int8_t
        {
            /// <summary> Not sure which motor this is meant for. </summary>
            Unknown = 0,
            /// <summary> LRA Vibration Motor that is located on the thumb fingertip </summary>
            ThumbFingerTip,
            /// <summary> LRA Vibration Motor that is located on the index fingertip </summary>
            IndexFingerTip,
            /// <summary> LRA Vibration Motor that is located on the hand palm, roughly at the Index MCP joint. </summary>
            PalmIndexSide,
            /// <summary> LRA Vibration Motor that is located on the hand palm, roughly at the Pinky MCP joint. </summary>
            PalmPinkySide
        };

        class NovaGloveInfo;

        class SGCORE_API Nova2GloveSensorData;

        /// <summary> Interface for Nova 2.0 Gloves.  A soft glove with detachable force-feedback and sensor module, and active contact feedback in the front strap. </summary>
        class SGCORE_API Nova2Glove;
    } //namespace Nova
}// namespace SGCore

/// <summary> Interface for Nova 2.0 Gloves.  A soft glove with detachable force-feedback and sensor module, and active contact feedback in the front strap. </summary>
class SGCORE_API SGCore::Nova::Nova2Glove : public HapticGlove
{
    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The default constructor. </summary>
    /// <returns></returns>
    Nova2Glove();

    /**
     * The copy constructor.
     */
    Nova2Glove(const Nova2Glove& rhs);

    /**
     * The move constructor.
     */
    Nova2Glove(Nova2Glove&& rhs) noexcept;

    virtual ~Nova2Glove() override;

public:
    /**
     * The copy assignment operator.
     */
    Nova2Glove& operator=(const Nova2Glove& rhs);

    /**
     * The move assignment operator.
     */
    Nova2Glove& operator=(Nova2Glove&& rhs) noexcept;



    //---------------------------------------------------------------------------------
    // Actual C++ Constructor

    /// <summary> Creates a new instance of a Nova Glove. </summary>
    /// <param name="deviceInfo"></param>
    /// <returns></returns>
    explicit Nova2Glove(const NovaGloveInfo& deviceInfo);

    //---------------------------------------------------------------------------------
    // Nova 2.0 Accessors

public:

    /// <summary> Special Byte to identify the command as a Streaming Byte. </summary>
    /// <returns></returns>
    SG_NODISCARD static char GetStreamByte();

    /// <summary> Ranges before a Nova 2.0 Sensor is allowed to move. </summary>
    SG_NODISCARD static std::vector<float> GetNova2SensorRanges();

    /// <summary> If true, the Index Finger sensors will influence the tracking of the other fingers. </summary>
    /// <returns></returns>
    SG_NODISCARD bool GetIndexInfluencesOthers() const;
    void SetIndexInfluencesOthers(bool value);

    /// <summary> If true, the sensors of this Nova Glove are normalized on-board the device. Otherwise, sensor normalization runs inside the library. </summary>
    /// <returns></returns>
    SG_NODISCARD bool GetOnBoardNormalization() const;

    /// <summary> Access DeviceInfo of this Nova </summary>
    /// <returns></returns>
    SG_NODISCARD NovaGloveInfo GetGloveModel();

    /// <summary> Get a string representation of this Nova 2.0 Glove </summary>
    /// <returns></returns>
    SG_NODISCARD virtual std::string ToString() const override;

    //---------------------------------------------------------------------------------------------------------
    // SGDevice Implementation

public:

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

    /// <summary> Retireve this glove's latest IMU rotation, if one is present. </summary>
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

    /// <summary> Flush all streaming haptic effects on the different fingers to the Nova 2.0 Glove </summary>
    /// <returns></returns>
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

    
    // Wrist Squeeze a.k.a. Active Contact Feedback

    /// <summary> Set the amount of squeeze-feedback to the desired level (0 = no squeeze, 1 = full squeeze). </summary>
    /// <param name="squeezeLevel01"></param>
    /// <returns></returns>
    SG_NODISCARD virtual bool QueueSqueezeLevel(float squeezeLevel01);


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


    /// <summary> Retrieve any Glove's location, based on the device properties. if you're interested in Hand Tracking, use GetWristLocation instead. </summary>
    /// <param name="refPosition"></param>
    /// <param name="refRotation"></param>
    /// <param name="trackingHardware"></param>
    /// <param name="rightHand"></param>
    /// <param name="hardwareVersion"></param>
    /// <param name="glovePos"></param>
    /// <param name="gloveRot"></param>
    static void CalculateGloveLocation(const Kinematics::Vect3D& referencePosition,
                                       const Kinematics::Quat& referenceRotation,
                                       EPositionalTrackingHardware trackingHardware,
                                       bool rightHand, const std::string& hardwareVersion,
                                       Kinematics::Vect3D& out_glovePosition,
                                       Kinematics::Quat& out_gloveRotation);


    /// <summary> Retrieve the location of the wrist, based on a reference location and default glove-hand offsets, without needing an object reference. </summary>
    /// <remarks> The simplest interface, using default offsets </remarks>
    /// <param name="refPosition">Position of the tracked object, in mm, relative to your origin</param>
    /// <param name="refRotation">Rotation of the tracked object relative to your origin</param>
    /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
    /// <param name="bRightHanded">Whether this is right or left hand</param>
    /// <param name="out_wristPosition">The 3D Position of the wrist, in mm, relative to your origin</param>
    /// <param name="out_wristRotation">The 3D Rotation of the wrist, relative to your origin</param>
    static void CalculateWristLocation(const Kinematics::Vect3D& refPosition, const Kinematics::Quat& refRotation,
                                       EPositionalTrackingHardware trackingHardware, bool bRightHanded, const std::string& hardwareVersion,
                                       Kinematics::Vect3D& out_wristPosition, Kinematics::Quat& out_wristRotation);



    //--------------------------------------------------------------------------------------
    // DeviceList Integration

public:
    ///<summary> Deserializes a Nova from its ConstantsString. Returns a nullptr if unsuccessful. </summary>
    /// <param name="constantsString"></param>
    /// <returns></returns>
    static std::shared_ptr<SGDevice> Parse(const std::string& constantsString);

    /// <summary> Retrieve all Nova's. </summary>
    static std::vector<Nova2Glove> GetNova2Gloves();

    /// <summary> Retrieve the first connected Nova there is. </summary>
    static bool GetNova2Glove(Nova2Glove& out_glove);

    /// <summary> Retrieve the first (connected) right or left handed Nova. </summary>
    static bool GetNova2Glove(bool bRightHanded, Nova2Glove& out_glove);




    //---------------------------------------------------------------------------------
    // Nova 2.0 Sensor Data Functions

public:

    /// <summary> Get the latest Sensor Data from this Sense Glove. </summary>
    /// <returns></returns>
    bool GetSensorData(Nova2GloveSensorData& out_sensorData);


    /// <summary> Converts Nova_Sensor Data into floating point inputs for normalization. </summary>
    /// <param name="sensorData"></param>
    /// <returns></returns>
    static std::vector<float> ToNormalizedValues(Nova2GloveSensorData& sensorData);

    
    /// <summary> Returns the normalized Sensor Data of this Nova Glove. If no normalization is running on the glove(s), then it's done on the PC side. </summary>
    /// <param name="normalizedValues"></param>
    /// <returns></returns>
    bool GetNormalizedInput(std::vector<float>& out_normalizedValues);


    /// <summary> Tell the Nova Glove to send Raw Data instead of normalized data. </summary>
    /// <returns></returns>
    virtual bool SendRawData();

    /// <summary> Tell the Nova Glove to send normalized data. </summary>
    /// <returns></returns>
    virtual bool SendNormalizedData();

    /// <summary> Convert Sensor Data into a series of normalized values. </summary>
    /// <param name="sData"></param>
    /// <param name="sensorNormalizer"></param>
    /// <returns></returns>
    static std::vector<float> ToNormalizedValues(Nova2GloveSensorData& sData, Util::SensorNormalization& sensorNormalizer);

    //---------------------------------------------------------------------------------
    // Nova 2.0 HandPose Calculations


    /// <summary> Calculate Hand Angles for a Nova 2.0 Glove, based on normalized input. </summary>
    /// <param name="normalizedValues"></param>
    /// <param name="interpolator"></param>
    /// <param name="influenceIndex"></param>
    /// <returns></returns>
    static std::vector<std::vector<Kinematics::Vect3D>> CalculateHandAngles(const std::vector<float>& normalizedValues, Kinematics::HandInterpolator& interpolator, bool influenceIndex);
    

    /// <summary> Convert normalized inputs (5-6 sensors) to input for an Interpolator. </summary>
    /// <param name="normalizedData"></param>
    /// <param name="gloveInfo"></param>
    /// <returns></returns>
    static std::vector<std::vector<Kinematics::Vect3D>> ToNormalizedAngles(const std::vector<float>& normalizedData, const NovaGloveInfo& gloveInfo);


    //---------------------------------------------------------------------------------
    // Nova 2.0 Haptic Functions

public:

    // Nova 2.0 Vibrotactile Feedback

    /// <summary> Returns the channel index for a particular motor. Can make this as complex as I want for the Nova GLove(s). </summary>
    /// <param name="motor"></param>
    /// <returns></returns>
    virtual int32_t ChannelIndex(ENova2VibroMotors motor);

    /// <summary> Ensures the waveform that is to be sent to this Nova Glove has the appropriate parameters. </summary>
    /// <param name="waveform"></param>
    /// <param name="motor"></param>
    virtual void ValidateWaveform(CustomWaveform& waveform, ENova2VibroMotors motor);

    /// <summary> Directly sends a custom waveform to the Nova Glove motors, as opposed to specifying a Haptic Location. </summary>
    /// <param name="waveform"></param>
    /// <param name="motor"></param>
    /// <param name="validateWaveform"></param>
    /// <returns></returns>
    virtual bool SendCustomWaveform_Nova2(CustomWaveform& waveform, ENova2VibroMotors motor, bool validateWaveform = true);

    /// <summary> Convert a HapticLocation into a Nova 2.0 Motor location </summary>
    /// <param name="location"></param>
    /// <returns></returns>
    virtual ENova2VibroMotors ToNova2Motor(EHapticLocation location);


    // TODO: Threshold Commands



protected:

    /// <summary> Convert a series of ffb & squeeze commands into a string to be sent to the glove. </summary>
    static std::string ToStreamCommand(const std::vector<float>& ffbLevels, float squeezeLvl);


};
