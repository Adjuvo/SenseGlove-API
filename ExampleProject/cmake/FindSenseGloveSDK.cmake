#
# author: Mamadou Babaei <mamadou@senseglove.com>
#
# (The MIT License)
#
# Copyright (c) 2020 - 2026 SenseGlove
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

#
# FindSenseGloveSDK.cmake
#
# Locates the SenseGlove SDK and exposes:
#
#   SenseGloveSDK_FOUND
#   SenseGloveSDK_INCLUDE_DIRS
#   SenseGloveSDK_LIBRARIES
#
# User variables (set BEFORE find_package):
#
#   SenseGloveSDK_ROOT
#   SenseGloveSDK_LINK_STATIC
#
#   SenseGloveSDK_TOOLCHAIN_ANDROID
#   SenseGloveSDK_TOOLCHAIN_LINUX
#   SenseGloveSDK_TOOLCHAIN_WINDOWS
#

include(FindPackageHandleStandardArgs)

################################################################################
# Locate SDK root
################################################################################

if(NOT SenseGloveSDK_ROOT)

    set(_sgsdk_candidate_roots
        "${CMAKE_CURRENT_LIST_DIR}/../third-party/SenseGloveSDK"
        "${CMAKE_SOURCE_DIR}/third-party/SenseGloveSDK"
    )

    foreach(_path ${_sgsdk_candidate_roots})

        if(EXISTS "${_path}/include/SenseGlove")
            set(SenseGloveSDK_ROOT "${_path}")
            break()
        endif()

    endforeach()

endif()

if(NOT SenseGloveSDK_ROOT)
    message(FATAL_ERROR "SenseGloveSDK not found. Set SenseGloveSDK_ROOT.")
endif()

################################################################################
# Options verification
################################################################################

message(STATUS "SenseGlove SDK Options:")
message(STATUS "  - ROOT              : ${SenseGloveSDK_ROOT}")
message(STATUS "  - LINK_STATIC       : ${SenseGloveSDK_LINK_STATIC}")
message(STATUS "  - TOOLCHAIN_ANDROID : ${SenseGloveSDK_TOOLCHAIN_ANDROID}")
message(STATUS "  - TOOLCHAIN_LINUX   : ${SenseGloveSDK_TOOLCHAIN_LINUX}")
message(STATUS "  - TOOLCHAIN_WINDOWS : ${SenseGloveSDK_TOOLCHAIN_WINDOWS}")

################################################################################
# Platform detection
################################################################################

if(ANDROID)
    set(_sgsdk_platform android)

elseif(WIN32)
    set(_sgsdk_platform windows)

elseif(UNIX)
    set(_sgsdk_platform linux)

else()
    message(FATAL_ERROR "Unsupported platform!")
endif()

################################################################################
# Toolchain detection
################################################################################

set(_sgsdk_toolchain_root
    "${SenseGloveSDK_ROOT}/lib/${_sgsdk_platform}"
)

# If user provided a toolchain explicitly, use it
if(_sgsdk_platform STREQUAL "android" AND SenseGloveSDK_TOOLCHAIN_ANDROID)
    set(_sgsdk_toolchain ${SenseGloveSDK_TOOLCHAIN_ANDROID})

elseif(_sgsdk_platform STREQUAL "linux" AND SenseGloveSDK_TOOLCHAIN_LINUX)
    set(_sgsdk_toolchain ${SenseGloveSDK_TOOLCHAIN_LINUX})

elseif(_sgsdk_platform STREQUAL "windows" AND SenseGloveSDK_TOOLCHAIN_WINDOWS)
    set(_sgsdk_toolchain ${SenseGloveSDK_TOOLCHAIN_WINDOWS})

else()

    # Auto-detect newest toolchain
    file(GLOB _sgsdk_toolchain_dirs
        RELATIVE "${_sgsdk_toolchain_root}"
        "${_sgsdk_toolchain_root}/v*"
        "${_sgsdk_toolchain_root}/r*"
    )

    if(NOT _sgsdk_toolchain_dirs)
        message(FATAL_ERROR
            "No SenseGloveSDK toolchains found in ${_sgsdk_toolchain_root}"
        )
    endif()

    list(SORT _sgsdk_toolchain_dirs)
    list(GET _sgsdk_toolchain_dirs -1 _sgsdk_toolchain)

endif()

################################################################################
# Architecture detection
################################################################################

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64"
    OR CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64"
    OR CMAKE_SYSTEM_PROCESSOR STREQUAL "ARM64")
    set(_sgsdk_arch aarch64)
else()
    set(_sgsdk_arch x86-64)
endif()

################################################################################
# Library directory
################################################################################

set(_sgsdk_lib_dir_debug
    "${SenseGloveSDK_ROOT}/lib/${_sgsdk_platform}/${_sgsdk_toolchain}/${_sgsdk_arch}/debug"
)

