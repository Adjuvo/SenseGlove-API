/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2024 SenseGlove
 *
 * @section DESCRIPTION
 *
 *
 */


#pragma once

#include <string>

#include "Platform.hpp"

namespace SGCore
{
    class SGCORE_API SenseCom;
}// namespace SGCore

class SGCORE_API SGCore::SenseCom
{
public:
    /// <summary> Registers current process as the latest SenseCom build. </summary>
    /// <returns></returns>
    static bool RegisterExe();

    /// <summary> Register a particular path as the SenseGlove executable location. </summary>
    /// <param name="out_exePath"></param>
    /// <returns></returns>
    static bool RegisterExe(const std::string& out_exePath);

    /// <summary> Retrieve the location of SenseGlove executable. </summary>
    /// <param name="exePath"></param>
    /// <returns></returns>
    static bool GetExePath(std::string& exePath);

    /// <summary> Returns true if SenseCom scanning is active. </summary>
    /// <returns></returns>
    static bool ScanningActive();

    /// <summary> Returns the directory of the current process. </summary>
    /// <param name="out_directory"></param>
    /// <returns></returns>
    static bool GetCurrentExeDirectory(std::string& out_directory);

    /// <summary> Force-starts the SenseCom application if it is active on the system. </summary>
    /// <returns></returns>
    static bool StartupSenseCom();

private:
    struct Impl;

public:
    SenseCom() = delete;
    virtual ~SenseCom() = delete;
};