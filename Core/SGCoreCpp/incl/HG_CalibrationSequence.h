#pragma once

#include "SGCore.h"
#include <vector>
#include "CalDataPoint.h"
#include "HapticGlove.h"
#include "BasicHandModel.h"
#include "CalDataPoint.h"
#include "SensorRange.h"

namespace SGCore
{
	namespace Calibration
	{
        /// <summary> A sequence which collects data points untill specific criteria have been met. It must be 'fed' an Update command from your program in order to work. </summary>
        class SGCORE_API HG_CalibrationSequence
        {
            //--------------------------------------------------------------------------------------
            // Member Variables
        protected:

            /// <summary> Glove linked to this calibration sequence. Will attempt to gram data from this glove evey time Update() is called. </summary>
            std::shared_ptr<SGCore::HapticGlove> iGlove = nullptr;

          

            /// <summary> Basic constructor for subclasses to inherit from </summary>
            HG_CalibrationSequence() { }


            bool needHandModel = true;
            /// <summary> Kinematic information to generate a calibration preview pose. </summary>
            SGCore::Kinematics::BasicHandModel handModel;

        public:

            /// <summary> Calibration points colledted during this calibration process. One is added every thme the "Update()" function is called.
            /// Used to create a profile after the calibration finishes. </summary>
            std::vector<CalDataPoint> calibrationPoints = { };

            /// <summary> The maximum buffer size for calibration points. Once calibrationPoints exceeds this value, the  </summary>
            const static int maxDataPoints = 60000;

            /// <summary> How much time has elapsed during this calibration sequence. Useful for logging or for automated functions. </summary>
            float elapsedTime = 0;

            /// <summary> Used to determine if the user has manually ended the sequence, to prevent us from adding any more calibration points. </summary>
            bool manualCompleted = false;

            

            //--------------------------------------------------------------------------------------
            // Construction

            /// <summary> Create a new instance of a base HapitcGlove Calibration Sequence. </summary>
            /// <param name="gloveToCalibrate"></param>
            HG_CalibrationSequence(std::shared_ptr<SGCore::HapticGlove> gloveToCalibrate)
            {
                iGlove = gloveToCalibrate;
                Reset();
            }

            //--------------------------------------------------------------------------------------
            // Accessors

            /// <summary> If a sequence consists of multiple stages, this integer will show you which one is currently active. </summary>
            virtual int CurrentStageInt() { return -1;  }

            /// <summary> The Glove linked to this Calibration Sequence. Can be changed or re-assigned. </summary>
            std::shared_ptr<SGCore::HapticGlove> GetLinkedGlove() { return iGlove; }
            void SetLinkedGlove(std::shared_ptr<SGCore::HapticGlove> glove) { iGlove = glove; }


            /// <summary> Returns the amount of calibration points collected so far </summary>
            int DataPointCount()
            {
                return this->calibrationPoints.size();
            }

            /// <summary> Whether or not this sequence was completed as per it's own rules </summary>
            /// <returns></returns>
            virtual bool AutoCompleted()
            {
                return false;
            }


            /// <summary> Returns true if this sequence is marked as 'complete' and can begin compiling a profile. </summary>
            virtual bool Completed()
            {
                return this->AutoCompleted() || this->manualCompleted;
            }


            void SetHandModel(Kinematics::BasicHandModel geometry);

            Kinematics::BasicHandModel GetHandModel();


            //--------------------------------------------------------------------------------------
            // Sequence Functions

            /// <summary> Resets this calibration sequence's data, but not it's LinkedGlove. </summary>
            virtual void Reset()
            {
                this->calibrationPoints.clear();
                elapsedTime = 0;
                manualCompleted = false;
            }


            /// <summary> Safely adds calibration data. Automatically done within 'Update' </summary>
            /// <param name="calibrationData"></param>
            virtual void AddDataPoint(std::vector<Kinematics::Vect3D>& calibrationData) //we can add by refrence here because calDataPoint's constrctor copies it as well.
            {
                if (calibrationPoints.size() > maxDataPoints - 1) { calibrationPoints.erase(calibrationPoints.begin()); }
                calibrationPoints.push_back( CalDataPoint(CurrentStageInt(), calibrationData) );
            }

            /// <summary> Update this calibration sequence with new data. We use deltaTime to check for things like stability. </summary>
            /// <param name="deltaTime_s"></param>
            virtual void Update(float deltaTime_s)
            {
                if (!Completed())
                {
                    elapsedTime += deltaTime_s;
                    std::vector<Kinematics::Vect3D> calData;
                    if (iGlove != nullptr && iGlove->GetCalibrationValues(calData))
                    {
                        this->AddDataPoint(calData);
                    }
                }
            }

            /// <summary> Manual confirmation of whatever step we're supposed to making at the moment. </summary>
            virtual void ConfirmCurrentStep() { }


            //--------------------------------------------------------------------------------------
            // Profile Generation

            /// <summary> Compile a min/max range from the datapoints collected by this sequence. Returns true if it's actually possible. </summary>
            /// <param name="range"></param>
            /// <returns></returns>
            virtual bool CompileRange(SensorRange& range)
            {
                range = SensorRange();
                return false;
            }


            /// <summary> Compile a profile from the datapoints collected by this sequence. Returns true if it's actually possible.  </summary>
            /// <param name="forDevice"></param>
            /// <param name="rightHand"></param>
            /// <param name="profile"></param>
            /// <returns></returns>
            virtual bool CompileProfile(SGCore::DeviceType forDevice, bool rightHand, SGCore::HandProfile& profile)
            {
                profile = SGCore::HandProfile::Default(rightHand);
                return false;
            }

            /// <summary> Converts a calibration range taken from a Calibration sequence, and converts it into a profile. Use this if you're not actually using the sequence. </summary>
            /// <param name="range"></param>
            /// <param name="forDevice"></param>
            /// <param name="rightHand"></param>
            /// <param name="profile"></param>
            /// <returns></returns>
            static bool CompileProfile(SensorRange range, SGCore::DeviceType forDevice, bool rightHand, SGCore::HandProfile& profile);

            //--------------------------------------------------------------------------------------
            // Utility Functions

            /// <summary> Returns the current HandPose; either the one we should be making, or what it would look like at the moment.  </summary>
            /// <param name="currentPose"></param>
            /// <returns></returns>
            bool GetHandPose(SGCore::HandPose& currentPose)
            {
                if (this->iGlove != nullptr)
                {
                    return GetHandPose(iGlove->IsRight(), currentPose);
                }
                return false;
            }


            /// <summary> Returns the current HandPose; either the one we should be making, or what it would look like at the moment.  </summary>
            /// <param name="rightHand"></param>
            /// <param name="currentPose"></param>
            /// <returns></returns>
            virtual bool GetHandPose(bool rightHand, SGCore::HandPose& currentPose)
            {
                return false;
            }


            /// <summary> Retrieve instructions on what to do during the current step. </summary>
            /// <returns></returns>
            virtual std::string GetCurrentInstuction(std::string nextStepKey = "")
            {
                if (nextStepKey.length() > 0) { return "Press [" + nextStepKey + "] for the next step."; }
                return "";
            }

        };
	}
}
