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
 * File Input/output handling.
 */


#pragma once

#include <string>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Util
    {
        class SGCORE_API FileIO;
    }// namespace Util
}// namespace SGCore

class SGCORE_API SGCore::Util::FileIO
{
public:
    SG_FORCEINLINE static const std::string& GetDirectorySeparator()
    {
        static const std::string separator{
#if ! SG_PLATFORM_WINDOWS
                "/"
#else  /* ! SG_PLATFORM_WINDOWS */
                "\\"
#endif  /* ! SG_PLATFORM_WINDOWS */
        };
        return separator;
    }

    SG_FORCEINLINE static char GetDirectorySeparatorChar()
    {
        return GetDirectorySeparator().c_str()[0];
    }

    /// <summary> Attempt to read all lines from a file and place them in the string[]. Returns true if successful.
    /// If unable to open the file, the string[] will be empty.</summary>
    /// <param name="filePath"></param>
    /// <param name="out_lines"></param>
    /// <returns></returns>
    static bool ReadTextFile(const std::string& filePath, std::vector<std::string>& out_lines);

    /// <summary> Attempt to save a string[] to a filename within a desired directory. Returns true if successful.
    /// </summary>
    /// <remarks> Directory is added as a separate variable so we can more easily check for its existence. </remarks>
    /// <param name="directory"></param>
    /// <param name="fileName"></param>
    /// <param name="contents"></param>
    /// <param name="append"></param>
    /// <returns></returns>
    static bool SaveTextFile(const std::string& directory, const std::string& fileName,
                             const std::vector<std::string>& contents, bool bAppend = false);

    /// <summary> Creates a new directory. Returns  false if it already existed. </summary>
    /// <param name="directory"></param>
    /// <returns></returns>
    static bool CreateFullDirectory(const std::string& directoryPath);

    /// <summary> Returns true if the directory exists </summary>
    /// <param name="dir"></param>
    /// <returns></returns>
    SG_NODISCARD static bool DirectoryExists(const std::string& directoryPath);

    /// <summary> Returns true if this file exists </summary>
    /// <param name="filePath"></param>
    /// <returns></returns>
    static bool FileExists(const std::string& filePath);

    /// <summary> STUB - Gets the working directory of the current process. </summary>
    /// <returns></returns>
    SG_NODISCARD static std::string GetWorkingDirectory();

    /// <summary> Get the Path to MyDocuments, but without '\\' at the end. </summary>
    /// <returns></returns>
    SG_NODISCARD static std::string GetMyDocumentsPath();

    /// <summary> Get the Path to XDG_CONFIG_HOME on non-Windows platforms. </summary>
    /// <returns></returns>
    SG_NODISCARD static std::string GetXdgConfigHomePath();

    /// <summary> An easy way to get the SenseGlove home directory in a platform-agnostic manner,
    /// without the separator char at the end, unless the user specifies one through the env vars
    /// on non-Windows platforms. This should be fine on Linux, Android as well even if we end up
    /// having multiple consecutive slashes. </summary>
    /// <returns></returns>
    SG_NODISCARD static std::string GetSenseGloveHomePath();

public:
    FileIO() = delete;
    virtual ~FileIO() = delete;
};