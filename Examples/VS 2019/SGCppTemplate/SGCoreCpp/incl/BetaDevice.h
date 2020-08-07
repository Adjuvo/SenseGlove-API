// ----------------------------------------------------------------------------------
// Represents a Sense Glove Device that has no specific class within the API.
// Used to test different iterations of the same product before integrating it into the Core API.
// Allows access to raw sensor values and commands of such a device.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include "SGDevice.h"
#include <string>
#include <memory>

namespace SGCore
{
	/// <summary> A Device that adheres to the SenseGlove communications protocol, but which has no implementation in this API. </summary>
	class SGCORE_API BetaDevice : public SGDevice
	{

	protected:

		//--------------------------------------------------------------------------------------
		// Properties

		/// <summary> The constants string retrieved when the device is first connected. </summary>
		std::string cString;

		/// <summary> The deviceID of this Beta Device. </summary>
		std::string deviceID;

		/// <summary> The hardware (sub) version of this Beta Device. </summary>
		std::string hwVersion;

		/// <summary> The firmware version of the Beta Device. </summary>
		int fwVersionMain, fwVersionSub;

	public:

		//--------------------------------------------------------------------------------------
		// Construction

		/// <summary> Basic Class Constructor. </summary>
		BetaDevice();
		/// <summary> Basic Class Destructor. </summary>
		~BetaDevice() { }

		/// <summary> Creates a new instance of a Beta Device. </summary>
		BetaDevice(std::string constants, std::string id, std::string hwVer, int fwMain, int fwSub);


		//--------------------------------------------------------------------------------------
		// Accessors

		///<summary> Get the DeviceType enumerator of this SenseGlove, used in DeviceList enumeration. </summary>
		DeviceType GetDeviceType() override { return DeviceType::BETADEVICE; }

		/// <summary> Get the unique identifier of this device. </summary>
		std::string GetDeviceID() override { return deviceID; }

		/// <summary> Retrieve this device's hardware version. </summary>
		std::string GetHardwareVersion() override { return hwVersion; }

		/// <summary> Retireve this device's firmware version. </summary>
		int GetFirmwareVersion() override { return fwVersionMain; }

		/// <summary> Retireve this device's sub-firmware version. </summary>
		int GetSubFirmwareVersion() override { return fwVersionSub; }

		//--------------------------------------------------------------------------------------
		// Class Methods

		/// <summary> Retrieve the Constants string for additional processing. </summary>
		std::string GetConstantsString();

		/// <summary> Retrieve a raw sensor string from this Beta Device. </summary>
		std::string GetSensorData();

		/// <summary> Retireve a the last command retrieved from this Beta Device. </summary>
		std::string GetLastCmd();

		/// <summary> Send a raw string command to this device. </summary>
		bool SendHaptics(std::string command);

		///<summary> Create a string representation of this device for reporting purposes. </summary>
		std::string ToString() override { return "Beta Device " + GetDeviceID(); };


		//--------------------------------------------------------------------------------------
		// Serialization

		///<summary> Deserialize a beta device from its basic cstring. Returns nullptr is unsuccesfull. </summary>
		static std::shared_ptr<SGDevice> Parse(std::string cstring);

	};
}
