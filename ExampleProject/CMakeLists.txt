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


################################################################################
# Generic CMake / Build Settings
################################################################################

cmake_minimum_required(VERSION 3.21...3.31)

project(SenseGloveSDKExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################################################################################
# Disable RTTI/Exceptions
################################################################################

# By default, the SenseGlove SDK binaries are built with `Exceptions` and `RTTI`
# disabled. On some compilers and toolchains, these settings can influence C++
# symbol name mangling and the linker’s expectations when resolving symbols. As
# a result, projects compiled with different `Exceptions` or `RTTI` settings may
# encounter linker errors when linking against the SDK.

# If you run into such issues, please feel free to contact us. We can provide
# SDK binaries built with `Exceptions` and `RTTI` settings that match your
# project's configuration.

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")

    # Disable C++ exceptions
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>)

    # Disable RTTI
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

    # Disable C++ exceptions
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/EHs-c->)

    # Disable RTTI
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/GR->)

endif()

################################################################################
# SenseGlove SDK configuration
################################################################################

# These should be set before making a call to:
# find_package(SenseGloveSDK REQUIRED)

# Static (.lib/.a) vs dynamic (.dll/.so) linking
# default is OFF
set(SenseGloveSDK_LINK_STATIC ON)

# Toolchains
# If left empty, tries to detect the latest toolchain on each platform
set(SenseGloveSDK_TOOLCHAIN_ANDROID r27c)
set(SenseGloveSDK_TOOLCHAIN_LINUX   v26)
set(SenseGloveSDK_TOOLCHAIN_WINDOWS v143)

################################################################################
# Find modules
################################################################################

# Tell CMake where our Find modules live
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find SenseGlove SDK
find_package(SenseGloveSDK REQUIRED)

if(NOT SenseGloveSDK_FOUND)
    message(FATAL_ERROR "Could not find the SenseGloveSDK!")
endif()

################################################################################
# Helper function to create example apps
################################################################################

function(add_senseglove_example TARGET_NAME TARGET_DIR)

    add_executable(${TARGET_NAME}
        ${TARGET_DIR}/main.cpp
    )

    target_include_directories(${TARGET_NAME}
        PRIVATE
            SenseGloveSDK::SenseGloveSDK
    )

    target_link_libraries(${TARGET_NAME}
        PRIVATE
            SenseGloveSDK::SenseGloveSDK
    )

endfunction()

################################################################################
# Applications
################################################################################

add_senseglove_example(
    sgconnect-client-simple
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sgconnect-client-simple
)

add_senseglove_example(
    sgcore-client-no-sensecom
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sgcore-client-no-sensecom
)

add_senseglove_example(
    sgcore-client-simple
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sgcore-client-simple
)
