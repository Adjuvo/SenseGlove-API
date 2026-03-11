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
 * Contains reusable piece of code to include the proper math defines like
 * Pi / Sin / Sqrt.
 */


#pragma once

#include <SenseGlove/Common/Platform.hpp>

#if !defined ( _USE_MATH_DEFINES )
#define _USE_MATH_DEFINES
#endif  /* ! defined ( _USE_MATH_DEFINES ) */

#if SG_PLATFORM_WINDOWS
#include <algorithm>
#include "math.h"
#endif  /*SG_PLATFORM_WINDOWS*/

#include <cmath>

namespace SGCommon
{
    SG_FORCEINLINE float sg_acosf(const float num)
    {
        return ::acosf(num);
    }

    SG_FORCEINLINE float sg_atan2f(const float y, const float x)
    {
        return ::atan2f(y, x);
    }

    template<class Integer>
    SG_FORCEINLINE double sg_fabs(const Integer num)
    {
        return ::fabs(num);
    }
}// namespace SGCommon