set(_sgsdk_lib_dir_release
    "${SenseGloveSDK_ROOT}/lib/${_sgsdk_platform}/${_sgsdk_toolchain}/${_sgsdk_arch}/release"
)

if(NOT EXISTS "${_sgsdk_lib_dir_debug}")
    message(FATAL_ERROR
        "SenseGloveSDK libraries not found:\n${_sgsdk_lib_dir_debug}"
    )
endif()

if(NOT EXISTS "${_sgsdk_lib_dir_release}")
    message(FATAL_ERROR
        "SenseGloveSDK libraries not found:\n${_sgsdk_lib_dir_release}"
    )
endif()

################################################################################
# Collect libraries
################################################################################

set(_sgsdk_libs)

if(SenseGloveSDK_LINK_STATIC)

    if(WIN32)

        set(_sgsdk_libs_debug
            ${_sgsdk_lib_dir_debug}/flatbuffers.lib
            ${_sgsdk_lib_dir_debug}/fmtd.lib
            ${_sgsdk_lib_dir_debug}/logurud.lib
            ${_sgsdk_lib_dir_debug}/nng.lib
            ${_sgsdk_lib_dir_debug}/serial.lib

            ${_sgsdk_lib_dir_debug}/sgcommon.lib
            ${_sgsdk_lib_dir_debug}/sglog.lib
            ${_sgsdk_lib_dir_debug}/sgserial.lib
            ${_sgsdk_lib_dir_debug}/sgconnectshm.lib
            ${_sgsdk_lib_dir_debug}/sgconnect.lib
            ${_sgsdk_lib_dir_debug}/sgcoreshm.lib
            ${_sgsdk_lib_dir_debug}/sgcore.lib
        )

        set(_sgsdk_libs_release
            ${_sgsdk_lib_dir_release}/flatbuffers.lib
            ${_sgsdk_lib_dir_release}/fmt.lib
            ${_sgsdk_lib_dir_release}/loguru.lib
            ${_sgsdk_lib_dir_release}/nng.lib
            ${_sgsdk_lib_dir_release}/serial.lib

            ${_sgsdk_lib_dir_release}/sgcommon.lib
            ${_sgsdk_lib_dir_release}/sglog.lib
            ${_sgsdk_lib_dir_release}/sgserial.lib
            ${_sgsdk_lib_dir_release}/sgconnectshm.lib
            ${_sgsdk_lib_dir_release}/sgconnect.lib
            ${_sgsdk_lib_dir_release}/sgcoreshm.lib
            ${_sgsdk_lib_dir_release}/sgcore.lib
        )

    else()

        set(_sgsdk_libs_debug
            ${_sgsdk_lib_dir_debug}/libflatbuffers.a
            ${_sgsdk_lib_dir_debug}/libfmtd.a
            ${_sgsdk_lib_dir_debug}/liblogurud.a
            ${_sgsdk_lib_dir_debug}/libnng.a
            ${_sgsdk_lib_dir_debug}/libserial.a

            ${_sgsdk_lib_dir_debug}/libsgcommon.a
            ${_sgsdk_lib_dir_debug}/libsglog.a
            ${_sgsdk_lib_dir_debug}/libsgserial.a
            ${_sgsdk_lib_dir_debug}/libsgconnectshm.a
            ${_sgsdk_lib_dir_debug}/libsgconnect.a
            ${_sgsdk_lib_dir_debug}/libsgcoreshm.a
            ${_sgsdk_lib_dir_debug}/libsgcore.a
        )

        set(_sgsdk_libs_release
            ${_sgsdk_lib_dir_release}/libflatbuffers.a
            ${_sgsdk_lib_dir_release}/libfmt.a
            ${_sgsdk_lib_dir_release}/libloguru.a
            ${_sgsdk_lib_dir_release}/libnng.a
            ${_sgsdk_lib_dir_release}/libserial.a

            ${_sgsdk_lib_dir_release}/libsgcommon.a
            ${_sgsdk_lib_dir_release}/libsglog.a
            ${_sgsdk_lib_dir_release}/libsgserial.a
            ${_sgsdk_lib_dir_release}/libsgconnectshm.a
            ${_sgsdk_lib_dir_release}/libsgconnect.a
            ${_sgsdk_lib_dir_release}/libsgcoreshm.a
            ${_sgsdk_lib_dir_release}/libsgcore.a
        )

    endif()

else()

    if(WIN32)

        set(_sgsdk_libs_debug
            "${_sgsdk_lib_dir_debug}/sgcore.lib"
            "${_sgsdk_lib_dir_debug}/sgconnect.lib"
        )

        set(_sgsdk_libs_release
            "${_sgsdk_lib_dir_release}/sgcore.lib"
            "${_sgsdk_lib_dir_release}/sgconnect.lib"
        )

    else()

        set(_sgsdk_libs_debug
            "${_sgsdk_lib_dir_debug}/libsgcore.so"
            "${_sgsdk_lib_dir_debug}/libsgconnect.so"
        )

        set(_sgsdk_libs_release
            "${_sgsdk_lib_dir_release}/libsgcore.so"
            "${_sgsdk_lib_dir_release}/libsgconnect.so"
        )

    endif()

