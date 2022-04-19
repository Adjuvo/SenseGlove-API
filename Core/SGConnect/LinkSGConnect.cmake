# CMakeList file that will be copied to the SGConnect "source" directory
# It is meant to link the SGConnect C++ library to your (defined) project, and is NOT meant to be used by itself. 
# If you'd like to know how to link this file to your existing project, check out SGCoreCpp/examples

message(STATUS "Adding SGConnect C++ Library and Headers to this project...")

# SGConnect C++ root directory - Where did you install the Repository?
set (SGCONNECT_SOURCE_PATH ${CMAKE_CURRENT_LIST_DIR})
message(STATUS "SGConnect Source Code: ${SGCONNECT_SOURCE_PATH}")

#Add the incl/ directory - it has the header files. No platfrom dependent suff
include_directories("${SGCONNECT_SOURCE_PATH}/incl")

#Determine path to binaries based on platform
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(SGCONNECT_BINS "${SGCONNECT_SOURCE_PATH}/lib/linux")
ELSE()
	set(SGCONNECT_BINS "${SGCONNECT_SOURCE_PATH}/lib/win")
ENDIF()

#Find Debug Binary to link for Debug Configuration(s)
find_library(
    SGCONNECT_BIN_DEBUG
    NAMES SGConnect
    HINTS ${SGCONNECT_BINS}/Debug/)
mark_as_advanced(FORCE SGCONNECT_BIN_DEBUG) #hide it from the GUI

#Find Release Binary to link for Release Configuration(s)
find_library(
    SGCONNECT_BIN_RELEASE
    NAMES SGConnect
    HINTS ${SGCONNECT_BINS}/Release/)
mark_as_advanced(FORCE SGCONNECT_BIN_RELEASE) #hide it from the GUI

# Link the appropriate binaries based on configuration
target_link_libraries ( ${PROJECT_NAME}
    debug ${SGCONNECT_BIN_DEBUG}
    optimized ${SGCONNECT_BIN_RELEASE} )

# Useful for .dll libraries only:
# Ensure that the .dll file is copied to the output of your project
# Otherwise, you cannot run your builds (they expect the .dll to be there).
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "${SGCONNECT_BINS}/$<CONFIGURATION>/SGConnect.dll" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)
