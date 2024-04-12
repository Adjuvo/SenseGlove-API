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
 * Internal class used to encode / decode Nova Waveforms. Not used outside the
 * API.
 */

#pragma once

#include "Platform.hpp"
#include "Values.hpp"

namespace SGCore
{
    /// <summary> A single vibration pulse for Nova Gloves. </summary>
    class SGCORE_API CustomWaveform;

    namespace Nova
    {
        /// <summary> Internal class used to encode / decode Nova Waveforms. </summary>
        class NovaGloveHapticEncoder;
    }
}// namespace SGCore

/// <summary> Internal class used to encode / decode Nova Waveforms. </summary>
class SGCore::Nova::NovaGloveHapticEncoder
{
    //-----------------------------------------------------------------------------------------------------------------------------------
    // Custom Waveform Encoding

public:
    //-----------------------------------------------------------------------------------------------------------------------------------
    // Vibrotactile Constants

    /// <summary> The maximum attack time, in seconds. Used for Encoding. </summary>
    static float GetMinAttackTime();// = 0.0f;
    /// <summary> The maximum attack time, in seconds. Used for Encoding. </summary>
    static float GetMaxAttackTime();// = 1.0f;

    /// <summary> The minimum value for sustain time, in seconds. Used for Encoding. </summary>
    static float GetMinSustainTime();// = 0.0f;
    /// <summary> The maximum sustain time, in seconds. Used for Encoding. </summary>
    static float GetMaxSustainTime();// = 1.0f;

    /// <summary> The maximum attack time, in seconds. Used for Encoding. </summary>
    static float GetMinDecayTime();// = 0.0f;
    /// <summary> The maximum attack time, in seconds. Used for Encoding. </summary>
    static float GetMaxDecayTime();// = 1.0f;

    /// <summary> Minimum Frequency Range </summary>
    static float GetMinFreqRange();// = 10.0f;
    /// <summary> Maximum Frequency Range </summary>
    static float GetMaxFreqRange();// = 500.0f;

    /// <summary> Maximum amount a signal is allowed to repeat, limited by encoding. </summary>
    static int32_t GetMaxRepeatAmount();// = 100;

    /// <summary> The minimum master control 'volume'. </summary>
    static float GetMinAmplitude();// = 0.0f;
    /// <summary> The maximum master control 'volume'. </summary>
    static float GetMaxAmplitude();// = 1.0f;

    /// <summary> Minimum value of minimum frequency factor </summary>
    static float GetMinFreqFactor();// = 1.0f;
    /// <summary> Maximum value of minimum frequency factor</summary>
    static float GetMaxFreqFactor();// = 3.0f;

    /// <summary> Encode a 'repeat' byte based on the amount of times someone wants to repeat it, vs whether or not its
    /// set to bInfinite. </summary>
    /// <param name="repeatAmount"></param>
    /// <param name="bInfinite"></param>
    /// <returns></returns>
    static int32_t RepeatByte(int32_t repeatAmount, bool bInfinite);

    /*
    * A new special command
    * {Znasdwf1f2rd1d2s1s2m}
    *   1. actuator [1=thumper, 2=lra1, 3=lra2]
        2. attack [1=80 frames (=0.01sec) ... 101 = 8000 frames (= 1.0sec)]
        3. sustain ["]
        4. decay ["]
        5. wave [1=sine, 2=square, 3=sawup, 4=sawdown, 5=triangle, 6=noise]
        6. start frequency [1=10hz, 101=500Hz]
        7. end frequency [1=10hz, 101=500Hz]
        8. repeat [1=inf, 2..101:1-100]
        9. dutycycle [not used, keep at 51]
        10. duyshift [not used, keep at 1]
        11. frequency switch [1=1x time (default) 101= 3x times]
        12. frequenct time switch [1 = at 0% of (attack/sustain/decay), 51= at 50%]
        13. master = [1=0, 101=100%]
    */

    /// <summary> Encodes the values of a CustomWaveform into a command that can be sent to the Nova Glove. </summary>
    /// <param name="waveform"></param>
    /// <param name="motor"></param>
    /// <returns></returns>
    static std::string ToNovaCommand(const CustomWaveform& waveform, int32_t motor);

    static std::string ToNova2Command(const CustomWaveform& waveform, int32_t motor);

    /// <summary> Decode a command back into a waveform (though it won't be exactly the same due to the resolution of
    /// said encoding). </summary>
    /// <param name="command"></param>
    /// <param name="waveform"></param>
    /// <param name="location"></param>
    /// <returns></returns>
    static bool DecodeWaveform(const std::string& command, CustomWaveform& out_waveform, int32_t& out_motor);

    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    NovaGloveHapticEncoder() = delete;
    virtual ~NovaGloveHapticEncoder() = delete;
};