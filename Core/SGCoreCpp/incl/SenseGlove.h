// ----------------------------------------------------------------------------------
// An interface for the Sense Glove exoskeleton glove.
// Contains methods for Kinematics, Haptics and Serialization.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include "SGDevice.h"
#include "SG_GloveInfo.h"
#include "SG_SensorData.h"
#include "SG_GlovePose.h"
#include "SG_HandProfile.h"
#include "HandPose.h"
#include "HapticGlove.h"

#include "SG_FFBCmd.h"
#include "SG_BuzzCmd.h"
#include "SG_ThumperCmd.h"

#include <memory>

namespace SGCore
{
	namespace SG
	{
		

		//--------------------------------------------------------------------------------------
		// Sense Glove Interface

		/// <summary> Interface for the Sense Glove; and exoskeleton Force-Feedback glove. </summary>
		class SGCORE_API SenseGlove : public HapticGlove
		{

		protected:

			//--------------------------------------------------------------------------------------
			// Properties

			/// <summary> Contains all data regarding this Sense Glove </summary>
			/// <remarks> 
			/// We're not using a generic DeviceModel as that would require casting
			/// its DeviceModel to an SGModel each frame. Adding this interface here is faster
			/// </remarks>
			//SG_Model gloveModel;

			SG_GloveInfo gloveInfo;

			/// <summary> Byte indicating a new Sense Glove haptic command. </summary>
			const static char hapticsByte;
			/// <summary> Byte indicating a new Thumper command. </summary>
			const static char thumperByte;


			//--------------------------------------------------------------------------------------
			// Internal Methods

			/// <summary> Convert a Force-Feedback command to a string which can be sent to this particular Sense Glove device. </summary>
			/// <remarks> Implemented here because the conversion may depend on firmware/hardware version. </remarks>
			std::string ToBytes(Haptics::SG_FingerCmd cmd);

			/// <summary> Convert a Thumper command into a string that this SenseGlove can understand. </summary>
			/// <param name="cmd"></param>
			/// <returns></returns>
			std::string ToBytes(Haptics::ThumperCmd cmd);

		public:

			//--------------------------------------------------------------------------------------
			// Construction

			///<summary> Basic Constructor </summary>
			SenseGlove();

			///<summary> Basic Destructor </summary>
			~SenseGlove();

			/// <summary> Create a new instance of a Sense Glove. </summary>
			SenseGlove(SG_GloveInfo myModel);

			//--------------------------------------------------------------------------------------
			// SGDevice Methods

			///<summary> Get the DeviceType enumerator of this SenseGlove, used in DeviceList enumeration. </summary>
			DeviceType GetDeviceType() override { return DeviceType::SENSEGLOVE; }

			/// <summary> Retrieve this Sense Glove's unique identifier. </summary>
			std::string GetDeviceID() override { return gloveInfo.deviceID; };

			/// <summary> Retrieve this glove's hardware (sub) version.  </summary>
			std::string GetHardwareVersion() override { return gloveInfo.hardwareVer; };

			/// <summary> Retrieve this device's firmware version. </summary>
			int GetFirmwareVersion() override { return gloveInfo.firmwareVer; };

			/// <summary> Retrieve this device's sub-firmware version. </summary>
			int GetSubFirmwareVersion() override { return gloveInfo.subFirmwareVer; }

			//--------------------------------------------------------------------------------------
			// Class Methods

			/// <summary> Create a string representation of this device for reporting purposes. </summary>
			std::string ToString() override { return "Sense Glove " + GetDeviceID(); };

			/// <summary> Check if this Sense Glove is right handed. </summary>
			/// <remarks> While the variable is stored in SG_GloveModel, added direct access here since its frequently used. </remarks>
			bool IsRight() { return gloveInfo.isRight; } //direct access since its frequently used.

			/// <summary> Retrieve this glove's hardware model, which contains its hardware data. </summary>
			SG_GloveInfo GetGloveModel() { return gloveInfo; }


			/// <summary> Get the latest Sensor Data from this Sense Glove </summary>
			bool GetSensorData(SG_SensorData& sensorData);

			bool GetIMURotation(Kinematics::Quat& IMU) override;

			/// <summary> Get the pose of this Sense Glove's hardware, based on its latest Sensor Data </summary>
			bool GetGlovePose(SG_GlovePose& glovePose);

			/// <summary> Get the pose of this Sense Glove's hardware based on a set of Sensor Data </summary>
			bool GetGlovePose(SG::SG_SensorData sData, SG_GlovePose& glovePose);

