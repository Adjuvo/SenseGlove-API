/*
    Console application demonstrating the main funtion(s) of the SGCore library.

    author:
    max@senseglove.com
    mamadou@senseglove.com
*/

#include <SenseGlove/Common/Platform.hpp>

#include <cstdint>
#include <string>
#include <thread>
#include <iostream>

#include <SenseGlove/Core/HandLayer.hpp>
#include <SenseGlove/Core/HandPose.hpp>
#include <SenseGlove/Core/HapticGlove.hpp>
#include <SenseGlove/Core/Library.hpp>
#include <SenseGlove/Core/Quat.hpp>
#include <SenseGlove/Core/SenseCom.hpp>
#include <SenseGlove/Core/StringUtils.hpp>
#include <SenseGlove/Core/Tracking.hpp>
#include <SenseGlove/Core/Vect3D.hpp>

#include <SenseGlove/Connect/SGConnect.hpp>

using namespace SGCore;
using namespace SGCore::Kinematics;

using namespace SGConnect;

/// <summary> Test a vibration, taking into account timing </summary>
static void TestVibration(bool rightHand, float amplitude, float duration, float frequency, SGCore::EHapticLocation location)
{
    if (!HandLayer::DeviceConnected(rightHand))
        return;

    std::string hand = rightHand ? "right hand" : "left hand";
    if (HandLayer::SupportsCustomWaveform(rightHand, location)) {
        SGCore::CustomWaveform waveform{amplitude, duration, frequency};
        HandLayer::SendCustomWaveform(rightHand, waveform, location);
    } else {
        std::cout << "The " << hand << " does not support Custom Waveforms (at " << HapticGlove::ToString(location)
                  << " ), so we're sending a vibration to the Index Finger instead" << std::endl;
        //whole hand and / or custom waveforms not supported. So we're pulsing the index finger instead.
        HandLayer::QueueCommand_VibroLevel(rightHand, 1, 1.0f, true);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int32_t>(duration * 1000))); //s to ms
        HandLayer::QueueCommand_VibroLevel(rightHand, 1, 0.0f, true);//turn it back off
    }
}

