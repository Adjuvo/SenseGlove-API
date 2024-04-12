// SGCoreCppClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>

#include <SenseGlove/Connect/SGConnect.hpp>
#include <SenseGlove/Core/Debugger.hpp>
#include <SenseGlove/Core/SenseCom.hpp>
#include <SenseGlove/Core/Library.hpp>

#include <SenseGlove/Core/HandLayer.hpp>

#include <SenseGlove/Core/HandPose.hpp>
#include <SenseGlove/Core/Quat.hpp>
#include <SenseGlove/Core/Vect3D.hpp>

#include <SenseGlove/Core/HapticGlove.hpp>
#include <SenseGlove/Core/Tracking.hpp>
#include <SenseGlove/Core/StringUtils.hpp>


using namespace SGCore;
using namespace SGCore::Kinematics;

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
        std::cout << ("The " + hand + " does not support Custom Waveforms (at " + HapticGlove::ToString(location) + "), so we're sending a vibration to the Index Finger instead") << std::endl;
        //whole hand and / or custom waveforms not supported. So we're pulsing the index finger instead.
        HandLayer::QueueCommand_VibroLevel(rightHand, 1, 1.0f, true);
        std::this_thread::sleep_for(std::chrono::milliseconds( (int32_t)(duration * 1000) )); //s to ms
        HandLayer::QueueCommand_VibroLevel(rightHand, 1, 0.0f, true);//turn it back off
    }
}

/// <summary> Test HandPoses </summary>
/// <param name="rightHand"></param>
static void TestHandTracking(bool rightHand)
{
    if (!HandLayer::DeviceConnected(rightHand))
        return;

    std::string hand = rightHand ? "right hand" : "left hand";
    SGCore::EHapticGloveCalibrationState calState = HandLayer::GetCalibrationState(rightHand);
    SGCore:HandPose handPose;
    if (calState == EHapticGloveCalibrationState::Unknown) {
        std::cout << ("THe Calibration State of the " + hand + " is not known. So we cannot retrieve a proper HandPose...") << std::endl;
    }
    if (calState == EHapticGloveCalibrationState::MoveFingers)//improvised calibration
    {
        int32_t timeout = 20;             //every 20ms, since the Nova doesn't update more than 60Hz anyway.
        int32_t sanityTimeout = 20 * 1000;//10 s timeout.
        int32_t sanityTimer = 0;

        int32_t moveTimer = 0;
        int32_t moveTimeout = 1 * 1000;//s after you start moving
        std::cout << ("Calibration on the " + hand + " is yet to be completed. If it's a Nova Glove, calibration will automatically happen as you call a GetHandPose() / GetSensorData() function.") << std::endl;
        std::cout << ("Let's try it now: Move each of the sensors on your " + hand + " within the next " + std::to_string(sanityTimeout / 1000.0f) + " seconds. Pay special attention to your thumb sensor(s)") << std::endl;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeout));//s to ms
            HandLayer::GetHandPose(rightHand, handPose);//normally, you'd grab this mutliple times.
            sanityTimer += timeout;
            calState = HandLayer::GetCalibrationState(rightHand);
            if (calState == EHapticGloveCalibrationState::AllSensorsMoved) {
                moveTimer += timeout;
            }
        } while (sanityTimer < sanityTimeout && moveTimer < moveTimeout);

        if (calState == EHapticGloveCalibrationState::MoveFingers)//you still haven't moved enough yet. That was the longer timeout.
        {
            std::cout << ("You haven't moved all sensors yet, so some of the angles might a bit off. But we can grab a HandPose either way. Press a key to continue...") << std::endl;
            system("pause");
        } else {
            std::cout << ("You've moved enough of your fingers! Press a key to grab a proper pose... ") << std::endl;
            system("pause");
        }
    } else {
        std::cout << ("Press a key to grab a HandPose for the " + hand) << std::endl;
        system("pause");
    }
    //Actually grab a HandPose
    if (HandLayer::GetHandPose(rightHand, handPose)) {
        std::cout << ("Grabbed a HandPose for the " + hand + ":") << std::endl;
        std::cout << (handPose.ToString()) << std::endl;
    } else {
        std::cout << ("We couldn't grab a " + hand + " pose. That can happen because sensor data was corrupted, or because the glove is (no longer) connected. Try again later..") << std::endl;
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

    std::cout << (hand + " wrist position (" + trackerPosition.ToString() + " mm, " + trackerRotation.ToEuler().ToString() + " rad) for "
        + Tracking::ToString( trackingHardware ) + ": => " + wristPosition.ToString() + " mm, " + wristRotation.ToEuler().ToString() + " rad.") << std::endl;
}



