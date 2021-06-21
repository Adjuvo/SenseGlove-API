#pragma once

#include "SGCore.h"
#include "HG_CalibrationSequence.h"

namespace SGCore
{
	namespace Calibration
	{
		class SGCORE_API HG_QuickCalibration : public HG_CalibrationSequence
		{
            //--------------------------------------------------------------------------------------
            // Member Variables

        protected:

            /// <summary> Time after you've first started moving. </summary>
            float movedTime;

            bool newProfile = true;

        public:

            /// <summary> time, in seconds, after which this sequence stops gathering data. Based on the DeltaTime variable passed in the Update() function. </summary>
            float autoEndAfter;

            /// <summary> Default time in seconds, to end this sequence. 15 seconds is very quick for some people. </summary>
            const static float autoEndTime;

            /// <summary> When compiling the final profile, we use a Weighted Moving Average filter with this period to filer out some outliers. </summary>
            int smoothingSamples = 5;

            /// <summary> The min/max values recorded during this calibration sequence. </summary>
            SensorRange sensorRange;
            /// <summary> A temporary profile to apply the sensorRange to. Used to generate a 'preview' HandPose. </summary>
            SGCore::HandProfile tempProfile;

            /// <summary> Determines if the user has moved enough so that we can animate. </summary>
            bool canAnimate;

            //--------------------------------------------------------------------------------------
            // Member Variables

            /// <summary> Create a new instance of a QuickCalibration for Haptic Gloves. </summary>
            /// <param name="gloveToCalibrate"></param>
            /// <param name="endAfter_s"></param>
            HG_QuickCalibration(std::shared_ptr<SGCore::HapticGlove> gloveToCalibrate, float endAfter_s = autoEndTime);

            //--------------------------------------------------------------------------------------
            // Accessors

            /// <summary> This sequence autocmpletes after its autoEndTime has elapsed. </summary>
            bool AutoCompleted() override;

            //--------------------------------------------------------------------------------------
            // Sequence Functions

            /// <summary> After we confirm the current step, we're basically done. </summary>
            void ConfirmCurrentStep() override;


            /// <summary> Resets datapoints, min/max ranges and profile. </summary>
            void Reset() override;

            /// <summary> Update this calibration sequence with new data. We use deltaTime to check for things like stability. </summary>
            /// <param name="deltaTime_s"></param>
            void Update(float deltaTime_s) override;


            /// <summary> Add a new datapoint to this sequence's collection. Updates the range and profile used to generate a preview. </summary>
            /// <param name="calibrationData"></param>
            void AddDataPoint(std::vector<Kinematics::Vect3D>& calibrationData) override;

            //--------------------------------------------------------------------------------------
            // Profile Functions

            /// <summary> Compile a sensor range from the data points collected while the sequence was running. Smoothed by a Moving Average Filter. </summary>
            /// <param name="range"></param>
            /// <returns></returns>
            bool CompileRange(SensorRange& range) override;


            //--------------------------------------------------------------------------------------
            // Utility Functions

            /// <summary> Retrieve instructions on what to do during the current step.  </summary>
            /// <param name="nextStepKey"></param>
            /// <returns></returns>
            std::string GetCurrentInstuction(std::string nextStepKey = "") override;

            /// <summary> Returns a 'preview' of what a HandPose with this sequence's current settings would look like.  </summary>
            /// <param name="rightHand"></param>
            /// <param name="currentPose"></param>
            /// <returns></returns>
            bool GetHandPose(bool rightHand, HandPose& currentPose) override;

		};
	}
}
