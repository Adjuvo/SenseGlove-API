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
 * Platform-specific hacks and macros.
 */


#pragma once

/*******************************************************************************
* Architecture macros
*******************************************************************************/

#if defined(__i386__) || defined(_M_IX86)
#define SG_CPU_X86 1
#else   /* defined(__i386__) || defined(_M_IX86) */
#define SG_CPU_X86 0
#endif  /* defined(__i386__) || defined(_M_IX86) */

#if defined(__x86_64__) || defined(_M_X64)
#define SG_CPU_X86_64 1
#else   /* defined(__x86_64__) || defined(_M_X64) */
#define SG_CPU_X86_64 0
#endif  /* defined(__x86_64__) || defined(_M_X64) */

#if defined(__arm__) || defined(_M_ARM)
#define SG_CPU_ARM32 1
#else   /* defined(__arm__) || defined(_M_ARM) */
#define SG_CPU_ARM32 0
#endif  /* defined(__arm__) || defined(_M_ARM) */

#if defined(__aarch64__) || defined(_M_ARM64)
#define SG_CPU_ARM64 1
#else   /* defined(__aarch64__) || defined(_M_ARM64) */
#define SG_CPU_ARM64 0
#endif  /* defined(__aarch64__) || defined(_M_ARM64) */

/* Fallback "is-any" CPU family flags */
#define SG_CPU_ANY_X86 (SG_CPU_X86 || SG_CPU_X86_64)
#define SG_CPU_ANY_ARM (SG_CPU_ARM32 || SG_CPU_ARM64)

/*******************************************************************************
* Platform macros
*******************************************************************************/

#if defined(__ANDROID__)
#define SG_PLATFORM_ANDROID 1
#else   /* defined(__ANDROID__) */
#define SG_PLATFORM_ANDROID 0
#endif  /* defined(__ANDROID__) */

#if SG_PLATFORM_ANDROID
#if defined(__arm__)
#define SG_PLATFORM_ANDROID_ARM 1
#endif  /* defined(__arm__) */
#if defined(__aarch64__)
#define SG_PLATFORM_ANDROID_ARM64 1
#endif  /* defined(__aarch64__) */
#if defined(__i386__)
#define SG_PLATFORM_ANDROID_X86 1
#endif  /* defined(__i386__) */
#if defined(__x86_64__)
#define SG_PLATFORM_ANDROID_X64 1
#endif  /* defined(__x86_64__) */
#endif  /* SG_PLATFORM_ANDROID */

#if !defined(SG_PLATFORM_ANDROID_ARM)
#define SG_PLATFORM_ANDROID_ARM 0
#endif  /* !defined(SG_PLATFORM_ANDROID_ARM) */

#if !defined(SG_PLATFORM_ANDROID_ARM64)
#define SG_PLATFORM_ANDROID_ARM64 0
#endif  /* !defined(SG_PLATFORM_ANDROID_ARM64) */

#if !defined(SG_PLATFORM_ANDROID_X86)
#define SG_PLATFORM_ANDROID_X86 0
#endif  /* !defined(SG_PLATFORM_ANDROID_X86) */

#if !defined(SG_PLATFORM_ANDROID_X64)
#define SG_PLATFORM_ANDROID_X64 0
#endif  /* !defined(SG_PLATFORM_ANDROID_X64) */

#if defined(__linux__)
#define SG_PLATFORM_LINUX 1
#else   /* defined(__linux__) */
#define SG_PLATFORM_LINUX 0
#endif  /* defined(__linux__) */

#if SG_PLATFORM_LINUX && SG_CPU_X86_64
#define SG_PLATFORM_LINUX_X86_64 1
#else   /* SG_PLATFORM_LINUX && SG_CPU_X86_64 */
#define SG_PLATFORM_LINUX_X86_64 0
#endif  /* SG_PLATFORM_LINUX && SG_CPU_X86_64 */

#if SG_PLATFORM_LINUX && SG_CPU_ARM64
#define SG_PLATFORM_LINUX_AARCH64 1
#else   /* SG_PLATFORM_LINUX && SG_CPU_ARM64 */
#define SG_PLATFORM_LINUX_AARCH64 0
#endif  /* SG_PLATFORM_LINUX && SG_CPU_ARM64 */

