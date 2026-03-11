/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2026 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Contains global defines, such as the import / export API.
 * Is also the main interface for DLLImport for C++ / C#.
 */


#pragma once

/**
 * Defines a C++ like static_assert.
 */
#if !__cplusplus
#include <assert.h>
#endif  /* !__cplusplus */

/**
 * Contains __bool_true_false_are_defined macro that can be used in order to
 * check whether boolean type is supported by the compiler or not.
 */
#if !__cplusplus
#include <stdbool.h>
#endif  /* !__cplusplus */

/**
 * Check at compile time whether the C compiler has support for bool, true,
 * and false macros.
 */
#if !__cplusplus
static_assert(__bool_true_false_are_defined, "Error: bool, true, and false are not defined!");
#endif  /* !__cplusplus */

#if __cplusplus
#include <string>
#endif  /* __cplusplus */

#include <SenseGlove/Common/Platform.hpp>

/*******************************************************************************
* Non-exported functions
*******************************************************************************/

#if __cplusplus

namespace SGConnect
{
    // ---------------------------------------------------------------------------------------------
    // Resource Management

    /// <summary> Begin Scanning for Sense Glove Devices and set up communications with them. </summary>
    /// <returns>
    /// -103 : Android JNI-specific Error: Invalid Java method ID!
    /// -102 : Android JNI-specific Error: Invalid Java class!
    /// -101 : Android JNI-specific Error: Invalid Java environment!
    /// -100 : Android JNI-specific Error: Generic Error! Note: you should never see this!
    /// -3 : An Unexpected error occurred. Please try again.
    /// -2 : Device Scanning is already running within a different program.
    /// -1 : Device Scanning already being initialized (function called twice in short succession).
    ///  0 : Device Scanning is already running within this program.
    ///  1 : Successfully started up DeviceScanning from the current program.
    /// </returns>
    /// <remarks> If the Init function returns a value > 0 it's a success, and your program should also dispose of it
    /// at the end of its life. </remarks>
    SGCONNECT_API int32_t Init();

    /// <summary> Dispose of unmanaged resources and finalize Sense Glove devices. </summary>
    /// <returns>
    /// -103 : Android JNI-specific Error: Invalid Java method ID!
    /// -102 : Android JNI-specific Error: Invalid Java class!
    /// -101 : Android JNI-specific Error: Invalid Java environment!
    /// -100 : Android JNI-specific Error: Generic Error! Note: you should never see this!
    /// -3 : An Unexpected error occurred. Please try again.
    /// -2 : Not allowed to dispose of Device Scanning because this is not the program which started it.
    /// -1 : Device Scanning is currently being disposed off. This takes a second or two. (function called twice in
    /// short succession).
    ///  0 : There is no deviceScanner running from any program, so disposing is skipped.
    ///  1 : Successfully disposed of DeviceScanner resources.
    /// </returns>
    /// <remarks> If the Dispose function returns 1, the resources were neatly disposed of. Only a value of -3 is cause
    /// for concern. </remarks>
    SGCONNECT_API int32_t Dispose();

    // ---------------------------------------------------------------------------------------------
    // Util

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve all ports that might be Sense Gloves, that can be safely connected to. </summary>
    SGCONNECT_API int32_t GetPorts(bool bWithBluetooth, char* out_ports);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve all Serial Ports, their PID/VIDs and Description. Used to debug ports.  </summary>
    SGCONNECT_API int32_t GetPortInfo(bool bWithBluetooth, char* out_portInfo);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve all available connections, their PID/VIDs and Description.  </summary>
    SGCONNECT_API int32_t GetSGConnectionInfo(bool bWithBluetooth, char* out_connectionInfo);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Clears ScanningActive for debug purposes. </summary>
    SGCONNECT_API void ClearSharedMem();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Copy debug messages from the queue and clears it. </summary>
    SGCONNECT_API int32_t GetDebugMessages(char* out_debugMessages);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Turn debug queue on / off. If turned on, we will begin buffering connection messages. </summary>
    SGCONNECT_API void SetDebugQueue(bool bActive);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

    /// <summary> Check which version of SGConnect you are using. </summary>
    SGCONNECT_API std::size_t GetLibraryVersion_I(char* out_libraryVersion);