			/// <summary> Retrieve a new hand pose using this glove's data, based on (calibrated) user data. </summary>
			bool GetHandPose(Kinematics::BasicHandModel& handGeometry, SG_HandProfile& profile, HandPose& handPose);

			/// <summary> Calculate the Hand Pose of this device, provided it has Hand Tracking available  </summary>
			bool GetHandPose(Kinematics::BasicHandModel& handGeometry, HandProfile& handProfile, HandPose& handPose) override;

			/// <summary> Calculate the HandPose of this Device, taking into account user values, but not hand geometry. </summary>
			bool GetHandPose(HandProfile& handProfile, HandPose& handPose) override;


			//--------------------------------------------------------------------------------------
			// Feedback Methods

			/// <summary> Set the level(s) of Force and Vibrotactile feedback, with an optional thumper command </summary>
			bool SendHaptics(Haptics::SG_FFBCmd ffbCmd, Haptics::SG_BuzzCmd buzzCmd,
				Haptics::SG_ThumperCmd thumperCmd = Haptics::SG_ThumperCmd::None);


			/// <summary> Send a thumper command. </summary>
			bool SendHaptics(Haptics::SG_ThumperCmd thumperCmd);

			/// <summary> Send Haptic Commands to this Glove. </summary>
			void SendHaptics(Haptics::SG_FFBCmd ffb) override 
			{
				SendHaptics(ffb, lastBuzzCmd, lastThumper);
			}

			/// <summary> Send Haptic Commands to this Glove. </summary>
			void SendHaptics(Haptics::SG_BuzzCmd buzz) override
			{
				SendHaptics(lastFFBCmd, buzz, lastThumper);
			}

			/// <summary> Retrieve this device's firmware version. </summary>
			void SendHaptics(Haptics::SG_FFBCmd ffb, Haptics::SG_BuzzCmd buzz, Haptics::ThumperCmd thumper) override;

			//--------------------------------------------------------------------------------------
			// Kinematics

			/// <summary> Calculates a GlovePose based on sensor angles and a glove model. </summary>
			/// <remarks> Use this when you already have gloveAngles collected </remarks>
			static SG_GlovePose CalculateGlovePose(SG_SensorData& sensorData, SG_GloveInfo& gloveModel);


			/// <summary> Calculates a GlovePose based on gloveAngles and a glove model. </summary>
			/// <remarks> Use this when you already have gloveAngles collected </remarks>
			static SG_GlovePose CalculateGlovePose(std::vector< std::vector<Kinematics::Vect3D> > gloveAngles, SG_GloveInfo& gloveModel);


			///<summary> </summary>
			///<remarks> Use this when you already have a GlovePose </remarks>
			static HandPose CalculateHandPose(SG_GlovePose glovePose, Kinematics::BasicHandModel handModel, SG_HandProfile profile);


			//--------------------------------------------------------------------------------------
			// Devicelist Integration

			///<summary> Deserializes a Sense Glove from its CString. Returns a nullptr if unsuccesfull. </summary>
			static std::shared_ptr<SGDevice> Parse(std::string cString);


			/// <summary> Retrieve all Sense Gloves connected to this system. </summary>
			static std::vector<SenseGlove> GetSenseGloves(bool onlyConnected = true);

			/// <summary> Retrieve the first connected Sense Glove there is. </summary>
			static bool GetSenseGlove(SenseGlove& glove);

			/// <summary> Retrieve the first (connected) right- or left handed sense glove. </summary>
			static bool GetSenseGlove(bool rightHanded, SenseGlove& glove);

			//--------------------------------------------------------------------------------------
			// Calibration Methods

			/// <summary> Retrieve calibration values of this glove, as an array of size 5, containing x (roll), y (flexion), z (abduction) values. </summary>
			bool GetCalibrationValues(std::vector<SGCore::Kinematics::Vect3D>& values) override;

			/// <summary> Convert a SenseGlove GlovePose into calibrationValues. </summary>
			static std::vector<SGCore::Kinematics::Vect3D> GetCalibrationValues(SG_GlovePose glovePose);

		
			/// <summary> Apply this glove's calibration range to a handProfile </summary>
			void ResetCalibrationRange() override;


			/// <summary> Apply this glove's calibration range to a handProfile </summary>
			void ApplyCalibration(HandProfile& profile) override;

			/// <summary> Apply this glove's calibration range to a SG_HandProfile </summary>
			void ApplyCalibration(SG_HandProfile& profile);

		};
	}
}