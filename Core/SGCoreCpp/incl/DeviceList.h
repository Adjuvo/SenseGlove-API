// ----------------------------------------------------------------------------------
// Interface for SenseCom, allows the retrieval of Devices and Data, but only as
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <vector>
#include <string>
#include "DeviceTypes.h"
#include "SGDevice.h"

#include <memory> //for shared::ptrs

namespace SGCore
{
	/// <summary> Interface for SenseCom, allows the retrieval of Devices and Data. </summary>
	class DeviceList
	{

	private:

		//--------------------------------------------------------------------------------------
		// Properties

		///<summary> A list of all devices that have been detected via the SenseCom executable. </summary>
		static std::vector< std::shared_ptr<SGDevice> > devices; //TODO: Make this a singleton?


		static bool disposed;

		//--------------------------------------------------------------------------------------
		// Internal Methods

		/// <summary> Check the IPC for new data, and add any new devices to our list. Returns -1 if SenseCom is not running. </summary>
		/// <remarks> Should be called whenever any GetDevices functions is called. </remarks>
		static int CheckDevices();

		/// <summary> Factory function to deserialize an SGDevice out of a DeviceList string. </summary>
		/// <remarks> Intended use: Returns true if serialization is succesfull, false if errors occured. In that case output = null. </remarks>
		static bool Deserialize(std::string& serialized, std::shared_ptr<SGDevice>& output);





	public:

		//--------------------------------------------------------------------------------------
		// Accessors

		///<summary> Retrieve the number of devices that have been detected by the SenseCom executable. </summary>
		static SGCORE_API int ActiveDevices();

		/// <summary> Returns true if the SenseCom program is running. </summary>
		static SGCORE_API bool SenseComRunning();

		/// <summary> Clear the device list, and block any further attempt to add to it untill ReInitialize is called. </summary>
		/// <remarks> Useful if your IDE has troubles unloading dlls (cough, Unity, Cough). </remarks>
		/// <returns></returns>
		static SGCORE_API void Dispose();

		/// <summary> When you've accidentaly disposed of the list before you meant to. </summary>
		/// <returns></returns>
		static SGCORE_API void ReInitialize();

		//--------------------------------------------------------------------------------------
		// Device Access Methods

		/// <summary> Retrieve all Sense Glove Devices connected to this system. </summary>
		static SGCORE_API std::vector< std::shared_ptr<SGDevice> > GetDevices();

		/// <summary> Retrieve a list of SGDevices of a specific class. </summary>
		template <class T> static std::vector< std::shared_ptr<T> > GetDevices()
		{
			int currentDevices = DeviceList::ActiveDevices();
			const std::type_info& tType = typeid(T);
			std::vector< std::shared_ptr<T> > res = { }; //empty vector
			for (int i = 0; i < currentDevices; i++)
			{
				if (typeid(*devices[i]) == tType)
					res.push_back(std::dynamic_pointer_cast<T>(devices[i]));
			}
			return res;
		}


		//--------------------------------------------------------------------------------------
		// Device Communication Methods

		///<summary> Retrieve the latest (raw) sensor data from a specific device in our list. </summary>
		static SGCORE_API bool GetSensorDataString(int ipcIndex, std::string& ipcAddress, std::string& output);

		///<summary> Send a (raw) command to a specific device in the list. </summary>
		static SGCORE_API bool SendHaptics(int ipcIndex, std::string& ipcAddress, std::string& commands);

		static std::string GetDeviceStringAt(int ipcIndex, std::string& ipcAddress, int index);




        /// <summary> Retrieve Device Address </summary>
		static std::string GetAddress(int ipcIndex, std::string& ipcAddress);


        /// <summary> Retieve this device's connectionType. </summary>
		static SGDevice::ConnectionType GetConnectionType(int ipcIndex, std::string& ipcAddress);


        /// <summary> Returns true if the device at  this connection side is properly connected. </summary>
		static bool IsConnected(int ipcIndex, std::string& ipcAddress);


        /// <summary> Retrieve the device's Packets per Second Variable </summary>
        /// <returns></returns>
		static int PacketsPerSecondReceived(int ipcIndex, std::string& ipcAddress);


        /// <summary> Retrieve the device's Packets per Second sent Variable </summary>
        /// <returns></returns>
		static int PacketsPerSecondSent(int ipcIndex, std::string& ipcAddress);

	};

}