/// <summary> Test HandPoses </summary>
/// <param name="rightHand"></param>
static void TestHandTracking(bool rightHand)
{
    if (!HandLayer::DeviceConnected(rightHand))
        return;

    SGCore::HandLayer::ResetCalibration(rightHand);

    std::string hand = rightHand ? "right hand" : "left hand";
    SGCore::EHapticGloveCalibrationState calState = HandLayer::GetCalibrationState(rightHand);
    SGCore:HandPose handPose;
    if (calState == EHapticGloveCalibrationState::Unknown) {
        std::cout << "The Calibration State of the " << hand << " is not known. So we cannot retrieve a proper HandPose..." << std::endl;
        return;
    }

    switch (calState)
    {
        case EHapticGloveCalibrationState::MoveFingers:
            std::cout << hand << " state is MoveFingers" << std::endl;
            break;
        case EHapticGloveCalibrationState::AllSensorsMoved:
            std::cout << hand << " state is AllSensorsMoved" << std::endl;
            break;
        case EHapticGloveCalibrationState::CalibrationLocked:
            std::cout << hand << " state is CalibrationLocked" << std::endl;
            break;
        default:
            break;
    }

    if (calState == EHapticGloveCalibrationState::MoveFingers)//improvised calibration
    {
        int32_t timeout = 20;             //every 20ms, since the Nova doesn't update more than 60Hz anyway.
        int32_t sanityTimeout = 20 * 1000;//10 s timeout.
        int32_t sanityTimer = 0;
        int32_t displayAnglesAfter = 3;

        int32_t moveTimer = 0;
        int32_t moveTimeout = 1 * 1000;//s after you start moving
        std::cout << "Calibration on the " << hand << " is yet to be completed. If it's a Nova Glove, calibration will automatically happen as you call a GetHandPose() / GetSensorData() function." << std::endl;
        std::cout << "Let's try it now: Move each of the sensors on your " << hand << " within the next " << std::to_string(sanityTimeout / 1000.0f) << " seconds. Pay special attention to your thumb sensor(s)" << std::endl;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeout));//s to ms
            HandLayer::GetHandPose(rightHand, handPose);//normally, you'd grab this mutliple times.

            sanityTimer += timeout;
            calState = HandLayer::GetCalibrationState(rightHand);

            if (calState == EHapticGloveCalibrationState::AllSensorsMoved) {
                moveTimer += timeout;
            }
        } while (calState != EHapticGloveCalibrationState::CalibrationLocked && sanityTimer < sanityTimeout && moveTimer < moveTimeout);

        if (calState == EHapticGloveCalibrationState::MoveFingers)//you still haven't moved enough yet. That was the longer timeout.
        {
            std::cout << "You haven't moved all sensors yet, so some of the angles might a bit off. But we can grab a HandPose either way. Press Return to continue..." << std::endl;
            while (std::cin.get() != '\n') {}
        }
        if (calState == EHapticGloveCalibrationState::AllSensorsMoved)
        {
            std::cout << "You've moved enough of your fingers! Give us a thumbs up to lock it in!" << std::endl;
            sanityTimer = 0.0f;
            moveTimer = 0.0f;
            do {

                std::this_thread::sleep_for(std::chrono::milliseconds(timeout));//s to ms
                HandLayer::GetHandPose(rightHand, handPose);                    //normally, you'd grab this mutliple times.
                sanityTimer += timeout;

                if (sanityTimer >= displayAnglesAfter) {
                    std::vector<float> normalized = handPose.GetNormalizedFlexion();
                    std::string log{"["};
                    for (size_t i = 0; i < normalized.size(); ++i) {
                        log += std::to_string(normalized[i]);
                        if (i < normalized.size() - 1)
                            log += ", ";
                    }
                    log += "]";
                    std::cout << log << std::endl;
                }
                calState = HandLayer::GetCalibrationState(rightHand);
                if (calState == EHapticGloveCalibrationState::CalibrationLocked) {
                    moveTimer += timeout;
                }
            } while (sanityTimer < sanityTimeout && moveTimer < moveTimeout);

            std::cout << "You've moved enough of your fingers! Press Return to grab a proper pose... " << std::endl;
            while (std::cin.get() != '\n') {}
        }
        else {
            std::cout << "Calibration finished. Press Return to grab a handpose" << std::endl;
            while (std::cin.get() != '\n') {}
        }
    } else {
        std::cout << "Press Return to grab a HandPose for the " << hand << std::endl;
        while (std::cin.get() != '\n') {}
    }
    //Actually grab a HandPose
    if (HandLayer::GetHandPose(rightHand, handPose)) {
        std::cout << "Grabbed a HandPose for the " << hand << std::endl;
        std::cout << handPose.ToString() << std::endl;
    } else {
        std::cout << "We couldn't grab a " << hand << " pose. That can happen because sensor data was corrupted, or because the glove is (no longer) connected. Try again later..." << std::endl;
    }
}

/// <summary> Test Wrist Tracking </summary>
/// <param name="rightHand"></param>
static void TestWristTracking(bool rightHand)
{
    if (!HandLayer::DeviceConnected(rightHand))
        return;
    std::string hand = rightHand ? "Right hand" : "Left hand";

    // Since our Gloves do not have their own on-board tracking, we rely on another Tracking Source, like a Quest 2 controller:
    EPositionalTrackingHardware trackingHardware = EPositionalTrackingHardware::Quest2Controller;
    Vect3D trackerPosition = Vect3D(0.0f, 0.0f, 0.0f);
    Quat trackerRotation = Quat::FromEuler(0.0f, 0.0f, 0.0f);

    // We then calculate the wrist location as follows:
    Vect3D wristPosition;
    Quat wristRotation;
    HandLayer::GetWristLocation(rightHand, trackerPosition, trackerRotation, trackingHardware, wristPosition, wristRotation);

    std::cout << hand << " wrist position (" << trackerPosition.ToString() << " mm, "
              << trackerRotation.ToEuler().ToString() << " rad) for "
              << Tracking::ToString(trackingHardware) << " : => "
              << wristPosition.ToString()  << " mm, "
              << wristRotation.ToEuler().ToString() << "  rad." << std::endl;
}

