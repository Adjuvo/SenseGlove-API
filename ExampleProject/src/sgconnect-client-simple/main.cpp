/*
    Console application demonstrating the main funtion(s) of the SGConnect library.

    author:
    max@senseglove.com
    mamadou@senseglove.com
*/

#include <SenseGlove/Common/Platform.hpp>

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <SenseGlove/Connect/SGConnect.hpp>


int32_t main()
{
    //SGConnect::SetSerialConnectionsEnabled(true); //Set this to false to ignore Serial Connections (older Nova's)
    SGConnect::SetSerialConnectionsEnabled(false); //Set this to false to ignore Serial Connections (older Nova's)

    //Change these to your Nova 2 names. Recommend caching these on disk somehwere.
    std::vector<std::string> nova2BleDevices{
            "Nova 2-03004-R",
            "Nova 2-03481-L"
    };


    std::string libraryVersion;
    SGConnect::GetLibraryVersion(&libraryVersion);
    std::cout << "SGConnect version: " << libraryVersion << std::endl;

    std::cout << "Press Enter to initialize SG Back End." << std::endl;
    std::cout << "=========================================" << std::endl;
    while (std::cin.get() != '\n') {}//Wait for the user to confirm before exiting. Platform agnostic

    std::cout << "Testing " << libraryVersion << std::endl;
    std::cout << "=========================================" << std::endl;

    //--------------------------------------------------------------------------------------------------------------------------------------------------
    // Register BLE Connections (can also be done after Init - but this ensures it's already set up for you)

    for (int i = 0; i < nova2BleDevices.size(); i++) {
        std::cout << "Registering " << nova2BleDevices[i] << std::endl;
        SGConnect::RegisterNova2BLEConnection(nova2BleDevices[i].c_str());
    }


    //--------------------------------------------------------------------------------------------------------------------------------------------------
    // Initializing (unless someone else is already running SenseCom

    bool scanActive = SGConnect::ScanningActive();
    if (scanActive) {//We only get here if another process is already running (e.g. ScanningActive == true).
        std::cout << "A SenseGlove scanning process is already running (ScanState " << SGConnect::ScanningState() << " > 0)." << std::endl;
        std::cout << "Seeing as we've just started up, it can't possibly be this process that did it." << std::endl;
        std::cout << "It is safe to call SGConnect::Init() even if this is the case, but no new process will be started." << std::endl;
        int initCode = SGConnect::Init();
        std::cout << "The SGConnect::Init() will return 0, to let us know no Initialization was done: " << initCode << std::endl;
        std::cout << "" << std::endl;
        std::cout << "We can call SGConnect::Dispose() safely, but this will not stop the original process." << std::endl;
        int disposeVal = SGConnect::Dispose();
        std::cout << "The SGConnect::Dispose() will return 0, to let us know nothing was Disposed of: " << disposeVal << std::endl;
        std::cout << "If you wish to dispose of the already running process, you should call SGConnect::Dispose() from the program that originally called SGConnect::Init()" << std::endl;
    }
    else {
        std::cout << "We call SGConnect::Init() to startup a background process, which will begin scanning for SenseGlove devices." << std::endl;
        int initCode = SGConnect::Init();
        if (initCode > 0) {
            std::cout << "Successfully initialized background process: (InitCode = " << initCode << ")" << std::endl;
            std::cout << "This process will begin connecting to ports that should belong to SenseGlove devices." << std::endl;
            std::cout << "It will take a few seconds before the devices appear to the SenseGlove API, especially when using Bluetooth devices." << std::endl;
            std::cout << "Below, you will see debug messages appear from the background process. Type 'X' when you are ready to finish" << std::endl;
            std::cout << "---------------------------------------------------------------------------------" << std::endl;
            while (std::cin.get() != '\n') {}//Wait for the user to confirm before exiting.
            std::cout << "" << std::endl;

            //--------------------------------------------------------------------------------------------------------------------------------------------------
            // Running a test program: Keep going until someone types 'X' / 'x'

            std::string response;
            bool runProgram = true;
            do {

                std::getline(std::cin, response);
                if (!response.empty()) {
                    char choice = std::toupper(response[0]);// Consider only the first character
                    if (choice == 'X')
                        runProgram = false;
                }
                if (runProgram)//Reminder for shutdown procedure
                {
                    int32_t sgDevices = SGConnect::ActiveDevices();
                    std::cout << "There are currently " << std::to_string(sgDevices) << " active SenseGlove Devices. You can interface with them using the SGCore Library." << std::endl;
                    std::cout << "Write 'X' to exit, or press return again to refresh the list." << std::endl;
                }
            } while (runProgram);


            //--------------------------------------------------------------------------------------------------------------------------------------------------
            // Disposing of SGConnect Resources

            int disposeCode = SGConnect::Dispose();
            if (disposeCode > 0) {
                std::cout << "Successfully cleaned up SGConnect resources: (DisposeCode = " << disposeCode << ")" << std::endl;
            } else {
                std::cout << "Unable to properly dispose of SGConnect resources: (DisposeCode = " << disposeCode << ")" << std::endl;
                std::cout << "Fortunately, closing this process will cause them to go out of scope and be destroyed either way." << std::endl;
            }

        } else {
            std::cout << "Oddly enough, we could not initialize the SGConnect library. (InitCode = " << initCode << ")" << std::endl;
            std::cout << "Please close this program, and try again." << std::endl;
        }


    }

    std::cout << "=========================================" << std::endl;
    std::cout << "Done. Press Return to exit." << std::endl;
    while (std::cin.get() != '\n') {}//Wait for the user to confirm before exiting.


    return 0;
}