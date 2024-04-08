/**
 * @file
 *
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2024 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Provides Android-specific functionality.
 */


#pragma once

#include "Platform.hpp"

#if SG_PLATFORM_ANDROID

#include <cstring>
#include <memory>
#include <string>

#include <jni.h>

#include "Platform.hpp"

namespace SGCore
{
    class Android;
}// namespace SGCore

class SGCore::Android
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
    SG_NODISCARD int32_t ActiveDevices() const;

    SG_NODISCARD std::string GetDeviceString(int32_t deviceAddress) const;

    SG_NODISCARD std::string GetSensorString(int32_t deviceAddress) const;

    int32_t WriteHaptics(int32_t deviceAddress, int32_t channelIndex, const std::string& haptics) const;
};

#endif /* SG_PLATFORM_ANDROID */