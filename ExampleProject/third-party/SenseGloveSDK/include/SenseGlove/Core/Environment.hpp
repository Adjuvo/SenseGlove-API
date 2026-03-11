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
 * Utilities to query the runtime environment.
 */


#pragma once

#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    class SGCORE_API Environment;
}// namespace SGCore

class SGCORE_API SGCore::Environment
{
public:
    static bool GetEnv(const char* var, std::string& out_value);

public:
    Environment() = delete;
    virtual ~Environment() = delete;
};
