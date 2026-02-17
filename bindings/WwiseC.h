/* wwise-c headers are manually copied and edited code from Wwise SDK so I put the original license here */
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

// BEGIN AkTypedefs
#include <AK/SoundEngine/Common/AkTypedefs.h>
// END AkTypedefs

// BEGIN AkConstants
#include <AK/SoundEngine/Common/AkConstants.h>
// END AkConstants

// BEGIN AkEnums
#include <AK/SoundEngine/Common/AkEnums.h>
// END AkEnums

// BEGIN Ak3DObjects
#include <AK/SoundEngine/Common/Ak3DObjects.h>

    typedef struct WWISEC_AkSphericalCoord
    {
        AkPolarCoord base;
        AkReal32 phi;
    } WWISEC_AkSphericalCoord;

    typedef struct WWISEC_AkEmitterListenerPair
    {
        struct AkWorldTransform emitter;   ///< Emitter position.
        AkReal32 fDistance;                ///< Distance between emitter and listener.
        AkReal32 fEmitterAngle;            ///< Angle between position vector and emitter orientation.
        AkReal32 fListenerAngle;           ///< Angle between position vector and listener orientation.
        AkReal32 fDryMixGain;              ///< Emitter-listener-pair-specific gain (due to distance and cone attenuation) for direct connections.
        AkReal32 fGameDefAuxMixGain;       ///< Emitter-listener-pair-specific gain (due to distance and cone attenuation) for game-defined send connections.
        AkReal32 fUserDefAuxMixGain;       ///< Emitter-listener-pair-specific gain (due to distance and cone attenuation) for user-defined send connections.
        AkReal32 fOcclusion;               ///< Emitter-listener-pair-specific occlusion factor
        AkReal32 fObstruction;             ///< Emitter-listener-pair-specific obstruction factor
        AkReal32 fDiffraction;             ///< Emitter-listener-pair-specific diffraction coefficient
        AkReal32 fTransmissionLoss;        ///< Emitter-listener-pair-specific transmission occlusion.
        AkReal32 fSpread;                  ///< Emitter-listener-pair-specific spread
        AkReal32 fAperture;                ///< Emitter-listener-pair-specific aperture
        AkReal32 fScalingFactor;           ///< Combined scaling factor due to both emitter and listener.
        AkReal32 fPathGain;                ///< Emitter-listener-pair-specific overall gain that scales fDryMixGain, fGameDefAuxMixGain and fUserDefAuxMixGain
        AkChannelMask uEmitterChannelMask; ///< Channels of the emitter that apply to this ray.
        AkRayID id;                        ///< ID of this emitter-listener pair, unique for a given emitter.
        AkGameObjectID m_uListenerID;      ///< Listener game object ID.
    } WWISEC_AkEmitterListenerPair;
    // END Ak3DObjects

// BEGIN AkSoundEngineTypes
#include <AK/SoundEngine/Common/AkSoundEngineTypes.h>

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

    void WWISEC_AkOutputSettings_Init(struct AkOutputSettings* outputSettings, const char* in_szDeviceShareSet, AkUniqueID in_idDevice, struct AkChannelConfig in_channelConfig, enum AkPanningRule in_ePanning);
// END AkSoundEngineTypes

