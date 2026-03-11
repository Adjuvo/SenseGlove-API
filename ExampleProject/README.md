# SenseGlove C++ SDK Usage Example

This repository provides a **minimal CMake integration example** for the **SenseGlove SDK**.
It demonstrates how to link against **SGCore** and **SGConnect** from a custom CMake project on **Linux** and **Windows**.

The project includes:

* A reusable **`FindSenseGloveSDK.cmake`** module
* Three **minimal C++ examples** demonstating how to use `SGConnect` and `SGCore` libraries
* **CMake configuration scripts**
* **Build scripts for Linux and Windows**

These examples are intended to help developers quickly integrate the SenseGlove SDK into their own CMake-based projects.

---

# Overview

This repository demonstrates:

* How to **locate the SenseGlove SDK using CMake**
* How to **link against SGCore and SGConnect**
* How to structure a **portable CMake project**
* How to build and run examples on **Linux and Windows**

The examples intentionally keep the code small and focused so that the build configuration remains easy to understand and reuse.

---

# Repository Structure

Below is the directory structure of the repository and a brief description of each component.

```
.
├── cmake
│   └── FindSenseGloveSDK.cmake
├── CMakeLists.txt
├── linux-build-debug.sh
├── linux-build-release.sh
├── linux-clean.sh
├── linux-configure.sh
├── README.md
├── src
│   ├── sgconnect-client-simple
│   │   └── main.cpp
│   ├── sgcore-client-no-sensecom
│   │   └── main.cpp
│   └── sgcore-client-simple
│       └── main.cpp
├── third-party
│   └── SenseGloveSDK
├── windows-build-debug.cmd
├── windows-build-release.cmd
├── windows-clean.cmd
└── windows-configure.cmd
```



## SenseGlove SDK Directory Structure

The SenseGlove SDK is typically organized using a directory and file structure similar to the following:

```
.
├── android
├── include
│   └── SenseGlove
│       ├── BLE
│       ├── Common
│       ├── Connect
│       ├── Core
│       └── Log
└── lib
    ├── android
    │   ├── r25b
    │   │   ├── aarch64
    │   │   │   ├── debug
    │   │   │   └── release
    │   │   └── x86-64
    │   │       ├── debug
    │   │       └── release
    │   └── r27c
    │       ├── aarch64
    │       │   ├── debug
    │       │   └── release
    │       └── x86-64
    │           ├── debug
    │           └── release
    ├── linux
    │   ├── rustc
    │   │   ├── aarch64
    │   │   │   ├── debug
    │   │   │   └── release
    │   │   └── x86-64
    │   │       ├── debug
    │   │       └── release
    │   ├── v23
    │   │   ├── aarch64
    │   │   │   ├── debug
    │   │   │   └── release
    │   │   └── x86-64
    │   │       ├── debug
    │   │       └── release
    │   ├── v25
    │   │   ├── aarch64
    │   │   │   ├── debug
    │   │   │   └── release
    │   │   └── x86-64
    │   │       ├── debug
    │   │       └── release
    │   └── v26
    │       ├── aarch64
    │       │   ├── debug
    │       │   └── release
    │       └── x86-64
    │           ├── debug
    │           └── release
    └── windows
        ├── rustc
        │   └── x86-64
        │       ├── debug
        │       └── release
        └── v143
            └── x86-64
                ├── debug
                └── release
```

Once the SDK is placed in the directory expected by the build system, the SenseGlove SDK directory structure will typically look like the following:

