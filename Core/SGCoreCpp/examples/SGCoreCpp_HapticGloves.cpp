/*
A console application demonstrating the intended use of a SenseGlove interface.
Used to compile the programs in the SGCoreCpp/test folder.
*/

#include <iostream> //Output to console

#include <thread>  //To pause the main() while vibrating
#include <chrono>  //To pause the thread for std::chrono::seconds

#include "Library.h"	// Access library details
#include "DeviceList.h" // Access devices and communication state
#include "SenseGlove.h" // SenseGlove interface through which we access SenseGlove data.
#include "NovaGlove.h" // SenseGlove interface through which we access Nova data.
#include "Debugger.h"

/// <summary> Replace "static void BasicTest()" with int main() to compile as a console application. </summary>
//static void HapticGloveTests()
int main()
{
	std::cout << "Testing " + SGCore::Library::Version() + " compiled for " + SGCore::Library::BackEndVersion() << std::endl;
	std::cout << "=======================================" << std::endl;

	SGCore::Diagnostics::Debugger::debugLevel = SGCore::Diagnostics::DebugLevel::ERRORSONLY;

	if (SGCore::DeviceList::SenseCommRunning())
	{
		std::cout << "Grabbing a glove to test..." << std::endl;
		std::shared_ptr<SGCore::HapticGlove> testGlove;
		if (SGCore::HapticGlove::GetGlove(testGlove)) //if this function returns true, we found a connected glove, and testGlove is assigned.
		{
			bool rightHanded = testGlove->IsRight();
			SGCore::DeviceType deviceType = testGlove->GetDeviceType();

			std::cout << "We've found a " << (rightHanded ? "right" : "left") << "-handed " << (deviceType == SGCore::DeviceType::NOVA ? "Nova" : "Sense") << " Glove!" << std::endl;
			std::cout << "Press a key to make it vibrate!" << std::endl;
			system("pause");

			std::cout << std::endl;
			if (deviceType == SGCore::DeviceType::NOVA) { testGlove->SendHaptics(SGCore::Haptics::ThumperCmd(80)); } //vibrate wrist at 80%
			else if (deviceType == SGCore::DeviceType::SENSEGLOVE) { testGlove->SendHaptics(SGCore::Haptics::SG_BuzzCmd(SGCore::Finger::Index, 100)); } //vibrate index finger at 100%
			std::this_thread::sleep_for(std::chrono::milliseconds(500)); //vibrate for 500ms
			testGlove->StopHaptics(); //turn off vibratin

			std::cout << "Press a key to access tracking data" << std::endl;
			system("pause");

			//Generate a default profile for now.
			SGCore::HandProfile defaultProfile = SGCore::HandProfile::Default(rightHanded);

			if (deviceType == SGCore::DeviceType::NOVA)
			{
				std::shared_ptr<SGCore::Nova::NovaGlove> nova =	std::dynamic_pointer_cast<SGCore::Nova::NovaGlove> (testGlove);
				std::cout << "Since this is a Nova Glove, calibration is required. I'll instead grab some Sensor Data" << std::endl;
				SGCore::Nova::Nova_SensorData novaData;
				if (nova->GetSensorData(novaData))
				{
					std::cout << novaData.ToString() << std::endl;
				}
				else { std::cout << "Something went wrong while retrieving data..." << std::endl; }


				// Nova sensors are relative to where they started, and everyone's range is different. So it needs to be calibrated.
				// For more in-depth explanation, check SGCoreCpp_Calibration.cpp in the examples folder.

				// First, let's see if someone's already been calibrated.
				SGCore::HandProfile cachedProfile = SGCore::HandProfile::Default(testGlove->IsRight()); //a default profile for the right-sided glove.
				if (SGCore::HandProfile::GetLatestProfile(testGlove->IsRight(), cachedProfile) && !cachedProfile.Equals(defaultProfile))
				{
					std::cout << std::endl;
					std::cout << "Loaded a valid calibration profile from " << SGCore::HandProfile::GetProfileDir() << ", so we're skipping Steps 1 and 2." << std::endl;
				}
				else
				{
					// Step 1: Open hand - Calibrates extension
					std::cout << std::endl;
					std::cout << "Step 1: Place your hand on a flat surface, like a table, and spread your thumb and fingers." << std::endl;
					std::cout << "Once your hand is in the right position, press any key to continue" << std::endl;
					system("pause");
					testGlove->UpdateCalibrationRange(); // Instead of this method, you can also use the GetSensorData(), GetGlovePose() or GetHandPose function instead.

					// Step 2: Fist - Calibrates flexion
					std::cout << std::endl;
					std::cout << "Step 2: Close your hand into a fist. Make sure your fingers aren't wrapped around your thumb." << std::endl;
					std::cout << "Once your hand is in the right position, press any key to continue" << std::endl;
					system("pause");
					testGlove->UpdateCalibrationRange();

					// We have a min / max range.
					// Now we apply the calibration to a default profile
					testGlove->ApplyCalibration(cachedProfile);

					// Let's save it for next time:
					SGCore::HandProfile::StoreProfile(cachedProfile);
				}

				std::cout << std::endl;
				std::cout << "Step 3: Make any pose with your hand." << std::endl;
				std::cout << "Once your hand is in the right position, press any key to calculate it." << std::endl;
				system("pause");

				// And can now use it to calculate handPoses
				SGCore::HandPose handPose;
				if (testGlove->GetHandPose(cachedProfile, handPose))
				{
					std::cout << std::endl << "With these ranges, we've calculated the following hand angles:" << std::endl;
					std::cout << handPose.ToString() << std::endl;
				}
				else
				{
					std::cout << "Something went wrong while trying to calucate a handPose. Perhaps a packet was dropped or an exception occurs." << std::endl;
				}
			}
			else
			{
				std::cout << "Since this is a SenseGlove, no calibration is required." << std::endl;
				SGCore::HandPose handPose;
				if (testGlove->GetHandPose(defaultProfile, handPose))
				{
					std::cout << handPose.ToString() << std::endl;
				}
				else { std::cout << "Something went wrong while retrieving data..." << std::endl; }
			}
		}
		else
		{
			std::cout << "There are no Haptic Gloves connected to your system. Please ensure your device is paired or connected via USB." << std::endl;
		}
	}
	else
	{
		std::cout << "SenseCom process is not running. Please start it and try again!" << std::endl;
	}


	std::cout << "=======================================" << std::endl;
	std::cout << "Press any key to exit." << std::endl;
	system("pause");
}

