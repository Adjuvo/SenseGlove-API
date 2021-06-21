#pragma once

#include "SGCore.h"
#include <vector>
#include "Vect3D.h"
#include <string>

namespace SGCore
{
    namespace Calibration
    {
        class SGCORE_API CalDataPoint
        {
        public:

            /// <summary> Actual calibration values. </summary>
            std::vector<Kinematics::Vect3D> calibrationValues;

            /// <summary> The Calibration stage this data point belongs to. </summary>
            int stage;

            /// <summary> Create a new data point </summary>
            /// <param name="currSate"></param>
            /// <param name="calVals"></param>
            CalDataPoint(int currSate, std::vector<Kinematics::Vect3D> calVals);

            /// <summary> Log Calibration values for storing on disk </summary>
            /// <param name="delim"></param>
            /// <returns></returns>
            std::string ToLogData(std::string delim = "\t");
        };
    }
}
