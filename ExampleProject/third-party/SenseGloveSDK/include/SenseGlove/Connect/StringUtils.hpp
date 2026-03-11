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
 * String conversion, parsing and other utility stuff. Much more prominent in
 * C++.
 */


#pragma once

#include <SenseGlove/Common/Platform.hpp>

#include <memory>
#if SG_HAS_STD_FORMAT
#include <format>
#endif  /* SG_HAS_STD_FORMAT */
#include <stdexcept>
#include <string>
#include <vector>

#include "ExitCodes.hpp"

namespace SGConnect
{
    class StringUtils;
}

/// <summary> Utility class to convert strings into usable values. </summary>
class SGCONNECT_API SGConnect::StringUtils
{
public:
    /// <summary> Split a std::string into a vector of std::strings by a delimiter </summary>
    static std::vector<std::string> Split(const std::string& str, char delimiter);

    /// <summary> Convert a string into an integer value. </summary>
    static int32_t ToInt(const std::string& str);

    /// <summary> Convert a string into a decimal value. </summary>
    static float ToFloat(const std::string& str);

    static std::string ToString(EExitCode code);

    // NOTE:
    // SG_HAS_STD_FORMAT is a mandatory workaround for Android NDK r25b and Epic
    // Native or Cross Toolchains v22, which lack full <format> support.
    // Once support for these toolchains is dropped, SG_HAS_STD_FORMAT and
    // StringUtils::FormatString() can be removed in favor of direct usage of
    // std::format().
#if SG_HAS_STD_FORMAT
    template<typename... Args>
    SG_FORCEINLINE static std::string FormatString(std::format_string<Args...> fmt, Args&&... args)
    {
        return std::format(fmt, std::forward<Args>(args)...);
    }
#else   /* SG_HAS_STD_FORMAT */
    template<typename... Args>
    static std::string FormatString(const std::string& fmt, const Args&... args)
    {
        int32_t size = std::snprintf(nullptr, 0, fmt.c_str(), args...) + 1;// extra space for '\0'
        SG_ASSERT(size > 0, "Error during formatting: size must be positive.");
        std::unique_ptr<char[]> buffer{std::make_unique<char[]>(size)};
        std::snprintf(buffer.get(), size, fmt.c_str(), args...);
        return std::string{buffer.get(), buffer.get() + size - 1};// we don't want the '\0' inside
    }
#endif   /* SG_HAS_STD_FORMAT */

    //Base64 Encoding - for firmware. Taken from https://github.com/tobiaslocker/base64
    static std::string get_base64_chars();
    static std::string CharV_to_base64(const std::vector<char>& data);

    static bool CopyString(const std::string& data, char* out_buffer, std::string& out_error);

public:
    StringUtils() = delete;
    virtual ~StringUtils() = delete;
};