    /// <summary> Check which version of SGConnect you are using.
    /// out_libraryVersion is of type std::string, which is troublesome inside an extern "C" due to the fact that
    /// C language cannot fathom std::string. You could call this like this:
    /// std::string version;
    /// GetLibraryVersion(&version);
    /// </summary>
    SGCONNECT_API void GetLibraryVersion(void* out_libraryVersion);

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Get the connectionStates from C# </summary>
    /// <param name="output"></param>
    /// <returns></returns>
    SGCONNECT_API int32_t GetConnectionStates_I(char* out_connectionStates);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve connection state messages </summary>
    /// out_libraryVersion is of type std::string, which is troublesome inside an extern "C" due to the fact that
    /// C language cannot fathom std::string. You could call this like this:
    /// std::string states;
    /// GetConnectionStates(&states);
    /// </summary>
    SGCONNECT_API void GetConnectionStates(void* out_connectionStates);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Releases any Idle connections that have hooked around a device that is turned off. </summary>
    SGCONNECT_API void ReleaseIdleConnections();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

    // ---------------------------------------------------------------------------------------------
    // C# / IPC interface

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Count the active devices within the SenseComm shared memory. </summary>
    SGCONNECT_API int32_t ActiveDevices();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Returns true if a Device Scanning instance is already running. </summary>
    SGCONNECT_API bool ScanningActive();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Returns the scanningState of the SGConnect library. Used by ScanningActive. </summary>
    /// <returns>
    /// -3 : Error while checking; something is wrong. -> not sure
    /// -2 : Shared Memory exists, but it's timed out -> false
    /// -1 : The current process has an instance of DeviceScanner, but it is no longer live... -> false
    ///  0 : No scanning whatsoever is active -> false
    ///  1 : The current process has an instance of DeviceScanner, and it is live -> true
    ///  2 : SharedMemory exists, and it's still up to date -> true
    /// </returns>
    SGCONNECT_API int32_t ScanningState();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Get the raw (unprocessed) device data of the SGDevice at index, as discovered by SenseCom </summary>
    SGCONNECT_API int32_t GetDeviceString(char* deviceAddress, char* out_deviceString);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Get the raw (unprocessed) sensor data of the SGDevice at index, as discovered by SenseCom. </summary>
    SGCONNECT_API int32_t GetSensorString(char* deviceAddress, char* out_sensorString);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Write a haptics string to the shared memory of a particular device. </summary>
    SGCONNECT_API int32_t WriteHaptics(char* deviceAddress, char* haptics);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Get the raw (unprocessed) haptic command of the SGDevice at index, as discovered by SenseCom.
    /// </summary>
    SGCONNECT_API int32_t GetHapticString(char* deviceAddress, char* out_hapticString);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Write a command string to the shared memory of a particular device. </summary>
    SGCONNECT_API int32_t WriteCommandString(char* deviceAddress, char* commands);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve the last received command from the device </summary>
    SGCONNECT_API int32_t GetCommandResponse(char* deviceAddress, char* out_cmdResponse);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

    //-------------------------------------------------------------------------------------------------------------
    // WhiteList for adding custom Devices.

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Add a device to the Whitelist, so it can be connected to as if it was a SenseGlove Device. </summary>
    /// <param name="pidVidContains"></param>
    /// <returns></returns>
    SGCONNECT_API bool AddToSerialWhiteList(char* pidVidContains);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Remove a device to the Whitelist, It will no longer be connected to. </summary>
    /// <param name="pidVidContains"></param>
    /// <returns></returns>
    SGCONNECT_API bool RemoveFromSerialWhiteList(char* pidVidContains);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

