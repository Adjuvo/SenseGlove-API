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
 * Floating point related utility macros and methods.
 */


#pragma once

#include "MathDefines.hpp"
#include "Platform.hpp"

#define SG_SMALL_NUMBER (1.e-8f)
#define SG_KINDA_SMALL_NUMBER (1.e-4f)

namespace SGCore
{
    namespace Util
    {
        class SGCORE_API FloatUtils;
    }// namespace Util
}// namespace SGCore

class SGCORE_API SGCore::Util::FloatUtils
{
public:
    static SG_FORCEINLINE bool IsNearlyEqual(const float a, const float b, const float errorTolerance = SG_SMALL_NUMBER)
    {
        return std::abs(a - b) <= errorTolerance;
    }

    static SG_FORCEINLINE bool IsNearlyZero(const float value, const float errorTolerance = SG_SMALL_NUMBER)
    {
        return std::abs(value) <= errorTolerance;
    }

public:
    FloatUtils() = delete;
    virtual ~FloatUtils() = delete;
};