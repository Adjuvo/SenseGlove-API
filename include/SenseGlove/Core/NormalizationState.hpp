/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2023 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Enumerators for sensor normalization
 */


#pragma once

#include <cstdint>

#include "Platform.hpp"

namespace SGCore
{
    namespace Nova
    {
        /// <summary> State of the Nova's sensor Normalization.  </summary>
        enum class SGCORE_API ENormalizationState : uint8_t
        {
            /// <summary> Unable to retrieve the state out of our Sensor Data :( </summary>
            Unknown = 1,

            /// <summary> Developer has asked the glove to send raw data. So  </summary>
            SendingRawData,

            /// <summary> The glove is currently normalzing, but the fingers haven't moved enough. </summary>
            Normalizing_MoveFingers,

            /// <summary> Fires when all fingers have moved enough and you _could_ stop normalization collection. </summary>
            Normalizing_AwaitConfirm,

            /// <summary> Normalization is completed. The user  </summary>
            NormalizationFinished

        };
    }// namespace Nova
}// namespace SGCore