# SenseGlove API

This repository houses the Software APIs for SenseGlove Devices for C++ for Windows, Linux and Android.

The SenseGlove API consists of two libraries: **SGConnect** and **SGCore**. SGConnect is responsible for detecting and communicating with various SenseGlove Devices. Once initialized, any (VR) program on the system can communicate to SenseGlove devices using the **SGCore** library. On Desktop, we provide a program called **SenseCom** to both manage the SGConnect runtime and provide information on the status of one's devices. When using SenseCom, one does not need to integrate SGConnect. On Android devices, the SGConnect runtime should be managed within the app iself.

# Documentation

The latest documentation for this API can be found on [our documentation website](https://senseglove.gitlab.io/SenseGloveDocs/native/core-api-intro.html).

# Package Contents
The SenseGlove API is provided to you as a folder that contains everything one requires to begin software development. Before jumping into development, it is recommended to read through this section and the following Getting Started section.

## Android
Contains SGConnect.jar, used when compiling C++ for Android.

## Examples
Contains example code that makes use of the Core API to call various Glove functons. Also contains example executables to show certain Sense Glove features.

## Include
Contains Header (.hpp) files for the SGCore and SGConnect libraries: *include/SenseGlove/SGCore/* and *include/SenseGlove/SGConnect/* respectively.

## Lib
Contains binaries to both dynamically and statically link SGCore and SGConnect to your projects. 

## SenseCom
Contains binaries of SenseCom for the Windows, Linux, and Android platforms. Run this program in the background on Windows and Linux to interface with your SenseGlove hardware. On Android, it can be used to check your setup and tets your devices.


# Getting Started
With development on Windows and Linux
- Download the latest SenseGlove binaries from this repository.
- [Install the SenseCom software](https://senseglove.gitlab.io/SenseGloveDocs/sensecom/install-instructions.html). Optional, but reccomended.
- [Connect your SenseGlove Device to your PC](https://senseglove.gitlab.io/SenseGloveDocs/connecting-devices.html)
- Run the SenseCom executable, and wait for your glove to connect.
- Run the SGCoreClient executable built for your platform, it runs you though a few basic functions