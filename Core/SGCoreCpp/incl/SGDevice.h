// ----------------------------------------------------------------------------------
// Represents a Device built by the Sense Glove company that is compatible with 
// our Communications Protocol. All such devices derive from this abstract class.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include <string>
#include "DeviceTypes.h"

namespace SGCore
{
	/// <summary> A Sense Glove device that can send / recieve data via the SenseCom program. </summary>
	class SGCORE_API SGDevice
	{

	protected:

		//--------------------------------------------------------------------------------------
		// Properties

		/// <summary> The index of this device inside the SenseCom program. Used to access shared memory. </summary>
		int deviceIndex = -1;

		/// <summary> Address of this Device for inter-process communications. </summary>
		std::string ipcAddress;

	public:

		//--------------------------------------------------------------------------------------
		// Enum

		/// <summary> Connection type of this device, as detected by the SGConnect library. </summary>
		enum ConnectionType
		{
			/// <summary> Could not determine which connection type this SGDevice is using, most likely because it is disconnected. </summary>
			Unknown = -1,
			/// <summary> USB Serial communication. </summary>
			Serial,
			/// <summary> A bluetooth connection that creates up to two Serial Ports. </summary>
			BluetoothSerial,
			/// <summary> Bluetooth Connection Via Android/Java SDK </summary>
			BluetoothAndroid
		};


		//--------------------------------------------------------------------------------------
		// Construction

		/// <summary> Basic Constructor. </summary>
		SGDevice();

		/// <summary> Basic Destructor. </summary>
		~SGDevice();


		//--------------------------------------------------------------------------------------
		// Device Accessors

		///<summary> Check which DeviceType this class belongs to </summary>
		virtual DeviceType GetDeviceType();

		/// <summary> Retrieve this device's unique identifier. </summary>
		virtual std::string GetDeviceID() = 0;

		/// <summary> Retrieve this device's hardware version. </summary>
		virtual std::string GetHardwareVersion() = 0;

		/// <summary> Retrieve this device's main firmware version. v4.12 returns 4. </summary>
		virtual int GetFirmwareVersion() = 0;

		/// <summary> Retrieve this device's sub firmware version. v4.12 returns 12. </summary>
		virtual int GetSubFirmwareVersion() { return 0; }

		virtual std::string GetFirmwareString() { return GetFirmwareVersion() + "." + GetSubFirmwareVersion(); }

		//--------------------------------------------------------------------------------------
		// I/O Accessors

		///<summary> Retrieve this Device's Serial/Bluetooth address. </summary>
		std::string GetAddress();

		/// <summary> Check if this device is currently connected to the system. </summary>
		bool IsConnected();

		/// <summary> Retrieve the connection type of this Sense Glove. </summary>
		ConnectionType GetConnectionType();

		/// <summary> Retrieve the device's Packets per Second Variable </summary>
		int PacketsPerSecondReceived();

		/// <summary> Retrieve the device's Packets per Second Variable </summary>
		int PacketsPerSecondSent();

		/// <summary> Retrieve the index of this device within SenseCom. </summary>
		int GetDeviceIndex();

		/// <summary> Change this device's index within the SenseCom. Warning: Can cause errors. </summary>
		void SetDeviceIndex(int newIndex);


		/// <summary> Returns true if this device is connected over a connection other than usb cable. </summary>
		/// <returns></returns>
		virtual bool IsWireless();

		/// <summary> Returns true if this device operates on a battery </summary>
		/// <returns></returns>
		virtual bool HasBattery();

		/// <summary> Returns true if this device is currently charging </summary>
		/// <returns></returns>
		virtual bool IsCharging();

		/// <summary> Returns the device's battery level, as a value between 0 (empty) and 1 (full). </summary>
		/// <param name="battLvl"></param>
		/// <returns></returns>
		virtual bool GetBatteryLevel(float& battLvl);


		//--------------------------------------------------------------------------------------
		// Class Methods

		///<summary> Get a string representation of this SGDevice, used for debugging. </summary>
		virtual std::string ToString();


		/// <summary> Parse a main and sub firmware version from its raw (v4.12) notation </summary>
		static void ParseFirmware(std::string rawFW, int& mainVer, int& subVer);

		static std::string ToString(DeviceType device);
	};
}
