# CMakeList to create a project with an executable, linked to the SGCore C++ Library as a .dll file

cmake_minimum_required (VERSION 3.8)
project ("SGCore_Example" VERSION 1.0.0)

# Our main project will be an executable with the main.cpp in the same folder as this file.
add_executable(${PROJECT_NAME} main.cpp)
#Make sure that it is the startup project if we're using VS
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

message(STATUS "Attempting to add the SGCoreCpp project at ${CMAKE_CURRENT_SOURCE_DIR}../../")
include(${CMAKE_CURRENT_SOURCE_DIR}/../../LinkSGCoreCpp.cmake) # Runs the module that include SGCoreCpp into this project
message(STATUS "Done!")