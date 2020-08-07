# Core API
The SenseGlove Core API contains all kinematics and parsing algorithms needed to interface with SenseCom and to work with SenseGlove hardware. All versions share the same architecture, though their syntax will suit the programming language.

## SGConnect
A C++ library to setup and connect to SenseGlove devices in the background. Use this library if you don't want to have the SenseCom UI run in the background. 

## SGCoreCpp
Contains the C++ version of the Core API. Inside the incl folder are the header files, while the lib folder contains the .lib and .dll files for different operating systems, platforms and configurations (Debug, Release).
Further documentation is available in the folder.

## SGCoreCs
Contains the C# version of the Core API. The C# API makes use of the SGConnect.dll to interface with SenseCom. When building a C# application using SGCore for C#, ensure that the SGConnect.dll is inside your build folder as well.
The lib folder contains the .lib and .dll files for different operating systems, platforms and configurations (Debug, Release).
Further documentation is available in the folder.

# Working with the Core API
This guide assumes you were able to successfully add the appropriate version of the SenseGlove Core API into your project.

The most important features to know are;

- The Core API follows an Object Oriented Programming paradigm. Such objects are passed as arguments into (static) functions to make kinematic calculations.
- All functions and classes written by SenseGlove developers are part of the SGCore namespace.
- Each SenseGlove device class derives from an abstract SGDevice. These (sub)classes allow one to send haptics and receive data to and from a single device.
- The DeviceList class is used as the main interface to the SenseCom program. Use this class to check is the program is running and to get all SGDevices connected to the system. 


- The SGCore > SG namespace contains all classes and functions specific to the SenseGlove DK1, The SenseGlove class being the main interface for this hardware.
- The SenseGlove class has a number of static functions to access either all SenseGloves connected to the system, or the first connected SenseGlove, with an optional filter for left/right hands. Note that SenseGloves that are no longer connected to the system will not be retrieved in this way.﻿The IsRight() function allows one to check if an instance of SenseGlove belongs to a left- or right hand.
- Once you have a reference to a SenseGlove object / class, you are then able to send Haptic commands though a SendHaptics function. These functions allow one to set the level of force- and vibrotactile feedback for each finger. The hardware will play the indicated effect until a new command is received: for example, when a command is sent to vibrate the thumb, the hardware will continue to vibrate the thumb until a new command is sent which turns it off.
- The GetSensorData and GetGlovePose methods all return data based on the latest sensor values. They are given the appropriate output as a parameter, and will return true if nothing went wrong. It is also possible to calculate the GlovePose based on SensorData that was retrieved earlier.
- The GetHandPose outputs an estimate of the Hand pose, and requires a HandProfile to be given as a parameter, which contains information about the hand. The Solver parameter will determine how the GlovePose and HandProfile are used to calculate the HandPose. One can retrieve a basic HandProfile using HandProfile.Default(bool) specifying if it is used for a left or right hand.
