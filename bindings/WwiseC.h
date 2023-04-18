// wwise-c headers are manually copied and edited code from Wwise SDK so I put the original license here
/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2023 Audiokinetic Inc.
*******************************************************************************/
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __cplusplus
#include <stdbool.h>
#include <wchar.h> // wchar_t not a built-in type in C
#endif

#include <AK/AkPlatforms.h>

#if !defined(AK_WIN)
#define AKSOUNDENGINE_CALL
#endif

    // BEGIN AkTypes
    typedef AkUInt32 WWISEC_AkUniqueID;          ///< Unique 32-bit ID
    typedef AkUInt32 WWISEC_AkStateID;           ///< State ID
    typedef AkUInt32 WWISEC_AkStateGroupID;      ///< State group ID
    typedef AkUInt32 WWISEC_AkPlayingID;         ///< Playing ID
    typedef AkInt32 WWISEC_AkTimeMs;             ///< Time in ms
    typedef AkUInt16 WWISEC_AkPortNumber;        ///< Port number
    typedef AkReal32 WWISEC_AkPitchValue;        ///< Pitch value
    typedef AkReal32 WWISEC_AkVolumeValue;       ///< Volume value( also apply to LFE )
    typedef AkUInt64 WWISEC_AkGameObjectID;      ///< Game object ID
    typedef AkReal32 WWISEC_AkLPFType;           ///< Low-pass filter type
    typedef AkInt32 WWISEC_AkMemPoolId;          ///< Memory pool ID
    typedef AkUInt32 WWISEC_AkPluginID;          ///< Source or effect plug-in ID
    typedef AkUInt32 WWISEC_AkCodecID;           ///< Codec plug-in ID
    typedef AkUInt32 WWISEC_AkAuxBusID;          ///< Auxilliary bus ID
    typedef AkInt16 WWISEC_AkPluginParamID;      ///< Source or effect plug-in parameter ID
    typedef AkInt8 WWISEC_AkPriority;            ///< Priority
    typedef AkUInt16 WWISEC_AkDataCompID;        ///< Data compression format ID
    typedef AkUInt16 WWISEC_AkDataTypeID;        ///< Data sample type ID
    typedef AkUInt8 WWISEC_AkDataInterleaveID;   ///< Data interleaved state ID
    typedef AkUInt32 WWISEC_AkSwitchGroupID;     ///< Switch group ID
    typedef AkUInt32 WWISEC_AkSwitchStateID;     ///< Switch ID
    typedef AkUInt32 WWISEC_AkRtpcID;            ///< Real time parameter control ID
    typedef AkReal32 WWISEC_AkRtpcValue;         ///< Real time parameter control value
    typedef AkUInt32 WWISEC_AkBankID;            ///< Run time bank ID
    typedef AkUInt32 WWISEC_AkBankType;          ///< Run time bank type
    typedef AkUInt32 WWISEC_AkFileID;            ///< Integer-type file identifier
    typedef AkUInt32 WWISEC_AkDeviceID;          ///< I/O device ID
    typedef AkUInt32 WWISEC_AkTriggerID;         ///< Trigger ID
    typedef AkUInt32 WWISEC_AkArgumentValueID;   ///< Argument value ID
    typedef AkUInt32 WWISEC_AkChannelMask;       ///< Channel mask (similar to WAVE_FORMAT_EXTENSIBLE). Bit values are defined in AkSpeakerConfig.h.
    typedef AkUInt32 WWISEC_AkModulatorID;       ///< Modulator ID
    typedef AkUInt32 WWISEC_AkAcousticTextureID; ///< Acoustic Texture ID
    typedef AkUInt32 WWISEC_AkImageSourceID;     ///< Image Source ID
    typedef AkUInt64 WWISEC_AkOutputDeviceID;    ///< Audio Output device ID
    typedef AkUInt32 WWISEC_AkPipelineID;        ///< Unique node (bus, voice) identifier for profiling.
    typedef AkUInt32 WWISEC_AkRayID;             ///< Unique (per emitter) identifier for an emitter-listener ray.
    typedef AkUInt64 WWISEC_AkAudioObjectID;     ///< Audio Object ID
    typedef AkUInt32 WWISEC_AkJobType;           ///< Job type identifier

    // Constants.
    static const WWISEC_AkPluginID WWISEC_AK_INVALID_PLUGINID = (WWISEC_AkPluginID)-1;                  ///< Invalid FX ID
    static const WWISEC_AkPluginID WWISEC_AK_INVALID_SHARE_SET_ID = (WWISEC_AkPluginID)-1;              ///< Invalid Share Set ID
    static const WWISEC_AkGameObjectID WWISEC_AK_INVALID_GAME_OBJECT = (WWISEC_AkGameObjectID)-1;       ///< Invalid game object (may also mean all game objects)
    static const WWISEC_AkUniqueID WWISEC_AK_INVALID_UNIQUE_ID = 0;                                     ///< Invalid unique 32-bit ID
    static const WWISEC_AkRtpcID WWISEC_AK_INVALID_RTPC_ID = WWISEC_AK_INVALID_UNIQUE_ID;               ///< Invalid RTPC ID
    static const WWISEC_AkPlayingID WWISEC_AK_INVALID_PLAYING_ID = WWISEC_AK_INVALID_UNIQUE_ID;         ///< Invalid playing ID
    static const AkUInt32 WWISEC_AK_DEFAULT_SWITCH_STATE = 0;                                           ///< Switch selected if no switch has been set yet
    static const WWISEC_AkMemPoolId WWISEC_AK_INVALID_POOL_ID = -1;                                     ///< Invalid pool ID
    static const WWISEC_AkMemPoolId WWISEC_AK_DEFAULT_POOL_ID = -1;                                     ///< Default pool ID, same as AK_INVALID_POOL_ID
    static const WWISEC_AkAuxBusID WWISEC_AK_INVALID_AUX_ID = WWISEC_AK_INVALID_UNIQUE_ID;              ///< Invalid auxiliary bus ID (or no Aux bus ID)
    static const WWISEC_AkFileID WWISEC_AK_INVALID_FILE_ID = (WWISEC_AkFileID)-1;                       ///< Invalid file ID
    static const WWISEC_AkDeviceID WWISEC_AK_INVALID_DEVICE_ID = (WWISEC_AkDeviceID)-1;                 ///< Invalid streaming device ID
    static const WWISEC_AkBankID WWISEC_AK_INVALID_BANK_ID = WWISEC_AK_INVALID_UNIQUE_ID;               ///< Invalid bank ID
    static const WWISEC_AkArgumentValueID WWISEC_AK_FALLBACK_ARGUMENTVALUE_ID = 0;                      ///< Fallback argument value ID
    static const WWISEC_AkChannelMask WWISEC_AK_INVALID_CHANNELMASK = 0;                                ///< Invalid channel mask
    static const AkUInt32 WWISEC_AK_INVALID_OUTPUT_DEVICE_ID = WWISEC_AK_INVALID_UNIQUE_ID;             ///< Invalid Device ID
    static const WWISEC_AkPipelineID WWISEC_AK_INVALID_PIPELINE_ID = WWISEC_AK_INVALID_UNIQUE_ID;       ///< Invalid pipeline ID (for profiling)
    static const WWISEC_AkAudioObjectID WWISEC_AK_INVALID_AUDIO_OBJECT_ID = (WWISEC_AkAudioObjectID)-1; ///< Invalid audio object ID

    // Priority.
    static const WWISEC_AkPriority WWISEC_AK_DEFAULT_PRIORITY = 50; ///< Default sound / I/O priority
    static const WWISEC_AkPriority WWISEC_AK_MIN_PRIORITY = 0;      ///< Minimal priority value [0,100]
    static const WWISEC_AkPriority WWISEC_AK_MAX_PRIORITY = 100;    ///< Maximal priority value [0,100]

    // Default bank I/O settings.
    static const WWISEC_AkPriority WWISEC_AK_DEFAULT_BANK_IO_PRIORITY = WWISEC_AK_DEFAULT_PRIORITY; ///<  Default bank load I/O priority
    static const AkReal32 WWISEC_AK_DEFAULT_BANK_THROUGHPUT = 1 * 1024 * 1024 / 1000.f;             ///<  Default bank load throughput (1 Mb/ms)

    // Bank version
    static const AkUInt32 WWISEC_AK_SOUNDBANK_VERSION = 145; ///<  Version of the soundbank reader

    // Job types
    static const WWISEC_AkJobType WWISEC_AkJobType_Generic = 0;         ///< Job type for general-purpose work
    static const WWISEC_AkJobType WWISEC_AkJobType_AudioProcessing = 1; ///< Job type for DSP work
    static const WWISEC_AkJobType WWISEC_AkJobType_SpatialAudio = 2;    ///< Job type for Spatial Audio computations
    static const AkUInt32 WWISEC_AK_NUM_JOB_TYPES = 3;                  ///< Number of possible job types recognized by the Sound Engine

    typedef enum WWISEC_AKRESULT
    {
        WWISEC_AK_NotImplemented = 0,               ///< This feature is not implemented.
        WWISEC_AK_Success = 1,                      ///< The operation was successful.
        WWISEC_AK_Fail = 2,                         ///< The operation failed.
        WWISEC_AK_PartialSuccess = 3,               ///< The operation succeeded partially.
        WWISEC_AK_NotCompatible = 4,                ///< Incompatible formats
        WWISEC_AK_AlreadyConnected = 5,             ///< The stream is already connected to another node.
        WWISEC_AK_InvalidFile = 7,                  ///< The provided file is the wrong format or unexpected values causes the file to be invalid.
        WWISEC_AK_AudioFileHeaderTooLarge = 8,      ///< The file header is too large.
        WWISEC_AK_MaxReached = 9,                   ///< The maximum was reached.
        WWISEC_AK_InvalidID = 14,                   ///< The ID is invalid.
        WWISEC_AK_IDNotFound = 15,                  ///< The ID was not found.
        WWISEC_AK_InvalidInstanceID = 16,           ///< The InstanceID is invalid.
        WWISEC_AK_NoMoreData = 17,                  ///< No more data is available from the source.
        WWISEC_AK_InvalidStateGroup = 20,           ///< The StateGroup is not a valid channel.
        WWISEC_AK_ChildAlreadyHasAParent = 21,      ///< The child already has a parent.
        WWISEC_AK_InvalidLanguage = 22,             ///< The language is invalid (applies to the Low-Level I/O).
        WWISEC_AK_CannotAddItseflAsAChild = 23,     ///< It is not possible to add itself as its own child.
        WWISEC_AK_InvalidParameter = 31,            ///< Something is not within bounds, check the documentation of the function returning this code.
        WWISEC_AK_ElementAlreadyInList = 35,        ///< The item could not be added because it was already in the list.
        WWISEC_AK_PathNotFound = 36,                ///< This path is not known.
        WWISEC_AK_PathNoVertices = 37,              ///< Stuff in vertices before trying to start it
        WWISEC_AK_PathNotRunning = 38,              ///< Only a running path can be paused.
        WWISEC_AK_PathNotPaused = 39,               ///< Only a paused path can be resumed.
        WWISEC_AK_PathNodeAlreadyInList = 40,       ///< This path is already there.
        WWISEC_AK_PathNodeNotInList = 41,           ///< This path is not there.
        WWISEC_AK_DataNeeded = 43,                  ///< The consumer needs more.
        WWISEC_AK_NoDataNeeded = 44,                ///< The consumer does not need more.
        WWISEC_AK_DataReady = 45,                   ///< The provider has available data.
        WWISEC_AK_NoDataReady = 46,                 ///< The provider does not have available data.
        WWISEC_AK_InsufficientMemory = 52,          ///< Memory error.
        WWISEC_AK_Cancelled = 53,                   ///< The requested action was cancelled (not an error).
        WWISEC_AK_UnknownBankID = 54,               ///< Trying to load a bank using an ID which is not defined.
        WWISEC_AK_BankReadError = 56,               ///< Error while reading a bank.
        WWISEC_AK_InvalidSwitchType = 57,           ///< Invalid switch type (used with the switch container)
        WWISEC_AK_FormatNotReady = 63,              ///< Source format not known yet.
        WWISEC_AK_WrongBankVersion = 64,            ///< The bank version is not compatible with the current bank reader.
        WWISEC_AK_FileNotFound = 66,                ///< File not found.
        WWISEC_AK_DeviceNotReady = 67,              ///< Specified ID doesn't match a valid hardware device: either the device doesn't exist or is disabled.
        WWISEC_AK_BankAlreadyLoaded = 69,           ///< The bank load failed because the bank is already loaded.
        WWISEC_AK_RenderedFX = 71,                  ///< The effect on the node is rendered.
        WWISEC_AK_ProcessNeeded = 72,               ///< A routine needs to be executed on some CPU.
        WWISEC_AK_ProcessDone = 73,                 ///< The executed routine has finished its execution.
        WWISEC_AK_MemManagerNotInitialized = 74,    ///< The memory manager should have been initialized at this point.
        WWISEC_AK_StreamMgrNotInitialized = 75,     ///< The stream manager should have been initialized at this point.
        WWISEC_AK_SSEInstructionsNotSupported = 76, ///< The machine does not support SSE instructions (required on PC).
        WWISEC_AK_Busy = 77,                        ///< The system is busy and could not process the request.
        WWISEC_AK_UnsupportedChannelConfig = 78,    ///< Channel configuration is not supported in the current execution context.
        WWISEC_AK_PluginMediaNotAvailable = 79,     ///< Plugin media is not available for effect.
        WWISEC_AK_MustBeVirtualized = 80,           ///< Sound was Not Allowed to play.
        WWISEC_AK_CommandTooLarge = 81,             ///< SDK command is too large to fit in the command queue.
        WWISEC_AK_RejectedByFilter = 82,            ///< A play request was rejected due to the MIDI filter parameters.
        WWISEC_AK_InvalidCustomPlatformName = 83,   ///< Detecting incompatibility between Custom platform of banks and custom platform of connected application
        WWISEC_AK_DLLCannotLoad = 84,               ///< Plugin DLL could not be loaded, either because it is not found or one dependency is missing.
        WWISEC_AK_DLLPathNotFound = 85,             ///< Plugin DLL search path could not be found.
        WWISEC_AK_NoJavaVM = 86,                    ///< No Java VM provided in AkInitSettings.
        WWISEC_AK_OpenSLError = 87,                 ///< OpenSL returned an error.  Check error log for more details.
        WWISEC_AK_PluginNotRegistered = 88,         ///< Plugin is not registered.  Make sure to implement a AK::PluginRegistration class for it and use AK_STATIC_LINK_PLUGIN in the game binary.
        WWISEC_AK_DataAlignmentError = 89,          ///< A pointer to audio data was not aligned to the platform's required alignment (check AkTypes.h in the platform-specific folder)
        WWISEC_AK_DeviceNotCompatible = 90,         ///< Incompatible Audio device.
        WWISEC_AK_DuplicateUniqueID = 91,           ///< Two Wwise objects share the same ID.
        WWISEC_AK_InitBankNotLoaded = 92,           ///< The Init bank was not loaded yet, the sound engine isn't completely ready yet.
        WWISEC_AK_DeviceNotFound = 93,              ///< The specified device ID does not match with any of the output devices that the sound engine is currently using.
        WWISEC_AK_PlayingIDNotFound = 94,           ///< Calling a function with a playing ID that is not known.
        WWISEC_AK_InvalidFloatValue = 95,           ///< One parameter has a invalid float value such as NaN, INF or FLT_MAX.
        WWISEC_AK_FileFormatMismatch = 96,          ///< Media file format unexpected
        WWISEC_AK_NoDistinctListener = 97,          ///< No distinct listener provided for AddOutput
        WWISEC_AK_ACP_Error = 98,                   ///< Generic XMA decoder error.
        WWISEC_AK_ResourceInUse = 99,               ///< Resource is in use and cannot be released.
        WWISEC_AK_InvalidBankType = 100,            ///< Invalid bank type. The bank type was either supplied through a function call (e.g. LoadBank) or obtained from a bank loaded from memory.
        WWISEC_AK_AlreadyInitialized = 101,         ///< Init() was called but that element was already initialized.
        WWISEC_AK_NotInitialized = 102,             ///< The component being used is not initialized. Most likely AK::SoundEngine::Init() was not called yet, or AK::SoundEngine::Term was called too early.
        WWISEC_AK_FilePermissionError = 103,        ///< The file access permissions prevent opening a file.
        WWISEC_AK_UnknownFileError = 104,           ///< Rare file error occured, as opposed to AK_FileNotFound or AK_FilePermissionError. This lumps all unrecognized OS file system errors.
    } WWISEC_AKRESULT;

    typedef enum WWISEC_AkGroupType
    {
        // should stay set as Switch = 0 and State = 1
        WWISEC_AkGroupType_Switch = 0, ///< Type switch
        WWISEC_AkGroupType_State = 1   ///< Type state
    } WWISEC_AkGroupType;

    /// Configured audio settings
    typedef struct WWISEC_AkAudioSettings
    {
        AkUInt32 uNumSamplesPerFrame;  ///< Number of samples per audio frame (256, 512, 1024 or 2048).
        AkUInt32 uNumSamplesPerSecond; ///< Number of samples per second.
    } WWISEC_AkAudioSettings;

    typedef enum WWISEC_AkAudioDeviceState
    {
        WWISEC_AkDeviceState_Unknown = 0,                                                                                                                          ///< The audio device state is unknown or invalid.
        WWISEC_AkDeviceState_Active = 1 << 0,                                                                                                                      ///< The audio device is active That is, the audio adapter that connects to the endpoint device is present and enabled.
        WWISEC_AkDeviceState_Disabled = 1 << 1,                                                                                                                    ///< The audio device is disabled.
        WWISEC_AkDeviceState_NotPresent = 1 << 2,                                                                                                                  ///< The audio device is not present because the audio adapter that connects to the endpoint device has been removed from the system.
        WWISEC_AkDeviceState_Unplugged = 1 << 3,                                                                                                                   ///< The audio device is unplugged.
        WWISEC_AkDeviceState_All = WWISEC_AkDeviceState_Active | WWISEC_AkDeviceState_Disabled | WWISEC_AkDeviceState_NotPresent | WWISEC_AkDeviceState_Unplugged, ///< Includes audio devices in all states.
    } WWISEC_AkAudioDeviceState;

    typedef struct WWISEC_AkDeviceDescription
    {
        AkUInt32 idDevice;                         ///< Device ID for Wwise. This is the same as what is returned from AK::GetDeviceID and AK::GetDeviceIDFromName. Use it to specify the main device in AkPlatformInitSettings.idAudioDevice or in AK::SoundEngine::AddSecondaryOutput.
        AkOSChar deviceName[AK_MAX_PATH];          ///< The user-friendly name for the device.
        WWISEC_AkAudioDeviceState deviceStateMask; ///< Bitmask used to filter the device based on their state.
        bool isDefaultDevice;                      ///< Identify default device. Always false when not supported.
    } WWISEC_AkDeviceDescription;

    typedef enum WWISEC_AkPanningRule
    {
        WWISEC_AkPanningRule_Speakers = 0,  ///< Left and right positioned 60 degrees apart (by default - see AK::SoundEngine::GetSpeakerAngles()).
        WWISEC_AkPanningRule_Headphones = 1 ///< Left and right positioned 180 degrees apart.
    } WWISEC_AkPanningRule;
    // END AkTypes

    // BEGIN AkMemoryMgr
    /// Memory category IDs.
    typedef enum WWISEC_AkMemID
    {
        WWISEC_AkMemID_Object,               ///< Generic placeholder for allocations tied to the Wwise project.
        WWISEC_AkMemID_Event,                ///< Events from the Wwise project.
        WWISEC_AkMemID_Structure,            ///< Structures from the Wwise project.
        WWISEC_AkMemID_Media,                ///< Media from the Wwise project.
        WWISEC_AkMemID_GameObject,           ///< Game Objects and related.
        WWISEC_AkMemID_Processing,           ///< Anything tied to instancing and processing of the DSP graph.
        WWISEC_AkMemID_ProcessingPlugin,     ///< Plug-in allocations related to the DSP graph.
        WWISEC_AkMemID_Streaming,            ///< Streaming Manager objects.
        WWISEC_AkMemID_StreamingIO,          ///< Streaming Manager I/O memory.
        WWISEC_AkMemID_SpatialAudio,         ///< Spatial audio.
        WWISEC_AkMemID_SpatialAudioGeometry, ///< Spatial audio geometry data.
        WWISEC_AkMemID_SpatialAudioPaths,    ///< Spatial audio paths data.
        WWISEC_AkMemID_GameSim,              ///< Game Simulator allocations.
        WWISEC_AkMemID_MonitorQueue,         ///< Monitor Queue.
        WWISEC_AkMemID_Profiler,             ///< Profiler.
        WWISEC_AkMemID_FilePackage,          ///< File packager.
        WWISEC_AkMemID_SoundEngine,          ///< Base sound engine allocations (managers, etc).
        WWISEC_AkMemID_Integration,          ///< Game engine integration allocations.
        WWISEC_AkMemID_JobMgr,               ///< Allocations for Sound Engine jobs and job dependencies.

        WWISEC_AkMemID_NUM,               ///< Category count.
        WWISEC_AkMemID_MASK = 0x1FFFFFFF, ///< Mask for category IDs.

        WWISEC_AkMemType_Media = 0x20000000,  ///< Media memory type bit.
        WWISEC_AkMemType_Device = 0x40000000, ///< Device memory type bit.
        WWISEC_AkMemType_NoTrack = 0x80000000 ///< Do not track this allocation.
    } WWISEC_AkMemID;

    typedef struct WWISEC_AK_MemoryMgr_CategoryStats
    {
        // Current state
        AkUInt64 uUsed; ///< Used memory (in bytes)

        // Statistics
        AkUInt64 uPeakUsed; ///< Peak used memory (in bytes)
        AkUInt32 uAllocs;   ///< Number of allocation calls since initialization
        AkUInt32 uFrees;    ///< Number of free calls since initialization
    } WWISEC_AK_MemoryMgr_CategoryStats;

    typedef struct WWISEC_AK_MemoryMgr_GlobalStats
    {
        AkUInt64 uUsed;       ///< Total memory used including all categories (in bytes)
        AkUInt64 uDeviceUsed; ///< Total device memory used including all categories (in bytes)
        AkUInt64 uReserved;   ///< Total reserved memory. (Used and unused). Will return 0 if the reserved memory is not traceable.
        AkUInt64 uMax;        ///< Maximum total allocation size, specified in the initialization settings through uMemAllocationSizeLimit. Will be 0 if no limit was set.
    } WWISEC_AK_MemoryMgr_GlobalStats;

    bool WWISEC_AK_MemoryMgr_IsInitialized();
    void WWISEC_AK_MemoryMgr_Term();
    void WWISEC_AK_MemoryMgr_InitForThread();
    void WWISEC_AK_MemoryMgr_TermForThread();
    void* WWISEC_AK_MemoryMgr_Malloc(WWISEC_AkMemPoolId in_poolId, size_t in_uSize);
    void* WWISEC_AK_MemoryMgr_ReallocAligned(WWISEC_AkMemPoolId in_poolId, void* in_pAlloc, size_t in_uSize, AkUInt32 in_uAlignment);
    void WWISEC_AK_MemoryMgr_Free(WWISEC_AkMemPoolId in_poolId, void* in_pMemAddress);
    void* WWISEC_AK_MemoryMgr_Malign(WWISEC_AkMemPoolId in_poolId, size_t in_USize, AkUInt32 in_uAlignment);
    void WWISEC_AK_MemoryMgr_GetCategoryStats(WWISEC_AkMemPoolId in_poolId, WWISEC_AK_MemoryMgr_CategoryStats* out_poolStats);
    void WWISEC_AK_MemoryMgr_GetGlobalStats(WWISEC_AK_MemoryMgr_GlobalStats* out_stats);
    void WWISEC_AK_MemoryMgr_StartProfileThreadUsage();
    AkUInt64 WWISEC_AK_MemoryMgr_StopProfileThreadUsage();
    void WWISEC_AK_MemoryMgr_DumpToFile(const AkOSChar* pszFilename);
    // END AkMemoryMgr

    // BEGIN AkModule
    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemInitForThread)();

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemTermForThread)();

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemTrimForThread)();

    typedef void*(AKSOUNDENGINE_CALL* WWISEC_AkMemMalloc)(
        WWISEC_AkMemPoolId poolId,
        size_t uSize);

    typedef void*(AKSOUNDENGINE_CALL* WWISEC_AkMemMalign)(
        WWISEC_AkMemPoolId poolId,
        size_t uSize,
        AkUInt32 uAlignment);

    typedef void*(AKSOUNDENGINE_CALL* WWISEC_AkMemRealloc)(
        WWISEC_AkMemPoolId poolId,
        void* pAddress,
        size_t uSize);

    typedef void*(AKSOUNDENGINE_CALL* WWISEC_AkMemReallocAligned)(
        WWISEC_AkMemPoolId poolId,
        void* pAddress,
        size_t uSize,
        AkUInt32 uAlignment);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemFree)(
        WWISEC_AkMemPoolId poolId,
        void* pAddress);

    typedef size_t(AKSOUNDENGINE_CALL* WWISEC_AkMemTotalReservedMemorySize)();

    typedef size_t(AKSOUNDENGINE_CALL* WWISEC_AkMemSizeOfMemory)(
        WWISEC_AkMemPoolId poolId,
        void* pAddress);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemDebugMalloc)(
        WWISEC_AkMemPoolId poolId,
        size_t uSize,
        void* pAddress,
        char const* pszFile,
        AkUInt32 uLine);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemDebugMalign)(
        WWISEC_AkMemPoolId poolId,
        size_t uSize,
        AkUInt32 uAlignment,
        void* pAddress,
        char const* pszFile,
        AkUInt32 uLine);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemDebugRealloc)(
        WWISEC_AkMemPoolId poolId,
        void* pOldAddress,
        size_t uSize,
        void* pNewAddress,
        char const* pszFile,
        AkUInt32 uLine);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemDebugReallocAligned)(
        WWISEC_AkMemPoolId poolId,
        void* pOldAddress,
        size_t uSize,
        AkUInt32 uAlignment,
        void* pNewAddress,
        char const* pszFile,
        AkUInt32 uLine);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemDebugFree)(
        WWISEC_AkMemPoolId poolId,
        void* pAddress);

    typedef void* (*WWISEC_AkMemAllocVM)(
        size_t size,
        size_t* extra);

    typedef void (*WWISEC_AkMemFreeVM)(
        void* address,
        size_t size,
        size_t extra,
        size_t release);

    typedef struct WWISEC_AkMemSettings
    {
        /// @name High-level memory allocation hooks. When not NULL, redirect allocations normally forwarded to rpmalloc.
        //@{
        WWISEC_AkMemInitForThread pfInitForThread;                     ///< (Optional) Thread-specific allocator initialization hook.
        WWISEC_AkMemTermForThread pfTermForThread;                     ///< (Optional) Thread-specific allocator termination hook.
        WWISEC_AkMemMalloc pfMalloc;                                   ///< (Optional) Memory allocation hook.
        WWISEC_AkMemMalign pfMalign;                                   ///< (Optional) Memory allocation hook.
        WWISEC_AkMemRealloc pfRealloc;                                 ///< (Optional) Memory allocation hook.
        WWISEC_AkMemReallocAligned pfReallocAligned;                   ///< (Optional) Memory allocation hook.
        WWISEC_AkMemFree pfFree;                                       ///< (Optional) Memory allocation hook.
        WWISEC_AkMemTotalReservedMemorySize pfTotalReservedMemorySize; ///< (Optional) Memory allocation statistics hook.
        WWISEC_AkMemSizeOfMemory pfSizeOfMemory;                       ///< (Optional) Memory allocation statistics hook.
        //@}

        /// @name Configuration.
        //@{
        AkUInt64 uMemAllocationSizeLimit; ///< When non-zero, limits the total amount of virtual and device memory allocated by AK::MemoryMgr.
        bool bUseDeviceMemAlways;         ///< Use device memory for all allocations (on applicable platforms).
        //@}

        /// @name Page allocation hooks, used by rpmalloc. Default to AKPLATFORM::AllocVM et al.
        //@{
        WWISEC_AkMemAllocVM pfAllocVM;     ///< Virtual page allocation hook.
        WWISEC_AkMemFreeVM pfFreeVM;       ///< Virtual page allocation hook.
        WWISEC_AkMemAllocVM pfAllocDevice; ///< Device page allocation hook.
        WWISEC_AkMemFreeVM pfFreeDevice;   ///< Device page allocation hook.
        AkUInt32 uVMPageSize;              ///< Virtual memory page size. Defaults to 0 which means auto-detect.
        AkUInt32 uDevicePageSize;          ///< Device memory page size. Defaults to 0 which means auto-detect.
        //@}

        /// @name Memory allocation debugging.
        //@{
        WWISEC_AkMemDebugMalloc pfDebugMalloc;                 ///< (Optional) Memory allocation debugging hook. Used for tracking calls to pfMalloc.
        WWISEC_AkMemDebugMalign pfDebugMalign;                 ///< (Optional) Memory allocation debugging hook. Used for tracking calls to pfMalign.
        WWISEC_AkMemDebugRealloc pfDebugRealloc;               ///< (Optional) Memory allocation debugging hook. Used for tracking calls to pfRealloc.
        WWISEC_AkMemDebugReallocAligned pfDebugReallocAligned; ///< (Optional) Memory allocation debugging hook. Used for tracking calls to pfReallocAligned.
        WWISEC_AkMemDebugFree pfDebugFree;                     ///< (Optional) Memory allocation debugging hook. Used for tracking calls to pfFree.
        AkUInt32 uMemoryDebugLevel;                            ///< Default 0 disabled. 1 debug enabled. 2 stomp allocator enabled. 3 stomp allocator and debug enabled. User implementations may use multiple non-zero values to offer different features.
        //@}

        // Moved to end-of-struct to maintain stability across 2022.1 modules.
        WWISEC_AkMemTrimForThread pfTrimForThread; ///< (Optional) Thread-specific allocator "trimming" hook.
    } WWISEC_AkMemSettings;

    WWISEC_AKRESULT WWISEC_AK_MemoryMgr_Init(WWISEC_AkMemSettings* in_pSettings);
    void WWISEC_AK_MemoryMgr_GetDefaultSettings(WWISEC_AkMemSettings* out_pMemSettings);
    // END AkModule

    // BEGIN AkSpeakerConfig
    typedef AkUInt32 WWISEC_AkChannelConfig;
    // END AkSpeakerConfig

    // BEGIN AkSoundEngine
    typedef WWISEC_AKRESULT (*WWISEC_AkBackgroundMusicChangeCallbackFunc)(
        bool in_bBackgroundMusicMuted, ///< Flag indicating whether the busses tagged as "background music" in the project are muted or not.
        void* in_pCookie               ///< User-provided data, e.g. a user structure.
    );

    typedef struct WWISEC_AkOutputSettings
    {
        WWISEC_AkUniqueID audioDeviceShareset; ///< Unique ID of a custom audio device to be used. Custom audio devices are defined in the Audio Device Shareset section of the Wwise project.
                                               ///< If you want to output normally through the output device defined on the Master Bus in your project, leave this field to its default value (AK_INVALID_UNIQUE_ID, or value 0).
                                               ///< Typical usage: AkInitSettings.eOutputSettings.audioDeviceShareset = AK::SoundEngine::GetIDFromString("InsertYourAudioDeviceSharesetNameHere");
                                               /// \sa <tt>\ref AK::SoundEngine::GetIDFromString()</tt>
                                               /// \sa \ref soundengine_plugins_audiodevices
                                               /// \sa \ref integrating_secondary_outputs
                                               /// \sa \ref default_audio_devices

        AkUInt32 idDevice; ///< Device specific identifier, when multiple devices of the same type are possible.  If only one device is possible, leave to 0.
                           ///< - PS4 Controller-Speakers: UserID as returned from sceUserServiceGetLoginUserIdList
                           ///< - XBoxOne Controller-Headphones: Use the AK::GetDeviceID function to get the ID from an IMMDevice. Find the player's device with the WASAPI API (IMMDeviceEnumerator, see Microsoft documentation) or use AK::GetDeviceIDFromName.
                           ///< - Windows: Use AK::GetDeviceID or AK::GetDeviceIDFromName to get the correct ID.  Leave to 0 for the default Windows device as seen in Audio Properties.
                           ///< - All other outputs: use 0 to select the default for the selected audio device type (shareset)

        WWISEC_AkPanningRule ePanningRule; ///< Rule for 3D panning of signals routed to a stereo bus. In AkPanningRule_Speakers mode, the angle of the front loudspeakers
                                           ///< (uSpeakerAngles[0]) is used. In AkPanningRule_Headphones mode, the speaker angles are superseded by constant power panning
                                           ///< between two virtual microphones spaced 180 degrees apart.

        WWISEC_AkChannelConfig channelConfig; ///< Channel configuration for this output. Call AkChannelConfig::Clear() to let the engine use the default output configuration.
                                              ///< Hardware might not support the selected configuration.
    } WWISEC_AkOutputSettings;

    void WWISEC_AkOutputSettings_Init(WWISEC_AkOutputSettings* outputSettings, const char* in_szDeviceShareSet, WWISEC_AkUniqueID in_idDevice, WWISEC_AkChannelConfig in_channelConfig, WWISEC_AkPanningRule in_ePanning);

    typedef enum WWISEC_AkFloorPlane
    {
        WWISEC_AkFloorPlane_XZ = 0,                          ///< The floor is oriented along the ZX-plane. The front vector points towards +Z, the up vector towards +Y, and the side vector towards +X.
        WWISEC_AkFloorPlane_XY,                              ///< The floor is oriented along the XY-plane. The front vector points towards +X, the up vector towards +Z, and the side vector towards +Y.
        WWISEC_AkFloorPlane_YZ,                              ///< The floor is oriented along the YZ-plane. The front vector points towards +Y, the up vector towards +X, and the side vector towards +Z.
        WWISEC_AkFloorPlane_Default = WWISEC_AkFloorPlane_XZ ///< The Wwise default floor plane is ZX.
    } WWISEC_AkFloorPlane;

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddOutput(WWISEC_AkOutputSettings* in_Settings, WWISEC_AkOutputDeviceID *out_pDeviceID, const WWISEC_AkGameObjectID* in_pListenerIDs, AkUInt32 in_uNumListeners);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RemoveOutput(WWISEC_AkOutputDeviceID in_idOutput);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_ReplaceOutput(WWISEC_AkOutputSettings* in_Settings, WWISEC_AkOutputDeviceID in_outputDeviceId, WWISEC_AkOutputDeviceID *out_pOutputDeviceId);
    // END AkSoundEngine

#ifdef __cplusplus
}
#endif