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

#ifndef WWISEC_AK_COMM_DEFAULT_DISCOVERY_PORT
#define WWISEC_AK_COMM_DEFAULT_DISCOVERY_PORT 24024 ///< Default discovery port for most platforms using IP sockets for communication.
#endif

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

    typedef struct WWISEC_AkExternalSourceInfo
    {
        AkUInt32 iExternalSrcCookie; ///< Cookie identifying the source, given by hashing the name of the source given in the project.  See \ref AK::SoundEngine::GetIDFromString. \aknote If an event triggers the playback of more than one external source, they must be named uniquely in the project therefore have a unique cookie) in order to tell them apart when filling the AkExternalSourceInfo structures. \endaknote
        WWISEC_AkCodecID idCodec;    ///< Codec ID for the file.  One of the audio formats defined in AkTypes.h (AKCODECID_XXX)
        AkOSChar* szFile;            ///< File path for the source.  If not NULL, the source will be streaming from disk. Set pInMemory to NULL. If idFile is set, this field is used as stream name (for profiling purposes). /// The only file format accepted is a fully formed WEM file, as converted by Wwise.
        void* pInMemory;             ///< Pointer to the in-memory file.  If not NULL, the source will be read from memory. Set szFile and idFile to NULL. The only file format accepted is a fully formed WEM file, as converted by Wwise.
        AkUInt32 uiMemorySize;       ///< Size of the data pointed by pInMemory
        WWISEC_AkFileID idFile;      ///< File ID.  If not zero, the source will be streaming from disk.  This ID can be anything.  Note that you must override the low-level IO to resolve this ID to a real file.  See \ref streamingmanager_lowlevel for more information on overriding the Low Level IO.
    } WWISEC_AkExternalSourceInfo;

    typedef enum WWISEC_AK_SoundEngine_MultiPositionType
    {
        WWISEC_AK_SoundEngine_MultiPositionType_SingleSource,   ///< Used for normal sounds, not expected to pass to AK::SoundEngine::SetMultiplePosition() (if done, only the first position will be used).
        WWISEC_AK_SoundEngine_MultiPositionType_MultiSources,   ///< Simulate multiple sources in one sound playing, adding volumes. For instance, all the torches on your level emitting using only one sound.
        WWISEC_AK_SoundEngine_MultiPositionType_MultiDirections ///< Simulate one sound coming from multiple directions. Useful for repositionning sounds based on wall openings or to simulate areas like forest or rivers ( in combination with spreading in the attenuation of the sounds ).
    } WWISEC_AK_SoundEngine_MultiPositionType;

    typedef enum WWISEC_AkSetPositionFlags
    {
        WWISEC_AkSetPositionFlags_Emitter = 1 << 0,  // Only set the emitter component position.
        WWISEC_AkSetPositionFlags_Listener = 1 << 1, // Only set the listener component position.

        WWISEC_AkSetPositionFlags_Default = (WWISEC_AkSetPositionFlags_Emitter | WWISEC_AkSetPositionFlags_Listener) // Default: set both emitter and listener component positions.
    } WWISEC_AkSetPositionFlags;

    enum
    {
        WWISEC_AkSpeakerPanningType_AK_DirectSpeakerAssignment = 0, ///< No panning: route to matching channels between input and output.
        WWISEC_AkSpeakerPanningType_AK_BalanceFadeHeight = 1,       ///< Balance-Fade-Height: Traditional "box" or "car"-like panner.
        WWISEC_AkSpeakerPanningType_AK_SteeringPanner = 2           ///< Steering panner.
    };
    typedef AkUInt8 WWISEC_AkSpeakerPanningType;

    /// 3D position type: defines what acts as the emitter position for computing spatialization against the listener. Used when Ak3DSpatializationMode is AK_SpatializationMode_PositionOnly or AK_SpatializationMode_PositionAndOrientation.
    enum
    {
        WWISEC_Ak3DPositionType_AK_3DPositionType_Emitter = 0,               ///< 3D spatialization is computed directly from the emitter game object position.
        WWISEC_Ak3DPositionType_AK_3DPositionType_EmitterWithAutomation = 1, ///< 3D spatialization is computed from the emitter game object position, translated by user-defined automation.
        WWISEC_Ak3DPositionType_AK_3DPositionType_ListenerWithAutomation = 2 ///< 3D spatialization is computed from the listener game object position, translated by user-defined automation.
    };
    typedef AkUInt8 WWISEC_Ak3DPositionType;

    typedef enum WWISEC_AkPanningRule
    {
        WWISEC_AkPanningRule_Speakers = 0,  ///< Left and right positioned 60 degrees apart (by default - see AK::SoundEngine::GetSpeakerAngles()).
        WWISEC_AkPanningRule_Headphones = 1 ///< Left and right positioned 180 degrees apart.
    } WWISEC_AkPanningRule;

    /// 3D spatialization mode.
    enum
    {
        WWISEC_Ak3DSpatializationMode_AK_SpatializationMode_None = 0,                  ///< No spatialization
        WWISEC_Ak3DSpatializationMode_AK_SpatializationMode_PositionOnly = 1,          ///< Spatialization based on emitter position only.
        WWISEC_Ak3DSpatializationMode_AK_SpatializationMode_PositionAndOrientation = 2 ///< Spatialization based on both emitter position and emitter orientation.
    };
    typedef AkUInt8 WWISEC_Ak3DSpatializationMode;

    typedef AkUInt8 WWISEC_AkMeteringFlags;

    typedef enum WWISEC_AkPluginType
    {
        WWISEC_AkPluginTypeNone = 0,   ///< Unknown/invalid plug-in type.
        WWISEC_AkPluginTypeCodec = 1,  ///< Compressor/decompressor plug-in (allows support for custom audio file types).
        WWISEC_AkPluginTypeSource = 2, ///< Source plug-in: creates sound by synthesis method (no input, just output).
        WWISEC_AkPluginTypeEffect = 3, ///< Effect plug-in: applies processing to audio data.
        // WWISEC_AkPluginTypeMotionDevice = 4,	///< Motion Device plug-in: feeds movement data to devices. Deprecated by Motion refactor.
        // WWISEC_AkPluginTypeMotionSource = 5,	///< Motion Device source plug-in: feeds movement data to device busses. Deprecated by Motion refactor.
        WWISEC_AkPluginTypeMixer = 6,           ///< Mixer plug-in: mix voices at the bus level.
        WWISEC_AkPluginTypeSink = 7,            ///< Sink plug-in: implement custom sound engine end point.
        WWISEC_AkPluginTypeGlobalExtension = 8, ///< Global Extension plug-in: (e.g. Spatial Audio, Interactive Music)
        WWISEC_AkPluginTypeMetadata = 9,        ///< Metadata plug-in: applies object-based processing to audio data
        WWISEC_AkPluginTypeMask = 0xf           ///< Plug-in type mask is 4 bits.
    } WWISEC_AkPluginType;

    typedef enum WWISEC_AkCurveInterpolation
    {
        WWISEC_AkCurveInterpolation_Log3 = 0,          ///< Log3
        WWISEC_AkCurveInterpolation_Sine = 1,          ///< Sine
        WWISEC_AkCurveInterpolation_Log1 = 2,          ///< Log1
        WWISEC_AkCurveInterpolation_InvSCurve = 3,     ///< Inversed S Curve
        WWISEC_AkCurveInterpolation_Linear = 4,        ///< Linear (Default)
        WWISEC_AkCurveInterpolation_SCurve = 5,        ///< S Curve
        WWISEC_AkCurveInterpolation_Exp1 = 6,          ///< Exp1
        WWISEC_AkCurveInterpolation_SineRecip = 7,     ///< Reciprocal of sine curve
        WWISEC_AkCurveInterpolation_Exp3 = 8,          ///< Exp3
        WWISEC_AkCurveInterpolation_LastFadeCurve = 8, ///< Update this value to reflect last curve available for fades
        WWISEC_AkCurveInterpolation_Constant = 9       ///< Constant ( not valid for fading values )
    } WWISEC_AkCurveInterpolation;

    typedef struct WWISEC_AkAuxSendValue
    {
        WWISEC_AkGameObjectID listenerID; ///< Game object ID of the listener associated with this send. Use AK_INVALID_GAME_OBJECT as a wildcard to set the auxiliary send to all connected listeners (see AK::SoundEngine::SetListeners).
        WWISEC_AkAuxBusID auxBusID;       ///< Auxiliary bus ID.
        AkReal32 fControlValue;           ///< A value in the range [0.0f:16.0f] ( -∞ dB to +24 dB).
                                          ///< Represents the attenuation or amplification factor applied to the volume of the sound going through the auxiliary bus.
                                          ///< A value greater than 1.0f will amplify the sound.
    } WWISEC_AkAuxSendValue;

    typedef enum WWISEC_AkConnectionType
    {
        WWISEC_ConnectionType_Direct = 0x0,          ///< Direct (main, dry) connection.
        WWISEC_ConnectionType_GameDefSend = 0x1,     ///< Connection by a game-defined send.
        WWISEC_ConnectionType_UserDefSend = 0x2,     ///< Connection by a user-defined send.
        WWISEC_ConnectionType_ReflectionsSend = 0x3, ///< Connection by a early reflections send.
    } WWISEC_AkConnectionType;

    typedef struct WWISEC_AkVector64
    {
        AkReal64 X; ///< X Position
        AkReal64 Y; ///< Y Position
        AkReal64 Z; ///< Z Position
    } WWISEC_AkVector64;

    typedef struct WWISEC_AkVector
    {
        AkReal32 X; ///< X Position
        AkReal32 Y; ///< Y Position
        AkReal32 Z; ///< Z Position
    } WWISEC_AkVector;

    typedef struct WWISEC_AkWorldTransform
    {
        WWISEC_AkVector orientationFront; ///< Orientation of the listener
        WWISEC_AkVector orientationTop;   ///< Top orientation of the listener
        WWISEC_AkVector64 position;       ///< Position of the listener
    } WWISEC_AkWorldTransform;

    typedef struct WWISEC_AkTransform
    {
        WWISEC_AkVector orientationFront; ///< Orientation of the listener
        WWISEC_AkVector orientationTop;   ///< Top orientation of the listener
        WWISEC_AkVector position;         ///< Position of the listener
    } WWISEC_AkTransform;

    typedef WWISEC_AkWorldTransform WWISEC_AkSoundPosition;
    typedef WWISEC_AkWorldTransform WWISEC_AkListenerPosition;

    typedef struct WWISEC_AkObstructionOcclusionValues
    {
        AkReal32 occlusion;   ///< OcclusionLevel: [0.0f..1.0f]
        AkReal32 obstruction; ///< ObstructionLevel: [0.0f..1.0f]
    } WWISEC_AkObstructionOcclusionValues;

    typedef struct WWISEC_AkChannelEmitter
    {
        WWISEC_AkWorldTransform position;    ///< Emitter position.
        WWISEC_AkChannelMask uInputChannels; ///< Channels to which the above position applies.
        char padding[4];                     ///< In order to preserve consistent struct size across archs, we need some padding
    } WWISEC_AkChannelEmitter;

    typedef struct WWISEC_AkEmitterListenerPair
    {
        WWISEC_AkWorldTransform emitter;          ///< Emitter position.
        AkReal32 fDistance;                       ///< Distance between emitter and listener.
        AkReal32 fEmitterAngle;                   ///< Angle between position vector and emitter orientation.
        AkReal32 fListenerAngle;                  ///< Angle between position vector and listener orientation.
        AkReal32 fDryMixGain;                     ///< Emitter-listener-pair-specific gain (due to distance and cone attenuation) for direct connections.
        AkReal32 fGameDefAuxMixGain;              ///< Emitter-listener-pair-specific gain (due to distance and cone attenuation) for game-defined send connections.
        AkReal32 fUserDefAuxMixGain;              ///< Emitter-listener-pair-specific gain (due to distance and cone attenuation) for user-defined send connections.
        AkReal32 fOcclusion;                      ///< Emitter-listener-pair-specific occlusion factor
        AkReal32 fObstruction;                    ///< Emitter-listener-pair-specific obstruction factor
        AkReal32 fDiffraction;                    ///< Emitter-listener-pair-specific diffraction coefficient
        AkReal32 fTransmissionLoss;               ///< Emitter-listener-pair-specific transmission occlusion.
        AkReal32 fSpread;                         ///< Emitter-listener-pair-specific spread
        AkReal32 fAperture;                       ///< Emitter-listener-pair-specific aperture
        AkReal32 fScalingFactor;                  ///< Combined scaling factor due to both emitter and listener.
        WWISEC_AkChannelMask uEmitterChannelMask; ///< Channels of the emitter that apply to this ray.
        WWISEC_AkRayID id;                        ///< ID of this emitter-listener pair, unique for a given emitter.
        WWISEC_AkGameObjectID m_uListenerID;      ///< Listener game object ID.
    } WWISEC_AkEmitterListenerPair;

    // ---------------------------------------------------------------
// Languages
// ---------------------------------------------------------------
#define WWISEC_AK_MAX_LANGUAGE_NAME_SIZE (32)

// ---------------------------------------------------------------
// File Type ID Definitions
// ---------------------------------------------------------------

// These correspond to IDs specified in the conversion plug-ins' XML
// files. Audio sources persist them to "remember" their format.
// DO NOT CHANGE THEM without talking to someone in charge of persistence!

// Company ID for plugin development.
#define WWISEC_AKCOMPANYID_PLUGINDEV_MIN (64)
#define WWISEC_AKCOMPANYID_PLUGINDEV_MAX (255)

// Vendor ID.
#define WWISEC_AKCOMPANYID_AUDIOKINETIC (0)          ///< Audiokinetic inc.
#define WWISEC_AKCOMPANYID_AUDIOKINETIC_EXTERNAL (1) ///< Audiokinetic inc.
#define WWISEC_AKCOMPANYID_MCDSP (256)               ///< McDSP
#define WWISEC_AKCOMPANYID_WAVEARTS (257)            ///< WaveArts
#define WWISEC_AKCOMPANYID_PHONETICARTS (258)        ///< Phonetic Arts
#define WWISEC_AKCOMPANYID_IZOTOPE (259)             ///< iZotope
#define WWISEC_AKCOMPANYID_CRANKCASEAUDIO (261)      ///< Crankcase Audio
#define WWISEC_AKCOMPANYID_IOSONO (262)              ///< IOSONO
#define WWISEC_AKCOMPANYID_AUROTECHNOLOGIES (263)    ///< Auro Technologies
#define WWISEC_AKCOMPANYID_DOLBY (264)               ///< Dolby
#define WWISEC_AKCOMPANYID_TWOBIGEARS (265)          ///< Two Big Ears
#define WWISEC_AKCOMPANYID_OCULUS (266)              ///< Oculus
#define WWISEC_AKCOMPANYID_BLUERIPPLESOUND (267)     ///< Blue Ripple Sound
#define WWISEC_AKCOMPANYID_ENZIEN (268)              ///< Enzien Audio
#define WWISEC_AKCOMPANYID_KROTOS (269)              ///< Krotos (Dehumanizer)
#define WWISEC_AKCOMPANYID_NURULIZE (270)            ///< Nurulize
#define WWISEC_AKCOMPANYID_SUPERPOWERED (271)        ///< Super Powered
#define WWISEC_AKCOMPANYID_GOOGLE (272)              ///< Google
#define WWISEC_AKCOMPANYID_VISISONICS (277)          ///< Visisonics

// File/encoding types of Audiokinetic.
#define WWISEC_AKCODECID_BANK (0)             ///< Bank encoding
#define WWISEC_AKCODECID_PCM (1)              ///< PCM encoding
#define WWISEC_AKCODECID_ADPCM (2)            ///< ADPCM encoding
#define WWISEC_AKCODECID_XMA (3)              ///< XMA encoding
#define WWISEC_AKCODECID_VORBIS (4)           ///< Vorbis encoding
#define WWISEC_AKCODECID_WIIADPCM (5)         ///< ADPCM encoding on the Wii
#define WWISEC_AKCODECID_PCMEX (7)            ///< Standard PCM WAV file parser for Wwise Authoring
#define WWISEC_AKCODECID_EXTERNAL_SOURCE (8)  ///< External Source (unknown encoding)
#define WWISEC_AKCODECID_XWMA (9)             ///< xWMA encoding
#define WWISEC_AKCODECID_FILE_PACKAGE (11)    ///< File package files generated by the File Packager utility.
#define WWISEC_AKCODECID_ATRAC9 (12)          ///< ATRAC-9 encoding
#define WWISEC_AKCODECID_VAG (13)             ///< VAG/HE-VAG encoding
#define WWISEC_AKCODECID_PROFILERCAPTURE (14) ///< Profiler capture file (.prof) as written through AK::SoundEngine::StartProfilerCapture
#define WWISEC_AKCODECID_ANALYSISFILE (15)    ///< Analysis file
#define WWISEC_AKCODECID_MIDI (16)            ///< MIDI file
#define WWISEC_AKCODECID_OPUSNX (17)          ///< OpusNX encoding
#define WWISEC_AKCODECID_CAF (18)             ///< CAF file
#define WWISEC_AKCODECID_AKOPUS (19)          ///< Opus encoding, 2018.1 to 2019.2
#define WWISEC_AKCODECID_AKOPUS_WEM (20)      ///< Opus encoding, wrapped in WEM
#define WWISEC_AKCODECID_MEMORYMGR_DUMP (21)  ///< Memory stats file as written through AK::MemoryMgr::DumpToFile();
#define WWISEC_AKCODECID_SONY360 (22)         ///< Sony 360 encoding

#define WWISEC_AKCODECID_BANK_EVENT (30) ///< Bank encoding for event banks. These banks are contained in the /event sub-folder.
#define WWISEC_AKCODECID_BANK_BUS (31)   ///< Bank encoding for bus banks. These banks are contained in the /bus sub-folder.

#define WWISEC_AKPLUGINID_METER (129)    ///< Meter Plugin
#define WWISEC_AKPLUGINID_RECORDER (132) ///< Recorder Plugin
#define WWISEC_AKPLUGINID_IMPACTER (184)
#define WWISEC_AKPLUGINID_SYSTEM_OUTPUT_META (900)            ///< System output metadata
#define WWISEC_AKPLUGINID_AUDIO_OBJECT_ATTENUATION_META (901) ///< Attenuation curve metadata
#define WWISEC_AKPLUGINID_AUDIO_OBJECT_PRIORITY_META (902)    ///< Audio object priority metadata

#define WWISEC_AKEXTENSIONID_SPATIALAUDIO (800)     ///< Spatial Audio
#define WWISEC_AKEXTENSIONID_INTERACTIVEMUSIC (801) ///< Interactive Music
#define WWISEC_AKEXTENSIONID_MIDIDEVICEMGR (802)    ///< MIDI Device Manager (Authoring)

// The following are internally defined
#define WWISEC_AK_WAVE_FORMAT_VAG 0xFFFB
#define WWISEC_AK_WAVE_FORMAT_AT9 0xFFFC
#define WWISEC_AK_WAVE_FORMAT_VORBIS 0xFFFF
#define WWISEC_AK_WAVE_FORMAT_OPUSNX 0x3039
#define WWISEC_AK_WAVE_FORMAT_OPUS 0x3040
#define WWISEC_AK_WAVE_FORMAT_OPUS_WEM 0x3041
#define WWISEC_WAVE_FORMAT_XMA2 0x166

    typedef struct WWISEC_IAkSoftwareCodec WWISEC_IAkSoftwareCodec;
    typedef struct WWISEC_IAkFileCodec WWISEC_IAkFileCodec;
    typedef struct WWISEC_IAkGrainCodec WWISEC_IAkGrainCodec;
    /// Registered file source creation function prototype.
    AK_CALLBACK(WWISEC_IAkSoftwareCodec*, WWISEC_AkCreateFileSourceCallback)
    (void* in_pCtx);
    /// Registered bank source node creation function prototype.
    AK_CALLBACK(WWISEC_IAkSoftwareCodec*, WWISEC_AkCreateBankSourceCallback)
    (void* in_pCtx);
    /// Registered FileCodec creation function prototype.
    AK_CALLBACK(WWISEC_IAkFileCodec*, WWISEC_AkCreateFileCodecCallback)
    ();
    /// Registered IAkGrainCodec creation function prototype.
    AK_CALLBACK(WWISEC_IAkGrainCodec*, WWISEC_AkCreateGrainCodecCallback)
    ();

    typedef struct WWISEC_AkCodecDescriptor
    {
        WWISEC_AkCreateFileSourceCallback pFileSrcCreateFunc;    // File VPL source.
        WWISEC_AkCreateBankSourceCallback pBankSrcCreateFunc;    // Bank VPL source.
        WWISEC_AkCreateFileCodecCallback pFileCodecCreateFunc;   // FileCodec utility.
        WWISEC_AkCreateGrainCodecCallback pGrainCodecCreateFunc; // GrainCodec utility.
    } WWISEC_AkCodecDescriptor;

    typedef enum WWISEC_AkBankTypeEnum
    {
        WWISEC_AkBankType_User = WWISEC_AKCODECID_BANK,        ///< User-defined bank.
        WWISEC_AkBankType_Event = WWISEC_AKCODECID_BANK_EVENT, ///< Bank generated for one event.
        WWISEC_AkBankType_Bus = WWISEC_AKCODECID_BANK_BUS,     ///< Bank generated for one bus or aux bus.
    } WWISEC_AkBankTypeEnum;
    // END AkTypes

    // BEGIN AkSpeakerConfig
    typedef AkUInt32 WWISEC_AkChannelConfig;
    // END AkSpeakerConfig

    // BEGIN AkMidiTypes
    //-----------------------------------------------------------------------------
    // Types.
    //-----------------------------------------------------------------------------

    typedef AkUInt8 WWISEC_AkMidiChannelNo; ///< MIDI channel number, usually 0-15.
    typedef AkUInt8 WWISEC_AkMidiNoteNo;    ///< MIDI note number.

    //-----------------------------------------------------------------------------
    // Constants.
    //-----------------------------------------------------------------------------

    // Invalid values
    static const WWISEC_AkMidiChannelNo WWISEC_AK_INVALID_MIDI_CHANNEL = (WWISEC_AkMidiChannelNo)-1; ///< Not a valid midi channel
    static const WWISEC_AkMidiNoteNo WWISEC_AK_INVALID_MIDI_NOTE = (AkUInt8)-1;                      ///< Not a valid midi note

// List of event types
#define WWISEC_AK_MIDI_EVENT_TYPE_INVALID 0x00
#define WWISEC_AK_MIDI_EVENT_TYPE_NOTE_OFF 0x80
#define WWISEC_AK_MIDI_EVENT_TYPE_NOTE_ON 0x90
#define WWISEC_AK_MIDI_EVENT_TYPE_NOTE_AFTERTOUCH 0xa0
#define WWISEC_AK_MIDI_EVENT_TYPE_CONTROLLER 0xb0
#define WWISEC_AK_MIDI_EVENT_TYPE_PROGRAM_CHANGE 0xc0
#define WWISEC_AK_MIDI_EVENT_TYPE_CHANNEL_AFTERTOUCH 0xd0
#define WWISEC_AK_MIDI_EVENT_TYPE_PITCH_BEND 0xe0
#define WWISEC_AK_MIDI_EVENT_TYPE_SYSEX 0xf0
#define WWISEC_AK_MIDI_EVENT_TYPE_ESCAPE 0xf7
#define WWISEC_AK_MIDI_EVENT_TYPE_WWISE_CMD 0xfe
#define WWISEC_AK_MIDI_EVENT_TYPE_META 0xff

// List of Continuous Controller (cc) values
#define WWISEC_AK_MIDI_CC_BANK_SELECT_COARSE 0
#define WWISEC_AK_MIDI_CC_MOD_WHEEL_COARSE 1
#define WWISEC_AK_MIDI_CC_BREATH_CTRL_COARSE 2
#define WWISEC_AK_MIDI_CC_CTRL_3_COARSE 3
#define WWISEC_AK_MIDI_CC_FOOT_PEDAL_COARSE 4
#define WWISEC_AK_MIDI_CC_PORTAMENTO_COARSE 5
#define WWISEC_AK_MIDI_CC_DATA_ENTRY_COARSE 6
#define WWISEC_AK_MIDI_CC_VOLUME_COARSE 7
#define WWISEC_AK_MIDI_CC_BALANCE_COARSE 8
#define WWISEC_AK_MIDI_CC_CTRL_9_COARSE 9
#define WWISEC_AK_MIDI_CC_PAN_POSITION_COARSE 10
#define WWISEC_AK_MIDI_CC_EXPRESSION_COARSE 11
#define WWISEC_AK_MIDI_CC_EFFECT_CTRL_1_COARSE 12
#define WWISEC_AK_MIDI_CC_EFFECT_CTRL_2_COARSE 13
#define WWISEC_AK_MIDI_CC_CTRL_14_COARSE 14
#define WWISEC_AK_MIDI_CC_CTRL_15_COARSE 15
#define WWISEC_AK_MIDI_CC_GEN_SLIDER_1 16
#define WWISEC_AK_MIDI_CC_GEN_SLIDER_2 17
#define WWISEC_AK_MIDI_CC_GEN_SLIDER_3 18
#define WWISEC_AK_MIDI_CC_GEN_SLIDER_4 19
#define WWISEC_AK_MIDI_CC_CTRL_20_COARSE 20
#define WWISEC_AK_MIDI_CC_CTRL_21_COARSE 21
#define WWISEC_AK_MIDI_CC_CTRL_22_COARSE 22
#define WWISEC_AK_MIDI_CC_CTRL_23_COARSE 23
#define WWISEC_AK_MIDI_CC_CTRL_24_COARSE 24
#define WWISEC_AK_MIDI_CC_CTRL_25_COARSE 25
#define WWISEC_AK_MIDI_CC_CTRL_26_COARSE 26
#define WWISEC_AK_MIDI_CC_CTRL_27_COARSE 27
#define WWISEC_AK_MIDI_CC_CTRL_28_COARSE 28
#define WWISEC_AK_MIDI_CC_CTRL_29_COARSE 29
#define WWISEC_AK_MIDI_CC_CTRL_30_COARSE 30
#define WWISEC_AK_MIDI_CC_CTRL_31_COARSE 31
#define WWISEC_AK_MIDI_CC_BANK_SELECT_FINE 32
#define WWISEC_AK_MIDI_CC_MOD_WHEEL_FINE 33
#define WWISEC_AK_MIDI_CC_BREATH_CTRL_FINE 34
#define WWISEC_AK_MIDI_CC_CTRL_3_FINE 35
#define WWISEC_AK_MIDI_CC_FOOT_PEDAL_FINE 36
#define WWISEC_AK_MIDI_CC_PORTAMENTO_FINE 37
#define WWISEC_AK_MIDI_CC_DATA_ENTRY_FINE 38
#define WWISEC_AK_MIDI_CC_VOLUME_FINE 39
#define WWISEC_AK_MIDI_CC_BALANCE_FINE 40
#define WWISEC_AK_MIDI_CC_CTRL_9_FINE 41
#define WWISEC_AK_MIDI_CC_PAN_POSITION_FINE 42
#define WWISEC_AK_MIDI_CC_EXPRESSION_FINE 43
#define WWISEC_AK_MIDI_CC_EFFECT_CTRL_1_FINE 44
#define WWISEC_AK_MIDI_CC_EFFECT_CTRL_2_FINE 45
#define WWISEC_AK_MIDI_CC_CTRL_14_FINE 46
#define WWISEC_AK_MIDI_CC_CTRL_15_FINE 47

#define WWISEC_AK_MIDI_CC_CTRL_20_FINE 52
#define WWISEC_AK_MIDI_CC_CTRL_21_FINE 53
#define WWISEC_AK_MIDI_CC_CTRL_22_FINE 54
#define WWISEC_AK_MIDI_CC_CTRL_23_FINE 55
#define WWISEC_AK_MIDI_CC_CTRL_24_FINE 56
#define WWISEC_AK_MIDI_CC_CTRL_25_FINE 57
#define WWISEC_AK_MIDI_CC_CTRL_26_FINE 58
#define WWISEC_AK_MIDI_CC_CTRL_27_FINE 59
#define WWISEC_AK_MIDI_CC_CTRL_28_FINE 60
#define WWISEC_AK_MIDI_CC_CTRL_29_FINE 61
#define WWISEC_AK_MIDI_CC_CTRL_30_FINE 62
#define WWISEC_AK_MIDI_CC_CTRL_31_FINE 63

#define WWISEC_AK_MIDI_CC_HOLD_PEDAL 64
#define WWISEC_AK_MIDI_CC_PORTAMENTO_ON_OFF 65
#define WWISEC_AK_MIDI_CC_SUSTENUTO_PEDAL 66
#define WWISEC_AK_MIDI_CC_SOFT_PEDAL 67
#define WWISEC_AK_MIDI_CC_LEGATO_PEDAL 68
#define WWISEC_AK_MIDI_CC_HOLD_PEDAL_2 69

#define WWISEC_AK_MIDI_CC_SOUND_VARIATION 70
#define WWISEC_AK_MIDI_CC_SOUND_TIMBRE 71
#define WWISEC_AK_MIDI_CC_SOUND_RELEASE_TIME 72
#define WWISEC_AK_MIDI_CC_SOUND_ATTACK_TIME 73
#define WWISEC_AK_MIDI_CC_SOUND_BRIGHTNESS 74
#define WWISEC_AK_MIDI_CC_SOUND_CTRL_6 75
#define WWISEC_AK_MIDI_CC_SOUND_CTRL_7 76
#define WWISEC_AK_MIDI_CC_SOUND_CTRL_8 77
#define WWISEC_AK_MIDI_CC_SOUND_CTRL_9 78
#define WWISEC_AK_MIDI_CC_SOUND_CTRL_10 79