// BEGIN AkMidiTypes
#include <AK/SoundEngine/Common/AkMidiTypes.h>
    // END AkMidiTypes

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
        AkPlayingID in_playingID;    ///< Related Playing ID if applicable
        AkGameObjectID in_gameObjID; ///< Related Game Object ID if applicable, AK_INVALID_GAME_OBJECT otherwise
        AkUniqueID in_soundID;       ///< Related Audio Node ID if applicable, AK_INVALID_UNIQUE_ID otherwise
        bool in_bIsBus;              ///< true if in_audioNodeID is a bus
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
        WWISEC_AK_Monitor_ErrorCode_IODeviceStr,
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
        WWISEC_AK_Monitor_ErrorCode_AudioNodeNotFound,
        WWISEC_AK_Monitor_ErrorCode_SetBusConfigUnsupported,
        WWISEC_AK_Monitor_ErrorCode_BusNotFound,

        WWISEC_AK_Monitor_ErrorCode_MismatchingMediaSize,
        WWISEC_AK_Monitor_ErrorCode_IncompatibleBankVersion,
        WWISEC_AK_Monitor_ErrorCode_UnexpectedPrepareGameSyncsCall,
        WWISEC_AK_Monitor_ErrorCode_LoadingBankMismatch,

        WWISEC_AK_Monitor_ErrorCode_ProxyObjectMismatch,
        WWISEC_AK_Monitor_ErrorCode_ProxyObjectMemory,

        WWISEC_AK_Monitor_ErrorCode_MasterBusStructureNotLoaded,
        WWISEC_AK_Monitor_ErrorCode_TooManyChildren,
        WWISEC_AK_Monitor_ErrorCode_BankContainUneditableEffect,
        WWISEC_AK_Monitor_ErrorCode_MemoryAllocationFailed,
        WWISEC_AK_Monitor_ErrorCode_InvalidFloatPriority,
        WWISEC_AK_Monitor_ErrorCode_SoundLoadFailedInsufficientMemory,
        WWISEC_AK_Monitor_ErrorCode_NXDeviceRegistrationFailed,
        WWISEC_AK_Monitor_ErrorCode_MixPluginOnObjectBus,

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
        WWISEC_AK_Monitor_ErrorCode_FilePermissionError,

        WWISEC_AK_Monitor_ErrorCode_SetEffectOnRendered,
        WWISEC_AK_Monitor_ErrorCode_GeometryNotWatertight,

        WWISEC_AK_Monitor_ErrorCode_CannotInitialize3DAudio,
        WWISEC_AK_Monitor_ErrorCode_CannotInitializeInputCallbacks,
        WWISEC_AK_Monitor_ErrorCode_CannotConnectAVAudioEngineSource,

        WWISEC_AK_Monitor_ErrorCode_ChannelConfigRequestDenied,
        WWISEC_AK_Monitor_ErrorCode_MediaUpdatedFromWwise,
        WWISEC_AK_Monitor_ErrorCode_MediaErrorFromWwise,
        WWISEC_AK_Monitor_ErrorCode_OutputAlreadyExists,
        WWISEC_AK_Monitor_ErrorCode_UnknownStateGroup,
        WWISEC_AK_Monitor_ErrorCode_MediaErrorWwiseMRUFull,
        WWISEC_AK_Monitor_ErrorCode_AudioOut2ContextCreateError,
        WWISEC_AK_Monitor_ErrorCode_AudioOut2UserCreateError,

        WWISEC_AK_Monitor_ErrorCode_FeedbackOnAudioObjectsBus,

        WWISEC_AK_Monitor_ErrorCode_SpatialAudio_SiblingPortal,
        WWISEC_AK_Monitor_ErrorCode_ActivityPlayback_Warning,

        WWISEC_AK_Monitor_ErrorCode_CannotPlaySource_FileAccess,
        WWISEC_AK_Monitor_ErrorCode_MediaDiscrepancy,
        WWISEC_AK_Monitor_ErrorCode_WwiseIODisconnected,
        WWISEC_AK_Monitor_ErrorCode_WwiseIODisconnectedStr,
        WWISEC_AK_Monitor_ErrorCode_IODevice,

        WWISEC_AK_Monitor_ErrorCode_InvalidCommand,
        WWISEC_AK_Monitor_ErrorCode_PlayingIDAlreadyExists,
        WWISEC_AK_Monitor_ErrorCode_IOStreamLeak,

        WWISEC_AK_Monitor_ErrorCode_SetSidechainMixConfigInvalid,

        WWISEC_AK_Monitor_ErrorCode_NodeNotCompatibleWithMidi,
        // ALWAYS ADD NEW CODES AT THE END !!!!!!!
        // Otherwise it may break comm compatibility in a patch

        WWISEC_AK_Monitor_Num_ErrorCodes // THIS STAYS AT END OF ENUM
    } WWISEC_AK_Monitor_ErrorCode;

    AK_CALLBACK(void, WWISEC_AK_Monitor_LocalOutputFunc)
    (
        WWISEC_AK_Monitor_ErrorCode in_eErrorCode,   ///< Error code number value
        const AkOSChar* in_pszError,                 ///< Message or error string to be displayed
        WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel, ///< Specifies whether it should be displayed as a message or an error
        AkPlayingID in_playingID,                    ///< Related Playing ID if applicable, AK_INVALID_PLAYING_ID otherwise
        AkGameObjectID in_gameObjID                  ///< Related Game Object ID if applicable, AK_INVALID_GAME_OBJECT otherwise
    );

    typedef struct WWISEC_AkStreamMgrSettings WWISEC_AkStreamMgrSettings;
    typedef struct WWISEC_AkDeviceSettings WWISEC_AkDeviceSettings;

    AKRESULT WWISEC_AK_Monitor_PostCode(WWISEC_AK_Monitor_ErrorCode in_eError, WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel, AkPlayingID in_playingID, AkGameObjectID in_gameObjID, AkUniqueID in_audioNodeID, bool in_bIsBus);
    AKRESULT WWISEC_AK_Monitor_PostString(const char* in_pszError, WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel, AkPlayingID in_playingID, AkGameObjectID in_gameObjID, AkUniqueID in_audioNodeID, bool in_bIsBus);
    AKRESULT WWISEC_AK_Monitor_SetLocalOutput(AkUInt32 in_uErrorLevel, WWISEC_AK_Monitor_LocalOutputFunc in_pMonitorFunc);
    AKRESULT WWISEC_AK_Monitor_AddTranslator(WWISEC_AkErrorMessageTranslator* translator, bool overridePreviousTranslators);
    AKRESULT WWISEC_AK_Monitor_ResetTranslator();
    AkTimeMs WWISEC_AK_Monitor_GetTimeStamp();
    void WWISEC_AK_Monitor_MonitorStreamMgrInit(const WWISEC_AkStreamMgrSettings* in_streamMgrSettings);
    void WWISEC_AK_Monitor_MonitorStreamingDeviceInit(AkDeviceID in_deviceID, const WWISEC_AkDeviceSettings* in_deviceSettings);
    void WWISEC_AK_Monitor_MonitorStreamingDeviceDestroyed(AkDeviceID in_deviceID);
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
    const AkDataTypeID WWISEC_AK_INT = 0;   ///< Integer data type (uchar, short, and so on)
    const AkDataTypeID WWISEC_AK_FLOAT = 1; ///< Float data type

    typedef struct WWISEC_AK_AkMetering
    {
        /// Peak of each channel in this frame.
        /// Vector of linear peak levels, corresponding to each channel. NULL if AK_EnableBusMeter_Peak is not set (see IAkMixerPluginContext::SetMeteringFlags() or AK::SoundEngine::RegisterBusMeteringCallback()).
        AkSpeakerVolumesMatrixPtr peak;

        /// True peak of each channel (as defined by ITU-R BS.1770) in this frame.
        /// Vector of linear true peak levels, corresponding to each channel. NULL if AK_EnableBusMeter_TruePeak is not set (see IAkMixerPluginContext::SetMeteringFlags() or AK::SoundEngine::RegisterBusMeteringCallback()).
        AkSpeakerVolumesMatrixPtr truePeak;

        /// RMS value of each channel in this frame.
        /// Vector of linear rms levels, corresponding to each channel. NULL if AK_EnableBusMeter_RMS is not set (see IAkMixerPluginContext::SetMeteringFlags() or AK::SoundEngine::RegisterBusMeteringCallback()).
        AkSpeakerVolumesMatrixPtr rms;

        /// Mean k-weighted power value in this frame, used to compute loudness (as defined by ITU-R BS.1770).
        /// Total linear k-weighted power of all channels. 0 if AK_EnableBusMeter_KPower is not set (see IAkMixerPluginContext::SetMeteringFlags() or AK::SoundEngine::RegisterBusMeteringCallback()).
        AkReal32 fMeanPowerK;
    } WWISEC_AK_AkMetering;

    typedef AkReal32 WWISEC_AkSampleType; ///< Audio sample data type (32 bit floating point)

    typedef struct WWISEC_AkAudioBuffer
    {
        void* pData;                          ///< Start of the audio buffer.
        struct AkChannelConfig channelConfig; ///< Channel config.
        AKRESULT eState;                      ///< Execution status
        AkUInt16 uMaxFrames;                  ///< Number of sample frames the buffer can hold. Access through AkAudioBuffer::MaxFrames().
        AkUInt16 uValidFrames;                ///< Number of valid sample frames in the audio buffer
    } WWISEC_AkAudioBuffer;

    void WWISEC_AkAudioBuffer_ClearData(WWISEC_AkAudioBuffer* instance);
    void WWISEC_AkAudioBuffer_Clear(WWISEC_AkAudioBuffer* instance);
    AkUInt32 WWISEC_AkAudioBuffer_NumChannels(const WWISEC_AkAudioBuffer* instance);
    bool WWISEC_AkAudioBufer_HasLFE(const WWISEC_AkAudioBuffer* instance);
    struct AkChannelConfig WWISEC_AkAudioBuffer_GetChannelConfig(const WWISEC_AkAudioBuffer* instance);
    void* WWISEC_AkAudioBuffer_GetInterleavedData(WWISEC_AkAudioBuffer* instance);
    void WWISEC_AkAudioBuffer_AttachInterleavedData(WWISEC_AkAudioBuffer* instance, void* in_pData, AkUInt16 in_uMaxFrames, AkUInt16 in_uValidFrames);
    void WWISEC_AkAudioBuffer_AttachInterleavedData1(WWISEC_AkAudioBuffer* instance, void* in_pData, AkUInt16 in_uMaxFrames, AkUInt16 in_uValidFrames, struct AkChannelConfig in_channelConfig);
    bool WWISEC_AkAudioBuffer_HasData(const WWISEC_AkAudioBuffer* instance);
    AkUInt32 WWISEC_AkAudioBuffer_StandardToPipelineIndex(struct AkChannelConfig in_channelConfig, AkUInt32 in_uChannelIdx);
    WWISEC_AkSampleType* WWISEC_AkAudioBuffer_GetChannel(WWISEC_AkAudioBuffer* instance, AkUInt32 in_uIndex);
    WWISEC_AkSampleType* WWISEC_AkAudioBuffer_GetLFE(WWISEC_AkAudioBuffer* instance);
    void WWISEC_AkAudioBuffer_ZeroPadToMaxFrames(WWISEC_AkAudioBuffer* instance);
    void WWISEC_AkAudioBuffer_AttachContiguousDeinterleavedData(WWISEC_AkAudioBuffer* instance, void* in_pData, AkUInt16 in_uMaxFrames, AkUInt16 in_uValidFrames, struct AkChannelConfig in_channelConfig);
    void* WWISEC_AkAudioBuffer_DetachContiguousDeinterleavedData(WWISEC_AkAudioBuffer* instance);
    bool WWISEC_AkAudioBuffer_CheckValidSamples(WWISEC_AkAudioBuffer* instance);
    void WWISEC_AkAudioBuffer_RelocateMedia(WWISEC_AkAudioBuffer* instance, AkUInt8* in_pNewMedia, AkUInt8* in_pOldMedia);
    AkUInt16 WWISEC_AkAudioBuffer_MaxFrames(const WWISEC_AkAudioBuffer* instance);
    // END AkCommonDefs

    typedef struct WWISEC_AK_IAkStreamMgr WWISEC_AK_IAkStreamMgr;
    typedef struct WWISEC_AK_IAkMixerPluginContext WWISEC_AK_IAkMixerPluginContext;
    typedef struct WWISEC_AK_IAkMixerInputContext WWISEC_AK_IAkMixerInputContext;
    typedef struct WWISEC_AK_IAkGlobalPluginContext WWISEC_AK_IAkGlobalPluginContext;
    typedef struct WWISEC_AK_IAkPlugin WWISEC_AK_IAkPlugin;
    typedef struct WWISEC_AK_IAkPluginParam WWISEC_AK_IAkPluginParam;
    typedef struct WWISEC_AK_IAkPluginMemAlloc WWISEC_AK_IAkPluginMemAlloc;

    // BEGIN AkCallbackType
    typedef enum WWISEC_AkCallbackType
    {
        WWISEC_AK_EndOfEvent = 0x0001,               ///< Callback triggered when reaching the end of an event. AkCallbackInfo can be cast to AkEventCallbackInfo.
        WWISEC_AK_EndOfDynamicSequenceItem = 0x0002, ///< Callback triggered when reaching the end of a dynamic sequence item. AkCallbackInfo can be cast to AkDynamicSequenceItemCallbackInfo.
        WWISEC_AK_Marker = 0x0004,                   ///< Callback triggered when encountering a marker during playback. AkCallbackInfo can be cast to AkMarkerCallbackInfo.
        WWISEC_AK_Duration = 0x0008,                 ///< Callback triggered when the duration of the sound is known by the sound engine. AkCallbackInfo can be cast to AkDurationCallbackInfo.
        WWISEC_AK_SpeakerVolumeMatrix = 0x0010,      ///< Callback triggered at each frame, letting the client modify the speaker volume matrix. AkCallbackInfo can be cast to AkSpeakerVolumeMatrixCallbackInfo.
        WWISEC_AK_Starvation = 0x0020,               ///< Callback triggered when playback skips a frame due to stream starvation. AkCallbackInfo can be cast to AkEventCallbackInfo.
        WWISEC_AK_MusicPlaylistSelect = 0x0040,      ///< Callback triggered when music playlist container must select the next item to play. AkCallbackInfo can be cast to AkMusicPlaylistCallbackInfo.
        WWISEC_AK_MusicPlayStarted = 0x0080,         ///< Callback triggered when a "Play" or "Seek" command has been executed ("Seek" commands are issued from AK::SoundEngine::SeekOnEvent()). Applies to objects of the Interactive-Music Hierarchy only. AkCallbackInfo can be cast to AkEventCallbackInfo.
        WWISEC_AK_MusicSyncBeat = 0x0100,            ///< Enable notifications on Music Beat. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncBar = 0x0200,             ///< Enable notifications on Music Bar. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncEntry = 0x0400,           ///< Enable notifications on Music Entry Cue. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncExit = 0x0800,            ///< Enable notifications on Music Exit Cue. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncGrid = 0x1000,            ///< Enable notifications on Music Grid. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncUserCue = 0x2000,         ///< Enable notifications on Music Custom Cue. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MusicSyncPoint = 0x4000,           ///< Enable notifications on Music switch transition synchronization point. AkCallbackInfo can be cast to AkMusicSyncCallbackInfo.
        WWISEC_AK_MIDIEvent = 0x8000,                ///< Enable notifications for MIDI events. AkCallbackInfo can be cast to AkMIDIEventCallbackInfo.
        WWISEC_AK_DynamicSequenceSelect = 0x10000,   ///< Callback triggered when dynamic sequence must select the next item to play. Callback info can be cast to AkDynamicSequenceSelectCallbackInfo.

        WWISEC_AK_Callback_Last = 0x20000, ///< Last calblack unused bit, invalid value.

        // A few useful bitmasks.
        WWISEC_AK_MusicSyncAll = 0x7f00, ///< Use this flag if you want to receive all notifications concerning AK_MusicSync registration.
        WWISEC_AK_CallbackBits = 0xffff, ///< Bitmask for all callback types.

        // Not callback types, but need to be part of same bitfield for AK::SoundEngine::PostEvent().
        WWISEC_AK_EnableGetMusicPlayPosition = 0x200000,     ///< Enable play position information of music objects, queried via AK::MusicEngine::GetPlayingSegmentInfo().
        WWISEC_AK_EnableGetSourceStreamBuffering = 0x400000, ///< Enable stream buffering information for use by AK::SoundEngine::GetSourceStreamBuffering().

        WWISEC_AK_SourceInfo_Last = 0x800000, ///< Last source info enable bit, invalid value.
    } WWISEC_AkCallbackType;

    typedef enum WWISEC_AK_AkAudioDeviceEvent
    {
        WWISEC_AK_AkAudioDeviceEvent_Initialization, ///< Sent after an Audio Device has initialized.  Initialization might have failed, check the AKRESULT.
        WWISEC_AK_AkAudioDeviceEvent_Removal,        ///< Audio device was removed through explicit call (AK::SoundEngine::RemoveOutput or AK::SoundEngine::Term)
        WWISEC_AK_AkAudioDeviceEvent_SystemRemoval,  ///< Audio device was removed because of a system event (disconnection), hardware or driver problem. Check the AKRESULT when called through AkDeviceStatusCallbackFunc, it may give more context.
        WWISEC_AK_AkAudioDeviceEvent_Last            ///< End of enum, invalid value.
    } WWISEC_AK_AkAudioDeviceEvent;

    typedef AkUInt8 WWISEC_AkAudioDeviceEvent_t;

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
        WWISEC_AkGlobalCallbackLocation_ProfilerConnect = (1 << 13),                ///< Wwise Profiler has connected to the game.
        WWISEC_AkGlobalCallbackLocation_ProfilerDisconnect = (1 << 14),             ///< Wwise Profiler has disconnected from the game.
        WWISEC_AkGlobalCallbackLocation_Num = 15                                    ///< Total number of global callback locations.
    } WWISEC_AkGlobalCallbackLocation;

    typedef struct WWISEC_AkSegmentInfo
    {
        AkTimeMs iCurrentPosition;        ///< Current position of the segment, relative to the Entry Cue, in milliseconds. Range is [-iPreEntryDuration, iActiveDuration+iPostExitDuration].
        AkTimeMs iPreEntryDuration;       ///< Duration of the pre-entry region of the segment, in milliseconds.
        AkTimeMs iActiveDuration;         ///< Duration of the active region of the segment (between the Entry and Exit Cues), in milliseconds.
        AkTimeMs iPostExitDuration;       ///< Duration of the post-exit region of the segment, in milliseconds.
        AkTimeMs iRemainingLookAheadTime; ///< Number of milliseconds remaining in the "looking-ahead" state of the segment, when it is silent but streamed tracks are being prefetched.
        AkReal32 fBeatDuration;           ///< Beat Duration in seconds.
        AkReal32 fBarDuration;            ///< Bar Duration in seconds.
        AkReal32 fGridDuration;           ///< Grid duration in seconds.
        AkReal32 fGridOffset;             ///< Grid offset in seconds.
    } WWISEC_AkSegmentInfo;

    typedef struct WWISEC_AkEventCallbackInfo
    {
        AkGameObjectID gameObjID; ///< Game object ID
        AkPlayingID playingID;    ///< Playing ID of Event, returned by PostEvent()
        AkUniqueID eventID;       ///< Unique ID of Event, passed to PostEvent()
    } WWISEC_AkEventCallbackInfo;

    typedef struct WWISEC_AkMIDIEventCallbackInfo
    {
        struct AkMIDIEvent midiEvent; ///< MIDI event triggered by event.
    } WWISEC_AkMIDIEventCallbackInfo;

    typedef struct WWISEC_AkMarkerCallbackInfo
    {
        AkUInt32 uIdentifier; ///< Cue point identifier
        AkUInt32 uPosition;   ///< Position in the cue point (unit: sample frames)
        const char* strLabel; ///< Label of the marker, read from the file
        AkUInt32 uLabelSize;  ///< Size of the label string (including the terminating null character)
    } WWISEC_AkMarkerCallbackInfo;

    typedef struct WWISEC_AkDurationCallbackInfo
    {
        AkReal32 fDuration;          ///< Duration of the sound (unit: milliseconds)
        AkReal32 fEstimatedDuration; ///< Estimated duration of the sound depending on source settings such as pitch. (unit: milliseconds)
        AkUniqueID audioNodeID;      ///< Audio Node ID of playing item
        AkUniqueID mediaID;          ///< Media ID of playing item. (corresponds to 'ID' attribute of 'File' element in SoundBank metadata file)
        bool bStreaming;             ///< True if source is streaming, false otherwise.
    } WWISEC_AkDurationCallbackInfo;

    typedef struct WWISEC_AkDynamicSequenceItemCallbackInfo
    {
        AkUniqueID audioNodeID; ///< Audio Node ID of finished item
        void* pCustomInfo;      ///< Custom info passed to the DynamicSequence::Open function
    } WWISEC_AkDynamicSequenceItemCallbackInfo;

    typedef struct WWISEC_AkSpeakerVolumeMatrixCallbackInfo
    {
        AkSpeakerVolumesMatrixPtr pVolumes;             ///< Pointer to volume matrix describing the contribution of each source channel to destination channels. Use methods of AK::SpeakerVolumes::Matrix to interpret them.
        struct AkChannelConfig inputConfig;             ///< Channel configuration of the voice/bus.
        struct AkChannelConfig outputConfig;            ///< Channel configuration of the output bus.
        AkReal32* pfBaseVolume;                         ///< Base volume, common to all channels.
        AkReal32* pfEmitterListenerVolume;              ///< Emitter-listener pair-specific gain. When there are multiple emitter-listener pairs, this volume is set to that of the loudest pair, and the relative gain of other pairs is applied directly on the channel volume matrix pVolumes.
        WWISEC_AK_IAkMixerInputContext* pContext;       ///< Context of the current voice/bus about to be mixed into the output bus with specified base volume and volume matrix.
        WWISEC_AK_IAkMixerPluginContext* pMixerContext; ///< Output mixing bus context. Use it to access a few useful panning and mixing services, as well as the ID of the output bus. NULL if pContext is the master audio bus.
    } WWISEC_AkSpeakerVolumeMatrixCallbackInfo;

    typedef struct WWISEC_AkMusicPlaylistCallbackInfo
    {
        AkUniqueID playlistID;       ///< ID of playlist node
        AkUInt32 uNumPlaylistItems;  ///< Number of items in playlist node (may be segments or other playlists)
        AkUInt32 uPlaylistSelection; ///< Selection: set by sound engine, modifWWISEC_AkMusicPlaylistCallbackInfoied by callback function (if not in range 0 <= uPlaylistSelection < uNumPlaylistItems then ignored).
        AkUInt32 uPlaylistItemDone;  ///< Playlist node done: set by sound engine, modified by callback function (if set to anything but 0 then the current playlist item is done, and uPlaylistSelection is ignored)
    } WWISEC_AkMusicPlaylistCallbackInfo;

    typedef struct WWISEC_AkMusicSyncCallbackInfo
    {
        WWISEC_AkSegmentInfo segmentInfo;    ///< Segment information corresponding to the segment triggering this callback.
        WWISEC_AkCallbackType musicSyncType; ///< Would be either \ref AK_MusicSyncEntry, \ref AK_MusicSyncBeat, \ref AK_MusicSyncBar, \ref AK_MusicSyncExit, \ref AK_MusicSyncGrid, \ref AK_MusicSyncPoint or \ref AK_MusicSyncUserCue.
        char* pszUserCueName;                ///< Cue name (UTF-8 string). Set for notifications AK_MusicSyncUserCue. NULL if cue has no name.
    } WWISEC_AkMusicSyncCallbackInfo;

    typedef struct WWISEC_AkCallbackInfo
    {
        void* pCookie;            ///< User data, passed to PostEvent()
        AkGameObjectID gameObjID; ///< Game object ID
    } WWISEC_AkCallbackInfo;

    typedef struct WWISEC_AkBusMeteringCallbackInfo
    {
        WWISEC_AkCallbackInfo base;
        WWISEC_AK_AkMetering* pMetering;      ///< Struct containing metering information.
        struct AkChannelConfig channelConfig; ///< Channel configuration of the bus.
        enum AkMeteringFlags eMeteringFlags;  ///< Metering flags that were asked for in RegisterBusMeteringCallback(). You may only access corresponding meter values from in_pMeteringInfo. Others will fail.
    } WWISEC_AkBusMeteringCallbackInfo;

    typedef struct WWISEC_AkOutputDeviceMeteringCallbackInfo
    {
        WWISEC_AkCallbackInfo base;
        WWISEC_AK_AkMetering* pMainMixMetering;             ///< Metering information for the main mix
        struct AkChannelConfig mainMixConfig;               ///< Channel configuration of the main mix
        WWISEC_AK_AkMetering* pPassthroughMetering;         ///< Metering information for the passthrough mix (if any; will be null otherwise)
        struct AkChannelConfig passthroughMixConfig;        ///< Channel configuration of the passthrough mix (if any; will be invalid otherwise)
        AkUInt32 uNumSystemAudioObjects;                    ///< Number of System Audio Objects going out of the output device
        WWISEC_AK_AkMetering** ppSystemAudioObjectMetering; ///< Metering information for each System Audio Object (number of elements is equal to uNumSystemAudioObjects)
        enum AkMeteringFlags eMeteringFlags;                ///< Metering flags that were asked for in RegisterOutputDeviceMeteringCallback(). You may only access corresponding meter values from the metering objects. Others will fail.
    } WWISEC_AkOutputDeviceMeteringCallbackInfo;

    typedef struct WWISEC_AkResourceMonitorDataSummary
    {
        AkReal32 totalCPU;       ///< Pourcentage of the cpu time used for processing audio. Please note that the numbers may add up when using multiple threads.
        AkReal32 pluginCPU;      ///< Pourcentage of the cpu time used by plugin processing. Please note that the numbers may add up when using multiple threads.
        AkUInt32 physicalVoices; ///< Number of active physical voices
        AkUInt32 virtualVoices;  ///< Number of active virtual voices
        AkUInt32 totalVoices;    ///< Number of active physical and virtual voices
        AkUInt32 nbActiveEvents; ///< Number of events triggered at a certain time
    } WWISEC_AkResourceMonitorDataSummary;

    typedef struct WWISEC_AkDynamicSequenceSelectCallbackInfo
    {
        AkUniqueID audioNodeID;                  ///< Unique ID of Audio Node (can be resolved using AK::SoundEngine::DynamicDialogue API). Set to AK_INVALID_UNIQUE_ID to signal that no item is available to play.
        AkTimeMs msDelay;                        ///< Delay before playing this item, in milliseconds
        void* pCustomInfo;                       ///< Optional user data
        AkExternalSourceArray arExternalSources; ///< Optional external sources. Use API described in AkExternalSourceArray.h to add required external sources to play the next item.
    } WWISEC_AkDynamicSequenceSelectCallbackInfo;

    AK_CALLBACK(void, WWISEC_AkEventCallbackFunc)
    (
        WWISEC_AkCallbackType in_eType,
        WWISEC_AkEventCallbackInfo* in_pEventInfo,
        void* in_pCallbackInfo,
        void* in_pCookie);

    typedef WWISEC_AkEventCallbackFunc WWISEC_AkCallbackFunc;

    AK_CALLBACK(void, WWISEC_AkBusCallbackFunc)
    (
        WWISEC_AkSpeakerVolumeMatrixCallbackInfo* in_pCallbackInfo,
        void* in_pCookie);

    AK_CALLBACK(void, WWISEC_AkBankCallbackFunc)
    (
        AkUInt32 in_bankID,
        const void* in_pInMemoryBankPtr,
        AKRESULT in_eLoadResult,
        void* in_pCookie);

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

    AK_CALLBACK(void, WWISEC_AK_AkDeviceStatusCallbackFunc)
    (
        WWISEC_AK_IAkGlobalPluginContext* in_pContext, ///< Engine context.
        AkUniqueID in_idAudioDeviceShareset,           ///< The audio device shareset attached, as passed to AK::SoundEngine::AddOutput or AK::SoundEngine::Init
        AkUInt32 in_idDeviceID,                        ///< The audio device specific id, as passed to AK::SoundEngine::AddOutput or AK::SoundEngine::Init
        WWISEC_AK_AkAudioDeviceEvent in_idEvent,       ///< The event for which this callback was called.  See AK::AkAudioDeviceEvent.  AKRESULT may provide more information.
        AKRESULT in_AkResult                           ///< Result of the last operation.
    );

    AK_CALLBACK(void, WWISEC_AkBusMeteringCallbackFunc)
    (
        WWISEC_AkBusMeteringCallbackInfo* in_pCallbackInfo ///< Structure containing desired bus information.
    );

    AK_CALLBACK(void, WWISEC_AkOutputDeviceMeteringCallbackFunc)
    (
        WWISEC_AkOutputDeviceMeteringCallbackInfo* in_pCallbackInfo ///< Structure containing desired output device information.
    );

    AK_CALLBACK(void, WWISEC_AkCaptureCallbackFunc)
    (
        WWISEC_AkAudioBuffer* in_CaptureBuffer, ///< Capture audio buffer. The data is always float interleaved.
        AkOutputDeviceID in_idOutput,           ///< The audio device specific id, as passed to AK::SoundEngine::AddOutput or AK::SoundEngine::Init
        void* in_pCookie                        ///< Callback cookie that will be sent to the callback function along with additional information
    );
    // END AkCallbackType

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
        WWISEC_AkMemID_TempAudioRender,      ///< Temporary allocations for audio render.
        WWISEC_AkMemID_BookmarkAlloc,        ///< Allocations serviced by the bookmark allocator

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
        AkUInt64 uUsed;     ///< Total memory used including all categories (in bytes)
        AkUInt64 uReserved; ///< Total reserved memory. (Used and unused). Will return 0 if the reserved memory is not traceable.
    } WWISEC_AK_MemoryMgr_GlobalStats;

    bool WWISEC_AK_MemoryMgr_IsInitialized();
    void WWISEC_AK_MemoryMgr_Term();
    void WWISEC_AK_MemoryMgr_InitForThread();
    void WWISEC_AK_MemoryMgr_TermForThread();
    void* WWISEC_AK_MemoryMgr_Malloc(AkMemPoolId in_poolId, size_t in_uSize);
    void* WWISEC_AK_MemoryMgr_ReallocAligned(AkMemPoolId in_poolId, void* in_pAlloc, size_t in_uSize, AkUInt32 in_uAlignment);
    void WWISEC_AK_MemoryMgr_Free(AkMemPoolId in_poolId, void* in_pMemAddress);
    void* WWISEC_AK_MemoryMgr_Malign(AkMemPoolId in_poolId, size_t in_USize, AkUInt32 in_uAlignment);
    void WWISEC_AK_MemoryMgr_GetCategoryStats(AkMemPoolId in_poolId, WWISEC_AK_MemoryMgr_CategoryStats* out_poolStats);
    void WWISEC_AK_MemoryMgr_GetGlobalStats(WWISEC_AK_MemoryMgr_GlobalStats* out_stats);
    void WWISEC_AK_MemoryMgr_StartProfileThreadUsage();
    AkUInt64 WWISEC_AK_MemoryMgr_StopProfileThreadUsage();
    void WWISEC_AK_MemoryMgr_DumpToFile(const AkOSChar* pszFilename);
    // END AkMemoryMgr

    // BEGIN AkTempAllocDefs
    /// Temp-alloc memory statistics. Whenever these are fetched, they represent the last completed temp-alloc "tick".
    /// \remarks These statistics are not collected in the Release configuration of the memory mgr.
    typedef struct WWISEC_AK_TempAlloc_Stats
    {
        AkUInt32 uMemUsed;      ///< Used memory (in bytes).
        AkUInt32 uMemAllocated; ///< Allocated memory (in bytes).
        AkUInt32 uBlocksUsed;   ///< Number of individual blocks used.

        AkUInt32 uPeakMemUsed;      ///< The peak value for uMemUsed since initialization.
        AkUInt32 uPeakMemAllocated; ///< The peak value for uMemAllocated since initialization.
        AkUInt32 uPeakBlocksUsed;   ///< The peak value for uBlocksUsed since initialization.
        AkUInt32 uPeakBlockUsed;    ///< The peak amount of used memory in any single block since initialization.
    } WWISEC_AK_TempAlloc_Stats;

    /// IDs of temporary memory pools used by the sound engine.
    typedef enum WWISEC_AK_TempAlloc_Type
    {
        WWISEC_AK_TempAlloc_Type_AudioRender,
        WWISEC_AK_TempAlloc_Type_NUM, // end of the enum list
    } WWISEC_AK_TempAlloc_Type;

    /// Initialization settings for temporary-memory pools. Separate settings are specified for each temporary-memory pool.
    typedef struct WWISEC_AK_TempAlloc_InitSettings
    {
        AkUInt32 uMinimumBlockCount;   ///< The number of blocks of memory the system is initialized with and is the minimum kept around forever. Defaults to 1. Higher values increase upfront memory use, but can reduce, or eliminate, the creation and destruction of memory blocks over time.
        AkUInt32 uMinimumBlockSize;    ///< The minimum size of each block. If a new allocation requests a new block of memory, then the new block is the size of the requested allocation times four, and then rounded up to the next multiple of this value. Defaults to 2MiB.
        AkUInt32 uMaximumUnusedBlocks; ///< The maximum number of blocks that the system keeps in an unused state, and avoids freeing. Defaults to 1. Higher values do not increase the peak memory use, but do prevent unused memory from being freed, in order to reduce creation and destruction of memory blocks.

        // Various debug options for monitoring and analyzing potential issues in usage of the TempAlloc system. All of these are ignored (treated as disabled) in Release configurations.
        bool bDebugDetailedStats;    ///< Enable to track detailed stats and include them in the detailed stat dump. Detailed stats include the size and quantity of each type of allocation from the system. Disabled by default.
        bool bDebugClearMemory;      ///< Enable to clear any allocation to a deterministic garbage value. Useful to make sure memory is initialized properly. Disabled by default.
        bool bDebugEnableSentinels;  ///< Enable to write out sentinels between most allocations to help detect memory overwrites, verified at the end of a tick. Enabled by default. Increases memory usage of blocks slightly.
        bool bDebugFlushBlocks;      ///< Enable to forcefully release all blocks at the end of a tick and recreate them from scratch every tick. Useful to ensure stale memory is not being accessed. Disabled by default. This might interfere with some stats reporting due to blocks being released between ticks.
        bool bDebugStandaloneAllocs; ///< Enable to force the block size to be as small as possible for each allocation (smaller than can be achieved by just setting uMinimumBlockSize to very low values). Useful to investigate memory overruns in-depth, especially in conjunction with other options like bDebugFlushBlocks and the MemoryMgr's stomp allocator. If enabled, bDebugDetailedStats and bDebugEnableSentinels will be disabled. Greatly increases CPU and memory usage.
    } WWISEC_AK_TempAlloc_InitSettings;

    /// Get simple statistics for a given temporary-memory pool
    void WWISEC_AK_TempAlloc_GetStats(WWISEC_AK_TempAlloc_Type in_eType, WWISEC_AK_TempAlloc_Stats* out_stats);

    /// Get a detailed listing of the allocations into the temp-alloc pool, and output them to a file.
    /// \note TempAllocInitSettings::bTrackDetailedStats must be enabled for the specified type to get detailed information about the underlying allocs. Otherwise, only the simple stats are listed.
    void WWISEC_AK_TempAlloc_DumpTempAllocsToFile(WWISEC_AK_TempAlloc_Type in_eType, const AkOSChar* pszFilename);

    typedef struct WWISEC_AK_BookmarkAlloc_Stats
    {
        AkUInt32 uRecentPeakMemUsed;   ///< Peak used memory in a single BookmarkAlloc region since the last tick (in bytes).
        AkUInt32 uRecentBlocksFetched; ///< Number of times a block was fetched from the cache, not including the base block. High values here may indicate that block sizes need to be larger.
        AkUInt32 uMemAllocated;        ///< Currently allocated memory (in bytes).
        AkUInt32 uBlocksAllocated;     ///< Number of individual blocks currently allocated.

        AkUInt32 uPeakMemUsed;         ///< The peak value for uRecentPeakMemUsed since initialization.
        AkUInt32 uPeakMemAllocated;    ///< The peak value for uMemAllocated since initialization.
        AkUInt32 uPeakBlocksFetched;   ///< The peak value for uRecentBlocksFetched since initialization.
        AkUInt32 uPeakBlocksAllocated; ///< The peak value for uBlocksAllocated since initialization.
        AkUInt32 uPeakBlockSize;       ///< The peak size of any single block since initialization.
    } WWISEC_AK_BookmarkAlloc_Stats;

    /// Initialization settings for Bookmark-allocator memory.
    /// \remarks The debug options are intended for monitoring and analyzing potential issues in usage of the BookmarkAlloc system during development. Their functionality is specifically removed in Release configurations of the AkMemoryMgr.
    typedef struct WWISEC_AK_BookmarkAlloc_InitSettings
    {
        AkUInt32 uMinimumBlockCount;   ///< The number of blocks of memory the system is initialized with and is the minimum kept around forever. Defaults to 1. Higher values increase upfront memory use, but can reduce, or eliminate, the creation and destruction of memory blocks over time.
        AkUInt32 uMinimumBlockSize;    ///< The minimum size of each block. If a new allocation requests a new block of memory, then the new block is the size of the requested allocation times four, and then rounded up to the next multiple of this value. Defaults to 64 KiB.
        AkUInt32 uMaximumUnusedBlocks; ///< The maximum number of blocks that the system keeps in an unused state, and avoids freeing. Defaults to 1. Higher values do not increase the peak memory use, but do prevent unused memory from being freed, in order to reduce creation and destruction of memory blocks.

        bool bDebugDetailedStats;    ///< Enable to track detailed stats, specifically collection of Stats::uRecentPeakMemUsed. Enabled by default.
        bool bDebugClearMemory;      ///< Enable to clear any allocation to a deterministic garbage value during allocs, and after the stack is rewound to a bookmark. Useful to make sure memory is initialized properly. Disabled by default.
        bool bDebugEnableSentinels;  ///< Enable to write out sentinels between most allocations to help detect memory overwrites, which are verified at the termination of a bookmark alloc region. Enabled by default. Increases memory usage of blocks slightly.
        bool bDebugStandaloneAllocs; ///< Enable to force the block size to be as small as possible for each allocation (smaller than can be achieved by just setting uMinimumBlockSize to very low values). Useful to investigate memory overruns in-depth, especially in conjunction with the MemoryMgr's stomp allocator. If enabled, bDebugEnableSentinels will be disabled. Greatly increases CPU and memory usage.
    } WWISEC_AK_BookmarkAlloc_InitSettings;

    /// Get simple statistics for the Bookmark allocator
    void WWISEC_AK_BookmarkAlloc_GetStats(WWISEC_AK_BookmarkAlloc_Stats* out_stats);
    // END AkTempAllocDefs

    // BEGIN AkMemoryArenaTypes
    typedef void*(AKSOUNDENGINE_CALL* WWISEC_AkAllocSpan)(
        size_t in_uSize,
        size_t* out_userData);
    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkFreeSpan)(
        void* in_pAddress,
        size_t in_uSize,
        size_t in_userData);

    typedef struct WWISEC_AK_MemoryArea_AkMemoryArenaSettings
    {
        bool bEnableSba;                 // Used to determine if the SbaHeap should be initialized and utilized at all. If disabled, all small allocs (size < kAllocSizeMedium) will go into the TlsfHeap and be treated as "Medium" allocs.
        AkUInt32 uSbaInitSize;           // the size of the initial allocation of memory for the small block allocator (SBA). This allocation will be made inside the main "tlsf" heap, and will always persist. Sub-allocations that fit in this range will have better fragmentation characteristics, and an overall reduction in memory overhead. This does not have to be a power-of-two.
        AkUInt32 uSbaSpanSize;           // the size of each span of memory for the SBA. Each span has a unique size class. Lower values can slightly increase the overhead of initializing SBA allocations, but can reduce overall memory reservation. This must be a power-of-two.
        AkUInt32 uSbaMaximumUnusedSpans; // The maximum number of SBA spans that the system keeps in an unused state, and avoids freeing. Defaults to 1. Higher values do not increase the peak memory use, but do prevent unused memory from being freed, in order to reduce creation and destruction of SBA spans.

        AkUInt32 uTlsfInitSize;                 // the size of the initial span of memory requested for the main tlsf heap. This span will always persist. (does not have to be a power-of-two)
        AkUInt32 uTlsfSpanSize;                 // when a memory allocation cannot fit in the main tlsf heap, and is a medium-sized allocation, new spans requested will be a multiple of this size (does not have to be a power-of-two)
        AkUInt32 uTlsfLargeSpanSize;            // when a memory allocation cannot fit in the main tlsf heap, and is a large-sized allocation, new spans requested will be a multiple of this size (does not have to be a power-of-two)
        AkUInt32 uTlsfSpanOverhead;             // the amount of allocation 'overhead' assumed for each span. When new spans for Tlsf are requested, this is subtracted from the size of the requested span, after multiplying the requested size up by uPageSize. Defaults to 128.
        AkUInt32 uTlsfMaximumUnusedMediumSpans; // The maximum number of "medium spans" that the system keeps in an unused state, and avoids freeing. Defaults to 1. Higher values do not increase the peak memory use, but do prevent unused memory from being freed, in order to reduce creation and destruction of medium spans.
        AkUInt32 uTlsfMaximumUnusedLargeSpans;  // The maximum number of "large spans" that the system keeps in an unused state, and avoids freeing. Defaults to 1. Higher values do not increase the peak memory use, but do prevent unused memory from being freed, in order to reduce creation and destruction of large spans.

        AkUInt32 uAllocSizeLarge; // defines the minimum size for an allocation to qualify as "Large". Default to UINT_MAX, so that all large allocs are treated as Medium allocs. Large allocs go into best-fit searches, same as medium allocations, but will go to a separate list of secondary spans, distinct from "Medium" allocations
        AkUInt32 uAllocSizeHuge;  // defines the minimum size for an allocation to qualify as "Huge". Huge allocs always go into standalone spans even if there is space available in an existing span

        AkUInt32 uMemReservedLimit; // the limit on how much memory will be reserved by this arena. If a request for to reserve more memory is made that would go over this limit, a nullptr is returned. If set to zero, no limit is in place.

        WWISEC_AkAllocSpan fnMemAllocSpan; // called when the arena needs a new span of memory, including the initial one requested. Set to nullptr to disable initialization of the arena.
        WWISEC_AkFreeSpan fnMemFreeSpan;   // called when the arena is releasing a span of memory
    } WWISEC_AK_MemoryArea_AkMemoryArenaSettings;
    // END AkMemoryArenaTypes

    // BEGIN AkMemoryMgrModule
    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemInitForThread)();

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemTermForThread)();

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemTrimForThread)();

    typedef void*(AKSOUNDENGINE_CALL* WWISEC_AkMemMalloc)(
        AkMemPoolId poolId,
        size_t uSize);

    typedef void*(AKSOUNDENGINE_CALL* WWISEC_AkMemMalign)(
        AkMemPoolId poolId,
        size_t uSize,
        AkUInt32 uAlignment);

    typedef void*(AKSOUNDENGINE_CALL* WWISEC_AkMemRealloc)(
        AkMemPoolId poolId,
        void* pAddress,
        size_t uSize);

    typedef void*(AKSOUNDENGINE_CALL* WWISEC_AkMemReallocAligned)(
        AkMemPoolId poolId,
        void* pAddress,
        size_t uSize,
        AkUInt32 uAlignment);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemFree)(
        AkMemPoolId poolId,
        void* pAddress);

    typedef size_t(AKSOUNDENGINE_CALL* WWISEC_AkMemTotalReservedMemorySize)();

    typedef size_t(AKSOUNDENGINE_CALL* WWISEC_AkMemSizeOfMemory)(
        AkMemPoolId poolId,
        void* pAddress);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemDebugMalloc)(
        AkMemPoolId poolId,
        size_t uSize,
        void* pAddress,
        char const* pszFile,
        AkUInt32 uLine);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemDebugMalign)(
        AkMemPoolId poolId,
        size_t uSize,
        AkUInt32 uAlignment,
        void* pAddress,
        char const* pszFile,
        AkUInt32 uLine);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemDebugRealloc)(
        AkMemPoolId poolId,
        void* pOldAddress,
        size_t uSize,
        void* pNewAddress,
        char const* pszFile,
        AkUInt32 uLine);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemDebugReallocAligned)(
        AkMemPoolId poolId,
        void* pOldAddress,
        size_t uSize,
        AkUInt32 uAlignment,
        void* pNewAddress,
        char const* pszFile,
        AkUInt32 uLine);

    typedef void(AKSOUNDENGINE_CALL* WWISEC_AkMemDebugFree)(
        AkMemPoolId poolId,
        void* pAddress);

    // Listing of every memory arena used by the AkMemoryMgr, when using default AkMemoryMgr systems in Wwise
    typedef enum WWISEC_AkMemoryMgrArena
    {
        WWISEC_AkMemoryMgrArena_Primary = 0,
        WWISEC_AkMemoryMgrArena_Media,
        WWISEC_AkMemoryMgrArena_Profiler, // "Profiler" arena will not be available in AK_OPTIMIZED (e.g. "Release") builds
        WWISEC_AkMemoryMgrArena_Device,   // "Device" arena will only be available on platforms that use device memory for voice decoding
        WWISEC_AkMemoryMgrArena_NUM,
    } WWISEC_AkMemoryMgrArena;

    typedef struct WWISEC_AK_MemoryArea_AkMemoryArea WWISEC_AK_MemoryArea_AkMemoryArea;
    typedef struct WWISEC_AkMemSettings
    {
        /// @name High-level memory allocation hooks. When not NULL, redirect allocations normally forwarded to rpmalloc.
        //@{
        WWISEC_AkMemInitForThread pfInitForThread;                     ///< (Optional) Thread-specific allocator initialization hook.
        WWISEC_AkMemTermForThread pfTermForThread;                     ///< (Optional) Thread-specific allocator termination hook.
        WWISEC_AkMemTrimForThread pfTrimForThread;                     ///< (Optional) Thread-specific allocator "trimming" hook.
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
        WWISEC_AK_MemoryArea_AkMemoryArenaSettings memoryAreaSettings[WWISEC_AkMemoryMgrArena_NUM];
        WWISEC_AK_TempAlloc_InitSettings tempAllocSettings[WWISEC_AK_TempAlloc_Type_NUM];
        WWISEC_AK_BookmarkAlloc_InitSettings bookmarkAllocSettings;
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
    } WWISEC_AkMemSettings;

    AKRESULT WWISEC_AK_MemoryMgr_Init(WWISEC_AkMemSettings* in_pSettings);
    void WWISEC_AK_MemoryMgr_GetDefaultSettings(WWISEC_AkMemSettings* out_pMemSettings);

    void WWISEC_AK_MemoryMgr_VerifyMemoryArenaIntegrity(WWISEC_AkMemoryMgrArena in_eArena);
    WWISEC_AK_MemoryArea_AkMemoryArea* WWISEC_AK_MemoryMgr_GetMemoryArena(WWISEC_AkMemoryMgrArena in_eArena);
    // END AkMemoryMgrModule

    // BEGIN Platform-specific (Ak*SoundEngine and AkPlatformFunc)
    typedef struct WWISEC_WIN_AkThreadProperties
    {
        int nPriority;           ///< Thread priority
        AkUInt32 dwAffinityMask; ///< Affinity mask
        AkUInt32 uStackSize;     ///< Thread stack size.
    } WWISEC_WIN_AkThreadProperties;

    typedef struct WWISEC_WIN_AkPlatformInitSettings
    {
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
        AkDataTypeID sampleType;          ///< Sample type. AK_FLOAT for 32 bit float, AK_INT for 16 bit signed integer, defaults to AK_FLOAT.
                                          ///< Supported by AkAPI_PulseAudio only.
    } WWISEC_LINUX_AkPlatformInitSettings;

    typedef enum WWISEC_AkAudioAPIMac
    {
        WWISEC_AkAudioAPIMac_AVAudioEngine = 1 << 0,                                                        ///< Use AVFoundation framework (modern, has more capabilities, available only for macOS 10.15 or above)
        WWISEC_AkAudioAPIMac_AudioUnit = 1 << 1,                                                            ///< Use AudioUnit framework (basic functionality, compatible with all macOS devices)
        WWISEC_AkAudioAPIMac_Default = WWISEC_AkAudioAPIMac_AVAudioEngine | WWISEC_AkAudioAPIMac_AudioUnit, ///< Default value, will select the more appropriate API (AVAudioEngine for compatible devices, AudioUnit for others)
    } WWISEC_AkAudioAPIMac;

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
        WWISEC_AkAudioAPIMac eAudioAPI;
        AkUInt32 uNumSpatialAudioPointSources;
        bool bVerboseSystemOutput;
    } WWISEC_MACOSX_AkPlatformInitSettings;

    /// \cond !(Web)
    ///< API used for audio output
    ///< Use with AkPlatformInitSettings to select the API used for audio output.
    ///< Use AkAudioAPI_Default, it will select the more appropriate API depending on the computer's capabilities.  Other values should be used for testing purposes.
    ///< \sa AK::SoundEngine::Init
    typedef enum WWISEC_AkAudioAPIAndroid
    {
        WWISEC_AkAudioAPIAndroid_AAudio = 1 << 0,                                                                ///< Use AAudio (lower latency, available only for Android 8.1 or above)
        WWISEC_AkAudioAPIAndroid_OpenSL_ES = 1 << 1,                                                             ///< Use OpenSL ES (older API, compatible with all Android devices)
        WWISEC_AkAudioAPIAndroid_Default = WWISEC_AkAudioAPIAndroid_AAudio | WWISEC_AkAudioAPIAndroid_OpenSL_ES, ///< Default value, will select the more appropriate API (AAudio for compatible devices, OpenSL for others)
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
        bool bEnableLowLatency; ///< Use a low latency audio path for the current hardware.
                                /// If true (default), the output audio device will be initialized in low-latency operation, allowing for more responsive audio playback on most devices. However, when operating in low-latency mode, some devices may have differences in audio reproduction.
                                /// If false, the output audio device will be initialized without low-latency operation.

        // When bEnableLowLatency is set to true, this dictates whether the AAudio stream should be opened in exclusive mode.
        // This mode bypasses the system audio mixer for best latency.
        // When available, this mode gives the best latency. However, it has several drawbacks to be aware of:
        // - App audio will not be mixed with other apps. Other apps will be prevented from using exclusive mode while this output stream is active.
        // - Screen recordings may not contain any audio.
        // - When the app is put in the background, there is a possibility that another app 'steals' this path. When the Wwise app comes back to the foreground, this mode can become unavailable.
        // - Audio will bypass system-level DSP effects like volume normalization and spatialization. 3D Audio will not work, and output volume may be abnormally loud or quiet.
        // - Other functionality such as audio recording may be disabled when using this path.
        //
        // This setting has no effect when bEnableLowLatency is set to FALSE.
        // For backward-compatibility reasons, this setting is TRUE by default. But it is recommended to turn it off if any audio output problem arises on certain device models.
        bool bEnableExclusiveMode;
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

    /// The IDs of the iOS audio session route sharing policies, which determine which audio routes are permitted for the audio session controlled by Wwise. These policies only apply for the "Playback" audio session category. These IDs are funtionally equivalent to the corresponding constants defined by the iOS audio session service backend (AVAudioSession). Refer to Xcode documentation for details on the audio session route-sharing policies. The original prefix "AV" is replaced with "Ak" for the ID names.
    typedef enum WWISEC_IOS_AkAudioSessionRouteSharingPolicy
    {
        WWISEC_IOS_AkAudioSessionRouteSharingPolicyDefault = 0,       ///< Corresponds to AVAudioSessionRouteSharingPolicyDefault
        WWISEC_IOS_AkAudioSessionRouteSharingPolicyLongFormAudio = 1, ///< Corresponds to AVAudioSessionRouteSharingPolicyLongFormAudio
        WWISEC_IOS_AkAudioSessionRouteSharingPolicyLongFormVideo = 3, ///< Corresponds to AVAudioSessionRouteSharingPolicyLongFormVideo
        WWISEC_IOS_AkAudioSessionRouteSharingPolicy_Last,             ///< End of enum, invalid value.
    } WWISEC_IOS_AkAudioSessionRouteSharingPolicy;

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
        WWISEC_IOS_AkAudioSessionCategory eCategory;               ///< \sa AkAudioSessionCategory
        WWISEC_IOS_AkAudioSessionCategoryOptions eCategoryOptions; ///< \sa AkAudioSessionCategoryOptions
        WWISEC_IOS_AkAudioSessionMode eMode;                       ///< \sa AkAudioSessionMode
        WWISEC_IOS_AkAudioSessionRouteSharingPolicy eRouteSharingPolicy;
        WWISEC_IOS_AkAudioSessionSetActiveOptions eSetActivateOptions;  ///< \sa AkAudioSessionSetActiveOptions
        WWISEC_IOS_AkAudioSessionBehaviorOptions eAudioSessionBehavior; ///< Flags to change the default Sound Engine behavior related to the management of the iOS Audio Session with regards to application lifecycle events. \sa AkAudioSessionBehaviorFlags
    } WWISEC_IOS_AkAudioSessionProperties;

    typedef enum WWISEC_AkAudioAPIiOS
    {
        WWISEC_AkAudioAPIiOS_AVAudioEngine = 1 << 0,                                                        ///< Use AVFoundation framework (modern, has more capabilities, available only for iOS/tvOS 13 or above)
        WWISEC_AkAudioAPIiOS_AudioUnit = 1 << 1,                                                            ///< Use AudioUnit framework (basic functionality, compatible with all iOS devices)
        WWISEC_AkAudioAPIiOS_Default = WWISEC_AkAudioAPIiOS_AVAudioEngine | WWISEC_AkAudioAPIiOS_AudioUnit, ///< Default value, will select the more appropriate API (AVAudioEngine for compatible devices, AudioUnit for others)
    } WWISEC_AkAudioAPIiOS;