#if defined(_WIN32) || defined(_WIN64)
#define SG_PLATFORM_WINDOWS 1
#else   /* defined(_WIN32) || defined(_WIN64) */
#define SG_PLATFORM_WINDOWS 0
#endif  /* defined(_WIN32) || defined(_WIN64) */

/*******************************************************************************
* Compiler detection macros
*******************************************************************************/

#if defined(__clang__)
#define SG_COMPILER_CLANG 1
#else   /* defined(__clang__) */
#define SG_COMPILER_CLANG 0
#endif  /* defined(__clang__) */

#if defined(__GNUC__) && !defined(__clang__)
#define SG_COMPILER_GCC 1
#else   /* defined(__GNUC__) && !defined(__clang__) */
#define SG_COMPILER_GCC 0
#endif  /* defined(__GNUC__) && !defined(__clang__) */

#if defined(_MSC_VER)
#define SG_COMPILER_MSVC 1
#else   /* defined(__MSC_VER) */
#define SG_COMPILER_MSVC 0
#endif  /* defined(__MSC_VER) */

#if defined(__cplusplus)
#define SG_IS_CPP_COMPILER 1
#else  /* defined(__cplusplus) */
#define SG_IS_CPP_COMPILER 0
#endif /* defined(__cplusplus) */

/*******************************************************************************
* C++ standard library implementaion detection macros
*******************************************************************************/

#if defined(__GLIBCXX__) || defined(__GLIBCPP__)
#define SG_LIBCPP_GNU 1
#else  /* defined(__GLIBCXX__) || defined(__GLIBCPP__) */
#define SG_LIBCPP_GNU 0
#endif  /* defined(__GLIBCXX__) || defined(__GLIBCPP__) */

#if defined(_LIBCPP_VERSION)
#define SG_LIBCPP_LLVM 1
#else  /* defined(_LIBCPP_VERSION) */
#define SG_LIBCPP_LLVM 0
#endif  /* defined(_LIBCPP_VERSION) */

#if defined(_YVALS_CORE_H_)
#define SG_LIBCPP_MICROSOFT 1
#else  /* defined(_YVALS_CORE_H_) */
#define SG_LIBCPP_MICROSOFT 0
#endif  /* defined(_YVALS_CORE_H_) */

/*******************************************************************************
* Function type macros
*******************************************************************************/

#if SG_PLATFORM_WINDOWS
#define SG_FORCEINLINE __forceinline          /* Force the code to be inline */
#define SG_FORCENOINLINE __declspec(noinline) /* Force the code to NOT be inline */
#else                                         /* Other platforms than Windows */
#if defined(SENSEGLOVE_DEBUG_BUILD)
#define SG_FORCEINLINE inline /* Don't force code to be inline, or you'll run into -Wignored-attributes */
#else   /* defined(SENSEGLOVE_DEBUG_BUILD) */
#define SG_FORCEINLINE inline __attribute__((always_inline)) /* Force the code to be inline */
#endif                                                       /* defined(SENSEGLOVE_DEBUG_BUILD) */
#define SG_FORCENOINLINE __attribute__((noinline))           /* Force the code to NOT be inline */
#endif                                                       /* SG_PLATFORM_WINDOWS */

/*******************************************************************************
* Exceptions Detection
*******************************************************************************/

#if SG_IS_CPP_COMPILER && SG_COMPILER_CLANG && defined(__has_feature)
#if __has_feature(cxx_exceptions)
#define SG_HAS_EXCEPTIONS 1
#else   /* __has_feature(cxx_exceptions) */
#define SG_HAS_EXCEPTIONS 0
#endif  /* __has_feature(cxx_exceptions) */
#elif SG_COMPILER_GCC && defined(__EXCEPTIONS)
#define SG_HAS_EXCEPTIONS 1
#elif SG_COMPILER_MSVC && defined(_CPPUNWIND)
#define SG_HAS_EXCEPTIONS 1
#else   /* SG_IS_CPP_COMPILER && SG_COMPILER_CLANG && defined(__has_feature) */
#define SG_HAS_EXCEPTIONS 0
#endif  /* SG_IS_CPP_COMPILER && SG_COMPILER_CLANG && defined(__has_feature) */