```
├── third-party
│   └── SenseGloveSDK
│       ├── android
│       │   └── sgconnect.jar
│       ├── include
│       │   └── SenseGlove
│       │       ├── BLE
│       │       │   ├── sgble.h
│       │       │   ├── sgble.hpp
│       │       │   └── SGBLExx.hpp
│       │       ├── Common
│       │       │   ├── FloatUtils.hpp
│       │       │   ├── HybridMutex.hpp
│       │       │   ├── HybridSharedMutex.hpp
│       │       │   ├── Intrinsics.hpp
│       │       │   ├── MathDefines.hpp
│       │       │   └── Platform.hpp
│       │       ├── Connect
│       │       │   ├── Android.hpp
│       │       │   ├── BleInfo.hpp
│       │       │   ├── BleUtil.hpp
│       │       │   ├── ConnectionData.hpp
│       │       │   ├── ConnectionFactory.hpp
│       │       │   ├── Connection.hpp
│       │       │   ├── ConnectionsTracker.hpp
│       │       │   ├── ConnectionTester.hpp
│       │       │   ├── Debugger.hpp
│       │       │   ├── DeviceScanner.hpp
│       │       │   ├── EFWErrorCodes.hpp
│       │       │   ├── ExitCodes.hpp
│       │       │   ├── FirmwareUploader.hpp
│       │       │   ├── HapticResponse.hpp
│       │       │   ├── IdResponse.hpp
│       │       │   ├── IpcCommand.hpp
│       │       │   ├── NewSGDevice.hpp
│       │       │   ├── Nova2BleDevice.hpp
│       │       │   ├── PortInfo.hpp
│       │       │   ├── SerialConnection.hpp
│       │       │   ├── SerialPorts.hpp
│       │       │   ├── SGBleDevice.hpp
│       │       │   ├── SGConnect.hpp
│       │       │   ├── SGDevice.hpp
│       │       │   ├── StringUtils.hpp
│       │       │   ├── TestingState.hpp
│       │       │   └── TransmissionMode.hpp
│       │       ├── Core
│       │       │   ├── Anatomy.hpp
│       │       │   ├── Android.hpp
│       │       │   ├── BasicHandModel.hpp
│       │       │   ├── BetaDevice.hpp
│       │       │   ├── BuzzCommand.hpp
│       │       │   ├── CalibrationDataPoint.hpp
│       │       │   ├── Communications.hpp
│       │       │   ├── ConnectionStatus.hpp
│       │       │   ├── CustomWaveform.hpp
│       │       │   ├── CVHandDataSmoother.hpp
│       │       │   ├── CVHandLayer.hpp
│       │       │   ├── CVHandTrackingData.hpp
│       │       │   ├── CVKinematics.hpp
│       │       │   ├── CVProcessedHandData.hpp
│       │       │   ├── DeviceList.hpp
│       │       │   ├── DeviceModel.hpp
│       │       │   ├── DeviceTypes.hpp
│       │       │   ├── Environment.hpp
│       │       │   ├── FileIO.hpp
│       │       │   ├── FingerCommand.hpp
│       │       │   ├── Fingers.hpp
│       │       │   ├── ForceFeedbackCommand.hpp
│       │       │   ├── HandInterpolator.hpp
│       │       │   ├── HandLayer.hpp
│       │       │   ├── HandPose.hpp
│       │       │   ├── HandProfile.hpp
│       │       │   ├── HapticChannelInfo.hpp
│       │       │   ├── HapticGloveCalibrationCheck.hpp
│       │       │   ├── HapticGloveCalibrationSequence.hpp
│       │       │   ├── HapticGloveCommandBuffer.hpp
│       │       │   ├── HapticGloveHandProfiles.hpp
│       │       │   ├── HapticGlove.hpp
│       │       │   ├── HapticGloveQuickCalibration.hpp
│       │       │   ├── InterpolationSet.hpp
│       │       │   ├── JointKinematics.hpp
│       │       │   ├── Library.hpp
│       │       │   ├── NormalizationState.hpp
│       │       │   ├── Nova2Glove.hpp
│       │       │   ├── Nova2GloveSensorData.hpp
│       │       │   ├── NovaGloveCalibration.hpp
│       │       │   ├── NovaGloveHandProfile.hpp
│       │       │   ├── NovaGloveHapticEncoder.hpp
│       │       │   ├── NovaGloveHapticStream.hpp
│       │       │   ├── NovaGlove.hpp
│       │       │   ├── NovaGloveInfo.hpp
│       │       │   ├── NovaGloveSensorData.hpp
│       │       │   ├── NovaGloveVars.hpp
│       │       │   ├── OnDiskCalibration.hpp
│       │       │   ├── Quat.hpp
│       │       │   ├── SenseCom.hpp
│       │       │   ├── SenseGloveHandProfile.hpp
│       │       │   ├── SenseGloveHapticStream.hpp
│       │       │   ├── SenseGlove.hpp
│       │       │   ├── SenseGloveInfo.hpp
│       │       │   ├── SenseGlovePose.hpp
│       │       │   ├── SenseGloveSensorData.hpp
│       │       │   ├── SenseGloveSensorNormalizer.hpp
│       │       │   ├── SenseGloveThumperCommand.hpp
│       │       │   ├── SenseGloveVars.hpp
│       │       │   ├── SensorNormalization.hpp
│       │       │   ├── SensorRange.hpp
│       │       │   ├── Serializer.hpp
│       │       │   ├── SGDevice.hpp
│       │       │   ├── StringUtils.hpp
│       │       │   ├── ThresholdCommand.hpp
│       │       │   ├── ThumperCommand.hpp
│       │       │   ├── TimedBuzzCommand.hpp
│       │       │   ├── TimedThumpCommand.hpp
│       │       │   ├── Tracking.hpp
│       │       │   ├── Values.hpp
│       │       │   └── Vect3D.hpp
│       │       └── Log
│       │           ├── SGLogExportedFunctions.hpp
│       │           ├── SGLogFfiTypes.hpp
│       │           └── SGLog.hpp
│       └── lib
│           ├── android
│           │   ├── r25b
│           │   │   ├── aarch64
│           │   │   │   ├── debug
│           │   │   │   │   ├── libfmtd.a
│           │   │   │   │   ├── liblogurud.a
│           │   │   │   │   ├── libserial.a
│           │   │   │   │   ├── libsgcommon.a
│           │   │   │   │   ├── libsgconnect.a
│           │   │   │   │   ├── libsgconnectshm.a
│           │   │   │   │   ├── libsgconnect.so
│           │   │   │   │   ├── libsgcore.a
│           │   │   │   │   ├── libsgcoreshm.a
│           │   │   │   │   ├── libsgcore.so
│           │   │   │   │   ├── libsglog.a
│           │   │   │   │   └── libsgserial.a
│           │   │   │   └── release
│           │   │   │       ├── libfmt.a
│           │   │   │       ├── libloguru.a
│           │   │   │       ├── libserial.a
│           │   │   │       ├── libsgcommon.a
│           │   │   │       ├── libsgconnect.a
│           │   │   │       ├── libsgconnectshm.a
│           │   │   │       ├── libsgconnect.so
│           │   │   │       ├── libsgcore.a
│           │   │   │       ├── libsgcoreshm.a
│           │   │   │       ├── libsgcore.so
│           │   │   │       ├── libsglog.a
│           │   │   │       └── libsgserial.a
│           │   │   └── x86-64
│           │   │       ├── debug
│           │   │       │   ├── libfmtd.a
│           │   │       │   ├── liblogurud.a
│           │   │       │   ├── libserial.a
│           │   │       │   ├── libsgcommon.a
│           │   │       │   ├── libsgconnect.a
│           │   │       │   ├── libsgconnectshm.a
│           │   │       │   ├── libsgconnect.so
│           │   │       │   ├── libsgcore.a
│           │   │       │   ├── libsgcoreshm.a
│           │   │       │   ├── libsgcore.so
│           │   │       │   ├── libsglog.a
│           │   │       │   └── libsgserial.a
│           │   │       └── release
│           │   │           ├── libfmt.a
│           │   │           ├── libloguru.a
│           │   │           ├── libserial.a
│           │   │           ├── libsgcommon.a
│           │   │           ├── libsgconnect.a
│           │   │           ├── libsgconnectshm.a
│           │   │           ├── libsgconnect.so
│           │   │           ├── libsgcore.a
│           │   │           ├── libsgcoreshm.a
│           │   │           ├── libsgcore.so
│           │   │           ├── libsglog.a
│           │   │           └── libsgserial.a
│           │   └── r27c
│           │       ├── aarch64
│           │       │   ├── debug
│           │       │   │   ├── libfmtd.a
│           │       │   │   ├── liblogurud.a
│           │       │   │   ├── libserial.a
│           │       │   │   ├── libsgcommon.a
│           │       │   │   ├── libsgconnect.a
│           │       │   │   ├── libsgconnectshm.a
│           │       │   │   ├── libsgconnect.so
│           │       │   │   ├── libsgcore.a
│           │       │   │   ├── libsgcoreshm.a
│           │       │   │   ├── libsgcore.so
│           │       │   │   ├── libsglog.a
│           │       │   │   └── libsgserial.a
│           │       │   └── release
│           │       │       ├── libfmt.a
│           │       │       ├── libloguru.a
│           │       │       ├── libserial.a
│           │       │       ├── libsgcommon.a
│           │       │       ├── libsgconnect.a
│           │       │       ├── libsgconnectshm.a
│           │       │       ├── libsgconnect.so
│           │       │       ├── libsgcore.a
│           │       │       ├── libsgcoreshm.a
│           │       │       ├── libsgcore.so
│           │       │       ├── libsglog.a
│           │       │       └── libsgserial.a
│           │       └── x86-64
│           │           ├── debug
│           │           │   ├── libfmtd.a
│           │           │   ├── liblogurud.a
│           │           │   ├── libserial.a
│           │           │   ├── libsgcommon.a
│           │           │   ├── libsgconnect.a
│           │           │   ├── libsgconnectshm.a
│           │           │   ├── libsgconnect.so
│           │           │   ├── libsgcore.a
│           │           │   ├── libsgcoreshm.a
│           │           │   ├── libsgcore.so
│           │           │   ├── libsglog.a
│           │           │   └── libsgserial.a
│           │           └── release
│           │               ├── libfmt.a
│           │               ├── libloguru.a
│           │               ├── libserial.a
│           │               ├── libsgcommon.a
│           │               ├── libsgconnect.a
│           │               ├── libsgconnectshm.a
│           │               ├── libsgconnect.so
│           │               ├── libsgcore.a
│           │               ├── libsgcoreshm.a
│           │               ├── libsgcore.so
│           │               ├── libsglog.a
│           │               └── libsgserial.a
│           ├── linux
│           │   ├── rustc
│           │   │   ├── aarch64
│           │   │   │   ├── debug
│           │   │   │   │   └── libsgble.a
│           │   │   │   └── release
│           │   │   │       └── libsgble.a
│           │   │   └── x86-64
│           │   │       ├── debug
│           │   │       │   └── libsgble.a
│           │   │       └── release
│           │   │           └── libsgble.a
│           │   ├── v23
│           │   │   ├── aarch64
│           │   │   │   ├── debug
│           │   │   │   │   ├── libflatbuffers.a
│           │   │   │   │   ├── libfmtd.a
│           │   │   │   │   ├── liblogurud.a
│           │   │   │   │   ├── libnng.a
│           │   │   │   │   ├── libserial.a
│           │   │   │   │   ├── libsgcommon.a
│           │   │   │   │   ├── libsgconnect.a
│           │   │   │   │   ├── libsgconnectshm.a
│           │   │   │   │   ├── libsgconnect.so
│           │   │   │   │   ├── libsgcore.a
│           │   │   │   │   ├── libsgcoreshm.a
│           │   │   │   │   ├── libsgcore.so
│           │   │   │   │   ├── libsglog.a
│           │   │   │   │   └── libsgserial.a
│           │   │   │   └── release
│           │   │   │       ├── libflatbuffers.a
│           │   │   │       ├── libfmt.a
│           │   │   │       ├── libloguru.a
│           │   │   │       ├── libnng.a
│           │   │   │       ├── libserial.a
│           │   │   │       ├── libsgcommon.a
│           │   │   │       ├── libsgconnect.a
│           │   │   │       ├── libsgconnectshm.a
│           │   │   │       ├── libsgconnect.so
│           │   │   │       ├── libsgcore.a
│           │   │   │       ├── libsgcoreshm.a
│           │   │   │       ├── libsgcore.so
│           │   │   │       ├── libsglog.a
│           │   │   │       └── libsgserial.a
│           │   │   └── x86-64
│           │   │       ├── debug
│           │   │       │   ├── libflatbuffers.a
│           │   │       │   ├── libfmtd.a
│           │   │       │   ├── liblogurud.a
│           │   │       │   ├── libnng.a
│           │   │       │   ├── libserial.a
│           │   │       │   ├── libsgcommon.a
│           │   │       │   ├── libsgconnect.a
│           │   │       │   ├── libsgconnectshm.a
│           │   │       │   ├── libsgconnect.so
│           │   │       │   ├── libsgcore.a
│           │   │       │   ├── libsgcoreshm.a
│           │   │       │   ├── libsgcore.so
│           │   │       │   ├── libsglog.a
│           │   │       │   └── libsgserial.a
│           │   │       └── release
│           │   │           ├── libflatbuffers.a
│           │   │           ├── libfmt.a
│           │   │           ├── libloguru.a
│           │   │           ├── libnng.a
│           │   │           ├── libserial.a
│           │   │           ├── libsgcommon.a
│           │   │           ├── libsgconnect.a
│           │   │           ├── libsgconnectshm.a
│           │   │           ├── libsgconnect.so
│           │   │           ├── libsgcore.a
│           │   │           ├── libsgcoreshm.a
│           │   │           ├── libsgcore.so
│           │   │           ├── libsglog.a
│           │   │           └── libsgserial.a
│           │   ├── v25
│           │   │   ├── aarch64
│           │   │   │   ├── debug
│           │   │   │   │   ├── libflatbuffers.a
│           │   │   │   │   ├── libfmtd.a
│           │   │   │   │   ├── liblogurud.a
│           │   │   │   │   ├── libnng.a
│           │   │   │   │   ├── libserial.a
│           │   │   │   │   ├── libsgcommon.a
│           │   │   │   │   ├── libsgconnect.a
│           │   │   │   │   ├── libsgconnectshm.a
│           │   │   │   │   ├── libsgconnect.so
│           │   │   │   │   ├── libsgcore.a
│           │   │   │   │   ├── libsgcoreshm.a
│           │   │   │   │   ├── libsgcore.so
│           │   │   │   │   ├── libsglog.a
│           │   │   │   │   └── libsgserial.a
│           │   │   │   └── release
│           │   │   │       ├── libflatbuffers.a
│           │   │   │       ├── libfmt.a
│           │   │   │       ├── libloguru.a
│           │   │   │       ├── libnng.a
│           │   │   │       ├── libserial.a
│           │   │   │       ├── libsgcommon.a
│           │   │   │       ├── libsgconnect.a
│           │   │   │       ├── libsgconnectshm.a
│           │   │   │       ├── libsgconnect.so
│           │   │   │       ├── libsgcore.a
│           │   │   │       ├── libsgcoreshm.a
│           │   │   │       ├── libsgcore.so
│           │   │   │       ├── libsglog.a
│           │   │   │       └── libsgserial.a
│           │   │   └── x86-64
│           │   │       ├── debug
│           │   │       │   ├── libflatbuffers.a
│           │   │       │   ├── libfmtd.a
│           │   │       │   ├── liblogurud.a
│           │   │       │   ├── libnng.a
│           │   │       │   ├── libserial.a
│           │   │       │   ├── libsgcommon.a
│           │   │       │   ├── libsgconnect.a
│           │   │       │   ├── libsgconnectshm.a
│           │   │       │   ├── libsgconnect.so
│           │   │       │   ├── libsgcore.a
│           │   │       │   ├── libsgcoreshm.a
│           │   │       │   ├── libsgcore.so
│           │   │       │   ├── libsglog.a
│           │   │       │   └── libsgserial.a
│           │   │       └── release
│           │   │           ├── libflatbuffers.a
│           │   │           ├── libfmt.a
│           │   │           ├── libloguru.a
│           │   │           ├── libnng.a
│           │   │           ├── libserial.a
│           │   │           ├── libsgcommon.a
│           │   │           ├── libsgconnect.a
│           │   │           ├── libsgconnectshm.a
│           │   │           ├── libsgconnect.so
│           │   │           ├── libsgcore.a
│           │   │           ├── libsgcoreshm.a
│           │   │           ├── libsgcore.so
│           │   │           ├── libsglog.a
│           │   │           └── libsgserial.a
│           │   └── v26
│           │       ├── aarch64
│           │       │   ├── debug
│           │       │   │   ├── libflatbuffers.a
│           │       │   │   ├── libfmtd.a
│           │       │   │   ├── liblogurud.a
│           │       │   │   ├── libnng.a
│           │       │   │   ├── libserial.a
│           │       │   │   ├── libsgcommon.a
│           │       │   │   ├── libsgconnect.a
│           │       │   │   ├── libsgconnectshm.a
│           │       │   │   ├── libsgconnect.so
│           │       │   │   ├── libsgcore.a
│           │       │   │   ├── libsgcoreshm.a
│           │       │   │   ├── libsgcore.so
│           │       │   │   ├── libsglog.a
│           │       │   │   └── libsgserial.a
│           │       │   └── release
│           │       │       ├── libflatbuffers.a
│           │       │       ├── libfmt.a
│           │       │       ├── libloguru.a
│           │       │       ├── libnng.a
│           │       │       ├── libserial.a
│           │       │       ├── libsgcommon.a
│           │       │       ├── libsgconnect.a
│           │       │       ├── libsgconnectshm.a
│           │       │       ├── libsgconnect.so
│           │       │       ├── libsgcore.a
│           │       │       ├── libsgcoreshm.a
│           │       │       ├── libsgcore.so
│           │       │       ├── libsglog.a
│           │       │       └── libsgserial.a
│           │       └── x86-64
│           │           ├── debug
│           │           │   ├── libflatbuffers.a
│           │           │   ├── libfmtd.a
│           │           │   ├── liblogurud.a
│           │           │   ├── libnng.a
│           │           │   ├── libserial.a
│           │           │   ├── libsgcommon.a
│           │           │   ├── libsgconnect.a
│           │           │   ├── libsgconnectshm.a
│           │           │   ├── libsgconnect.so
│           │           │   ├── libsgcore.a
│           │           │   ├── libsgcoreshm.a
│           │           │   ├── libsgcore.so
│           │           │   ├── libsglog.a
│           │           │   └── libsgserial.a
│           │           └── release
│           │               ├── libflatbuffers.a
│           │               ├── libfmt.a
│           │               ├── libloguru.a
│           │               ├── libnng.a
│           │               ├── libserial.a
│           │               ├── libsgcommon.a
│           │               ├── libsgconnect.a
│           │               ├── libsgconnectshm.a
│           │               ├── libsgconnect.so
│           │               ├── libsgcore.a
│           │               ├── libsgcoreshm.a
│           │               ├── libsgcore.so
│           │               ├── libsglog.a
│           │               └── libsgserial.a
│           └── windows
│               ├── rustc
│               │   └── x86-64
│               │       ├── debug
│               │       │   └── sgble.lib
│               │       └── release
│               │           └── sgble.lib
│               └── v143
│                   └── x86-64
│                       ├── debug
│                       │   ├── flatbuffers.lib
│                       │   ├── flatbuffers.pdb
│                       │   ├── fmtd.lib
│                       │   ├── fmtd.pdb
│                       │   ├── logurud.lib
│                       │   ├── logurud.pdb
│                       │   ├── nng.lib
│                       │   ├── nng.pdb
│                       │   ├── serial.lib
│                       │   ├── serial.pdb
│                       │   ├── sgcommon.lib
│                       │   ├── sgcommon.pdb
│                       │   ├── sgconnect.dll
│                       │   ├── sgconnect.lib
│                       │   ├── sgconnect.pdb
│                       │   ├── sgconnectshm.lib
│                       │   ├── sgconnectshm.pdb
│                       │   ├── sgcore.dll
│                       │   ├── sgcore.lib
│                       │   ├── sgcore.pdb
│                       │   ├── sgcoreshm.lib
│                       │   ├── sgcoreshm.pdb
│                       │   ├── sglog.lib
│                       │   ├── sglog.pdb
│                       │   ├── sgserial.lib
│                       │   └── sgserial.pdb
│                       └── release
│                           ├── flatbuffers.lib
│                           ├── fmt.lib
│                           ├── loguru.lib
│                           ├── nng.lib
│                           ├── serial.lib
│                           ├── sgcommon.lib
│                           ├── sgconnect.dll
│                           ├── sgconnect.lib
│                           ├── sgconnectshm.lib
│                           ├── sgcore.dll
│                           ├── sgcore.lib
│                           ├── sgcoreshm.lib
│                           ├── sglog.lib
│                           └── sgserial.lib
```