int32_t main()
{
    SGConnect::SetSerialConnectionsEnabled(false); //Set this to false to ignore Serial Connections (older Nova's)

    //Change these to your Nova 2 names. Recommend caching these on disk somehwere.
    std::vector<std::string> nova2BleDevices{
            "Nova 2-03004-R",
            "Nova 2-03481-L"
    };


    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Checking the Library

    // Displaying Library information - Useful to know when asking for any kind of support
    std::string sgcVersion;
    SGConnect::GetLibraryVersion(&sgcVersion);

    std::cout << "Testing " << SGCore::Library::Version() << ", compiled for " << SGCore::Library::BackendVersion()
              << " with " << sgcVersion << std::endl;

    std::cout << "=========================================================================" << std::endl;

    //--------------------------------------------------------------------------------------------------------------------------------------------------
    // Register BLE Connections (can also be done after Init - but this ensures it's already set up for you)

    for (int i = 0; i < nova2BleDevices.size(); i++) {
        std::cout << "Registering " << nova2BleDevices[i] << std::endl;
        SGConnect::RegisterNova2BLEConnection(nova2BleDevices[i].c_str());
    }

    //--------------------------------------------------------------------------------------------------------------------------------------------------
    // Initializing (unless someone else is already running SenseCom


    bool scanActive = SGConnect::ScanningActive();
    int32_t initCode = 0;

    if (scanActive) {//We only get here if another process is already running (e.g. ScanningActive == true).
        std::cout << "A SenseGlove scanning process is already running (ScanState " << SGConnect::ScanningState() << " > 0)." << std::endl;
    } else {
        initCode = SGConnect::Init();
        if (initCode > 0) {
            std::cout << "Successfully initialized background process: (InitCode = " << initCode << ")" << std::endl;

            //--------------------------------------------------------------------------------------------------------------------------------------------------
            // Running a test program: Keep going until someone types 'X' / 'x'
            std::cout << "Write 'X' to continue, or press return again to refresh the list." << std::endl;

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
                    std::cout << "Write 'X' to continue, or press return again to refresh the list." << std::endl;
                }
            } while (runProgram);

        } else {
            std::cout << "Oddly enough, we could not initialize the SGConnect library. (InitCode = " << initCode << ")" << std::endl;
            std::cout << "Please close this program, and try again." << std::endl;
        }
    }


    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Checking for Connections
    {
        int32_t gloveAmount = HandLayer::GlovesConnected();//GlovesConnected gives you the amount of gloves connected to your system.
        while (gloveAmount == 0)                      //For this exercise, I'll keep trying to connect to a glove.
        {
            std::cout << "Failed to Detect a Haptic Glove on your System. Please ensure your device is paired or connected via USB." << std::endl;
            std::cout << "Press Return to try again..." << std::endl;
            while (std::cin.get() != '\n') {}
            gloveAmount = HandLayer::GlovesConnected();
        }

        // When we get here, we've got one glove connected. Yay.

        if (gloveAmount == 1) {
            std::cout << "There is 1 Haptic Glove connected to your system." << std::endl;
            bool rightHand = HandLayer::GetFirstGloveHandedness();
            std::cout << "It is a " << (rightHand ? "Right" : "Left") << " handed glove of type " << SGDevice::ToString(HandLayer::GetDeviceType(rightHand)) << std::endl;
        } else {
            std::cout << "There are " << std::to_string(gloveAmount) << " Haptic Gloves connected to your system." << std::endl;

            if (HandLayer::DeviceConnected(true)) {
                std::cout << "The right hand is a " << SGDevice::ToString(HandLayer::GetDeviceType(true)) << std::endl;
            } else {
                std::cout << "There is no right hand connected." << std::endl;
            }

            if (HandLayer::DeviceConnected(false)) {
                std::cout << "The left hand is a " << SGDevice::ToString(HandLayer::GetDeviceType(false)) << std::endl;
            } else {
                std::cout << "There is no left hand connected." << std::endl;
            }
        }
        std::cout << "-------------------------------------------------------------------------" << std::endl;
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Force-Feedback Command(s)
    {
        //Toggles FFB for the first 3 fingers; thumb, index, and middle finger.
        std::vector<float> fingerFfb = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };//there's 5 fingers.
        for (int32_t f = 0; f < 3; f++) {
            EFinger finger = static_cast<EFinger>(f);
            std::cout << "Press Return to turn on the Force-Feedback of the " << SGCore::Util::StringUtils::ToString(finger) << std::endl;
            while (std::cin.get() != '\n') {}

            fingerFfb[f] = 1.0f;//sets the finger ffb for the current finger to 100%
            //Queue these for the left / right hand, and send them immediately afterward
            HandLayer::QueueCommand_ForceFeedbackLevels(true, fingerFfb, true);
            HandLayer::QueueCommand_ForceFeedbackLevels(false, fingerFfb, true);

            std::cout << "Press Return to turn it back off" << std::endl;
            while (std::cin.get() != '\n') {}

            fingerFfb[f] = 0.0f;//sets the finger ffb for the current finger back to 0%.
            //Queue these for the left / right hand, and send them immediately afterward
            HandLayer::QueueCommand_ForceFeedbackLevels(true, fingerFfb, true);
            HandLayer::QueueCommand_ForceFeedbackLevels(false, fingerFfb, true);
        }
        std::cout << "-------------------------------------------------------------------------" << std::endl;
    }


    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Vibration Command
    {
        std::cout << "Press Return to send a vibration to both hands." << std::endl;
        while (std::cin.get() != '\n') {}

        float amplitude = 1.0f; //100% intensity
        float duration = 0.200f;//200 ms
        float frequency = 80.0f;//80 Hz
        EHapticLocation location = EHapticLocation::WholeHand;
        std::cout << "Sending a vibration of " << std::to_string(duration) << "s, amplitude " << amplitude << " and Fequency of " << static_cast<int32_t>(frequency) << "Hz to " << HapticGlove::ToString(location),
        TestVibration(true, amplitude, duration, frequency, location);
        TestVibration(false, amplitude, duration, frequency, location);

        std::cout << "-------------------------------------------------------------------------" << std::endl;
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Active Contact Feedback (Nova 2.0 only)
    {
        if (HandLayer::SupportsWristSqueeze(true) || HandLayer::SupportsWristSqueeze(false)) {
            std::cout << "Press Return to activate active contact feedback (wrist squeeze) on the hand(s)" << std::endl;
            while (std::cin.get() != '\n') {}

            HandLayer::QueueCommand_WristSqueeze(true, 1.0f, true);
            HandLayer::QueueCommand_WristSqueeze(false, 1.0f, true);

            std::cout << "Press Return to dectivate it" << std::endl;
            while (std::cin.get() != '\n') {}

            HandLayer::QueueCommand_WristSqueeze(true, 0.0f, true);
            HandLayer::QueueCommand_WristSqueeze(false, 0.0f, true);

            std::cout << "-------------------------------------------------------------------------" << std::endl;
        }
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Finger Tracking
    {
        std::cout << "Let's test out some finger tracking next" << std::endl;

        TestHandTracking(true);
        TestHandTracking(false);

        std::cout << "-------------------------------------------------------------------------" << std::endl;
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // 6Dof Wrist Tracking
    {
        std::cout << "Finally, we'll test wrist tracking" << std::endl;

        TestWristTracking(true);
        TestWristTracking(false);

        std::cout << "-------------------------------------------------------------------------" << std::endl;
    }



    std::cout << "-------------------------------------------------------------------------" << std::endl;

    //--------------------------------------------------------------------------------------------------------------------------------------------------
    // Disposing of SGConnect Resources

    if (initCode > 0) {
        int disposeCode = SGConnect::Dispose();
        if (disposeCode > 0) {
            std::cout << "Successfully cleaned up SGConnect resources: (DisposeCode = " << disposeCode << ")" << std::endl;
        } else {
            std::cout << "Unable to properly dispose of SGConnect resources: (DisposeCode = " << disposeCode << ")" << std::endl;
            std::cout << "Fortunately, closing this process will cause them to go out of scope and be destroyed either way." << std::endl;
        }
    }

    std::cout << "=========================================================================" << std::endl;
    std::cout << "Press any key to exit." << std::endl;
    while (std::cin.get() != '\n') {}

    return 0;
}