// ----------------------------------------------------------------------------------
// Utility Class used to write and read to/from IPC
// a.k.a. The (only) one with access to Boost::Interprocess
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <string>
#include <string.h>

namespace SGCore
{

	/// <summary> Utility Class used to write and read to/from IPC </summary>
	class SharedMem
	{

	public:

		// Defines

		///<summary> Shared Memory block containing number of devices and deviceInfo from each device </summary>
		static const std::string devices;
		///<summary> Shared Memory block containing haptic commands from each device </summary>
		static const std::string haptics;
		///<summary>  Shared Memory block containing sensor data from each device </summary>
		static const std::string data;
		///<summary> Shared Memory block containing commands to be sent to the devices </summary>
		static const std::string inCommands;
		///<summary> Shared Memory block containing commands/reposnes from the devices </summary>
		static const std::string outCommands;

		///<summary> Address in devices where the number of devices is stored. </summary>
		static const std::string numDevices;

		///<summary> Address in devices where the scanner's processing id is stored. </summary>
		static const std::string scanActive;

		///<summary> Address in devices where the scanner's processing id is stored. </summary>
		static const long maxTimeTick;

		///<summary> Delimiter to split data in Shared Memory </summary>
		static const char listDelim;

		///<summary> Standard size of Shared Memory. It works with this but could probably use a lower value. </summary>
		static const unsigned int stdSize;

		// IPC Functions

		///<summary> Write a string to Shared Memory at block-addess. Returns true if succesful. </summary>
		static bool WriteTo(std::string block, std::string address, std::string value, unsigned int size = stdSize);

		///<summary> Retrieve value from Shared Memory at block-addess. Returns true if succesful. </summary>
		static bool ReadFrom(std::string block, std::string address, std::string& output);

		///<summary> Dispose of a shared memory block so it no longer takes up space on the PC. Returns true if succesful. </summary>
		static bool Dispose(std::string block);

		/// <summary> Access the time since the last update from SGConnect </summary>
		static bool ScanningActive();


	};
}