---

## Root CMake Project

```
CMakeLists.txt
```

The main CMake entry point that:

* Loads the custom `FindSenseGloveSDK.cmake`
* Configures the example applications
* Links the SenseGlove SDK libraries

This file also demonstrates how to structure a project that depends on the SDK.

---

## CMake Module

```
cmake/FindSenseGloveSDK.cmake
```

This module allows CMake to locate the SenseGlove SDK installation and expose the required include paths and libraries.

The module defines variables such as:

```
SenseGloveSDK_FOUND
SenseGloveSDK_INCLUDE_DIRS
SenseGloveSDK_LIBRARIES
```

You can reuse this module in your own projects by copying it into your project's `cmake/` directory.

---

## Example Applications

Three small example applications are provided.

### SGConnect Client Example

```
src/sgconnect-client-simple/
```

This example demonstrates how to:

* Initialize **SGConnect**
* Detect available devices
* Query connection information

---

### SGCore Client Example

```
src/sgcore-client-simple/
```

This example demonstrates how to use the **SGCore API** to interact with SenseGlove devices.

---

### SGCore Client (Without SenseCom)

```
src/sgcore-client-no-sensecom/
```

This example demonstrates usage of SGCore without relying on SenseCom services.

---

# Building the Examples

The project can be built on **Linux** and **Windows** using the provided scripts.


