#pragma once

#include "SGCore.h"
#include <vector>
#include "Vect3D.h"
#include "Nova_Profile.h"

namespace SGCore
{
    namespace Calibration
    {
        class SGCORE_API Nova_Calibration
        {
        public:

            /// <summary> Apply a glove's default interpolation values to a profile, using the 'default' hand angles from calibration </summary>
            static void ApplyInterpolationValues_DefaultCalibration(std::vector<Kinematics::Vect3D>& retractedValues, std::vector<Kinematics::Vect3D>& extendedValues, Nova::Nova_Profile& profile);


            /// <summary> Apply a set of sensor-to-joint-angle interplations to a nova profile. </summary>
            /// <param name="retractedValues"></param>
            /// <param name="extendedValues"></param>
            /// <param name="retractedAngles"></param>
            /// <param name="extendedAngles"></param>
            /// <param name="profile"></param>
            static void ApplyInterpolationValues(std::vector<Kinematics::Vect3D>& retractedValues, std::vector<Kinematics::Vect3D>& extendedValues,
                std::vector<std::vector<Kinematics::Vect3D>>& retractedAngles, std::vector<std::vector<Kinematics::Vect3D>>& extendedAngles, Nova::Nova_Profile& profile);
        };
    }
}