#define WWISEC_AK_MIDI_CC_GENERAL_BUTTON_1 80
#define WWISEC_AK_MIDI_CC_GENERAL_BUTTON_2 81
#define WWISEC_AK_MIDI_CC_GENERAL_BUTTON_3 82
#define WWISEC_AK_MIDI_CC_GENERAL_BUTTON_4 83

#define WWISEC_AK_MIDI_CC_REVERB_LEVEL 91
#define WWISEC_AK_MIDI_CC_TREMOLO_LEVEL 92
#define WWISEC_AK_MIDI_CC_CHORUS_LEVEL 93
#define WWISEC_AK_MIDI_CC_CELESTE_LEVEL 94
#define WWISEC_AK_MIDI_CC_PHASER_LEVEL 95
#define WWISEC_AK_MIDI_CC_DATA_BUTTON_P1 96
#define WWISEC_AK_MIDI_CC_DATA_BUTTON_M1 97

#define WWISEC_AK_MIDI_CC_NON_REGISTER_COARSE 98
#define WWISEC_AK_MIDI_CC_NON_REGISTER_FINE 99

#define WWISEC_AK_MIDI_CC_ALL_SOUND_OFF 120
#define WWISEC_AK_MIDI_CC_ALL_CONTROLLERS_OFF 121
#define WWISEC_AK_MIDI_CC_LOCAL_KEYBOARD 122
#define WWISEC_AK_MIDI_CC_ALL_NOTES_OFF 123
#define WWISEC_AK_MIDI_CC_OMNI_MODE_OFF 124
#define WWISEC_AK_MIDI_CC_OMNI_MODE_ON 125
#define WWISEC_AK_MIDI_CC_OMNI_MONOPHONIC_ON 126
#define WWISEC_AK_MIDI_CC_OMNI_POLYPHONIC_ON 127

    typedef struct WWISEC_AkMIDIEvent_tGen
    {
        AkUInt8 byParam1;
        AkUInt8 byParam2;
    } WWISEC_AkMIDIEvent_tGen;

    typedef struct WWISEC_AkMIDIEvent_tNoteOnOff
    {
        WWISEC_AkMidiNoteNo byNote;
        AkUInt8 byVelocity;
    } WWISEC_AkMIDIEvent_tNoteOnOff;

    typedef struct WWISEC_AkMIDIEvent_tCc
    {
        AkUInt8 byCc;
        AkUInt8 byValue;
    } WWISEC_AkMIDIEvent_tCc;

    typedef struct WWISEC_AkMIDIEvent_tPitchBend
    {
        AkUInt8 byValueLsb;
        AkUInt8 byValueMsb;
    } WWISEC_AkMIDIEvent_tPitchBend;

    typedef struct WWISEC_AkMIDIEvent_tNoteAftertouch
    {
        AkUInt8 byNote;
        AkUInt8 byValue;
    } WWISEC_AkMIDIEvent_tNoteAftertouch;

    typedef struct WWISEC_AkMIDIEvent_tChanAftertouch
    {
        AkUInt8 byValue;
    } WWISEC_AkMIDIEvent_tChanAftertouch;

    typedef struct WWISEC_AkMIDIEvent_tProgramChange
    {
        AkUInt8 byProgramNum;
    } WWISEC_AkMIDIEvent_tProgramChange;

    typedef struct WWISEC_AkMIDIEvent_tWwiseCmd
    {
        AkUInt16 uCmd; ///< See AK_MIDI_WWISE_CMD_* pre-processor definitions
        AkUInt32 uArg; ///< Optional argument for some commands
    } WWISEC_AkMIDIEvent_tWwiseCmd;

    typedef struct WWISEC_AkMIDIEvent
    {
        AkUInt8 byType; ///< See AK_MIDI_EVENT_TYPE_* pre-processor definitions
        WWISEC_AkMidiChannelNo byChan;

        union {
            WWISEC_AkMIDIEvent_tGen Gen;
            WWISEC_AkMIDIEvent_tCc Cc;
            WWISEC_AkMIDIEvent_tNoteOnOff NoteOnOff;
            WWISEC_AkMIDIEvent_tPitchBend PitchBend;
            WWISEC_AkMIDIEvent_tNoteAftertouch NoteAftertouch;
            WWISEC_AkMIDIEvent_tChanAftertouch ChanAftertouch;
            WWISEC_AkMIDIEvent_tProgramChange ProgramChange;
            WWISEC_AkMIDIEvent_tWwiseCmd WwiseCmd;
        };
    } WWISEC_AkMIDIEvent;

#pragma pack(push, 4)
    // NOTE: mlarouche: We are copying and inlining AkMIDIEvent and related inside AkMIDIPost to have proper alignment
    typedef struct WWISEC_AkMIDIPost_tGen
    {
        AkUInt8 byParam1;
        AkUInt8 byParam2;
    } WWISEC_AkMIDIPost_tGen;

    typedef struct WWISEC_AkMIDIPost_tNoteOnOff
    {
        WWISEC_AkMidiNoteNo byNote;
        AkUInt8 byVelocity;
    } WWISEC_AkMIDIPost_tNoteOnOff;

    typedef struct WWISEC_AkMIDIPost_tCc
    {
        AkUInt8 byCc;
        AkUInt8 byValue;
    } WWISEC_AkMIDIPost_tCc;

    typedef struct WWISEC_AkMIDIPost_tPitchBend
    {
        AkUInt8 byValueLsb;
        AkUInt8 byValueMsb;
    } WWISEC_AkMIDIPost_tPitchBend;

    typedef struct WWISEC_AkMIDIPost_tNoteAftertouch
    {
        AkUInt8 byNote;
        AkUInt8 byValue;
    } WWISEC_AkMIDIPost_tNoteAftertouch;

    typedef struct WWISEC_AkMIDIPost_tChanAftertouch
    {
        AkUInt8 byValue;
    } WWISEC_AkMIDIPost_tChanAftertouch;

    typedef struct WWISEC_AkMIDIPost_tProgramChange
    {
        AkUInt8 byProgramNum;
    } WWISEC_AkMIDIPost_tProgramChange;

    typedef struct WWISEC_AkMIDIPost_tWwiseCmd
    {
        AkUInt16 uCmd; ///< See AK_MIDI_WWISE_CMD_* pre-processor definitions
        AkUInt32 uArg; ///< Optional argument for some commands
    } WWISEC_AkMIDIPost_tWwiseCmd;

    typedef struct WWISEC_AkMIDIPost
    {
        AkUInt8 byType; ///< See AK_MIDI_EVENT_TYPE_* pre-processor definitions
        WWISEC_AkMidiChannelNo byChan;
        union {
            WWISEC_AkMIDIPost_tGen Gen;
            WWISEC_AkMIDIPost_tCc Cc;
            WWISEC_AkMIDIPost_tNoteOnOff NoteOnOff;
            WWISEC_AkMIDIPost_tPitchBend PitchBend;
            WWISEC_AkMIDIPost_tNoteAftertouch NoteAftertouch;
            WWISEC_AkMIDIPost_tChanAftertouch ChanAftertouch;
            WWISEC_AkMIDIPost_tProgramChange ProgramChange;
            WWISEC_AkMIDIPost_tWwiseCmd WwiseCmd;
        };

        AkUInt64 uOffset; ///< Frame offset (in samples) for MIDI event post
    } WWISEC_AkMIDIPost;

#pragma pack(pop)
    // END AkMidiTypes

    // BEGIN AkSpeakerVolumes
    typedef AkReal32* WWISEC_AK_SpeakerVolumes_VectorPtr;            ///< Volume vector. Access each element with the standard bracket [] operator.
    typedef AkReal32* WWISEC_AK_SpeakerVolumes_MatrixPtr;            ///< Volume matrix. Access each input channel vector with AK::SpeakerVolumes::Matrix::GetChannel().
    typedef const AkReal32* WWISEC_AK_SpeakerVolumes_ConstVectorPtr; ///< Constant volume vector. Access each element with the standard bracket [] operator.
    typedef const AkReal32* WWISEC_AK_SpeakerVolumes_ConstMatrixPtr; ///< Constant volume matrix. Access each input channel vector with AK::SpeakerVolumes::Matrix::GetChannel().
    // END AkSpeakerVolumes