**IMPORTANT**:

By default, the SenseGlove SDK binaries are built with `Exceptions` and `RTTI` disabled. On some compilers and toolchains, these settings can influence C++ symbol name mangling and the linker’s expectations when resolving symbols. As a result, projects compiled with different `Exceptions` or `RTTI` settings may encounter linker errors when linking against the SDK.

If you run into such issues, please feel free to contact us. We can provide SDK binaries built with `Exceptions` and `RTTI` settings that match your project's configuration.

Please see the relevant section inside the provided [`CMakeLists.txt`](./CMakeLists.txt) and adjust it accordingly.

---

# Linux

## Linux Toolchain Compatibility

**IMPORTANT**: If your project uses GCC with `libstdc++`, you may encounter linker or ABI compatibility issues.

The prebuilt Linux libraries included in the SenseGlove SDK are compiled using **LLVM Clang with `libc++`** rather than **GCC with `libstdc++`**.

This is intentional.

The SenseGlove backend is primarily developed for **Unreal Engine integrations**, and Unreal Engine uses [**Epic's native/cross-compilation toolchains**](https://dev.epicgames.com/documentation/en-us/unreal-engine/linux-development-requirements-for-unreal-engine) on GNU/Linux, which preferes **Clang and `libc++`** builds. To maintain ABI compatibility with Unreal Engine builds, the distributed Linux binaries follow the same toolchain setup.

As a result, the provided libraries are **not currently compatible with `libstdc++` builds**.

### Supported Linux Toolchains

To use the prebuilt SDK binaries on Linux, your project must be compiled using one of the following:

* **LLVM Clang + `libc++`**
* **Epic Native Toolchain**
* **Epic Cross Toolchain**

These toolchains ensure ABI compatibility with the provided libraries.

### Using Epic Toolchains

Epic provides prebuilt native and cross-compilation toolchains used by Unreal Engine.

These toolchains can be downloaded from [Epic's official website](https://dev.epicgames.com/documentation/en-us/unreal-engine/linux-development-requirements-for-unreal-engine).

Using these toolchains guarantees compatibility with the distributed SenseGlove SDK binaries.

### Using Your Distribution's Toolchain

If you are using your Linux distribution's toolchain, ensure that the required **LLVM/Clang and libc++ components** are installed. The SenseGlove SDK libraries are built against **Clang and `libc++`**, so these components must be available on your system.

For example, on **Void Linux**:

```sh
$ xbps-install -S \
    llvm \
    clang \
    lldb \
    lld \
    libcxx \
    libcxx-devel \
    libcxxabi-devel \
    libunwind \
    ninja \
    cmake
```

### Future Support

At this time, the SDK does **not provide binaries compiled with GCC and `libstdc++`**.

Support for **libstdc++ / GCC-compatible builds** may be added in future releases if there is sufficient demand.

---

## Configure

```sh
$ ./linux-configure.sh
```

This runs CMake and generates the build files.

---

## Build (Debug)

```sh
$ ./linux-build-debug.sh
```

---

## Build (Release)

```sh
$ ./linux-build-release.sh
```

---

# Windows

On Windows, the project uses **Visual Studio generators**.

---

## Configure

```cmd
> windows-configure.cmd
```

This generates the Visual Studio solution.

---

## Build (Debug)

```cmd
> windows-build-debug.cmd
```

---

## Build (Release)

```cmd
> windows-build-release.cmd
```

---

# Building Directly in Visual Studio

After running the configure script, a **Visual Studio solution** will be generated.

You may open the solution and build directly inside Visual Studio.

This allows you to:

* Build
* Debug
* Run the examples
* Inspect the project configuration

---

# Running the Examples on Windows

When running the examples on Windows, the required DLLs must be available next to the executable.

You must copy the following libraries:

```
SGConnect.dll
SGCore.dll
```

The correct DLLs depend on the build configuration.

---

## Debug Build

Copy the `SGConnect` and `SGCore` DLLs from the SDK **Debug directory**.

```
third-party/SenseGloveSDK/lib/windows/v143/x86-64/debug/
```

Place them next to the compiled executable.

---

## Release Build

Copy the `SGConnect` and `SGCore` DLLs from the SDK **Release directory**.

```
third-party/SenseGloveSDK/lib/windows/v143/x86-64/release/
```

Place them next to the executable.

---

⚠️ If the **wrong configuration DLLs** are used (for example Debug DLLs with a Release executable), the program may fail to start or crash at runtime.

---

# Android

## Android Toolchain Compatibility

The prebuilt Android libraries included in the SenseGlove SDK are compiled using specific **Android NDK versions**. To ensure ABI compatibility, projects integrating the SDK should use one of the supported NDK versions listed below.

### Supported Android NDK Versions

The SenseGlove SDK currently provides libraries built against the following Android NDK versions:

* **NDK r25b**
* **NDK r27c**

These correspond to the directory structure inside the SDK:

```
lib/android/
├── r25b
└── r27c
```

Each NDK version contains builds for the supported Android architectures.

Example:

```
lib/android/r25b/aarch64/debug
lib/android/r25b/aarch64/release
```

### Selecting the Android Toolchain in CMake

When using the `FindSenseGloveSDK.cmake` module, you can explicitly specify the NDK toolchain version using:

```cmake
set(SenseGloveSDK_TOOLCHAIN_ANDROID "r27c")
```

Example configuration:

```cmake
set(SenseGloveSDK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third-party/SenseGloveSDK")
set(SenseGloveSDK_TOOLCHAIN_ANDROID "r27c")

find_package(SenseGloveSDK REQUIRED)
```

### Notes

* Using a different NDK version may lead to **ABI incompatibilities**.
* For best compatibility, use the same NDK version that the SDK binaries were built with.
* The SDK currently provides builds for the **`aarch64`** and **`x86-64`** Android architectures.

Future SDK releases may add or remove support for additional NDK versions as needed.

---

# Using the CMake Module in Your Own Project

You can integrate the SDK into your own CMake project by copying the module:

```
cmake/FindSenseGloveSDK.cmake
```

Then configure your project as follows.

---

## Example CMake Setup

```cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SenseGloveSDK REQUIRED)

add_executable(my_app main.cpp)

target_link_libraries(my_app
    ${SenseGloveSDK_LIBRARIES}
)

target_include_directories(my_app
    PRIVATE
    ${SenseGloveSDK_INCLUDE_DIRS}
)
```

---

Your README is already very solid. The only real gap is documenting the **user variables that must be set before `find_package`**, and tightening a few small inconsistencies (like the `SENSEGLOVE_SDK_ROOT` vs `SenseGloveSDK_ROOT` naming).

Below is a **clean section you should insert right after “CMake Module” and before “Example Applications”**. This is the logical place because it explains how the module is configured.

---

## Configuring `FindSenseGloveSDK.cmake`

The `FindSenseGloveSDK.cmake` module supports several **user-configurable variables** that can be set **before calling `find_package()`**.

These variables allow you to control where the SDK is located and how it should be linked.

Example:

```cmake
set(SenseGloveSDK_ROOT "/path/to/SenseGloveSDK")
set(SenseGloveSDK_LINK_STATIC ON)

find_package(SenseGloveSDK REQUIRED)
```

---

### User Variables

The following variables can be configured before calling `find_package(SenseGloveSDK)`.

### `SenseGloveSDK_ROOT`

Specifies the root directory of the SenseGlove SDK installation.

Example:

```cmake
set(SenseGloveSDK_ROOT "/opt/SenseGloveSDK")
```

If not specified, the module will attempt to locate the SDK using default search paths.

---

### `SenseGloveSDK_LINK_STATIC`

Controls whether the SDK should be linked **statically** or **dynamically**.

```
ON  → Link static libraries (.a / .lib)
OFF → Link shared libraries (.so / .dll)
```

Example:

```cmake
set(SenseGloveSDK_LINK_STATIC ON)
```

---

### `SenseGloveSDK_TOOLCHAIN_ANDROID`

Specifies the Android toolchain version used to build the SDK libraries.

Example values correspond to the directories inside:

```
lib/android/
```

Example:

```cmake
set(SenseGloveSDK_TOOLCHAIN_ANDROID "r27c")
```

---

### `SenseGloveSDK_TOOLCHAIN_LINUX`

Specifies the Linux toolchain version used to build the SDK libraries.

Typical values correspond to directories such as:

```
lib/linux/v23
lib/linux/v25
lib/linux/v26
```

Example:

```cmake
set(SenseGloveSDK_TOOLCHAIN_LINUX "v26")
```

---

### `SenseGloveSDK_TOOLCHAIN_WINDOWS`

Specifies the Visual Studio toolchain used to build the SDK libraries.

Typical values correspond to directories such as:

```
lib/windows/v143
```

Example:

```cmake
set(SenseGloveSDK_TOOLCHAIN_WINDOWS "v143")
```

---

### Example Configuration

A full example configuration might look like this:

```cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(SenseGloveSDK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third-party/SenseGloveSDK")
set(SenseGloveSDK_LINK_STATIC OFF)
set(SenseGloveSDK_TOOLCHAIN_LINUX "v26")

find_package(SenseGloveSDK REQUIRED)
```

---

### Notes

* These variables **must be defined before calling `find_package(SenseGloveSDK)`**.
* If they are not specified, the module will attempt to detect reasonable defaults based on the current platform and toolchain.

---

# Notes

* The examples are intentionally minimal.
* The provided CMake module is designed to be reusable in other projects.
* The scripts are provided only for convenience — developers can use their own build workflow.

---

# License

This example project is provided for demonstration purposes.

For usage terms please visit:

- [LICENSE.md](LICENSE.md) for the main license
- [LICENSE-SDK.md](LICENSE-SDK.md) for SenseGlove SDK license
- [LICENSE-THIRD-PARTY.md](LICENSE-THIRD-PARTY.md) for third-party licenses
