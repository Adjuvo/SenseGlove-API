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
		/// <returns> 
		/// -3 : An Unexpected error occured. Please try again.
		/// -2 : Device Scanning is already running within a different program.
		/// -1 : Device Scanning already being initialized (function called twice in short succession).
		///  0 : Device Scanning is already running in within this program.
		///  1 : Succesfully started up DeviceScanning from the current program.
		/// </returns>
		/// <remarks> If the Init function returns a value > 0 it's a success, and your program should also dispose of it at the end of its life. </remarks>
		SGCONNECT_API int Init();

		///<summary> Dispose of unmanaged resources and finalize Sense Glove devices. </summary>
		/// <returns> 
		/// -3 : An Unexpected error occured. Please try again.
		/// -2 : Not allowed to dispose of Device Scanning because this is not the program which started it.
		/// -1 : Device Scanning is currently being disposed off. This takes a second or two. (function called twice in short succession).
		///  0 : There is no deviceScanner running from any program, so disposing is skipped.
		///  1 : Succesfully disposed of DeviceScanner resources.
		/// </returns>
		/// <remarks> If the Dispose function returns 1, the resources were neatly disposed of. Only a value of -3 is cause for concern. </remarks>
		SGCONNECT_API int Dispose();


		// ---------------------------------------------------------------------------------------------
		// Util

		///<summary> Clears ScanningActive for debug purposes. </summary>
		SGCONNECT_API void ClearSharedMem();

	    ///<summary> Check which version of SGConnect you are using. </summary>
		SGCONNECT_API int GetLibraryVersion_I(char* output);

		///<summary> Check which version of SGConnect you are using. </summary>
		SGCONNECT_API std::string GetLibraryVersion();

		// ---------------------------------------------------------------------------------------------
		// C# / IPC interface

		///<summary> Count the active devices within the SenseComm shared memory. </summary>
		SGCONNECT_API int ActiveDevices();

		///<summary> Returns true if a Device Scanning instance is already running. </summary>
		SGCONNECT_API bool ScanningActive();


		/// <summary> Returns the scanningState of the SGConnect library. Used by ScanningActive. </summary>
		/// <returns>
		/// -3 : Error while checking; something is wrong. -> not sure
		/// -2 : Sharedmemory exists, but it's timed out -> false
		/// -1 : The current process has an instance of DeviceScanner, but it is no longer live... -> false
		///  0 : No scanning whatsoever is active -> false
		///  1 : The current process has an instance of DeviceScanner, and it is live -> true
		///  2 : SharedMemory exists, and it's still up to date -> true
		///</returns>
		SGCONNECT_API int ScanningState();
	}
}