    //-------------------------------------------------------------------------------------------------------------
    // Firmware Uploads

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Upload the contents of the file at filePath onto an SGDevice with the specified Index, provided the device can actually update. Calling this wihtout knowing what you are doing can brick your device! </summary>
    /// <param name="deviceIndex"></param>
    /// <param name="filePath"></param>
    /// <param name="chunkSize"></param>
    /// <returns></returns>
    SGCONNECT_API int32_t Nova2OTAFirmwareUpload(int32_t deviceIndex, const char* filePath, const int32_t chunkSize);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Returns 0 .. 100 if a process is running, otherwise returns -1. </summary>
    /// <returns></returns>
    SGCONNECT_API int32_t GetFirmwareProgress();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Returns the latest upload code from the firmware upload thread. </summary>
    /// <returns></returns>
    SGCONNECT_API int32_t GetLastFirmwareResult();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    //HIGHLY specific case where a user updates a Nova 2 from Bluetooth Serial to Bluetooth Low Energy
    //After Fw finishes uploading, we do not wait to reconnect. Instead, we wait for an external process (SenseCom) to tell us to proceed & clean.
    SGCONNECT_API int32_t Nova2OTAFirmwareUpload_BTS_to_BLE(int32_t deviceIndex, const char* filePath, const int32_t chunkSize);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    SGCONNECT_API void CompleteNova2Nova2OTAFirmwareUpload();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

    //-------------------------------------------------------------------------------------------------------------
    // BLE Functionality

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> If set to true (Default = true) the SGConnect Library will look for and connect with Bluetooth Serial Devices. If set to false, we will not be checking any BTSerial devices.
    /// Intended use is to set this variable before calling INIT(), and not calling it while anything is running. </summary>
    /// <returns></returns>
    SGCONNECT_API void SetSerialConnectionsEnabled(bool bEnabled);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Informs our back-end to start connecting to and exchanging data with a particular device. </summary>
    SGCONNECT_API int32_t RegisterNova2BLEConnection(const char* localName);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Informs our back-end to stop exchanging data with a particular device. The device itself will still exist, but no data will be exchanged. </summary>
    SGCONNECT_API int32_t UnregisterNova2BLEConnection(const char* localName);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve the currrent (SenseGlove) BLE Devices in the Vicinity. Structured in a JSON String as an array of devices with a Name and Address </summary>
    /// <param name="localName"></param>
    /// <returns></returns>
    SGCONNECT_API int32_t GetNearbyBLEDevices(char* nearbyDevices);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Copies a string placed in Shared Memory into a char* </summary>
    int32_t CopyIpcStr(const std::string& block, const std::string& address, char* out_str);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Copies a string contained in a char* to a block of shared memory </summary>
    int32_t WriteIpcStr(const std::string& block, const std::string& address, const std::string& value);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Copy debug messages from the queue and clears it. </summary>
    int32_t GetDebugMessages_S(std::string& out_debugMessages);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */
}

#endif  /* __cplusplus */

/*******************************************************************************
* End of non-exported functions
*******************************************************************************/

/*******************************************************************************
* Exported functions
*******************************************************************************/

/**
 * If C++ is used, switch to C mode in order to prevent C++'s name mangling of
 * method names.
 */
