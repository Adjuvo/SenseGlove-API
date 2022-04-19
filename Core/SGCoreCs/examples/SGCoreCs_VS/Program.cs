/*
 * Example code on how to interface with SenseGlove Devices.
 * This is the source code for the program in the SGCoreCs/test folder.
 * We're using brackets { } around each section.
 */


using System;
using SGCore; //All SenseGlove classes are contained in this namespace


namespace CsCoreClient
{
	class Program
	{
		//static void RunBase()
		static void Main(string[] args)
		{
			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
			// Checking the Library

			// Displaying Library information - Useful to know when asking for any kind of support
			Console.Write("Testing " + SGCore.Library.Version + ", compiled for " + SGCore.Library.BackEndVersion());
			if (SGCore.Library.GetBackEndType() == SGCore.Library.BackEndType.SharedMemory) // By default, your library will be compiled to use Shared Memory via the SGConnect library
            {
				Console.Write(" using " + SGCore.Library.SGConnectVersion); //If you replace SGConnect.dll, this will give you its current version number.
            }
			Console.WriteLine("");
			Console.WriteLine("The source code for this program is located in the SGCoreCs/test/ folder.");
			Console.WriteLine("=========================================================================");


			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
			// Ensuring connectivity

			// Connecting to SenseGlove devices is done in a separate "Connection Process" - contained in the SGConnect library.
			// We can test if this Connection Process is running on this PC. Usually, it runs inside SenseCom.
			// It's good practice to start this process if your user has not sone so yet.
			{
				bool connectionsActive = SGCore.SGConnect.ScanningActive(); //returns true if SenseCom (or another program) has started the SenseGlove Communications Process.
				if (!connectionsActive) // If this process is not running yet, we can "Force-Start" SenseCom. Provided it has run on this PC at least once.
				{
					Console.WriteLine("SenseCom is not yet running. Without it, we cannot connect to SenseGlove devices.");
					bool startedSenseCom = SGCore.SenseCom.StartupSenseCom(); //Returns true if the process was started.
					if (startedSenseCom)
					{
						Console.WriteLine("Successfully started SenseCom. It will take a few seconds to connect...");
						connectionsActive = SGCore.SGConnect.ScanningActive(); //this will return false immedeately after you called StartupSenseCom(). Because the program has yet to initialize.
																			   // Even if SenseCom started and the connections process is active, there's no guarantee that the user has turned their device(s) on. More on that later.
					}
					else // If StartupSenseCom() returns false, you've either never run SenseCom, or it is already running. But at that point, the ScanningActive() should have returned true. 
					{
						Console.WriteLine("Could not Start the SenseCom process.");
					}
					Console.WriteLine();
				}
			}


			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
			// Accessing Haptic Gloves

			// You interface with SenseGlove devices through an instance of a HapticGlove class.
			// At any point in your program, you can try to grab a SenseGlove Device. There's no guarantee that one is connected, though.
			// Let's try and grab a Haptic Glove, a class from which both our Nova Glove and SenseGlove DK1 Exoskeletons derive.
			// Using the HapticGlove as opposed to the specific Nova / SenseGlove class allows your software to be compatible with both types of devices (as well as any other types of gloves we add later).
			{
				SGCore.HapticGlove testGlove; //SGCore.HapticGlove - The class from which all of our gloves derive.
				bool gotHapticGlove = SGCore.HapticGlove.GetGlove(out testGlove); //GetGlove returns the first glove connected to your system - doesn't care if it's a left or a right hand.
				while (!gotHapticGlove) //For this exercise, I'll keep trying to connect to a glove.
				{
					Console.WriteLine("Failed to Detect a Haptic Glove on your System. Please ensure your device is paired or connected via USB.");
					Console.WriteLine("Press Return to try again...");
					Console.ReadLine();
					gotHapticGlove = SGCore.HapticGlove.GetGlove(out testGlove);
				}

				// If we were looking for a specific hand, we can pass a boolean to the GetGlove function. I know you have at least one - or you wouldn't have passed this section.
				
				SGCore.HapticGlove leftGlove, rightGlove;
				bool gotLeft  = SGCore.HapticGlove.GetGlove(false, out leftGlove); // passing false returns the first connected left hand
				bool gotRight = SGCore.HapticGlove.GetGlove(true,  out rightGlove); // passing true returns the first connected right hand

				// Alternatively, you can get a list of all connected Haptic Gloves on your system
				SGCore.HapticGlove[] allGloves = SGCore.HapticGlove.GetHapticGloves();

				Console.WriteLine("There are " + allGloves.Length + " Haptic Glove(s) connected to your system.");

				if (gotLeft)
				{ Console.WriteLine("Your Left hand is " + leftGlove.ToString()); }
				else
				{ Console.WriteLine("You have no left hands connected to your system."); }

				if (gotRight)
				{ Console.WriteLine("Your Right hand is " + rightGlove.ToString()); }
				else
				{ Console.WriteLine("You have no right hands connected to your system."); }

				Console.WriteLine("The first Haptic Glove connected to your system is " + testGlove.ToString() + " - we will use this one for testing.");
				Console.WriteLine();
			}


			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
			// Using a Haptic Glove instance

			// SenseGlove Devices are chached inside the SGCore library. The GetGloves() function returns a reference to them, not a copy.
			// Let's pretend this is a frame of your simulation
			// Once you have a HapticGlove instance , you request specific data.
			{
				// Basic Device Information
				bool rightHand = true; // I'm going to use this for the next part of this test.
				SGCore.HapticGlove testGlove;
				if (SGCore.HapticGlove.GetGlove(out testGlove)) //remember, if this function returns true, we've succesfully connected to a Glove.
                {
					rightHand = testGlove.IsRight();	//Returns true if this is a right hand. If false, this is a left hand.
					string deviceID = testGlove.GetDeviceID();	//The Device's Unique Identifier. Useful if you have multiple of them.
					string type = testGlove.GetDeviceType().ToString(); //The DeviceType (SenseGlove DK1, SenseGlove Nova, etc.)
					Console.WriteLine( deviceID + " is a " + (rightHand ? "Right" : "Left") + " hand whose deviceType is " + type);
                }
				// if the above returned false, there is no glove. So there's no use to run the tests.


				// For a more practical example: Let's assume this is 1 frame of your simulation.
				// You've defined which glove you want to use (left/right) - in this case, let's use the same side as our testGlove.

				SGCore.HapticGlove glove;
				if (SGCore.HapticGlove.GetGlove(rightHand, out glove))
                {
					//Step 1: Hand Pose

					// We want to get the pose of the hand - to animate a virtual model
					SGCore.HandPose handPose; //The handPose class contains all data you'll need to animate a virtual hand
					if (glove.GetHandPose(out handPose)) //returns the HandPose based on the latest device data, using the latest Profile and the default HandGeometry
                    {
						Console.WriteLine("Retrieved the latest Hand Pose from " + glove.ToString() + ". The ToString() function reports important finger angles, in degrees, in our coodinate system:");
						Console.WriteLine(handPose.ToString());

						// The HandPose is still in our Coordinate System, relative to the wrist.
						// You'll need to convert our Vect3D and Quats to your own coordinate system. You can find an explanation of our Coordinate system at docs.senseglove.com/

						// We also offer "normalized" angles : Which gives you the total flexion of the finger(s) as a value between 0 and 1,
						// where 0 represents the fingers fully extended, and 1 represents the finger fully flexed.
						float[] flexions = handPose.GetNormalizedFlexion();
						string flexes = "";
						for (int i=0; i<flexions.Length; i++)
                        {
							flexes += System.Math.Round(flexions[i], 2).ToString();
							if (i < flexions.Length - 1) { flexes += ", "; }
                        }
						Console.WriteLine("Normalized finger flexions [" + flexes + "]");
						Console.WriteLine("");
					}
					else //This function could return false if no data for this glove is available (yet).
					{
						Console.WriteLine("Something went wrong trying to access the HandPose of " + glove.ToString() + ". Try again later.");
                    }


					//Step 2: Wrist Location

					// The glove does not come with a built-in hand tracking. I want to know the location of the wrist in 3D space - to determine my finger locations, for example.
					// Let's say we've connected a Vive Tracker to the glove - and we know it's position / location
					PosTrackingHardware tracker = PosTrackingHardware.ViveTracker;
					SGCore.Kinematics.Vect3D trackerPosition = SGCore.Kinematics.Vect3D.zero; //set at 0, 0, 0
					SGCore.Kinematics.Quat trackerRotation = SGCore.Kinematics.Quat.identity; //no rotation either.

					SGCore.Kinematics.Vect3D wristPosition;
					SGCore.Kinematics.Quat wristRotation;
					glove.GetWristLocation(trackerPosition, trackerRotation, tracker, out wristPosition, out wristRotation);

					Console.WriteLine("If your tracked device (" + tracker.ToString() + ") is at position " + trackerPosition.ToString() + ", and rotation " + trackerRotation.ToEuler().ToString()
						+ ", your wrist position is " + wristPosition.ToString() + ", with rotation at " + wristRotation.ToEuler().ToString());
					Console.WriteLine();

					// Now that you know both the wrist location and the handPose, you can apply these to your 3D Hand model. Since this is a Console Application, we're skipping that part.


					//Step 3: Haptics

					// Let's say we've animated our hand, and determined that we need a force the index finger
					// Force is defined between 0% and 100% of the force.

					Console.WriteLine("We've determined that we want Force-Feedback on the Index finger. Press Return to apply it.");
					Console.ReadKey();

					//We create a new Force-Feedback Command
					SGCore.Haptics.SG_FFBCmd ffb = new SGCore.Haptics.SG_FFBCmd(0, 100, 0, 0, 0); //sets each of the fingers to a desired level [thumb ... pinky]
					glove.SendHaptics(ffb); //and send it to the SendHaptics Command

					// In a normal scenario, you'll send the up to date levels each frame. Note that the glove will only respond to the latest command. They are not cumulative!
					// E.g. when calling
					// glove.SendHaptics( new SGCore.Haptics.SG_FFBCmd(0, 100, 0, 100, 0) );
					// glove.SendHaptics( new SGCore.Haptics.SG_FFBCmd(100, 80, 0, 0, 0) );
					// Only the last command is sent to the glove. FFB on the ring finger will not turn on.

					Console.WriteLine();
					Console.WriteLine("Now that the Force-Feedback is on, you can press Return again to cancel it.");
					Console.ReadKey();

					glove.StopHaptics(); //turns off all Vibration and Force-Feedback. 
					// Alternatively, you could call glove.SendHaptics(SGCore.Haptics.SG_FFBCmd.Off);

					//If we wanted to send vibration to the fingers, we send a BuzzCmd:
					SGCore.Haptics.SG_BuzzCmd buzz = new SGCore.Haptics.SG_BuzzCmd(0, 100, 0, 0, 0); //sets each of the fingers to a desired level [thumb ... pinky]

					Console.WriteLine();
					Console.WriteLine("Let's send some vibrations; press Return to vibrate the Index finger.");
					Console.ReadKey();

					glove.SendHaptics(buzz);

					// Normally, you'd need to keep track of how long you want the glove to vibrate. Use callbacks or events. In this console app, we'll use Sleep();
					System.Threading.Thread.Sleep(500);

					glove.StopVibrations(); //Stops all vibrations on the glove.
					// Alternatively, we could have used glove.SendHaptics(SGCore.Haptics.SG_BuzzCmd.Off);

					Console.WriteLine("That was a brief introduction into Tracking and Haptics. Check out more examples at docs.senseglove.com!");
				}
				//If there is no more glove, we don't need to do anything this frame.
			}

			Console.WriteLine("=========================================================================");
			Console.WriteLine("Press any key to exit.");
			Console.ReadKey();
		}
	}
}
