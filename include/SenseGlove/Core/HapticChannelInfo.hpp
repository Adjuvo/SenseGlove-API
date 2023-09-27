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
 * Contains information on Haptic channels available to this device for IPC.
 * Some devices have different "Haptic Channels". This info is exposed via IPC to SGCore.
 */


#pragma once

#include <memory>

#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    /// <summary> Different types of Haptic Channels - with different behaviours </summary>
    enum class SGCORE_API EHapticChannelType : int8_t
    {
        /// <summary> This type of haptic channel can be constantly overridden. SGConnect will only send a command if a change occurs. Ideal for Force-Feedback. </summary>
        StreamingChannel,
        /// <summary> These commands must be sent once, after thire queue is cleared. </summary>
        FireAndForgetChannel
    };

    /// <summary> Contains information on Haptic channels available to this device for IPC. </summary>
    class SGCORE_API HapticChannelInfo;
}// namespace SGCore

/// <summary> Contains information on Haptic channels available to this device for IPC. </summary>
class SGCORE_API SGCore::HapticChannelInfo
{
    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /**
     * The copy constructor.
     */
    HapticChannelInfo(const HapticChannelInfo& rhs);

    /**
     * The move constructor.
     */
    HapticChannelInfo(HapticChannelInfo&& rhs)
    noexcept;

    virtual ~HapticChannelInfo();


    /**
     * The copy assignment operator.
     */
    HapticChannelInfo& operator=(const HapticChannelInfo& rhs);

    /**
     * The move assignment operator.
     */
    HapticChannelInfo& operator=(HapticChannelInfo&& rhs) noexcept;

public:
    

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    /// <summary> Creates a default HapticChannelInfo, with solely a single streaming haptic Channel </summary>
    HapticChannelInfo();

    HapticChannelInfo(const std::vector<int32_t>& streamInd, const std::vector<int32_t>& fireNforgetInd);

    //---------------------------------------------------------------------------------
    // Accessors

public:

    /// <summary> Byte used to identify streaming channels </summary>
    SG_NODISCARD static int32_t GetStreamingType();
    /// <summary> byte used to indicate fire-and-forget channels. </summary>
    SG_NODISCARD static int32_t GetFireNForgetType();


    //---------------------------------------------------------------------------------
    // Member Functions

public:

    /// <summary> Returns the amount of streaming channels available for haptics. Will indicate if a device can support the haptics you're trying to send through it. </summary>
    /// <returns></returns>
    SG_NODISCARD int32_t GetStreamChannelCount();

    /// <summary> Returns the amount of fire-and-forget channels available for haptics. Will indicate if a device can support the haptics you're trying to send through it. </summary>
    /// <returns></returns>
    SG_NODISCARD int32_t GetFireAndForgetChannelCount();

    /// <summary> retrieve the total amount of channels for this device. </summary>
    /// <returns></returns>
    SG_NODISCARD int32_t GetTotalChannelCount();

    /// <summary> Returns the address that corresponds to the nth channel of a specific type. It's unguarded, which means I dont check the validity of index - could result in an exception. Optimized piece of code for for loops. </summary>
    /// <param name="type"></param>
    /// <param name="typeIndex"></param>
    /// <returns></returns>
    SG_NODISCARD std::string GetAddress_Unguarded(EHapticChannelType type, int32_t typeIndex);

    /// <summary> Returns the address that corresponds to the nth channel of a specific type. It's unguarded, which means I dont check the validity of index - could result in an exception. Optimized piece of code for for loops. Used for Internals </summary>
    /// <param name="type"></param>
    /// <param name="typeIndex"></param>
    /// <param name="addressString"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    void GetIPCParams_Unguarded(EHapticChannelType type, int32_t typeIndex, int32_t& out_index, std::string& out_addressString);


    /// <summary> Regenerate the channel names for a specific device Index in shared memory. </summary>
    /// <param name="forDeviceIndex"></param>
    void RegenerateAddresses(int32_t forDeviceIndex);

    /// <summary> Returns an array of all the haptic addrsses stored for this info channel. </summary>
    /// <returns></returns>
    SG_NODISCARD std::vector<std::string> GetAllAddresses();


    /// <summary> Generate a single IPCAddress for an address. </summary>
    /// <param name="deviceIndex"></param>
    /// <param name="channelIndex"></param>
    /// <returns></returns>
    SG_NODISCARD static std::string GenerateAddress(int32_t deviceIndex, int32_t channelIndex);


    /// <summary> Parse HapticChannelInfo received through IPC into useable data </summary>
    /// <param name="ipcString"></param>
    /// <returns></returns>
    SG_NODISCARD static HapticChannelInfo Parse(std::string ipcString);
};
