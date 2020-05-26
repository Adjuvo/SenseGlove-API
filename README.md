# SenseGlove API

This repository houses the Software APIs for SenseGlove Devices for C++ and C# development for Windows and MacOS.

The Sense Glove Core API is the combination of a **Communications Program** named "SenseCom", and a **Core Library**, all running on the same computer. Any (VR) program using the Core Library can exchange data with any **SenseGlove Device** through the Communications Program. Without SenseCom, the Core API will not detect any devices. 

## Package Contents
The SenseGlove API is provided to you as a folder that contains everything one requires to begin software development. Before jumping into development, it is recommended to read through this section and the following Getting Started section.

## SenseCom
Contains executable versions of SenseCom for the Windows and Linux platform. Run this program in the background to interface with your SenseGlove hardware.

## Core
Contains folders for different programming languages and operating systems to access SenseCom data, as well as guides on how to import the API into your project.
The Cpp folder contains a dynamic library for C++, as well as a folder containing the Header files to import into your classes.
The Cs folder contains a dynamic library for C# projects. This API is built on the .NET Framework, and therefore works on Windows only.

## Plugins
Contains plugins to add Sense Glove into other engines, such as the Unity Engine.

## Examples
Contains example projects that make use of the Core API to show how integration would work. Also contains example executables to show certain Sense Glove features.

# Getting Started
Plug in one or more SenseGloves into your desktop computer as per the guidelines on page 6 of your SenseGlove user manual.


Navigate to the SenseCom folder in the SenseGloveAPI package and run the version that matches your platform. For Linux users; the SenseCom program should have its 'allow to run as a program' property enabled. Upon startup, you will be met with a small UI:

While the icon(s) are not filled, the program has not yet detected any Sense Gloves. When the icon is filled, the device has been detected. Use this UI to verify that all Sense Gloves you have plugged in are recognized. Note that it may take up to 10 seconds for your system to detect the Hardware and install the appropriate drivers before SenseCom is able to detect anything.