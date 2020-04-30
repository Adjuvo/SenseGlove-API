// ----------------------------------------------------------------------------------
// An interface for the Sense Glove exoskeleton glove.
// Contains methods for Kinematics, Haptics and Serialization.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include "SGDevice.h"
#include "SG_Model.h"
#include "SG_SensorData.h"
#include "SG_GlovePose.h"
#include "SG_HandProfile.h"
#include "HandPose.h"

#include "SG_FFBCmd.h"
#include "SG_BuzzCmd.h"
#include "SG_ThumperCmd.h"

#include <memory>

namespace SGCore
{
	namespace SG
	{
		//--------------------------------------------------------------------------------------
		// Solver

		///<summary> How this Sense Glove converts sensor data into a HandPose. </summary>
		enum SGCORE_API SG_Solver
		{
			/// <summary> Hand angles are interpolated based on the total flexion / abduction of the exoskeleton </summary>
			Interpolation = 0 //default.
		};

		//--------------------------------------------------------------------------------------
		// Sense Glove Interface

		/// <summary> Interface for the Sense Glove; and exoskeleton Force-Feedback glove. </summary>
		class SGCORE_API SenseGlove : public SGDevice
		{

		protected:

			//--------------------------------------------------------------------------------------
			// Properties

			/// <summary> Contains all data regarding this Sense Glove </summary>
			/// <remarks> 
			/// We're not using a generic DeviceModel as that would require casting
			/// its DeviceModel to an SGModel each frame. Adding this interface here is faster
			/// </remarks>
			SG_Model gloveModel;

			/// <summary> The last Force-Feedback command sent by this Sense Glove. </summary>
			Haptics::SG_FFBCmd lastFFBCmd = Haptics::SG_FFBCmd::off;

			/// <summary> The last Force-Feedback command sent by this Sense Glove. </summary>
			Haptics::SG_BuzzCmd lastBuzzCmd = Haptics::SG_BuzzCmd::off;

			/// <summary> Byte indicating a new Sense Glove haptic command. </summary>
			const static char hapticsByte;
			/// <summary> Byte indicating a new Thumper command. </summary>
			const static char thumperByte;


			//--------------------------------------------------------------------------------------
			// Internal Methods

			/// <summary> Convert a Force-Feedback command to a string which can be sent to this particular Sense Glove device. </summary>
			/// <remarks> Implemented here because the conversion may depend on firmware/hardware version. </remarks>
			std::string ToBytes(Haptics::SG_FingerCmd cmd);


		public:

			//--------------------------------------------------------------------------------------
			// Construction

			///<summary> Basic Constructor </summary>
			SenseGlove();

			///<summary> Basic Destructor </summary>
			~SenseGlove();

			/// <summary> Create a new instance of a Sense Glove. </summary>
			SenseGlove(SG_Model myModel);

			//--------------------------------------------------------------------------------------
			// SGDevice Methods

			 ///<summary> Get the DeviceType enumerator of this SenseGlove, used in DeviceList enumeration. </summary>
			DeviceType GetDeviceType() override { return DeviceType::SENSEGLOVE; }

			/// <summary> Retrieve this Sense Glove's unique identifier. </summary>
			std::string GetDeviceID() override { return gloveModel.GetDeviceID(); };

			/// <summary> Retrieve this glove's hardware (sub) version.  </summary>
			std::string GetHardwareVersion() override { return gloveModel.GetHardwareVersion(); };

			/// <summary> Retrieve this device's firmware version. </summary>
			int GetFirmwareVersion() override { return gloveModel.GetFirmwareVersion(); };

			/// <summary> Retrieve this device's sub-firmware version. </summary>
			int GetSubFirmwareVersion() override { return gloveModel.GetSubFirmwareVersion(); }

			//--------------------------------------------------------------------------------------
			// Class Methods

			/// <summary> Create a string representation of this device for reporting purposes. </summary>
			std::string ToString() override { return "Sense Glove " + GetDeviceID(); };

			/// <summary> Check if this Sense Glove is right handed. </summary>
			/// <remarks> While the variable is stored in SG_GloveModel, added direct access here since its frequently used. </remarks>
			bool IsRight() { return gloveModel.IsRight(); } //direct access since its frequently used.

			/// <summary> Retrieve this glove's hardware model, which contains its hardware data. </summary>
			SG_Model GetGloveModel() { return gloveModel; }


			/// <summary> Get the latest Sensor Data from this Sense Glove </summary>
			bool GetSensorData(SG_SensorData& sensorData);

			/// <summary> Get the pose of this Sense Glove's hardware, based on its latest Sensor Data </summary>
			bool GetGlovePose(SG_GlovePose& glovePose);

			/// <summary> Get the pose of this Sense Glove's hardware based on a set of Sensor Data </summary>
			bool GetGlovePose(SG::SG_SensorData sData, SG_GlovePose& glovePose);

			/// <summary> Retrieve a new hand pose using this glove's data, based on (calibrated) user data. </summary>
			bool GetHandPose(SG_HandProfile profile, SG_Solver solver, HandPose& handPose);


			//--------------------------------------------------------------------------------------
			// Feedback Methods

			/// <summary> Set the level(s) of Force and Vibrotactile feedback, with an optional thumper command </summary>
			bool SendHaptics(Haptics::SG_FFBCmd ffbCmd, Haptics::SG_BuzzCmd buzzCmd,
				Haptics::SG_ThumperCmd thumperCmd = Haptics::SG_ThumperCmd::None);

			/// <summary> Send a Force-Feedback command to the Sense Glove. </summary>
			bool SendHaptics(Haptics::SG_FFBCmd ffbCmd);

			/// <summary> Send a vibration command to the Sense Glove. </summary>
			bool SendHaptics(Haptics::SG_BuzzCmd buzzCmd);

			/// <summary> Send a thumper command. </summary>
			bool SendHaptics(Haptics::SG_ThumperCmd thumperCmd);

			/// <summary> Stop all haptic feedback on this device. </summary>
			bool StopFeedback();

			//--------------------------------------------------------------------------------------
			// Kinematics

			/// <summary> Calculates a GlovePose based on sensor angles and a glove model. </summary>
			/// <remarks> Use this when you already have gloveAngles collected </remarks>
			static SG_GlovePose CalculateGlovePose(SG_SensorData& sensorData, SG_Model& gloveModel);


			/// <summary> Calculates a GlovePose based on gloveAngles and a glove model. </summary>
			/// <remarks> Use this when you already have gloveAngles collected </remarks>
			static SG_GlovePose CalculateGlovePose(std::vector< std::vector<Kinematics::Vect3D> > gloveAngles, SG_Model& gloveModel);


			///<summary> </summary>
			///<remarks> Use this when you already have a GlovePose </remarks>
			static HandPose CalculateHandPose(SG_GlovePose glovePose, SG_HandProfile profile, SG_Solver solver);


			//--------------------------------------------------------------------------------------
			// Devicelist Integration

			///<summary> Deserializes a Sense Glove from its CString. Returns a nullptr if unsuccesfull. </summary>
			static std::shared_ptr<SGDevice> Deserialize(std::string cString);



			/// <summary> Retrieve all connected Sense Gloves. </summary>
			static std::vector<SenseGlove> GetSenseGloves();

			/// <summary> Retrieve the first connected Sense Glove there is. </summary>
			static bool GetSenseGlove(SenseGlove& glove);

			/// <summary> Retrieve the first (connected) right- or left handed sense glove. </summary>
			static bool GetSenseGlove(bool rightHanded, SenseGlove& glove);

		};
	}
}