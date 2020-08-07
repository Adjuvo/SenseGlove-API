// ----------------------------------------------------------------------------------
// Contains global defines, such as the import / export API.
// Is also the main interface for DLLImport for C++ / C#
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

// SerialType determines how we work with Serial Communications
// 0 - Klemen Method -> Ready with callback which cannot distinguish between commands
// 1 - Max Method -> ReadThread that can distinguish between commands and sensor data
// 2 - Hybrid Method -> Readthread with a callback for safety
#define SERIALMODE 2 //at the moment, Max Method seems to be the most stable


#ifdef _WIN32	//Windows requires us to define __declspec(dllexport), while MacOs and Linux do not.
	#define WIN32_LEAN_AND_MEAN					// Exclude rarely-used stuff from Windows headers
	//#define _WIN32_WINNT 0x0501				//Some weird Boost targets for windows 7 ?

	#ifdef SGCONNECT_EXPORTS 	//SGCONNECT_EXPORTS should be added in the preprocessor definition when building a DLL.
		#ifndef SGCONNECT_API
			#define SGCONNECT_API __declspec(dllexport)
		#endif
	#else
		#ifndef SGCONNECT_API
			#define SGCONNECT_API __declspec(dllimport)
		#endif
	#endif
#else
	#ifndef SGCONNECT_API
		#define SGCONNECT_API 	//Guards against redeclaring SENSEGLOVE_API
	#endif
#endif

//we use std::string a lot, and every class has SGConnect added to it. Including both does not seem to impact compiling.
#include <string>	//Required for Windows
#include <string.h> //required for Mac anc Linux

extern "C"
{
	namespace SGConnect
	{
		// ---------------------------------------------------------------------------------------------
		// Resource Management

		///<summary> Begin Scanning for Sense Glove Devices and set up communications with them. </summary>
		SGCONNECT_API int Init();

		///<summary> Dispose of unmanaged resources and finalize Sense Glove devices. </summary>
		SGCONNECT_API int Dispose();

		///<summary> Clears ScanningActive for debug purposes. </summary>
		SGCONNECT_API void ClearSharedMem();


		
		// ---------------------------------------------------------------------------------------------
		// C# / IPC interface

		///<summary> Count the active devices within the SenseComm shared memory. </summary>
		SGCONNECT_API int ActiveDevices();

		///<summary> Returns true if a Device Scanning instance is already running. </summary>
		SGCONNECT_API bool ScanningActive();

	}
}
