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
#include <AK/SoundEngine/Common/AkSoundEngineExport.h>

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

    // BEGIN Platform-specific (Ak*SoundEngine and AkPlatformFunc)
    typedef struct WWISEC_WIN_AkThreadProperties
    {
        int nPriority;           ///< Thread priority
        AkUInt32 dwAffinityMask; ///< Affinity mask
        AkUInt32 uStackSize;     ///< Thread stack size.
    } WWISEC_WIN_AkThreadProperties;

    typedef struct WWISEC_WIN_AkPlatformInitSettings
    {
        // Direct sound.
        void* hWnd; ///< Handle of the window associated with the audio.
                    ///< Each game must specify the HWND of the application for device detection purposes.
                    ///< The value returned by GetDefaultPlatformInitSettings is the foreground HWND at
                    ///< the moment of the initialization of the sound engine and might not be the correct one for your game.
                    ///< Each game must provide the correct HWND to use.

        // Threading model.
        WWISEC_WIN_AkThreadProperties threadLEngine;     ///< Lower engine threading properties
        WWISEC_WIN_AkThreadProperties threadOutputMgr;   ///< Ouput thread threading properties
        WWISEC_WIN_AkThreadProperties threadBankManager; ///< Bank manager threading properties (its default priority is AK_THREAD_PRIORITY_NORMAL)
        WWISEC_WIN_AkThreadProperties threadMonitor;     ///< Monitor threading properties (its default priority is AK_THREAD_PRIORITY_ABOVENORMAL). This parameter is not used in Release build.

        // Voices.
        AkUInt16 uNumRefillsInVoice; ///< Number of refill buffers in voice buffer. 2 == double-buffered, defaults to 4.

        AkUInt32 uSampleRate; ///< Sampling Rate. Default is 48000 Hz. Use 24000hz for low quality. Any positive reasonable sample rate is supported. However be careful setting a custom value. Using an odd or really low sample rate may result in malfunctionning sound engine.

        bool bEnableAvxSupport; ///< Enables run-time detection of AVX and AVX2 SIMD support in the engine and plug-ins. Disabling this may improve CPU performance by allowing for higher CPU clockspeeds.

        AkUInt32 uMaxSystemAudioObjects; ///< Dictates how many Microsoft Spatial Sound dynamic objects will be reserved by the System sink. On Windows, other running processes will be prevented from reserving these objects. Set to 0 to disable the use of System Audio Objects. Default is 128.
    } WWISEC_WIN_AkPlatformInitSettings;

    typedef struct WWISEC_POSIX_AkThreadProperties
    {
        int nPriority;           ///< Thread priority
        size_t uStackSize;       ///< Thread stack size
        int uSchedPolicy;        ///< Thread scheduling policy
        AkUInt32 dwAffinityMask; ///< Affinity mask
    } WWISEC_POSIX_AkThreadProperties;

    /// \cond !(Web)
    ///< API used for audio output
    ///< Use with AkPlatformInitSettings to select the API used for audio output.
    ///< Use AkAPI_Default, it will select the more appropriate API depending on the computer's capabilities.  Other values should be used for testing purposes.
    ///< \sa AK::SoundEngine::Init
    typedef enum WWISEC_AkAudioAPILinux
    {
        WWISEC_AkAPI_PulseAudio = 1 << 0,                                   ///< Use PulseAudio (this is the preferred API on Linux)
        WWISEC_AkAPI_ALSA = 1 << 1,                                         ///< Use ALSA
        WWISEC_AkAPI_Default = WWISEC_AkAPI_PulseAudio | WWISEC_AkAPI_ALSA, ///< Default value, will select the more appropriate API
    } WWISEC_AkAudioAPILinux;

    /// Platform specific initialization settings
    /// \sa AK::SoundEngine::Init
    /// \sa AK::SoundEngine::GetDefaultPlatformInitSettings
    typedef struct WWISEC_LINUX_AkPlatformInitSettings
    {
        // Threading model.
        WWISEC_POSIX_AkThreadProperties threadLEngine;     ///< Lower engine threading properties
        WWISEC_POSIX_AkThreadProperties threadOutputMgr;   ///< Ouput thread threading properties
        WWISEC_POSIX_AkThreadProperties threadBankManager; ///< Bank manager threading properties (its default priority is AK_THREAD_PRIORITY_NORMAL)
        WWISEC_POSIX_AkThreadProperties threadMonitor;     ///< Monitor threading properties (its default priority is AK_THREAD_PRIORITY_ABOVENORMAL). This parameter is not used in Release build.

        // Voices.
        AkUInt32 uSampleRate;             ///< Sampling Rate. Default 48000 Hz
        AkUInt16 uNumRefillsInVoice;      ///< Number of refill buffers in voice buffer. 2 == double-buffered, defaults to 4.
        WWISEC_AkAudioAPILinux eAudioAPI; ///< Main audio API to use. Leave to AkAPI_Default for the default sink (default value).
                                          ///< If a valid audioDeviceShareset plug-in is provided, the AkAudioAPI will be Ignored.
                                          ///< \ref AkAudioAPI
        WWISEC_AkDataTypeID sampleType;   ///< Sample type. AK_FLOAT for 32 bit float, AK_INT for 16 bit signed integer, defaults to AK_FLOAT.
                                          ///< Supported by AkAPI_PulseAudio only.
    } WWISEC_LINUX_AkPlatformInitSettings;

    /// \cond !(Web)
    /// Platform specific initialization settings
    /// \sa AK::SoundEngine::Init
    /// \sa AK::SoundEngine::GetDefaultPlatformInitSettings
    typedef struct WWISEC_MACOSX_AkPlatformInitSettings
    {
        // Threading model.
        WWISEC_POSIX_AkThreadProperties threadLEngine;     ///< Lower engine threading properties
        WWISEC_POSIX_AkThreadProperties threadOutputMgr;   ///< Ouput thread threading properties
        WWISEC_POSIX_AkThreadProperties threadBankManager; ///< Bank manager threading properties (its default priority is AK_THREAD_PRIORITY_NORMAL)
        WWISEC_POSIX_AkThreadProperties threadMonitor;     ///< Monitor threading properties (its default priority is AK_THREAD_PRIORITY_ABOVENORMAL). This parameter is not used in Release build.

        AkUInt32 uSampleRate; ///< Sampling Rate. Default 48000 Hz
        // Voices.
        AkUInt16 uNumRefillsInVoice; ///< Number of refill buffers in voice buffer. 2 == double-buffered, defaults to 4.
    } WWISEC_MACOSX_AkPlatformInitSettings;

    /// \cond !(Web)
    ///< API used for audio output
    ///< Use with AkPlatformInitSettings to select the API used for audio output.
    ///< Use AkAudioAPI_Default, it will select the more appropriate API depending on the computer's capabilities.  Other values should be used for testing purposes.
    ///< \sa AK::SoundEngine::Init
    typedef enum WWISEC_AkAudioAPIAndroid
    {
        WWISEC_AkAudioAPI_AAudio = 1 << 0,                                                  ///< Use AAudio (lower latency, available only for Android 8.1 or above)
        WWISEC_AkAudioAPI_OpenSL_ES = 1 << 1,                                               ///< Use OpenSL ES (older API, compatible with all Android devices)
        WWISEC_AkAudioAPI_Default = WWISEC_AkAudioAPI_AAudio | WWISEC_AkAudioAPI_OpenSL_ES, ///< Default value, will select the more appropriate API (AAudio for compatible devices, OpenSL for others)
    } WWISEC_AkAudioAPIAndroid;

    typedef const void* WWISEC_SLObjectItf;
    typedef const void* WWISEC_JavaVM;
    typedef void* WWISEC_jobject;

    /// Platform specific initialization settings
    /// \sa AK::SoundEngine::Init
    /// \sa AK::SoundEngine::GetDefaultPlatformInitSettings
    typedef struct WWISEC_ANDROID_AkPlatformInitSettings
    {
        // Threading model.
        WWISEC_POSIX_AkThreadProperties threadLEngine;     ///< Lower engine threading properties
        WWISEC_POSIX_AkThreadProperties threadOutputMgr;   ///< Ouput thread threading properties
        WWISEC_POSIX_AkThreadProperties threadBankManager; ///< Bank manager threading properties (its default priority is AK_THREAD_PRIORITY_NORMAL)
        WWISEC_POSIX_AkThreadProperties threadMonitor;     ///< Monitor threading properties (its default priority is AK_THREAD_PRIORITY_ABOVENORMAL). This parameter is not used in Release build.

        WWISEC_AkAudioAPIAndroid eAudioAPI; ///< Main audio API to use. Leave to AkAPI_Default for the default sink (default value).
                                            ///< \ref AkAudioAPI

        AkUInt32 uSampleRate;         ///< Sampling Rate.  Set to 0 to get the native sample rate.  Default value is 0.
        AkUInt16 uNumRefillsInVoice;  ///< Number of refill buffers in voice buffer.  Defaults to 4.
        bool bRoundFrameSizeToHWSize; ///< Used when hardware-preferred frame size and user-preferred frame size (AkInitSettings.uNumSamplesPerFrame) are not compatible.
                                      /// If true (default) the sound engine will initialize to a multiple of the HW setting, close to the user setting.
                                      /// If false, the user setting is used as is, regardless of the HW preference (might incur a performance hit).

        WWISEC_SLObjectItf pSLEngine; ///< OpenSL engine reference for sharing between various audio components.
        WWISEC_JavaVM* pJavaVM;       ///< Active JavaVM for the app, used for internal system calls.  Usually provided through the android_app structure given at startup or the NativeActivity. This parameter needs to be set to allow the sound engine initialization.
        WWISEC_jobject jActivity;     ///< android.app.Activity instance for this application. Usually provided through the android_app structure, or through other means if your application has an overridden activity.

        bool bVerboseSink;      ///< Enable this to inspect sink behavior. Useful for debugging non-standard Android devices.
        bool bEnableLowLatency; ///< Used the lowest output latency possible for the current hardware.
                                /// If true (default), the output audio device will be initialized in low-latency operation, allowing for more responsive audio playback on most devices. However, when operating in low-latency mode, some devices may have differences in audio reproduction.
                                /// If false, the output audio device will be initialized without low-latency operation.
    } WWISEC_ANDROID_AkPlatformInitSettings;

    /// The IDs of the iOS audio session categories, useful for defining app-level audio behaviours such as inter-app audio mixing policies and audio routing behaviours. These IDs are funtionally equivalent to the corresponding constants defined by the iOS audio session service backend (AVAudioSession). Refer to Xcode documentation for details on the audio session categories. The original prefix "AV" is replaced with "Ak" for the ID names.
    ///
    /// \sa
    /// - \ref AkPlatformInitSettings
    /// - \ref AkAudioSessionCategoryOptions
    /// - \ref AkAudioSessionProperties
    typedef enum WWISEC_IOS_AkAudioSessionCategory
    {
        WWISEC_IOS_AkAudioSessionCategoryAmbient,       ///< Audio session category corresponding to the AVAudiosession's AVAudioSessionCategoryAmbient constant
        WWISEC_IOS_AkAudioSessionCategorySoloAmbient,   ///< Audio session category corresponding to the AVAudiosession's AVAudioSessionCategorySoloAmbient constant
        WWISEC_IOS_AkAudioSessionCategoryPlayAndRecord, ///< Audio session category corresponding to the AVAudiosession's AVAudioSessionCategoryPlayAndRecord constant
        WWISEC_IOS_AkAudioSessionCategoryPlayback       ///< Audio session category corresponding to the AVAudiosession's AVAudioSessionCategoryPlayback constant
    } WWISEC_IOS_AkAudioSessionCategory;

    /// The IDs of the iOS audio session category options, used for customizing the audio session category features. These IDs are funtionally equivalent to the corresponding constants defined by the iOS audio session service backend (AVAudioSession). Refer to Xcode documentation for details on the audio session category options. The original prefix "AV" is replaced with "Ak" for the ID names.
    /// \remark These options only have an effect with specific audio session categories. See the documentation for each option to learn which category they affect.
    ///
    /// \sa
    /// - \ref AkPlatformInitSettings
    /// - \ref AkAudioSessionCategory
    /// - \ref AkAudioSessionProperties
    typedef enum WWISEC_IOS_AkAudioSessionCategoryOptions
    {
        WWISEC_IOS_AkAudioSessionCategoryOptionMixWithOthers = 1,        ///< Same as AVAudioSessionCategoryOptionMixWithOthers. Only affects PlayAndRecord and Playback categories.
        WWISEC_IOS_AkAudioSessionCategoryOptionDuckOthers = 2,           ///< Same as AVAudioSessionCategoryOptionDuckOthers. Implicitely sets the MixWithOthers option. Only affects PlayAndRecord and Playback categories.
        WWISEC_IOS_AkAudioSessionCategoryOptionAllowBluetooth = 4,       ///< Same as AVAudioSessionCategoryOptionAllowBluetooth. Only affects PlayAndRecord category.
        WWISEC_IOS_AkAudioSessionCategoryOptionDefaultToSpeaker = 8,     ///< Same as AVAudioSessionCategoryOptionDefaultToSpeaker. Only affects PlayAndRecord category.
        WWISEC_IOS_AkAudioSessionCategoryOptionAllowBluetoothA2DP = 0x20 ///< Same as AVAudioSessionCategoryOptionAllowBluetoothA2DP. Only affects PlayAndRecord category.
    } WWISEC_IOS_AkAudioSessionCategoryOptions;

    /// The IDs of the iOS audio session modes, used for customizing the audio session for typical app types. These IDs are funtionally equivalent to the corresponding constants defined by the iOS audio session service backend (AVAudioSession). Refer to Xcode documentation for details on the audio session category options. The original prefix "AV" is replaced with "Ak" for the ID names.
    ///
    /// \sa
    /// - \ref AkPlatformInitSettings
    /// - \ref AkAudioSessionProperties
    typedef enum WWISEC_IOS_AkAudioSessionMode
    {
        WWISEC_IOS_AkAudioSessionModeDefault = 0,    ///< Audio session mode corresponding to the AVAudiosession's AVAudioSessionModeDefault constant
        WWISEC_IOS_AkAudioSessionModeVoiceChat,      ///< Audio session mode corresponding to the AVAudiosession's AVAudioSessionModeVoiceChat constant
        WWISEC_IOS_AkAudioSessionModeGameChat,       ///< Audio session mode corresponding to the AVAudiosession's AVAudioSessionModeGameChat constant
        WWISEC_IOS_AkAudioSessionModeVideoRecording, ///< Audio session mode corresponding to the AVAudiosession's AVAudioSessionModeVideoRecording constant
        WWISEC_IOS_AkAudioSessionModeMeasurement,    ///< Audio session mode corresponding to the AVAudiosession's AVAudioSessionModeMeasurement constant
        WWISEC_IOS_AkAudioSessionModeMoviePlayback,  ///< Audio session mode corresponding to the AVAudiosession's AVAudioSessionModeMoviePlayback constant
        WWISEC_IOS_AkAudioSessionModeVideoChat       ///< Audio session mode corresponding to the AVAudiosession's AVAudioSessionModeMoviePlayback constant
    } WWISEC_IOS_AkAudioSessionMode;

    /// The behavior flags for when iOS audio session is activated. These IDs are functionally equivalent to the corresponding constants defined by the iOS audio session service backend (AVAudioSession). Refer to Xcode documentation for details on the audio session options. The original prefix "AV" is replaced with "Ak" for the ID names.
    ///
    /// \sa
    /// - \ref AkPlatformInitSettings
    /// - \ref AkAudioSessionProperties
    typedef enum WWISEC_IOS_AkAudioSessionSetActiveOptions
    {
        WWISEC_IOS_AkAudioSessionSetActiveOptionNotifyOthersOnDeactivation = 1 ///< Audio session activation option corresponding to the AVAudiosession's AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation constant
    } WWISEC_IOS_AkAudioSessionSetActiveOptions;

    /// Flags that can modify the default Sound Engine behavior related to the management of the audio session. These do not have equivalences in the official iOS SDK; they apply uniquely to Wwise's approach to interruption handling.
    typedef enum WWISEC_IOS_AkAudioSessionBehaviorOptions
    {
        WWISEC_IOS_AkAudioSessionBehaviorSuspendInBackground = 0x1 ///< By default, the Sound Engine continues to render audio in the background when using PlayAndRecord or Playback categories. Setting this flag causes the Sound Engine to suspend audio rendering when in the background, thus disabling background audio. Only affects Playback and PlayAndRecord audio session categories.
    } WWISEC_IOS_AkAudioSessionBehaviorOptions;

    /// The API structure used with AkPlatformInitSettings for specifying iOS audio session for the sound engine.
    ///
    /// \sa
    /// - \ref AkPlatformInitSettings
    /// - \ref AkAudioSessionCategory
    /// - \ref AkAudioSessionCategoryOptions
    /// - \ref AkAudioSessionMode
    /// - \ref AkAudioSessionSetActiveOptions
    typedef struct WWISEC_IOS_AkAudioSessionProperties
    {
        WWISEC_IOS_AkAudioSessionCategory eCategory;                    ///< \sa AkAudioSessionCategory
        WWISEC_IOS_AkAudioSessionCategoryOptions eCategoryOptions;      ///< \sa AkAudioSessionCategoryOptions
        WWISEC_IOS_AkAudioSessionMode eMode;                            ///< \sa AkAudioSessionMode
        WWISEC_IOS_AkAudioSessionSetActiveOptions eSetActivateOptions;  ///< \sa AkAudioSessionSetActiveOptions
        WWISEC_IOS_AkAudioSessionBehaviorOptions eAudioSessionBehavior; ///< Flags to change the default Sound Engine behavior related to the management of the iOS Audio Session with regards to application lifecycle events. \sa AkAudioSessionBehaviorFlags
    } WWISEC_IOS_AkAudioSessionProperties;

    typedef struct WWISEC_AudioBufferList WWISEC_AudioBufferList;

    /// iOS-only callback function prototype used for audio input source plugin. Implement this function to transfer the
    /// input sample data to the sound engine and perform brief custom processing.
    /// \remark See the remarks of \ref AkGlobalCallbackFunc.
    ///
    /// \sa
    /// - \ref AkPlatformInitSettings
    typedef WWISEC_AKRESULT (*WWISEC_IOS_AudioInputCallbackFunc)(
        WWISEC_AudioBufferList* io_Data, ///< An exposed CoreAudio structure that holds the input audio samples generated from
                                         ///< audio input hardware. The buffer is pre-allocated by the sound engine and the buffer
                                         ///< size can be obtained from the structure. Refer to the microphone demo of the IntegrationDemo for an example of usage.
        void* in_pCookie                 ///< User-provided data, e.g., a user structure.
    );

    /// iOS-only callback function prototype used for handling audio session interruptions.
    /// Implementing this is optional, but useful for application-specific responses to interruptions. For example, an application can enable or disable certain UI elements when an interruption begins and ends.
    /// \remark
    /// - There is no need to call AK::SoundEngine::Suspend() and AK::SoundEngine::WakeupFromSuspend() in this callback. The sound engine call them internally depending on the interruption status.
    /// - When in_bEnterInterruption is true, this callback is called \a before the sound engine calls AK::SoundEngine::Suspend(), where the user can take actions to prepare for the suspend, e.g., posting global pause events or switching to a special user interface.
    /// - When in_bEnterInterruption is false, this callback is called \a before the sound engine calls AK::SoundEngine::WakeFromSuspend(). In this callback, the user can restore suspended resources, e.g., post global resume events or switch back to the default user interface.
    /// - To receive a callback \a after the Sound Engine has woken up from suspend after an interruption, use AK::SoundEngine::RegisterGlobalCallback with the AkGlobalCallbackLocation_WakeupFromSuspend location instead.
    ///
    /// \sa
    /// - \ref AkGlobalCallbackFunc
    /// - \ref AkPlatformInitSettings
    /// - \ref AK::SoundEngine::Suspend
    /// - \ref AK::SoundEngine::WakeupFromSuspend
    /// - \ref AK::SoundEngine::RegisterGlobalCallback
    typedef void (*WWISEC_IOS_AudioInterruptionCallbackFunc)(
        bool in_bEnterInterruption, ///< Indicating whether or not an interruption is about to start (e.g., an incoming
                                    ///< call is received) or end (e.g., the incoming call is dismissed).

        void* in_pCookie ///< User-provided data, e.g., a user structure.
    );

    /// The API structure used for specifying all iOS-specific callback functions and user data from the app side.
    ///
    /// \sa
    /// - \ref AkPlatformInitSettings
    typedef struct WWISEC_IOS_AkAudioCallbacks
    {
        WWISEC_IOS_AudioInputCallbackFunc inputCallback;               ///< Application-defined audio input callback function
        void* inputCallbackCookie;                                     ///< Application-defined user data for the audio input callback function
        WWISEC_IOS_AudioInterruptionCallbackFunc interruptionCallback; ///< Application-defined audio interruption callback function
        void* interruptionCallbackCookie;                              ///< Application-defined user data for the audio interruption callback function
    } WWISEC_IOS_AkAudioCallbacks;

    /// \cond !(Web)
    /// Platform specific initialization settings
    /// \sa AK::SoundEngine::Init
    /// \sa AK::SoundEngine::GetDefaultPlatformInitSettings
    /// - \ref AK::SoundEngine::iOS::AkAudioSessionCategory
    typedef struct WWISEC_IOS_AkPlatformInitSettings
    {
        // Threading model.
        WWISEC_POSIX_AkThreadProperties threadLEngine;     ///< Lower engine threading properties
        WWISEC_POSIX_AkThreadProperties threadOutputMgr;   ///< Ouput thread threading properties
        WWISEC_POSIX_AkThreadProperties threadBankManager; ///< Bank manager threading properties (its default priority is AK_THREAD_PRIORITY_NORMAL)
        WWISEC_POSIX_AkThreadProperties threadMonitor;     ///< Monitor threading properties (its default priority is AK_THREAD_PRIORITY_ABOVENORMAL). This parameter is not used in Release build.

        AkUInt32 uSampleRate; ///< Sampling Rate. Default 48000 Hz
        // Voices.
        AkUInt16 uNumRefillsInVoice;                      ///< Number of refill buffers in voice buffer. 2 == double-buffered, defaults to 4
        WWISEC_IOS_AkAudioSessionProperties audioSession; ///< iOS audio session properties
        WWISEC_IOS_AkAudioCallbacks audioCallbacks;       ///< iOS audio callbacks

        bool bVerboseSystemOutput; ///< Print additional debugging information specific to iOS to the system output log.
    } WWISEC_IOS_AkPlatformInitSettings;

