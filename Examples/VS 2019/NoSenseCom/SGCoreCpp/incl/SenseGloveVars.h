// ----------------------------------------------------------------------------------
// Contains enumerators and classes to aid in Sense Glove Deserialization.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include <string>
#include <vector>
#include "Vect3D.h"
#include "Quat.h"

namespace SGCore
{
	namespace Parsing
	{
		//--------------------------------------------------------------------------------
		// Data Formats

		///<summary> Sense Glove C string Variables, enumerated for our convinience. </summary>
		enum SG_CVar
		{
			ConstOpen = 0,
			ID,
			gloveVersion,
			FirmwareVersion,
			LeftRight,
			Functions,
			GlovePos,
			GloveLengths, //all gloves have functionality up to this point.
			NumberOfSensors,
			IMUCorrection,
			/// <summary> Utility value used in iteration / checking lengths </summary>
			AllC
		};

		///<summary> Sense Glove sensor string Variables, enumerated for our convinience. </summary>
		enum SG_SVar
		{
			RTError = 0,    //real-time error
			FingerSensors,
			IMUData,
			WDError,        //watchdog-error
			SemanfError,    //semaphore-error
			/// <summary> Utility value used in iteration / checking lengths </summary>
			AllS
		};
	}

	namespace SG //separate sub-namespace for SenseGlove(s)
	{
		//--------------------------------------------------------------------------------
		// Glove Data and Constants


		/// <summary> "Database" class containing Sense Glove internal variables </summary>
		class SGCORE_API SenseGloveVars
		{
		public:

			///<summary> Retrieve a basic Cstring for a Sense Glove of a specific Hardware Version. Used for debugging / unit tests. </summary>
			///<returns> Returns an empty string when an invalid glove version is requested. </returns>
			static std::string GetStdCString(std::string hwVersion, float fwVersion, bool rightHand);

			/// <summary> Retrieve an example sensor string of a Sense Glove with a particular hardware- and firmware version. </summary>
			static std::string GetSensorString(std::string hwVersion, float fwVersion);


			/// <summary> Retrieve the starting positions of a particular Sense Glove. </summary>
			static std::vector< Kinematics::Vect3D > GetStartPositions(std::string hwVersion, bool isRight);

			/// <summary> Retrieve the starting rotations of a particular Sense Glove. </summary>
			static std::vector< Kinematics::Quat > GetStartRotations(std::string hwVersion, bool isRight);

			/// <summary> Retrieve the glove finger lengths of a particular Sense Glove. </summary>
			static std::vector< std::vector< Kinematics::Vect3D > > GetGloveLengths(std::string hwVersion);

		};
	}
}