// BEGIN AkErrorMessageTranslator
#define WWISEC_AK_TRANSLATOR_MAX_NAME_SIZE 150
#define WWISEC_AK_MAX_ERROR_LENGTH 1000

    typedef struct WWISEC_AkErrorMessageTranslator_TagInformation
    {
        const AkOSChar* m_pTag;
        const AkOSChar* m_pStartBlock;
        const char* m_args;
        AkOSChar m_parsedInfo[WWISEC_AK_TRANSLATOR_MAX_NAME_SIZE];
        AkUInt32 m_argSize;
        AkUInt16 m_len;
        bool m_infoIsParsed;
    } WWISEC_AkErrorMessageTranslator_TagInformation;

    typedef struct WWISEC_AkErrorMessageTranslator WWISEC_AkErrorMessageTranslator;
    typedef struct WWISEC_AkErrorMessageTranslator_FunctionTable
    {
        void (*Destructor)(void* instance);

        void (*Term)(void* instance);

        bool (*Translate)(void* instance, const AkOSChar* in_pszError, AkOSChar* out_translatedPszError, AkInt32 in_maxPszErrorSize, char* in_args, AkUInt32 in_uArgSize);

        bool (*GetInfo)(void* instance, WWISEC_AkErrorMessageTranslator_TagInformation* in_pTagList, AkUInt32 in_uCount, AkUInt32* out_uTranslated);
    } WWISEC_AkErrorMessageTranslator_FunctionTable;

    WWISEC_AkErrorMessageTranslator* WWISEC_AkErrorMessageTranslator_CreateInstance(void* instance, const WWISEC_AkErrorMessageTranslator_FunctionTable* functionTable);
    void WWISEC_AkErrorMessageTranslator_DestroyInstance(WWISEC_AkErrorMessageTranslator* instance);

    void WWISEC_AkErrorMessageTranslator_Term(WWISEC_AkErrorMessageTranslator* instance);
    void WWISEC_AkErrorMessageTranslator_SetFallBackTranslator(WWISEC_AkErrorMessageTranslator* instance, WWISEC_AkErrorMessageTranslator* in_fallBackTranslator);
    bool WWISEC_AkErrorMessageTranslator_Translate(WWISEC_AkErrorMessageTranslator* instance, const AkOSChar* in_pszError, AkOSChar* out_translatedPszError, AkInt32 in_maxPszErrorSize, char* in_args, AkUInt32 in_uArgSize);
    // END AkErrorMessageTranslator

    // BEGIN AkMonitorError
    typedef struct WWISEC_AK_Monitor_MsgContext
    {
        WWISEC_AkPlayingID in_playingID;    ///< Related Playing ID if applicable
        WWISEC_AkGameObjectID in_gameObjID; ///< Related Game Object ID if applicable, AK_INVALID_GAME_OBJECT otherwise
        WWISEC_AkUniqueID in_soundID;       ///< Related Audio Node ID if applicable, AK_INVALID_UNIQUE_ID otherwise
        bool in_bIsBus;                     ///< true if in_audioNodeID is a bus
    } WWISEC_AK_Monitor_MsgContext;

    typedef enum WWISEC_AK_Monitor_ErrorLevel
    {
        WWISEC_AK_Monitor_ErrorLevel_Message = (1 << 0), // used as bitfield
        WWISEC_AK_Monitor_ErrorLevel_Error = (1 << 1),

        WWISEC_AK_Monitor_ErrorLevel_All = WWISEC_AK_Monitor_ErrorLevel_Message | WWISEC_AK_Monitor_ErrorLevel_Error
    } WWISEC_AK_Monitor_ErrorLevel;

    /// ErrorCode
    typedef enum WWISEC_AK_Monitor_ErrorCode
    {
        WWISEC_AK_Monitor_ErrorCode_NoError = 0, // 0-based index into AK::Monitor::s_aszMonitorErrorInfos table
        WWISEC_AK_Monitor_ErrorCode_FileNotFound,
        WWISEC_AK_Monitor_ErrorCode_CannotOpenFile,
        WWISEC_AK_Monitor_ErrorCode_CannotStartStreamNoMemory,
        WWISEC_AK_Monitor_ErrorCode_IODevice,
        WWISEC_AK_Monitor_ErrorCode_IncompatibleIOSettings,

        WWISEC_AK_Monitor_ErrorCode_PluginUnsupportedChannelConfiguration,
        WWISEC_AK_Monitor_ErrorCode_PluginMediaUnavailable,
        WWISEC_AK_Monitor_ErrorCode_PluginInitialisationFailed,
        WWISEC_AK_Monitor_ErrorCode_PluginProcessingFailed,
        WWISEC_AK_Monitor_ErrorCode_PluginExecutionInvalid,
        WWISEC_AK_Monitor_ErrorCode_PluginAllocationFailed,

        WWISEC_AK_Monitor_ErrorCode_VorbisSeekTableRecommended,

        WWISEC_AK_Monitor_ErrorCode_VorbisDecodeError,

        WWISEC_AK_Monitor_ErrorCode_ATRAC9DecodeFailed,
        WWISEC_AK_Monitor_ErrorCode_ATRAC9LoopSectionTooSmall,

        WWISEC_AK_Monitor_ErrorCode_InvalidAudioFileHeader,
        WWISEC_AK_Monitor_ErrorCode_AudioFileHeaderTooLarge,
        WWISEC_AK_Monitor_ErrorCode_LoopTooSmall,

        WWISEC_AK_Monitor_ErrorCode_TransitionNotAccurateChannel,
        WWISEC_AK_Monitor_ErrorCode_TransitionNotAccuratePluginMismatch,
        WWISEC_AK_Monitor_ErrorCode_TransitionNotAccurateRejectedByPlugin,
        WWISEC_AK_Monitor_ErrorCode_TransitionNotAccurateStarvation,
        WWISEC_AK_Monitor_ErrorCode_TransitionNotAccurateCodecError,
        WWISEC_AK_Monitor_ErrorCode_NothingToPlay,
        WWISEC_AK_Monitor_ErrorCode_PlayFailed,

        WWISEC_AK_Monitor_ErrorCode_StingerCouldNotBeScheduled,
        WWISEC_AK_Monitor_ErrorCode_TooLongSegmentLookAhead,
        WWISEC_AK_Monitor_ErrorCode_CannotScheduleMusicSwitch,
        WWISEC_AK_Monitor_ErrorCode_TooManySimultaneousMusicSegments,
        WWISEC_AK_Monitor_ErrorCode_PlaylistStoppedForEditing,
        WWISEC_AK_Monitor_ErrorCode_MusicClipsRescheduledAfterTrackEdit,

        WWISEC_AK_Monitor_ErrorCode_CannotPlaySource_Create,
        WWISEC_AK_Monitor_ErrorCode_CannotPlaySource_VirtualOff,
        WWISEC_AK_Monitor_ErrorCode_CannotPlaySource_TimeSkip,
        WWISEC_AK_Monitor_ErrorCode_CannotPlaySource_InconsistentState,
        WWISEC_AK_Monitor_ErrorCode_MediaNotLoaded,
        WWISEC_AK_Monitor_ErrorCode_VoiceStarving,
        WWISEC_AK_Monitor_ErrorCode_StreamingSourceStarving,
        WWISEC_AK_Monitor_ErrorCode_XMADecoderSourceStarving,
        WWISEC_AK_Monitor_ErrorCode_XMADecodingError,
        WWISEC_AK_Monitor_ErrorCode_InvalidXMAData,

        WWISEC_AK_Monitor_ErrorCode_PluginNotRegistered,
        WWISEC_AK_Monitor_ErrorCode_CodecNotRegistered,
        WWISEC_AK_Monitor_ErrorCode_PluginVersionMismatch,

        WWISEC_AK_Monitor_ErrorCode_EventIDNotFound,

        WWISEC_AK_Monitor_ErrorCode_InvalidGroupID,
        WWISEC_AK_Monitor_ErrorCode_SelectedNodeNotAvailable,
        WWISEC_AK_Monitor_ErrorCode_SelectedMediaNotAvailable,
        WWISEC_AK_Monitor_ErrorCode_NoValidSwitch,

        WWISEC_AK_Monitor_ErrorCode_BankLoadFailed,
        WWISEC_AK_Monitor_ErrorCode_ErrorWhileLoadingBank,
        WWISEC_AK_Monitor_ErrorCode_InsufficientSpaceToLoadBank,

        WWISEC_AK_Monitor_ErrorCode_LowerEngineCommandListFull,

        WWISEC_AK_Monitor_ErrorCode_SeekNoMarker,
        WWISEC_AK_Monitor_ErrorCode_CannotSeekContinuous,
        WWISEC_AK_Monitor_ErrorCode_SeekAfterEof,

        WWISEC_AK_Monitor_ErrorCode_UnknownGameObject,
        WWISEC_AK_Monitor_ErrorCode_GameObjectNeverRegistered, // To be used by the Capture Log to replace ErrorCode_UnknownGameObject
        WWISEC_AK_Monitor_ErrorCode_DeadGameObject,            // To be used by the Capture Log to replace ErrorCode_UnknownGameObject
        WWISEC_AK_Monitor_ErrorCode_GameObjectIsNotEmitter,

        WWISEC_AK_Monitor_ErrorCode_ExternalSourceNotResolved,
        WWISEC_AK_Monitor_ErrorCode_FileFormatMismatch,

        WWISEC_AK_Monitor_ErrorCode_CommandQueueFull,
        WWISEC_AK_Monitor_ErrorCode_CommandTooLarge,

        WWISEC_AK_Monitor_ErrorCode_XMACreateDecoderLimitReached,
        WWISEC_AK_Monitor_ErrorCode_XMAStreamBufferTooSmall,

        WWISEC_AK_Monitor_ErrorCode_ModulatorScopeError_Inst,
        WWISEC_AK_Monitor_ErrorCode_ModulatorScopeError_Obj,

        WWISEC_AK_Monitor_ErrorCode_SeekAfterEndOfPlaylist,

        WWISEC_AK_Monitor_ErrorCode_OpusRequireSeekTable,
        WWISEC_AK_Monitor_ErrorCode_OpusDecodeError,

        WWISEC_AK_Monitor_ErrorCode_SourcePluginNotFound,

        WWISEC_AK_Monitor_ErrorCode_VirtualVoiceLimit,

        WWISEC_AK_Monitor_ErrorCode_NotEnoughMemoryToStart,
        WWISEC_AK_Monitor_ErrorCode_UnknownOpusError, // Deprecated Opus error.

        WWISEC_AK_Monitor_ErrorCode_AudioDeviceInitFailure,
        WWISEC_AK_Monitor_ErrorCode_AudioDeviceRemoveFailure,
        WWISEC_AK_Monitor_ErrorCode_AudioDeviceNotFound,
        WWISEC_AK_Monitor_ErrorCode_AudioDeviceNotValid,

        WWISEC_AK_Monitor_ErrorCode_SpatialAudio_ListenerAutomationNotSupported,
        WWISEC_AK_Monitor_ErrorCode_MediaDuplicationLength,

        WWISEC_AK_Monitor_ErrorCode_HwVoicesSystemInitFailed,  // When the hardware-accelerated subsystem fails to initialize
        WWISEC_AK_Monitor_ErrorCode_HwVoicesDecodeBatchFailed, // When a grouping of hardware-accelerated voices fail to decode collectively
        WWISEC_AK_Monitor_ErrorCode_HwVoiceLimitReached,       // Cannot create any more hardware-accelerated voices
        WWISEC_AK_Monitor_ErrorCode_HwVoiceInitFailed,         // A hardware-accelerated voice fails to be created, but not because the max number of voices was reached

        WWISEC_AK_Monitor_ErrorCode_OpusHWCommandFailed,

        WWISEC_AK_Monitor_ErrorCode_AddOutputListenerIdWithZeroListeners,

        WWISEC_AK_Monitor_ErrorCode_3DObjectLimitExceeded,

        WWISEC_AK_Monitor_ErrorCode_OpusHWFatalError,
        WWISEC_AK_Monitor_ErrorCode_OpusHWDecodeUnavailable,
        WWISEC_AK_Monitor_ErrorCode_OpusHWTimeout,

        WWISEC_AK_Monitor_ErrorCode_SystemAudioObjectsUnavailable,

        WWISEC_AK_Monitor_ErrorCode_AddOutputNoDistinctListener,

        WWISEC_AK_Monitor_ErrorCode_PluginCannotRunOnObjectConfig,
        WWISEC_AK_Monitor_ErrorCode_SpatialAudio_ReflectionBusError,

        WWISEC_AK_Monitor_ErrorCode_VorbisHWDecodeUnavailable,
        WWISEC_AK_Monitor_ErrorCode_ExternalSourceNoMemorySize,

        WWISEC_AK_Monitor_ErrorCode_MonitorQueueFull,
        WWISEC_AK_Monitor_ErrorCode_MonitorMsgTooLarge,

        WWISEC_AK_Monitor_ErrorCode_NonCompliantDeviceMemory,

        WWISEC_AK_Monitor_ErrorCode_JobWorkerFuncCallMismatch,
        WWISEC_AK_Monitor_ErrorCode_JobMgrOutOfMemory,

        WWISEC_AK_Monitor_ErrorCode_InvalidFileSize,
        WWISEC_AK_Monitor_ErrorCode_PluginMsg,

        WWISEC_AK_Monitor_ErrorCode_SinkOpenSL,
        WWISEC_AK_Monitor_ErrorCode_AudioOutOfRange,
        WWISEC_AK_Monitor_ErrorCode_AudioOutOfRangeOnBus,
        WWISEC_AK_Monitor_ErrorCode_AudioOutOfRangeOnBusFx,
        WWISEC_AK_Monitor_ErrorCode_AudioOutOfRangeRay,
        WWISEC_AK_Monitor_ErrorCode_UnknownDialogueEvent,
        WWISEC_AK_Monitor_ErrorCode_FailedPostingEvent,
        WWISEC_AK_Monitor_ErrorCode_OutputDeviceInitializationFailed,
        WWISEC_AK_Monitor_ErrorCode_UnloadBankFailed,

        WWISEC_AK_Monitor_ErrorCode_PluginFileNotFound,
        WWISEC_AK_Monitor_ErrorCode_PluginFileIncompatible,
        WWISEC_AK_Monitor_ErrorCode_PluginFileNotEnoughMemoryToStart,
        WWISEC_AK_Monitor_ErrorCode_PluginFileInvalid,
        WWISEC_AK_Monitor_ErrorCode_PluginFileRegisterFailed,

        WWISEC_AK_Monitor_ErrorCode_UnknownArgument,

        WWISEC_AK_Monitor_ErrorCode_DynamicSequenceAlreadyClosed,
        WWISEC_AK_Monitor_ErrorCode_PendingActionDestroyed,
        WWISEC_AK_Monitor_ErrorCode_CrossFadeTransitionIgnored,
        WWISEC_AK_Monitor_ErrorCode_MusicRendererSeekingFailed,

        // MONITOR_ERRORMSG
        WWISEC_AK_Monitor_ErrorCode_DynamicSequenceIdNotFound,
        WWISEC_AK_Monitor_ErrorCode_BusNotFoundByName,
        WWISEC_AK_Monitor_ErrorCode_AudioDeviceShareSetNotFound,
        WWISEC_AK_Monitor_ErrorCode_AudioDeviceShareSetNotFoundByName,

        WWISEC_AK_Monitor_ErrorCode_SoundEngineTooManyGameObjects,
        WWISEC_AK_Monitor_ErrorCode_SoundEngineTooManyPositions,
        WWISEC_AK_Monitor_ErrorCode_SoundEngineCantCallOnChildBus,
        WWISEC_AK_Monitor_ErrorCode_SoundEnginePlayingIdNotFound,
        WWISEC_AK_Monitor_ErrorCode_SoundEngineInvalidTransform,
        WWISEC_AK_Monitor_ErrorCode_SoundEngineTooManyEventPosts,

        WWISEC_AK_Monitor_ErrorCode_AudioSubsystemStoppedResponding,

        WWISEC_AK_Monitor_ErrorCode_NotEnoughMemInFunction,
        WWISEC_AK_Monitor_ErrorCode_FXNotFound,
        WWISEC_AK_Monitor_ErrorCode_SetMixerNotABus,
        WWISEC_AK_Monitor_ErrorCode_AudioNodeNotFound,
        WWISEC_AK_Monitor_ErrorCode_SetMixerFailed,
        WWISEC_AK_Monitor_ErrorCode_SetBusConfigUnsupported,
        WWISEC_AK_Monitor_ErrorCode_BusNotFound,

        WWISEC_AK_Monitor_ErrorCode_MismatchingMediaSize,
        WWISEC_AK_Monitor_ErrorCode_IncompatibleBankVersion,
        WWISEC_AK_Monitor_ErrorCode_UnexpectedPrepareGameSyncsCall,
        WWISEC_AK_Monitor_ErrorCode_MusicEngineNotInitialized,
        WWISEC_AK_Monitor_ErrorCode_LoadingBankMismatch,

        WWISEC_AK_Monitor_ErrorCode_MasterBusStructureNotLoaded,
        WWISEC_AK_Monitor_ErrorCode_TooManyChildren,
        WWISEC_AK_Monitor_ErrorCode_BankContainUneditableEffect,
        WWISEC_AK_Monitor_ErrorCode_MemoryAllocationFailed,
        WWISEC_AK_Monitor_ErrorCode_InvalidFloatPriority,
        WWISEC_AK_Monitor_ErrorCode_SoundLoadFailedInsufficientMemory,
        WWISEC_AK_Monitor_ErrorCode_NXDeviceRegistrationFailed,
        WWISEC_AK_Monitor_ErrorCode_MixPluginOnObjectBus,

        WWISEC_AK_Monitor_ErrorCode_XboxXMAVoiceResetFailed,
        WWISEC_AK_Monitor_ErrorCode_XboxACPMessage,
        WWISEC_AK_Monitor_ErrorCode_XboxFrameDropped,
        WWISEC_AK_Monitor_ErrorCode_XboxACPError,
        WWISEC_AK_Monitor_ErrorCode_XboxXMAFatalError,
        WWISEC_AK_Monitor_ErrorCode_MissingMusicNodeParent,
        WWISEC_AK_Monitor_ErrorCode_HardwareOpusDecoderError,
        WWISEC_AK_Monitor_ErrorCode_SetGeometryTooManyTriangleConnected,
        WWISEC_AK_Monitor_ErrorCode_SetGeometryTriangleTooLarge,
        WWISEC_AK_Monitor_ErrorCode_SetGeometryFailed,
        WWISEC_AK_Monitor_ErrorCode_RemovingGeometrySetFailed,
        WWISEC_AK_Monitor_ErrorCode_SetGeometryInstanceFailed,
        WWISEC_AK_Monitor_ErrorCode_RemovingGeometryInstanceFailed,

        WWISEC_AK_Monitor_ErrorCode_RevertingToDefaultAudioDevice,
        WWISEC_AK_Monitor_ErrorCode_RevertingToDummyAudioDevice,
        WWISEC_AK_Monitor_ErrorCode_AudioThreadSuspended,
        WWISEC_AK_Monitor_ErrorCode_AudioThreadResumed,
        WWISEC_AK_Monitor_ErrorCode_ResetPlaylistActionIgnoredGlobalScope,
        WWISEC_AK_Monitor_ErrorCode_ResetPlaylistActionIgnoredContinuous,
        WWISEC_AK_Monitor_ErrorCode_PlayingTriggerRateNotSupported,
        WWISEC_AK_Monitor_ErrorCode_SetGeometryTriangleIsSkipped,
        WWISEC_AK_Monitor_ErrorCode_SetGeometryInstanceInvalidTransform,

        // AkSpatialAudio:AkMonitorError_WithID
        WWISEC_AK_Monitor_ErrorCode_SetGameObjectRadiusSizeError,
        WWISEC_AK_Monitor_ErrorCode_SetPortalNonDistinctRoom,
        WWISEC_AK_Monitor_ErrorCode_SetPortalInvalidExtent,
        WWISEC_AK_Monitor_ErrorCode_SpatialAudio_PortalNotFound,

        // Invalid float
        WWISEC_AK_Monitor_ErrorCode_InvalidFloatInFunction,
        WWISEC_AK_Monitor_ErrorCode_FLTMAXNotSupported,

        WWISEC_AK_Monitor_ErrorCode_CannotInitializeAmbisonicChannelConfiguration,
        WWISEC_AK_Monitor_ErrorCode_CannotInitializePassthrough,
        WWISEC_AK_Monitor_ErrorCode_3DAudioUnsupportedSize,
        WWISEC_AK_Monitor_ErrorCode_AmbisonicNotAvailable,

        WWISEC_AK_Monitor_ErrorCode_NoAudioDevice,

        WWISEC_AK_Monitor_ErrorCode_Support,
        WWISEC_AK_Monitor_ErrorCode_ReplayMessage,
        WWISEC_AK_Monitor_ErrorCode_GameMessage,
        WWISEC_AK_Monitor_ErrorCode_TestMessage,
        WWISEC_AK_Monitor_ErrorCode_TranslatorStandardTagTest,
        WWISEC_AK_Monitor_ErrorCode_TranslatorWwiseTagTest,
        WWISEC_AK_Monitor_ErrorCode_TranslatorStringSizeTest,

        WWISEC_AK_Monitor_ErrorCode_InvalidParameter,

        WWISEC_AK_Monitor_ErrorCode_MaxAudioObjExceeded,
        WWISEC_AK_Monitor_ErrorCode_MMSNotEnabled,
        WWISEC_AK_Monitor_ErrorCode_NotEnoughSystemObj,
        WWISEC_AK_Monitor_ErrorCode_NotEnoughSystemObjWin,

        WWISEC_AK_Monitor_ErrorCode_TransitionNotAccurateSourceTooShort,

        WWISEC_AK_Monitor_ErrorCode_AlreadyInitialized,
        WWISEC_AK_Monitor_ErrorCode_WrongNumberOfArguments,
        WWISEC_AK_Monitor_ErrorCode_DataAlignement,
        WWISEC_AK_Monitor_ErrorCode_PluginMsgWithShareSet,
        WWISEC_AK_Monitor_ErrorCode_SoundEngineNotInit,
        WWISEC_AK_Monitor_ErrorCode_NoDefaultSwitch,
        WWISEC_AK_Monitor_ErrorCode_CantSetBoundSwitch,
        WWISEC_AK_Monitor_ErrorCode_IODeviceInitFailed,
        WWISEC_AK_Monitor_ErrorCode_SwitchListEmpty,
        WWISEC_AK_Monitor_ErrorCode_NoSwitchSelected,

        // ALWAYS ADD NEW CODES AT THE END !!!!!!!
        // Otherwise it may break comm compatibility in a patch

        WWISEC_AK_Monitor_Num_ErrorCodes // THIS STAYS AT END OF ENUM
    } WWISEC_AK_Monitor_ErrorCode;

    AK_CALLBACK(void, WWISEC_AK_Monitor_LocalOutputFunc)
    (
        WWISEC_AK_Monitor_ErrorCode in_eErrorCode,   ///< Error code number value
        const AkOSChar* in_pszError,                 ///< Message or error string to be displayed
        WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel, ///< Specifies whether it should be displayed as a message or an error
        WWISEC_AkPlayingID in_playingID,             ///< Related Playing ID if applicable, AK_INVALID_PLAYING_ID otherwise
        WWISEC_AkGameObjectID in_gameObjID           ///< Related Game Object ID if applicable, AK_INVALID_GAME_OBJECT otherwise
    );

    typedef struct WWISEC_AkStreamMgrSettings WWISEC_AkStreamMgrSettings;
    typedef struct WWISEC_AkDeviceSettings WWISEC_AkDeviceSettings;

    WWISEC_AKRESULT WWISEC_AK_Monitor_PostCode(WWISEC_AK_Monitor_ErrorCode in_eError, WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel, WWISEC_AkPlayingID in_playingID, WWISEC_AkGameObjectID in_gameObjID, WWISEC_AkUniqueID in_audioNodeID, bool in_bIsBus);
    WWISEC_AKRESULT WWISEC_AK_Monitor_PostString(const char* in_pszError, WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel, WWISEC_AkPlayingID in_playingID, WWISEC_AkGameObjectID in_gameObjID, WWISEC_AkUniqueID in_audioNodeID, bool in_bIsBus);
    WWISEC_AKRESULT WWISEC_AK_Monitor_SetLocalOutput(AkUInt32 in_uErrorLevel, WWISEC_AK_Monitor_LocalOutputFunc in_pMonitorFunc);
    WWISEC_AKRESULT WWISEC_AK_Monitor_AddTranslator(WWISEC_AkErrorMessageTranslator* translator, bool overridePreviousTranslators);
    WWISEC_AKRESULT WWISEC_AK_Monitor_ResetTranslator();
    WWISEC_AkTimeMs WWISEC_AK_Monitor_GetTimeStamp();
    void WWISEC_AK_Monitor_MonitorStreamMgrInit(const WWISEC_AkStreamMgrSettings* in_streamMgrSettings);
    void WWISEC_AK_Monitor_MonitorStreamingDeviceInit(WWISEC_AkDeviceID in_deviceID, const WWISEC_AkDeviceSettings* in_deviceSettings);
    void WWISEC_AK_Monitor_MonitorStreamingDeviceDestroyed(WWISEC_AkDeviceID in_deviceID);
    void WWISEC_AK_Monitor_MonitorStreamMgrTerm();
    // END AkMonitorError

    // BEGIN IBytes
    typedef struct WWISEC_AK_IReadBytes WWISEC_AK_IReadBytes;

    typedef struct WWISEC_AK_IReadBytes_FunctionTable
    {
        bool (*ReadBytes)(void* instance, void* in_pData, AkInt32 in_cBytes, AkInt32* out_cRead);
    } WWISEC_AK_IReadBytes_FunctionTable;

    WWISEC_AK_IReadBytes* WWISEC_AK_IReadBytes_CreateInstance(void* instance, const WWISEC_AK_IReadBytes_FunctionTable* functionTable);
    void WWISEC_AK_IReadBytes_DestroyInstance(WWISEC_AK_IReadBytes* instance);

    bool WWISEC_AK_IReadBytes_ReadBytes(WWISEC_AK_IReadBytes* instance, void* in_pData, AkInt32 in_cBytes, AkInt32* out_cRead);

    typedef struct WWISEC_AK_IWriteBytes WWISEC_AK_IWriteBytes;

    typedef struct WWISEC_AK_IWriteBytes_FunctionTable
    {
        bool (*WriteBytes)(void* instance, const void* in_pData, AkInt32 in_cBytes, AkInt32* out_cWritten);
    } WWISEC_AK_IWriteBytes_FunctionTable;

    WWISEC_AK_IWriteBytes* WWISEC_AK_IWriteBytes_CreateInstance(void* instance, const WWISEC_AK_IWriteBytes_FunctionTable* functionTable);
    void WWISEC_AK_IWriteBytes_DestroyInstance(WWISEC_AK_IWriteBytes* instance);

    bool WWISE_AK_IWriteBytes_WriteBytes(WWISEC_AK_IWriteBytes* instance, const void* in_pData, AkInt32 in_cBytes, AkInt32* out_cWritten);
    // END IBytes

    // BEGIN AkCommonDefs
    const WWISEC_AkDataTypeID WWISEC_AK_INT = 0;   ///< Integer data type (uchar, short, and so on)
    const WWISEC_AkDataTypeID WWISEC_AK_FLOAT = 1; ///< Float data type

    typedef struct WWISEC_AK_AkMetering
    {
        /// Peak of each channel in this frame.
        /// Vector of linear peak levels, corresponding to each channel. NULL if AK_EnableBusMeter_Peak is not set (see IAkMixerPluginContext::SetMeteringFlags() or AK::SoundEngine::RegisterBusMeteringCallback()).
        WWISEC_AK_SpeakerVolumes_VectorPtr peak;

        /// True peak of each channel (as defined by ITU-R BS.1770) in this frame.
        /// Vector of linear true peak levels, corresponding to each channel. NULL if AK_EnableBusMeter_TruePeak is not set (see IAkMixerPluginContext::SetMeteringFlags() or AK::SoundEngine::RegisterBusMeteringCallback()).
        WWISEC_AK_SpeakerVolumes_VectorPtr truePeak;

        /// RMS value of each channel in this frame.
        /// Vector of linear rms levels, corresponding to each channel. NULL if AK_EnableBusMeter_RMS is not set (see IAkMixerPluginContext::SetMeteringFlags() or AK::SoundEngine::RegisterBusMeteringCallback()).
        WWISEC_AK_SpeakerVolumes_VectorPtr rms;

        /// Mean k-weighted power value in this frame, used to compute loudness (as defined by ITU-R BS.1770).
        /// Total linear k-weighted power of all channels. 0 if AK_EnableBusMeter_KPower is not set (see IAkMixerPluginContext::SetMeteringFlags() or AK::SoundEngine::RegisterBusMeteringCallback()).
        AkReal32 fMeanPowerK;
    } WWISEC_AK_AkMetering;

    typedef struct WWISEC_Ak3DAudioSinkCapabilities
    {
        WWISEC_AkChannelConfig channelConfig;  /// Channel configuration of the main mix.
        AkUInt32 uMaxSystemAudioObjects;       /// Maximum number of System Audio Objects that can be active concurrently. A value of zero indicates the system does not support this feature.
        AkUInt32 uAvailableSystemAudioObjects; /// How many System Audio Objects can currently be sent to the sink. This value can change at runtime depending on what is playing. Can never be higher than uMaxSystemAudioObjects.
        bool bPassthrough;                     /// Separate  pass-through mix is supported.
        bool bMultiChannelObjects;             /// Can handle multi-channel objects
    } WWISEC_Ak3DAudioSinkCapabilities;

    typedef AkReal32 WWISEC_AkSampleType; ///< Audio sample data type (32 bit floating point)

    typedef struct WWISEC_AkAudioBuffer
    {
        void* pData;                          ///< Start of the audio buffer.
        WWISEC_AkChannelConfig channelConfig; ///< Channel config.
        WWISEC_AKRESULT eState;               ///< Execution status
        AkUInt16 uMaxFrames;                  ///< Number of sample frames the buffer can hold. Access through AkAudioBuffer::MaxFrames().
        AkUInt16 uValidFrames;                ///< Number of valid sample frames in the audio buffer
    } WWISEC_AkAudioBuffer;

    void WWISEC_AkAudioBuffer_ClearData(WWISEC_AkAudioBuffer* instance);
    void WWISEC_AkAudioBuffer_Clear(WWISEC_AkAudioBuffer* instance);
    AkUInt32 WWISEC_AkAudioBuffer_NumChannels(const WWISEC_AkAudioBuffer* instance);
    bool WWISEC_AkAudioBufer_HasLFE(const WWISEC_AkAudioBuffer* instance);
    WWISEC_AkChannelConfig WWISEC_AkAudioBuffer_GetChannelConfig(const WWISEC_AkAudioBuffer* instance);
    void* WWISEC_AkAudioBuffer_GetInterleavedData(WWISEC_AkAudioBuffer* instance);
    void WWISEC_AkAudioBuffer_AttachInterleavedData(WWISEC_AkAudioBuffer* instance, void* in_pData, AkUInt16 in_uMaxFrames, AkUInt16 in_uValidFrames);
    void WWISEC_AkAudioBuffer_AttachInterleavedData1(WWISEC_AkAudioBuffer* instance, void* in_pData, AkUInt16 in_uMaxFrames, AkUInt16 in_uValidFrames, WWISEC_AkChannelConfig in_channelConfig);
    bool WWISEC_AkAudioBuffer_HasData(const WWISEC_AkAudioBuffer* instance);
    AkUInt32 WWISEC_AkAudioBuffer_StandardToPipelineIndex(WWISEC_AkChannelConfig in_channelConfig, AkUInt32 in_uChannelIdx);
    WWISEC_AkSampleType* WWISEC_AkAudioBuffer_GetChannel(WWISEC_AkAudioBuffer* instance, AkUInt32 in_uIndex);
    WWISEC_AkSampleType* WWISEC_AkAudioBuffer_GetLFE(WWISEC_AkAudioBuffer* instance);
    void WWISEC_AkAudioBuffer_ZeroPadToMaxFrames(WWISEC_AkAudioBuffer* instance);
    void WWISEC_AkAudioBuffer_AttachContiguousDeinterleavedData(WWISEC_AkAudioBuffer* instance, void* in_pData, AkUInt16 in_uMaxFrames, AkUInt16 in_uValidFrames, WWISEC_AkChannelConfig in_channelConfig);
    void* WWISEC_AkAudioBuffer_DetachContiguousDeinterleavedData(WWISEC_AkAudioBuffer* instance);
    bool WWISEC_AkAudioBuffer_CheckValidSamples(WWISEC_AkAudioBuffer* instance);
    void WWISEC_AkAudioBuffer_RelocateMedia(WWISEC_AkAudioBuffer* instance, AkUInt8* in_pNewMedia, AkUInt8* in_pOldMedia);
    AkUInt16 WWISEC_AkAudioBuffer_MaxFrames(const WWISEC_AkAudioBuffer* instance);
    // END AkCommonDefs

    typedef struct WWISEC_AK_IAkStreamMgr WWISEC_AK_IAkStreamMgr;
    typedef struct WWISEC_AK_IAkMixerInputContext WWISEC_AK_IAkMixerInputContext;
    typedef struct WWISEC_AK_IAkMixerPluginContext WWISEC_AK_IAkMixerPluginContext;
    typedef struct WWISEC_AK_IAkGlobalPluginContext WWISEC_AK_IAkGlobalPluginContext;
    typedef struct WWISEC_AK_IAkPlugin WWISEC_AK_IAkPlugin;
    typedef struct WWISEC_AK_IAkPluginParam WWISEC_AK_IAkPluginParam;
    typedef struct WWISEC_AK_IAkPluginMemAlloc WWISEC_AK_IAkPluginMemAlloc;

    // BEGIN AkCallback
    typedef enum WWISEC_AkCallbackType
    {
        WWISEC_AK_EndOfEvent = 0x0001,                      ///< Callback triggered when reaching the end of an event. AkCallbackInfo can be cast to AkEventCallbackInfo.
        WWISEC_AK_EndOfDynamicSequenceItem = 0x0002,        ///< Callback triggered when reaching the end of a dynamic sequence item. AkCallbackInfo can be cast to AkDynamicSequenceItemCallbackInfo.
        WWISEC_AK_Marker = 0x0004,                          ///< Callback triggered when encountering a marker during playback. AkCallbackInfo can be cast to AkMarkerCallbackInfo.
        WWISEC_AK_Duration = 0x0008,                        ///< Callback triggered when the duration of the sound is known by the sound engine. AkCallbackInfo can be cast to AkDurationCallbackInfo.
        WWISEC_AK_SpeakerVolumeMatrix = 0x0010,             ///< Callback triggered at each frame, letting the client modify the speaker volume matrix. AkCallbackInfo can be cast to AkSpeakerVolumeMatrixCallbackInfo.
        WWISEC_AK_Starvation = 0x0020,                      ///< Callback triggered when playback skips a frame due to stream starvation. AkCallbackInfo can be cast to AkEventCallbackInfo.
        WWISEC_AK_MusicPlaylistSelect = 0x0040,             ///< Callback triggered when music playlist container must select the next item to play. AkCallbackInfo can be cast to AkMusicPlaylistCallbackInfo.
        WWISEC_AK_MusicPlayStarted = 0x0080,                ///< Callback triggered when a "Play" or "Seek" command has been executed ("Seek" commands are issued from AK::SoundEngine::SeekOnEvent()). Applies to objects of the Interactive-Music Hierarchy only. AkCallbackInfo can be cast to AkEventCallbackInfo.
        WWISEC_AK_MusicSyncBeat = 0x0100,                   ///< Enable notifications on Music Beat. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncBar = 0x0200,                    ///< Enable notifications on Music Bar. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncEntry = 0x0400,                  ///< Enable notifications on Music Entry Cue. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncExit = 0x0800,                   ///< Enable notifications on Music Exit Cue. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncGrid = 0x1000,                   ///< Enable notifications on Music Grid. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncUserCue = 0x2000,                ///< Enable notifications on Music Custom Cue. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncPoint = 0x4000,                  ///< Enable notifications on Music switch transition synchronization point. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncAll = 0x7f00,                    ///< Use this flag if you want to receive all notifications concerning AK_MusicSync registration.
        WWISEC_AK_MIDIEvent = 0x10000,                      ///< Enable notifications for MIDI events. AkCallbackInfo can be cast to AkMIDIEventCallbackInfo.
        WWISEC_AK_CallbackBits = 0xfffff,                   ///< Bitmask for all callback types.
        WWISEC_AK_EnableGetSourcePlayPosition = 0x100000,   ///< Enable play position information for use by AK::SoundEngine::GetSourcePlayPosition().
        WWISEC_AK_EnableGetMusicPlayPosition = 0x200000,    ///< Enable play position information of music objects, queried via AK::MusicEngine::GetPlayingSegmentInfo().
        WWISEC_AK_EnableGetSourceStreamBuffering = 0x400000 ///< Enable stream buffering information for use by AK::SoundEngine::GetSourceStreamBuffering().
    } WWISEC_AkCallbackType;

    typedef struct WWISEC_AkCallbackInfo
    {
        void* pCookie;                   ///< User data, passed to PostEvent()
        WWISEC_AkGameObjectID gameObjID; ///< Game object ID
    } WWISEC_AkCallbackInfo;

    typedef struct WWISEC_AkEventCallbackInfo
    {
        WWISEC_AkCallbackInfo base;
        WWISEC_AkPlayingID playingID; ///< Playing ID of Event, returned by PostEvent()
        WWISEC_AkUniqueID eventID;    ///< Unique ID of Event, passed to PostEvent()
    } WWISEC_AkEventCallbackInfo;

    typedef struct WWISEC_AkMIDIEventCallbackInfo
    {
        WWISEC_AkEventCallbackInfo base;
        WWISEC_AkMIDIEvent midiEvent; ///< MIDI event triggered by event.
    } WWISEC_AkMIDIEventCallbackInfo;

    typedef struct WWISEC_AkMarkerCallbackInfo
    {
        WWISEC_AkEventCallbackInfo base;
        AkUInt32 uIdentifier; ///< Cue point identifier
        AkUInt32 uPosition;   ///< Position in the cue point (unit: sample frames)
        const char* strLabel; ///< Label of the marker, read from the file
    } WWISEC_AkMarkerCallbackInfo;

    typedef struct WWISEC_AkDurationCallbackInfo
    {
        WWISEC_AkEventCallbackInfo base;
        AkReal32 fDuration;            ///< Duration of the sound (unit: milliseconds)
        AkReal32 fEstimatedDuration;   ///< Estimated duration of the sound depending on source settings such as pitch. (unit: milliseconds)
        WWISEC_AkUniqueID audioNodeID; ///< Audio Node ID of playing item
        WWISEC_AkUniqueID mediaID;     ///< Media ID of playing item. (corresponds to 'ID' attribute of 'File' element in SoundBank metadata file)
        bool bStreaming;               ///< True if source is streaming, false otherwise.
    } WWISEC_AkDurationCallbackInfo;

    typedef struct WWISEC_AkDynamicSequenceItemCallbackInfo
    {
        WWISEC_AkCallbackInfo base;
        WWISEC_AkPlayingID playingID;  ///< Playing ID of Dynamic Sequence, returned by AK::SoundEngine:DynamicSequence::Open()
        WWISEC_AkUniqueID audioNodeID; ///< Audio Node ID of finished item
        void* pCustomInfo;             ///< Custom info passed to the DynamicSequence::Open function
    } WWISEC_AkDynamicSequenceItemCallbackInfo;

    typedef struct WWISEC_AkSpeakerVolumeMatrixCallbackInfo
    {
        WWISEC_AkEventCallbackInfo base;
        WWISEC_AK_SpeakerVolumes_MatrixPtr pVolumes;    ///< Pointer to volume matrix describing the contribution of each source channel to destination channels. Use methods of AK::SpeakerVolumes::Matrix to interpret them.
        WWISEC_AkChannelConfig inputConfig;             ///< Channel configuration of the voice/bus.
        WWISEC_AkChannelConfig outputConfig;            ///< Channel configuration of the output bus.
        AkReal32* pfBaseVolume;                         ///< Base volume, common to all channels.
        AkReal32* pfEmitterListenerVolume;              ///< Emitter-listener pair-specific gain. When there are multiple emitter-listener pairs, this volume is set to that of the loudest pair, and the relative gain of other pairs is applied directly on the channel volume matrix pVolumes.
        WWISEC_AK_IAkMixerInputContext* pContext;       ///< Context of the current voice/bus about to be mixed into the output bus with specified base volume and volume matrix.
        WWISEC_AK_IAkMixerPluginContext* pMixerContext; ///< Output mixing bus context. Use it to access a few useful panning and mixing services, as well as the ID of the output bus. NULL if pContext is the master audio bus.
    } WWISEC_AkSpeakerVolumeMatrixCallbackInfo;

    typedef struct WWISEC_AkBusMeteringCallbackInfo
    {
        WWISEC_AkCallbackInfo base;
        WWISEC_AK_AkMetering* pMetering;       ///< Struct containing metering information.
        WWISEC_AkChannelConfig channelConfig;  ///< Channel configuration of the bus.
        WWISEC_AkMeteringFlags eMeteringFlags; ///< Metering flags that were asked for in RegisterBusMeteringCallback(). You may only access corresponding meter values from in_pMeteringInfo. Others will fail.
    } WWISEC_AkBusMeteringCallbackInfo;

    typedef struct WWISEC_AkOutputDeviceMeteringCallbackInfo
    {
        WWISEC_AkCallbackInfo base;
        WWISEC_AK_AkMetering* pMainMixMetering;             ///< Metering information for the main mix
        WWISEC_AkChannelConfig mainMixConfig;               ///< Channel configuration of the main mix
        WWISEC_AK_AkMetering* pPassthroughMetering;         ///< Metering information for the passthrough mix (if any; will be null otherwise)
        WWISEC_AkChannelConfig passthroughMixConfig;        ///< Channel configuration of the passthrough mix (if any; will be invalid otherwise)
        AkUInt32 uNumSystemAudioObjects;                    ///< Number of System Audio Objects going out of the output device
        WWISEC_AK_AkMetering** ppSystemAudioObjectMetering; ///< Metering information for each System Audio Object (number of elements is equal to uNumSystemAudioObjects)
        WWISEC_AkMeteringFlags eMeteringFlags;              ///< Metering flags that were asked for in RegisterOutputDeviceMeteringCallback(). You may only access corresponding meter values from the metering objects. Others will fail.
    } WWISEC_AkOutputDeviceMeteringCallbackInfo;

    typedef struct WWISEC_AkMusicPlaylistCallbackInfo
    {
        WWISEC_AkEventCallbackInfo base;
        WWISEC_AkUniqueID playlistID; ///< ID of playlist node
        AkUInt32 uNumPlaylistItems;   ///< Number of items in playlist node (may be segments or other playlists)
        AkUInt32 uPlaylistSelection;  ///< Selection: set by sound engine, modifWWISEC_AkMusicPlaylistCallbackInfoied by callback function (if not in range 0 <= uPlaylistSelection < uNumPlaylistItems then ignored).
        AkUInt32 uPlaylistItemDone;   ///< Playlist node done: set by sound engine, modified by callback function (if set to anything but 0 then the current playlist item is done, and uPlaylistSelection is ignored)
    } WWISEC_AkMusicPlaylistCallbackInfo;

    typedef struct WWISEC_AkSegmentInfo
    {
        WWISEC_AkTimeMs iCurrentPosition;        ///< Current position of the segment, relative to the Entry Cue, in milliseconds. Range is [-iPreEntryDuration, iActiveDuration+iPostExitDuration].
        WWISEC_AkTimeMs iPreEntryDuration;       ///< Duration of the pre-entry region of the segment, in milliseconds.
        WWISEC_AkTimeMs iActiveDuration;         ///< Duration of the active region of the segment (between the Entry and Exit Cues), in milliseconds.
        WWISEC_AkTimeMs iPostExitDuration;       ///< Duration of the post-exit region of the segment, in milliseconds.
        WWISEC_AkTimeMs iRemainingLookAheadTime; ///< Number of milliseconds remaining in the "looking-ahead" state of the segment, when it is silent but streamed tracks are being prefetched.
        AkReal32 fBeatDuration;                  ///< Beat Duration in seconds.
        AkReal32 fBarDuration;                   ///< Bar Duration in seconds.
        AkReal32 fGridDuration;                  ///< Grid duration in seconds.
        AkReal32 fGridOffset;                    ///< Grid offset in seconds.
    } WWISEC_AkSegmentInfo;

    typedef struct WWISEC_AkMusicSyncCallbackInfo
    {
        WWISEC_AkCallbackInfo base;
        WWISEC_AkPlayingID playingID;        ///< Playing ID of Event, returned by PostEvent()
        WWISEC_AkSegmentInfo segmentInfo;    ///< Segment information corresponding to the segment triggering this callback.
        WWISEC_AkCallbackType musicSyncType; ///< Would be either \ref AK_MusicSyncEntry, \ref AK_MusicSyncBeat, \ref AK_MusicSyncBar, \ref AK_MusicSyncExit, \ref AK_MusicSyncGrid, \ref AK_MusicSyncPoint or \ref AK_MusicSyncUserCue.
        char* pszUserCueName;                ///< Cue name (UTF-8 string). Set for notifications AK_MusicSyncUserCue. NULL if cue has no name.
    } WWISEC_AkMusicSyncCallbackInfo;

    typedef struct WWISEC_AkResourceMonitorDataSummary
    {
        AkReal32 totalCPU;       ///< Pourcentage of the cpu time used for processing audio. Please note that the numbers may add up when using multiple threads.
        AkReal32 pluginCPU;      ///< Pourcentage of the cpu time used by plugin processing. Please note that the numbers may add up when using multiple threads.
        AkUInt32 physicalVoices; ///< Number of active physical voices
        AkUInt32 virtualVoices;  ///< Number of active virtual voices
        AkUInt32 totalVoices;    ///< Number of active physical and virtual voices
        AkUInt32 nbActiveEvents; ///< Number of events triggered at a certain time
    } WWISEC_AkResourceMonitorDataSummary;

    AK_CALLBACK(void, WWISEC_AkCallbackFunc)
    (
        WWISEC_AkCallbackType in_eType,         ///< Callback type.
        WWISEC_AkCallbackInfo* in_pCallbackInfo ///< Structure containing desired information. You can cast it to the proper sub-type, depending on the callback type.
    );

    AK_CALLBACK(void, WWISEC_AkBusCallbackFunc)
    (
        WWISEC_AkSpeakerVolumeMatrixCallbackInfo* in_pCallbackInfo ///< Structure containing desired bus information.
    );

    AK_CALLBACK(void, WWISEC_AkBusMeteringCallbackFunc)
    (
        WWISEC_AkBusMeteringCallbackInfo* in_pCallbackInfo ///< Structure containing desired bus information.
    );

    AK_CALLBACK(void, WWISEC_AkOutputDeviceMeteringCallbackFunc)
    (
        WWISEC_AkOutputDeviceMeteringCallbackInfo* in_pCallbackInfo ///< Structure containing desired output device information.
    );

    AK_CALLBACK(void, WWISEC_AkBankCallbackFunc)
    (
        AkUInt32 in_bankID,
        const void* in_pInMemoryBankPtr,
        WWISEC_AKRESULT in_eLoadResult,
        void* in_pCookie);

    typedef enum WWISEC_AkGlobalCallbackLocation
    {
        WWISEC_AkGlobalCallbackLocation_Register = (1 << 0),                        ///< Right after successful registration of callback/plugin. Typically used by plugins along with AkGlobalCallbackLocation_Term for allocating memory for the lifetime of the sound engine.
        WWISEC_AkGlobalCallbackLocation_Begin = (1 << 1),                           ///< Start of audio processing. The number of frames about to be rendered depends on the sink/end-point and can be zero.
        WWISEC_AkGlobalCallbackLocation_PreProcessMessageQueueForRender = (1 << 2), ///< Start of frame rendering, before having processed game messages.
        WWISEC_AkGlobalCallbackLocation_PostMessagesProcessed = (1 << 3),           ///< After one or more messages have been processed, but before updating game object and listener positions internally.
        WWISEC_AkGlobalCallbackLocation_BeginRender = (1 << 4),                     ///< Start of frame rendering, after having processed game messages.
        WWISEC_AkGlobalCallbackLocation_EndRender = (1 << 5),                       ///< End of frame rendering.
        WWISEC_AkGlobalCallbackLocation_End = (1 << 6),                             ///< End of audio processing.
        WWISEC_AkGlobalCallbackLocation_Term = (1 << 7),                            ///< Sound engine termination.
        WWISEC_AkGlobalCallbackLocation_Monitor = (1 << 8),                         ///< Send monitor data
        WWISEC_AkGlobalCallbackLocation_MonitorRecap = (1 << 9),                    ///< Send monitor data connection to recap.
        WWISEC_AkGlobalCallbackLocation_Init = (1 << 10),                           ///< Sound engine initialization.
        WWISEC_AkGlobalCallbackLocation_Suspend = (1 << 11),                        ///< Sound engine suspension through \ref AK::SoundEngine::Suspend
        WWISEC_AkGlobalCallbackLocation_WakeupFromSuspend = (1 << 12),              ///< Sound engine awakening through \ref AK::SoundEngine::WakeupFromSuspend
        WWISEC_AkGlobalCallbackLocation_Num = 13                                    ///< Total number of global callback locations.
    } WWISEC_AkGlobalCallbackLocation;

    AK_CALLBACK(void, WWISEC_AkGlobalCallbackFunc)
    (
        WWISEC_AK_IAkGlobalPluginContext* in_pContext, ///< Engine context.
        WWISEC_AkGlobalCallbackLocation in_eLocation,  ///< Location where this callback is fired.
        void* in_pCookie                               ///< User cookie passed to AK::SoundEngine::RegisterGlobalCallback().
    );

    AK_CALLBACK(void, WWISEC_AkResourceMonitorCallbackFunc)
    (
        const WWISEC_AkResourceMonitorDataSummary* in_pdataSummary ///< Data summary passed to the function registered using AK::SoundEngine::RegisterResourceMonitorCallback().
    );

    typedef enum WWISEC_AK_AkAudioDeviceEvent
    {
        WWISEC_AK_AkAudioDeviceEvent_Initialization, ///< Sent after an Audio Device has initialized.  Initialization might have failed, check the AKRESULT.
        WWISEC_AK_AkAudioDeviceEvent_Removal,        ///< Audio device was removed through explicit call (AK::SoundEngine::RemoveOutput or AK::SoundEngine::Term)
        WWISEC_AK_AkAudioDeviceEvent_SystemRemoval   ///< Audio device was removed because of a system event (disconnection), hardware or driver problem. Check the AKRESULT when called through AkDeviceStatusCallbackFunc, it may give more context.
    } WWISEC_AK_AkAudioDeviceEvent;

    AK_CALLBACK(void, WWISEC_AK_AkDeviceStatusCallbackFunc)
    (
        WWISEC_AK_IAkGlobalPluginContext* in_pContext, ///< Engine context.
        WWISEC_AkUniqueID in_idAudioDeviceShareset,    ///< The audio device shareset attached, as passed to AK::SoundEngine::AddOutput or AK::SoundEngine::Init
        AkUInt32 in_idDeviceID,                        ///< The audio device specific id, as passed to AK::SoundEngine::AddOutput or AK::SoundEngine::Init
        WWISEC_AK_AkAudioDeviceEvent in_idEvent,       ///< The event for which this callback was called.  See AK::AkAudioDeviceEvent.  AKRESULT may provide more information.
        WWISEC_AKRESULT in_AkResult                    ///< Result of the last operation.
    );

    AK_CALLBACK(void, WWISEC_AkCaptureCallbackFunc)
    (
        WWISEC_AkAudioBuffer* in_CaptureBuffer, ///< Capture audio buffer. The data is always float interleaved.
        WWISEC_AkOutputDeviceID in_idOutput,    ///< The audio device specific id, as passed to AK::SoundEngine::AddOutput or AK::SoundEngine::Init
        void* in_pCookie                        ///< Callback cookie that will be sent to the callback function along with additional information
    );
    // END AkCallback

    // BEGIN AkVirtualAcoustics
    typedef struct WWISEC_AkAcousticTexture
    {
        AkUInt32 ID;

        AkReal32 fAbsorptionOffset;
        AkReal32 fAbsorptionLow;
        AkReal32 fAbsorptionMidLow;
        AkReal32 fAbsorptionMidHigh;
        AkReal32 fAbsorptionHigh;
        AkReal32 fScattering;
    } WWISEC_AkAcousticTexture;
    // END AkVirtualAcoustics

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

    typedef enum WWISEC_AkSpanCount
    {
        // Span count attempts to be as low as possible. Offers lowest memory usage, but reduces CPU performance due to increased calls to pfAllocVM and other memory allocation hooks.
        WWISEC_AkSpanCount_Small = 0,

        // Span count attempts to match 512KiB mappings. Offers moderate balance between memory and CPU usage.
        WWISEC_AkSpanCount_Medium,

        // Span count attempts to match 2MiB, or AK_VM_HUGE_PAGE_SIZE, mappings. Offers best overall CPU performance due to use of 2MiB page mappings, but increased memory usage.
        WWISEC_AkSpanCount_Huge,

        WWISEC_AkSpanCount_END,
    } WWISEC_AkSpanCount;

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
        WWISEC_AkMemAllocVM pfAllocVM;         ///< Virtual page allocation hook.
        WWISEC_AkMemFreeVM pfFreeVM;           ///< Virtual page allocation hook.
        WWISEC_AkMemAllocVM pfAllocDevice;     ///< Device page allocation hook.
        WWISEC_AkMemFreeVM pfFreeDevice;       ///< Device page allocation hook.
        AkUInt32 uVMPageSize;                  ///< Virtual memory page size. Defaults to 0 which means auto-detect.
        AkUInt32 uDevicePageSize;              ///< Device memory page size. Defaults to 0 which means auto-detect.
        AkUInt32 uMaxThreadLocalHeapAllocSize; ///< All memory allocations of sizes larger than this value will go to a global heap shared across all threads. Defaults to 0 which means all allocations go to a global heap.
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
        WWISEC_AkSpanCount uVMSpanCount;
        WWISEC_AkSpanCount uDeviceSpanCount;
    } WWISEC_AkMemSettings;

    WWISEC_AKRESULT WWISEC_AK_MemoryMgr_Init(WWISEC_AkMemSettings* in_pSettings);
    void WWISEC_AK_MemoryMgr_GetDefaultSettings(WWISEC_AkMemSettings* out_pMemSettings);
    // END AkModule

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

    // BEGIN IAkPlugin
    typedef struct WWISEC_AkInitSettings WWISEC_AkInitSettings;
    typedef struct WWISEC_IAkPlatformContext WWISEC_IAkPlatformContext;
    typedef struct WWISEC_IAkPluginService WWISEC_IAkPluginService;

    AK_CALLBACK(WWISEC_AK_IAkPlugin*, WWISEC_AkCreatePluginCallback)
    (WWISEC_AK_IAkPluginMemAlloc* in_pAllocator);
    AK_CALLBACK(WWISEC_AK_IAkPluginParam*, WWISEC_AkCreateParamCallback)
    (WWISEC_AK_IAkPluginMemAlloc* in_pAllocator);
    /// Registered plugin device enumeration function prototype, used for providing lists of devices by plug-ins.
    AK_CALLBACK(WWISEC_AKRESULT, WWISEC_AkGetDeviceListCallback)
    (
        AkUInt32* io_maxNumDevices,                        ///< In: The length of the out_deviceDescriptions array, or zero is out_deviceDescriptions is null. Out: If out_deviceDescriptions is not-null, this should be set to the number of entries in out_deviceDescriptions that was populated (and should be less-than-or-equal to the initial value). If out_deviceDescriptions is null, this should be set to the maximum number of devices that may be returned by this callback.
        WWISEC_AkDeviceDescription* out_deviceDescriptions ///< The output array of device descriptions. If this is not-null, there will be a number of entries equal to the input value of io_maxNumDevices.
    );

    typedef enum WWISEC_AK_AkPluginServiceType
    {
        WWISEC_AK_PluginServiceType_Mixer = 0,
        WWISEC_AK_PluginServiceType_RNG = 1,
        WWISEC_AK_PluginServiceType_AudioObjectAttenuation = 2,
        WWISEC_AK_PluginServiceType_AudioObjectPriority = 3,
        WWISEC_AK_PluginServiceType_MAX,
    } WWISEC_AK_AkPluginServiceType;

    WWISEC_AK_IAkStreamMgr* WWISEC_AK_IAkGlobalPluginContext_GetStreamMgr(const WWISEC_AK_IAkGlobalPluginContext* self);
    AkUInt16 WWISEC_AK_IAkGlobalPluginContext_GetMaxBufferLength(const WWISEC_AK_IAkGlobalPluginContext* self);
    bool WWISEC_AK_IAkGlobalPluginContext_IsRenderingOffline(const WWISEC_AK_IAkGlobalPluginContext* self);
    AkUInt32 WWISEC_AK_IAkGlobalPluginContext_GetSampleRate(const WWISEC_AK_IAkGlobalPluginContext* self);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_PostMonitorMessage(WWISEC_AK_IAkGlobalPluginContext* self, const char* in_pszError, WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterPlugin(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreatePluginCallback in_pCreateFunc, WWISEC_AkCreateParamCallback in_pCreateParamFunc);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterCodec(WWISEC_AK_IAkGlobalPluginContext* self, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreateFileSourceCallback in_pFileCreateFunc, WWISEC_AkCreateBankSourceCallback in_pBankCreateFunc);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterGlobalCallback(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation, void* in_pCookie);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_UnregisterGlobalCallback(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation);
    WWISEC_AK_IAkPluginMemAlloc* WWISEC_AK_IAkGlobalPluginContext_GetAllocator(WWISEC_AK_IAkGlobalPluginContext* self);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_SetRTPCValue(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkRtpcID in_rtpcID, WWISEC_AkRtpcValue in_value, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_SendPluginCustomGameData(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkUniqueID in_busID, WWISEC_AkGameObjectID in_busObjectID, WWISEC_AkPluginType in_eType, AkUInt32 in_uCompanyID, AkUInt32 in_uPluginID, const void* in_pData, AkUInt32 in_uSizeInBytes);
    void WWISEC_AK_IAkGlobalPluginContext_ComputeAmbisonicsEncoding(WWISEC_AK_IAkGlobalPluginContext* self, AkReal32 in_fAzimuth, AkReal32 in_fElevation, WWISEC_AkChannelConfig in_cfgAmbisonics, WWISEC_AK_SpeakerVolumes_VectorPtr out_vVolumes);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_ComputeWeightedAmbisonicsDecodingFromSampledSphere(WWISEC_AK_IAkGlobalPluginContext* self, const WWISEC_AkVector* in_samples, AkUInt32 in_uNumSamples, WWISEC_AkChannelConfig in_cfgAmbisonics, WWISEC_AK_SpeakerVolumes_MatrixPtr out_mxVolume);
    const WWISEC_AkAcousticTexture* WWISEC_AK_IAkGlobalPluginContext_GetAcousticTexture(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkAcousticTextureID in_AcousticTextureID);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_ComputeSphericalCoordinates(const WWISEC_AK_IAkGlobalPluginContext* self, const WWISEC_AkEmitterListenerPair* in_pair, AkReal32* out_fAzimuth, AkReal32* out_fElevation);
    const WWISEC_AkPlatformInitSettings* WWISEC_AK_IAkGlobalPluginContext_GetPlatformInitSettings(const WWISEC_AK_IAkGlobalPluginContext* self);
    const WWISEC_AkInitSettings* WWISEC_AK_IAkGlobalPluginContext_GetInitSettings(const WWISEC_AK_IAkGlobalPluginContext* self);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_GetAudioSettings(const WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkAudioSettings* out_audioSettings);
    AkUInt32 WWISEC_AK_IAkGlobalPluginContext_GetIDFromString(const WWISEC_AK_IAkGlobalPluginContext* self, const char* in_pszString);
    WWISEC_AkPlayingID WWISEC_AK_IAkGlobalPluginContext_PostEventSync(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources, WWISEC_AkPlayingID in_PlayingID);
    WWISEC_AkPlayingID WWISEC_AK_IAkGlobalPluginContext_PostMIDIOnEventSync(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkMIDIPost* in_pPosts, AkUInt16 in_uNumPosts, bool in_bAbsoluteOffsets, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, WWISEC_AkPlayingID in_playingID);
    WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_StopMIDIOnEventSync(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkPlayingID in_playingID);
    WWISEC_IAkPlatformContext* WWISEC_AK_IAkGlobalPluginContext_GetPlatformContext(const WWISEC_AK_IAkGlobalPluginContext* self);
    WWISEC_IAkPluginService* WWISEC_AK_IAkGlobalPluginContext_GetPluginService(const WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AK_AkPluginServiceType in_pluginService);
    AkUInt32 WWISEC_AK_IAkGlobalPluginContext_GetBufferTick(const WWISEC_AK_IAkGlobalPluginContext* self);
    // END IAkPlugin

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

    typedef enum WWISEC_AkActionOnEventType
    {
        WWISEC_AkActionOnEventType_Stop = 0,           ///< Stop
        WWISEC_AkActionOnEventType_Pause = 1,          ///< Pause
        WWISEC_AkActionOnEventType_Resume = 2,         ///< Resume
        WWISEC_AkActionOnEventType_Break = 3,          ///< Break
        WWISEC_AkActionOnEventType_ReleaseEnvelope = 4 ///< Release envelope
    } WWISEC_AkActionOnEventType;

    typedef struct WWISEC_AkSourceSettings
    {
        WWISEC_AkUniqueID sourceID; ///< Source ID (available in the SoundBank content files)
        AkUInt8* pMediaMemory;      ///< Pointer to the data to be set for the source
        AkUInt32 uMediaSize;        ///< Size, in bytes, of the data to be set for the source
    } WWISEC_AkSourceSettings;

    typedef struct WWISEC_AkSourcePosition
    {
        WWISEC_AkUniqueID audioNodeID; ///< Audio Node ID of playing item
        WWISEC_AkUniqueID mediaID;     ///< Media ID of playing item. (corresponds to 'ID' attribute of 'File' element in SoundBank metadata file)
        WWISEC_AkTimeMs msTime;        ///< Position of the source (in ms) associated with that playing item
        AkUInt32 samplePosition;       ///< Position of the source (in samples) associated with that playing item
        AkUInt32 updateBufferTick;     ///< Value of GetBufferTick() at the time the position was updated
    } WWISEC_AkSourcePosition;

    typedef enum WWISEC_AK_SoundEngine_PreparationType
    {
        WWISEC_AK_SoundEngine_Preparation_Load,         ///< \c PrepareEvent() will load required information to play the specified event.
        WWISEC_AK_SoundEngine_Preparation_Unload,       ///< \c PrepareEvent() will unload required information to play the specified event.
        WWISEC_AK_SoundEngine_Preparation_LoadAndDecode ///< Vorbis media is decoded when loading, and an uncompressed PCM version is used for playback.
    } WWISEC_AK_SoundEngine_PreparationType;

    typedef enum WWISEC_AK_SoundEngine_AkBankContent
    {
        WWISEC_AK_SoundEngine_AkBankContent_StructureOnly, ///< Use AkBankContent_StructureOnly to load only the structural content, including Events, and then later use the PrepareEvent() functions to load media on demand from loose files on the disk.
        WWISEC_AK_SoundEngine_AkBankContent_All            ///< Use AkBankContent_All to load both the media and structural content.
    } WWISEC_AK_SoundEngine_AkBankContent;

    bool WWISEC_AK_SoundEngine_IsInitialized();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Init(WWISEC_AkInitSettings* in_pSettings, WWISEC_AkPlatformInitSettings* in_pPlatformSettings);

    void WWISEC_AK_SoundEngine_GetDefaultInitSettings(WWISEC_AkInitSettings* out_settings);

    void WWISEC_AK_SoundEngine_GetDefaultPlatformInitSettings(WWISEC_AkPlatformInitSettings* out_platformSettings);

    void WWISEC_AK_SoundEngine_Term();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetAudioSettings(WWISEC_AkAudioSettings* out_audioSettings);

    WWISEC_AkChannelConfig WWISEC_AK_SoundEngine_GetSpeakerConfiguration(WWISEC_AkOutputDeviceID in_idOutput);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetOutputDeviceConfiguration(WWISEC_AkOutputDeviceID in_idOutput, WWISEC_AkChannelConfig* io_channelConfig, WWISEC_Ak3DAudioSinkCapabilities* io_capabilities);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetPanningRule(WWISEC_AkPanningRule* out_ePanningRule, WWISEC_AkOutputDeviceID in_idOutput);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetPanningRule(WWISEC_AkPanningRule in_ePanningRule, WWISEC_AkOutputDeviceID in_idOutput);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetSpeakerAngles(AkReal32* io_pfSpeakerAngles, AkUInt32* io_uNumAngles, AkReal32* out_fHeightAngle, WWISEC_AkOutputDeviceID in_idOutput);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetSpeakerAngles(const AkReal32* in_pfSpeakerAngles, AkUInt32 in_uNumAngles, AkReal32 in_fHeightAngle, WWISEC_AkOutputDeviceID in_idOutput);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetVolumeThreshold(AkReal32 in_fVolumeThresholdDB);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMaxNumVoicesLimit(AkUInt16 in_maxNumberVoices);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetJobMgrMaxActiveWorkers(WWISEC_AkJobType in_jobType, AkUInt32 in_uNewMaxActiveWorkers);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RenderAudio(bool in_bAllowSyncRender);

    WWISEC_AK_IAkGlobalPluginContext* WWISEC_AK_SoundEngine_GetGlobalPluginContext();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterPlugin(WWISEC_AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreatePluginCallback in_pCreateFunc, WWISEC_AkCreateParamCallback in_pCreateParamFunc);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterPluginDLL(const AkOSChar* in_DllName, const AkOSChar* in_DllPath);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterGlobalCallback(WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation, void* in_pCookie, WWISEC_AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterGlobalCallback(WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterResourceMonitorCallback(WWISEC_AkResourceMonitorCallbackFunc in_pCallback);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterResourceMonitorCallback(WWISEC_AkResourceMonitorCallbackFunc in_pCallback);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterAudioDeviceStatusCallback(WWISEC_AK_AkDeviceStatusCallbackFunc in_pCallback);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterAudioDeviceStatusCallback();

    AkUInt32 WWISEC_AK_SoundEngine_GetIDFromString(const char* in_pszString);

    WWISEC_AkPlayingID WWISEC_AK_SoundEngine_PostEvent_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources, WWISEC_AkPlayingID in_PlayingID);

    WWISEC_AkPlayingID WWISEC_AK_SoundEngine_PostEvent_String(const char* in_pszEventName, WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources, WWISEC_AkPlayingID in_PlayingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_ExecuteActionOnEvent_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkActionOnEventType in_ActionType, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, WWISEC_AkPlayingID in_PlayingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_ExecuteActionOnEvent_String(const char* in_pszEventName, WWISEC_AkActionOnEventType in_ActionType, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, WWISEC_AkPlayingID in_PlayingID);

    WWISEC_AkPlayingID WWISEC_AK_SoundEngine_PostMIDIOnEvent(WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkMIDIPost* in_pPosts, AkUInt16 in_uNumPosts, bool in_bAbsoluteOffsets, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, WWISEC_AkPlayingID in_playingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_StopMIDIOnEvent(WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkPlayingID in_playingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PinEventInStreamCache_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkPriority in_uActivePriority, WWISEC_AkPriority in_uInactivePriority);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PinEventInStreamCache_String(const char* in_pszEventName, WWISEC_AkPriority in_uActivePriority, WWISEC_AkPriority in_uInactivePriority);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnpinEventInStreamCache_ID(WWISEC_AkUniqueID in_eventID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnpinEventInStreamCache_String(const char* in_pszEventName);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetBufferStatusForPinnedEvent_ID(WWISEC_AkUniqueID in_eventID, AkReal32* out_fPercentBuffered, bool* out_bCachePinnedMemoryFull);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetBufferStatusForPinnedEvent_String(const char* in_pszEventName, AkReal32* out_fPercentBuffered, bool* out_bCachePinnedMemoryFull);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Time_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_iPosition, bool in_bSeekToNearestMarker, WWISEC_AkPlayingID in_PlayingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Time_String(const char* in_pszEventName, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_iPosition, bool in_bSeekToNearestMarker, WWISEC_AkPlayingID in_PlayingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Percent_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker, WWISEC_AkPlayingID in_PlayingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Percent_String(const char* in_pszEventName, WWISEC_AkGameObjectID in_gameObjectID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker, WWISEC_AkPlayingID in_PlayingID);

    void WWISEC_AK_SoundEngine_CancelEventCallbackCookie(void* in_pCookie);

    void WWISEC_AK_SoundEngine_CancelEventCallbackGameObject(WWISEC_AkGameObjectID in_gameObjectID);

    void WWISEC_AK_SoundEngine_CancelEventCallback(WWISEC_AkPlayingID in_playingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetSourcePlayPosition(WWISEC_AkPlayingID in_PlayingID, WWISEC_AkTimeMs* out_puPosition, bool in_bExtrapolate);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetSourcePlayPositions(WWISEC_AkPlayingID in_PlayingID, WWISEC_AkSourcePosition* out_puPositions, AkUInt32* io_pcPositions, bool in_bExtrapolate);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetSourceStreamBuffering(WWISEC_AkPlayingID in_PlayingID, WWISEC_AkTimeMs* out_buffering, bool* out_bIsBuffering);

    void WWISEC_AK_SoundEngine_StopAll(WWISEC_AkGameObjectID in_gameObjectID);

    void WWISEC_AK_SoundEngine_StopPlayingID(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve);

    void WWISEC_AK_SoundEngine_ExecuteActionOnPlayingID(WWISEC_AkActionOnEventType in_ActionType, WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve);

    void WWISEC_AK_SoundEngine_SetRandomSeed(AkUInt32 in_uSeed);

    void WWISEC_AK_SoundEngine_MuteBackgroundMusic(bool in_bMute);

    bool WWISEC_AK_SoundEngine_GetBackgroundMusicMute();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SendPluginCustomGameData(WWISEC_AkUniqueID in_busID, WWISEC_AkGameObjectID in_busObjectID, WWISEC_AkPluginType in_eType, AkUInt32 in_uCompanyID, AkUInt32 in_uPluginID, const void* in_pData, AkUInt32 in_uSizeInBytes);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterGameObj(WWISEC_AkGameObjectID in_gameObjectID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterGameObjWithName(WWISEC_AkGameObjectID in_gameObjectID, const char* in_pszObjName);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterGameObj(WWISEC_AkGameObjectID in_gameObjectID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterAllGameObj();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetPosition(WWISEC_AkGameObjectID in_GameObjectID, const WWISEC_AkSoundPosition* in_Position, WWISEC_AkSetPositionFlags in_eFlags);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMultiplePositions_SoundPosition(WWISEC_AkGameObjectID in_GameObjectID, const WWISEC_AkSoundPosition* in_pPositions, AkUInt16 in_NumPositions, WWISEC_AK_SoundEngine_MultiPositionType in_eMultiPositionType, WWISEC_AkSetPositionFlags in_eFlags);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMultiplePositions_ChannelEmitter(WWISEC_AkGameObjectID in_GameObjectID, const WWISEC_AkChannelEmitter* in_pPositions, AkUInt16 in_NumPositions, WWISEC_AK_SoundEngine_MultiPositionType in_eMultiPositionType, WWISEC_AkSetPositionFlags in_eFlags);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetScalingFactor(WWISEC_AkGameObjectID in_GameObjectID, AkReal32 in_fAttenuationScalingFactor);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetDistanceProbe(WWISEC_AkGameObjectID in_listenerGameObjectID, WWISEC_AkGameObjectID in_distanceProbeGameObjectID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_ClearBanks();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBankLoadIOSettings(AkReal32 in_fThroughput, WWISEC_AkPriority in_priority);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBank_String(const char* in_pszString, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBank_ID(WWISEC_AkBankID in_bankID, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankID* out_bankID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType* out_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankID* out_bankID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType* out_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DecodeBank(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkMemPoolId in_uPoolForDecodedBank, void** out_pDecodedBankPtr, AkUInt32* out_uDecodedBankSize);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBank_Async_String(const char* in_pszString, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBank_Async_ID(WWISEC_AkBankID in_bankID, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_Async(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankID* out_bankID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_Async_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType* out_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy_Async(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType* out_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnloadBank_String(const char* in_pszString, const void* in_pInMemoryBankPtr, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnloadBank_ID(WWISEC_AkBankID in_bankID, const void* in_pInMemoryBankPtr, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnloadBank_Async_String(const char* in_pszString, const void* in_pInMemoryBankPtr, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnloadBank_Async_ID(WWISEC_AkBankID in_bankID, const void* in_pInMemoryBankPtr, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankType in_bankType);

    void WWISEC_AK_SoundEngine_CancelBankCallbackCookie(void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareBank_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char* in_pszString, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareBank_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkBankID in_bankID, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareBank_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char* in_pszString, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareBank_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkBankID in_bankID, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, WWISEC_AkBankType in_bankType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_ClearPreparedEvents();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uNumEvent);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkUniqueID* in_pEventID, AkUInt32 in_uNumEvent);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uNumEvent, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkUniqueID* in_pEventID, AkUInt32 in_uNumEvent, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMedia(WWISEC_AkSourceSettings* in_pSourceSettings, AkUInt32 in_uNumSourceSettings);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnsetMedia(WWISEC_AkSourceSettings* in_pSourceSettings, AkUInt32 in_uNumSourceSettings);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_TryUnsetMedia(WWISEC_AkSourceSettings* in_pSourceSettings, AkUInt32 in_uNumSourceSettings, WWISEC_AKRESULT* out_pUnsetResults);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkGroupType in_eGameSyncType, const char* in_pszGroupName, const char** in_ppszGameSyncName, AkUInt32 in_uNumGameSyncs);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkGroupType in_eGameSyncType, AkUInt32 in_GroupID, AkUInt32* in_paGameSyncID, AkUInt32 in_uNumGameSyncs);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkGroupType in_eGameSyncType, const char* in_pszGroupName, const char** in_ppszGameSyncName, AkUInt32 in_uNumGameSyncs, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkGroupType in_eGameSyncType, AkUInt32 in_GroupID, AkUInt32* in_paGameSyncID, AkUInt32 in_uNumGameSyncs, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetListeners(WWISEC_AkGameObjectID in_emitterGameObj, const WWISEC_AkGameObjectID* in_pListenerGameObjs, AkUInt32 in_uNumListeners);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddListener(WWISEC_AkGameObjectID in_emitterGameObj, WWISEC_AkGameObjectID in_listenerGameObj);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RemoveListener(WWISEC_AkGameObjectID in_emitterGameObj, WWISEC_AkGameObjectID in_listenerGameObj);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetDefaultListeners(const WWISEC_AkGameObjectID* in_pListenerObjs, AkUInt32 in_uNumListeners);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddDefaultListener(WWISEC_AkGameObjectID in_listenerGameObj);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RemoveDefaultListener(WWISEC_AkGameObjectID in_listenerGameObj);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_ResetListenersToDefault(WWISEC_AkGameObjectID in_emitterGameObj);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetListenerSpatialization(WWISEC_AkGameObjectID in_uListenerID, bool in_bSpatialized, WWISEC_AkChannelConfig in_channelConfig, WWISEC_AK_SpeakerVolumes_VectorPtr in_pVolumeOffsets);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetRTPCValue_ID(WWISEC_AkRtpcID in_rtpcID, WWISEC_AkRtpcValue in_value, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetRTPCValue_String(const char* in_pszRtpcName, WWISEC_AkRtpcValue in_value, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetRTPCValueByPlayingID_ID(WWISEC_AkRtpcID in_rtpcID, WWISEC_AkRtpcValue in_value, WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetRTPCValueByPlayingID_String(const char* in_pszRtpcName, WWISEC_AkRtpcValue in_value, WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValue_ID(WWISEC_AkRtpcID in_rtpcID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValue_String(const char* in_pszRtpcName, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetSwitch_ID(WWISEC_AkSwitchGroupID in_switchGroup, WWISEC_AkSwitchStateID in_switchState, WWISEC_AkGameObjectID in_gameObjectID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetSwitch_String(const char* in_pszSwitchGroup, const char* in_pszSwitchState, WWISEC_AkGameObjectID in_gameObjectID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PostTrigger_ID(WWISEC_AkTriggerID in_triggerID, WWISEC_AkGameObjectID in_gameObjectID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_PostTrigger_String(const char* in_pszTrigger, WWISEC_AkGameObjectID in_gameObjectID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetState_ID(WWISEC_AkStateGroupID in_stateGroup, WWISEC_AkStateID in_state);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetState_String(const char* in_pszStateGroup, const char* in_pszState);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetGameObjectAuxSendValues(WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkAuxSendValue* in_aAuxSendValues, AkUInt32 in_uNumSendValues);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterBusVolumeCallback(WWISEC_AkUniqueID in_busID, WWISEC_AkBusCallbackFunc in_pfnCallback, void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterBusMeteringCallback(WWISEC_AkUniqueID in_busID, WWISEC_AkBusMeteringCallbackFunc in_pfnCallback, WWISEC_AkMeteringFlags in_eMeteringFlags, void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterOutputDeviceMeteringCallback(WWISEC_AkOutputDeviceID in_idOutput, WWISEC_AkOutputDeviceMeteringCallbackFunc in_pfnCallback, WWISEC_AkMeteringFlags in_eMeteringFlags, void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetGameObjectOutputBusVolume(WWISEC_AkGameObjectID in_emitterObjID, WWISEC_AkGameObjectID in_listenerObjID, AkReal32 in_fControlValue);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetActorMixerEffect(WWISEC_AkUniqueID in_audioNodeID, AkUInt32 in_uFXIndex, WWISEC_AkUniqueID in_shareSetID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusEffect_ID(WWISEC_AkUniqueID in_audioNodeID, AkUInt32 in_uFXIndex, WWISEC_AkUniqueID in_shareSetID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusEffect_String(const char* in_pszBusName, AkUInt32 in_uFXIndex, WWISEC_AkUniqueID in_shareSetID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetOutputDeviceEffect(WWISEC_AkOutputDeviceID in_outputDeviceID, AkUInt32 in_uFXIndex, WWISEC_AkUniqueID in_FXShareSetID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMixer_ID(WWISEC_AkUniqueID in_audioNodeID, WWISEC_AkUniqueID in_shareSetID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMixer_String(const char* in_pszBusName, WWISEC_AkUniqueID in_shareSetID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusConfig_ID(WWISEC_AkUniqueID in_audioNodeID, WWISEC_AkChannelConfig in_channelConfig);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusConfig_String(const char* in_pszBusName, WWISEC_AkChannelConfig in_channelConfig);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetObjectObstructionAndOcclusion(WWISEC_AkGameObjectID in_EmitterID, WWISEC_AkGameObjectID in_ListenerID, AkReal32 in_fObstructionLevel, AkReal32 in_fOcclusionLevel);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMultipleObstructionAndOcclusion(WWISEC_AkGameObjectID in_EmitterID, WWISEC_AkGameObjectID in_uListenerID, WWISEC_AkObstructionOcclusionValues* in_fObstructionOcclusionValues, AkUInt32 in_uNumOcclusionObstruction);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetContainerHistory(WWISEC_AK_IWriteBytes* in_pBytes);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetContainerHistory(WWISEC_AK_IReadBytes* in_pBytes);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_StartOutputCapture(const AkOSChar* in_CaptureFileName);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_StopOutputCapture();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddOutputCaptureMarker(const char* in_MarkerText);

    AkUInt32 WWISEC_AK_SoundEngine_GetSampleRate();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterCaptureCallback(WWISEC_AkCaptureCallbackFunc in_pfnCallback, WWISEC_AkOutputDeviceID in_idOutput, void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterCaptureCallback(WWISEC_AkCaptureCallbackFunc in_pfnCallback, WWISEC_AkOutputDeviceID in_idOutput, void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_StartProfilerCapture(const AkOSChar* in_CaptureFileName);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_StopProfilerCapture();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetOfflineRenderingFrameTime(AkReal32 in_fFrameTimeInSeconds);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetOfflineRendering(bool in_bEnableOfflineRendering);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddOutput(const WWISEC_AkOutputSettings* in_Settings, WWISEC_AkOutputDeviceID* out_pDeviceID, const WWISEC_AkGameObjectID* in_pListenerIDs, AkUInt32 in_uNumListeners);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_RemoveOutput(WWISEC_AkOutputDeviceID in_idOutput);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_ReplaceOutput(const WWISEC_AkOutputSettings* in_Settings, WWISEC_AkOutputDeviceID in_outputDeviceId, WWISEC_AkOutputDeviceID* out_pOutputDeviceId);

    WWISEC_AkOutputDeviceID WWISEC_AK_SoundEngine_GetOutputID_ID(WWISEC_AkUniqueID in_idShareset, AkUInt32 in_idDevice);

    WWISEC_AkOutputDeviceID WWISEC_AK_SoundEngine_GetOutputID_String(const char* in_szShareSet, AkUInt32 in_idDevice);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusDevice_ID(WWISEC_AkUniqueID in_idBus, WWISEC_AkUniqueID in_idNewDevice);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusDevice_String(const char* in_BusName, const char* in_DeviceName);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetDeviceList_Plugin(AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, AkUInt32* io_maxNumDevices, WWISEC_AkDeviceDescription* out_deviceDescriptions);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetDeviceList_ShareSet(WWISEC_AkUniqueID in_audioDeviceShareSetID, AkUInt32* io_maxNumDevices, WWISEC_AkDeviceDescription* out_deviceDescriptions);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetOutputVolume(WWISEC_AkOutputDeviceID in_idOutput, AkReal32 in_fVolume);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetDeviceSpatialAudioSupport(AkUInt32 in_idDevice);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Suspend(bool in_bRenderAnyway, bool in_bFadeOut);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_WakeupFromSuspend(AkUInt32 in_uDelayMs);

    AkUInt32 WWISEC_AK_SoundEngine_GetBufferTick();

    AkUInt64 WWISEC_AK_SoundEngine_GetSampleTick();
// END AkSoundEngine

// BEGIN IAkStreamMgr
#define WWISEC_AK_MONITOR_STREAMNAME_MAXLENGTH (64)
#define WWISEC_AK_MONITOR_DEVICENAME_MAXLENGTH (16)

    /// Stream status.
    typedef enum WWISEC_AkStmStatus
    {
        WWISEC_AK_StmStatusIdle = 0,      ///< The stream is idle
        WWISEC_AK_StmStatusCompleted = 1, ///< Operation completed / Automatic stream reached end
        WWISEC_AK_StmStatusPending = 2,   ///< Operation pending / The stream is waiting for I/O
        WWISEC_AK_StmStatusCancelled = 3, ///< Operation cancelled
        WWISEC_AK_StmStatusError = 4      ///< The low-level I/O reported an error
    } WWISEC_AkStmStatus;

    /// Move method for position change.
    /// \sa
    /// - AK::IAkStdStream::SetPosition()
    /// - AK::IAkAutoStream::SetPosition()
    typedef enum WWISEC_AkMoveMethod
    {
        WWISEC_AK_MoveBegin = 0,   ///< Move offset from the start of the stream
        WWISEC_AK_MoveCurrent = 1, ///< Move offset from the current stream position
        WWISEC_AK_MoveEnd = 2      ///< Move offset from the end of the stream
    } WWISEC_AkMoveMethod;

    /// File open mode.
    typedef enum WWISEC_AkOpenMode
    {
        WWISEC_AK_OpenModeRead = 0,       ///< Read-only access
        WWISEC_AK_OpenModeWrite = 1,      ///< Write-only access (opens the file if it already exists)
        WWISEC_AK_OpenModeWriteOvrwr = 2, ///< Write-only access (deletes the file if it already exists)
        WWISEC_AK_OpenModeReadWrite = 3   ///< Read and write access
    } WWISEC_AkOpenMode;

    typedef struct WWISEC_AkFileSystemFlags
    {
        AkUInt32 uCompanyID;        ///< Company ID (Wwise uses AKCOMPANYID_AUDIOKINETIC, defined in AkTypes.h, for soundbanks and standard streaming files, and AKCOMPANYID_AUDIOKINETIC_EXTERNAL for streaming external sources).
        AkUInt32 uCodecID;          ///< File/codec type ID (defined in AkTypes.h)
        AkUInt32 uCustomParamSize;  ///< Size of the custom parameter
        void* pCustomParam;         ///< Custom parameter
        bool bIsLanguageSpecific;   ///< True when the file location depends on language
        bool bIsAutomaticStream;    ///< True when the file is opened to be used as an automatic stream. Note that you don't need to set it.
                                    ///< If you pass an AkFileSystemFlags to IAkStreamMgr CreateStd|Auto(), it will be set internally to the correct value.
        WWISEC_AkFileID uCacheID;   ///< Cache ID for caching system used by automatic streams. The user is responsible for guaranteeing unicity of IDs.
                                    ///< When set, it supersedes the file ID passed to AK::IAkStreamMgr::CreateAuto() (ID version). Caching is optional and depends on the implementation.
        AkUInt32 uNumBytesPrefetch; ///< Indicates the number of bytes from the beginning of the file that should be streamed into cache via a caching stream. This field is only relevant when opening caching streams via
                                    ///< AK::IAkStreamMgr::PinFileInCache() and AK::SoundEngine::PinEventInStreamCache().  When using AK::SoundEngine::PinEventInStreamCache(),
                                    ///< it is initialized to the prefetch size stored in the sound bank, but may be changed by the file location resolver, or set to 0 to cancel caching.
        AkUInt32 uDirectoryHash;    ///< If the implementation uses a hashed directory structure, this is the hash value that should be employed for determining the directory structure
    } WWISEC_AkFileSystemFlags;

    typedef struct WWISEC_AkStreamInfo
    {
        WWISEC_AkDeviceID deviceID; ///< Device ID
        const AkOSChar* pszName;    ///< User-defined stream name (specified through AK::IAkStdStream::SetStreamName() or AK::IAkAutoStream::SetStreamName())
        AkUInt64 uSize;             ///< Total stream/file size in bytes
        bool bIsOpen;               ///< True when the file is open (implementations may defer file opening)
    } WWISEC_AkStreamInfo;

    /// Automatic streams heuristics.
    typedef struct WWISEC_AkAutoStmHeuristics
    {
        AkReal32 fThroughput;       ///< Average throughput in bytes/ms
        AkUInt32 uLoopStart;        ///< Set to the start of loop (byte offset from the beginning of the stream) for streams that loop, 0 otherwise
        AkUInt32 uLoopEnd;          ///< Set to the end of loop (byte offset from the beginning of the stream) for streams that loop, 0 otherwise
        AkUInt8 uMinNumBuffers;     ///< Minimum number of buffers if you plan to own more than one buffer at a time, 0 or 1 otherwise
                                    ///< \remarks You should always release buffers as fast as possible, therefore this heuristic should be used only when
                                    ///< dealing with special contraints, like drivers or hardware that require more than one buffer at a time.\n
                                    ///< Also, this is only a heuristic: it does not guarantee that data will be ready when calling AK::IAkAutoStream::GetBuffer().
        WWISEC_AkPriority priority; ///< The stream priority. it should be between AK_MIN_PRIORITY and AK_MAX_PRIORITY (included).
    } WWISEC_AkAutoStmHeuristics;

    /// Automatic streams buffer settings/constraints.
    typedef struct WWISEC_AkAutoStmBufSettings
    {
        AkUInt32 uBufferSize;    ///< Hard user constraint: When non-zero, forces the I/O buffer to be of size uBufferSize
                                 ///< (overriding the device's granularity).
                                 ///< Otherwise, the size is determined by the device's granularity.
        AkUInt32 uMinBufferSize; ///< Soft user constraint: When non-zero, specifies a minimum buffer size
                                 ///< \remarks Ignored if uBufferSize is specified.
        AkUInt32 uBlockSize;     ///< Hard user constraint: When non-zero, buffer size will be a multiple of that number, and returned addresses will always be aligned on multiples of this value.
    } WWISEC_AkAutoStmBufSettings;

#pragma pack(push, 4)

    /// Device descriptor.
    typedef struct WWISEC_AkDeviceDesc
    {
        WWISEC_AkDeviceID deviceID;                                   ///< Device ID
        bool bCanWrite;                                               ///< Specifies whether or not the device is writable
        bool bCanRead;                                                ///< Specifies whether or not the device is readable
        AkUtf16 szDeviceName[WWISEC_AK_MONITOR_DEVICENAME_MAXLENGTH]; ///< Device name
        AkUInt32 uStringSize;                                         ///< Device name string's size (number of characters)
    } WWISEC_AkDeviceDesc;

    /// Device descriptor.
    typedef struct WWISEC_AkDeviceData
    {
        WWISEC_AkDeviceID deviceID;             ///< Device ID
        AkUInt32 uMemSize;                      ///< IO memory pool size
        AkUInt32 uMemUsed;                      ///< IO memory pool used
        AkUInt32 uAllocs;                       ///< Cumulative number of allocations
        AkUInt32 uFrees;                        ///< Cumulative number of deallocations
        AkUInt32 uPeakRefdMemUsed;              ///< Memory peak since monitoring started
        AkUInt32 uUnreferencedCachedBytes;      ///< IO memory that is cached but is not currently used for active streams.
        AkUInt32 uGranularity;                  ///< IO memory pool block size
        AkUInt32 uNumActiveStreams;             ///< Number of streams that have been active in the previous frame
        AkUInt32 uTotalBytesTransferred;        ///< Number of bytes transferred, including cached transfers
        AkUInt32 uLowLevelBytesTransferred;     ///< Number of bytes transferred exclusively via low-level
        AkReal32 fAvgCacheEfficiency;           ///< Total bytes from cache as a percentage of total bytes.
        AkUInt32 uNumLowLevelRequestsCompleted; ///< Number of low-level transfers that have completed in the previous monitoring frame
        AkUInt32 uNumLowLevelRequestsCancelled; ///< Number of low-level transfers that were cancelled in the previous monitoring frame
        AkUInt32 uNumLowLevelRequestsPending;   ///< Number of low-level transfers that are currently pending
        AkUInt32 uCustomParam;                  ///< Custom number queried from low-level IO.
        AkUInt32 uCachePinnedBytes;             ///< Number of bytes that can be pinned into cache.
    } WWISEC_AkDeviceData;

    /// Stream general information.
    typedef struct WWISEC_AkStreamRecord
    {
        AkUInt32 uStreamID;                                           ///< Unique stream identifier
        WWISEC_AkDeviceID deviceID;                                   ///< Device ID
        AkUtf16 szStreamName[WWISEC_AK_MONITOR_STREAMNAME_MAXLENGTH]; ///< Stream name
        AkUInt32 uStringSize;                                         ///< Stream name string's size (number of characters)
        AkUInt64 uFileSize;                                           ///< File size
        AkUInt32 uCustomParamSize;                                    ///< File descriptor's uCustomParamSize
        AkUInt32 uCustomParam;                                        ///< File descriptor's pCustomParam (on 32 bits)
        bool bIsAutoStream;                                           ///< True for auto streams
        bool bIsCachingStream;                                        ///< True for caching streams
    } WWISEC_AkStreamRecord;

    /// Stream statistics.
    typedef struct WWISEC_AkStreamData
    {
        AkUInt32 uStreamID; ///< Unique stream identifier
        // Status (replace)
        AkUInt32 uPriority;                   ///< Stream priority
        AkUInt64 uFilePosition;               ///< Current position
        AkUInt32 uTargetBufferingSize;        ///< Total stream buffer size (specific to IAkAutoStream)
        AkUInt32 uVirtualBufferingSize;       ///< Size of available data including requested data (specific to IAkAutoStream)
        AkUInt32 uBufferedSize;               ///< Size of available data (specific to IAkAutoStream)
        AkUInt32 uNumBytesTransfered;         ///< Transfered amount since last query (Accumulate/Reset)
        AkUInt32 uNumBytesTransferedLowLevel; ///< Transfered amount (from low-level IO only) since last query (Accumulate/Reset)
        AkUInt32 uMemoryReferenced;           ///< Amount of streaming memory referenced by this stream
        AkReal32 fEstimatedThroughput;        ///< Estimated throughput heuristic
        bool bActive;                         ///< True if this stream has been active (that is, was ready for I/O or had at least one pending I/O transfer, uncached or not) in the previous frame
    } WWISEC_AkStreamData;

#pragma pack(pop)

    typedef struct WWISEC_AK_IAkStreamProfile WWISEC_AK_IAkStreamProfile;

    typedef struct WWISEC_AK_IAkStreamProfile_FunctionTable
    {
        void (*Destructor)(void* instance);

        void (*GetStreamRecord)(void* instance, WWISEC_AkStreamRecord* out_streamRecord);
        void (*GetStreamData)(void* instance, WWISEC_AkStreamData* out_streamData);
        bool (*IsNew)(void* instance);
        void (*ClearNew)(void* instance);

    } WWISEC_AK_IAkStreamProfile_FunctionTable;

    WWISEC_AK_IAkStreamProfile* WWISEC_AK_IAkStreamProfile_CreateInstance(void* instance, const WWISEC_AK_IAkStreamProfile_FunctionTable* functionTable);
    void WWISEC_AK_IAkStreamProfile_DestroyInstance(WWISEC_AK_IAkStreamProfile* instance);

    void WWISEC_AK_IAkStreamProfile_GetStreamRecord(WWISEC_AK_IAkStreamProfile* instance, WWISEC_AkStreamRecord* out_streamRecord);
    void WWISEC_AK_IAkStreamProfile_GetStreamData(WWISEC_AK_IAkStreamProfile* instance, WWISEC_AkStreamData* out_streamData);
    bool WWISEC_AK_IAkStreamProfile_IsNew(WWISEC_AK_IAkStreamProfile* instance);
    void WWISEC_AK_IAkStreamProfile_ClearNew(WWISEC_AK_IAkStreamProfile* instance);

    typedef struct WWISEC_AK_IAkDeviceProfile WWISEC_AK_IAkDeviceProfile;

    typedef struct WWISEC_AK_IAkDeviceProfile_FunctionTable
    {
        void (*Destructor)(void* instance);

        void (*OnProfileStart)(void* instance);
        void (*OnProfileEnd)(void* instance);
        void (*GetDesc)(void* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
        void (*GetData)(void* instance, WWISEC_AkDeviceData* out_deviceData);
        bool (*IsNew)(void* instance);
        void (*ClearNew)(void* instance);
        AkUInt32 (*GetNumStreams)(void* instance);
        WWISEC_AK_IAkStreamProfile* (*GetStreamProfile)(void* instance, AkUInt32 in_uStreamIndex);

    } WWISEC_AK_IAkDeviceProfile_FunctionTable;

    WWISEC_AK_IAkDeviceProfile* WWISEC_AK_IAkDeviceProfile_CreateInstance(void* instance, const WWISEC_AK_IAkDeviceProfile_FunctionTable* functionTable);
    void WWISEC_AK_IAkDeviceProfile_DestroyInstance(WWISEC_AK_IAkStreamProfile* instance);

    void WWISEC_AK_IAkDeviceProfile_OnProfileStart(WWISEC_AK_IAkDeviceProfile* instance);
    void WWISEC_AK_IAkDeviceProfile_OnProfileEnd(WWISEC_AK_IAkDeviceProfile* instance);
    void WWISEC_AK_IAkDeviceProfile_GetDesc(WWISEC_AK_IAkDeviceProfile* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
    void WWISEC_AK_IAkDeviceProfile_GetData(WWISEC_AK_IAkDeviceProfile* instance, WWISEC_AkDeviceData* out_deviceData);
    bool WWISEC_AK_IAkDeviceProfile_IsNew(WWISEC_AK_IAkDeviceProfile* instance);
    void WWISEC_AK_IAkDeviceProfile_ClearNew(WWISEC_AK_IAkDeviceProfile* instance);
    AkUInt32 WWISEC_AK_IAkDeviceProfile_GetNumStreams(WWISEC_AK_IAkDeviceProfile* instance);
    WWISEC_AK_IAkStreamProfile* WWISEC_AK_IAkDeviceProfile_GetStreamProfile(WWISEC_AK_IAkDeviceProfile* instance, AkUInt32 in_uStreamIndex);

    typedef struct WWISEC_AK_IAkStreamMgrProfile WWISEC_AK_IAkStreamMgrProfile;

    typedef struct WWISEC_AK_IAkStreamMgrProfile_FunctionTable
    {
        void (*Destructor)(void* instance);

        WWISEC_AKRESULT(*StartMonitoring)
        (void* instance);
        void (*StopMonitoring)(void* instance);
        AkUInt32 (*GetNumDevices)(void* instance);
        WWISEC_AK_IAkDeviceProfile* (*GetDeviceProfile)(void* instance, AkUInt32 in_uDeviceIndex);
    } WWISEC_AK_IAkStreamMgrProfile_FunctionTable;

    WWISEC_AK_IAkStreamMgrProfile* WWISEC_AK_IAkStreamMgrProfile_CreateInstance(void* instance, const WWISEC_AK_IAkStreamMgrProfile_FunctionTable* functionTable);
    void WWISEC_AK_IAkStreamMgrProfile_DestroyInstance(WWISEC_AK_IAkStreamMgrProfile* instance);

    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgrProfile_StartMonitoring(WWISEC_AK_IAkStreamMgrProfile* instance);
    void WWISEC_AK_IAkStreamMgrProfile_StopMonitoring(WWISEC_AK_IAkStreamMgrProfile* instance);
    AkUInt32 WWISEC_AK_IAkStreamMgrProfile_GetNumDevices(WWISEC_AK_IAkStreamMgrProfile* instance);
    WWISEC_AK_IAkDeviceProfile* WWISEC_AK_IAkStreamMgrProfile_GetDeviceProfile(WWISEC_AK_IAkStreamMgrProfile* instance, AkUInt32 in_uDeviceIndex);

    typedef struct WWISEC_AK_IAkStdStream WWISEC_AK_IAkStdStream;

    typedef struct WWISEC_AK_IAkStdStream_FunctionTable
    {
        void (*Destructor)(void* instance);

        void (*Destroy)(void* instance);
        void (*GetInfo)(void* instance, WWISEC_AkStreamInfo* out_info);
        void* (*GetFileDescriptor)(void* instance);

        WWISEC_AKRESULT(*SetStreamName)
        (void* instance, const AkOSChar* in_pszStreamName);

        AkUInt32 (*GetBlockSize)(void* instance);

        WWISEC_AKRESULT(*Read)
        (void* instance, void* in_pBuffer,
         AkUInt32 in_uReqSize,
         bool in_bWait,
         WWISEC_AkPriority in_priority,
         AkReal32 in_fDeadline,
         AkUInt32* out_uSize);

        WWISEC_AKRESULT(*Write)
        (void* instance,
         void* in_pBuffer,
         AkUInt32 in_uReqSize,
         bool in_bWait,
         WWISEC_AkPriority in_priority,
         AkReal32 in_fDeadline,
         AkUInt32* out_uSize);

        AkUInt64 (*GetPosition)(void* instance, bool* out_pbEndOfStream);

        WWISEC_AKRESULT(*SetPosition)
        (void* instance, AkInt64 in_iMoveOffset, WWISEC_AkMoveMethod in_eMoveMethod, AkInt64* out_piRealOffset);

        void (*Cancel)(void* instance);
        void* (*GetData)(void* instance, AkUInt32* out_uSize);
        WWISEC_AkStmStatus (*GetStatus)(void* instance);
        WWISEC_AkStmStatus (*WaitForPendingOperation)(void* instance);
    } WWISEC_AK_IAkStdStream_FunctionTable;

    WWISEC_AK_IAkStdStream* WWISEC_AK_IAkStdStream_CreateInstance(void* instance, const WWISEC_AK_IAkStdStream_FunctionTable* functionTable);
    void WWISEC_AK_IAkStdStream_DestroyInstance(WWISEC_AK_IAkStdStream* instance);

    void WWISEC_AK_IAkStdStream_Destroy(WWISEC_AK_IAkStdStream* instance);
    void WWISEC_AK_IAkStdStream_GetInfo(WWISEC_AK_IAkStdStream* instance, WWISEC_AkStreamInfo* out_info);
    void* WWISEC_AK_IAkStdStream_GetFileDescriptor(WWISEC_AK_IAkStdStream* instance);
    WWISEC_AKRESULT WWISEC_AK_IAkStdStream_SetStreamName(WWISEC_AK_IAkStdStream* instance, const AkOSChar* in_pszStreamName);
    AkUInt32 WWISEC_AK_IAkStdStream_GetBlockSize(WWISEC_AK_IAkStdStream* instance);
    WWISEC_AKRESULT WWISEC_AK_IAkStdStream_Read(WWISEC_AK_IAkStdStream* instance, void* in_pBuffer, AkUInt32 in_uReqSize, bool in_bWait, WWISEC_AkPriority in_priority, AkReal32 in_fDeadline, AkUInt32* out_uSize);
    WWISEC_AKRESULT WWISEC_AK_IAkStdStream_Write(WWISEC_AK_IAkStdStream* instance, void* in_pBuffer, AkUInt32 in_uReqSize, bool in_bWait, WWISEC_AkPriority in_priority, AkReal32 in_fDeadline, AkUInt32* out_uSize);
    AkUInt64 WWISEC_AK_IAkStdStream_GetPosition(WWISEC_AK_IAkStdStream* instance, bool* out_pbEndOfStream);
    WWISEC_AKRESULT WWISEC_AK_IAkStdStream_SetPosition(WWISEC_AK_IAkStdStream* instance, AkInt64 in_iMoveOffset, WWISEC_AkMoveMethod in_eMoveMethod, AkInt64* out_piRealOffset);
    void WWISEC_AK_IAkStdStream_Cancel(WWISEC_AK_IAkStdStream* instance);
    void* WWISEC_AK_IAkStdStream_GetData(WWISEC_AK_IAkStdStream* instance, AkUInt32* out_uSize);
    WWISEC_AkStmStatus WWISEC_AK_IAkStdStream_GetStatus(WWISEC_AK_IAkStdStream* instance);
    WWISEC_AkStmStatus WWISEC_AK_IAkStdStream_WaitForPendingOperation(WWISEC_AK_IAkStdStream* instance);

    typedef struct WWISEC_AK_IAkAutoStream WWISEC_AK_IAkAutoStream;

    typedef struct WWISEC_AK_IAkAutoStream_FunctionTable
    {
        void (*Destructor)(void* instance);

        void (*Destroy)(void* instance);
        void (*GetInfo)(void* instance, WWISEC_AkStreamInfo* out_info);
        void* (*GetFileDescriptor)(void* instance);
        void (*GetHeuristics)(void* instance, WWISEC_AkAutoStmHeuristics* out_heuristics);

        WWISEC_AKRESULT(*SetHeuristics)
        (void* instance, const WWISEC_AkAutoStmHeuristics* in_heuristics);

        WWISEC_AKRESULT(*SetMinimalBufferSize)
        (void* instance, AkUInt32 in_uMinBufferSize);

        WWISEC_AKRESULT(*SetMinTargetBufferSize)
        (void* instance, AkUInt32 in_uMinTargetBufferSize);

        WWISEC_AKRESULT(*SetStreamName)
        (void* instance, const AkOSChar* in_pszStreamName);

        AkUInt32 (*GetBlockSize)(void* instance);

        WWISEC_AKRESULT(*QueryBufferingStatus)
        (void* instance, AkUInt32* out_uNumBytesAvailable);

        AkUInt32 (*GetNominalBuffering)(void* instance);

        WWISEC_AKRESULT(*Start)
        (void* instance);

        WWISEC_AKRESULT(*Stop)
        (void* instance);

        AkUInt64 (*GetPosition)(void* instance, bool* out_pbEndOfStream);

        WWISEC_AKRESULT(*SetPosition)
        (void* instance, AkInt64 in_iMoveOffset, WWISEC_AkMoveMethod in_eMoveMethod, AkInt64* out_piRealOffset);

        WWISEC_AKRESULT(*GetBuffer)
        (void* instance, void** out_pBuffer, AkUInt32* out_uSize, bool in_bWait);

        WWISEC_AKRESULT(*ReleaseBuffer)
        (void* instance);
    } WWISEC_AK_IAkAutoStream_FunctionTable;

    WWISEC_AK_IAkAutoStream* WWISEC_AK_IAkAutoStream_CreateInstance(void* instance, const WWISEC_AK_IAkAutoStream_FunctionTable* functionTable);
    void WWISEC_AK_IAkAutoStream_DestroyInstance(WWISEC_AK_IAkAutoStream* instance);

    void WWISEC_AK_IAkAutoStream_Destroy(WWISEC_AK_IAkAutoStream* instance);
    void WWISEC_AK_IAkAutoStream_GetInfo(WWISEC_AK_IAkAutoStream* instance, WWISEC_AkStreamInfo* out_info);
    void* WWISEC_AK_IAkAutoStream_GetFileDescriptor(WWISEC_AK_IAkAutoStream* instance);
    void WWISEC_AK_IAkAutoStream_GetHeuristics(WWISEC_AK_IAkAutoStream* instance, WWISEC_AkAutoStmHeuristics* out_heuristics);
    WWISEC_AKRESULT WWISEC_AK_IAkAutoStream_SetHeuristics(WWISEC_AK_IAkAutoStream* instance, const WWISEC_AkAutoStmHeuristics* in_heuristics);
    WWISEC_AKRESULT WWISEC_AK_IAkAutoStream_SetMinimalBufferSize(WWISEC_AK_IAkAutoStream* instance, AkUInt32 in_uMinBufferSize);
    WWISEC_AKRESULT WWISEC_AK_IAkAutoStream_SetMinTargetBufferSize(WWISEC_AK_IAkAutoStream* instance, AkUInt32 in_uMinTargetBufferSize);
    WWISEC_AKRESULT WWISEC_AK_IAkAutoStream_SetStreamName(WWISEC_AK_IAkAutoStream* instance, const AkOSChar* in_pszStreamName);
    AkUInt32 WWISEC_AK_IAkAutoStream_GetBlockSize(WWISEC_AK_IAkAutoStream* instance);
    WWISEC_AKRESULT WWISEC_AK_IAkAutoStream_QueryBufferingStatus(WWISEC_AK_IAkAutoStream* instance, AkUInt32* out_uNumBytesAvailable);
    AkUInt32 WWISEC_AK_IAkAutoStream_GetNominalBuffering(WWISEC_AK_IAkAutoStream* instance);
    WWISEC_AKRESULT WWISEC_AK_IAkAutoStream_Start(WWISEC_AK_IAkAutoStream* instance);
    WWISEC_AKRESULT WWISEC_AK_IAkAutoStream_Stop(WWISEC_AK_IAkAutoStream* instance);
    AkUInt64 WWISEC_AK_IAkAutoStream_GetPosition(WWISEC_AK_IAkAutoStream* instance, bool* out_pbEndOfStream);
    WWISEC_AKRESULT WWISEC_AK_IAkAutoStream_SetPosition(WWISEC_AK_IAkAutoStream* instance, AkInt64 in_iMoveOffset, WWISEC_AkMoveMethod in_eMoveMethod, AkInt64* out_piRealOffset);
    WWISEC_AKRESULT WWISEC_AK_IAkAutoStream_GetBuffer(WWISEC_AK_IAkAutoStream* instance, void** out_pBuffer, AkUInt32* out_uSize, bool in_bWait);
    WWISEC_AKRESULT WWISEC_AK_IAkAutoStream_ReleaseBuffer(WWISEC_AK_IAkAutoStream* instance);

    typedef struct WWISEC_AK_IAkStreamMgr WWISEC_AK_IAkStreamMgr;

    typedef struct WWISEC_AK_IAkStreamMgr_FunctionTable
    {
        void (*Destructor)(void* instance);

        void (*Destroy)(void* instance);

        WWISEC_AK_IAkStreamMgrProfile* (*GetStreamMgrProfile)(void* instance);

        WWISEC_AKRESULT(*CreateStd_String)
        (
            void* instance,
            const AkOSChar* in_pszFileName,
            WWISEC_AkFileSystemFlags* in_pFSFlags,
            WWISEC_AkOpenMode in_eOpenMode,
            WWISEC_AK_IAkStdStream** out_pStream,
            bool in_bSyncOpen);

        WWISEC_AKRESULT(*CreateStd_ID)
        (
            void* instance,
            WWISEC_AkFileID in_fileID,
            WWISEC_AkFileSystemFlags* in_pFSFlags,
            WWISEC_AkOpenMode in_eOpenMode,
            WWISEC_AK_IAkStdStream** out_pStream,
            bool in_bSyncOpen);

        WWISEC_AKRESULT(*CreateAuto_String)
        (
            void* instance,
            const AkOSChar* in_pszFileName,
            WWISEC_AkFileSystemFlags* in_pFSFlags,
            const WWISEC_AkAutoStmHeuristics* in_heuristics,
            WWISEC_AkAutoStmBufSettings* in_pBufferSettings,
            WWISEC_AK_IAkAutoStream** out_pStream,
            bool in_bSyncOpen);

        WWISEC_AKRESULT(*CreateAuto_ID)
        (
            void* instance,
            WWISEC_AkFileID in_fileID,
            WWISEC_AkFileSystemFlags* in_pFSFlags,
            const WWISEC_AkAutoStmHeuristics* in_heuristics,
            WWISEC_AkAutoStmBufSettings* in_pBufferSettings,
            WWISEC_AK_IAkAutoStream** out_pStream,
            bool in_bSyncOpen);

        WWISEC_AKRESULT(*CreateAuto_Memory)
        (
            void* instance,
            void* in_pBuffer,
            AkUInt64 in_uSize,
            const WWISEC_AkAutoStmHeuristics* in_heuristics,
            WWISEC_AK_IAkAutoStream** out_pStream);

        WWISEC_AKRESULT(*PinFileInCache)
        (
            void* instance,
            WWISEC_AkFileID in_fileID,
            WWISEC_AkFileSystemFlags* in_pFSFlags,
            WWISEC_AkPriority in_uPriority);

        WWISEC_AKRESULT(*UnpinFileInCache)
        (
            void* instance,
            WWISEC_AkFileID in_fileID,
            WWISEC_AkPriority in_uPriority);

        WWISEC_AKRESULT(*UpdateCachingPriority)
        (
            void* instance,
            WWISEC_AkFileID in_fileID,
            WWISEC_AkPriority in_uPriority,
            WWISEC_AkPriority in_uOldPriority);

        WWISEC_AKRESULT(*GetBufferStatusForPinnedFile)
        (
            void* instance,
            WWISEC_AkFileID in_fileID,
            AkReal32* out_fPercentBuffered,
            bool* out_bCacheFull);

        WWISEC_AKRESULT(*RelocateMemoryStream)
        (
            void* instance,
            WWISEC_AK_IAkAutoStream* in_pStream,
            AkUInt8* in_pNewStart);
    } WWISEC_AK_IAkStreamMgr_FunctionTable;

    WWISEC_AK_IAkStreamMgr* WWISEC_AK_IAkStreamMgr_CreateInstance(void* instance, const WWISEC_AK_IAkStreamMgr_FunctionTable* functionTable);
    void WWISEC_AK_IAkStreamMgr_DestroyInstance(WWISEC_AK_IAkStreamMgr* instance);

    void WWISEC_AK_IAkStreamMgr_Destroy(WWISEC_AK_IAkStreamMgr* instance);
    WWISEC_AK_IAkStreamMgrProfile* WWISEC_AK_IAkStreamMgr_GetStreamMgrProfile(WWISEC_AK_IAkStreamMgr* instance);
    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgr_CreateStd_String(WWISEC_AK_IAkStreamMgr* instance, const AkOSChar* in_pszFileName, WWISEC_AkFileSystemFlags* in_pFSFlags, WWISEC_AkOpenMode in_eOpenMode, WWISEC_AK_IAkStdStream** out_pStream, bool in_bSyncOpen);
    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgr_CreateStd_ID(WWISEC_AK_IAkStreamMgr* instance, WWISEC_AkFileID in_fileID, WWISEC_AkFileSystemFlags* in_pFSFlags, WWISEC_AkOpenMode in_eOpenMode, WWISEC_AK_IAkStdStream** out_pStream, bool in_bSyncOpen);
    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgr_CreateAuto_String(WWISEC_AK_IAkStreamMgr* instance, const AkOSChar* in_pszFileName, WWISEC_AkFileSystemFlags* in_pFSFlags, const WWISEC_AkAutoStmHeuristics* in_heuristics, WWISEC_AkAutoStmBufSettings* in_pBufferSettings, WWISEC_AK_IAkAutoStream** out_pStream, bool in_bSyncOpen);
    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgr_CreateAuto_ID(WWISEC_AK_IAkStreamMgr* instance, WWISEC_AkFileID in_fileID, WWISEC_AkFileSystemFlags* in_pFSFlags, const WWISEC_AkAutoStmHeuristics* in_heuristics, WWISEC_AkAutoStmBufSettings* in_pBufferSettings, WWISEC_AK_IAkAutoStream** out_pStream, bool in_bSyncOpen);
    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgr_CreateAuto_Memory(WWISEC_AK_IAkStreamMgr* instance, void* in_pBuffer, AkUInt64 in_uSize, const WWISEC_AkAutoStmHeuristics* in_heuristics, WWISEC_AK_IAkAutoStream** out_pStream);
    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgr_PinFileInCache(WWISEC_AK_IAkStreamMgr* instance, WWISEC_AkFileID in_fileID, WWISEC_AkFileSystemFlags* in_pFSFlags, WWISEC_AkPriority in_uPriority);
    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgr_UnpinFileInCache(WWISEC_AK_IAkStreamMgr* instance, WWISEC_AkFileID in_fileID, WWISEC_AkPriority in_uPriority);
    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgr_UpdateCachingPriority(WWISEC_AK_IAkStreamMgr* instance, WWISEC_AkFileID in_fileID, WWISEC_AkPriority in_uPriority, WWISEC_AkPriority in_uOldPriority);
    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgr_GetBufferStatusForPinnedFile(WWISEC_AK_IAkStreamMgr* instance, WWISEC_AkFileID in_fileID, AkReal32* out_fPercentBuffered, bool* out_bCacheFull);
    WWISEC_AKRESULT WWISEC_AK_IAkStreamMgr_RelocateMemoryStream(WWISEC_AK_IAkStreamMgr* instance, WWISEC_AK_IAkAutoStream* in_pStream, AkUInt8* in_pNewStart);

    WWISEC_AK_IAkStreamMgr* WWISEC_AK_IAkStreamMgr_Get();
    // END IAkStreamMgr

    // BEGIN AkStreamMgrModule
    typedef struct WWISEC_AkStreamMgrSettings
    {
        unsigned char dummy;
    } WWISEC_AkStreamMgrSettings;

    typedef struct WWISEC_AkDeviceSettings
    {
        void* pIOMemory;                            ///< Pointer for I/O memory allocated by user.
                                                    ///< Pass NULL if you want memory to be allocated via AK::MemoryMgr::Malign().
                                                    ///< If specified, uIOMemorySize, uIOMemoryAlignment and ePoolAttributes are ignored.
        AkUInt32 uIOMemorySize;                     ///< Size of memory for I/O (for automatic streams). It is passed directly to AK::MemoryMgr::Malign(), after having been rounded down to a multiple of uGranularity.
        AkUInt32 uIOMemoryAlignment;                ///< I/O memory alignment. It is passed directly to AK::MemoryMgr::Malign().
        AkUInt32 ePoolAttributes;                   ///< Attributes for I/O memory. Here, specify the allocation type (AkMemType_Device, and so on). It is passed directly to AK::MemoryMgr::Malign().
        AkUInt32 uGranularity;                      ///< I/O requests granularity (typical bytes/request).
        AkUInt32 uSchedulerTypeFlags;               ///< Scheduler type flags.
        WWISEC_AkThreadProperties threadProperties; ///< Scheduler thread properties.
        AkReal32 fTargetAutoStmBufferLength;        ///< Targetted automatic stream buffer length (ms). When a stream reaches that buffering, it stops being scheduled for I/O except if the scheduler is idle.
        AkUInt32 uMaxConcurrentIO;                  ///< Maximum number of transfers that can be sent simultaneously to the Low-Level I/O.
        bool bUseStreamCache;                       ///< If true, the device attempts to reuse I/O buffers that have already been streamed from disk. This is particularly useful when streaming small looping sounds. However, there is a small increase in CPU usage when allocating memory, and a slightly larger memory footprint in the StreamManager pool.
        AkUInt32 uMaxCachePinnedBytes;              ///< Maximum number of bytes that can be "pinned" using AK::SoundEngine::PinEventInStreamCache() or AK::IAkStreamMgr::PinFileInCache()
    } WWISEC_AkDeviceSettings;

#define WWISEC_AK_SCHEDULER_BLOCKING (0x01)
#define WWISEC_AK_SCHEDULER_DEFERRED_LINED_UP (0x02)

    typedef struct WWISEC_AkFileDesc
    {
        AkInt64 iFileSize;          ///< File size in bytes
        AkUInt64 uSector;           ///< Start sector (the sector size is specified by the low-level I/O)
                                    ///< \sa
                                    ///< - AK::StreamMgr::IAkFileLocationResolver::Open()
                                    ///< - AK::StreamMgr::IAkLowLevelIOHook::GetBlockSize()
        AkUInt32 uCustomParamSize;  ///< Size of the custom parameter
        void* pCustomParam;         ///< Custom parameter
        AkFileHandle hFile;         ///< File handle/identifier
        WWISEC_AkDeviceID deviceID; ///< Device ID, obtained from CreateDevice() \sa AK::IAkStreamMgr::CreateDevice()
        void* pPackage;             ///< If this file is in a File Package, this will be the
    } WWISEC_AkFileDesc;

    typedef struct WWISEC_AkIOTransferInfo
    {
        AkUInt64 uFilePosition;  ///< File offset where transfer should begin.
        AkUInt32 uBufferSize;    ///< Size of the buffer in which the I/O hook can write to.
        AkUInt32 uRequestedSize; ///< Exact number of requested bytes for this transfer. Always equal to or smaller than uBufferSize.
    } WWISEC_AkIOTransferInfo;

    typedef struct WWISEC_AkAsyncIOTransferInfo WWISEC_AkAsyncIOTransferInfo;

    AK_CALLBACK(void, WWISEC_AkIOCallback)
    (
        WWISEC_AkAsyncIOTransferInfo* in_pTransferInfo, ///< Pointer to the AkAsyncIOTransferInfo structure that was passed to corresponding Read() or Write() call.
        WWISEC_AKRESULT in_eResult                      ///< Result of transfer: AK_Success or AK_Fail (streams waiting for this transfer become invalid).
    );

    AK_CALLBACK(void, WWISEC_AkBatchIOCallback)
    (
        AkUInt32 in_uNumTransfers,                        ///< Number of transfers to process
        WWISEC_AkAsyncIOTransferInfo** in_ppTransferInfo, ///< List of pointers to AkAsyncIOTransferInfo structures that were previously passed in to BatchRead() or BatchWrite()
        WWISEC_AKRESULT* in_peResult                      ///< Array of results of each transfer: AK_Success or AK_Fail (streams waiting for this transfer become invalid).
    );

    typedef struct WWISEC_AkAsyncIOTransferInfo
    {
        WWISEC_AkIOTransferInfo base;
        void* pBuffer;                 ///< Buffer for data transfer.
        WWISEC_AkIOCallback pCallback; ///< Callback function used to notify the high-level device when the transfer is complete.
        void* pCookie;                 ///< Reserved. The I/O device uses this cookie to retrieve the owner of the transfer.
        void* pUserData;               ///< Custom user data.
    } WWISEC_AkAsyncIOTransferInfo;

    typedef struct WWISEC_AkIoHeuristics
    {
        AkReal32 fDeadline;         ///< Operation deadline (ms).
        WWISEC_AkPriority priority; ///< Operation priority (at the time it was scheduled and sent to the Low-Level I/O). Range is [AK_MIN_PRIORITY,AK_MAX_PRIORITY], inclusively.
    } WWISEC_AkIoHeuristics;

    AK_CALLBACK(void, WWISEC_AK_StreamMgr_AkLanguageChangeHandler)
    (
        const AkOSChar* const in_pLanguageName, ///< New language name.
        void* in_pCookie                        ///< Cookie that was passed to AddLanguageChangeObserver().
    );

    typedef struct WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem
    {
        WWISEC_AkFileDesc* pFileDesc;
        WWISEC_AkIoHeuristics ioHeuristics;
        WWISEC_AkAsyncIOTransferInfo* pTransferInfo;
    } WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem;

    typedef struct WWISEC_AK_StreamMgr_IAkLowLevelIOHook WWISEC_AK_StreamMgr_IAkLowLevelIOHook;

    typedef struct WWISEC_AK_StreamMgr_IAkLowLevelIOHook_FunctionTable
    {
        void (*Destructor)(void* instance);

        WWISEC_AKRESULT(*Close)
        (void* instance, WWISEC_AkFileDesc* in_fileDesc);

        AkUInt32 (*GetBlockSize)(void* instance, WWISEC_AkFileDesc* in_fileDesc);
        void (*GetDeviceDesc)(void* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
        AkUInt32 (*GetDeviceData)(void* instance);
    } WWISEC_AK_StreamMgr_IAkLowLevelIOHook_FunctionTable;
    WWISEC_AK_StreamMgr_IAkLowLevelIOHook* WWISEC_AK_StreamMgr_IAkLowLevelIOHook_CreateInstance(void* instance, const WWISEC_AK_StreamMgr_IAkLowLevelIOHook_FunctionTable* functionTable);
    void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_DestroyInstance(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance);

    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Close(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, WWISEC_AkFileDesc* in_fileDesc);
    AkUInt32 WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetBlockSize(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, WWISEC_AkFileDesc* in_fileDesc);
    void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetDeviceDesc(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
    AkUInt32 WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetDeviceData(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance);

    typedef struct WWISEC_AK_StreamMgr_IAkIOHookBlocking WWISEC_AK_StreamMgr_IAkIOHookBlocking;

    typedef struct WWISEC_AK_StreamMgr_IAkIOHookBlocking_FunctionTable
    {
        void (*Destructor)(void* instance);

        WWISEC_AKRESULT(*Close)
        (void* instance, WWISEC_AkFileDesc* in_fileDesc);

        AkUInt32 (*GetBlockSize)(void* instance, WWISEC_AkFileDesc* in_fileDesc);
        void (*GetDeviceDesc)(void* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
        AkUInt32 (*GetDeviceData)(void* instance);

        WWISEC_AKRESULT(*Read)
        (void* instance, WWISEC_AkFileDesc* in_fileDesc, const WWISEC_AkIoHeuristics* in_heuristics, void* out_pBuffer, WWISEC_AkIOTransferInfo* in_transferInfo);

        WWISEC_AKRESULT(*Write)
        (void* instance, WWISEC_AkFileDesc* in_fileDesc, const WWISEC_AkIoHeuristics* in_heuristics, void* in_pData, WWISEC_AkIOTransferInfo* io_transferInfo);
    } WWISEC_AK_StreamMgr_IAkIOHookBlocking_FunctionTable;
    WWISEC_AK_StreamMgr_IAkIOHookBlocking* WWISEC_AK_StreamMgr_IAkIOHookBlocking_CreateInstance(void* instance, const WWISEC_AK_StreamMgr_IAkIOHookBlocking_FunctionTable* functionTable);
    void WWISEC_AK_StreamMgr_IAkIOHookBlocking_DestroyInstance(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance);

    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookBlocking_Close(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance, WWISEC_AkFileDesc* in_fileDesc);
    AkUInt32 WWISEC_AK_StreamMgr_IAkIOHookBlocking_GetBlockSize(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance, WWISEC_AkFileDesc* in_fileDesc);
    void WWISEC_AK_StreamMgr_IAkIOHookBlocking_GetDeviceDesc(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
    AkUInt32 WWISEC_AK_StreamMgr_IAkIOHookBlocking_GetDeviceData(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookBlocking_Read(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance, WWISEC_AkFileDesc* in_fileDesc, const WWISEC_AkIoHeuristics* in_heuristics, void* out_pBuffer, WWISEC_AkIOTransferInfo* in_transferInfo);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookBlocking_Write(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance, WWISEC_AkFileDesc* in_fileDesc, const WWISEC_AkIoHeuristics* in_heuristics, void* in_pData, WWISEC_AkIOTransferInfo* io_transferInfo);

    typedef struct WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch;

    typedef struct WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_FunctionTable
    {
        void (*Destructor)(void* instance);

        WWISEC_AKRESULT(*Close)
        (void* instance, WWISEC_AkFileDesc* in_fileDesc);

        AkUInt32 (*GetBlockSize)(void* instance, WWISEC_AkFileDesc* in_fileDesc);
        void (*GetDeviceDesc)(void* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
        AkUInt32 (*GetDeviceData)(void* instance);

        WWISEC_AKRESULT(*BatchRead)
        (void* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, WWISEC_AkBatchIOCallback in_pBatchIoCallback, WWISEC_AKRESULT* io_pDispatchResults);

        WWISEC_AKRESULT(*BatchWrite)
        (void* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, WWISEC_AkBatchIOCallback in_pBatchIoCallback, WWISEC_AKRESULT* io_pDispatchResults);

        void (*BatchCancel)(void* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, bool** io_ppbCancelAllTransfersForThisFile);
    } WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_FunctionTable;
    WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch* WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_CreateInstance(void* instance, const WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_FunctionTable* functionTable);
    void WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_DestroyInstance(WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch* instance);

    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_Close(WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch* instance, WWISEC_AkFileDesc* in_fileDesc);
    AkUInt32 WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_GetBlockSize(WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch* instance, WWISEC_AkFileDesc* in_fileDesc);
    void WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_GetDeviceDesc(WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
    AkUInt32 WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_GetDeviceData(WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch* instance);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchRead(WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, WWISEC_AkBatchIOCallback in_pBatchIoCallback, WWISEC_AKRESULT* io_pDispatchResults);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchWrite(WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, WWISEC_AkBatchIOCallback in_pBatchIoCallback, WWISEC_AKRESULT* io_pDispatchResults);
    void WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchCancel(WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, bool** io_ppbCancelAllTransfersForThisFile);

    typedef struct WWISEC_AK_StreamMgr_IAkIOHookDeferred WWISEC_AK_StreamMgr_IAkIOHookDeferred;

    typedef struct WWISEC_AK_StreamMgr_IAkIOHookDeferred_FunctionTable
    {
        void (*Destructor)(void* instance);

        WWISEC_AKRESULT(*Close)
        (void* instance, WWISEC_AkFileDesc* in_fileDesc);

        AkUInt32 (*GetBlockSize)(void* instance, WWISEC_AkFileDesc* in_fileDesc);
        void (*GetDeviceDesc)(void* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
        AkUInt32 (*GetDeviceData)(void* instance);

        WWISEC_AKRESULT(*BatchRead)
        (void* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, WWISEC_AkBatchIOCallback in_pBatchIoCallback, WWISEC_AKRESULT* io_pDispatchResults);

        WWISEC_AKRESULT(*BatchWrite)
        (void* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, WWISEC_AkBatchIOCallback in_pBatchIoCallback, WWISEC_AKRESULT* io_pDispatchResults);

        void (*BatchCancel)(void* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, bool** io_ppbCancelAllTransfersForThisFile);

        WWISEC_AKRESULT(*Read)
        (void* instance, WWISEC_AkFileDesc* in_fileDesc, const WWISEC_AkIoHeuristics* in_heuristics, WWISEC_AkAsyncIOTransferInfo* io_transferInfo);

        WWISEC_AKRESULT(*Write)
        (void* instance, WWISEC_AkFileDesc* in_fileDesc, const WWISEC_AkIoHeuristics* in_heuristics, WWISEC_AkAsyncIOTransferInfo* io_transferInfo);

        void (*Cancel)(void* instance, WWISEC_AkFileDesc* in_fileDesc, WWISEC_AkAsyncIOTransferInfo* io_transferInfo, bool* io_bCancelAllTransfersForThisFile);
    } WWISEC_AK_StreamMgr_IAkIOHookDeferred_FunctionTable;
    WWISEC_AK_StreamMgr_IAkIOHookDeferred* WWISEC_AK_StreamMgr_IAkIOHookDeferred_CreateInstance(void* instance, const WWISEC_AK_StreamMgr_IAkIOHookDeferred_FunctionTable* functionTable);
    void WWISEC_AK_StreamMgr_IAkIOHookDeferred_DestroyInstance(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance);

    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookDeferred_Close(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance, WWISEC_AkFileDesc* in_fileDesc);
    AkUInt32 WWISEC_AK_StreamMgr_IAkIOHookDeferred_GetBlockSize(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance, WWISEC_AkFileDesc* in_fileDesc);
    void WWISEC_AK_StreamMgr_IAkIOHookDeferred_GetDeviceDesc(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
    AkUInt32 WWISEC_AK_StreamMgr_IAkIOHookDeferred_GetDeviceData(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookDeferred_BatchRead(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, WWISEC_AkBatchIOCallback in_pBatchIoCallback, WWISEC_AKRESULT* io_pDispatchResults);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookDeferred_BatchWrite(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, WWISEC_AkBatchIOCallback in_pBatchIoCallback, WWISEC_AKRESULT* io_pDispatchResults);
    void WWISEC_AK_StreamMgr_IAkIOHookDeferred_BatchCancel(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem* in_pTransferItems, bool** io_ppbCancelAllTransfersForThisFile);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookDeferred_Read(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance, WWISEC_AkFileDesc* in_fileDesc, const WWISEC_AkIoHeuristics* in_heuristics, WWISEC_AkAsyncIOTransferInfo* io_transferInfo);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookDeferred_Write(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance, WWISEC_AkFileDesc* in_fileDesc, const WWISEC_AkIoHeuristics* in_heuristics, WWISEC_AkAsyncIOTransferInfo* io_transferInfo);
    void WWISEC_AK_StreamMgr_IAkIOHookDeferred_Cancel(WWISEC_AK_StreamMgr_IAkIOHookDeferred* instance, WWISEC_AkFileDesc* in_fileDesc, WWISEC_AkAsyncIOTransferInfo* io_transferInfo, bool* io_bCancelAllTransfersForThisFile);

    typedef struct WWISEC_AK_StreamMgr_IAkFileLocationResolver WWISEC_AK_StreamMgr_IAkFileLocationResolver;

    typedef struct WWISEC_AK_StreamMgr_IAkFileLocationResolver_FunctionTable
    {
        void (*Destructor)(void* instance);

        WWISEC_AKRESULT(*Open_String)
        (void* instance, const AkOSChar* in_pszFileName, WWISEC_AkOpenMode in_eOpenMode, WWISEC_AkFileSystemFlags* in_pFlags, bool* io_bSyncOpen, WWISEC_AkFileDesc* io_fileDesc);

        WWISEC_AKRESULT(*Open_ID)
        (void* instance, WWISEC_AkFileID in_fileID, WWISEC_AkOpenMode in_eOpenMode, WWISEC_AkFileSystemFlags* in_pFlags, bool* io_bSyncOpen, WWISEC_AkFileDesc* io_fileDesc);

        WWISEC_AKRESULT(*OutputSearchedPaths_String)
        (void* instance, const WWISEC_AKRESULT* in_result, const AkOSChar* in_pszFileName, WWISEC_AkFileSystemFlags* in_pFlags, WWISEC_AkOpenMode in_eOpenMode, AkOSChar* out_searchedPath, AkInt32 in_pathSize);

        WWISEC_AKRESULT(*OutputSearchedPaths_ID)
        (void* instance, const WWISEC_AKRESULT* in_result, const WWISEC_AkFileID in_fileID, WWISEC_AkFileSystemFlags* in_pFlags, WWISEC_AkOpenMode in_eOpenMode, AkOSChar* out_searchedPath, AkInt32 in_pathSize);

    } WWISEC_AK_StreamMgr_IAkFileLocationResolver_FunctionTable;
    WWISEC_AK_StreamMgr_IAkFileLocationResolver* WWISEC_AK_StreamMgr_IAkFileLocationResolver_CreateInstance(void* instance, const WWISEC_AK_StreamMgr_IAkFileLocationResolver_FunctionTable* functionTable);
    void WWISEC_AK_StreamMgr_IAkFileLocationResolver_DestroyInstance(WWISEC_AK_StreamMgr_IAkFileLocationResolver* instance);

    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkFileLocationResolver_Open_String(WWISEC_AK_StreamMgr_IAkFileLocationResolver* instance, const AkOSChar* in_pszFileName, WWISEC_AkOpenMode in_eOpenMode, WWISEC_AkFileSystemFlags* in_pFlags, bool* io_bSyncOpen, WWISEC_AkFileDesc* io_fileDesc);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkFileLocationResolver_Open_ID(WWISEC_AK_StreamMgr_IAkFileLocationResolver* instance, WWISEC_AkFileID in_fileID, WWISEC_AkOpenMode in_eOpenMode, WWISEC_AkFileSystemFlags* in_pFlags, bool* io_bSyncOpen, WWISEC_AkFileDesc* io_fileDesc);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkFileLocationResolver_OutputSearchedPaths_String(WWISEC_AK_StreamMgr_IAkFileLocationResolver* instance, const WWISEC_AKRESULT* in_result, const AkOSChar* in_pszFileName, WWISEC_AkFileSystemFlags* in_pFlags, WWISEC_AkOpenMode in_eOpenMode, AkOSChar* out_searchedPath, AkInt32 in_pathSize);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkFileLocationResolver_OutputSearchedPaths_ID(WWISEC_AK_StreamMgr_IAkFileLocationResolver* instance, const WWISEC_AKRESULT* in_result, const WWISEC_AkFileID in_fileID, WWISEC_AkFileSystemFlags* in_pFlags, WWISEC_AkOpenMode in_eOpenMode, AkOSChar* out_searchedPath, AkInt32 in_pathSize);

    void* WWISEC_AK_StreamMgr_Create(WWISEC_AkStreamMgrSettings* in_settings);
    void WWISEC_AK_StreamMgr_GetDefaultSettings(WWISEC_AkStreamMgrSettings* out_settings);
    void* WWISEC_AK_StreamMgr_GetFileLocationResolver();
    void WWISEC_AK_StreamMgr_SetFileLocationResolver(void* in_pFileLocationResolver);
    WWISEC_AkDeviceID WWISEC_AK_StreamMgr_CreateDevice(const WWISEC_AkDeviceSettings* in_settings, void* in_pLowLevelHook);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_DestroyDevice(WWISEC_AkDeviceID in_deviceID);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_PerformIO();
    void WWISEC_AK_StreamMgr_GetDefaultDeviceSettings(WWISEC_AkDeviceSettings* out_settings);
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_SetCurrentLanguage(const AkOSChar* in_pszLanguageName);
    const AkOSChar* WWISEC_AK_StreamMgr_GetCurrentLanguage();
    WWISEC_AKRESULT WWISEC_AK_StreamMgr_AddLanguageChangeObserver(WWISEC_AK_StreamMgr_AkLanguageChangeHandler in_handler, void* in_pCookie);
    void WWISEC_AK_StreamMgr_RemoveLanguageChangeObserver(void* in_pCookie);
    void WWISEC_AK_StreamMgr_FlushAllCaches();
    // END AkStreamMgrModule

    // BEGIN AkMusicEngine
    typedef struct WWISEC_AkMusicSettings
    {
        AkReal32 fStreamingLookAheadRatio; ///< Multiplication factor for all streaming look-ahead heuristic values.
    } WWISEC_AkMusicSettings;

    WWISEC_AKRESULT WWISEC_AK_MusicEngine_Init(WWISEC_AkMusicSettings* in_pSettings);
    void WWISEC_AK_MusicEngine_GetDefaultInitSettings(WWISEC_AkMusicSettings* out_settings);
    void WWISEC_AK_MusicEngine_Term();
    WWISEC_AKRESULT WWISEC_AK_MusicEngine_GetPlayingSegmentInfo(WWISEC_AkPlayingID in_PlayingID, WWISEC_AkSegmentInfo* out_segmentInfo, bool in_bExtrapolate);
// END AkMusicEngine

// BEGIN AkCommunication
#if defined(WWISEC_USE_COMMUNICATION)
#define WWISEC_AK_COMM_SETTINGS_MAX_STRING_SIZE 64
#define WWISEC_AK_COMM_SETTINGS_MAX_URL_SIZE 128

    typedef struct WWISEC_AkCommSettings_Ports
    {
        AkUInt16 uDiscoveryBroadcast;
        AkUInt16 uCommand;
    } WWISEC_AkCommSettings_Ports;

    typedef enum WWISEC_AkCommSettings_AkCommSystem
    {
        AkCommSystem_Socket, /// The recommended default communication system
        AkCommSystem_HTCS    /// HTCS when available only, will default to AkCommSystem_Socket if the HTCS system is not available.
    } WWISEC_AkCommSettings_AkCommSystem;

    typedef struct WWISEC_AkCommSettings
    {
        WWISEC_AkCommSettings_Ports ports;
        WWISEC_AkCommSettings_AkCommSystem commSystem;
        bool bInitSystemLib;
        char szAppNetworkName[WWISEC_AK_COMM_SETTINGS_MAX_STRING_SIZE];
        char szCommProxyServerUrl[WWISEC_AK_COMM_SETTINGS_MAX_URL_SIZE];
    } WWISEC_AkCommSettings;

    WWISEC_AKRESULT WWISEC_AK_Comm_Init(const WWISEC_AkCommSettings* in_settings);
    void WWISEC_AK_Comm_GetDefaultInitSettings(WWISEC_AkCommSettings* out_settings);
    void WWISEC_AK_Comm_Term();
    WWISEC_AKRESULT WWISEC_AK_Comm_Reset();
    const WWISEC_AkCommSettings* WWISEC_AK_Comm_GetCurrentSettings();
#endif
    // END AkCommunication

    // BEGIN AkDynamicDialogue
    AK_CALLBACK(bool, WWISEC_AkCandidateCallbackFunc)
    (
        WWISEC_AkUniqueID in_idEvent,
        WWISEC_AkUniqueID in_idCandidate,
        void* in_cookie);

    WWISEC_AkUniqueID WWISEC_AK_SoundEngine_DynamicDialogue_ResolveDialogueEvent_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkArgumentValueID* in_aArgumentValues, AkUInt32 in_uNumArguments, WWISEC_AkPlayingID in_idSequence, WWISEC_AkCandidateCallbackFunc in_candidateCallbackFunc, void* in_pCookie);

    WWISEC_AkUniqueID WWISEC_AK_SoundEngine_DynamicDialogue_ResolveDialogueEvent_String(const char* in_pszEventName, const char** in_aArgumentValueNames, AkUInt32 in_uNumArguments, WWISEC_AkPlayingID in_idSequence, WWISEC_AkCandidateCallbackFunc in_candidateCallbackFunc, void* in_pCookie);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicDialogue_GetDialogueEventCustomPropertyValue(WWISEC_AkUniqueID in_eventID, AkUInt32 in_uPropID, AkInt32* out_iValue);
    // END AkDynamicDialogue

    // BEGIN AkDynamicSequence
    typedef struct WWISEC_AkExternalSourceArray WWISEC_AkExternalSourceArray;

    typedef struct WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem
    {
        WWISEC_AkUniqueID audioNodeID; ///< Unique ID of Audio Node
        WWISEC_AkTimeMs msDelay;       ///< Delay before playing this item, in milliseconds
        void* pCustomInfo;             ///< Optional user data
        WWISEC_AkExternalSourceArray* pExternalSrcs;
    } WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem;

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem_SetExternalSources(WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* self, AkUInt32 in_nExternalSrc, WWISEC_AkExternalSourceInfo* in_pExternalSrc);

    typedef struct WWISEC_AK_SoundEngine_DynamicSequence_Playlist WWISEC_AK_SoundEngine_DynamicSequence_Playlist;

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Enqueue(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, WWISEC_AkUniqueID in_audioNodeID, WWISEC_AkTimeMs in_msDelay, void* in_pCustomInfo, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources);
    void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Erase(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uIndex);
    void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_EraseSwap(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uIndex);
    bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_IsGrowingAllowed(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Reserve(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_ulReserve);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_ReserveExtra(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_ulReserve);
    AkUInt32 WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Reserved(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Term(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    AkUInt32 WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Length(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Data(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_IsEmpty(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Exists(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item);
    WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_AddLast(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_AddLastItem(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item);
    WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Last(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveLast(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Remove(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveSwap(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item);
    void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveAll(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_At(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uiIndex);
    WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Insert(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uIndex);
    bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_GrowArray(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_GrowArraySize(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_uGrowBy);
    bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Resize(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_uiSize);
    void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Transfer(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, WWISEC_AK_SoundEngine_DynamicSequence_Playlist* in_rSource);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Copy(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_Playlist* in_rSource);

    typedef enum WWISEC_AK_SoundEngine_DynamicSequence_DynamicSequenceType
    {
        WWISEC_AK_SoundEngine_DynamicSequence_DynamicSequenceType_SampleAccurate,  ///< Sample accurate mode
        WWISEC_AK_SoundEngine_DynamicSequence_DynamicSequenceType_NormalTransition ///< Normal transition mode, allows the entire playlist to be edited at all times.
    } WWISEC_AK_SoundEngine_DynamicSequence_DynamicSequenceType;

    WWISEC_AkPlayingID WWISEC_AK_SoundEngine_DynamicSequence_Open(WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, WWISEC_AK_SoundEngine_DynamicSequence_DynamicSequenceType in_eDynamicSequenceType);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Close(WWISEC_AkPlayingID in_playingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Play(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Pause(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Resume(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Stop(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Break(WWISEC_AkPlayingID in_playingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Seek_Time(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_iPosition, bool in_bSeekToNearestMarker);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Seek_Percent(WWISEC_AkPlayingID in_playingID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_GetPauseTimes(WWISEC_AkPlayingID in_playingID, AkUInt32* out_uTime, AkUInt32* out_uDuration);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_GetPlayingItem(WWISEC_AkPlayingID in_playingID, WWISEC_AkUniqueID* out_audioNodeID, void** out_pCustomInfo);

    WWISEC_AK_SoundEngine_DynamicSequence_Playlist* WWISEC_AK_SoundEngine_DynamicSequence_LockPlaylist(WWISEC_AkPlayingID in_playingID);

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_UnlockPlaylist(WWISEC_AkPlayingID in_playingID);
    // END AkDynamicSequence

    // BEGIN AkQueryParameters

    /// Positioning information obtained from an object
    typedef struct WWISEC_AkPositioningInfo
    {
        AkReal32 fCenterPct;                                 ///< Center % [0..1]
        WWISEC_AkSpeakerPanningType pannerType;              ///< Speaker panning type: type of panning logic when object is not 3D spatialized.
        WWISEC_Ak3DPositionType e3dPositioningType;          ///< 3D position type: defines what acts as the emitter position for computing spatialization against the listener.
        bool bHoldEmitterPosAndOrient;                       ///< Hold emitter position and orientation values when starting playback.
        WWISEC_Ak3DSpatializationMode e3DSpatializationMode; ///< Spatialization mode
        bool bEnableAttenuation;                             ///< Attenuation parameter set is active.

        bool bUseConeAttenuation;     ///< Use the cone attenuation
        AkReal32 fInnerAngle;         ///< Inner angle
        AkReal32 fOuterAngle;         ///< Outer angle
        AkReal32 fConeMaxAttenuation; ///< Cone max attenuation
        WWISEC_AkLPFType LPFCone;     ///< Cone low pass filter value
        WWISEC_AkLPFType HPFCone;     ///< Cone low pass filter value

        AkReal32 fMaxDistance;              ///< Maximum distance
        AkReal32 fVolDryAtMaxDist;          ///< Volume dry at maximum distance
        AkReal32 fVolAuxGameDefAtMaxDist;   ///< Volume wet at maximum distance (if any) (based on the Game defined distance attenuation)
        AkReal32 fVolAuxUserDefAtMaxDist;   ///< Volume wet at maximum distance (if any) (based on the User defined distance attenuation)
        WWISEC_AkLPFType LPFValueAtMaxDist; ///< Low pass filter value at max distance (if any)
        WWISEC_AkLPFType HPFValueAtMaxDist; ///< High pass filter value at max distance (if any)
    } WWISEC_AkPositioningInfo;

    /// Object information structure for QueryAudioObjectsIDs
    typedef struct WWISEC_AkObjectInfo
    {
        WWISEC_AkUniqueID objID;    ///< Object ID
        WWISEC_AkUniqueID parentID; ///< Object ID of the parent
        AkInt32 iDepth;             ///< Depth in tree
    } WWISEC_AkObjectInfo;

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetPosition(WWISEC_AkGameObjectID in_GameObjectID, WWISEC_AkSoundPosition* out_rPosition);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetListeners(WWISEC_AkGameObjectID in_GameObjectID, WWISEC_AkGameObjectID* out_ListenerObjectIDs, AkUInt32* oi_uNumListeners);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetListenerPosition(WWISEC_AkGameObjectID in_uListenerID, WWISEC_AkListenerPosition* out_rPosition);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetListenerSpatialization(WWISEC_AkGameObjectID in_uListenerID, bool* out_rbSpatialized, WWISEC_AK_SpeakerVolumes_VectorPtr* out_pVolumeOffsets, WWISEC_AkChannelConfig* out_channelConfig);

    typedef enum WWISEC_AK_SoundEngine_Query_RTPCValue_type
    {
        WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_Default,    ///< The value is the Default RTPC.
        WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_Global,     ///< The value is the Global RTPC.
        WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_GameObject, ///< The value is the game object specific RTPC.
        WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_PlayingID,  ///< The value is the playing ID specific RTPC.
        WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_Unavailable ///< The value is not available for the RTPC specified.
    } WWISEC_AK_SoundEngine_Query_RTPCValue_type;

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetRTPCValue_ID(WWISEC_AkRtpcID in_rtpcID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkPlayingID in_playingID, WWISEC_AkRtpcValue* out_rValue, WWISEC_AK_SoundEngine_Query_RTPCValue_type* io_rValueType);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetRTPCValue_String(const char* in_pszRtpcName, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkPlayingID in_playingID, WWISEC_AkRtpcValue* out_rValue, WWISEC_AK_SoundEngine_Query_RTPCValue_type* io_rValueType);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetSwitch_ID(WWISEC_AkSwitchGroupID in_switchGroup, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkSwitchStateID* out_rSwitchState);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetSwitch_String(const char* in_pstrSwitchGroupName, WWISEC_AkGameObjectID in_GameObj, WWISEC_AkSwitchStateID* out_rSwitchState);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetState_ID(WWISEC_AkStateGroupID in_stateGroup, WWISEC_AkStateID* out_rState);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetState_String(const char* in_pstrStateGroupName, WWISEC_AkStateID* out_rState);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetGameObjectAuxSendValues(WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkAuxSendValue* out_paAuxSendValues, AkUInt32* io_ruNumSendValues);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetGameObjectDryLevelValue(WWISEC_AkGameObjectID in_EmitterID, WWISEC_AkGameObjectID in_ListenerID, AkReal32* out_rfControlValue);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetObjectObstructionAndOcclusion(WWISEC_AkGameObjectID in_EmitterID, WWISEC_AkGameObjectID in_ListenerID, AkReal32* out_rfObstructionLevel, AkReal32* out_rfOcclusionLevel);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_QueryAudioObjectIDs_ID(WWISEC_AkUniqueID in_eventID, AkUInt32* io_ruNumItems, WWISEC_AkObjectInfo* out_aObjectInfos);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_QueryAudioObjectIDs_String(const char* in_pszEventName, AkUInt32* io_ruNumItems, WWISEC_AkObjectInfo* out_aObjectInfos);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetPositioningInfo(WWISEC_AkUniqueID in_ObjectID, WWISEC_AkPositioningInfo* out_rPositioningInfo);

    typedef struct WWISEC_AK_SoundEngine_Query_AkGameObjectsList
    {
        WWISEC_AkGameObjectID* items;
        AkUInt32 length;
        AkUInt32 reserved;
    } WWISEC_AK_SoundEngine_Query_AkGameObjectsList;

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetActiveGameObjects(WWISEC_AK_SoundEngine_Query_AkGameObjectsList* io_GameObjectList);
    bool WWISEC_AK_SoundEngine_Query_GetIsGameObjectActive(WWISEC_AkGameObjectID in_GameObjId);

    typedef struct WWISEC_AK_SoundEngine_Query_GameObjDst
    {
        WWISEC_AkGameObjectID m_gameObjID; ///< Game object ID
        AkReal32 m_dst;                    ///< MaxDistance
    } WWISEC_AK_SoundEngine_Query_GameObjDst;

    typedef struct WWISEC_AK_SoundEngine_Query_AkRadiusList
    {
        WWISEC_AK_SoundEngine_Query_GameObjDst* items;
        AkUInt32 length;
        AkUInt32 reserved;
    } WWISEC_AK_SoundEngine_Query_AkRadiusList;

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetMaxRadius_List(WWISEC_AK_SoundEngine_Query_AkRadiusList* io_RadiusList);
    AkReal32 WWISEC_AK_SoundEngine_Query_GetMaxRadius_Single(WWISEC_AkGameObjectID in_GameObjId);
    WWISEC_AkUniqueID WWISEC_AK_SoundEngine_Query_GetEventIDFromPlayingID(WWISEC_AkPlayingID in_playingID);
    WWISEC_AkGameObjectID WWISEC_AK_SoundEngine_Query_GetGameObjectFromPlayingID(WWISEC_AkPlayingID in_playingID);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetPlayingIDsFromGameObject(WWISEC_AkGameObjectID in_GameObjId, AkUInt32* io_ruNumIDs, WWISEC_AkPlayingID* out_aPlayingIDs);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetCustomPropertyValue_Int(WWISEC_AkUniqueID in_ObjectID, AkUInt32 in_uPropID, AkInt32* out_iValue);
    WWISEC_AKRESULT WWISEC_AK_SoundEngine_Query_GetCustomPropertyValue_Float(WWISEC_AkUniqueID in_ObjectID, AkUInt32 in_uPropID, AkReal32* out_fValue);
// END AkQueryParameters

// BEGIN IO Hooks
#if defined(WWISEC_INCLUDE_DEFAULT_IO_HOOK_BLOCKING)
    size_t WWISEC_AK_CAkDefaultIOHookBlocking_Sizeof();
    void* WWISEC_AK_CAkDefaultIOHookBlocking_Create(char* in_ioHookBuffer);
    void WWISEC_AK_CAkDefaultIOHookBlocking_Destroy(void* in_ioHook);
    WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookBlocking_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen);
    void WWISEC_AK_CAkDefaultIOHookBlocking_Term(void* in_ioHook);
    WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookBlocking_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookBlocking_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    void WWISEC_CAkDefaultIOHookBlocking_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering);
#endif

#if defined(WWISEC_INCLUDE_DEFAULT_IO_HOOK_DEFERRED)
    size_t WWISEC_AK_CAkDefaultIOHookDeferred_Sizeof();
    void* WWISEC_AK_CAkDefaultIOHookDeferred_Create(char* in_ioHookBuffer);
    void WWISEC_AK_CAkDefaultIOHookDeferred_Destroy(void* in_ioHook);
    WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen);
    void WWISEC_AK_CAkDefaultIOHookDeferred_Term(void* in_ioHook);
    WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    void WWISEC_CAkDefaultIOHookDeferred_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering);
#endif

#if defined(WWISEC_INCLUDE_FILE_PACKAGE_IO_BLOCKING)
    size_t WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Sizeof();
    void* WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Create(char* in_ioHookBuffer);
    void WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Destroy(void* in_ioHook);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen);
    void WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Term(void* in_ioHook);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    void WWISEC_CAkFilePackageLowLevelIOBlocking_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_LoadFilePackage(void* in_ioHook, const AkOSChar* in_pszFilePacakgeName, AkUInt32* out_uPackageID);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_UnloadFilePackage(void* in_ioHook, AkUInt32 in_uPackageID);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_UnloadAllFilePackages(void* in_ioHook);
    void WWISEC_AK_CAkFilePackageLowLevelIOBlocking_SetPackageFallbackBehavior(void* in_ioHook, bool bFallback);
#endif

#if defined(WWISEC_INCLUDE_FILE_PACKAGE_IO_DEFERRED)
    size_t WWISEC_AK_CAkFilePackageLowLevelIODeferred_Sizeof();
    void* WWISEC_AK_CAkFilePackageLowLevelIODeferred_Create(char* in_ioHookBuffer);
    void WWISEC_AK_CAkFilePackageLowLevelIODeferred_Destroy(void* in_ioHook);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen);
    void WWISEC_AK_CAkFilePackageLowLevelIODeferred_Term(void* in_ioHook);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    void WWISEC_CAkFilePackageLowLevelIODeferred_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_LoadFilePackage(void* in_ioHook, const AkOSChar* in_pszFilePackageName, AkUInt32* out_uPackageID);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadFilePackage(void* in_ioHook, AkUInt32 in_uPackageID);
    WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadAllFilePackages(void* in_ioHook);
    void WWISEC_AK_CAkFilePackageLowLevelIODeferred_SetPackageFallbackBehavior(void* in_ioHook, bool bFallback);
#endif
// END IO Hooks

// BEGIN AkJobWorkerMgr
#if defined(WWISEC_USE_DEFAULT_JOB_WORKER)
    typedef struct WWISEC_AK_JobWorkerMgr_InitSettings
    {
        AkUInt32 uExecutionTimeUSec;                         // Maximum amount of time allotted for one execution of a worker, in microseconds. Defaults to 0 (no timeout).
        AkUInt32 uNumWorkerThreads;                          // How many threads to allocate for processing jobs. Defaults to 2
        WWISEC_AkThreadProperties* arThreadWorkerProperties; // Array of thread settings, should have uNumWorkerThreads elements. If null, will take default thread settings
    } WWISEC_AK_JobWorkerMgr_InitSettings;

    void WWISEC_AK_JobWorkerMgr_InitSettings_GetJobMgrSettings(WWISEC_AK_JobWorkerMgr_InitSettings* self, WWISEC_AkJobMgrSettings* out_JobMgrSettings);

    void WWISEC_AK_JobWorkerMgr_GetDefaultInitSettings(WWISEC_AK_JobWorkerMgr_InitSettings* out_initSettings);
    bool WWISEC_AK_JobWorkerMgr_IsInitialized();
    WWISEC_AKRESULT WWISEC_AK_JobWorkerMgr_InitWorkers(const WWISEC_AK_JobWorkerMgr_InitSettings* in_implInitSettings);
    void WWISEC_AK_JobWorkerMgr_TermWorkers();
#endif
    // END AkJobWorkerMgr

#if defined(WWISEC_USE_SPATIAL_AUDIO)
// BEGIN AkSpatialAudioTypes
#define WWISEC_AK_MAX_REFLECT_ORDER 4
#define WWISEC_AK_MAX_REFLECTION_PATH_LENGTH (WWISEC_AK_MAX_REFLECT_ORDER + 4)
#define WWISEC_AK_MAX_SOUND_PROPAGATION_DEPTH 8
#define WWISEC_AK_MAX_SOUND_PROPAGATION_WIDTH 8
#define WWISEC_AK_DEFAULT_MOVEMENT_THRESHOLD (1.0f)
#define WWISEC_AK_SA_EPSILON (0.001f)
#define WWISEC_AK_SA_DIFFRACTION_EPSILON (0.002f)       // Radians
#define WWISEC_AK_SA_DIFFRACTION_DOT_EPSILON (0.000002) // 1.f - cos(AK_SA_DIFFRACTION_EPSILON)
#define WWISEC_AK_SA_PLANE_THICKNESS_RATIO (0.005f)
#define WWISEC_AK_SA_MIN_ENVIRONMENT_ABSORPTION (0.1f)
#define WWISEC_AK_SA_MIN_ENVIRONMENT_SURFACE_AREA (1.0f)

    const AkUInt32 WWISEC_kDefaultDiffractionMaxEdges = 8;
    const AkUInt32 WWISEC_kDefaultDiffractionMaxPaths = 8;
    const AkReal32 WWISEC_kMaxDiffraction = 1.0f;

    // Max values that are used for calculating diffraction paths between the listener and a portal.
    const AkUInt32 WWISEC_kDiffractionMaxEdges = 8;
    const AkUInt32 WWISEC_kDiffractionMaxPaths = 8;
    const AkUInt32 WWISEC_kPortalToPortalDiffractionMaxPaths = 8;

    typedef AkUInt16 WWISEC_AkVertIdx;
    typedef AkUInt16 WWISEC_AkTriIdx;
    typedef AkUInt16 WWISEC_AkSurfIdx;
    typedef AkUInt16 WWISEC_AkEdgeIdx;
    typedef AkUInt16 WWISEC_AkEdgeReceptorIdx;

#define WWISEC_AK_INVALID_VERTEX ((WWISEC_AkVertIdx)(-1))
#define WWISEC_AK_INVALID_TRIANGLE ((WWISEC_AkTriIdx)(-1))
#define WWISEC_AK_INVALID_SURFACE ((WWISEC_AkSurfIdx)(-1))
#define WWISEC_AK_INVALID_EDGE ((WWISEC_AkEdgeIdx)(-1))

    typedef struct WWISEC_AkSpatialAudioID
    {
        AkUInt64 id;
    } WWISEC_AkSpatialAudioID;

    typedef struct WWISEC_AkRoomID
    {
        AkUInt64 id;
    } WWISEC_AkRoomID;

    static const WWISEC_AkGameObjectID WWISEC_OutdoorsGameObjID = (WWISEC_AkGameObjectID)-4;

    extern const WWISEC_AkRoomID WWISEC_AK_SpatialAudio_kOutdoorRoomID;

    ///< Unique ID for portals.  This ID type exists in the same ID-space as game object ID's.  The client is responsible for not choosing portal ID's
    /// that conflict with registered game objects' ID's.  Internally, the spatial audio rooms and portals API manages registration and un-registration of game objects that
    /// represent portals using AkPortalID's provided by the client; AkPortalID's are convertied to AkGameObjectID's by calling AsGameObjectID().
    /// \sa
    ///	- \ref AK::SpatialAudio::SetPortal
    ///	- \ref AK::SpatialAudio::RemovePortal
    typedef WWISEC_AkSpatialAudioID WWISEC_AkPortalID;

    ///< Unique ID for identifying geometry sets.  Chosen by the client using any means desired.
    /// \sa
    ///	- \ref AK::SpatialAudio::SetGeometry
    ///	- \ref AK::SpatialAudio::RemoveGeometry
    typedef WWISEC_AkSpatialAudioID WWISEC_AkGeometrySetID;

    ///< Unique ID for identifying geometry set instances.  Chosen by the client using any means desired.
    /// \sa
    ///	- \ref AK::SpatialAudio::SetGeometry
    ///	- \ref AK::SpatialAudio::RemoveGeometry
    typedef WWISEC_AkSpatialAudioID WWISEC_AkGeometryInstanceID;

// END AkSpatialAudioTypes

// BEGIN AkReflectGameData
#define WWISEC_AK_MAX_NUM_TEXTURE 4

    /// Data used to describe one image source in Reflect.
    typedef struct WWISEC_AkImageSourceName
    {
        AkUInt32 uNumChar; ///< Number of characters in image source name.
        const char* pName; ///< Optional image source name. Appears in Reflect's editor when profiling.
    } WWISEC_AkImageSourceName;

    typedef struct WWISEC_AkImageSourceTexture
    {
        AkUInt32 uNumTexture;                                     ///< Number of valid textures in the texture array.
        WWISEC_AkUniqueID arTextureID[WWISEC_AK_MAX_NUM_TEXTURE]; ///< Unique IDs of the Acoustics Texture ShareSets used to filter this image source.
    } WWISEC_AkImageSourceTexture;

    typedef struct WWISEC_AkImageSourceParams
    {
        WWISEC_AkVector64 sourcePosition; ///< Image source position, relative to the world.
        AkReal32 fDistanceScalingFactor;  ///< Image source distance scaling. This number effectively scales the sourcePosition vector with respect to the listener and, consequently, scales distance and preserves orientation.
        AkReal32 fLevel;                  ///< Game-controlled level for this source, linear.
        AkReal32 fDiffraction;            ///< Diffraction amount, normalized to the range [0,1].
        AkUInt8 uDiffractionEmitterSide;  ///< If there is a shadow zone diffraction just after the emitter in the reflection path, indicates the number of diffraction edges, otherwise 0 if no diffraction.
        AkUInt8 uDiffractionListenerSide; ///< If there is a shadow zone diffraction before reaching the listener in the reflection path, indicates the number of diffraction edges, otherwise 0 if no diffraction.
    } WWISEC_AkImageSourceParams;

    typedef struct WWISEC_AkReflectImageSource
    {
        WWISEC_AkImageSourceID uID; ///< Image source ID (for matching delay lines across frames)
        WWISEC_AkImageSourceParams params;
        WWISEC_AkImageSourceTexture texture;
        WWISEC_AkImageSourceName name;
    } WWISEC_AkReflectImageSource;

    /// Data structure sent by the game to an instance of the Reflect plug-in.
    typedef struct WWISEC_AkReflectGameData
    {
        WWISEC_AkGameObjectID listenerID;         ///< ID of the listener used to compute spatialization and distance evaluation from within the targeted Reflect plug-in instance. It needs to be one of the listeners that are listening to the game object associated with the targeted plug-in instance. See AK::SoundEngine::SetListeners and AK::SoundEngine::SetGameObjectAuxSendValues.
        AkUInt32 uNumImageSources;                ///< Number of image sources passed in the variable array, below.
        WWISEC_AkReflectImageSource arSources[1]; ///< Variable array of image sources. You should allocate storage for the structure by calling AkReflectGameData::GetSize() with the desired number of sources.
    } WWISEC_AkReflectGameData;
    // END AkReflectGameData

    // BEGIN AkSpatialAudio
    /// Initialization settings of the spatial audio module.
    typedef struct WWISEC_AkSpatialAudioInitSettings
    {
        AkUInt32 uMaxSoundPropagationDepth;              ///< Maximum number of portals that sound can propagate through; must be less than or equal to AK_MAX_SOUND_PROPAGATION_DEPTH.
        AkReal32 fMovementThreshold;                     ///< Amount that an emitter or listener has to move to trigger a recalculation of reflections/diffraction. Larger values can reduce the CPU load at the cost of reduced accuracy.
        AkUInt32 uNumberOfPrimaryRays;                   ///< The number of primary rays used in the ray tracing engine. A larger number of rays will increase the chances of finding reflection and diffraction paths, but will result in higher CPU usage. When CPU limit is active (see \ref AkSpatialAudioInitSettings::fCPULimitPercentage), this setting represents the maximum allowed number of primary rays.
        AkUInt32 uMaxReflectionOrder;                    ///< Maximum reflection order [1, 4] - the number of 'bounces' in a reflection path. A high reflection order renders more details at the expense of higher CPU usage.
        AkUInt32 uMaxDiffractionOrder;                   ///< Maximum diffraction order [1, 8] - the number of 'bends' in a diffraction path. A high diffraction order accommodates more complex geometry at the expense of higher CPU usage.
                                                         ///< Diffraction must be enabled on the geometry to find diffraction paths (refer to \c AkGeometryParams). Set to 0 to disable diffraction on all geometry.
                                                         ///< This parameter limits the recursion depth of diffraction rays cast from the listener to scan the environment, and also the depth of the diffraction search to find paths between emitter and listener.
                                                         ///< To optimize CPU usage, set it to the maximum number of edges you expect the obstructing geometry to traverse.
                                                         ///< For example, if box-shaped geometry is used exclusively, and only a single box is expected between an emitter and then listener, limiting \c uMaxDiffractionOrder to 2 may be sufficient.
                                                         ///< A diffraction path search starts from the listener, so when the maximum diffraction order is exceeded, the remaining geometry between the end of the path and the emitter is ignored.
                                                         ///< In such case, where the search is terminated before reaching the emitter, the diffraction coefficient will be underestimated. It is calculated from a partial path, ignoring any remaining geometry.
        AkUInt32 uDiffractionOnReflectionsOrder;         ///< The maximum possible number of diffraction points at each end of a reflection path. Diffraction on reflection allows reflections to fade in and out smoothly as the listener or emitter moves in and out of the reflection's shadow zone.
                                                         ///< When greater than zero, diffraction rays are sent from the listener to search for reflections around one or more corners from the listener.
                                                         ///< Diffraction must be enabled on the geometry to find diffracted reflections (refer to \c AkGeometryParams). Set to 0 to disable diffraction on reflections.
        AkReal32 fMaxPathLength;                         ///< The total length of a path composed of a sequence of segments (or rays) cannot exceed the defined maximum path length. High values compute longer paths but increase the CPU cost.
                                                         ///< Each individual sound is also affected by its maximum attenuation distance, specified in the Authoring tool. Reflection or diffraction paths, calculated inside Spatial Audio, will never exceed a sound's maximum attenuation distance.
                                                         ///< Note, however, that attenuation is considered infinite if the furthest point is above the audibility threshold.
        AkReal32 fCPULimitPercentage;                    ///< Defines the targeted computation time allocated for the ray tracing engine. Defined as a percentage [0, 100] of the current audio frame. The ray tracing engine dynamically adapts the number of primary rays to target the specified computation time value. In all circumstances, the computed number of primary rays cannot exceed the number of primary rays specified by AkSpatialAudioInitSettings::uNumberOfPrimaryRays.
                                                         ///< A value of 0 indicates no target has been set. In this case, the number of primary rays is fixed and is set by AkSpatialAudioInitSettings::uNumberOfPrimaryRays.
        AkUInt32 uLoadBalancingSpread;                   ///< Spread the computation of paths on uLoadBalancingSpread frames [1..[. When uLoadBalancingSpread is set to 1, no load balancing is done. Values greater than 1 indicate the computation of paths will be spread on this number of frames.
        bool bEnableGeometricDiffractionAndTransmission; ///< Enable computation of geometric diffraction and transmission paths for all sources that have the <b>Enable Diffraction and Transmission</b> box checked in the Positioning tab of the Wwise Property Editor.
                                                         ///< This flag enables sound paths around (diffraction) and through (transmission) geometry (see \c AK::SpatialAudio::SetGeometry).
                                                         ///< Setting \c bEnableGeometricDiffractionAndTransmission to false implies that geometry is only to be used for reflection calculation.
                                                         ///< Diffraction edges must be enabled on geometry for diffraction calculation (see \c AkGeometryParams).
                                                         ///< If \c bEnableGeometricDiffractionAndTransmission is false but a sound has <b>Enable Diffraction and Transmission</b> selected in the Positioning tab of the authoring tool, the sound will diffract through portals but will pass through geometry as if it is not there.
                                                         ///< One would typically disable this setting in the case that the game intends to perform its own obstruction calculation, but geometry is still passed to spatial audio for reflection calculation.
        bool bCalcEmitterVirtualPosition;                ///< An emitter that is diffracted through a portal or around geometry will have its apparent or virtual position calculated by Wwise Spatial Audio and passed on to the sound engine.
    } WWISEC_AkSpatialAudioInitSettings;

    // Settings for individual image sources.
    typedef struct WWISEC_AkImageSourceSettings
    {
        /// Image source parameters.
        WWISEC_AkImageSourceParams params;

        /// Acoustic texture that goes with this image source.
        WWISEC_AkImageSourceTexture texture;
    } WWISEC_AkImageSourceSettings;

    typedef struct WWISEC_AkVertex
    {
        AkReal32 X; ///< X coordinate
        AkReal32 Y; ///< Y coordinate
        AkReal32 Z; ///< Z coordinate
    } WWISEC_AkVertex;

    ///  AkExtent describes an extent with width, height and depth. halfWidth, halfHeight and halfDepth should form a vector from the centre of the volume to the positive corner.
    ///  For portals, negative values in the extent will cause an error. For rooms, negative values can be used to opt out of room transmission.
    typedef struct WWISEC_AkExtent
    {
        AkReal32 halfWidth;
        AkReal32 halfHeight;
        AkReal32 halfDepth;
    } WWISEC_AkExtent;

    /// Triangle for a spatial audio mesh.
    typedef struct WWISEC_AkTriangle
    {
        /// Index into the vertex table passed into \c AkGeometryParams that describes the first vertex of the triangle. Triangles are double-sided, so vertex order in not important.
        WWISEC_AkVertIdx point0;

        /// Index into the vertex table passed into \c AkGeometryParams that describes the second vertex of the triangle. Triangles are double-sided, so vertex order in not important.
        WWISEC_AkVertIdx point1;

        /// Index into the vertex table passed into \c AkGeometryParams that describes the third vertex of the triangle. Triangles are double-sided, so vertex order in not important.
        WWISEC_AkVertIdx point2;

        /// Index into the surface table passed into \c AkGeometryParams that describes the surface properties of the triangle.
        /// If this field is left as \c AK_INVALID_SURFACE, then a default-constructed \c AkAcousticSurface is used.
        WWISEC_AkSurfIdx surface;
    } WWISEC_AkTriangle;

    /// Describes the acoustic surface properties of one or more triangles.
    /// An single acoustic surface may describe any number of triangles, depending on the granularity desired.  For example, if desired for debugging, one could create a unique
    /// \c AkAcousticSurface struct for each triangle, and define a unique name for each.  Alternatively, a single \c AkAcousticSurface could be used to describe all triangles.
    /// In fact it is not necessary to define any acoustic surfaces at all.  If the \c AkTriangle::surface field is left as \c AK_INVALID_SURFACE, then a default-constructed \c AkAcousticSurface is used.
    typedef struct WWISEC_AkAcousticSurface
    {
        /// Acoustic texture ShareSet ID for the surface.  The acoustic texture is authored in Wwise, and the shareset ID may be obtained by calling \c AK::SoundEngine::GetIDFromString
        /// \sa <tt>\ref AK::SoundEngine::GetIDFromString()</tt>
        AkUInt32 textureID;

        /// Value to set when modeling sound transmission through geometry. Transmission is modeled only when the sound emitted enables diffraction and there is no direct line of sight from the emitter to the listener.
        /// If more that one surface is between the emitter and the listener, the maximum of each surface's transmission loss value is used. If the emitter and listener are in different rooms, then the rooms' transmission loss is taken into account.
        /// The maximum of all the surfaces' transmission loss value, and the transmission loss value (see \c AkRoomParams) is used to render the transmission path.
        /// Valid range: (0.f-1.f)
        /// - \ref AkRoomParams
        AkReal32 transmissionLoss;

        /// Name to describe this surface
        const char* strName;
    } WWISEC_AkAcousticSurface;

    /// Structure for retrieving information about the indirect paths of a sound that have been calculated via the geometric reflections API. Useful for debug draw applications.
    typedef struct WWISEC_AkReflectionPathInfo
    {
        /// Apparent source of the reflected sound that follows this path.
        WWISEC_AkVector64 imageSource;

        /// Vertices of the indirect path.
        /// pathPoint[0] is closest to the emitter, pathPoint[numPathPoints-1] is closest to the listener.
        WWISEC_AkVector64 pathPoint[WWISEC_AK_MAX_REFLECTION_PATH_LENGTH];

        /// The surfaces that were hit in the path.
        /// surfaces[0] is closest to the emitter, surfaces[numPathPoints-1] is closest to the listener.
        WWISEC_AkAcousticSurface surfaces[WWISEC_AK_MAX_REFLECTION_PATH_LENGTH];

        /// Number of valid elements in the \c pathPoint[], \c surfaces[], and \c diffraction[] arrays.
        AkUInt32 numPathPoints;

        /// Number of reflections in the \c pathPoint[] array. Shadow zone diffraction does not count as a reflection. If there is no shadow zone diffraction, \c numReflections is equal to \c numPathPoints.
        AkUInt32 numReflections;

        /// Diffraction amount, normalized to the range [0,1]
        AkReal32 diffraction[WWISEC_AK_MAX_REFLECTION_PATH_LENGTH];

        /// Linear gain applied to image source.
        AkReal32 level;

        /// Deprecated - always false. Occluded paths are not generated.
        bool isOccluded;
    } WWISEC_AkReflectionPathInfo;

    /// Structure for retrieving information about paths for a given emitter.
    /// The diffraction paths represent indirect sound paths from the emitter to the listener, whether they go through portals
    /// (via the rooms and portals API) or are diffracted around edges (via the geometric diffraction API).
    /// The direct path is included here and can be identified by checking \c nodeCount == 0. The direct path may have a non-zero transmission loss
    /// if it passes through geometry or between rooms.
    typedef struct WWISEC_AkDiffractionPathInfo
    {
        /// Diffraction points along the path. nodes[0] is the point closest to the listener; nodes[numNodes-1] is the point closest to the emitter.
        /// Neither the emitter position nor the listener position are represented in this array.
        WWISEC_AkVector64 nodes[WWISEC_AK_MAX_SOUND_PROPAGATION_DEPTH];

        /// Emitter position. This is the source position for an emitter. In all cases, except for radial emitters, it is the same position as the game object position.
        /// For radial emitters, it is the calculated position at the edge of the volume.
        WWISEC_AkVector64 emitterPos;

        /// Raw diffraction angles at each point, in radians.
        AkReal32 angles[WWISEC_AK_MAX_SOUND_PROPAGATION_DEPTH];

        /// ID of the portals that the path passes through.  For a given node at position i (in the nodes array), if the path diffracts on a geometric edge, then portals[i] will be an invalid portal ID (ie. portals[i].IsValid() will return false).
        /// Otherwise, if the path diffracts through a portal at position i, then portals[i] will be the ID of that portal.
        /// portal[0] represents the node closest to the listener; portal[numNodes-1] represents the node closest to the emitter.
        WWISEC_AkPortalID portals[WWISEC_AK_MAX_SOUND_PROPAGATION_DEPTH];

        /// ID's of the rooms that the path passes through. For a given node at position i, room[i] is the room on the listener's side of the node. If node i diffracts through a portal,
        /// then rooms[i] is on the listener's side of the portal, and rooms[i+1] is on the emitters side of the portal.
        /// There is always one extra slot for a room so that the emitters room is always returned in slot room[numNodes] (assuming the path has not been truncated).
        WWISEC_AkRoomID rooms[WWISEC_AK_MAX_SOUND_PROPAGATION_DEPTH + 1];

        /// Virtual emitter position. This is the position that is passed to the sound engine to render the audio using multi-positioning, for this particular path.
        WWISEC_AkWorldTransform virtualPos;

        /// Total number of nodes in the path.  Defines the number of valid entries in the \c nodes, \c angles, and \c portals arrays. The \c rooms array has one extra slot to fit the emitter's room.
        AkUInt32 nodeCount;

        /// Calculated total diffraction from this path, normalized to the range [0,1]
        /// The diffraction amount is calculated from the sum of the deviation angles from a straight line, of all angles at each nodePoint.
        //	Can be thought of as how far into the 'shadow region' the sound has to 'bend' to reach the listener.
        /// This value is applied internally, by spatial audio, as the Diffraction value and built-in parameter of the emitter game object.
        /// \sa
        /// - \ref AkSpatialAudioInitSettings
        AkReal32 diffraction;

        /// Calculated total transmission loss from this path, normalized to the range [0,1]
        /// This field will be 0 for diffraction paths where \c nodeCount > 0. It may be non-zero for the direct path where \c nodeCount == 0.
        /// The path's transmission loss value is the combination of the geometric transmission loss and the room transmission loss, by taking the greater of the two.
        /// The geometric transmission loss is calculated from the transmission loss values assigned to the geometry that this path transmits through.
        /// If a path transmits through multiple geometries with different transmission loss values, the largest value is taken.
        /// The room transmission loss is taken from the emitter and listener rooms' transmission loss values, and likewise,
        /// if the listener's room and the emitter's room have different transmission loss values, the greater of the two is used.
        /// This value is applied internally, by spatial audio, as the Transmission Loss value and built-in parameter of the emitter game object.
        /// \sa
        /// - \ref AkSpatialAudioInitSettings
        /// - \ref AkRoomParams
        /// - \ref AkAcousticSurface
        AkReal32 transmissionLoss;

        /// Total path length
        /// Represents the sum of the length of the individual segments between nodes, with a correction factor applied for diffraction.
        /// The correction factor simulates the phenomenon where by diffracted sound waves decay faster than incident sound waves and can be customized in the spatial audio init settings.
        /// \sa
        /// - \ref AkSpatialAudioInitSettings
        AkReal32 totLength;

        /// Obstruction value for this path
        /// This value includes the accumulated portal obstruction for all portals along the path.
        AkReal32 obstructionValue;
    } WWISEC_AkDiffractionPathInfo;

    /// Parameters passed to \c SetPortal
    typedef struct WWISEC_AkPortalParams
    {
        /// Portal's position and orientation in the 3D world.
        /// Position vector is the center of the opening.
        /// OrientationFront vector must be unit-length and point along the normal of the portal, and must be orthogonal to Up. It defines the local positive-Z dimension (depth/transition axis) of the portal, used by Extent.
        /// OrientationTop vector must be unit-length and point along the top of the portal (tangent to the wall), must be orthogonal to Front. It defines the local positive-Y direction (height) of the portal, used by Extent.
        WWISEC_AkWorldTransform Transform;

        /// Portal extent. Defines the dimensions of the portal relative to its center; all components must be positive numbers. The local right and up dimensions are used in diffraction calculations,
        /// whereas the front dimension defines a depth value which is used to implement smooth transitions between rooms. It is recommended that users experiment with different portal depths to find a value
        /// that results in appropriately smooth transitions between rooms. Extent dimensions must be positive.
        WWISEC_AkExtent Extent;

        /// Whether or not the portal is active/enabled. For example, this parameter may be used to simulate open/closed doors.
        /// Portal diffraction is simulated when at least one portal exists and is active between an emitter and the listener.
        bool bEnabled;

        /// ID of the room to which the portal connects, in the direction of the Front vector.  If a room with this ID has not been added via AK::SpatialAudio::SetRoom,
        /// a room will be created with this ID and with default AkRoomParams.  If you would later like to update the AkRoomParams, simply call AK::SpatialAudio::SetRoom again with this same ID.
        ///	- \ref AK::SpatialAudio::SetRoom
        ///	- \ref AK::SpatialAudio::RemoveRoom
        /// - \ref AkRoomParams
        WWISEC_AkRoomID FrontRoom;

        /// ID of the room to which the portal connects, in the direction opposite to the Front vector. If a room with this ID has not been added via AK::SpatialAudio::SetRoom,
        /// a room will be created with this ID and with default AkRoomParams.  If you would later like to update the AkRoomParams, simply call AK::SpatialAudio::SetRoom again with this same ID.
        ///	- \ref AK::SpatialAudio::SetRoom
        ///	- \ref AK::SpatialAudio::RemoveRoom
        /// - \ref AkRoomParams
        WWISEC_AkRoomID BackRoom;
    } WWISEC_AkPortalParams;

    /// Parameters passed to \c SetRoom
    typedef struct WWISEC_AkRoomParams
    {
        /// Room Orientation. Up and Front must be orthonormal.
        /// Room orientation has an effect when the associated aux bus (see ReverbAuxBus) is set with 3D Spatialization in Wwise, as 3D Spatialization implements relative rotation of the emitter (room) and listener.
        WWISEC_AkVector Front;

        /// Room Orientation. Up and Front must be orthonormal.
        /// Room orientation has an effect when the associated aux bus (see ReverbAuxBus) is set with 3D Spatialization in Wwise, as 3D Spatialization implements relative rotation of the emitter (room) and listener.
        WWISEC_AkVector Up;

        /// The reverb aux bus that is associated with this room.
        /// When Spatial Audio is told that a game object is in a particular room via SetGameObjectInRoom, a send to this aux bus will be created to model the reverb of the room.
        /// Using a combination of Rooms and Portals, Spatial Audio manages which game object the aux bus is spawned on, and what control gain is sent to the bus.
        /// When a game object is inside a connected portal, as defined by the portal's orientation and extent vectors, both this aux send and the aux send of the adjacent room are active.
        /// Spatial audio modulates the control value for each send based on the game object's position, in relation to the portal's z-azis and extent, to crossfade the reverb between the two rooms.
        /// If more advanced control of reverb is desired, SetGameObjectAuxSendValues can be used to add additional sends on to a game object.
        /// - \ref AK::SpatialAudio::SetGameObjectInRoom
        /// - \ref AK::SoundEngine::SetGameObjectAuxSendValues
        WWISEC_AkAuxBusID ReverbAuxBus;

        /// The reverb control value for the send to ReverbAuxBus. Valid range: (0.f-1.f)
        /// Can be used to implement multiple rooms that share the same aux bus, but have different reverb levels.
        AkReal32 ReverbLevel;

        /// Level to set when modeling transmission through walls. Transmission is modeled only when the sound emitted enables diffraction and there is no direct line of sight from the emitter to the listener.
        /// This transmission loss value is only applied when the listener and the emitter are in different rooms; it is taken as the maximum between the emitter's room's transmission loss value and the listener's room's transmission loss value.
        /// If there is geometry in between the listener and the emitter, then the transmission loss value assigned to surfaces hit by the ray between the emitter and listener is also taken into account.
        /// The maximum of all the surfaces' transmission loss value (see \c AkAcousticSurface), and the room's transmission loss value is used to render the transmission path.
        /// Valid range: (0.f-1.f)
        /// - \ref AkAcousticSurface
        AkReal32 TransmissionLoss;

        /// Send level for sounds that are posted on the room game object; adds reverb to ambience and room tones. Valid range: (0.f-1.f).  Set to a value greater than 0 to have spatial audio create a send on the room game object,
        /// where the room game object itself is specified as the listener and ReverbAuxBus is specified as the aux bus. A value of 0 disables the aux send. This should not be confused with ReverbLevel, which is the send level
        /// for spatial audio emitters sending to the room game object.
        /// \aknote The room game object can be accessed though the ID that is passed to \c SetRoom() and the \c AkRoomID::AsGameObjectID() method.  Posting an event on the room game object leverages automatic room game object placement
        ///	by spatial audio so that when the listener is inside the room, the sound comes from all around the listener, and when the listener is outside the room, the sound comes from the portal(s). Typically, this would be used for
        /// surround ambiance beds or room tones. Point source sounds should use separate game objects that are registered as spatial audio emitters.
        /// \sa
        /// - \ref AkRoomParams::RoomGameObj_KeepRegistered
        /// - \ref AkRoomID
        AkReal32 RoomGameObj_AuxSendLevelToSelf;

        /// If set to true, the room game object will be registered on calling \c SetRoom(), and not released untill the room is deleted or removed with \c RemoveRoom(). If set to false, spatial audio will register
        /// the room object only when it is needed by the sound propagation system for the purposes of reverb, and will unregister the game object when all reverb tails have finished.
        /// If the game intends to post events on the room game object for the purpose of ambiance or room tones, RoomGameObj_KeepRegistered should be set to true.
        /// \aknote The room game object can be accessed though the ID that is passed to \c SetRoom() and the \c AkRoomID::AsGameObjectID() method.  Posting an event on the room game object leverages automatic room game object placement
        ///	by spatial audio so that when the listener is inside the room, the sound comes from all around the listener, and when the listener is outside the room, the sound comes from the portal(s). Typically, this would be used for
        /// surround ambiance beds or room tones. Point source sounds should use separate game objects that are registered as spatial audio emitters.
        /// \sa
        /// - \ref AkRoomParams::RoomGameObj_AuxSendLevelToSelf
        /// - \ref AkRoomID
        bool RoomGameObj_KeepRegistered;

        /// Associate this room with the geometry instance \c GeometryInstanceID, describing the shape of the room. When a room is associated with a geometry instance, the vertices are used to compute the spread value for room transmission.
        /// The vertices are used for computing an oriented bounding box for the room where the orientation of the bounding box is given by the Up and Front vectors. The center of the room is defined as the oriented bounding box center.
        /// The extent of the bounding box is computed from the geometry set's vertices projected on to the orientation axes.
        /// \aknote If the geometry set is only to be used for the room and not for reflection and diffraction calculation, then make sure to set \c AkGeometryParams::EnableTriangles to false.
        /// It will still be necessary to create an instance for the geometry, so that the vertices can be positioned, scaled and rotated as desired.
        /// \sa
        /// - \ref spatial_audio_roomsportals_apiconfigroomgeometry
        /// - \ref AkGeometryParams
        WWISEC_AkGeometrySetID GeometryInstanceID;
    } WWISEC_AkRoomParams;

    /// Parameters passed to \c SetGeometry
    typedef struct WWISEC_AkGeometryParams
    {
        /// Pointer to an array of AkTriangle structures.
        /// This array will be copied into spatial audio memory and will not be accessed after \c SetGeometry returns.
        ///	- \ref AkTriangle
        ///	- \ref AK::SpatialAudio::SetGeometry
        ///	- \ref AK::SpatialAudio::RemoveGeometry
        WWISEC_AkTriangle* Triangles;

        /// Number of triangles in Triangles.
        WWISEC_AkTriIdx NumTriangles;

        /// Pointer to an array of AkVertex structures.
        /// This array will be copied into spatial audio memory and will not be accessed after \c SetGeometry returns.
        ///	- \ref AkVertex
        ///	- \ref AK::SpatialAudio::SetGeometry
        ///	- \ref AK::SpatialAudio::RemoveGeometry
        WWISEC_AkVertex* Vertices;

        ///< Number of vertices in Vertices.
        WWISEC_AkVertIdx NumVertices;

        ///< Pointer to an array of AkAcousticSurface structures.
        /// This array will be copied into spatial audio memory and will not be accessed after \c SetGeometry returns.
        ///	- \ref AkVertex
        ///	- \ref AK::SpatialAudio::SetGeometry
        ///	- \ref AK::SpatialAudio::RemoveGeometry
        WWISEC_AkAcousticSurface* Surfaces;

        /// Number of of AkTriangleInfo structures in in_pTriangleInfo and number of AkTriIdx's in in_infoMap.
        WWISEC_AkSurfIdx NumSurfaces;

        /// Switch to enable or disable geometric diffraction for this Geometry.
        bool EnableDiffraction;

        /// Switch to enable or disable geometric diffraction on boundary edges for this Geometry.  Boundary edges are edges that are connected to only one triangle.
        bool EnableDiffractionOnBoundaryEdges;

        /// Switch to enable or disable the use of the triangles for this Geometry. When enabled, the geometry triangles are indexed for ray computation and used to computed reflection and diffraction.
        /// Set EnableTriangles to false when using a geometry set only to describe a room, and not for reflection and diffraction calculation.
        ///	\sa
        /// - \ref AkRoomParams
        bool EnableTriangles;
    } WWISEC_AkGeometryParams;

#define WWISEC_AK_DEFAULT_GEOMETRY_POSITION_X (0.0)
#define WWISEC_AK_DEFAULT_GEOMETRY_POSITION_Y (0.0)
#define WWISEC_AK_DEFAULT_GEOMETRY_POSITION_Z (0.0)
#define WWISEC_AK_DEFAULT_GEOMETRY_FRONT_X (0.0)
#define WWISEC_AK_DEFAULT_GEOMETRY_FRONT_Y (0.0)
#define WWISEC_AK_DEFAULT_GEOMETRY_FRONT_Z (1.0)
#define WWISEC_AK_DEFAULT_GEOMETRY_TOP_X (0.0)
#define WWISEC_AK_DEFAULT_GEOMETRY_TOP_Y (1.0)
#define WWISEC_AK_DEFAULT_GEOMETRY_TOP_Z (0.0)

    typedef struct WWISEC_AkGeometryInstanceParams
    {
        /// Set the position and orientation of the geometry instance.
        /// AkWorldTransform uses one vector to define the position of the geometry instance, and two more to define the orientation; a forward vector and an up vector.
        /// To ensure that a geometry instance has the correct rotation with respect to the game, AkInitSettings::eFloorPlane must be initialized with the correct value.
        ///	\sa
        /// - \ref AkInitSettings::eFloorPlane
        /// - \ref AK::SpatialAudio::SetGeometryInstance
        ///	- \ref AK::SpatialAudio::RemoveGeometryInstance
        WWISEC_AkWorldTransform PositionAndOrientation;

        /// Set the 3-dimensional scaling of the geometry instance.
        /// \sa
        /// - \ref AK::SpatialAudio::SetGeometryInstance
        ///	- \ref AK::SpatialAudio::RemoveGeometryInstance
        WWISEC_AkVector Scale;

        /// Geometry set referenced by the instance
        /// \sa
        ///	- \ref AK::SpatialAudio::SetGeometry
        ///	- \ref AK::SpatialAudio::RemoveGeometry
        /// - \ref AK::SpatialAudio::SetGeometryInstance
        ///	- \ref AK::SpatialAudio::RemoveGeometryInstance
        WWISEC_AkGeometrySetID GeometrySetID;

        /// Associate this geometry instance with the room \c RoomID. Associating a geometry instance with a particular room will limit the scope in which the geometry is visible/accessible. \c RoomID can be left as default (-1), in which case
        /// this geometry instance will have a global scope. It is recommended to associate geometry with a room when the geometry is (1) fully contained within the room (ie. not visible to other rooms accept by portals),
        /// and (2) the room does not share geometry with other rooms. Doing so reduces the search space for ray casting performed by reflection and diffraction calculations. Take note that once one or more geometry instances
        /// are associated with a room, that room will no longer be able to access geometry that is in the global scope.
        ///	- \ref AK::SpatialAudio::SetRoom
        ///	- \ref AkRoomParams
        WWISEC_AkRoomID RoomID;
    } WWISEC_AkGeometryInstanceParams;

    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_Init(const WWISEC_AkSpatialAudioInitSettings* in_initSettings);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RegisterListener(WWISEC_AkGameObjectID in_gameObjectID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_UnregisterListener(WWISEC_AkGameObjectID in_gameObjectID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectRadius(WWISEC_AkGameObjectID in_gameObjectID, AkReal32 in_outerRadius, AkReal32 in_innerRadius);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetImageSource(WWISEC_AkImageSourceID in_srcID, const WWISEC_AkImageSourceSettings* in_info, const char* in_name, WWISEC_AkUniqueID in_AuxBusID, WWISEC_AkGameObjectID in_gameObjectID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RemoveImageSource(WWISEC_AkImageSourceID in_srcID, WWISEC_AkUniqueID in_AuxBusID, WWISEC_AkGameObjectID in_gameObjectID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_ClearImageSources(WWISEC_AkUniqueID in_AuxBusID, WWISEC_AkGameObjectID in_gameObjectID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetGeometry(WWISEC_AkGeometrySetID in_GeomSetID, const WWISEC_AkGeometryParams* in_params);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RemoveGeometry(WWISEC_AkGeometrySetID in_SetID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetGeometryInstance(WWISEC_AkGeometryInstanceID in_GeometryInstanceID, const WWISEC_AkGeometryInstanceParams* in_params);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RemoveGeometryInstance(WWISEC_AkGeometryInstanceID in_GeometryInstanceID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_QueryReflectionPaths(WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_positionIndex, WWISEC_AkVector64* out_listenerPos, WWISEC_AkVector64* out_emitterPos, WWISEC_AkReflectionPathInfo* out_aPaths, AkUInt32* io_uArraySize);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetRoom(WWISEC_AkRoomID in_RoomID, const WWISEC_AkRoomParams* in_Params, const char* in_RoomName);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RemoveRoom(WWISEC_AkRoomID in_RoomID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetPortal(WWISEC_AkPortalID in_PortalID, const WWISEC_AkPortalParams* in_Params, const char* in_PortalName);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RemovePortal(WWISEC_AkPortalID in_PortalID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectInRoom(WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkRoomID in_CurrentRoomID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetReflectionsOrder(AkUInt32 in_uReflectionsOrder, bool in_bUpdatePaths);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetDiffractionOrder(AkUInt32 in_uDiffractionOrder, bool in_bUpdatePaths);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetNumberOfPrimaryRays(AkUInt32 in_uNbPrimaryRays);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetLoadBalancingSpread(AkUInt32 in_uNbFrames);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetEarlyReflectionsAuxSend(WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkAuxBusID in_auxBusID);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetEarlyReflectionsVolume(WWISEC_AkGameObjectID in_gameObjectID, AkReal32 in_fSendVolume);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetPortalObstructionAndOcclusion(WWISEC_AkPortalID in_PortalID, AkReal32 in_fObstruction, AkReal32 in_fOcclusion);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectToPortalObstruction(WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkPortalID in_PortalID, AkReal32 in_fObstruction);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetPortalToPortalObstruction(WWISEC_AkPortalID in_PortalID0, WWISEC_AkPortalID in_PortalID1, AkReal32 in_fObstruction);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_QueryWetDiffraction(WWISEC_AkPortalID in_portal, AkReal32* out_wetDiffraction);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_QueryDiffractionPaths(WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_positionIndex, WWISEC_AkVector64* out_listenerPos, WWISEC_AkVector64* out_emitterPos, WWISEC_AkDiffractionPathInfo* out_aPaths, AkUInt32* io_uArraySize);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_ResetStochasticEngine();
    // END AkSpatialAudio

    // BEGIN AkReverbEstimation
    float WWISEC_AK_SpatialAudio_ReverbEstimation_CalculateSlope(const WWISEC_AkAcousticTexture* texture);
    void WWISEC_AK_SpatialAudio_ReverbEstimation_GetAverageAbsorptionValues(WWISEC_AkAcousticTexture* in_textures, float* in_surfaceAreas, int in_numTextures, WWISEC_AkAcousticTexture* out_average);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateT60Decay(AkReal32 in_volumeCubicMeters, AkReal32 in_surfaceAreaSquaredMeters, AkReal32 in_environmentAverageAbsorption, AkReal32* out_decayEstimate);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateTimeToFirstReflection(WWISEC_AkVector in_environmentExtentMeters, AkReal32* out_timeToFirstReflectionMs, AkReal32 in_speedOfSound);
    WWISEC_AKRESULT WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateHFDamping(WWISEC_AkAcousticTexture* in_textures, float* in_surfaceAreas, int in_numTextures, AkReal32* out_hfDamping);
    // END AkReverbEstimation
#endif

// BEGIN Platform-specific AkSoundEngine functions
#if defined(AK_WIN)
    typedef struct IMMDevice IMMDevice;

    AkUInt32 WWISEC_AK_GetDeviceID(IMMDevice* in_pDevice);

    AkUInt32 WWISEC_AK_GetDeviceIDFromName(wchar_t* in_szToken);

    const wchar_t* WWISEC_AK_GetWindowsDeviceName(AkInt32 index, AkUInt32* out_uDeviceID, WWISEC_AkAudioDeviceState uDeviceStateMask);

    AkUInt32 WWISEC_AK_GetWindowsDeviceCount(WWISEC_AkAudioDeviceState uDeviceStateMask);

    bool WWISEC_AK_GetWindowsDevice(AkInt32 in_index, AkUInt32* out_uDeviceID, IMMDevice** out_ppDevice, WWISEC_AkAudioDeviceState uDeviceStateMask);
#endif

#if defined(AK_ANDROID)
    WWISEC_SLObjectItf WWISEC_AK_SoundEngine_GetWwiseOpenSLInterface();

    WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetFastPathSettings(WWISEC_AkInitSettings* in_settings, WWISEC_AkPlatformInitSettings* in_pfSettings);
#endif

#if defined(AK_IOS)
    void WWISEC_AK_SoundEngine_iOS_ChangeAudioSessionProperties(const WWISEC_AkAudioSessionProperties* in_properties);
#endif
    // END Platform-specific AkSoundEngine functions

#ifdef __cplusplus
}
#endif