#if __cplusplus
extern "C" {
#endif  /* __cplusplus */

    // ---------------------------------------------------------------------------------------------
    // Resource Management

    /// <summary> Begin Scanning for Sense Glove Devices and set up communications with them. </summary>
    /// <returns>
    /// -103 : Android JNI-specific Error: Invalid Java method ID!
    /// -102 : Android JNI-specific Error: Invalid Java class!
    /// -101 : Android JNI-specific Error: Invalid Java environment!
    /// -100 : Android JNI-specific Error: Generic Error! Note: you should never see this!
    /// -3 : An Unexpected error occurred. Please try again.
    /// -2 : Device Scanning is already running within a different program.
    /// -1 : Device Scanning already being initialized (function called twice in short succession).
    ///  0 : Device Scanning is already running within this program.
    ///  1 : Successfully started up DeviceScanning from the current program.
    /// </returns>
    /// <remarks> If the Init function returns a value > 0 it's a success, and your program should also dispose of it
    /// at the end of its life. </remarks>
    SGCONNECT_API int32_t SGConnect_Init();

    /// <summary> Dispose of unmanaged resources and finalize Sense Glove devices. </summary>
    /// <returns>
    /// -103 : Android JNI-specific Error: Invalid Java method ID!
    /// -102 : Android JNI-specific Error: Invalid Java class!
    /// -101 : Android JNI-specific Error: Invalid Java environment!
    /// -100 : Android JNI-specific Error: Generic Error! Note: you should never see this!
    /// -3 : An Unexpected error occurred. Please try again.
    /// -2 : Not allowed to dispose of Device Scanning because this is not the program which started it.
    /// -1 : Device Scanning is currently being disposed off. This takes a second or two. (function called twice in
    /// short succession).
    ///  0 : There is no deviceScanner running from any program, so disposing is skipped.
    ///  1 : Successfully disposed of DeviceScanner resources.
    /// </returns>
    /// <remarks> If the Dispose function returns 1, the resources were neatly disposed of. Only a value of -3 is cause
    /// for concern. </remarks>
    SGCONNECT_API int32_t SGConnect_Dispose();

    // ---------------------------------------------------------------------------------------------
    // Util

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve all ports that might be Sense Gloves, that can be safely connected to. </summary>
    SGCONNECT_API int32_t SGConnect_GetPorts(bool bWithBluetooth, char* out_ports);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve all Serial Ports, their PID/VIDs and Description. Used to debug ports.  </summary>
    SGCONNECT_API int32_t SGConnect_GetPortInfo(bool bWithBluetooth, char* out_portInfo);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve all available connections, their PID/VIDs and Description.  </summary>
    SGCONNECT_API int32_t SGConnect_GetSGConnectionInfo(bool bWithBluetooth, char* out_connectionInfo);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Clears ScanningActive for debug purposes. </summary>
    SGCONNECT_API void SGConnect_ClearSharedMem();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Copy debug messages from the queue and clears it. </summary>
    SGCONNECT_API int32_t SGConnect_GetDebugMessages(char* out_debugMessages);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Turn debug queue on / off. If turned on, we will begin buffering connection messages. </summary>
    SGCONNECT_API void SGConnect_SetDebugQueue(bool bActive);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

    /// <summary> Check which version of SGConnect you are using. </summary>
    SGCONNECT_API std::size_t SGConnect_GetLibraryVersion_I(char* out_libraryVersion);

    /// <summary> Check which version of SGConnect you are using.
    /// out_libraryVersion is of type std::string, which is troublesome inside an extern "C" due to the fact that
    /// C language cannot fathom std::string. You could call this like this:
    /// std::string version;
    /// GetLibraryVersion(&version);
    /// </summary>
    SGCONNECT_API void SGConnect_GetLibraryVersion(void* out_libraryVersion);

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Get the connectionStates from C# </summary>
    /// <param name="output"></param>
    /// <returns></returns>
    SGCONNECT_API int32_t SGConnect_GetConnectionStates_I(char* out_connectionStates);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve connection state messages </summary>
    /// out_libraryVersion is of type std::string, which is troublesome inside an extern "C" due to the fact that
    /// C language cannot fathom std::string. You could call this like this:
    /// std::string states;
    /// GetConnectionStates(&states);
    /// </summary>
    SGCONNECT_API void SGConnect_GetConnectionStates(void* out_connectionStates);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Releases any Idle connections that have hooked around a device that is turned off. </summary>
    SGCONNECT_API void ReleaseIdleConnections();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

    // ---------------------------------------------------------------------------------------------
    // C# / IPC interface

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Count the active devices within the SenseComm shared memory. </summary>
    SGCONNECT_API int32_t SGConnect_ActiveDevices();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Returns true if a Device Scanning instance is already running. </summary>
    SGCONNECT_API bool SGConnect_ScanningActive();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Returns the scanningState of the SGConnect library. Used by ScanningActive. </summary>
    /// <returns>
    /// -3 : Error while checking; something is wrong. -> not sure
    /// -2 : Shared Memory exists, but it's timed out -> false
    /// -1 : The current process has an instance of DeviceScanner, but it is no longer live... -> false
    ///  0 : No scanning whatsoever is active -> false
    ///  1 : The current process has an instance of DeviceScanner, and it is live -> true
    ///  2 : SharedMemory exists, and it's still up to date -> true
    /// </returns>
    SGCONNECT_API int32_t SGConnect_ScanningState();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Get the raw (unprocessed) device data of the SGDevice at index, as discovered by SenseCom </summary>
    SGCONNECT_API int32_t SGConnect_GetDeviceString(char* deviceAddress, char* out_deviceString);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Get the raw (unprocessed) sensor data of the SGDevice at index, as discovered by SenseCom. </summary>
    SGCONNECT_API int32_t SGConnect_GetSensorString(char* deviceAddress, char* out_sensorString);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Write a haptics string to the shared memory of a particular device. </summary>
    SGCONNECT_API int32_t SGConnect_WriteHaptics(char* deviceAddress, char* haptics);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Get the raw (unprocessed) haptic command of the SGDevice at index, as discovered by SenseCom.
    /// </summary>
    SGCONNECT_API int32_t SGConnect_GetHapticString(char* deviceAddress, char* out_hapticString);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Write a command string to the shared memory of a particular device. </summary>
    SGCONNECT_API int32_t SGConnect_WriteCommandString(char* deviceAddress, char* commands);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve the last received command from the device </summary>
    SGCONNECT_API int32_t SGConnect_GetCommandResponse(char* deviceAddress, char* out_cmdResponse);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

    //-------------------------------------------------------------------------------------------------------------
    // WhiteList for adding custom Devices.

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Add a device to the Whitelist, so it can be connected to as if it was a SenseGlove Device. </summary>
    /// <param name="pidVidContains"></param>
    /// <returns></returns>
    SGCONNECT_API bool SGConnect_AddToSerialWhiteList(char* pidVidContains);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Remove a device to the Whitelist, It will no longer be connected to. </summary>
    /// <param name="pidVidContains"></param>
    /// <returns></returns>
    SGCONNECT_API bool SGConnect_RemoveFromSerialWhiteList(char* pidVidContains);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

    //-------------------------------------------------------------------------------------------------------------
    // Firmware Uploads

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Upload the contents of the file at filePath onto an SGDevice with the specified Index, provided the device can actually update. Calling this wihtout knowing what you are doing can brick your device! </summary>
    /// <param name="deviceIndex"></param>
    /// <param name="filePath"></param>
    /// <param name="chunkSize"></param>
    /// <returns></returns>
    SGCONNECT_API int32_t SGConnect_Nova2OTAFirmwareUpload(int32_t deviceIndex, const char* filePath, const int32_t chunkSize);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Returns 0 .. 100 if a process is running, otherwise returns -1. </summary>
    /// <returns></returns>
    SGCONNECT_API int32_t SGConnect_GetFirmwareProgress();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Returns the latest upload code from the firmware upload thread. </summary>
    /// <returns></returns>
    SGCONNECT_API int32_t SGConnect_GetLastFirmwareResult();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    //HIGHLY specific case where a user updates a Nova 2 from Bluetooth Serial to Bluetooth Low Energy
    //After Fw finishes uploading, we do not wait to reconnect. Instead, we wait for an external process (SenseCom) to tell us to proceed & clean.
    SGCONNECT_API int32_t SGConnect_Nova2OTAFirmwareUpload_BTS_to_BLE(int32_t deviceIndex, const char* filePath, const int32_t chunkSize);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    SGCONNECT_API void SGConnect_CompleteNova2Nova2OTAFirmwareUpload();
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

    //-------------------------------------------------------------------------------------------------------------
    // BLE Functionality

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> If set to true (Default = true) the SGConnect Library will look for and connect with Bluetooth Serial Devices. If set to false, we will not be checking any BTSerial devices.
    /// Intended use is to set this variable before calling INIT(), and not calling it while anything is running. </summary>
    /// <returns></returns>
    SGCONNECT_API void SGConnect_SetSerialConnectionsEnabled(bool bEnabled);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Informs our back-end to start connecting to and exchanging data with a particular device. </summary>
    SGCONNECT_API int32_t SGConnect_RegisterNova2BLEConnection(const char* localName);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Informs our back-end to stop exchanging data with a particular device. The device itself will still exist, but no data will be exchanged. </summary>
    SGCONNECT_API int32_t SGConnect_UnregisterNova2BLEConnection(const char* localName);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID
    /// <summary> Retrieve the currrent (SenseGlove) BLE Devices in the Vicinity. Structured in a JSON String as an array of devices with a Name and Address </summary>
    /// <param name="localName"></param>
    /// <returns></returns>
    SGCONNECT_API int32_t SGConnect_GetNearbyBLEDevices(char* nearbyDevices);
#endif  /* (SG_PLATFORM_LINUX || SG_PLATFORM_WINDOWS) && !SG_PLATFORM_ANDROID */

#if __cplusplus
}
#endif  /* __cplusplus */

/*******************************************************************************
* End of exported functions
*******************************************************************************/