endif()

set(_sgsdk_libs
    "$<$<CONFIG:Debug>:${_sgsdk_libs_debug}>"
    "$<$<CONFIG:Release>:${_sgsdk_libs_release}>"
    "$<$<CONFIG:RelWithDebInfo>:${_sgsdk_libs_release}>"
    "$<$<CONFIG:MinSizeRel>:${_sgsdk_libs_release}>"
)

################################################################################
# Collect Rust libraries
################################################################################

if(NOT ANDROID AND SenseGloveSDK_LINK_STATIC)

    set(_sgsdk_rust_dir_debug
        "${SenseGloveSDK_ROOT}/lib/${_sgsdk_platform}/rustc/${_sgsdk_arch}/debug"
    )

    set(_sgsdk_rust_dir_release
        "${SenseGloveSDK_ROOT}/lib/${_sgsdk_platform}/rustc/${_sgsdk_arch}/release"
    )

    set(_rust_libs_debug)
    set(_rust_libs_release)

    if(EXISTS "${_sgsdk_rust_dir_debug}")

        if(WIN32)
            set(_rust_libs_debug
                ${_sgsdk_rust_dir_debug}/sgble.lib
            )
        else()
            set(_rust_libs_debug
                ${_sgsdk_rust_dir_debug}/libsgble.a
            )
        endif()

    endif()

    if(EXISTS "${_sgsdk_rust_dir_release}")

        if(WIN32)
            set(_rust_libs_release
                ${_sgsdk_rust_dir_release}/sgble.lib
            )
        else()
            set(_rust_libs_release
                ${_sgsdk_rust_dir_release}/libsgble.a
            )
        endif()

    endif()

    if(_rust_libs_debug OR _rust_libs_release)

        list(APPEND _sgsdk_libs
            "$<$<CONFIG:Debug>:${_rust_libs_debug}>"
            "$<$<CONFIG:Release>:${_rust_libs_release}>"
            "$<$<CONFIG:RelWithDebInfo>:${_rust_libs_release}>"
            "$<$<CONFIG:MinSizeRel>:${_rust_libs_release}>"
        )

    endif()

endif()

################################################################################
# Export variables
################################################################################

set(SenseGloveSDK_INCLUDE_DIRS
    "${SenseGloveSDK_ROOT}/include"
)

set(SenseGloveSDK_LIBRARIES ${_sgsdk_libs})

if(NOT TARGET SenseGloveSDK::SenseGloveSDK)

    add_library(SenseGloveSDK::SenseGloveSDK INTERFACE IMPORTED GLOBAL)

    target_include_directories(SenseGloveSDK::SenseGloveSDK
        INTERFACE
            "${SenseGloveSDK_INCLUDE_DIRS}"
    )

    target_link_libraries(SenseGloveSDK::SenseGloveSDK
        INTERFACE
            ${SenseGloveSDK_LIBRARIES}
    )

    if(_sgsdk_platform STREQUAL "linux")

        find_package(Threads REQUIRED)

        target_link_libraries(SenseGloveSDK::SenseGloveSDK
            INTERFACE
                Threads::Threads
                rt
        )

    endif()

    if(_sgsdk_platform STREQUAL "windows")

        target_link_libraries(SenseGloveSDK::SenseGloveSDK
            INTERFACE
                bcrypt
                ntdll
                propsys
                runtimeobject
                userenv
                ws2_32
                setupapi
        )

    endif()

endif()

################################################################################
# Configuration verification
################################################################################

message(STATUS "SenseGlove SDK Configuration:")
message(STATUS "  - Architecture : ${_sgsdk_arch}")
message(STATUS "  - Platform     : ${_sgsdk_platform}")
message(STATUS "  - Toolchain    : ${_sgsdk_toolchain}")
message(STATUS "  - Include Dirs : ${SenseGloveSDK_INCLUDE_DIRS}")
message(STATUS "  - Libraries    : ${SenseGloveSDK_LIBRARIES}")

################################################################################
# Result
################################################################################

find_package_handle_standard_args(
    SenseGloveSDK
    REQUIRED_VARS
        SenseGloveSDK_ROOT
        SenseGloveSDK_INCLUDE_DIRS
        SenseGloveSDK_LIBRARIES
)

mark_as_advanced(
    SenseGloveSDK_ROOT
    SenseGloveSDK_LINK_STATIC
    SenseGloveSDK_TOOLCHAIN_ANDROID
    SenseGloveSDK_TOOLCHAIN_LINUX
    SenseGloveSDK_TOOLCHAIN_WINDOWS
)
