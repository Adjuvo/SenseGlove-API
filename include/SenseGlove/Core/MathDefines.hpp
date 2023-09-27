/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2023 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Contains reusable piece of code to include the proper math defines like
 * Pi / Sin / Sqrt.
 */


#pragma once

#include "Platform.hpp"

#if !defined ( _USE_MATH_DEFINES )
#define _USE_MATH_DEFINES
#endif /* ! defined ( _USE_MATH_DEFINES ) */

#if SG_PLATFORM_WINDOWS
#include <algorithm>
#include "math.h"
#endif

#include <cmath>