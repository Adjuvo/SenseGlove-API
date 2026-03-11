/**
 * @file
 *
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2026 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Provides Android-specific functionality.
 */


#pragma once

#include <SenseGlove/Common/Platform.hpp>

#if SG_PLATFORM_ANDROID

#include <cstring>
#include <memory>
#include <string>

#include <jni.h>

#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    class Android;
}// namespace SGCore

class SGCORE_API SGCore::Android
{
public:
    /// NOTE
    // If ContextWrapper.getFilesDir() is passed as storagePath, it won't require any special permission such as:
    // android.permission.WRITE_EXTERNAL_STORAGE or android.permission.READ_EXTERNAL_STORAGE.
    // On the Unreal Engine side, this would be FPaths::ProjectSavedDir. It also requires the following configuration:
    // [/Script/AndroidRuntimeSettings.AndroidRuntimeSettings]
    // bUseExternalFilesDir=True
    // inside the DefaultEngine.ini file.
    // Also, note that we'd assume the directory exists and user has the sufficient read/write permissions, so we won't
    // try to create the directory.
    /// <returns>
    /// -101 : Android JNI Error: Invalid JNI environment!
    /// -102 : Android JNI Error: Could not get the Java VM!
    /// -103 : Android JNI Error: Failed to attach the current thread to the Java VM!
    /// -104 : Android JNI Error: Could not find the Android Java class!
    /// -105 : Android JNI Error: Could not find the ActiveDevices method!
    /// -106 : Android JNI Error: Could not find the GetDeviceString method!
    /// -107 : Android JNI Error: Could not find the GetSensorString method!
    /// -108 : Android JNI Error: Could not find the WriteHaptics method!
    /// </returns>
    static int32_t Initialize(JNIEnv* inEnv, jclass inClass = nullptr,
                              jmethodID inActiveDevicesMethodID = nullptr,
                              jmethodID inGetDeviceStringMethodID = nullptr,
                              jmethodID inGetSensorStringMethodID = nullptr,
                              jmethodID inWriteHapticsMethodID = nullptr,
                              const std::string& storagePath = "/mnt/sdcard/SenseGlove");

    static Android& GetInstance();

public:
    static const std::string& GetStoragePath();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

private:
    Android();

public:
    virtual ~Android();

public:
    /// <returns>
    /// -103 : Android JNI-specific Error: Invalid Java method ID!
    /// -102 : Android JNI-specific Error: Invalid Java class!
    /// -101 : Android JNI-specific Error: Invalid Java environment!
    /// -100 : Android JNI-specific Error: Generic Error! Note: you should never see this!
    /// </returns>
    [[nodiscard]] int32_t ActiveDevices() const;

    /// <returns>
    /// Empty String: Android JNI-specific failure!
    /// Device String: if succeeds.
    /// </returns>
    [[nodiscard]] std::string GetDeviceString(int32_t deviceAddress) const;

    /// <returns>
    /// Empty String: Android JNI-specific failure!
    /// Sensor String: if succeeds.
    /// </returns>
    [[nodiscard]] std::string GetSensorString(int32_t deviceAddress) const;

    /// <returns>
    /// -103 : Android JNI-specific Error: Invalid Java method ID!
    /// -102 : Android JNI-specific Error: Invalid Java class!
    /// -101 : Android JNI-specific Error: Invalid Java environment!
    /// -100 : Android JNI-specific Error: Generic Error! Note: you should never see this!
    /// </returns>
    int32_t WriteHaptics(int32_t deviceAddress, int32_t channelIndex, const std::string& haptics) const;
};

#endif /* SG_PLATFORM_ANDROID */
