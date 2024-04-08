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
 * Platform-specific hacks and macros.
 */


#pragma once

/*******************************************************************************
* Include directives
*******************************************************************************/

#include <string>

/*******************************************************************************
* Platform macros
*******************************************************************************/

#if defined ( __ANDROID__ )
#define SG_PLATFORM_ANDROID 1
#else   /* defined ( __ANDROID__) */
#define SG_PLATFORM_ANDROID 0
#endif  /* defined ( __ANDROID__ ) */

#if SG_PLATFORM_ANDROID
#if defined ( __arm__ )
#define SG_PLATFORM_ANDROID_ARM 1
#endif  /* defined ( __arm__ ) */
#if defined ( __aarch64__ )
#define SG_PLATFORM_ANDROID_ARM64 1
#endif  /* defined ( __aarch64__ ) */
#if defined ( __i386__ )
#define SG_PLATFORM_ANDROID_X86 1
#endif  /* defined ( __i386__ ) */
#if defined ( __x86_64__ )
#define SG_PLATFORM_ANDROID_X64 1
#endif  /* defined ( __x86_64__ ) */
#endif  /* SG_PLATFORM_ANDROID */

#if !defined ( SG_PLATFORM_ANDROID_ARM )
#define SG_PLATFORM_ANDROID_ARM 0
#endif  /* ! defined ( SG_PLATFORM_ANDROID_ARM ) */

#if !defined ( SG_PLATFORM_ANDROID_ARM64 )
#define SG_PLATFORM_ANDROID_ARM64 0
#endif  /* ! defined ( SG_PLATFORM_ANDROID_ARM64 ) */

#if !defined ( SG_PLATFORM_ANDROID_X86 )
#define SG_PLATFORM_ANDROID_X86 0
#endif  /* ! defined ( SG_PLATFORM_ANDROID_X86 ) */

#if !defined ( SG_PLATFORM_ANDROID_X64 )
#define SG_PLATFORM_ANDROID_X64 0
#endif  /* ! defined ( SG_PLATFORM_ANDROID_X64 ) */

#if defined ( __linux__ )
#define SG_PLATFORM_LINUX 1
#else   /* defined ( __linux__ ) */
#define SG_PLATFORM_LINUX 0
#endif  /* defined ( __linux__ ) */

#if defined ( _WIN32 ) || defined ( _WIN64 )
#define SG_PLATFORM_WINDOWS 1
#else   /* defined ( _WIN32 ) || defined ( _WIN64 ) */
#define SG_PLATFORM_WINDOWS 0
#endif  /* defined ( _WIN32 ) || defined ( _WIN64 ) */

/*******************************************************************************
* C++ standards macros
*******************************************************************************/

#if ( ( defined( _MSVC_LANG ) && _MSVC_LANG >= 201703L ) || __cplusplus >= 201703L )
#define SG_CPP17 1
#else   /* ( ( defined( _MSVC_LANG ) && _MSVC_LANG >= 201703L ) || __cplusplus >= 201703L ) */
#define SG_CPP17 0
#endif  /* ( ( defined( _MSVC_LANG ) && _MSVC_LANG >= 201703L ) || __cplusplus >= 201703L ) */

/*******************************************************************************
* C++ standard library implementaion detection macros
*******************************************************************************/

#if defined ( __GLIBCXX__ ) || defined ( __GLIBCPP__ )
#define SG_LIBCPP_GNU 1
#else  /* defined ( __GLIBCXX__ ) || defined ( __GLIBCPP__ ) */
#define SG_LIBCPP_GNU 0
#endif  /* defined ( __GLIBCXX__ ) || defined ( __GLIBCPP__ ) */

#if defined ( _LIBCPP_VERSION )
#define SG_LIBCPP_LLVM 1
#else  /* defined ( _LIBCPP_VERSION ) */
#define SG_LIBCPP_LLVM 0
#endif  /* defined ( _LIBCPP_VERSION ) */

#if defined ( _YVALS_CORE_H_ )
#define SG_LIBCPP_MICROSOFT 1
#else  /* defined ( _YVALS_CORE_H_ ) */
#define SG_LIBCPP_MICROSOFT 0
#endif  /* defined ( _YVALS_CORE_H_ ) */

/*******************************************************************************
* Function type macros
*******************************************************************************/

#if SG_PLATFORM_WINDOWS
#define SG_FORCEINLINE __forceinline          /* Force the code to be inline */
#define SG_FORCENOINLINE __declspec(noinline) /* Force the code to NOT be inline */
#else                                         /* Other platforms than Windows */
#if defined(SENSEGLOVE_DEBUG_BUILD)
#define SG_FORCEINLINE inline /* Don't force code to be inline, or you'll run into -Wignored-attributes */
#else
#define SG_FORCEINLINE inline __attribute__((always_inline)) /* Force the code to be inline */
#endif                                                       /* defined ( SENSEGLOVE_DEBUG_BUILD ) */
#define SG_FORCENOINLINE __attribute__((noinline))           /* Force the code to NOT be inline */
#endif                                                       /* defined ( SG_PLATFORM_WINDOWS ) */

#if SG_CPP17
#define SG_NODISCARD [[nodiscard]]
#else   /* SG_CPP17 */
#define SG_NODISCARD
#endif  /* SG_CPP17 */

/*******************************************************************************
* DLL export and import definitions
*******************************************************************************/

#if !defined ( SGCORE_SHARED )
#define SGCORE_SHARED 0
#endif  /* ! defined ( SGCORE_SHARED ) */

#if !defined ( SGCORE_EXPORT )
#define SGCORE_EXPORT 0
#endif  /* ! defined ( SGCORE_EXPORT ) */

#if SG_PLATFORM_WINDOWS
#define SG_DLLEXPORT __declspec(dllexport)
#define SG_DLLIMPORT __declspec(dllimport)
#else   /* Other platforms than Windows */
#define SG_DLLEXPORT __attribute__((visibility("default")))
#define SG_DLLIMPORT __attribute__((visibility("default")))
#endif  /* SG_PLATFORM_WINDOWS */

#if SGCORE_SHARED
#if SGCORE_EXPORT
#define SGCORE_API SG_DLLEXPORT
#else   /* SGCORE_EXPORT */
#define SGCORE_API SG_DLLIMPORT
#endif  /* SGCORE_EXPORT */
#else   /* SGCORE_SHARED */
#define SGCORE_API
#endif  /* SGCORE_SHARED */

/*******************************************************************************
* Unreal Engine support
*******************************************************************************/

#if !defined ( SENSEGLOVE_UNREAL_ENGINE_PLUGIN )
#define SENSEGLOVE_UNREAL_ENGINE_PLUGIN 0
#endif  /* !defined ( SENSEGLOVE_UNREAL_ENGINE_PLUGIN ) */

/*******************************************************************************
* The platform class implementation
*******************************************************************************/

#pragma once

namespace SGCore
{
    class SGCORE_API Platform;
}// namespace SGCore

class SGCORE_API SGCore::Platform
{
public:
    static bool GetEnv(const char* var, std::string& out_value);

public:
    Platform() = delete;
    virtual ~Platform() = delete;
};