/*
Calibration Example using the SenseGlove.
*/

#include <iostream>		// Output to console

#include "Library.h"	// Access library details
#include "DeviceList.h" // Access devices and communication state
#include "SenseGlove.h" // SenseGlove interface through which we access data.

/// <summary> Replace "static void CalibrationExample()" with int main() to compile as a console application. </summary>
static void CalibrationExample()
//int main()
{
	std::cout << "Calibration example using " << SGCore::Library::Version() << std::endl;
	std::cout << "=======================================" << std::endl;

	if (SGCore::DeviceList::SenseCommRunning()) //check if the Sense Comm is running. If not, warn the end user.
	{
		SGCore::SG::SenseGlove testGlove;
		if (SGCore::SG::SenseGlove::GetSenseGlove(testGlove)) //retrieves the first Sense Glove it can find. Returns true if one can be found
		{
			std::cout << "Connected to a " << (testGlove.IsRight() ? "right" : "left") << "-handed SenseGlove. Staring calibration" << std::endl;

			/*
			Our goal is to find the min / max sensor values, which correspond to the user opening their hand and making a fist.
			We can only update this range after parsing sensor data, which happens when accessing sensorData, glovePoses or handPoses.
			In our VR use cases, we pull new hand data each frame, and so this min/max range is updated automatically.
			In this example, we will update the range twice; once when the hand is 'open', once when it is closed into a fist.
			*/

			// Step 1: Open hand - Calibrates extension
			std::cout << std::endl;
			std::cout << "Step 1: Place your hand on a flat surface, like a table, and spread your thumb and fingers." << std::endl;
			// Once you get the hang of this motion, you can do it without the surface.
			std::cout << "Once your hand is in the right position, press any key to continue" << std::endl;
			system("pause");

			// This function updates the calibration range of testGlove.
			testGlove.UpdateCalibrationRange(); // Instead of this method, you can also use the GetSensorData(), GetGlovePose() or GetHandPose function instead.


			// Step 2: Fist - Calibrates flexion
			std::cout << std::endl;
			std::cout << "Step 2: Close your hand into a fist. Make sure your fingers aren't wrapped around your thumb." << std::endl;
			std::cout << "Once your hand is in the right position, press any key to continue" << std::endl;
			system("pause");

			// This function updates the calibration range of testGlove. 
			testGlove.UpdateCalibrationRange();


			// At this point, we've collected data while the hand was open, and when it was closed. 
			// The calibration range should now have the two extremes to interpolate between.
			// Let's check & ouput the ranges:
			std::vector<SGCore::Kinematics::Vect3D> minRanges, maxRanges;
			testGlove.GetCalibrationRange(minRanges, maxRanges);

			// The calibration ranges contain the x, y, z values, which represent the pronation/supination, flexion/extension, and abduction/adduction movements respectively, in radians. 
			// For readability's sake, we'll print out the flexion/extension values in degrees.
			float rad2Deg = 180 / M_PI;
			std::cout << std::endl << "Evaluated the following calibration range for extension/flexion" << std::endl;
			std::cout << "Extensions: ";
			for (int f = 0; f < minRanges.size(); f++)
			{
				std::cout << std::to_string((int)(rad2Deg * minRanges[f].y));
				if (f < minRanges.size() - 1) { std::cout << ", "; }
			}
			std::cout << std::endl << "Flexions: ";
			for (int f = 0; f < maxRanges.size(); f++)
			{
				std::cout << std::to_string((int)(rad2Deg * maxRanges[f].y));
				if (f < maxRanges.size() - 1) { std::cout << ", "; }
			}
			std::cout << std::endl;

			// Now we apply the calibration to a default profile
			SGCore::HandProfile cachedProfile = SGCore::HandProfile::Default(testGlove.IsRight()); //a default profile for the right-sided glove.
			testGlove.ApplyCalibration(cachedProfile);

			// And can now use it to calculate handPoses
			SGCore::HandPose handPose;
			if (testGlove.GetHandPose(cachedProfile, handPose))
			{
				std::cout << std::endl << "With these ranges, we've calculated the following hand angles:" << std::endl;
				std::cout << handPose.ToString() << std::endl;
			}
			else
			{
				std::cout << "Something went wrong while trying to calucate a handPose. Perhaps a packet was dropped or an exception occurs." << std::endl;
			}

			// Finally, we can store the profile in its serialized form to use later
			std::string serializedProfile = cachedProfile.Serialize();

			// And Deserialize it back into a useable profile
			SGCore::HandProfile loadedProfile = SGCore::HandProfile::Deserialize(serializedProfile);
		}
	}
	else
	{
		std::cout << "SenseComm is not running. Please start it and try again." << std::endl;
	}
	std::cout << "=======================================" << std::endl;
	std::cout << "Press any key to exit." << std::endl;
	system("pause");
}

