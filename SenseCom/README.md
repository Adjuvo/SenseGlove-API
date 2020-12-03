# SenseCom
SenseCom is a program (or process) that is responsible for detecting and communicating with SenseGlove Devices. When running SenseCom, the connection status of each SenseGlove device will be visible to the user. This is to ensure all hardware has been properly connected before starting a program.

This folder contains executable versions for different platforms. There is also a folder called SGConnect, which contains the tools to integrate a dynamic library of the same name into any 3rd party C++ program, should a standalone version of said project be desired.

## Running on Windows
Until a proper SenseCom installer is ready, note that you will need a Visual C++ package to be able to use the library, which you can download via https://aka.ms/vs/16/release/vc_redist.x64.exe or find in the Win folder

## Running on Linux
You can run the SenseCom.x86_64 as an executable by going to properties and checking "allow running as executable" in the permissions tab.
Also, ensure that you have set the permissions for SenseCOm to use your serial ports via the "sudo adduser $USER dialout" command.

## Advanced 

### Running without the SenseCom UI
SenseCom is technically a UI around the SGConnect library, which handles the detection of- and communication with SenseGlove devices. It adds features such as calibration and firmware checks. Sense Glove recommends using SenseCom as the method of establishing communications. If, for any reason, you are unable or unwilling to run SenseCom in the background, it is possible to isolate the SGConnect library and import it into your own C++ project. This library can be found in the "Core" folder.

- The ScanningActive() method will return true if another process is already interfacing with SenseGlove devices. Use this function to avoid calling the Init() function to prevent communication issues if your end user chooses to run SenseCom.
- By calling the Init() function of the SGConnect Library, you will start a background process which will begin scanning for devices. It is best to call this function as soon as you start your program, since it will take a few moments before all devices have been recognized. Use the ScanningActive() function described above to ensure proper interfacing.
- Calling the Dispose() function will stop the background thread and clean up its resources. It is important to call this function when your program ends or when you no longer require SenseGlove resources to ensure all devices are properly disconnected. 

An example implementation of the SGConnect Library can be found in the Examples > VS2019 > NoSenseCom project.


### Running without SenseCom altogether
In the rare case that one needs direct control over SenseGlove connections, such as running on web or mobile phone, it is possible to integrate SenseGlove devices directly if one is aware of the SenseGlove Communications Protocol. Provided that one is able to convert the raw data into SGCore classes, it is possible to then use the kinematics functions therein. However, this would require writing manual detection and parsing methods for the communications, and will require an NDA to be signed.