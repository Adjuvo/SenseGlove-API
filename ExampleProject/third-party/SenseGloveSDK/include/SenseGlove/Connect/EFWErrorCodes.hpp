/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2026 SenseGlove
 *
 * @section Keeps track of the various codes / ssues that could occur when one is running a firmware upload.
 *
 */


#pragma once

#include <cstdint>

#include <SenseGlove/Common/Platform.hpp>

namespace SGConnect
{
    /// <summary> Exit Codes for Firmware uploads - tell us why something did not work - or if it did. </summary>
    enum class SGCONNECT_API EFWErrorCodes : int8_t
    {
        /// <summary> Unknown Exit Code  </summary>
        Unknown,

        //-------------------------------------------------------------------------------------
        // Everything that can go wrong at startup

        /// <summary> Successfully Initialized a worker thread to upload Firmware. Exuberance! </summary>
        StartupInitialized, // == 1

        /// <summary> Successfully uploaded firmware, yay! </summary>
        UploadCompleted,// == 2 putting this here to it's 2 and a static number even if I add more error codes. It's also 2, so first you check == 1, then == 2.

        /// <summary> An exception has occured, but SGConnect has caught it. Your code is safe. But check your logs! </summary>
        SGConnectException,

        /// <summary> You're calling upload firmware, but you're not the one hosting the process... </summary>
        NotHostingProcess,

        /// <summary> No device with this index exists. You may have called this after a SenseCom crash! </summary>
        InvalidDeviceIndex,

        /// <summary> Firmware is already in the process of being uploaded! </summary>
        UploadInProgress,

        /// <summary> This Device is Null for some reason. This should not happend by should be chekced for regardless </summary>
        DeviceNULL,

        /// <summary> This device is already connected! </summary>
        DeviceNotConnected,

        /// <summary> Chunk Size <= 0 </summary>
        InvalidChunkSize,

        /// <summary> path is empty! </summary>
        EmptyPath,

        /// <summary> It;s now a .bin file </summary>
        UnsupportedFileType,

        /// <summary> An exception occured but we were able to catch it in the Startup phase. Check your logs. </summary>
        StartUploadException,

        //-------------------------------------------------------------------------
        // Everything that can go wrong inside the worker thread.

        /// <summary> The file could not be found </summary>
        NoFileExists,

        /// <summary> Fiel path is empty </summary>
        FileEmpty,

        /// <summary> An error occured while reading the file </summary>
        ErrorReadingFile,

        /// <summary> The initial command timed out. Could not verify that the SG has received it! </summary>
        InitialCommandTimeout,

        /// <summary> Error processing initial command. Don't worry, no data has been exchanged yet. But we might need a restart. </summary>
        InitialCommandError,


        /// <summary> There was an error sending over some data at one point... </summary>
        ChunkError,

        /// <summary> We timed out while waiting for a response on our next chunk... </summary>
        ChunkTimeout,

        /// <summary> We were almost there! But there was no response to my final validation :< </summary>
        FinalConfimrationError,

        /// <summary> At some point while uploading I lost connection :< </summary>
        DisconnectedDuringUpload,


        /// <summary> An exception occured but we were able to catch it in the worker thread. Check your logs. </summary>
        UploadThreadException,

        /// <summary> This is not supported in the current build of SGConnect, for this platform. </summary>
        NotSupportedInBuild,

        /// <summary> Did not receive constants from the device after a restart :< </summary>
        NoConstantsReceived,

        //--------------------------------------------------------------------------------------------------------------------
        // Special Cases

        AwaitingConfirmation,

        DeviceNotSupported,

    };
}