#define WWISEC_AKMOTION_RESIDENT_MODE (0x80000000)

    typedef struct WWISEC_AudioBufferList WWISEC_AudioBufferList;

    /// iOS-only callback function prototype used for audio input source plugin. Implement this function to transfer the
    /// input sample data to the sound engine and perform brief custom processing.
    /// \remark See the remarks of \ref AkGlobalCallbackFunc.
    ///
    /// \sa
    /// - \ref AkPlatformInitSettings
    typedef AKRESULT (*WWISEC_IOS_AudioInputCallbackFunc)(
        const WWISEC_AudioBufferList* io_Data, ///< An exposed CoreAudio structure that holds the input audio samples generated from
                                               ///< audio input hardware. The buffer is pre-allocated by the sound engine and the buffer
                                               ///< size can be obtained from the structure. Refer to the microphone demo of the IntegrationDemo for an example of usage.
        void* in_pCookie                       ///< User-provided data, e.g., a user structure.
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

        WWISEC_AkAudioAPIiOS eAudioAPI; ///< Main audio API to use. Leave to AkAPI_Default for the default sink (default value).

        AkUInt32 uNumSpatialAudioPointSources; ///< Number of Apple Spatial Audio point sources to allocate for 3D audio use (each point source is a system audio object). Default: 128

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
    AK_CALLBACK(AKRESULT, WWISEC_AkGetDeviceListCallback)
    (
        AkUInt32* io_maxNumDevices,                        ///< In: The length of the out_deviceDescriptions array, or zero is out_deviceDescriptions is null. Out: If out_deviceDescriptions is not-null, this should be set to the number of entries in out_deviceDescriptions that was populated (and should be less-than-or-equal to the initial value). If out_deviceDescriptions is null, this should be set to the maximum number of devices that may be returned by this callback.
        struct AkDeviceDescription* out_deviceDescriptions ///< The output array of device descriptions. If this is not-null, there will be a number of entries equal to the input value of io_maxNumDevices.
    );

    typedef enum WWISEC_AK_AkPluginServiceType
    {
        WWISEC_AK_PluginServiceType_Mixer = 0,
        WWISEC_AK_PluginServiceType_RNG = 1,
        WWISEC_AK_PluginServiceType_AudioObjectAttenuation = 2,
        WWISEC_AK_PluginServiceType_AudioObjectPriority = 3,
        WWISEC_AK_PluginServiceType_HashTable = 4,
        WWISEC_AK_PluginServiceType_Markers = 5,
        WWISEC_AK_PluginServiceType_TempAlloc = 6,
        WWISEC_AK_PluginServiceType_MAX,
    } WWISEC_AK_AkPluginServiceType;

    WWISEC_AK_IAkStreamMgr* WWISEC_AK_IAkGlobalPluginContext_GetStreamMgr(const WWISEC_AK_IAkGlobalPluginContext* self);
    AkUInt16 WWISEC_AK_IAkGlobalPluginContext_GetMaxBufferLength(const WWISEC_AK_IAkGlobalPluginContext* self);
    bool WWISEC_AK_IAkGlobalPluginContext_IsRenderingOffline(const WWISEC_AK_IAkGlobalPluginContext* self);
    AkUInt32 WWISEC_AK_IAkGlobalPluginContext_GetSampleRate(const WWISEC_AK_IAkGlobalPluginContext* self);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_PostMonitorMessage(WWISEC_AK_IAkGlobalPluginContext* self, const char* in_pszError, WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterPlugin(WWISEC_AK_IAkGlobalPluginContext* self, enum AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreatePluginCallback in_pCreateFunc, WWISEC_AkCreateParamCallback in_pCreateParamFunc);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterCodec(WWISEC_AK_IAkGlobalPluginContext* self, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreateFileSourceCallback in_pFileCreateFunc, WWISEC_AkCreateBankSourceCallback in_pBankCreateFunc);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterGlobalCallback(WWISEC_AK_IAkGlobalPluginContext* self, enum AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation, void* in_pCookie);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_UnregisterGlobalCallback(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation);
    WWISEC_AK_IAkPluginMemAlloc* WWISEC_AK_IAkGlobalPluginContext_GetAllocator(WWISEC_AK_IAkGlobalPluginContext* self);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_SetRTPCValue(WWISEC_AK_IAkGlobalPluginContext* self, AkRtpcID in_rtpcID, AkRtpcValue in_value, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_SendPluginCustomGameData(WWISEC_AK_IAkGlobalPluginContext* self, AkUniqueID in_busID, AkGameObjectID in_busObjectID, enum AkPluginType in_eType, AkUInt32 in_uCompanyID, AkUInt32 in_uPluginID, const void* in_pData, AkUInt32 in_uSizeInBytes);
    void WWISEC_AK_IAkGlobalPluginContext_ComputeAmbisonicsEncoding(WWISEC_AK_IAkGlobalPluginContext* self, AkReal32 in_fAzimuth, AkReal32 in_fElevation, struct AkChannelConfig in_cfgAmbisonics, AkSpeakerVolumesMatrixPtr out_vVolumes);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_ComputeWeightedAmbisonicsDecodingFromSampledSphere(WWISEC_AK_IAkGlobalPluginContext* self, const struct AkVector* in_samples, AkUInt32 in_uNumSamples, struct AkChannelConfig in_cfgAmbisonics, AkSpeakerVolumesMatrixPtr out_mxVolume);
    const WWISEC_AkAcousticTexture* WWISEC_AK_IAkGlobalPluginContext_GetAcousticTexture(WWISEC_AK_IAkGlobalPluginContext* self, AkAcousticTextureID in_AcousticTextureID);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_ComputeSphericalCoordinates(const WWISEC_AK_IAkGlobalPluginContext* self, const WWISEC_AkEmitterListenerPair* in_pair, AkReal32* out_fAzimuth, AkReal32* out_fElevation);
    const WWISEC_AkPlatformInitSettings* WWISEC_AK_IAkGlobalPluginContext_GetPlatformInitSettings(const WWISEC_AK_IAkGlobalPluginContext* self);
    const WWISEC_AkInitSettings* WWISEC_AK_IAkGlobalPluginContext_GetInitSettings(const WWISEC_AK_IAkGlobalPluginContext* self);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_GetAudioSettings(const WWISEC_AK_IAkGlobalPluginContext* self, struct AkAudioSettings* out_audioSettings);
    AkUInt32 WWISEC_AK_IAkGlobalPluginContext_GetIDFromString(const WWISEC_AK_IAkGlobalPluginContext* self, const char* in_pszString);
    AkPlayingID WWISEC_AK_IAkGlobalPluginContext_PostEventSync(WWISEC_AK_IAkGlobalPluginContext* self, AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, struct AkExternalSourceInfo* in_pExternalSources, AkPlayingID in_PlayingID);
    AkPlayingID WWISEC_AK_IAkGlobalPluginContext_PostMIDIOnEventSync(WWISEC_AK_IAkGlobalPluginContext* self, AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, struct AkMIDIPost* in_pPosts, AkUInt16 in_uNumPosts, bool in_bAbsoluteOffsets, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkPlayingID in_playingID);
    AKRESULT WWISEC_AK_IAkGlobalPluginContext_StopMIDIOnEventSync(WWISEC_AK_IAkGlobalPluginContext* self, AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkPlayingID in_playingID);
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

    typedef AKRESULT (*WWISEC_AkBackgroundMusicChangeCallbackFunc)(
        bool in_bBackgroundMusicMuted, ///< Flag indicating whether the busses tagged as "background music" in the project are muted or not.
        void* in_pCookie               ///< User-provided data, e.g. a user structure.
    );

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
        AkJobType in_jobType,
        AkUInt32 in_uExecutionTimeUsec);

    AK_CALLBACK(void, WWISEC_AkJobMgrSettings_FuncRequestJobWorker)
    (
        WWISEC_AkJobWorkerFunc in_fnJobWorker, ///< Function passed to host runtime that should be executed. Note that the function provided will exist for as long as the soundengine code is loaded, and will always be the same.
        AkJobType in_jobType,                  ///< The type of job worker that has been requested. This should be passed forward to in_fnJobWorker
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
        AkPluginID in_uPluginID,
        const char* in_pszZoneName);

    /// External (optional) function for tracking performance of the sound engine that is called when a timer stops. (only called in Debug and Profile binaries; this is not called in Release)
    AK_CALLBACK(void, WWISEC_AkProfilerPopTimerFunc)
    ();

    ///< External (optional) function for tracking notable events in the sound engine, to act as a marker or bookmark. (only called in Debug and Profile binaries; this is not called in Release)
    /// in_uPluginID may be non-zero when this function is called, to provide extra data about what context this Marker was posted in.
    /// in_pszMarkerName will point to a static string, so the pointer can be stored for later use, not just the contents of the string itself.
    AK_CALLBACK(void, WWISEC_AkProfilerPostMarkerFunc)
    (
        AkPluginID in_uPluginID,
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

        struct AkOutputSettings settingsMainOutput; ///< Main output device settings.
        WWISEC_AkJobMgrSettings settingsJobManager; ///< Settings to configure the behavior of the Sound Engine's internal job manager

        AkUInt32 uMaxHardwareTimeoutMs; ///< Amount of time to wait for HW devices to trigger an audio interrupt. If there is no interrupt after that time, the sound engine will revert to  silent mode and continue operating until the HW finally comes back. Default value: 2000 (2 seconds)

        bool bUseSoundBankMgrThread; ///< Use a separate thread for loading sound banks. Allows asynchronous operations.
        bool bUseLEngineThread;      ///< Use a separate thread for processing audio. If set to false, audio processing will occur in RenderAudio(). \ref goingfurther_eventmgrthread

        WWISEC_AkBackgroundMusicChangeCallbackFunc BGMCallback; ///< Application-defined audio source change event callback function.
        void* BGMCallbackCookie;                                ///< Application-defined user data for the audio source change event callback function.
        const AkOSChar* szPluginDLLPath;                        ///< When using DLLs for plugins, specify their path. Leave NULL if DLLs are in the same folder as the game executable.

        WWISEC_AkFloorPlane eFloorPlane; ///< Define the orientation of the the floor plane with respect to the X,Y,Z axes, and which axes represent the side, front and up vectors as a basis for rotations in Wwise.
                                         ///< AkFloorPlane is used in to orient the Game Object 3D Viewer in Wwise, and in the transformation of geometry instances in Wwise Spatial Audio.

        AkReal32 fGameUnitsToMeters; ///< The number of game units in a meter.
                                     ///< This setting is used to adapt the size of elements in the Authoring's Game Object 3D Viewer and Audio Object 3D Viewer to meters.
                                     ///< This setting is also used to simulate real-world positioning of System Audio Objects, to improve the HRTF in some cases.

        AkUInt32 uBankReadBufferSize; ///< The number of bytes read by the BankReader when new data needs to be loaded from disk during serialization. Increasing this trades memory usage for larger, but fewer, file-read events during bank loading.

        AkReal32 fDebugOutOfRangeLimit; ///< Debug setting: Only used when bDebugOutOfRangeCheckEnabled is true.  This defines the maximum values samples can have.  Normal audio must be contained within +1/-1.  This limit should be set higher to allow temporary or short excursions out of range.  Default is 16.

        bool bDebugOutOfRangeCheckEnabled; ///< Debug setting: Enable checks for out-of-range (and NAN) floats in the processing code.  This incurs a small performance hit, but can be enabled in most scenarios.  Will print error messages in the log if invalid values are found at various point in the pipeline. Contact AK Support with the new error messages for more information.

        bool bOfflineRendering; ///< Enables/disables offline rendering. \ref goingfurther_offlinerendering

        WWISEC_AkProfilerPushTimerFunc fnProfilerPushTimer;   ///< External (optional) function for tracking performance of the sound engine that is called when a timer starts. (only called in Debug and Profile binaries; this is not called in Release)
        WWISEC_AkProfilerPopTimerFunc fnProfilerPopTimer;     ///< External (optional) function for tracking performance of the sound engine that is called when a timer stops. (only called in Debug and Profile binaries; this is not called in Release)
        WWISEC_AkProfilerPostMarkerFunc fnProfilerPostMarker; ///< External (optional) function for tracking significant events in the sound engine, to act as a marker or bookmark. (only called in Debug and Profile binaries; this is not called in Release)
    } WWISEC_AkInitSettings;

    typedef struct WWISEC_AkSourceSettings
    {
        AkUniqueID sourceID;   ///< Source ID (available in the SoundBank content files)
        AkUInt8* pMediaMemory; ///< Pointer to the data to be set for the source
        AkUInt32 uMediaSize;   ///< Size, in bytes, of the data to be set for the source
    } WWISEC_AkSourceSettings;

    typedef struct WWISEC_AkSourcePosition
    {
        AkUniqueID audioNodeID;    ///< Audio Node ID of playing item
        AkUniqueID mediaID;        ///< Media ID of playing item. (corresponds to 'ID' attribute of 'File' element in SoundBank metadata file)
        AkTimeMs msTime;           ///< Position of the source (in ms) associated with that playing item
        AkUInt32 samplePosition;   ///< Position of the source (in samples) associated with that playing item
        AkUInt32 updateBufferTick; ///< Value of GetBufferTick() at the time the position was updated
    } WWISEC_AkSourcePosition;

    typedef enum WWISEC_AK_SoundEngine_PreparationType
    {
        WWISEC_AK_SoundEngine_Preparation_Load,          ///< \c PrepareEvent() will load required information to play the specified event.
        WWISEC_AK_SoundEngine_Preparation_Unload,        ///< \c PrepareEvent() will unload required information to play the specified event.
        WWISEC_AK_SoundEngine_Preparation_LoadAndDecode, ///< Vorbis media is decoded when loading, and an uncompressed PCM version is used for playback.
        WWISEC_AK_SoundEngine_Preparation_Last
    } WWISEC_AK_SoundEngine_PreparationType;

    typedef enum WWISEC_AK_SoundEngine_AkBankContent
    {
        WWISEC_AK_SoundEngine_AkBankContent_StructureOnly, ///< Use AkBankContent_StructureOnly to load only the structural content, including Events, and then later use the PrepareEvent() functions to load media on demand from loose files on the disk.
        WWISEC_AK_SoundEngine_AkBankContent_All,           ///< Use AkBankContent_All to load both the media and structural content.
        WWISEC_AK_SoundEngine_AkBankContent_Last
    } WWISEC_AK_SoundEngine_AkBankContent;

    bool WWISEC_AK_SoundEngine_IsInitialized();

    AKRESULT WWISEC_AK_SoundEngine_Init(WWISEC_AkInitSettings* in_pSettings, WWISEC_AkPlatformInitSettings* in_pPlatformSettings);

    void WWISEC_AK_SoundEngine_GetDefaultInitSettings(WWISEC_AkInitSettings* out_settings);

    void WWISEC_AK_SoundEngine_GetDefaultPlatformInitSettings(WWISEC_AkPlatformInitSettings* out_platformSettings);

    void WWISEC_AK_SoundEngine_Term();

    AKRESULT WWISEC_AK_SoundEngine_GetAudioSettings(struct AkAudioSettings* out_audioSettings);

    struct AkChannelConfig WWISEC_AK_SoundEngine_GetSpeakerConfiguration(AkOutputDeviceID in_idOutput);

    AKRESULT WWISEC_AK_SoundEngine_GetOutputDeviceConfiguration(AkOutputDeviceID in_idOutput, struct AkChannelConfig* io_channelConfig, struct Ak3DAudioSinkCapabilities* io_capabilities);

    AKRESULT WWISEC_AK_SoundEngine_GetPanningRule(enum AkPanningRule* out_ePanningRule, AkOutputDeviceID in_idOutput);

    AKRESULT WWISEC_AK_SoundEngine_SetPanningRule(enum AkPanningRule in_ePanningRule, AkOutputDeviceID in_idOutput);

    AKRESULT WWISEC_AK_SoundEngine_GetSpeakerAngles(AkReal32* io_pfSpeakerAngles, AkUInt32* io_uNumAngles, AkReal32* out_fHeightAngle, AkOutputDeviceID in_idOutput);

    AKRESULT WWISEC_AK_SoundEngine_SetSpeakerAngles(const AkReal32* in_pfSpeakerAngles, AkUInt32 in_uNumAngles, AkReal32 in_fHeightAngle, AkOutputDeviceID in_idOutput);

    AKRESULT WWISEC_AK_SoundEngine_SetVolumeThreshold(AkReal32 in_fVolumeThresholdDB);

    AKRESULT WWISEC_AK_SoundEngine_SetMaxNumVoicesLimit(AkUInt16 in_maxNumberVoices);

    AKRESULT WWISEC_AK_SoundEngine_SetJobMgrMaxActiveWorkers(AkJobType in_jobType, AkUInt32 in_uNewMaxActiveWorkers);

    AKRESULT WWISEC_AK_SoundEngine_RenderAudio(bool in_bAllowSyncRender);

    WWISEC_AK_IAkGlobalPluginContext* WWISEC_AK_SoundEngine_GetGlobalPluginContext();

    AKRESULT WWISEC_AK_SoundEngine_RegisterPlugin(enum AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreatePluginCallback in_pCreateFunc, WWISEC_AkCreateParamCallback in_pCreateParamFunc);

    AKRESULT WWISEC_AK_SoundEngine_RegisterPluginDLL(const AkOSChar* in_DllName, const AkOSChar* in_DllPath);

    bool WWISEC_AK_SoundEngine_IsPluginRegistered(enum AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID);

    AKRESULT WWISEC_AK_SoundEngine_RegisterGlobalCallback(WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation, void* in_pCookie, enum AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID);

    AKRESULT WWISEC_AK_SoundEngine_UnregisterGlobalCallback(WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation);

    AKRESULT WWISEC_AK_SoundEngine_RegisterResourceMonitorCallback(WWISEC_AkResourceMonitorCallbackFunc in_pCallback);

    AKRESULT WWISEC_AK_SoundEngine_UnregisterResourceMonitorCallback(WWISEC_AkResourceMonitorCallbackFunc in_pCallback);

    AKRESULT WWISEC_AK_SoundEngine_RegisterAudioDeviceStatusCallback(WWISEC_AK_AkDeviceStatusCallbackFunc in_pCallback);

    AKRESULT WWISEC_AK_SoundEngine_UnregisterAudioDeviceStatusCallback();

    AkUInt32 WWISEC_AK_SoundEngine_GetIDFromString(const char* in_pszString);

    AkPlayingID WWISEC_AK_SoundEngine_PostEvent_ID(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, struct AkExternalSourceInfo* in_pExternalSources, AkPlayingID in_PlayingID);

    AkPlayingID WWISEC_AK_SoundEngine_PostEvent_String(const char* in_pszEventName, AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, struct AkExternalSourceInfo* in_pExternalSources, AkPlayingID in_PlayingID);

    AKRESULT WWISEC_AK_SoundEngine_ExecuteActionOnEvent_ID(AkUniqueID in_eventID, enum AkActionOnEventType in_ActionType, AkGameObjectID in_gameObjectID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve, AkPlayingID in_PlayingID);

    AKRESULT WWISEC_AK_SoundEngine_ExecuteActionOnEvent_String(const char* in_pszEventName, enum AkActionOnEventType in_ActionType, AkGameObjectID in_gameObjectID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve, AkPlayingID in_PlayingID);

    AkPlayingID WWISEC_AK_SoundEngine_PostMIDIOnEvent(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, struct AkMIDIPost* in_pPosts, AkUInt16 in_uNumPosts, bool in_bAbsoluteOffsets, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkPlayingID in_playingID);

    AKRESULT WWISEC_AK_SoundEngine_StopMIDIOnEvent(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkPlayingID in_playingID);

    AKRESULT WWISEC_AK_SoundEngine_PinEventInStreamCache_ID(AkUniqueID in_eventID, AkPriority in_uActivePriority, AkPriority in_uInactivePriority);

    AKRESULT WWISEC_AK_SoundEngine_PinEventInStreamCache_String(const char* in_pszEventName, AkPriority in_uActivePriority, AkPriority in_uInactivePriority);

    AKRESULT WWISEC_AK_SoundEngine_UnpinEventInStreamCache_ID(AkUniqueID in_eventID);

    AKRESULT WWISEC_AK_SoundEngine_UnpinEventInStreamCache_String(const char* in_pszEventName);

    AKRESULT WWISEC_AK_SoundEngine_GetBufferStatusForPinnedEvent_ID(AkUniqueID in_eventID, AkReal32* out_fPercentBuffered, bool* out_bCachePinnedMemoryFull);

    AKRESULT WWISEC_AK_SoundEngine_GetBufferStatusForPinnedEvent_String(const char* in_pszEventName, AkReal32* out_fPercentBuffered, bool* out_bCachePinnedMemoryFull);

    AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Time_ID(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkTimeMs in_iPosition, bool in_bSeekToNearestMarker, AkPlayingID in_PlayingID);

    AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Time_String(const char* in_pszEventName, AkGameObjectID in_gameObjectID, AkTimeMs in_iPosition, bool in_bSeekToNearestMarker, AkPlayingID in_PlayingID);

    AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Percent_ID(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker, AkPlayingID in_PlayingID);

    AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Percent_String(const char* in_pszEventName, AkGameObjectID in_gameObjectID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker, AkPlayingID in_PlayingID);

    void WWISEC_AK_SoundEngine_CancelEventCallbackCookie(void* in_pCookie);

    void WWISEC_AK_SoundEngine_CancelEventCallbackGameObject(AkGameObjectID in_gameObjectID);

    void WWISEC_AK_SoundEngine_CancelEventCallback(AkPlayingID in_playingID);

    AKRESULT WWISEC_AK_SoundEngine_GetSourcePlayPosition(AkPlayingID in_PlayingID, AkTimeMs* out_puPosition, bool in_bExtrapolate);

    AKRESULT WWISEC_AK_SoundEngine_GetSourcePlayPositions(AkPlayingID in_PlayingID, WWISEC_AkSourcePosition* out_puPositions, AkUInt32* io_pcPositions, bool in_bExtrapolate);

    AKRESULT WWISEC_AK_SoundEngine_GetSourceStreamBuffering(AkPlayingID in_PlayingID, AkTimeMs* out_buffering, bool* out_bIsBuffering);

    void WWISEC_AK_SoundEngine_StopAll(AkGameObjectID in_gameObjectID);

    void WWISEC_AK_SoundEngine_StopPlayingID(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve);

    void WWISEC_AK_SoundEngine_ExecuteActionOnPlayingID(enum AkActionOnEventType in_ActionType, AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve);

    void WWISEC_AK_SoundEngine_SetRandomSeed(AkUInt32 in_uSeed);

    void WWISEC_AK_SoundEngine_MuteBackgroundMusic(bool in_bMute);

    bool WWISEC_AK_SoundEngine_GetBackgroundMusicMute();

    AKRESULT WWISEC_AK_SoundEngine_SendPluginCustomGameData(AkUniqueID in_busID, AkGameObjectID in_busObjectID, enum AkPluginType in_eType, AkUInt32 in_uCompanyID, AkUInt32 in_uPluginID, const void* in_pData, AkUInt32 in_uSizeInBytes);

    AKRESULT WWISEC_AK_SoundEngine_RegisterGameObj(AkGameObjectID in_gameObjectID);

    AKRESULT WWISEC_AK_SoundEngine_RegisterGameObjWithName(AkGameObjectID in_gameObjectID, const char* in_pszObjName);

    AKRESULT WWISEC_AK_SoundEngine_UnregisterGameObj(AkGameObjectID in_gameObjectID);

    AKRESULT WWISEC_AK_SoundEngine_UnregisterAllGameObj();

    AKRESULT WWISEC_AK_SoundEngine_SetPosition(AkGameObjectID in_GameObjectID, const AkSoundPosition* in_Position, enum AkSetPositionFlags in_eFlags);

    AKRESULT WWISEC_AK_SoundEngine_SetMultiplePositions_SoundPosition(AkGameObjectID in_GameObjectID, const AkSoundPosition* in_pPositions, AkUInt16 in_NumPositions, enum AkMultiPositionType in_eMultiPositionType, enum AkSetPositionFlags in_eFlags);

    AKRESULT WWISEC_AK_SoundEngine_SetMultiplePositions_ChannelEmitter(AkGameObjectID in_GameObjectID, const struct AkChannelEmitter* in_pPositions, AkUInt16 in_NumPositions, enum AkMultiPositionType in_eMultiPositionType, enum AkSetPositionFlags in_eFlags);

    AKRESULT WWISEC_AK_SoundEngine_SetScalingFactor(AkGameObjectID in_GameObjectID, AkReal32 in_fAttenuationScalingFactor);

    AKRESULT WWISEC_AK_SoundEngine_SetDistanceProbe(AkGameObjectID in_listenerGameObjectID, AkGameObjectID in_distanceProbeGameObjectID);

    AKRESULT WWISEC_AK_SoundEngine_ClearBanks();

    AKRESULT WWISEC_AK_SoundEngine_SetBankLoadIOSettings(AkReal32 in_fThroughput, AkPriority in_priority);

    AKRESULT WWISEC_AK_SoundEngine_LoadBank_String(const char* in_pszString, AkBankID* out_bankID, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_LoadBank_ID(AkBankID in_bankID, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, AkBankID* out_bankID);

    AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, AkBankID* out_bankID, AkBankType* out_bankType);

    AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, AkBankID* out_bankID);

    AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, AkBankID* out_bankID, AkBankType* out_bankType);

    AKRESULT WWISEC_AK_SoundEngine_DecodeBank(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, AkMemPoolId in_uPoolForDecodedBank, void** out_pDecodedBankPtr, AkUInt32* out_uDecodedBankSize);

    AKRESULT WWISEC_AK_SoundEngine_LoadBank_Async_String(const char* in_pszString, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankID* out_bankID, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_LoadBank_Async_ID(AkBankID in_bankID, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_Async(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankID* out_bankID);

    AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_Async_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankID* out_bankID, AkBankType* out_bankType);

    AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy_Async(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankID* out_bankID);

    AKRESULT WWISEC_AK_SoundEngine_UnloadBank_String(const char* in_pszString, const void* in_pInMemoryBankPtr, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_UnloadBank_ID(AkBankID in_bankID, const void* in_pInMemoryBankPtr, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_UnloadBank_Async_String(const char* in_pszString, const void* in_pInMemoryBankPtr, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_UnloadBank_Async_ID(AkBankID in_bankID, const void* in_pInMemoryBankPtr, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankType in_bankType);

    void WWISEC_AK_SoundEngine_CancelBankCallbackCookie(void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_PrepareBank_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char* in_pszString, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_PrepareBank_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkBankID in_bankID, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_PrepareBank_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char* in_pszString, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_PrepareBank_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkBankID in_bankID, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, AkBankType in_bankType);

    AKRESULT WWISEC_AK_SoundEngine_ClearPreparedEvents();

    AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uNumEvent);

    AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkUniqueID* in_pEventID, AkUInt32 in_uNumEvent);

    AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uNumEvent, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkUniqueID* in_pEventID, AkUInt32 in_uNumEvent, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_PrepareBus_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uBusses);

    AKRESULT WWISEC_AK_SoundEngine_PrepareBus_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkUniqueID* in_pBusID, AkUInt32 in_uBusses);

    AKRESULT WWISEC_AK_SoundEngine_PrepareBus_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uBusses, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_PrepareBus_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkUniqueID* in_pBusID, AkUInt32 in_uBusses, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_SetMedia(WWISEC_AkSourceSettings* in_pSourceSettings, AkUInt32 in_uNumSourceSettings);

    AKRESULT WWISEC_AK_SoundEngine_TryUnsetMedia(WWISEC_AkSourceSettings* in_pSourceSettings, AkUInt32 in_uNumSourceSettings, AKRESULT* out_pUnsetResults);

    AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, enum AkGroupType in_eGameSyncType, const char* in_pszGroupName, const char** in_ppszGameSyncName, AkUInt32 in_uNumGameSyncs);

    AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, enum AkGroupType in_eGameSyncType, AkUInt32 in_GroupID, AkUInt32* in_paGameSyncID, AkUInt32 in_uNumGameSyncs);

    AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, enum AkGroupType in_eGameSyncType, const char* in_pszGroupName, const char** in_ppszGameSyncName, AkUInt32 in_uNumGameSyncs, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, enum AkGroupType in_eGameSyncType, AkUInt32 in_GroupID, AkUInt32* in_paGameSyncID, AkUInt32 in_uNumGameSyncs, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_SetListeners(AkGameObjectID in_emitterGameObj, const AkGameObjectID* in_pListenerGameObjs, AkUInt32 in_uNumListeners);

    AKRESULT WWISEC_AK_SoundEngine_AddListener(AkGameObjectID in_emitterGameObj, AkGameObjectID in_listenerGameObj);

    AKRESULT WWISEC_AK_SoundEngine_RemoveListener(AkGameObjectID in_emitterGameObj, AkGameObjectID in_listenerGameObj);

    AKRESULT WWISEC_AK_SoundEngine_SetDefaultListeners(const AkGameObjectID* in_pListenerObjs, AkUInt32 in_uNumListeners);

    AKRESULT WWISEC_AK_SoundEngine_AddDefaultListener(AkGameObjectID in_listenerGameObj);

    AKRESULT WWISEC_AK_SoundEngine_RemoveDefaultListener(AkGameObjectID in_listenerGameObj);

    AKRESULT WWISEC_AK_SoundEngine_ResetListenersToDefault(AkGameObjectID in_emitterGameObj);

    AKRESULT WWISEC_AK_SoundEngine_SetListenerSpatialization(AkGameObjectID in_uListenerID, bool in_bSpatialized, struct AkChannelConfig in_channelConfig, AkSpeakerVolumesMatrixPtr in_pVolumeOffsets);

    AKRESULT WWISEC_AK_SoundEngine_SetRTPCValue_ID(AkRtpcID in_rtpcID, AkRtpcValue in_value, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    AKRESULT WWISEC_AK_SoundEngine_SetRTPCValue_String(const char* in_pszRtpcName, AkRtpcValue in_value, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    AKRESULT WWISEC_AK_SoundEngine_SetRTPCValueByPlayingID_ID(AkRtpcID in_rtpcID, AkRtpcValue in_value, AkPlayingID in_playingID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    AKRESULT WWISEC_AK_SoundEngine_SetRTPCValueByPlayingID_String(const char* in_pszRtpcName, AkRtpcValue in_value, AkPlayingID in_playingID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValue_ID(AkRtpcID in_rtpcID, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValue_String(const char* in_pszRtpcName, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValueByPlayingID_ID(AkRtpcID in_rtpcID, AkPlayingID in_playingID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValueByPlayingID_String(const char* in_pszRtpcName, AkPlayingID in_playingID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation);

    AKRESULT WWISEC_AK_SoundEngine_SetSwitch_ID(AkSwitchGroupID in_switchGroup, AkSwitchStateID in_switchState, AkGameObjectID in_gameObjectID);

    AKRESULT WWISEC_AK_SoundEngine_SetSwitch_String(const char* in_pszSwitchGroup, const char* in_pszSwitchState, AkGameObjectID in_gameObjectID);

    AKRESULT WWISEC_AK_SoundEngine_PostTrigger_ID(AkTriggerID in_triggerID, AkGameObjectID in_gameObjectID);

    AKRESULT WWISEC_AK_SoundEngine_PostTrigger_String(const char* in_pszTrigger, AkGameObjectID in_gameObjectID);

    AKRESULT WWISEC_AK_SoundEngine_SetState_ID(AkStateGroupID in_stateGroup, AkStateID in_state);

    AKRESULT WWISEC_AK_SoundEngine_SetState_String(const char* in_pszStateGroup, const char* in_pszState);

    AKRESULT WWISEC_AK_SoundEngine_SetGameObjectAuxSendValues(AkGameObjectID in_gameObjectID, struct AkAuxSendValue* in_aAuxSendValues, AkUInt32 in_uNumSendValues);

    AKRESULT WWISEC_AK_SoundEngine_RegisterBusVolumeCallback(AkUniqueID in_busID, WWISEC_AkBusCallbackFunc in_pfnCallback, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_RegisterBusMeteringCallback(AkUniqueID in_busID, WWISEC_AkBusMeteringCallbackFunc in_pfnCallback, enum AkMeteringFlags in_eMeteringFlags, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_RegisterOutputDeviceMeteringCallback(AkOutputDeviceID in_idOutput, WWISEC_AkOutputDeviceMeteringCallbackFunc in_pfnCallback, enum AkMeteringFlags in_eMeteringFlags, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_SetGameObjectOutputBusVolume(AkGameObjectID in_emitterObjID, AkGameObjectID in_listenerObjID, AkReal32 in_fControlValue);

    AKRESULT WWISEC_AK_SoundEngine_SetActorMixerEffect(AkUniqueID in_audioNodeID, AkUInt32 in_uFXIndex, AkUniqueID in_shareSetID);

    AKRESULT WWISEC_AK_SoundEngine_SetBusEffect_ID(AkUniqueID in_audioNodeID, AkUInt32 in_uFXIndex, AkUniqueID in_shareSetID);

    AKRESULT WWISEC_AK_SoundEngine_SetBusEffect_String(const char* in_pszBusName, AkUInt32 in_uFXIndex, AkUniqueID in_shareSetID);

    AKRESULT WWISEC_AK_SoundEngine_SetOutputDeviceEffect(AkOutputDeviceID in_outputDeviceID, AkUInt32 in_uFXIndex, AkUniqueID in_FXShareSetID);

    AKRESULT WWISEC_AK_SoundEngine_SetBusConfig_ID(AkUniqueID in_audioNodeID, struct AkChannelConfig in_channelConfig);

    AKRESULT WWISEC_AK_SoundEngine_SetBusConfig_String(const char* in_pszBusName, struct AkChannelConfig in_channelConfig);

    AKRESULT WWISEC_AK_SoundEngine_SetObjectObstructionAndOcclusion(AkGameObjectID in_EmitterID, AkGameObjectID in_ListenerID, AkReal32 in_fObstructionLevel, AkReal32 in_fOcclusionLevel);

    AKRESULT WWISEC_AK_SoundEngine_SetMultipleObstructionAndOcclusion(AkGameObjectID in_EmitterID, AkGameObjectID in_uListenerID, struct AkObstructionOcclusionValues* in_fObstructionOcclusionValues, AkUInt32 in_uNumOcclusionObstruction);

    AKRESULT WWISEC_AK_SoundEngine_GetContainerHistory(WWISEC_AK_IWriteBytes* in_pBytes);

    AKRESULT WWISEC_AK_SoundEngine_SetContainerHistory(WWISEC_AK_IReadBytes* in_pBytes);

    AKRESULT WWISEC_AK_SoundEngine_StartOutputCapture(const AkOSChar* in_CaptureFileName);

    AKRESULT WWISEC_AK_SoundEngine_StopOutputCapture();

    AKRESULT WWISEC_AK_SoundEngine_AddOutputCaptureMarker(const char* in_MarkerText);

    AKRESULT WWISEC_AK_SoundEngine_AddOutputCaptureBinaryMarker(void* in_pMarkerData, AkUInt32 in_uMarkerDataSize);

    AkUInt32 WWISEC_AK_SoundEngine_GetSampleRate();

    AKRESULT WWISEC_AK_SoundEngine_RegisterCaptureCallback(WWISEC_AkCaptureCallbackFunc in_pfnCallback, AkOutputDeviceID in_idOutput, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_UnregisterCaptureCallback(WWISEC_AkCaptureCallbackFunc in_pfnCallback, AkOutputDeviceID in_idOutput, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_StartProfilerCapture(const AkOSChar* in_CaptureFileName);

    AKRESULT WWISEC_AK_SoundEngine_StopProfilerCapture();

    AKRESULT WWISEC_AK_SoundEngine_SetOfflineRenderingFrameTime(AkReal32 in_fFrameTimeInSeconds);

    AKRESULT WWISEC_AK_SoundEngine_SetOfflineRendering(bool in_bEnableOfflineRendering);

    AKRESULT WWISEC_AK_SoundEngine_AddOutput(const struct AkOutputSettings* in_Settings, AkOutputDeviceID* out_pDeviceID, const AkGameObjectID* in_pListenerIDs, AkUInt32 in_uNumListeners);

    AKRESULT WWISEC_AK_SoundEngine_RemoveOutput(AkOutputDeviceID in_idOutput);

    AKRESULT WWISEC_AK_SoundEngine_ReplaceOutput(const struct AkOutputSettings* in_Settings, AkOutputDeviceID in_outputDeviceId, AkOutputDeviceID* out_pOutputDeviceId);

    AkOutputDeviceID WWISEC_AK_SoundEngine_GetOutputID_ID(AkUniqueID in_idShareset, AkUInt32 in_idDevice);

    AkOutputDeviceID WWISEC_AK_SoundEngine_GetOutputID_String(const char* in_szShareSet, AkUInt32 in_idDevice);

    AKRESULT WWISEC_AK_SoundEngine_SetBusDevice_ID(AkUniqueID in_idBus, AkUniqueID in_idNewDevice);

    AKRESULT WWISEC_AK_SoundEngine_SetBusDevice_String(const char* in_BusName, const char* in_DeviceName);

    AKRESULT WWISEC_AK_SoundEngine_GetDeviceList_Plugin(AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, AkUInt32* io_maxNumDevices, struct AkDeviceDescription* out_deviceDescriptions);

    AKRESULT WWISEC_AK_SoundEngine_GetDeviceList_ShareSet(AkUniqueID in_audioDeviceShareSetID, AkUInt32* io_maxNumDevices, struct AkDeviceDescription* out_deviceDescriptions);

    AKRESULT WWISEC_AK_SoundEngine_SetOutputVolume(AkOutputDeviceID in_idOutput, AkReal32 in_fVolume);

    AKRESULT WWISEC_AK_SoundEngine_GetDeviceSpatialAudioSupport(AkUInt32 in_idDevice);

    AKRESULT WWISEC_AK_SoundEngine_Suspend(bool in_bRenderAnyway, bool in_bFadeOut);

    AKRESULT WWISEC_AK_SoundEngine_WakeupFromSuspend(AkUInt32 in_uDelayMs);

    AkUInt32 WWISEC_AK_SoundEngine_GetBufferTick();

    AkUInt64 WWISEC_AK_SoundEngine_GetSampleTick();
    // END AkSoundEngine

    // BEGIN AkFileSystemFlags
    typedef struct WWISEC_AkFileSystemFlags
    {
        AkUInt32 uCompanyID;        ///< Company ID (Wwise uses AKCOMPANYID_AUDIOKINETIC, defined in AkTypes.h, for soundbanks and standard streaming files, and AKCOMPANYID_AUDIOKINETIC_EXTERNAL for streaming external sources).
        AkUInt32 uCodecID;          ///< File/codec type ID (defined in AkTypes.h)
        AkUInt32 uCustomParamSize;  ///< Size of the custom parameter
        void* pCustomParam;         ///< Custom parameter
        bool bIsLanguageSpecific;   ///< True when the file location depends on language
        bool bIsAutomaticStream;    ///< True when the file is opened to be used as an automatic stream. Note that you don't need to set it.
                                    ///< If you pass an AkFileSystemFlags to IAkStreamMgr CreateStd|Auto(), it will be set internally to the correct value.
        AkCacheID uCacheID;         ///< Cache ID for caching system used by automatic streams. The user is responsible for guaranteeing unicity of IDs.
                                    ///< When set, it supersedes the file ID passed to AK::IAkStreamMgr::CreateAuto() (ID version). Caching is optional and depends on the implementation.
        AkUInt32 uNumBytesPrefetch; ///< Indicates the number of bytes from the beginning of the file that should be streamed into cache via a caching stream. This field is only relevant when opening caching streams via
                                    ///< AK::IAkStreamMgr::PinFileInCache() and AK::SoundEngine::PinEventInStreamCache().  When using AK::SoundEngine::PinEventInStreamCache(),
                                    ///< it is initialized to the prefetch size stored in the sound bank, but may be changed by the file location resolver, or set to 0 to cancel caching.
        AkUInt32 uDirectoryHash;    ///< If the implementation uses a hashed directory structure, this is the hash value that should be employed for determining the directory structure
    } WWISEC_AkFileSystemFlags;
    // END AkFileSystemFlags

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

    typedef struct WWISEC_AkStreamInfo
    {
        AkDeviceID deviceID;      ///< Device ID
        const AkOSChar* pszName;  ///< User-defined stream name (specified through AK::IAkStdStream::SetStreamName() or AK::IAkAutoStream::SetStreamName())
        AkUInt64 uSize;           ///< Total stream/file size in bytes
        bool bIsOpen;             ///< True when the file is open (implementations may defer file opening)
        bool bIsLanguageSpecific; ///< True when the file was found in a language specific location
    } WWISEC_AkStreamInfo;

    /// Automatic streams heuristics.
    typedef struct WWISEC_AkAutoStmHeuristics
    {
        AkReal32 fThroughput;   ///< Average throughput in bytes/ms
        AkUInt64 uLoopStart;    ///< Set to the start of loop (byte offset from the beginning of the stream) for streams that loop, 0 otherwise
        AkUInt64 uLoopEnd;      ///< Set to the end of loop (byte offset from the beginning of the stream) for streams that loop, 0 otherwise
        AkUInt8 uMinNumBuffers; ///< Minimum number of buffers if you plan to own more than one buffer at a time, 0 or 1 otherwise
                                ///< \remarks You should always release buffers as fast as possible, therefore this heuristic should be used only when
                                ///< dealing with special contraints, like drivers or hardware that require more than one buffer at a time.\n
                                ///< Also, this is only a heuristic: it does not guarantee that data will be ready when calling AK::IAkAutoStream::GetBuffer().
        AkPriority priority;    ///< The stream priority. it should be between AK_MIN_PRIORITY and AK_MAX_PRIORITY (included).
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
        AkDeviceID deviceID;                                          ///< Device ID
        bool bCanWrite;                                               ///< Specifies whether or not the device is writable
        bool bCanRead;                                                ///< Specifies whether or not the device is readable
        AkUtf16 szDeviceName[WWISEC_AK_MONITOR_DEVICENAME_MAXLENGTH]; ///< Device name
        AkUInt32 uStringSize;                                         ///< Device name string's size (number of characters)
    } WWISEC_AkDeviceDesc;

    /// Device descriptor.
    typedef struct WWISEC_AkDeviceData
    {
        AkDeviceID deviceID;                    ///< Device ID
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
        AkDeviceID deviceID;                                          ///< Device ID
        AkUtf16 szStreamName[WWISEC_AK_MONITOR_STREAMNAME_MAXLENGTH]; ///< Stream name
        AkFileID idFile;
        AkUInt32 uStringSize;  ///< Stream name string's size (number of characters)
        AkUInt64 uFileSize;    ///< File size
        bool bIsAutoStream;    ///< True for auto streams
        bool bIsCachingStream; ///< True for caching streams
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

    typedef struct WWISEC_AkFileOpenData
    {
        const AkOSChar* pszFileName;      ///< File name. Only one of pszFileName or fileID should be valid (pszFileName null while fileID is not AK_INVALID_FILE_ID, or vice versa)
        AkFileID fileID;                  ///< File ID. Only one of pszFileName or fileID should be valid (pszFileName null while fileID is not AK_INVALID_FILE_ID, or vice versa)
        WWISEC_AkFileSystemFlags* pFlags; ///< Flags for opening, null when unused
        WWISEC_AkOpenMode eOpenMode;      ///< Open mode.
    } WWISEC_AkFileOpenData;
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

        AKRESULT(*StartMonitoring)
        (void* instance);
        void (*StopMonitoring)(void* instance);
        AkUInt32 (*GetNumDevices)(void* instance);
        WWISEC_AK_IAkDeviceProfile* (*GetDeviceProfile)(void* instance, AkUInt32 in_uDeviceIndex);
    } WWISEC_AK_IAkStreamMgrProfile_FunctionTable;

    WWISEC_AK_IAkStreamMgrProfile* WWISEC_AK_IAkStreamMgrProfile_CreateInstance(void* instance, const WWISEC_AK_IAkStreamMgrProfile_FunctionTable* functionTable);
    void WWISEC_AK_IAkStreamMgrProfile_DestroyInstance(WWISEC_AK_IAkStreamMgrProfile* instance);

    AKRESULT WWISEC_AK_IAkStreamMgrProfile_StartMonitoring(WWISEC_AK_IAkStreamMgrProfile* instance);
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

        AKRESULT(*SetStreamName)
        (void* instance, const AkOSChar* in_pszStreamName);

        AkUInt32 (*GetBlockSize)(void* instance);

        AKRESULT(*Read)
        (void* instance, void* in_pBuffer,
         AkUInt32 in_uReqSize,
         bool in_bWait,
         AkPriority in_priority,
         AkReal32 in_fDeadline,
         AkUInt32* out_uSize);

        AKRESULT(*Write)
        (void* instance,
         void* in_pBuffer,
         AkUInt32 in_uReqSize,
         bool in_bWait,
         AkPriority in_priority,
         AkReal32 in_fDeadline,
         AkUInt32* out_uSize);

        AkUInt64 (*GetPosition)(void* instance, bool* out_pbEndOfStream);

        AKRESULT(*SetPosition)
        (void* instance, AkInt64 in_iMoveOffset, WWISEC_AkMoveMethod in_eMoveMethod);

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
    AKRESULT WWISEC_AK_IAkStdStream_SetStreamName(WWISEC_AK_IAkStdStream* instance, const AkOSChar* in_pszStreamName);
    AkUInt32 WWISEC_AK_IAkStdStream_GetBlockSize(WWISEC_AK_IAkStdStream* instance);
    AKRESULT WWISEC_AK_IAkStdStream_Read(WWISEC_AK_IAkStdStream* instance, void* in_pBuffer, AkUInt32 in_uReqSize, bool in_bWait, AkPriority in_priority, AkReal32 in_fDeadline, AkUInt32* out_uSize);
    AKRESULT WWISEC_AK_IAkStdStream_Write(WWISEC_AK_IAkStdStream* instance, void* in_pBuffer, AkUInt32 in_uReqSize, bool in_bWait, AkPriority in_priority, AkReal32 in_fDeadline, AkUInt32* out_uSize);
    AkUInt64 WWISEC_AK_IAkStdStream_GetPosition(WWISEC_AK_IAkStdStream* instance, bool* out_pbEndOfStream);
    AKRESULT WWISEC_AK_IAkStdStream_SetPosition(WWISEC_AK_IAkStdStream* instance, AkInt64 in_iMoveOffset, WWISEC_AkMoveMethod in_eMoveMethod);
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

        AKRESULT(*SetHeuristics)
        (void* instance, const WWISEC_AkAutoStmHeuristics* in_heuristics);

        AKRESULT(*SetMinimalBufferSize)
        (void* instance, AkUInt32 in_uMinBufferSize);

        AKRESULT(*SetStreamName)
        (void* instance, const AkOSChar* in_pszStreamName);

        AkUInt32 (*GetBlockSize)(void* instance);

        AKRESULT(*QueryBufferingStatus)
        (void* instance, AkUInt32* out_uNumBytesAvailable);

        AkUInt32 (*GetNominalBuffering)(void* instance);

        AKRESULT(*Start)
        (void* instance);

        AKRESULT(*Stop)
        (void* instance);

        AkUInt64 (*GetPosition)(void* instance, bool* out_pbEndOfStream);

        AKRESULT(*SetPosition)
        (void* instance, AkInt64 in_iMoveOffset, WWISEC_AkMoveMethod in_eMoveMethod);

        AKRESULT(*GetBuffer)
        (void* instance, void** out_pBuffer, AkUInt32* out_uSize, bool in_bWait);

        AKRESULT(*ReleaseBuffer)
        (void* instance);
    } WWISEC_AK_IAkAutoStream_FunctionTable;

    WWISEC_AK_IAkAutoStream* WWISEC_AK_IAkAutoStream_CreateInstance(void* instance, const WWISEC_AK_IAkAutoStream_FunctionTable* functionTable);
    void WWISEC_AK_IAkAutoStream_DestroyInstance(WWISEC_AK_IAkAutoStream* instance);

    void WWISEC_AK_IAkAutoStream_Destroy(WWISEC_AK_IAkAutoStream* instance);
    void WWISEC_AK_IAkAutoStream_GetInfo(WWISEC_AK_IAkAutoStream* instance, WWISEC_AkStreamInfo* out_info);
    void* WWISEC_AK_IAkAutoStream_GetFileDescriptor(WWISEC_AK_IAkAutoStream* instance);
    void WWISEC_AK_IAkAutoStream_GetHeuristics(WWISEC_AK_IAkAutoStream* instance, WWISEC_AkAutoStmHeuristics* out_heuristics);
    AKRESULT WWISEC_AK_IAkAutoStream_SetHeuristics(WWISEC_AK_IAkAutoStream* instance, const WWISEC_AkAutoStmHeuristics* in_heuristics);
    AKRESULT WWISEC_AK_IAkAutoStream_SetMinimalBufferSize(WWISEC_AK_IAkAutoStream* instance, AkUInt32 in_uMinBufferSize);
    AKRESULT WWISEC_AK_IAkAutoStream_SetStreamName(WWISEC_AK_IAkAutoStream* instance, const AkOSChar* in_pszStreamName);
    AkUInt32 WWISEC_AK_IAkAutoStream_GetBlockSize(WWISEC_AK_IAkAutoStream* instance);
    AKRESULT WWISEC_AK_IAkAutoStream_QueryBufferingStatus(WWISEC_AK_IAkAutoStream* instance, AkUInt32* out_uNumBytesAvailable);
    AkUInt32 WWISEC_AK_IAkAutoStream_GetNominalBuffering(WWISEC_AK_IAkAutoStream* instance);
    AKRESULT WWISEC_AK_IAkAutoStream_Start(WWISEC_AK_IAkAutoStream* instance);
    AKRESULT WWISEC_AK_IAkAutoStream_Stop(WWISEC_AK_IAkAutoStream* instance);
    AkUInt64 WWISEC_AK_IAkAutoStream_GetPosition(WWISEC_AK_IAkAutoStream* instance, bool* out_pbEndOfStream);
    AKRESULT WWISEC_AK_IAkAutoStream_SetPosition(WWISEC_AK_IAkAutoStream* instance, AkInt64 in_iMoveOffset, WWISEC_AkMoveMethod in_eMoveMethod);
    AKRESULT WWISEC_AK_IAkAutoStream_GetBuffer(WWISEC_AK_IAkAutoStream* instance, void** out_pBuffer, AkUInt32* out_uSize, bool in_bWait);
    AKRESULT WWISEC_AK_IAkAutoStream_ReleaseBuffer(WWISEC_AK_IAkAutoStream* instance);

    typedef struct WWISEC_AK_IAkStreamMgr WWISEC_AK_IAkStreamMgr;

    typedef struct WWISEC_AK_IAkStreamMgr_FunctionTable
    {
        void (*Destructor)(void* instance);

        void (*Destroy)(void* instance);

        WWISEC_AK_IAkStreamMgrProfile* (*GetStreamMgrProfile)(void* instance);

        AKRESULT(*CreateStd)
        (
            void* instance,
            const WWISEC_AkFileOpenData* in_FileOpen,
            WWISEC_AK_IAkStdStream** out_pStream,
            bool in_bSyncOpen);

        AKRESULT(*CreateAuto_AkFileOpenData)
        (
            void* instance,
            const WWISEC_AkFileOpenData* in_FileOpen,
            const WWISEC_AkAutoStmHeuristics* in_heuristics,
            WWISEC_AkAutoStmBufSettings* in_pBufferSettings,
            WWISEC_AK_IAkAutoStream** out_pStream,
            bool in_bSyncOpen,
            bool in_bCaching);

        AKRESULT(*CreateAuto_Memory)
        (
            void* instance,
            void* in_pBuffer,
            AkUInt64 in_uSize,
            const WWISEC_AkAutoStmHeuristics* in_heuristics,
            WWISEC_AK_IAkAutoStream** out_pStream);

        AKRESULT(*PinFileInCache)
        (
            void* instance,
            AkFileID in_fileID,
            WWISEC_AkFileSystemFlags* in_pFSFlags,
            AkPriority in_uPriority);

        AKRESULT(*UnpinFileInCache)
        (
            void* instance,
            AkFileID in_fileID,
            AkPriority in_uPriority);

        AKRESULT(*UpdateCachingPriority)
        (
            void* instance,
            AkFileID in_fileID,
            AkPriority in_uPriority,
            AkPriority in_uOldPriority);

        AKRESULT(*GetBufferStatusForPinnedFile)
        (
            void* instance,
            AkFileID in_fileID,
            AkReal32* out_fPercentBuffered,
            bool* out_bCacheFull);

        AKRESULT(*RelocateMemoryStream)
        (
            void* instance,
            WWISEC_AK_IAkAutoStream* in_pStream,
            AkUInt8* in_pNewStart);
    } WWISEC_AK_IAkStreamMgr_FunctionTable;

    WWISEC_AK_IAkStreamMgr* WWISEC_AK_IAkStreamMgr_CreateInstance(void* instance, const WWISEC_AK_IAkStreamMgr_FunctionTable* functionTable);
    void WWISEC_AK_IAkStreamMgr_DestroyInstance(WWISEC_AK_IAkStreamMgr* instance);

    void WWISEC_AK_IAkStreamMgr_Destroy(WWISEC_AK_IAkStreamMgr* instance);
    WWISEC_AK_IAkStreamMgrProfile* WWISEC_AK_IAkStreamMgr_GetStreamMgrProfile(WWISEC_AK_IAkStreamMgr* instance);
    AKRESULT WWISEC_AK_IAkStreamMgr_CreateStd(WWISEC_AK_IAkStreamMgr* instance, const WWISEC_AkFileOpenData* in_FileOpen, WWISEC_AK_IAkStdStream** out_pStream, bool in_bSyncOpen);
    AKRESULT WWISEC_AK_IAkStreamMgr_CreateAuto_AkFileOpenData(WWISEC_AK_IAkStreamMgr* instance, const WWISEC_AkFileOpenData* in_FileOpen, const WWISEC_AkAutoStmHeuristics* in_heuristics, WWISEC_AkAutoStmBufSettings* in_pBufferSettings, WWISEC_AK_IAkAutoStream** out_pStream, bool in_bSyncOpen, bool in_bCaching);
    AKRESULT WWISEC_AK_IAkStreamMgr_CreateAuto_ID(WWISEC_AK_IAkStreamMgr* instance, AkFileID in_fileID, WWISEC_AkFileSystemFlags* in_pFSFlags, const WWISEC_AkAutoStmHeuristics* in_heuristics, WWISEC_AkAutoStmBufSettings* in_pBufferSettings, WWISEC_AK_IAkAutoStream** out_pStream, bool in_bSyncOpen);
    AKRESULT WWISEC_AK_IAkStreamMgr_CreateAuto_Memory(WWISEC_AK_IAkStreamMgr* instance, void* in_pBuffer, AkUInt64 in_uSize, const WWISEC_AkAutoStmHeuristics* in_heuristics, WWISEC_AK_IAkAutoStream** out_pStream);
    AKRESULT WWISEC_AK_IAkStreamMgr_PinFileInCache(WWISEC_AK_IAkStreamMgr* instance, AkFileID in_fileID, WWISEC_AkFileSystemFlags* in_pFSFlags, AkPriority in_uPriority);
    AKRESULT WWISEC_AK_IAkStreamMgr_UnpinFileInCache(WWISEC_AK_IAkStreamMgr* instance, AkFileID in_fileID, AkPriority in_uPriority);
    AKRESULT WWISEC_AK_IAkStreamMgr_UpdateCachingPriority(WWISEC_AK_IAkStreamMgr* instance, AkFileID in_fileID, AkPriority in_uPriority, AkPriority in_uOldPriority);
    AKRESULT WWISEC_AK_IAkStreamMgr_GetBufferStatusForPinnedFile(WWISEC_AK_IAkStreamMgr* instance, AkFileID in_fileID, AkReal32* out_fPercentBuffered, bool* out_bCacheFull);
    AKRESULT WWISEC_AK_IAkStreamMgr_RelocateMemoryStream(WWISEC_AK_IAkStreamMgr* instance, WWISEC_AK_IAkAutoStream* in_pStream, AkUInt8* in_pNewStart);

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
        WWISEC_AkThreadProperties threadProperties; ///< Scheduler thread properties.
        AkReal32 fTargetAutoStmBufferLength;        ///< Targetted automatic stream buffer length (ms). When a stream reaches that buffering, it stops being scheduled for I/O except if the scheduler is idle.
        AkUInt32 uMaxConcurrentIO;                  ///< Maximum number of transfers that can be sent simultaneously to the Low-Level I/O.
        bool bUseStreamCache;                       ///< If true, the device attempts to reuse I/O buffers that have already been streamed from disk. This is particularly useful when streaming small looping sounds. However, there is a small increase in CPU usage when allocating memory, and a slightly larger memory footprint in the StreamManager pool.
        AkUInt32 uMaxCachePinnedBytes;              ///< Maximum number of bytes that can be "pinned" using AK::SoundEngine::PinEventInStreamCache() or AK::IAkStreamMgr::PinFileInCache()
    } WWISEC_AkDeviceSettings;

    typedef struct WWISEC_AkFileDesc
    {
        AkInt64 iFileSize;   ///< File size in bytes
        AkUInt64 uSector;    ///< Start sector (the sector size is specified by the low-level I/O)
                             ///< \sa
                             ///< - AK::StreamMgr::IAkFileLocationResolver::Open()
                             ///< - AK::StreamMgr::IAkLowLevelIOHook::GetBlockSize()
        AkFileHandle hFile;  ///< File handle/identifier
        AkDeviceID deviceID; ///< Device ID, obtained from CreateDevice() \sa AK::IAkStreamMgr::CreateDevice()
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
        AKRESULT in_eResult                             ///< Result of transfer: AK_Success or AK_Fail (streams waiting for this transfer become invalid).
    );

    typedef struct WWISEC_AkAsyncIOTransferInfo
    {
        WWISEC_AkIOTransferInfo base;
        void* pBuffer;                 ///< Buffer for data transfer.
        WWISEC_AkIOCallback pCallback; ///< Callback function used to notify the high-level device when the transfer is complete.
        void* pCookie;                 ///< Reserved. The I/O device uses this cookie to retrieve the owner of the transfer.
        void* pUserData;               ///< Custom user data.
    } WWISEC_AkAsyncIOTransferInfo;

    typedef struct WWISEC_AkAsyncFileOpenData WWISEC_AkAsyncFileOpenData;

    /// Callback signature for the notification of completion of the asynchronous Open operation.
    /// \sa
    /// - AkAsyncFileOpenData
    /// - AK::StreamMgr::IAkLowLevelIOHook::BatchOpen
    AK_CALLBACK(void, WWISEC_AkFileOpenCallback)
    (
        WWISEC_AkAsyncFileOpenData* in_pOpenInfo, ///< Pointer to the AkAsyncFileOpenData structure that was passed to corresponding Open().
        AKRESULT in_eResult                       ///< Result of transfer: AK_Success or AK_Fail (streams waiting for this transfer become invalid).
    );

    typedef struct WWISEC_AkAsyncFileOpenData
    {
        WWISEC_AkFileOpenData base;
        WWISEC_AkFileOpenCallback pCallback; ///< Callback function used to notify the high-level device when Open is done
        void* pCookie;                       ///< Reserved. Pass this unchanged to the callback function. The I/O device uses this cookie to retrieve the owner of the transfer.
        WWISEC_AkFileDesc* pFileDesc;        ///< File Descriptor to fill once the Open operation is complete.
        void* pCustomData;                   ///< Convienience pointer for the IO hook implementer. Useful for additional data used in asynchronous implementations, for example.
        AkOSChar* pszStreamName;             ///< Display name. If provided, this will be used to set the stream name, which is used for the profiler. This struct is not responsible for the memory.
    } WWISEC_AkAsyncFileOpenData;

    typedef struct WWISEC_AkIoHeuristics
    {
        AkReal32 fDeadline;  ///< Operation deadline (ms).
        AkPriority priority; ///< Operation priority (at the time it was scheduled and sent to the Low-Level I/O). Range is [AK_MIN_PRIORITY,AK_MAX_PRIORITY], inclusively.
    } WWISEC_AkIoHeuristics;

    AK_CALLBACK(void, WWISEC_AK_StreamMgr_AkLanguageChangeHandler)
    (
        const AkOSChar* const in_pLanguageName, ///< New language name.
        void* in_pCookie                        ///< Cookie that was passed to AddLanguageChangeObserver().
    );

    typedef struct WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem
    {
        WWISEC_AkFileDesc* pFileDesc;
        WWISEC_AkIoHeuristics ioHeuristics;
        WWISEC_AkAsyncIOTransferInfo* pTransferInfo;
    } WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem;

    typedef struct WWISEC_AK_StreamMgr_IAkLowLevelIOHook WWISEC_AK_StreamMgr_IAkLowLevelIOHook;

    typedef struct WWISEC_AK_StreamMgr_IAkLowLevelIOHook_FunctionTable
    {
        void (*Destructor)(void* instance);

        AKRESULT(*Close)
        (void* instance, WWISEC_AkFileDesc* in_fileDesc);

        AkUInt32 (*GetBlockSize)(void* instance, WWISEC_AkFileDesc* in_fileDesc);
        void (*GetDeviceDesc)(void* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
        AkUInt32 (*GetDeviceData)(void* instance);

        void (*BatchOpen)(void* instance, AkUInt32 in_uNumFiles, WWISEC_AkAsyncFileOpenData** in_ppItems);
        void (*BatchRead)(void* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem* in_pTransferItems);
        void (*BatchWrite)(void* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem* in_pTransferItems);

        AKRESULT(*OutputSearchedPaths)
        (void* instance, AKRESULT in_result, const WWISEC_AkFileOpenData* in_FileOpen, AkOSChar* out_searchedPath, AkInt32 in_pathSize);
    } WWISEC_AK_StreamMgr_IAkLowLevelIOHook_FunctionTable;
    WWISEC_AK_StreamMgr_IAkLowLevelIOHook* WWISEC_AK_StreamMgr_IAkLowLevelIOHook_CreateInstance(void* instance, const WWISEC_AK_StreamMgr_IAkLowLevelIOHook_FunctionTable* functionTable);
    void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_DestroyInstance(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance);

    AKRESULT WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Close(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, WWISEC_AkFileDesc* in_fileDesc);
    AkUInt32 WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetBlockSize(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, WWISEC_AkFileDesc* in_fileDesc);
    void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetDeviceDesc(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, WWISEC_AkDeviceDesc* out_deviceDesc);
    AkUInt32 WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetDeviceData(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance);

    void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchOpen(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, AkUInt32 in_uNumFiles, WWISEC_AkAsyncFileOpenData** in_ppItems);
    void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchRead(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem* in_pTransferItems);
    void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchWrite(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem* in_pTransferItems);
    AKRESULT WWISEC_AK_StreamMgr_IAkLowLevelIOHook_OutputSearchedPaths(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, AKRESULT in_result, const WWISEC_AkFileOpenData* in_FileOpen, AkOSChar* out_searchedPath, AkInt32 in_pathSize);

    typedef struct WWISEC_AK_StreamMgr_IAkFileLocationResolver WWISEC_AK_StreamMgr_IAkFileLocationResolver;

    typedef struct WWISEC_AK_StreamMgr_IAkFileLocationResolver_FunctionTable
    {
        void (*Destructor)(void* instance);

        AKRESULT(*GetNextPreferredDevice)
        (void* instance, WWISEC_AkAsyncFileOpenData* in_FileOpen, AkDeviceID* io_idDevice);
    } WWISEC_AK_StreamMgr_IAkFileLocationResolver_FunctionTable;

    WWISEC_AK_StreamMgr_IAkFileLocationResolver* WWISEC_AK_StreamMgr_IAkFileLocationResolver_CreateInstance(void* instance, const WWISEC_AK_StreamMgr_IAkFileLocationResolver_FunctionTable* functionTable);
    void WWISEC_AK_StreamMgr_IAkFileLocationResolver_DestroyInstance(WWISEC_AK_StreamMgr_IAkFileLocationResolver* instance);

    AKRESULT WWISEC_AK_StreamMgr_IAkFileLocationResolver_GetNextPreferredDevice(WWISEC_AK_StreamMgr_IAkFileLocationResolver* instance, WWISEC_AkAsyncFileOpenData* in_FileOpen, AkDeviceID* io_idDevice);

    void* WWISEC_AK_StreamMgr_Create(WWISEC_AkStreamMgrSettings* in_settings);
    void WWISEC_AK_StreamMgr_GetDefaultSettings(WWISEC_AkStreamMgrSettings* out_settings);
    void* WWISEC_AK_StreamMgr_GetFileLocationResolver();
    void WWISEC_AK_StreamMgr_SetFileLocationResolver(void* in_pFileLocationResolver);
    AKRESULT WWISEC_AK_StreamMgr_CreateDevice(const WWISEC_AkDeviceSettings* in_settings, void* in_pLowLevelHook, AkDeviceID* out_idDevice);
    AKRESULT WWISEC_AK_StreamMgr_DestroyDevice(AkDeviceID in_deviceID);
    AKRESULT WWISEC_AK_StreamMgr_PerformIO();
    void WWISEC_AK_StreamMgr_GetDefaultDeviceSettings(WWISEC_AkDeviceSettings* out_settings);
    AKRESULT WWISEC_AK_StreamMgr_SetCurrentLanguage(const AkOSChar* in_pszLanguageName);
    const AkOSChar* WWISEC_AK_StreamMgr_GetCurrentLanguage();
    AKRESULT WWISEC_AK_StreamMgr_AddLanguageChangeObserver(WWISEC_AK_StreamMgr_AkLanguageChangeHandler in_handler, void* in_pCookie);
    void WWISEC_AK_StreamMgr_RemoveLanguageChangeObserver(void* in_pCookie);
    void WWISEC_AK_StreamMgr_FlushAllCaches();
    // END AkStreamMgrModule

    // BEGIN AkMusicEngine
    typedef struct WWISEC_AkMusicSettings
    {
        AkReal32 fStreamingLookAheadRatio; ///< Multiplication factor for all streaming look-ahead heuristic values.
    } WWISEC_AkMusicSettings;

    AKRESULT WWISEC_AK_MusicEngine_Init(WWISEC_AkMusicSettings* in_pSettings);
    void WWISEC_AK_MusicEngine_GetDefaultInitSettings(WWISEC_AkMusicSettings* out_settings);
    void WWISEC_AK_MusicEngine_Term();
    AKRESULT WWISEC_AK_MusicEngine_GetPlayingSegmentInfo(AkPlayingID in_PlayingID, WWISEC_AkSegmentInfo* out_segmentInfo, bool in_bExtrapolate);
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

    AKRESULT WWISEC_AK_Comm_Init(const WWISEC_AkCommSettings* in_settings);
    void WWISEC_AK_Comm_GetDefaultInitSettings(WWISEC_AkCommSettings* out_settings);
    void WWISEC_AK_Comm_Term();
    AKRESULT WWISEC_AK_Comm_Reset();
    const WWISEC_AkCommSettings* WWISEC_AK_Comm_GetCurrentSettings();
    AkUInt16 WWISEC_AK_Comm_GetCommandPort();
#endif
    // END AkCommunication

    // BEGIN AkDynamicDialogue
    AK_CALLBACK(bool, WWISEC_AkCandidateCallbackFunc)
    (
        AkUniqueID in_idEvent,
        AkUniqueID in_idCandidate,
        void* in_cookie);

    AkUniqueID WWISEC_AK_SoundEngine_DynamicDialogue_ResolveDialogueEvent_ID(AkUniqueID in_eventID, AkArgumentValueID* in_aArgumentValues, AkUInt32 in_uNumArguments, AkPlayingID in_idSequence, WWISEC_AkCandidateCallbackFunc in_candidateCallbackFunc, void* in_pCookie);

    AkUniqueID WWISEC_AK_SoundEngine_DynamicDialogue_ResolveDialogueEvent_String(const char* in_pszEventName, const char** in_aArgumentValueNames, AkUInt32 in_uNumArguments, AkPlayingID in_idSequence, WWISEC_AkCandidateCallbackFunc in_candidateCallbackFunc, void* in_pCookie);

    AKRESULT WWISEC_AK_SoundEngine_DynamicDialogue_GetDialogueEventCustomPropertyValue(AkUniqueID in_eventID, AkUInt32 in_uPropID, AkInt32* out_iValue);
    // END AkDynamicDialogue

    // BEGIN AkDynamicSequence
    typedef struct WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem
    {
        AkUniqueID audioNodeID; ///< Unique ID of Audio Node
        AkTimeMs msDelay;       ///< Delay before playing this item, in milliseconds
        void* pCustomInfo;      ///< Optional user data
        AkExternalSourceArray pExternalSrcs;
    } WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem;

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem_SetExternalSources(WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* self, AkUInt32 in_nExternalSrc, struct AkExternalSourceInfo* in_pExternalSrc);

    typedef struct WWISEC_AK_SoundEngine_DynamicSequence_Playlist WWISEC_AK_SoundEngine_DynamicSequence_Playlist;

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Enqueue(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUniqueID in_audioNodeID, AkTimeMs in_msDelay, void* in_pCustomInfo, AkUInt32 in_cExternals, struct AkExternalSourceInfo* in_pExternalSources);
    void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Erase(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uIndex);
    void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_EraseSwap(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uIndex);
    bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_IsGrowingAllowed(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Reserve(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_ulReserve);
    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_ReserveExtra(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_ulReserve);
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
    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Remove(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item);
    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveSwap(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item);
    void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveAll(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_At(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uiIndex);
    WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Insert(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uIndex);
    bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_GrowArray(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self);
    bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_GrowArraySize(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_uGrowBy);
    bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Resize(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_uiSize);
    void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Transfer(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, WWISEC_AK_SoundEngine_DynamicSequence_Playlist* in_rSource);
    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Copy(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_Playlist* in_rSource);

    AkPlayingID WWISEC_AK_SoundEngine_DynamicSequence_Open(AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, enum AkDynamicSequenceType in_eDynamicSequenceType);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Close(AkPlayingID in_playingID);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Play(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Pause(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Resume(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Stop(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Break(AkPlayingID in_playingID);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Seek_Time(AkPlayingID in_playingID, AkTimeMs in_iPosition, bool in_bSeekToNearestMarker);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Seek_Percent(AkPlayingID in_playingID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_GetPauseTimes(AkPlayingID in_playingID, AkUInt32* out_uTime, AkUInt32* out_uDuration);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_GetPlayingItem(AkPlayingID in_playingID, AkUniqueID* out_audioNodeID, void** out_pCustomInfo);

    WWISEC_AK_SoundEngine_DynamicSequence_Playlist* WWISEC_AK_SoundEngine_DynamicSequence_LockPlaylist(AkPlayingID in_playingID);

    AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_UnlockPlaylist(AkPlayingID in_playingID);
    // END AkDynamicSequence

    // BEGIN AkQueryParameters

    /// Positioning information obtained from an object
    typedef struct WWISEC_AkPositioningInfo
    {
        AkReal32 fCenterPct;                               ///< Center % [0..1]
        enum AkSpeakerPanningType pannerType;              ///< Speaker panning type: type of panning logic when object is not 3D spatialized.
        enum Ak3DPositionType e3dPositioningType;          ///< 3D position type: defines what acts as the emitter position for computing spatialization against the listener.
        bool bHoldEmitterPosAndOrient;                     ///< Hold emitter position and orientation values when starting playback.
        enum Ak3DSpatializationMode e3DSpatializationMode; ///< Spatialization mode
        bool bEnableAttenuation;                           ///< Attenuation parameter set is active.

        bool bUseConeAttenuation;     ///< Use the cone attenuation
        AkReal32 fInnerAngle;         ///< Inner angle
        AkReal32 fOuterAngle;         ///< Outer angle
        AkReal32 fConeMaxAttenuation; ///< Cone max attenuation
        AkLPFType LPFCone;            ///< Cone low pass filter value
        AkLPFType HPFCone;            ///< Cone low pass filter value

        AkReal32 fMaxDistance;            ///< Maximum distance
        AkReal32 fVolDryAtMaxDist;        ///< Volume dry at maximum distance
        AkReal32 fVolAuxGameDefAtMaxDist; ///< Volume wet at maximum distance (if any) (based on the Game defined distance attenuation)
        AkReal32 fVolAuxUserDefAtMaxDist; ///< Volume wet at maximum distance (if any) (based on the User defined distance attenuation)
        AkLPFType LPFValueAtMaxDist;      ///< Low pass filter value at max distance (if any)
        AkLPFType HPFValueAtMaxDist;      ///< High pass filter value at max distance (if any)
    } WWISEC_AkPositioningInfo;

    /// Object information structure for QueryAudioObjectsIDs
    typedef struct WWISEC_AkObjectInfo
    {
        AkUniqueID objID;    ///< Object ID
        AkUniqueID parentID; ///< Object ID of the parent
        AkInt32 iDepth;      ///< Depth in tree
    } WWISEC_AkObjectInfo;

    AKRESULT WWISEC_AK_SoundEngine_Query_GetPosition(AkGameObjectID in_GameObjectID, AkSoundPosition* out_rPosition);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetListeners(AkGameObjectID in_GameObjectID, AkGameObjectID* out_ListenerObjectIDs, AkUInt32* oi_uNumListeners);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetListenerPosition(AkGameObjectID in_uListenerID, AkListenerPosition* out_rPosition);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetListenerSpatialization(AkGameObjectID in_uListenerID, bool* out_rbSpatialized, AkSpeakerVolumesMatrixPtr* out_pVolumeOffsets, struct AkChannelConfig* out_channelConfig);

    typedef enum WWISEC_AK_SoundEngine_Query_RTPCValue_type
    {
        WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_Default,    ///< The value is the Default RTPC.
        WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_Global,     ///< The value is the Global RTPC.
        WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_GameObject, ///< The value is the game object specific RTPC.
        WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_PlayingID,  ///< The value is the playing ID specific RTPC.
        WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_Unavailable ///< The value is not available for the RTPC specified.
    } WWISEC_AK_SoundEngine_Query_RTPCValue_type;

    AKRESULT WWISEC_AK_SoundEngine_Query_GetRTPCValue_ID(AkRtpcID in_rtpcID, AkGameObjectID in_gameObjectID, AkPlayingID in_playingID, AkRtpcValue* out_rValue, WWISEC_AK_SoundEngine_Query_RTPCValue_type* io_rValueType);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetRTPCValue_String(const char* in_pszRtpcName, AkGameObjectID in_gameObjectID, AkPlayingID in_playingID, AkRtpcValue* out_rValue, WWISEC_AK_SoundEngine_Query_RTPCValue_type* io_rValueType);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetSwitch_ID(AkSwitchGroupID in_switchGroup, AkGameObjectID in_gameObjectID, AkSwitchStateID* out_rSwitchState);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetSwitch_String(const char* in_pstrSwitchGroupName, AkGameObjectID in_GameObj, AkSwitchStateID* out_rSwitchState);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetState_ID(AkStateGroupID in_stateGroup, AkStateID* out_rState);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetState_String(const char* in_pstrStateGroupName, AkStateID* out_rState);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetGameObjectAuxSendValues(AkGameObjectID in_gameObjectID, struct AkAuxSendValue* out_paAuxSendValues, AkUInt32* io_ruNumSendValues);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetGameObjectDryLevelValue(AkGameObjectID in_EmitterID, AkGameObjectID in_ListenerID, AkReal32* out_rfControlValue);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetObjectObstructionAndOcclusion(AkGameObjectID in_EmitterID, AkGameObjectID in_ListenerID, AkReal32* out_rfObstructionLevel, AkReal32* out_rfOcclusionLevel);
    AKRESULT WWISEC_AK_SoundEngine_Query_QueryAudioObjectIDs_ID(AkUniqueID in_eventID, AkUInt32* io_ruNumItems, WWISEC_AkObjectInfo* out_aObjectInfos);
    AKRESULT WWISEC_AK_SoundEngine_Query_QueryAudioObjectIDs_String(const char* in_pszEventName, AkUInt32* io_ruNumItems, WWISEC_AkObjectInfo* out_aObjectInfos);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetPositioningInfo(AkUniqueID in_ObjectID, WWISEC_AkPositioningInfo* out_rPositioningInfo);

    typedef struct WWISEC_AK_SoundEngine_Query_AkGameObjectsList
    {
        AkGameObjectID* items;
        AkUInt32 length;
        AkUInt32 reserved;
    } WWISEC_AK_SoundEngine_Query_AkGameObjectsList;

    AKRESULT WWISEC_AK_SoundEngine_Query_GetActiveGameObjects(WWISEC_AK_SoundEngine_Query_AkGameObjectsList* io_GameObjectList);
    bool WWISEC_AK_SoundEngine_Query_GetIsGameObjectActive(AkGameObjectID in_GameObjId);

    typedef struct WWISEC_AK_SoundEngine_Query_GameObjDst
    {
        AkGameObjectID m_gameObjID; ///< Game object ID
        AkReal32 m_dst;             ///< MaxDistance
    } WWISEC_AK_SoundEngine_Query_GameObjDst;

    typedef struct WWISEC_AK_SoundEngine_Query_AkRadiusList
    {
        WWISEC_AK_SoundEngine_Query_GameObjDst* items;
        AkUInt32 length;
        AkUInt32 reserved;
    } WWISEC_AK_SoundEngine_Query_AkRadiusList;

    AKRESULT WWISEC_AK_SoundEngine_Query_GetMaxRadius_List(WWISEC_AK_SoundEngine_Query_AkRadiusList* io_RadiusList);
    AkReal32 WWISEC_AK_SoundEngine_Query_GetMaxRadius_Single(AkGameObjectID in_GameObjId);
    AkUniqueID WWISEC_AK_SoundEngine_Query_GetEventIDFromPlayingID(AkPlayingID in_playingID);
    AkGameObjectID WWISEC_AK_SoundEngine_Query_GetGameObjectFromPlayingID(AkPlayingID in_playingID);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetPlayingIDsFromGameObject(AkGameObjectID in_GameObjId, AkUInt32* io_ruNumIDs, AkPlayingID* out_aPlayingIDs);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetCustomPropertyValue_Int(AkUniqueID in_ObjectID, AkUInt32 in_uPropID, AkInt32* out_iValue);
    AKRESULT WWISEC_AK_SoundEngine_Query_GetCustomPropertyValue_Float(AkUniqueID in_ObjectID, AkUInt32 in_uPropID, AkReal32* out_fValue);
// END AkQueryParameters

// BEGIN IO Hooks
#if defined(WWISEC_INCLUDE_DEFAULT_IO_HOOK_DEFERRED)
    size_t WWISEC_AK_CAkDefaultIOHookDeferred_Sizeof();
    void* WWISEC_AK_CAkDefaultIOHookDeferred_Create(char* in_ioHookBuffer);
    void WWISEC_AK_CAkDefaultIOHookDeferred_Destroy(void* in_ioHook);
    AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings);
    void WWISEC_AK_CAkDefaultIOHookDeferred_Term(void* in_ioHook);
    AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    void WWISEC_CAkDefaultIOHookDeferred_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering);
#endif

#if defined(WWISEC_INCLUDE_FILE_PACKAGE_IO_DEFERRED)
    size_t WWISEC_AK_CAkFilePackageLowLevelIODeferred_Sizeof();
    void* WWISEC_AK_CAkFilePackageLowLevelIODeferred_Create(char* in_ioHookBuffer);
    void WWISEC_AK_CAkFilePackageLowLevelIODeferred_Destroy(void* in_ioHook);
    AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings);
    void WWISEC_AK_CAkFilePackageLowLevelIODeferred_Term(void* in_ioHook);
    AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath);
    void WWISEC_CAkFilePackageLowLevelIODeferred_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering);
    AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_LoadFilePackage(void* in_ioHook, const AkOSChar* in_pszFilePackageName, AkUInt32* out_uPackageID);
    AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadFilePackage(void* in_ioHook, AkUInt32 in_uPackageID);
    AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadAllFilePackages(void* in_ioHook);
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
    AKRESULT WWISEC_AK_JobWorkerMgr_InitWorkers(const WWISEC_AK_JobWorkerMgr_InitSettings* in_implInitSettings);
    void WWISEC_AK_JobWorkerMgr_TermWorkers();
#endif
    // END AkJobWorkerMgr

#if defined(WWISEC_USE_SPATIAL_AUDIO)
// BEGIN AkSpatialAudioTypes
#define WWISEC_AK_MAX_REFLECT_ORDER 4
#define WWISEC_AK_MAX_REFLECTION_PATH_LENGTH (WWISEC_AK_MAX_REFLECT_ORDER + 4)
#define WWISEC_AK_MAX_SOUND_PROPAGATION_DEPTH 8
#define WWISEC_AK_MAX_SOUND_PROPAGATION_WIDTH 32
#define WWISEC_AK_DEFAULT_MOVEMENT_THRESHOLD (1.0f)
#define WWISEC_AK_SA_EPSILON (0.001f)
#define WWISEC_AK_SA_DIFFRACTION_EPSILON (0.002f)       // Radians
#define WWISEC_AK_SA_DIFFRACTION_DOT_EPSILON (0.000002) // 1.f - cos(AK_SA_DIFFRACTION_EPSILON)
#define WWISEC_AK_SA_PLANE_THICKNESS (0.01f)
#define WWISEC_AK_SA_MIN_ENVIRONMENT_ABSORPTION (0.1f)
#define WWISEC_AK_SA_MIN_ENVIRONMENT_SURFACE_AREA (1.0f)

    const AkUInt32 WWISEC_kDefaultDiffractionMaxEdges = 8;
    const AkUInt32 WWISEC_kDefaultDiffractionMaxPaths = 8;

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

    static const AkGameObjectID WWISEC_OutdoorsGameObjID = (AkGameObjectID)-4;

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
        AkUInt32 uNumTexture;                              ///< Number of valid textures in the texture array.
        AkUniqueID arTextureID[WWISEC_AK_MAX_NUM_TEXTURE]; ///< Unique IDs of the Acoustics Texture ShareSets used to filter this image source.
    } WWISEC_AkImageSourceTexture;

    typedef struct WWISEC_AkImageSourceParams
    {
        struct AkVector64 sourcePosition; ///< Image source position, relative to the world.
        AkReal32 fDistanceScalingFactor;  ///< Image source distance scaling. This number effectively scales the sourcePosition vector with respect to the listener and, consequently, scales distance and preserves orientation.
        AkReal32 fLevel;                  ///< Game-controlled level for this source, linear.
        AkReal32 fDiffraction;            ///< Diffraction amount, normalized to the range [0,1].
        AkReal32 fOcclusion;              ///< Portal occlusion amount, in the range [0,1].
        AkUInt8 uDiffractionEmitterSide;  ///< If there is a shadow zone diffraction just after the emitter in the reflection path, indicates the number of diffraction edges, otherwise 0 if no diffraction.
        AkUInt8 uDiffractionListenerSide; ///< If there is a shadow zone diffraction before reaching the listener in the reflection path, indicates the number of diffraction edges, otherwise 0 if no diffraction.
    } WWISEC_AkImageSourceParams;

    typedef struct WWISEC_AkReflectImageSource
    {
        AkImageSourceID uID; ///< Image source ID (for matching delay lines across frames)
        WWISEC_AkImageSourceParams params;
        WWISEC_AkImageSourceTexture texture;
        WWISEC_AkImageSourceName name;
    } WWISEC_AkReflectImageSource;

    /// Data structure sent by the game to an instance of the Reflect plug-in.
    typedef struct WWISEC_AkReflectGameData
    {
        AkGameObjectID listenerID;                ///< ID of the listener used to compute spatialization and distance evaluation from within the targeted Reflect plug-in instance. It needs to be one of the listeners that are listening to the game object associated with the targeted plug-in instance. See AK::SoundEngine::SetListeners and AK::SoundEngine::SetGameObjectAuxSendValues.
        AkUInt32 uNumImageSources;                ///< Number of image sources passed in the variable array, below.
        WWISEC_AkReflectImageSource arSources[1]; ///< Variable array of image sources. You should allocate storage for the structure by calling AkReflectGameData::GetSize() with the desired number of sources.
    } WWISEC_AkReflectGameData;
    // END AkReflectGameData

    // BEGIN AkSpatialAudio
    /// Initialization settings of the spatial audio module.
    enum
    {
        WWISEC_AkTransmissionOperation_Add,      ///< Transmission loss of each hit surface is summed until it reaches 100%.
        WWISEC_AkTransmissionOperation_Multiply, ///< The inverse of transmission loss (1 - TL) is multiplied in succession, and the result inverted. With each hit surface, the effect of additional transmission loss is reduced. The total loss will approach but never reach 100% unless a surface with 100% loss is found.
        WWISEC_AkTransmissionOperation_Max,      ///< The highest transmission loss of all hit surfaces is used.
        WWISEC_AkTransmissionOperation_Default = WWISEC_AkTransmissionOperation_Max,
    };
    typedef AkUInt8 WWISEC_AkTransmissionOperation;

    typedef struct WWISEC_AkSpatialAudioInitSettings
    {
        AkUInt32 uMaxSoundPropagationDepth;                    ///< Maximum number of portals that sound can propagate through; must be less than or equal to AK_MAX_SOUND_PROPAGATION_DEPTH.
        AkReal32 fMovementThreshold;                           ///< Amount that an emitter or listener has to move to trigger a validation of reflections/diffraction. Larger values can reduce the CPU load at the cost of reduced accuracy. Note that the ray tracing itself is not affected by this value. Rays are cast each time a Spatial Audio update is executed.
        AkUInt32 uNumberOfPrimaryRays;                         ///< The number of primary rays used in the ray tracing engine. A larger number of rays will increase the chances of finding reflection and diffraction paths, but will result in higher CPU usage. When CPU limit is active (see \ref AkSpatialAudioInitSettings::fCPULimitPercentage), this setting represents the maximum allowed number of primary rays.
        AkUInt32 uMaxReflectionOrder;                          ///< Maximum reflection order [1, 4] - the number of 'bounces' in a reflection path. A high reflection order renders more details at the expense of higher CPU usage.
        AkUInt32 uMaxDiffractionOrder;                         ///< Maximum diffraction order [1, 8] - the number of 'bends' in a diffraction path. A high diffraction order accommodates more complex geometry at the expense of higher CPU usage.
                                                               ///< Diffraction must be enabled on the geometry to find diffraction paths (refer to \c AkGeometryParams). Set to 0 to disable diffraction on all geometry.
                                                               ///< This parameter limits the recursion depth of diffraction rays cast from the listener to scan the environment, and also the depth of the diffraction search to find paths between emitter and listener.
                                                               ///< To optimize CPU usage, set it to the maximum number of edges you expect the obstructing geometry to traverse.
                                                               ///< For example, if box-shaped geometry is used exclusively, and only a single box is expected between an emitter and then listener, limiting \c uMaxDiffractionOrder to 2 may be sufficient.
                                                               ///< A diffraction path search starts from the listener, so when the maximum diffraction order is exceeded, the remaining geometry between the end of the path and the emitter is ignored.
                                                               ///< In such case, where the search is terminated before reaching the emitter, the diffraction coefficient will be underestimated. It is calculated from a partial path, ignoring any remaining geometry.
        AkUInt32 uMaxDiffractionPaths;                         ///< Limit the maximum number of diffraction paths computed per emitter, excluding the direct/transmission path. The acoustics engine searches for up to uMaxDiffractionPaths paths and stops searching when this limit is reached.
                                                               ///< Setting a low number for uMaxDiffractionPaths (1-4) uses fewer CPU resources, but is more likely to cause discontinuities in the resulting audio. This can occur, for example, when a more prominent path is discovered, displacing a less prominent one.
                                                               ///< Conversely, a larger number (8 or more) produces higher quality output but requires more CPU resources. The recommended range is 2-8.
        AkUInt32 uMaxGlobalReflectionPaths;                    ///< [\ref spatial_audio_experimental "Experimental"] Set a global reflection path limit among all sound emitters with early reflections enabled. Potential reflection paths, discovered by raycasting, are first sorted according to a heuristic to determine which paths are the most prominent.
                                                               ///< Afterwards, the full reflection path calculation is performed on only the uMaxGlobalReflectionPaths, most prominent paths. Limiting the total number of reflection path calculations can significantly reduce CPU usage. Recommended range: 10-50.
                                                               ///< Set to 0 to disable the limit. In this case, the number of paths computed is unbounded and depends on how many are discovered by raycasting.
        AkUInt32 uMaxEmitterRoomAuxSends;                      ///< The maximum number of game-defined auxiliary sends that can originate from a single emitter. An emitter can send to its own room, and to all adjacent rooms if the emitter and listener are in the same room. If a limit is set, the most prominent sends are kept, based on spread to the adjacent portal from the emitters perspective.
                                                               ///< Set to 1 to only allow emitters to send directly to their current room, and to the room a listener is transitioning to if inside a portal. Set to 0 to disable the limit.
        AkUInt32 uDiffractionOnReflectionsOrder;               ///< The maximum possible number of diffraction points at each end of a reflection path. Diffraction on reflection allows reflections to fade in and out smoothly as the listener or emitter moves in and out of the reflection's shadow zone.
                                                               ///< When greater than zero, diffraction rays are sent from the listener to search for reflections around one or more corners from the listener.
                                                               ///< Diffraction must be enabled on the geometry to find diffracted reflections (refer to \c AkGeometryParams). Set to 0 to disable diffraction on reflections.
                                                               ///< To allow reflections to propagate through portals without being cut off, set \c uDiffractionOnReflectionsOrder to 2 or greater.
        AkReal32 fMaxDiffractionAngleDegrees;                  ///< The largest possible diffraction value, in degrees, beyond which paths are not computed and are inaudible. Must be greater than zero. Default value: 180 degrees.
                                                               ///< A large value (for example, 360 degrees) allows paths to propagate further around corners and obstacles, but takes more CPU time to compute.
                                                               ///< A gain is applied to each diffraction path to taper the volume of the path to zero as the diffraction angle approaches fMaxDiffractionAngleDegrees,
                                                               ///< and appears in the Voice Inspector as "Propagation Path Gain". This tapering gain is applied in addition to the diffraction curves, and prevents paths from popping in or out suddenly when the maximum diffraction angle is exceeded.
                                                               ///< In Wwise Authoring, the horizontal axis of a diffraction curve in the attenuation editor is defined over the range 0-100%, corresponding to angles 0-180 degrees.
                                                               ///< If fMaxDiffractionAngleDegrees is greater than 180 degrees, diffraction coefficients over 100% are clamped and the curve is evaluated at the rightmost point.
        AkReal32 fMaxPathLength;                               ///< The total length of a path composed of a sequence of segments (or rays) cannot exceed the defined maximum path length. High values compute longer paths but increase the CPU cost.
                                                               ///< Each individual sound is also affected by its maximum attenuation distance, specified in the Authoring tool. Reflection or diffraction paths, calculated inside Spatial Audio, will never exceed a sound's maximum attenuation distance.
                                                               ///< Note, however, that attenuation is considered infinite if the furthest point is above the audibility threshold.
        AkReal32 fCPULimitPercentage;                          ///< Defines the targeted computation time allocated for the ray tracing engine. Defined as a percentage [0, 100] of the current audio frame. The ray tracing engine dynamically adapts the number of primary rays to target the specified computation time value. In all circumstances, the computed number of primary rays cannot exceed the number of primary rays specified by AkSpatialAudioInitSettings::uNumberOfPrimaryRays.
                                                               ///< A value of 0 indicates no target has been set. In this case, the number of primary rays is fixed and is set by AkSpatialAudioInitSettings::uNumberOfPrimaryRays.
        AkReal32 fSmoothingConstantMs;                         ///< [\ref spatial_audio_experimental "Experimental"]  Enable parameter smoothing on the diffraction paths output from the Acoustics Engine. Set fSmoothingConstantMs to a value greater than 0 to define the time constant (in milliseconds) for parameter smoothing.
                                                               ///< The time constant of an exponential moving average is the amount of time for the smoothed response of a unit step function to reach 1 - 1/e ~= 63.2% of the original signal.
                                                               ///< A large value (eg. 500-1000 ms) results in less variance but introduces lag, which is a good choice when using conservative values for uNumberOfPrimaryRays (eg. 5-10), uMaxDiffractionPaths (eg. 1-3) or fMovementThreshold ( > 1m ), in order to reduce overall CPU cost.
                                                               ///< A small value (eg. 10-100 ms) results in greater accuracy and faster convergence of rendering parameters. Set to 0 to disable path smoothing.
        AkUInt32 uLoadBalancingSpread;                         ///< Spread the computation of paths on uLoadBalancingSpread frames [1..[. When uLoadBalancingSpread is set to 1, no load balancing is done. Values greater than 1 indicate the computation of paths will be spread on this number of frames.
        bool bEnableGeometricDiffractionAndTransmission;       ///< Enable computation of geometric diffraction and transmission paths for all sources that have the <b>Enable Diffraction and Transmission</b> box checked in the Positioning tab of the Wwise Property Editor.
                                                               ///< This flag enables sound paths around (diffraction) and through (transmission) geometry (see \c AK::SpatialAudio::SetGeometry).
                                                               ///< Setting \c bEnableGeometricDiffractionAndTransmission to false implies that geometry is only to be used for reflection calculation.
                                                               ///< Diffraction edges must be enabled on geometry for diffraction calculation (see \c AkGeometryParams).
                                                               ///< If \c bEnableGeometricDiffractionAndTransmission is false but a sound has <b>Enable Diffraction and Transmission</b> selected in the Positioning tab of the authoring tool, the sound will diffract through portals but will pass through geometry as if it is not there.
                                                               ///< One would typically disable this setting in the case that the game intends to perform its own obstruction calculation, but geometry is still passed to spatial audio for reflection calculation.
        bool bCalcEmitterVirtualPosition;                      ///< An emitter that is diffracted through a portal or around geometry will have its apparent or virtual position calculated by Wwise Spatial Audio and passed on to the sound engine.
        WWISEC_AkTransmissionOperation eTransmissionOperation; ///< The operation used to determine transmission loss on direct paths.
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
        struct AkVector64 imageSource;

        /// Vertices of the indirect path.
        /// pathPoint[0] is closest to the emitter, pathPoint[numPathPoints-1] is closest to the listener.
        struct AkVector64 pathPoint[WWISEC_AK_MAX_REFLECTION_PATH_LENGTH];

        /// The texture that were hit in the path.
        /// textureIDs[0] is closest to the emitter, textureIDs[numPathPoints-1] is closest to the listener.
        AkUInt32 textureIDs[WWISEC_AK_MAX_REFLECTION_PATH_LENGTH];

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
        struct AkVector64 nodes[WWISEC_AK_MAX_SOUND_PROPAGATION_DEPTH];

        /// Emitter position. This is the source position for an emitter. In all cases, except for radial emitters, it is the same position as the game object position.
        /// For radial emitters, it is the calculated position at the edge of the volume.
        struct AkVector64 emitterPos;

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
        struct AkWorldTransform virtualPos;

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

        /// Occlusion value for this path
        /// This value includes the accumulated portal occlusion for all portals along the path.
        AkReal32 occlusionValue;

        /// Propagation path gain.
        /// Includes volume tapering gain to ensure that diffraction paths do not cut in or out when the maximum diffraction angle is exceeded.
        AkReal32 gain;
    } WWISEC_AkDiffractionPathInfo;

    /// Parameters passed to \c SetPortal
    typedef struct WWISEC_AkPortalParams
    {
        /// Portal's position and orientation in the 3D world.
        /// Position vector is the center of the opening.
        /// OrientationFront vector must be unit-length and point along the normal of the portal, and must be orthogonal to Up. It defines the local positive-Z dimension (depth/transition axis) of the portal, used by Extent.
        /// OrientationTop vector must be unit-length and point along the top of the portal (tangent to the wall), must be orthogonal to Front. It defines the local positive-Y direction (height) of the portal, used by Extent.
        struct AkWorldTransform Transform;

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
        struct AkVector Front;

        /// Room Orientation. Up and Front must be orthonormal.
        /// Room orientation has an effect when the associated aux bus (see ReverbAuxBus) is set with 3D Spatialization in Wwise, as 3D Spatialization implements relative rotation of the emitter (room) and listener.
        struct AkVector Up;

        /// The reverb aux bus that is associated with this room.
        /// When Spatial Audio is told that a game object is in a particular room via SetGameObjectInRoom, a send to this aux bus will be created to model the reverb of the room.
        /// Using a combination of Rooms and Portals, Spatial Audio manages which game object the aux bus is spawned on, and what control gain is sent to the bus.
        /// When a game object is inside a connected portal, as defined by the portal's orientation and extent vectors, both this aux send and the aux send of the adjacent room are active.
        /// Spatial audio modulates the control value for each send based on the game object's position, in relation to the portal's z-azis and extent, to crossfade the reverb between the two rooms.
        /// If more advanced control of reverb is desired, SetGameObjectAuxSendValues can be used to add additional sends on to a game object.
        /// - \ref AK::SpatialAudio::SetGameObjectInRoom
        /// - \ref AK::SoundEngine::SetGameObjectAuxSendValues
        AkAuxBusID ReverbAuxBus;

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

        AkReal32 RoomPriority;
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
        struct AkWorldTransform PositionAndOrientation;

        /// Set the 3-dimensional scaling of the geometry instance.
        /// \sa
        /// - \ref AK::SpatialAudio::SetGeometryInstance
        ///	- \ref AK::SpatialAudio::RemoveGeometryInstance
        struct AkVector Scale;

        /// Geometry set referenced by the instance
        /// \sa
        ///	- \ref AK::SpatialAudio::SetGeometry
        ///	- \ref AK::SpatialAudio::RemoveGeometry
        /// - \ref AK::SpatialAudio::SetGeometryInstance
        ///	- \ref AK::SpatialAudio::RemoveGeometryInstance
        WWISEC_AkGeometrySetID GeometrySetID;

        /// When enabled, the geometry instance is indexed for ray computation and used to compute reflection, diffraction, and transmission.
        /// If the geometry instance is used only for room containment, this flag must be set to false.
        ///	- \ref AK::SpatialAudio::SetRoom
        ///	- \ref AkRoomParams
        ///
        bool UseForReflectionAndDiffraction;

        /// [\ref spatial_audio_experimental "Experimental"]  When set to false (default), the intersection of the geometry instance with any portal bounding box is subtracted from the geometry. In effect, an opening is created at the portal location through which sound can pass.
        /// When set to true, portals cannot create openings in the geometry instance. Enable this to allow the geometry instance to be an obstacle to paths going into or through portal bounds.
        ///	- \ref AK::SpatialAudio::SetPortal
        ///
        bool BypassPortalSubtraction;

        /// A solid geometry instance applies transmission loss once for each time a transmission path enters and exits its volume, using the max transmission loss between each hit surface. A non-solid geometry instance is one where each surface is infinitely thin, applying transmission loss at each surface. This option has no effect if the Transmission Operation is set to Max.
        ///
        bool IsSolid;
    } WWISEC_AkGeometryInstanceParams;

    AKRESULT WWISEC_AK_SpatialAudio_Init(const WWISEC_AkSpatialAudioInitSettings* in_initSettings);
    AKRESULT WWISEC_AK_SpatialAudio_RegisterListener(AkGameObjectID in_gameObjectID);
    AKRESULT WWISEC_AK_SpatialAudio_UnregisterListener(AkGameObjectID in_gameObjectID);
    AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectRadius(AkGameObjectID in_gameObjectID, AkReal32 in_outerRadius, AkReal32 in_innerRadius);
    AKRESULT WWISEC_AK_SpatialAudio_SetImageSource(AkImageSourceID in_srcID, const WWISEC_AkImageSourceSettings* in_info, const char* in_name, AkUniqueID in_AuxBusID, AkGameObjectID in_gameObjectID);
    AKRESULT WWISEC_AK_SpatialAudio_RemoveImageSource(AkImageSourceID in_srcID, AkUniqueID in_AuxBusID, AkGameObjectID in_gameObjectID);
    AKRESULT WWISEC_AK_SpatialAudio_ClearImageSources(AkUniqueID in_AuxBusID, AkGameObjectID in_gameObjectID);
    AKRESULT WWISEC_AK_SpatialAudio_SetGeometry(WWISEC_AkGeometrySetID in_GeomSetID, const WWISEC_AkGeometryParams* in_params);
    AKRESULT WWISEC_AK_SpatialAudio_RemoveGeometry(WWISEC_AkGeometrySetID in_SetID);
    AKRESULT WWISEC_AK_SpatialAudio_SetGeometryInstance(WWISEC_AkGeometryInstanceID in_GeometryInstanceID, const WWISEC_AkGeometryInstanceParams* in_params);
    AKRESULT WWISEC_AK_SpatialAudio_RemoveGeometryInstance(WWISEC_AkGeometryInstanceID in_GeometryInstanceID);
    AKRESULT WWISEC_AK_SpatialAudio_QueryReflectionPaths(AkGameObjectID in_gameObjectID, AkUInt32 in_positionIndex, struct AkVector64* out_listenerPos, struct AkVector64* out_emitterPos, WWISEC_AkReflectionPathInfo* out_aPaths, AkUInt32* io_uArraySize);
    AKRESULT WWISEC_AK_SpatialAudio_SetRoom(WWISEC_AkRoomID in_RoomID, const WWISEC_AkRoomParams* in_Params, const char* in_RoomName);
    AKRESULT WWISEC_AK_SpatialAudio_RemoveRoom(WWISEC_AkRoomID in_RoomID);
    AKRESULT WWISEC_AK_SpatialAudio_SetPortal(WWISEC_AkPortalID in_PortalID, const WWISEC_AkPortalParams* in_Params, const char* in_PortalName);
    AKRESULT WWISEC_AK_SpatialAudio_RemovePortal(WWISEC_AkPortalID in_PortalID);
    AKRESULT WWISEC_AK_SpatialAudio_SetReverbZone(WWISEC_AkRoomID in_ReverbZone, WWISEC_AkRoomID in_ParentRoom, AkReal32 in_transitionRegionWidth);
    AKRESULT WWISEC_AK_SpatialAudio_RemoveReverbZone(WWISEC_AkRoomID in_ReverbZone);
    AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectInRoom(AkGameObjectID in_gameObjectID, WWISEC_AkRoomID in_CurrentRoomID);
    AKRESULT WWISEC_AK_SpatialAudio_UnsetGameObjectInRoom(AkGameObjectID in_gameObjectID);
    AKRESULT WWISEC_AK_SpatialAudio_SetReflectionsOrder(AkUInt32 in_uReflectionsOrder, bool in_bUpdatePaths);
    AKRESULT WWISEC_AK_SpatialAudio_SetDiffractionOrder(AkUInt32 in_uDiffractionOrder, bool in_bUpdatePaths);
    AKRESULT WWISEC_AK_SpatialAudio_SetMaxGlobalReflectionPaths(AkUInt32 in_uMaxGlobalReflectionPaths);
    AKRESULT WWISEC_AK_SpatialAudio_SetMaxDiffractionPaths(AkUInt32 in_uMaxDiffractionPaths, AkGameObjectID in_gameObjectID);
    AKRESULT WWISEC_AK_SpatialAudio_SetMaxEmitterRoomAuxSends(AkUInt32 in_uMaxEmitterRoomAuxSends);
    AKRESULT WWISEC_AK_SpatialAudio_SetNumberOfPrimaryRays(AkUInt32 in_uNbPrimaryRays);
    AKRESULT WWISEC_AK_SpatialAudio_SetLoadBalancingSpread(AkUInt32 in_uNbFrames);
    AKRESULT WWISEC_AK_SpatialAudio_SetSmoothingConstant(AkReal32 in_fSmoothingConstantMs, AkGameObjectID in_gameObjectID);
    AKRESULT WWISEC_AK_SpatialAudio_SetEarlyReflectionsAuxSend(AkGameObjectID in_gameObjectID, AkAuxBusID in_auxBusID);
    AKRESULT WWISEC_AK_SpatialAudio_SetEarlyReflectionsVolume(AkGameObjectID in_gameObjectID, AkReal32 in_fSendVolume);
    AKRESULT WWISEC_AK_SpatialAudio_SetPortalObstructionAndOcclusion(WWISEC_AkPortalID in_PortalID, AkReal32 in_fObstruction, AkReal32 in_fOcclusion);
    AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectToPortalObstruction(AkGameObjectID in_gameObjectID, WWISEC_AkPortalID in_PortalID, AkReal32 in_fObstruction);
    AKRESULT WWISEC_AK_SpatialAudio_SetPortalToPortalObstruction(WWISEC_AkPortalID in_PortalID0, WWISEC_AkPortalID in_PortalID1, AkReal32 in_fObstruction);
    AKRESULT WWISEC_AK_SpatialAudio_QueryWetDiffraction(WWISEC_AkPortalID in_portal, AkReal32* out_wetDiffraction);
    AKRESULT WWISEC_AK_SpatialAudio_QueryDiffractionPaths(AkGameObjectID in_gameObjectID, AkUInt32 in_positionIndex, struct AkVector64* out_listenerPos, struct AkVector64* out_emitterPos, WWISEC_AkDiffractionPathInfo* out_aPaths, AkUInt32* io_uArraySize);
    AKRESULT WWISEC_AK_SpatialAudio_SetTransmissionOperation(WWISEC_AkTransmissionOperation in_eOperation);
    AKRESULT WWISEC_AK_SpatialAudio_ResetStochasticEngine();
    // END AkSpatialAudio

    // BEGIN AkReverbEstimation
    float WWISEC_AK_SpatialAudio_ReverbEstimation_CalculateSlope(const WWISEC_AkAcousticTexture* texture);
    void WWISEC_AK_SpatialAudio_ReverbEstimation_GetAverageAbsorptionValues(WWISEC_AkAcousticTexture* in_textures, float* in_surfaceAreas, int in_numTextures, WWISEC_AkAcousticTexture* out_average);
    AKRESULT WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateT60Decay(AkReal32 in_volumeCubicMeters, AkReal32 in_surfaceAreaSquaredMeters, AkReal32 in_environmentAverageAbsorption, AkReal32* out_decayEstimate);
    AKRESULT WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateTimeToFirstReflection(struct AkVector in_environmentExtentMeters, AkReal32* out_timeToFirstReflectionMs, AkReal32 in_speedOfSound);
    AkReal32 WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateHFDamping(WWISEC_AkAcousticTexture* in_textures, float* in_surfaceAreas, int in_numTextures);
    // END AkReverbEstimation
#endif

// BEGIN Platform-specific AkSoundEngine functions
#if defined(AK_WIN)
    typedef struct IMMDevice IMMDevice;

    AkUInt32 WWISEC_AK_GetDeviceID(IMMDevice* in_pDevice);

    AkUInt32 WWISEC_AK_GetDeviceIDFromName(wchar_t* in_szToken);

    const wchar_t* WWISEC_AK_GetWindowsDeviceName(AkInt32 index, AkUInt32* out_uDeviceID, enum AkAudioDeviceState uDeviceStateMask);

    AkUInt32 WWISEC_AK_GetWindowsDeviceCount(enum AkAudioDeviceState uDeviceStateMask);

    bool WWISEC_AK_GetWindowsDevice(AkInt32 in_index, AkUInt32* out_uDeviceID, IMMDevice** out_ppDevice, enum AkAudioDeviceState uDeviceStateMask);
#endif

#if defined(AK_ANDROID)
    WWISEC_SLObjectItf WWISEC_AK_SoundEngine_GetWwiseOpenSLInterface();

    AKRESULT WWISEC_AK_SoundEngine_GetFastPathSettings(WWISEC_AkInitSettings* in_settings, WWISEC_AkPlatformInitSettings* in_pfSettings);
#endif

#if defined(AK_IOS)
    void WWISEC_AK_SoundEngine_iOS_ChangeAudioSessionProperties(const WWISEC_AkAudioSessionProperties* in_properties);
#endif
    // END Platform-specific AkSoundEngine functions

#ifdef __cplusplus
}
#endif