/*******************************************************************************
* RTTI Detection
*******************************************************************************/

#if SG_IS_CPP_COMPILER && SG_COMPILER_CLANG && defined(__has_feature)
#if __has_feature(cxx_rtti)
#define SG_HAS_RTTI 1
#else   /* __has_feature(cxx_rtti) */
#define SG_HAS_RTTI 0
#endif  /* __has_feature(cxx_rtti) */
#elif SG_COMPILER_GCC && defined(__GXX_RTTI)
#define SG_HAS_RTTI 1
#elif SG_COMPILER_MSVC && defined(_CPPRTTI)
#define SG_HAS_RTTI 1
#else   /* SG_IS_CPP_COMPILER && SG_COMPILER_CLANG && defined(__has_feature) */
#define SG_HAS_RTTI 0
#endif  /* SG_IS_CPP_COMPILER && SG_COMPILER_CLANG && defined(__has_feature) */

/*******************************************************************************
* Include directives
*******************************************************************************/

#if SG_COMPILER_MSVC
#include <intrin.h>
#endif  /* SG_COMPILER_MSVC */

#if SG_COMPILER_CLANG || SG_COMPILER_GCC
#if SG_IS_CPP_COMPILER
#include <csignal>
#else   /* SG_IS_CPP_COMPILER */
#include <signal.h>
#endif  /* SG_IS_CPP_COMPILER */
#endif  /* SG_COMPILER_CLANG || SG_COMPILER_GCC */

#if SG_IS_CPP_COMPILER
#include <cstdio>
#else   /* SG_IS_CPP_COMPILER */
#include <stdio.h>
#endif  /* SG_IS_CPP_COMPILER */

/*******************************************************************************
* Assertion Macros
*******************************************************************************/

#if SG_COMPILER_CLANG || SG_COMPILER_GCC
#define SG_DEBUG_BREAK() raise(SIGTRAP)
#elif SG_COMPILER_MSVC
#define SG_DEBUG_BREAK() __debugbreak()
#else   /* SG_COMPILER_CLANG || SG_COMPILER_GCC */
#define SG_DEBUG_BREAK() ((void)0)
#endif  /* SG_COMPILER_CLANG || SG_COMPILER_GCC */

