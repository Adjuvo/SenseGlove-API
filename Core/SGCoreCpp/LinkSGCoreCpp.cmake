# CMakeList file that will be copied to the SGCoreCpp "source" directory
# It is meant to link the SGCore C++ library to your (defined) project, and is NOT meant to be used by itself. 
# If you'd like to know how to link this file to your existing project, check out the CMakeLists.txt in the examples folder.

message(STATUS "Adding SGCore C++ Library and Headers to this project...")

# SGCore C++ root directory - Where did you install the Repository?
set (SGCORE_SOURCE_PATH ${CMAKE_CURRENT_LIST_DIR}) #I used find_path(SGCORE_SOURCE_PATH SGCore_SOURCE "SGCoreCpp") before.
message(STATUS "SGCoreCpp Source Code: ${SGCORE_SOURCE_PATH}")

#Add the incl/ directory - it has the header files. No platfrom dependent suff
include_directories("${SGCORE_SOURCE_PATH}/incl")

#Determine path to binaries based on platform
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(SGCORE_BINS "${SGCORE_SOURCE_PATH}/lib/linux")
ELSE()
	set(SGCORE_BINS "${SGCORE_SOURCE_PATH}/lib/win")
ENDIF()

#Find Debug Binary to link for Debug Configuration(s)
find_library(
    SGCORE_BIN_DEBUG
    NAMES SGCoreCpp
    HINTS ${SGCORE_BINS}/Debug/)
mark_as_advanced(FORCE SGCORE_BIN_DEBUG) #hide it from the GUI

#Find Release Binary to link for Release Configuration(s)
find_library(
    SGCORE_BIN_RELEASE
    NAMES SGCoreCpp
    HINTS ${SGCORE_BINS}/Release/)
mark_as_advanced(FORCE SGCORE_BIN_RELEASE) #hide it from the GUI

# Link the appropriate binaries based on configuration
target_link_libraries ( ${PROJECT_NAME}
    debug ${SGCORE_BIN_DEBUG}
    optimized ${SGCORE_BIN_RELEASE} )

# Useful for .dll libraries only:
# Ensure that the .dll file is copied to the output of your project
# Otherwise, you cannot run your builds (they expect the .dll to be there).
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "${SGCORE_BINS}/$<CONFIGURATION>/SGCoreCpp.dll" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)