int32_t main()
{
    //SGCore::Diagnostics::Debugger::SetDebugLevel(SGCore::Diagnostics::EDebugLevel::All);
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Checking the Library

    // Displaying Library information - Useful to know when asking for any kind of support
    std::cout << ("Testing " + SGCore::Library::Version() + ", compiled for " + SGCore::Library::BackendVersion());
    if (SGCore::Library::GetBackendType() == SGCore::EBackendType::SharedMemory)// By default, your library will be compiled to use Shared Memory via the SGConnect library
    {
        std::cout << (" using " + SGCore::Library::SGConnectVersion());//If you replace SGConnect.dll, this will give you its current version number.
    }
    std::cout << std::endl;
    std::cout << ("The source code for this program is located in the SGCoreCs/test/ folder.") << std::endl;
    std::cout << ("=========================================================================") << std::endl;


    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Ensuring connectivity

    // Connecting to SenseGlove devices is done in a separate "Connection Process" - contained in the SGConnect library.
    // We can test if this Connection Process is running on this PC. Usually, it runs inside SenseCom.
    // It's good practice to start this process if your user has not sone so yet.
    {
        bool connectionsActive = SGCore::SenseCom::ScanningActive();//returns true if SenseCom (or another program) has started the SenseGlove Communications Process.
        if (!connectionsActive)                                    // If this process is not running yet, we can "Force-Start" SenseCom. Provided it has run on this PC at least once.
        {
            std::cout << ("SenseCom is not yet running. Without it, we cannot connect to SenseGlove devices.") << std::endl;
            bool startedSenseCom = SGCore::SenseCom::StartupSenseCom();//Returns true if the process was started.
            if (startedSenseCom) {
                std::cout << ("Successfully started SenseCom. It will take a few seconds to connect...") << std::endl;
                connectionsActive = SGCore::SenseCom::ScanningActive();//this will return false immedeately after you called StartupSenseCom(). Because the program has yet to initialize.
                                                                      // Even if SenseCom started and the connections process is active, there's no guarantee that the user has turned their device(s) on. More on that later.
            } else                                                    // If StartupSenseCom() returns false, you've either never run SenseCom, or it is already running. But at that point, the ScanningActive() should have returned true.
            {
                std::cout << ("Could not Start the SenseCom process.") << std::endl;
            }
            std::cout << ("-------------------------------------------------------------------------") << std::endl;
        }
    }


    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Checking for Connections
    {
        int32_t gloveAmount = HandLayer::GlovesConnected();//GlovesConnected gives you the amount of gloves connected to your system.
        while (gloveAmount == 0)                      //For this exercise, I'll keep trying to connect to a glove.
        {
            std::cout << ("Failed to Detect a Haptic Glove on your System. Please ensure your device is paired or connected via USB.") << std::endl;
            std::cout << ("Press Return to try again...") << std::endl;
            system("pause");
            gloveAmount = HandLayer::GlovesConnected();
        }

        // When we get here, we've got one glove connected. Yay.

        if (gloveAmount == 1) {
            std::cout << ("There is 1 Haptic Glove connected to your system.") << std::endl;
            bool rightHand = HandLayer::GetFirstGloveHandedness();
            std::cout << "It is a ";
            std::cout << (rightHand ? "Right" : "Left");
            std::cout << " handed glove of type " + SGDevice::ToString( HandLayer::GetDeviceType(rightHand) ) << std::endl;
        } else {
            std::cout << ("There are " + std::to_string( gloveAmount ) + " Haptic Gloves connected to your system.") << std::endl;

            if (HandLayer::DeviceConnected(true)) {
                std::cout << ("The right hand is a " + SGDevice::ToString( HandLayer::GetDeviceType(true) )) << std::endl;
            } else {
                std::cout << ("There is no right hand connected.") << std::endl;
            }

            if (HandLayer::DeviceConnected(false)) {
                std::cout << ("The left hand is a " + SGDevice::ToString( HandLayer::GetDeviceType(false) )) << std::endl;
            } else {
                std::cout << ("There is no left hand connected.") << std::endl;
            }
        }
        std::cout << ("-------------------------------------------------------------------------") << std::endl;
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Force-Feedback Command(s)
    {
        //Toggles FFB for the first 3 fingers; thumb, index, and middle finger.
        std::vector<float> fingerFfb = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };//there's 5 fingers.
        for (int32_t f = 0; f < 3; f++) {
            EFinger finger = static_cast<EFinger>(f);
            std::cout << ("Press a key to turn on the Force-Feedback of the " + SGCore::Util::StringUtils::ToString(finger) ) << std::endl;
            system("pause");

            fingerFfb[f] = 1.0f;//sets the finger ffb for the current finger to 100%
            //Queue these for the left / right hand, and send them immediately afterward
            HandLayer::QueueCommand_ForceFeedbackLevels(true, fingerFfb, true);
            HandLayer::QueueCommand_ForceFeedbackLevels(false, fingerFfb, true);

            std::cout << ("Press a key to turn it back off") << std::endl;
            system("pause");

            fingerFfb[f] = 0.0f;//sets the finger ffb for the current finger back to 0%.
            //Queue these for the left / right hand, and send them immediately afterward
            HandLayer::QueueCommand_ForceFeedbackLevels(true, fingerFfb, true);
            HandLayer::QueueCommand_ForceFeedbackLevels(false, fingerFfb, true);
        }
        std::cout << ("-------------------------------------------------------------------------") << std::endl;
    }


    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Vibration Command
    {
        std::cout << ("Press a key to send a vibration to both hands.") << std::endl;
        system("pause");

        float amplitude = 1.0f; //100% intensity
        float duration = 0.200f;//200 ms
        float frequency = 80.0f;//80 Hz
        EHapticLocation location = EHapticLocation::WholeHand;
        std::cout << "Sending a vibration of " + std::to_string(duration) + "s, amplitude " + std::to_string(amplitude) + " and Fequency of " + std::to_string((int32_t) frequency)
            + "Hz to " + HapticGlove::ToString(location) << std::endl;
        TestVibration(true, amplitude, duration, frequency, location);
        TestVibration(false, amplitude, duration, frequency, location);

        std::cout << ("-------------------------------------------------------------------------") << std::endl;
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Active Contact Feedback (Nova 2.0 only)
    {
        if (HandLayer::SupportsWristSqueeze(true) || HandLayer::SupportsWristSqueeze(false)) {
            std::cout << ("Press a key to activate active contact feedback (wrist squeeze) on the hand(s)") << std::endl;
            system("pause");

            HandLayer::QueueCommand_WristSqueeze(true, 1.0f, true);
            HandLayer::QueueCommand_WristSqueeze(false, 1.0f, true);

            std::cout << ("Press a key to dectivate it") << std::endl;
            system("pause");

            HandLayer::QueueCommand_WristSqueeze(true, 0.0f, true);
            HandLayer::QueueCommand_WristSqueeze(false, 0.0f, true);

            std::cout << "-------------------------------------------------------------------------" << std::endl;
        }
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Finger Tracking
    {
        std::cout << ("Let's test out some finger tracking next") << std::endl;

        TestHandTracking(true);
        TestHandTracking(false);

        std::cout << ("-------------------------------------------------------------------------") << std::endl;
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // 6Dof Wrist Tracking
    {
        std::cout << ("Finally, we'll test wrist tracking") << std::endl;

        TestWristTracking(true);
        TestWristTracking(false);
    }


    std::cout << "=========================================================================" << std::endl;
    std::cout << "Press any key to exit." << std::endl;
    system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file