#if defined(SENSEGLOVE_DEBUG_BUILD)
#if SG_IS_CPP_COMPILER
#define SG_ASSERT(condition, message)                               \
    do {                                                            \
        if (!(condition)) {                                         \
            std::fprintf(stderr,                                    \
                         "[SG_ASSERT] Assertion failed!\n"          \
                         "  condition : %s\n"                       \
                         "  Message   : %s\n"                       \
                         "  File      : %s\n"                       \
                         "  Line      : %d\n",                      \
                         #condition, message, __FILE__, __LINE__);  \
            std::fflush(stderr);                                    \
            SG_DEBUG_BREAK();                                       \
        }                                                           \
    } while (0)
#else   /* SG_IS_CPP_COMPILER */
#define SG_ASSERT(condition, message)                          \
    do {                                                       \
        if (!(condition)) {                                    \
            fprintf(stderr,                                    \
                    "[SG_ASSERT] Assertion failed!\n"          \
                    "  condition : %s\n"                       \
                    "  Message   : %s\n"                       \
                    "  File      : %s\n"                       \
                    "  Line      : %d\n",                      \
                    #condition, message, __FILE__, __LINE__);  \
            fflush(stderr);                                    \
            SG_DEBUG_BREAK();                                  \
        }                                                      \
    } while (0)
#endif  /* SG_IS_CPP_COMPILER */
#else   /* defined(SENSEGLOVE_DEBUG_BUILD) */
#define SG_ASSERT(condition, message)
#endif  /* defined(SENSEGLOVE_DEBUG_BUILD) */

/*******************************************************************************
* std::format support detection
*******************************************************************************/

#if SG_IS_CPP_COMPILER

// NOTE:
// SG_HAS_STD_FORMAT is a mandatory workaround for Android NDK r25b and Epic
// Native or Cross Toolchains v22, which lack full <format> support.
// Once support for these toolchains is dropped, SG_HAS_STD_FORMAT and
// StringUtils::FormatString() can be removed in favor of direct usage of
// std::format().

#if defined(__has_include)
#if __has_include(<format>)
#include <version>
#if defined(__cpp_lib_format) && __cpp_lib_format >= 201907L
#if !defined(_MSC_VER) || _MSC_VER >= 1930
#define SG_HAS_STD_FORMAT 1
#endif  /* !defined(_MSC_VER) || _MSC_VER >= 1930 */
#endif  /* defined(__cpp_lib_format) && __cpp_lib_format >= 201907L */
#endif  /* __has_include(<format>) */
#endif  /* defined(__has_include) */

#if !defined(SG_HAS_STD_FORMAT)
#define SG_HAS_STD_FORMAT 0
#endif  /* !defined(SG_HAS_STD_FORMAT) */

#endif /* SG_IS_CPP_COMPILER */

/*******************************************************************************
* DLL export and import definitions
*******************************************************************************/

#if SG_PLATFORM_WINDOWS
#define SG_DLLEXPORT __declspec(dllexport)
#define SG_DLLIMPORT __declspec(dllimport)
#else   /* Other platforms than Windows */
#define SG_DLLEXPORT __attribute__((visibility("default")))
#define SG_DLLIMPORT __attribute__((visibility("default")))
#endif  /* SG_PLATFORM_WINDOWS */

#if SG_COMPILER_CLANG || SG_COMPILER_GCC
#define SG_WEAK_LINKAGE __attribute__((weak))
#elif SG_COMPILER_MSVC
#define SG_WEAK_LINKAGE SG_FORCEINLINE
#else   /* SG_COMPILER_CLANG || SG_COMPILER_GCC */
#define SG_WEAK_LINKAGE
#endif  /* SG_COMPILER_CLANG || SG_COMPILER_GCC */

/*******************************************************************************
* DLL export and import definitions - SGCommon
*******************************************************************************/

#if !defined(SGCOMMON_SHARED)
#define SGCOMMON_SHARED 0
#endif  /* !defined(SGCOMMON_SHARED) */

#if !defined(SGCOMMON_EXPORT)
#define SGCOMMON_EXPORT 0
#endif  /* !defined(SGCOMMON_EXPORT) */

#if SGCOMMON_SHARED
#if SGCOMMON_EXPORT
#define SGCOMMON_API SG_DLLEXPORT
#else   /* SGCOMMON_EXPORT */
#define SGCOMMON_API SG_DLLIMPORT
#endif  /* SGCOMMON_EXPORT */
#else   /* SGCOMMON_SHARED */
#define SGCOMMON_API
#endif  /* SGCOMMON_SHARED */

/*******************************************************************************
* DLL export and import definitions - SGConnect
*******************************************************************************/

#if !defined(SGCONNECT_SHARED)
#define SGCONNECT_SHARED 0
#endif  /* !defined(SGCONNECT_SHARED) */

#if !defined(SGCONNECT_EXPORT)
#define SGCONNECT_EXPORT 0
#endif  /* !defined(SGCONNECT_EXPORT) */

#if SGCONNECT_SHARED
#if SGCONNECT_EXPORT
#define SGCONNECT_API SG_DLLEXPORT
#else   /* SGCONNECT_EXPORT */
#define SGCONNECT_API SG_DLLIMPORT
#endif  /* SGCONNECT_EXPORT */
#else   /* SGCONNECT_SHARED */
#define SGCONNECT_API
#endif  /* SGCONNECT_SHARED */

/*******************************************************************************
* DLL export and import definitions - SGConnectShm
*******************************************************************************/

#if !defined(SGCONNECTSHM_SHARED)
#define SGCONNECTSHM_SHARED 0
#endif  /* !defined(SGCONNECTSHM_SHARED) */

#if !defined(SGCONNECTSHM_EXPORT)
#define SGCONNECTSHM_EXPORT 0
#endif  /* !defined(SGCONNECTSHM_EXPORT) */

#if SGCONNECTSHM_SHARED
#if SGCONNECTSHM_EXPORT
#define SGCONNECTSHM_API SG_DLLEXPORT
#else   /* SGCONNECTSHM_EXPORT */
#define SGCONNECTSHM_API SG_DLLIMPORT
#endif  /* SGCONNECTSHM_EXPORT */
#else   /* SGCONNECTSHM_SHARED */
#define SGCONNECTSHM_API
#endif  /* SGCONNECTSHM_SHARED */

/*******************************************************************************
* DLL export and import definitions - SGCore
*******************************************************************************/

#if !defined(SGCORE_SHARED)
#define SGCORE_SHARED 0
#endif  /* !defined(SGCORE_SHARED) */

#if !defined(SGCORE_EXPORT)
#define SGCORE_EXPORT 0
#endif  /* !defined(SGCORE_EXPORT) */

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
* DLL export and import definitions - SGCoreShm
*******************************************************************************/

#if !defined(SGCORESHM_SHARED)
#define SGCORESHM_SHARED 0
#endif  /* !defined(SGCORESHM_SHARED) */

#if !defined(SGCORESHM_EXPORT)
#define SGCORESHM_EXPORT 0
#endif  /* !defined(SGCORESHM_EXPORT) */

#if SGCORESHM_SHARED
#if SGCORESHM_EXPORT
#define SGCORESHM_API SG_DLLEXPORT
#else   /* SGCORESHM_EXPORT */
#define SGCORESHM_API SG_DLLIMPORT
#endif  /* SGCORESHM_EXPORT */
#else   /* SGCORESHM_SHARED */
#define SGCORESHM_API
#endif  /* SGCORESHM_SHARED */

/*******************************************************************************
* DLL export and import definitions - SGFakeShm
*******************************************************************************/

#if !defined(SGFAKESHM_SHARED)
#define SGFAKESHM_SHARED 0
#endif  /* !defined(SGFAKESHM_SHARED) */

#if !defined(SGFAKESHM_EXPORT)
#define SGFAKESHM_EXPORT 0
#endif  /* !defined(SGFAKESHM_EXPORT) */

#if SGFAKESHM_SHARED
#if SGFAKESHM_EXPORT
#define SGFAKESHM_API SG_DLLEXPORT
#else   /* SGFAKESHM_EXPORT */
#define SGFAKESHM_API SG_DLLIMPORT
#endif  /* SGFAKESHM_EXPORT */
#else   /* SGFAKESHM_SHARED */
#define SGFAKESHM_API
#endif  /* SGFAKESHM_SHARED */

/*******************************************************************************
* DLL export and import definitions - SGLog
*******************************************************************************/

#if !defined(SGLOG_SHARED)
#define SGLOG_SHARED 0
#endif  /* !defined(SGLOG_SHARED) */

#if !defined(SGLOG_EXPORT)
#define SGLOG_EXPORT 0
#endif  /* !defined(SGLOG_EXPORT) */

#if SGLOG_SHARED
#if SGLOG_EXPORT
#define SGLOG_API SG_DLLEXPORT
#else   /* SGLOG_EXPORT */
#define SGLOG_API SG_DLLIMPORT
#endif  /* SGLOG_EXPORT */
#else   /* SGLOG_SHARED */
#define SGLOG_API
#endif  /* SGLOG_SHARED */

/*******************************************************************************
* DLL export and import definitions - SGSerial
*******************************************************************************/

#if !defined(SGSERIAL_SHARED)
#define SGSERIAL_SHARED 0
#endif  /* !defined(SGSERIAL_SHARED) */

#if !defined(SGSERIAL_EXPORT)
#define SGSERIAL_EXPORT 0
#endif  /* !defined(SGSERIAL_EXPORT) */

#if SGSERIAL_SHARED
#if SGSERIAL_EXPORT
#define SGSERIAL_API SG_DLLEXPORT
#else   /* SGSERIAL_EXPORT */
#define SGSERIAL_API SG_DLLIMPORT
#endif  /* SGSERIAL_EXPORT */
#else   /* SGSERIAL_SHARED */
#define SGSERIAL_API
#endif  /* SGSERIAL_SHARED */

/*******************************************************************************
* Unreal Engine support
*******************************************************************************/

#if !defined(SENSEGLOVE_UNREAL_ENGINE_PLUGIN)
#define SENSEGLOVE_UNREAL_ENGINE_PLUGIN 0
#endif  /* !defined(SENSEGLOVE_UNREAL_ENGINE_PLUGIN) */
