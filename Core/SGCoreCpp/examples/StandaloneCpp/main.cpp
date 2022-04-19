// SGCoreCpp_Standalone.cpp : Example to show how to build a SenseGlove project that's independent of the SenseCom program.
//

#include <iostream>
#include "SGConnect.h"
#include "DeviceList.h"
#include "SenseGlove.h"
#include "Library.h"

#include <thread>
#include <chrono> //wait untill we find SenseGloves

int main()
{
	std::cout << "Standalone Communications using " << SGConnect::GetLibraryVersion() << " and " << SGCore::Library::Version() << std::endl;
	std::cout << "============================================================================================" << std::endl << std::endl;

	std::cout << "The SGConnect library allows us to initialize and detect SenseGloves and other SenseGlove Devices" << std::endl;

	//---------------------------------------------------------------------------
	// SGConnect Initalization - Parts taken from the SGConnect example code.

	SGConnect::SetDebugLevel(0); //0 disables the Devug level, 1 shows you only the errors.

	bool scanActive = SGConnect::ScanningActive(); //this returns true if there is already a SGConnect process running (For instance, from SenseCom)
	if (!scanActive)
	{
		std::cout << "We call SGConnect::Init() to startup a background process, which will begin scanning for SenseGlove devices." << std::endl;
		int initCode = SGConnect::Init();
		if (initCode > 0)
		{
			std::cout << "Succesfully initialized background process: (InitCode = " << std::to_string(initCode) << ")" << std::endl;
			std::cout << "This process will begin connecting to ports that should belong to SenseGlove devices." << std::endl;
			std::cout << "It will take a few seconds before the devices appear to the SenseGlove API, especially when using Bluetooth devices." << std::endl;
			std::cout << "Below, you will see debug messages appear from the background process. Press return when you see one appear, or when you're ready to end." << std::endl;
			std::cout << "" << std::endl;
			while (std::cin.get() != '\n') {} //Wait for the user to confirm before continuing.
			std::cout << "" << std::endl;
		}
		else
		{
			std::cout << "Oddly enough, we could not initialize the SGConnect library. (InitCode = " << std::to_string(initCode) << ")" << std::endl;
			std::cout << "Please close this program, and try again." << std::endl;
		}
	}
	else
	{
		std::cout << "A SenseGlove scanning process is already running (ScanState " << std::to_string(SGConnect::ScanningState()) << " > 0)." << std::endl;
		std::cout << "Seeing as we've just started up, it can't possibly be this process that did it." << std::endl;
		std::cout << "It is safe to call SGConnect::Init() even if this is the case, but no new process will be started." << std::endl;
		int initCode = SGConnect::Init();
		std::cout << "The SGConnect::Init() will return 0, to let us know no Initialization was done: " << std::to_string(initCode) << std::endl << std::endl;
		std::cout << std::endl;
		
	}

	//---------------------------------------------------------------------------
	// SGCoreCpp  - Parts taken from the SGCoreCpp example code.

	{
		// For a more practical example: Let's assume this is 1 frame of your simulation.
		// You've defined which glove you want to use (left/right) - in this case, let's use the same side as our testGlove.

		std::shared_ptr<SGCore::HapticGlove> glove;
		if (SGCore::HapticGlove::GetGlove(glove))
		{
			//Step 1: Hand Pose

			// We want to get the pose of the hand - to animate a virtual model
			SGCore::HandPose handPose; //The handPose class contains all data you'll need to animate a virtual hand
			if (glove->GetHandPose(handPose)) //returns the HandPose based on the latest device data, using the latest Profile and the default HandGeometry
			{
				std::cout << "Retrieved the latest Hand Pose from " + glove->ToString() + ". The ToString() function reports important finger angles, in degrees, in our coodinate system:" << std::endl;
				std::cout << handPose.ToString() << std::endl;

				// The HandPose is still in our Coordinate System, relative to the wrist.
				// You'll need to convert our Vect3D and Quats to your own coordinate system. You can find an explanation of our Coordinate system at docs.senseglove.com/

				// We also offer "normalized" angles : Which gives you the total flexion of the finger(s) as a value between 0 and 1,
				// where 0 represents the fingers fully extended, and 1 represents the finger fully flexed.
				std::vector<float> flexions = handPose.GetNormalizedFlexion();
				std::string flexes = "";
				for (int i = 0; i < flexions.size(); i++)
				{
					flexes += std::to_string((int)std::round(flexions[i]));
					if (i < flexions.size() - 1) { flexes += ", "; }
				}
				std::cout << "Normalized finger flexions [" + flexes + "]" << std::endl;
				std::cout << std::endl;
			}
			else //This function could return false if no data for this glove is available (yet).
			{
				std::cout << "Something went wrong trying to access the HandPose of " + glove->ToString() + ". Try again later.";
			}


			//Step 2: Wrist Location

			// The glove does not come with a built-in hand tracking. I want to know the location of the wrist in 3D space - to determine my finger locations, for example.
			// Let's say we've connected a Vive Tracker to the glove - and we know it's position / location
			SGCore::PosTrackingHardware tracker = SGCore::PosTrackingHardware::ViveTracker;
			SGCore::Kinematics::Vect3D trackerPosition = SGCore::Kinematics::Vect3D::zero; //set at 0, 0, 0
			SGCore::Kinematics::Quat trackerRotation = SGCore::Kinematics::Quat::identity; //no rotation either.

			SGCore::Kinematics::Vect3D wristPosition;
			SGCore::Kinematics::Quat wristRotation;
			glove->GetWristLocation(trackerPosition, trackerRotation, tracker, wristPosition, wristRotation);

			std::cout << "If your tracked device (" + SGCore::Tracking::ToString(tracker) + ") is at position " + trackerPosition.ToString() + ", and rotation " + trackerRotation.ToEuler().ToString()
				+ ", your wrist position is " + wristPosition.ToString() + ", with rotation at " + wristRotation.ToEuler().ToString() << std::endl;
			std::cout << std::endl;

			// Now that you know both the wrist location and the handPose, you can apply these to your 3D Hand model. Since this is a Console Application, we're skipping that part.


			//Step 3: Haptics

			// Let's say we've animated our hand, and determined that we need a force the index finger
			// Force is defined between 0% and 100% of the force.

			std::cout << "We've determined that we want Force-Feedback on the Index finger. Press Return to apply it." << std::endl;
			system("pause");

			//We create a new Force-Feedback Command
			SGCore::Haptics::SG_FFBCmd ffb(0, 100, 0, 0, 0); //sets each of the fingers to a desired level [thumb ... pinky]
			glove->SendHaptics(ffb); //and send it to the SendHaptics Command

			// In a normal scenario, you'll send the up to date levels each frame. Note that the glove will only respond to the latest command. They are not cumulative!
			// E.g. when calling
			// glove.SendHaptics( new SGCore.Haptics.SG_FFBCmd(0, 100, 0, 100, 0) );
			// glove.SendHaptics( new SGCore.Haptics.SG_FFBCmd(100, 80, 0, 0, 0) );
			// Only the last command is sent to the glove. FFB on the ring finger will not turn on.

			std::cout << std::endl;
			std::cout << "Now that the Force-Feedback is on, you can press Return again to cancel it." << std::endl;
			system("pause");

			glove->StopHaptics(); //turns off all Vibration and Force-Feedback. 
			// Alternatively, you could call glove->SendHaptics(SGCore::Haptics::SG_FFBCmd::off);

			//If we wanted to send vibration to the fingers, we send a BuzzCmd:
			SGCore::Haptics::SG_BuzzCmd buzz(0, 100, 0, 0, 0); //sets each of the fingers to a desired level [thumb ... pinky]

			std::cout << std::endl;
			std::cout << "Let's send some vibrations; press Return to vibrate the Index finger." << std::endl;
			system("pause");

			glove->SendHaptics(buzz);

			// Normally, you'd need to keep track of how long you want the glove to vibrate. Use callbacks or events. In this console app, we'll use Sleep();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			glove->StopVibrations(); //Stops all vibrations on the glove.
			// Alternatively, we could have used glove.SendHaptics(SGCore.Haptics.SG_BuzzCmd.Off);

			std::cout << "That was a brief introduction into Tracking and Haptics. Check out more examples at docs.senseglove.com!" << std::endl;
		}
		//If there is glove connected, we don't need to do anything this frame.
	}


	//---------------------------------------------------------------------------
	// SGConnect Cleanup - Parts taken from the SGConnect example code.
	
	std::cout << std::endl;
	if (!scanActive)
	{
		int disposeCode = SGConnect::Dispose();
		if (disposeCode > 0)
		{
			std::cout << "Succesfully cleaned up SGConnect resources: (DisposeCode = " << std::to_string(disposeCode) << ")" << std::endl;
			std::cout << "It's now safe to exit the program. Press return to end." << std::endl;
		}
		else
		{
			std::cout << "Unable to properly dispose of SGConnect resources: (DisposeCode = " << std::to_string(disposeCode) << ")." << std::endl;
			std::cout << "Fortunately, closing this process will cause them to go out of scope and be destroyed either way." << std::endl;
		}
	}
	else
	{
		std::cout << "Since this process did not start SGConnect, we don't need to clean anything up." << std::endl;
		std::cout << "We can call SGConnect::Dispose() safely, but this will not stop the original process." << std::endl;
		int disposeVal = SGConnect::Dispose();
		std::cout << "The SGConnect::Dispose() will return a value that is not 1, to let us know nothing was Disposed of: " << std::to_string(disposeVal) << std::endl;
		std::cout << "If you wish to dispose of the already running process, you should call SGConnect::Dispose() from the program that originally called SGConnect::Init()" << std::endl;
	}

	while (std::cin.get() != '\n') {} //Wait for the user to confirm before exiting.


	//// SGConnect Initialization
	//bool alreadyRunning = SGConnect::ScanningActive(); //this function tells us if there is already a scanner active.
	//if (alreadyRunning)
	//{
	//	std::cout << "Another program is already scanning, so we will skip the init method right now." << std::endl;
	//}
	//else
	//{
	//	std::cout << "Initializing SenseGlove Communications." << std::endl;
	//	SGConnect::Init();
	//	std::cout << "Done!" << std::endl;
	//}

	//std::cout << "Now that we have scanning up and running, we should wait for the Sense Glove to connect." << std::endl;
	//system("pause");
	//std::cout << std::endl;
	//int attempts = 0;
	//SGCore::SG::SenseGlove testGlove;
	//bool gloveFound = false;

	//do
	//{
	//	gloveFound = SGCore::SG::SenseGlove::GetSenseGlove(testGlove);
	//	attempts++;
	//	if (!gloveFound)
	//	{
	//		std::cout << "Checking for SenseGloves..." << std::endl;
	//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	//	}
	//} while (!gloveFound && attempts < 10);

	//if (gloveFound)
	//{
	//	std::cout << "Found a Device! Lets begin" << std::endl;

	//	//Begin Section of SGCPP
	//	std::cout << "Activating " << testGlove.ToString() << std::endl;

	//	testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd(0, 80, 0, 0, 0)); //vibrate the index fingerat 80% intensity.
	//	std::this_thread::sleep_for(std::chrono::milliseconds(200)); //vibrating for for 200ms.

	//	testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd::off); //turn off all Buzz Motors.
	//	std::this_thread::sleep_for(std::chrono::milliseconds(10)); //wait for 10ms.

	//	SGCore::SG::SG_GloveInfo model = testGlove.GetGloveModel(); //Retrieve device information
	//	std::cout << std::endl;
	//	std::cout << model.ToString(true) << std::endl; //Log some basic information to the user. (true indicates a short notation is desired)

	//	//Retrieving Sensor Data (raw). The lowest level data available
	//	SGCore::SG::SG_SensorData sensorData;
	//	if (testGlove.GetSensorData(sensorData)) //if GetSensorData is true, we have sucesfully recieved data
	//	{
	//		std::cout << std::endl;
	//		std::cout << sensorData.ToString() << std::endl;
	//	}

	//	//Retrieving Glove Pose: The position / rotation of the glove, as well as its sensor angles placed in the right direction.
	//	SGCore::SG::SG_GlovePose glovePose;
	//	if (testGlove.GetGlovePose(glovePose))
	//	{
	//		//As an example, lets calculate fingertip positions.

	//		//If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
	//		SGCore::SG::SG_HandProfile handProfile = SGCore::SG::SG_HandProfile::Default(testGlove.IsRight()); //create a default profile, either left or right.
	//		std::vector<SGCore::Kinematics::Vect3D> tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position

	//		std::cout << std::endl;
	//		for (int f = 0; f < tipPositions.size(); f++)
	//			std::cout << std::to_string(((SGCore::Finger)f)) << ": " << tipPositions[f].ToString() << std::endl; //writes "thumb: ", "index: " etc.

	//		float dThumbIndex = tipPositions[0].DistTo(tipPositions[1]); //calculates the distance between thumb (0) and index finger (1), in mm.
	//		std::cout << "The distance between thumb and index finger is " << std::to_string(dThumbIndex) << "mm." << std::endl;
	//	}

	//	//End Section of SGCPP

	//}
	//else
	//{
	//	std::cout << "Still no SenseGloves found. Please try again" << std::endl;
	//}

	//std::cout << std::endl << "Press any key to end. While SGConnect's resources are disposed of during GC, "
	//	<< "it is good practice to dispose of them ouselves if we started them up." << std::endl;
	//system("pause");

	//// SGConnect Dispose
	//if (!alreadyRunning)
	//{
	//	std::cout << std::endl << "This program initialized the SenseGlove Communications, so we should properly end them." << std::endl;
	//	std::cout << "Disposing..." << std::endl;
	//	SGConnect::Dispose();
	//	std::cout << "Done!" << std::endl;
	//}
}