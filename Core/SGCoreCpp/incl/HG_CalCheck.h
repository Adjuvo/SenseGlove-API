#pragma once

#include "SGCore.h"
#include "SensorRange.h"
#include "DeviceTypes.h"
#include <vector>

namespace SGCore
{
	namespace Calibration
	{
        //--------------------------------------------------------------------------------------
        // Calibration Checking Stage

        /// <summary> Startup Stage used to indicate where of not a glove must be recalibrated. </summary>
        enum SGCORE_API CalibrationStage
        {
            /// <summary> We've only just started up. User needs to move their hands so we know if we're still in the same sensor range. </summary>
            MoveFingers,
            /// <summary> After moving, we've determined that a calibration must happen for proper hand tracking to happen. </summary>
            CalibrationNeeded,
            /// <summary> After moving, we've determined that a calibration must happen for proper hand tracking to happen. </summary>
            Calibrating,
            /// <summary> We've determined that this needs no (more) calibration to function as intended. </summary>
            Done
        };


        /// <summary> An algorithm that checks whether or not our current user is running in the same calibration range as last time. </summary>
        class SGCORE_API HG_CalCheck
        {

        protected:

            /// <summary> The current stage of this algorithm </summary>
            CalibrationStage calibrationStage;

            bool firstRange;
            bool brokenRange;

        public:

            //--------------------------------------------------------------------------------------
            // Member Variables

            /// <summary> The calibration range from last time, that we are checking against. </summary>
            SensorRange lastRange;

            /// <summary> The calibration range measured as of right now. </summary>
            SensorRange currentRange;


            //When the user is at roughtly the right thresholds.

            /// <summary> If we're 'around' the lastRange for this amount of time, we're calling it 'done'. </summary>
            float perfectThresholdTime = 0.5f;
            /// <summary> Time that we've been around the last range for. </summary>
            float timer_atThreshold = 0;


            //Checks for when the user's fingers are much smaller, and can therefore not reach the extremes.

            /// <summary> Whether or not we've moved a minimum amount. Something that even someone with the smallest hands can do. </summary>
            bool movedMinimum = false;
            /// <summary> After moving the minimum amount of time but not reaching the perivous range, we'll say the hand is too small. </summary>
            float minMoveTime = 3.0f;
            /// <summary> Time since we made the minumum amount of movement </summary>
            float timer_MinMove = 0.0f;

            // When one or more of the sensors are suffuciently out of bounds to cause concern

            /// <summary> The amount of time the current values can be out of range for. Catches a minor case where sensor jitter causes us to be outside of the range. </summary>
            float outOfBoundsTime = 0.1f;
            /// <summary> Time we've been out of bounds for. </summary>
            float timer_outOfBounds = 0;



            //--------------------------------------------------------------------------------------
            // Accessors

            /// <summary> Whether or not his algorithm has determined if calibration is required. </summary>
            bool ReachedConclusion();

            CalibrationStage GetCalibrationStage();

            //--------------------------------------------------------------------------------------
            // Construction

            /// <summary> The last calibration range can be null, at which point you defnitely need calibration. </summary>
            /// <param name="lastCalibrationRange"></param>
            HG_CalCheck();

            /// <summary> The last calibration range can be null, at which point you defnitely need calibration. </summary>
            /// <param name="lastCalibrationRange"></param>
            HG_CalCheck(SGCore::Calibration::SensorRange& lastCalibrationRange);


            //--------------------------------------------------------------------------------------
            // Functions

            /// <summary> Reset the calibrationCheck. so it may be used again. This does not reset the LastRange. </summary>
            void Reset();

            /// <summary> Using the currently received Sensor Values, check if calibration is required. This function will have to be called until a conclusion can be reached. </summary>
            /// <param name="currentValues"></param>
            /// <param name="deltaTime_s"></param>
            /// <param name="deviceType"></param>
            void CheckRange(std::vector<Kinematics::Vect3D>& currentValues, float deltaTime_s, DeviceType deviceType);



            //------------------------------------------------------------------------------------------------------------------------------------------------------------------
            // Static Checker Functions

            /// <summary> SenseGlove: How far from the threshold one can be where we would still call it 'the same as before' </summary>
            const static float sgThreshold;
            /// <summary> Nova: How far from the threshold one can be where we would still call it 'the same as before' </summary>
            const static float novaThreshold;

            /// <summary> SenseGlove: The minumum amount of sensor flexion movement before we start testing for a smaller hand. </summary>
            const static float sgMinFlex;
            /// <summary> Nova: The minumum amount of sensor flexion movement before we start testing for a smaller hand. </summary>
            const static float novaMinFlex;

            /// <summary> SenseGlove: The minumum amount of sensor movement on the thumb abduction before we start testing for a smaller hand. </summary>
            const static float sgMinAbd;
            /// <summary> Nova: The minumum amount of sensor movement on the thumb abduction before we start testing for a smaller hand. </summary>
            const static float novaMinAbd;


            /// <summary> Returns true if this DeviceType requires a calibration check. </summary>
            /// <param name="device"></param>
            /// <returns></returns>
            static bool NeedsCheck(SGCore::DeviceType device);


            /// <summary> Checks if current values are operating out of the previous range. Returns -1 if all is fine. 0...4 to indicate which finger is out of bounds. </summary>
            /// <param name="previousRange"></param>
            /// <param name="currentValues"></param>
            /// <param name="type"></param>
            /// <returns></returns>
            static int OutOfBounds(SensorRange& previousRange, std::vector<Kinematics::Vect3D>& currentValues, SGCore::DeviceType type);


            /// <summary> Returns true if the user has moved enough in both flexion and thumb abduction movement to be considered 'active' </summary>
            /// <param name="currentRange"></param>
            /// <param name="type"></param>
            /// <returns></returns>
            static bool MovedMinimum(std::vector<Kinematics::Vect3D>& currentRange, SGCore::DeviceType type);



            /// <summary> Returns true if the current sensor values have moved roughly as much as last time. </summary>
            /// <param name="currentRange"></param>
            /// <param name="lastRange"></param>
            /// <param name="type"></param>
            /// <returns></returns>
            static bool MatchesLast(std::vector<Kinematics::Vect3D>& currentRange, std::vector<Kinematics::Vect3D>& lastRange, SGCore::DeviceType type);


        };
    }
}