#if defined(AK_WIN)
    typedef WWISEC_WIN_AkThreadProperties WWISEC_AkThreadProperties;
    typedef WWISEC_WIN_AkPlatformInitSettings WWISEC_AkPlatformInitSettings;
#elif defined(AK_LINUX_DESKTOP)
typedef WWISEC_POSIX_AkThreadProperties WWISEC_AkThreadProperties;
typedef WWISEC_LINUX_AkPlatformInitSettings WWISEC_AkPlatformInitSettings;
#elif defined(AK_ANDROID)
typedef WWISEC_POSIX_AkThreadProperties WWISEC_AkThreadProperties;
typedef WWISEC_ANDROID_AkPlatformInitSettings WWISEC_AkPlatformInitSettings;
#elif defined(AK_MAC_OS_X)
typedef WWISEC_POSIX_AkThreadProperties WWISEC_AkThreadProeprties;
typedef WWISEC_MACOSX_AkPlatformInitSettings WWISEC_AkPlatformInitSettings;
#elif defined(AK_IOS)
typedef WWISEC_POSIX_AkThreadProperties WWISEC_AkThreadProperties;
typedef WWISEC_IOS_AkPlatformInitSettings WWISEC_AkPlatformInitSettings;
#endif
    // END Platform-specific

    // BEGIN AkSoundEngine
    AK_CALLBACK(void, WWISEC_AkAssertHook)
    (
        const char* in_pszExpression, ///< Expression
        const char* in_pszFileName,   ///< File Name
        int in_lineNumber             ///< Line Number
    );

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

    // Function that the host runtime must call to allow for jobs to execute.
    // in_jobType is the type originally provided by AkJobMgrSettings::FuncRequestJobWorker.
    // in_uExecutionTimeUsec is the number of microseconds that the function should execute for before terminating.
    // Note that the deadline is only checked after each individual job completes execution, so the function may run slightly
    // longer than intended. The "in_uExecutionTimeUsec" should be considered a suggestion or guideline, not a strict rule.
    // A value of 0 means that the function will run until there are no more jobs ready to be immediately executed.
    AK_CALLBACK(void, WWISEC_AkJobWorkerFunc)
    (
        WWISEC_AkJobType in_jobType,
        AkUInt32 in_uExecutionTimeUsec);

    AK_CALLBACK(void, WWISEC_AkJobMgrSettings_FuncRequestJobWorker)
    (
        WWISEC_AkJobWorkerFunc in_fnJobWorker, ///< Function passed to host runtime that should be executed. Note that the function provided will exist for as long as the soundengine code is loaded, and will always be the same.
        WWISEC_AkJobType in_jobType,           ///< The type of job worker that has been requested. This should be passed forward to in_fnJobWorker
        AkUInt32 in_uNumWorkers,               ///< Number of workers requested
        void* in_pClientData                   ///< Data provided by client in AkJobMgrSettings
    );

    /// Settings for the Sound Engine's internal job manager
    typedef struct WWISEC_AkJobMgrSettings
    {
        WWISEC_AkJobMgrSettings_FuncRequestJobWorker fnRequestJobWorker; ///< Function called by the job manager when a new worker needs to be requested. When null, all jobs will be executed on the same thread that calls RenderAudio().

        AkUInt32 uMaxActiveWorkers[WWISEC_AK_NUM_JOB_TYPES]; ///< The maximum number of concurrent workers that will be requested. Must be >= 1 for each jobType.

        AkUInt32 uNumMemorySlabs; ///< Number of memory slabs to pre-allocate for job manager memory. At least one slab per worker thread should be pre-allocated. Default is 1.
        AkUInt32 uMemorySlabSize; ///< Size of each memory slab used for job manager memory. Must be a power of two. Default is 8K.

        void* pClientData; ///< Arbitrary data that will be passed back to the client when calling FuncRequestJobWorker
    } WWISEC_AkJobMgrSettings;

    /// External (optional) callback for tracking performance of the sound engine that is called when a timer starts. (only called in Debug and Profile binaries; this is not called in Release)
    /// in_uPluginID may be non-zero when this function is called, to provide extra data about what context this Timer was started in.
    /// in_pszZoneName will point to a static string, so the pointer can be stored for later use, not just the contents of the string itself.
    AK_CALLBACK(void, WWISEC_AkProfilerPushTimerFunc)
    (
        WWISEC_AkPluginID in_uPluginID,
        const char* in_pszZoneName);

    /// External (optional) function for tracking performance of the sound engine that is called when a timer stops. (only called in Debug and Profile binaries; this is not called in Release)
    AK_CALLBACK(void, WWISEC_AkProfilerPopTimerFunc)
    ();

    ///< External (optional) function for tracking notable events in the sound engine, to act as a marker or bookmark. (only called in Debug and Profile binaries; this is not called in Release)
    /// in_uPluginID may be non-zero when this function is called, to provide extra data about what context this Marker was posted in.
    /// in_pszMarkerName will point to a static string, so the pointer can be stored for later use, not just the contents of the string itself.
    AK_CALLBACK(void, WWISEC_AkProfilerPostMarkerFunc)
    (
        WWISEC_AkPluginID in_uPluginID,
        const char* in_pszMarkerName);

    /// Platform-independent initialization settings of the sound engine
    /// \sa
    /// - <tt>AK::SoundEngine::Init()</tt>
    /// - <tt>AK::SoundEngine::GetDefaultInitSettings()</tt>
    /// - \ref soundengine_integration_init_advanced
    typedef struct WWISEC_AkInitSettings
    {
        WWISEC_AkAssertHook pfnAssertHook; ///< External assertion handling function (optional)

        AkUInt32 uMaxNumPaths;                 ///< Maximum number of paths for positioning
        AkUInt32 uCommandQueueSize;            ///< Size of the command queue, in bytes
        bool bEnableGameSyncPreparation;       ///< Sets to true to enable AK::SoundEngine::PrepareGameSync usage.
        AkUInt32 uContinuousPlaybackLookAhead; ///< Number of quanta ahead when continuous containers should instantiate a new voice before which next sounds should start playing. This look-ahead time allows I/O to occur, and is especially useful to reduce the latency of continuous containers with trigger rate or sample-accurate transitions.
                                               ///< Default is 1 audio quantum, also known as an audio frame. Its size is equal to AkInitSettings::uNumSamplesPerFrame / AkPlatformInitSettings::uSampleRate. For many platforms the default values - which can be overridden - are respectively 1,024 samples and 48 kHz. This gives a default 21.3 ms for an audio quantum, which is adequate if you have a RAM-based streaming device that completes transfers within 20 ms. With 1 look-ahead quantum, voices spawned by continuous containers are more likely to be ready when they are required to play, thereby improving the overall precision of sound scheduling. If your device completes transfers in 30 ms instead, you might consider increasing this value to 2 because it will grant new voices 2 audio quanta (~43 ms) to fetch data.

        AkUInt32 uNumSamplesPerFrame; ///< Number of samples per audio frame (256, 512, 1024, or 2048).

        AkUInt32 uMonitorQueuePoolSize;   ///< Size of the monitoring queue, in bytes. This parameter is not used in Release build.
        AkUInt32 uCpuMonitorQueueMaxSize; ///< Maximum size of the CPU monitoring queue, per thread, in bytes. This parameter is not used in Release build.

        WWISEC_AkOutputSettings settingsMainOutput; ///< Main output device settings.
        WWISEC_AkJobMgrSettings settingsJobManager; ///< Settings to configure the behavior of the Sound Engine's internal job manager

        AkUInt32 uMaxHardwareTimeoutMs; ///< Amount of time to wait for HW devices to trigger an audio interrupt. If there is no interrupt after that time, the sound engine will revert to  silent mode and continue operating until the HW finally comes back. Default value: 2000 (2 seconds)

        bool bUseSoundBankMgrThread; ///< Use a separate thread for loading sound banks. Allows asynchronous operations.
        bool bUseLEngineThread;      ///< Use a separate thread for processing audio. If set to false, audio processing will occur in RenderAudio(). \ref goingfurther_eventmgrthread

        WWISEC_AkBackgroundMusicChangeCallbackFunc BGMCallback; ///< Application-defined audio source change event callback function.
        void* BGMCallbackCookie;                                ///< Application-defined user data for the audio source change event callback function.
        AkOSChar* szPluginDLLPath;                              ///< When using DLLs for plugins, specify their path. Leave NULL if DLLs are in the same folder as the game executable.

        WWISEC_AkFloorPlane eFloorPlane; ///< Define the orientation of the the floor plane with respect to the X,Y,Z axes, and which axes represent the side, front and up vectors as a basis for rotations in Wwise.
                                         ///< AkFloorPlane is used in to orient the Game Object 3D Viewer in Wwise, and in the transformation of geometry instances in Wwise Spatial Audio.

        AkReal32 fGameUnitsToMeters; ///< The number of game units in a meter.
                                     ///< This setting is used to adapt the size of elements in the Authoring's Game Object 3D Viewer and Audio Object 3D Viewer to meters.
                                     ///< This setting is also used to simulate real-world positioning of System Audio Objects, to improve the HRTF in some cases.

        AkUInt32 uBankReadBufferSize; ///< The number of bytes read by the BankReader when new data needs to be loaded from disk during serialization. Increasing this trades memory usage for larger, but fewer, file-read events during bank loading.

        AkReal32 fDebugOutOfRangeLimit; ///< Debug setting: Only used when bDebugOutOfRangeCheckEnabled is true.  This defines the maximum values samples can have.  Normal audio must be contained within +1/-1.  This limit should be set higher to allow temporary or short excursions out of range.  Default is 16.

        bool bDebugOutOfRangeCheckEnabled; ///< Debug setting: Enable checks for out-of-range (and NAN) floats in the processing code.  This incurs a small performance hit, but can be enabled in most scenarios.  Will print error messages in the log if invalid values are found at various point in the pipeline. Contact AK Support with the new error messages for more information.

        WWISEC_AkProfilerPushTimerFunc fnProfilerPushTimer;   ///< External (optional) function for tracking performance of the sound engine that is called when a timer starts. (only called in Debug and Profile binaries; this is not called in Release)
        WWISEC_AkProfilerPopTimerFunc fnProfilerPopTimer;     ///< External (optional) function for tracking performance of the sound engine that is called when a timer stops. (only called in Debug and Profile binaries; this is not called in Release)
        WWISEC_AkProfilerPostMarkerFunc fnProfilerPostMarker; ///< External (optional) function for tracking significant events in the sound engine, to act as a marker or bookmark. (only called in Debug and Profile binaries; this is not called in Release)
    } WWISEC_AkInitSettings;

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddOutput(WWISEC_AkOutputSettings* in_Settings, WWISEC_AkOutputDeviceID* out_pDeviceID, const WWISEC_AkGameObjectID* in_pListenerIDs, AkUInt32 in_uNumListeners);

    void WWISEC_AK_SoundEngine_GetDefaultInitSettings(WWISEC_AkInitSettings* out_settings);

    void WWISEC_AK_SoundEngine_GetDefaultPlatformInitSettings(WWISEC_AkPlatformInitSettings* out_platformSettings);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Init(WWISEC_AkInitSettings* in_pSettings, WWISEC_AkPlatformInitSettings* in_pPlatformSettings);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RemoveOutput(WWISEC_AkOutputDeviceID in_idOutput);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_ReplaceOutput(WWISEC_AkOutputSettings* in_Settings, WWISEC_AkOutputDeviceID in_outputDeviceId, WWISEC_AkOutputDeviceID* out_pOutputDeviceId);

    void WWISEC_AK_SoundEngine_Term();

    // END AkSoundEngine

#ifdef __cplusplus
}
#endif