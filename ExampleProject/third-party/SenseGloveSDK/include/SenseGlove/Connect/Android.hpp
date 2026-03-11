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

#include <cstdint>
#include <memory>
#include <string>

#include <jni.h>

namespace SGConnect
{
    class Android;
}// namespace SGConnect

class SGCONNECT_API SGConnect::Android
{
public:
    /// NOTE
    // If ContextWrapper.getFilesDir() is passed as storagePath, it won't require any special permission such as:
    // android.permission.WRITE_EXTERNAL_STORAGE or android.permission.READ_EXTERNAL_STORAGE.
    // On the Unreal Engine side, this would be FPaths::ProjectSavedDir.
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
    /// -105 : Android JNI Error: Could not find the Init method!
    /// -106 : Android JNI Error: Could not find the Dispose method!
    /// -107 : Android JNI Error: Could not find the GetLibraryVersion method!
    /// </returns>
    static int32_t Initialize(JNIEnv* inEnv, jclass inClass = nullptr,
                              jmethodID inInitMethodID = nullptr,
                              jmethodID inDisposeMethodID = nullptr,
                              jmethodID inGetLibraryVersionMethodID = nullptr,
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
    /// -3 : An Unexpected error occurred. Please try again.
    /// -2 : Device Scanning is already running within a different program.
    /// -1 : Device Scanning already being initialized (function called twice in short succession).
    ///  0 : Device Scanning is already running within this program.
    ///  1 : Successfully started up DeviceScanning from the current program.
    /// </returns>
    int32_t Init() const;

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
    int32_t Dispose() const;

    /// <returns>
    /// Empty String: Android JNI-specific failure!
    /// Version Number: if succeeds.
    /// </returns>
    [[nodiscard]] std::string GetLibraryVersion() const;
};

#endif  /* SG_PLATFORM_ANDROID */
