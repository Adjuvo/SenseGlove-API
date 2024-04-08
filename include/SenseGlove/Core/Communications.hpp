/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2024 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Contains internal enumerators and classes for raw byte communications with
 * Sense Glove Devices.
 */


#pragma once

#include <cstdint>
#include <vector>
#include "Platform.hpp"

namespace SGCore
{
    namespace Util
    {
        /// <summary> Indices to access DeviceList data in Shared Memory. </summary>
        enum class EListFormat : uint8_t
        {
            Connected = 0,
            PacketsPerSecondGot,
            DeviceType,
            ConstantsString,
            Address,
            ConnectionType,
            PacketsPerSecondSent,
            IPCChannels,
            All,
        };

        /// <summary> Indices to access Sensor Data in Shared Memory. </summary>
        enum class ESensorFormat : uint8_t
        {
            Sensors
        };

        class SGCORE_API Communications;
    }// namespace Util
}// namespace SGCore

/// <summary> "Database" containing communications bytes and conversions. </summary>
class SGCORE_API SGCore::Util::Communications
{
public:
    /// <summary> Byte indicating the start of a new command. </summary>
    SG_NODISCARD static char GetCommandOpen();

    /// <summary> Byte indicating the end of a command. </summary>
    SG_NODISCARD static char GetCommandClose();

    /// <summary> Byte indicating the start of a new sensor data package. </summary>
    SG_NODISCARD static char GetSenseOpen();

    /// <summary> Byte indicating the end of a sensor data package. </summary>
    SG_NODISCARD static char GetSenseClose();

    /// <summary> Denotes a block section of a DeviceList section. </summary>
    SG_NODISCARD static char GetListDelimiter();

    /// <summary> ':' - Used to split a set of different constant values into individual groups. </summary>
    SG_NODISCARD static char GetSectionDelimiter();

    /// <summary> ';' - Used to separate individual values </summary>
    SG_NODISCARD static char GetColumnDelimiter();

    /// <summary> '|' - Used to group a set of values, for example per finger. </summary>
    SG_NODISCARD static char GetRowDelimiter();

    /// <summary> Convert a value between 0..100 to a Sense Glove char/byte. </summary>
    SG_NODISCARD static char ToSGByte(int32_t level);

    /// <summary> Convert a value between 0..1 to a Sense Glove char/byte. </summary>
    SG_NODISCARD static char FloatToSGByte(float level01);

    /// <summary> Encode a series of floating-point values into a SenseGlove string </summary>
    /// <param name="values01"> An array of values that is to be encoded into multiple characters </param>
    /// <param name="messageLength"> The length of the message. </param>
    /// <param name="fallbackValue"> If values01 is not long enough to reach messageLength, pad valued with this </param>
    /// <returns></returns>
    SG_NODISCARD static std::string ToSGBytes(const std::vector<float>& values01, int32_t messageLength, float fallbackValue = 0.0f);

    /// <summary> Encode a single value into a character into a range of bytes. Will alsways clamp! </summary>
    /// <param name="value"></param>
    /// <param name="minValue"></param>
    /// <param name="maxValue"></param>
    /// <param name="minByte"></param>
    /// <param name="maxByte"></param>
    /// <returns></returns>
    SG_NODISCARD static int32_t EncodeLinear(float value, float minValue, float maxValue, int32_t minByte = 1, int32_t maxByte = 101);

    /// <summary> Convert a decoded byte back into its original floating value. Useful for decoding. </summary>
    /// <param name="byteFromChar"></param>
    /// <param name="minValue"></param>
    /// <param name="maxValue"></param>
    /// <param name="minByte"></param>
    /// <param name="maxByte"></param>
    /// <returns></returns>
    SG_NODISCARD static float DecodeLinear(int byteFromChar, float minValue, float maxValue, int32_t minByte = 1, int32_t maxByte = 101);

public:
    Communications() = delete;
    virtual ~Communications() = delete;
};