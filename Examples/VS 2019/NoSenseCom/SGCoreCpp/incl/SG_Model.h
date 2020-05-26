// ----------------------------------------------------------------------------------
// Model of the Sense Glove, created from its hard-coded values.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include "DeviceModel.h"
#include "SGDevice.h"
#include "Vect3D.h"
#include "Quat.h"

#include "SG_SensorData.h"

namespace SGCore
{
	namespace SG
	{
		//--------------------------------------------------------------------------------------
		// Function Enumerators

		///<summary> Functions that a Sense Glove cound have. </summary>
		enum SGCORE_API SG_Functions
		{
			/// <summary> Vibration Motors to send haptic pulses to individual fingers  </summary>
			SG_BuzzMotors = 0,

			/// <summary> Brakes which can inhibit grasping motions to create force feedback. </summary>
			SG_ForceFeedback,

			///<summary> A Thumper Module for global feedback. </summary>
			SG_Thumper,

			/// <summary> Utility value used for enumeration. It can also be used to check if a Sense Glove has all possible functionalities. </summary>
			SG_AllFunctions
		};


		//--------------------------------------------------------------------------------------
		// SG_Model Class

		/// <summary> Contains device information about a Sense Glove. </summary>
		class SGCORE_API SG_Model : public DeviceModel
		{

		protected:

			//--------------------------------------------------------------------------------------
			// Properties

			///<summary> Check if this Sense Glove belongs to a left or right hand. </summary>
			bool isRight;

			/// <summary> The number of Sensors in this SenseGlove. </summary>
			int numberOfSensors;

			///<summary> The IMU correction of this Sense Glove. </summary>
			Kinematics::Quat imuCorrection;

			/// <summary> The starting positions of each Sense Glove finger, relative to the glove origin </summary>
			std::vector<Kinematics::Vect3D> startPositions;

			/// <summary> The starting rotations of each Sense Glove finger, relative to the glove origin </summary>
			std::vector<Kinematics::Quat> startRotations;

			/// <summary> The lengths of each Sense Glove finger section, in mm. </summary>
			std::vector<std::vector<Kinematics::Vect3D>> gloveLengths;

			/// <summary> Whether this device has a specific function (T/F). </summary>
			std::vector<bool> functions;

			/// <summary> Parse a section of constants into a set of glove lengths. </summary>
			static std::vector<std::vector<Kinematics::Vect3D>> ParseLengthString(std::string rawLengths);

			/// <summary> Parse a section of constants into a set starting positions and -rotations. </summary>
			static void ParseStartValues(std::string rawValues, std::vector<Kinematics::Vect3D>& startPos,
				std::vector<Kinematics::Quat>& startRot);


		public:

			//--------------------------------------------------------------------------------------
			// Construction

			/// <summary> Default Constructor </summary>
			SG_Model();

			/// <summary> Create a new Sense Glove device model </summary>
			SG_Model(std::string ID, std::string hwVer, int fwVerMain, int fwVerSub, bool rightHand, int noSensors,
				Kinematics::Quat imuCorr, std::vector<Kinematics::Vect3D> startPos, std::vector<Kinematics::Quat> startRot,
				std::vector<std::vector<Kinematics::Vect3D>> lengths, std::vector<bool> functionality);

			/// <summary> Default Destructor </summary>
			~SG_Model();


			//--------------------------------------------------------------------------------------
			// Accessors

			///<summary> Check if this Sense Glove belongs to a left or right hand. </summary>
			bool IsRight() { return isRight; }

			/// <summary> Retrieve the number of Sensors in this SenseGlove. </summary>
			int NumberOfSensors() { return numberOfSensors; }

			///<summary> Retrieve the IMU correction of this Sense Glove. </summary>
			Kinematics::Quat GetIMUCorrection() { return imuCorrection; }

			/// <summary> The starting positions of each Sense Glove finger, relative to the glove origin </summary>
			std::vector<Kinematics::Vect3D> GetStartPositions();

			/// <summary> The starting position of one Sense Glove finger, relative to the glove origin </summary>
			Kinematics::Vect3D GetStartPosition(SGCore::Finger finger);

			/// <summary> The starting rotations of each Sense Glove finger, relative to the glove origin </summary>
			std::vector<Kinematics::Quat> GetStartRotations();
			/// <summary> The starting rotation of one Sense Glove finger, relative to the glove origin </summary>
			Kinematics::Quat GetStartRotation(SGCore::Finger finger);

			/// <summary> The lengths of each Sense Glove finger section, in mm. </summary>
			std::vector<std::vector<Kinematics::Vect3D>> GetGloveLengths();

			/// <summary> The lengths of one Sense Glove finger's sections, in mm. </summary>
			std::vector<Kinematics::Vect3D> GetGloveLengths(SGCore::Finger finger);


			//--------------------------------------------------------------------------------------
			// Class Methods

			///<summary> Place incoming sensor data into the right format, according to this glove's model. </summary>
			std::vector<std::vector<Kinematics::Vect3D>> ToGloveAngles(std::vector< std::vector< float > > sensorAngles);

			/// <summary> Place incoming sensor data into the right xyz format, according to this glove's model. </summary>
			bool HasFunction(SG_Functions function);

			/// <summary> Create a string representation for logging. If shortNotation is false, all values are reported. </summary>
			std::string ToString(bool shortNotation);

			/// <summary> Create a string representation for fast logging. </summary>
			std::string ToString() { return ToString(true); };

			/// <summary> Returns true if this SG_Model has the same values as another </summary>
			bool Equals(SG_Model other, bool geometryOnly = false);

			//---------------------------------------------------------------------------------------------------------------------
			// Serialization

			///<summary> Serialize this HandProfile into a string representation </summary>
			std::string Serialize();

			///<summary> Deserialize a HandProfile back into useable values. </summary>
			static SG_Model Deserialize(std::string serializedString);

			///<summary> Create an instance of the SGModel from its string representation. </summary>
			static bool Parse(std::string cString, SG_Model& model, bool updateOldModels = true);

		};
	}
}