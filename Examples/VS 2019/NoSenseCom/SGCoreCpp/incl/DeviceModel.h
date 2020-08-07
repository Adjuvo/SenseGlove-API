// ----------------------------------------------------------------------------------
// Base class for Device Models containing the minimum amount of data gathered 
// through Communications Protocol. Used for shared functionality.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <string>
#include <vector>

namespace SGCore
{
	/// <summary> Base class containing the minimum amount of data for device models. </summary>
	class SGCORE_API DeviceModel
	{

	protected:

		//--------------------------------------------------------------------------------------
		// Properties

		/// <summary> Unique identifier of this device. </summary>
		std::string deviceID;

		/// <summary> Hardware (sub) version of this Sense Glove Device. </summary>
		std::string hardwareVer;

		/// <summary> Firmware version running on the device's MicroController. </summary>
		int firmwareVer;

		/// <summary> Sub-Firmware version running on the device's MicroController. </summary>
		int subFirmwareVer;

	public:

		//--------------------------------------------------------------------------------------
		// Construction

		DeviceModel(); //empty constructor to be used by child classes.
		DeviceModel(std::string id, std::string hwVer, int fwVer, int subFWver);

		~DeviceModel() { }

		//--------------------------------------------------------------------------------------
		// Accessors

		/// <summary> Retrieve the Unique identifier of this device. </summary>
		std::string GetDeviceID() { return deviceID; }

		/// <summary> Retrieve the Hardware (sub) version of this Sense Glove Device. </summary>
		std::string GetHardwareVersion() { return hardwareVer; }

		/// <summary> Retrieve the Firmware version running on the device's MicroController. </summary>
		int GetFirmwareVersion() { return firmwareVer; }

		int GetSubFirmwareVersion() { return subFirmwareVer; }


		static void ParseFirmware(std::string& rawFW, int& mainVer, int& subVer);

		///<summary> Parse a 32-bit integer value into a set of booleans (010010011) that indicate which (optional) functions this device has.  </summary>
		static std::vector<bool> ParseFunctions(int value, int size);


	};

}
