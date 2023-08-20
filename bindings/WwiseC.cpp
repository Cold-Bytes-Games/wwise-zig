/*
MIT License

Copyright (c) 2023 Cold Bytes Games

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "WwiseC.h"

#include <AK/MusicEngine/Common/AkMusicEngine.h>

#include <AK/SoundEngine/Common/AkCallback.h>
#include <AK/SoundEngine/Common/AkDynamicDialogue.h>
#include <AK/SoundEngine/Common/AkDynamicSequence.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/AkModule.h>
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/SoundEngine/Common/AkTypes.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <Ak/SoundEngine/Common/AkVirtualAcoustics.h>
#include <Ak/SoundEngine/Common/IAkPlugin.h>

#include <new>

extern "C" void WWISEC_HACK_RegisterAllPlugins();

#define WWISEC_ASSERT_ENUM_VALUE_SAME(name) static_assert(static_cast<std::size_t>(WWISEC_##name) == static_cast<std::size_t>(name))

// BEGIN AkTypes
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_UnknownFileError);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_NUM_JOB_TYPES);
WWISEC_ASSERT_ENUM_VALUE_SAME(AkDeviceState_All);
WWISEC_ASSERT_ENUM_VALUE_SAME(ConnectionType_Direct);
WWISEC_ASSERT_ENUM_VALUE_SAME(ConnectionType_GameDefSend);
WWISEC_ASSERT_ENUM_VALUE_SAME(ConnectionType_UserDefSend);
WWISEC_ASSERT_ENUM_VALUE_SAME(ConnectionType_ReflectionsSend);
static_assert(sizeof(WWISEC_AkAudioSettings) == sizeof(AkAudioSettings));
static_assert(sizeof(WWISEC_AkDeviceDescription) == sizeof(AkDeviceDescription));
static_assert(sizeof(WWISEC_AkExternalSourceInfo) == sizeof(AkExternalSourceInfo));
static_assert(WWISEC_AK_COMM_DEFAULT_DISCOVERY_PORT == AK_COMM_DEFAULT_DISCOVERY_PORT);
static_assert(sizeof(WWISEC_AkAuxSendValue) == sizeof(AkAuxSendValue));
static_assert(sizeof(WWISEC_AkVector64) == sizeof(AkVector64));
static_assert(sizeof(WWISEC_AkVector) == sizeof(AkVector));
static_assert(sizeof(WWISEC_AkWorldTransform) == sizeof(AkWorldTransform));
static_assert(sizeof(WWISEC_AkTransform) == sizeof(AkTransform));
static_assert(sizeof(WWISEC_AkChannelEmitter) == sizeof(AkChannelEmitter));
static_assert(sizeof(WWISEC_AkEmitterListenerPair) == sizeof(AkEmitterListenerPair));
static_assert(sizeof(WWISEC_AkCodecDescriptor) == sizeof(AkCodecDescriptor));
// END AkTypes

// BEGIN AkMidiTypes
static_assert(sizeof(WWISEC_AkMIDIEvent_tGen) == sizeof(AkMIDIEvent::tGen));
static_assert(sizeof(WWISEC_AkMIDIEvent_tNoteOnOff) == sizeof(AkMIDIEvent::tNoteOnOff));
static_assert(sizeof(WWISEC_AkMIDIEvent_tCc) == sizeof(AkMIDIEvent::tCc));
static_assert(sizeof(WWISEC_AkMIDIEvent_tPitchBend) == sizeof(AkMIDIEvent::tPitchBend));
static_assert(sizeof(WWISEC_AkMIDIEvent_tNoteAftertouch) == sizeof(AkMIDIEvent::tNoteAftertouch));
static_assert(sizeof(WWISEC_AkMIDIEvent_tChanAftertouch) == sizeof(AkMIDIEvent::tChanAftertouch));
static_assert(sizeof(WWISEC_AkMIDIEvent_tProgramChange) == sizeof(AkMIDIEvent::tProgramChange));
static_assert(sizeof(WWISEC_AkMIDIEvent_tWwiseCmd) == sizeof(AkMIDIEvent::tWwiseCmd));
static_assert(sizeof(WWISEC_AkMIDIEvent) == sizeof(AkMIDIEvent));
static_assert(sizeof(WWISEC_AkMIDIPost) == sizeof(AkMIDIPost));
static_assert(offsetof(WWISEC_AkMIDIPost, byChan) == offsetof(AkMIDIPost, byChan));
static_assert(offsetof(WWISEC_AkMIDIPost, NoteOnOff.byNote) == offsetof(AkMIDIPost, NoteOnOff.byNote));
static_assert(offsetof(WWISEC_AkMIDIPost, NoteOnOff.byVelocity) == offsetof(AkMIDIPost, NoteOnOff.byVelocity));
static_assert(offsetof(WWISEC_AkMIDIPost, WwiseCmd.uCmd) == offsetof(AkMIDIPost, WwiseCmd.uCmd));
static_assert(offsetof(WWISEC_AkMIDIPost, WwiseCmd.uArg) == offsetof(AkMIDIPost, WwiseCmd.uArg));
// END AkMidiTypes

// BEGIN AkCommonDefs
static_assert(WWISEC_AK_INT == AK_INT);
static_assert(WWISEC_AK_FLOAT == AK_FLOAT);
static_assert(sizeof(WWISEC_AK_AkMetering) == sizeof(AK::AkMetering));
static_assert(sizeof(WWISEC_AkAudioBuffer) == sizeof(AkAudioBuffer));

void WWISEC_AkAudioBuffer_ClearData(WWISEC_AkAudioBuffer* instance)
{
    reinterpret_cast<AkAudioBuffer*>(instance)->ClearData();
}

void WWISEC_AkAudioBuffer_Clear(WWISEC_AkAudioBuffer* instance)
{
    reinterpret_cast<AkAudioBuffer*>(instance)->Clear();
}

AkUInt32 WWISEC_AkAudioBuffer_NumChannels(const WWISEC_AkAudioBuffer* instance)
{
    return reinterpret_cast<const AkAudioBuffer*>(instance)->NumChannels();
}

bool WWISEC_AkAudioBufer_HasLFE(const WWISEC_AkAudioBuffer* instance)
{
    return reinterpret_cast<const AkAudioBuffer*>(instance)->HasLFE();
}

WWISEC_AkChannelConfig WWISEC_AkAudioBuffer_GetChannelConfig(const WWISEC_AkAudioBuffer* instance)
{
    return static_cast<WWISEC_AkChannelConfig>(reinterpret_cast<const AkAudioBuffer*>(instance)->GetChannelConfig().Serialize());
}

void* WWISEC_AkAudioBuffer_GetInterleavedData(WWISEC_AkAudioBuffer* instance)
{
    return reinterpret_cast<AkAudioBuffer*>(instance)->GetInterleavedData();
}

void WWISEC_AkAudioBuffer_AttachInterleavedData(WWISEC_AkAudioBuffer* instance, void* in_pData, AkUInt16 in_uMaxFrames, AkUInt16 in_uValidFrames)
{
    reinterpret_cast<AkAudioBuffer*>(instance)->AttachInterleavedData(in_pData, in_uMaxFrames, in_uValidFrames);
}

void WWISEC_AkAudioBuffer_AttachInterleavedData1(WWISEC_AkAudioBuffer* instance, void* in_pData, AkUInt16 in_uMaxFrames, AkUInt16 in_uValidFrames, WWISEC_AkChannelConfig in_channelConfig)
{
    AkChannelConfig converted_channel_config;
    converted_channel_config.Deserialize(in_channelConfig);

    reinterpret_cast<AkAudioBuffer*>(instance)->AttachInterleavedData(in_pData, in_uMaxFrames, in_uValidFrames, converted_channel_config);
}

bool WWISEC_AkAudioBuffer_HasData(const WWISEC_AkAudioBuffer* instance)
{
    return reinterpret_cast<const AkAudioBuffer*>(instance)->HasData();
}

AkUInt32 WWISEC_AkAudioBuffer_StandardToPipelineIndex(WWISEC_AkChannelConfig in_channelConfig, AkUInt32 in_uChannelIdx)
{
    AkChannelConfig converted_channel_config;
    converted_channel_config.Deserialize(in_channelConfig);
    return AkAudioBuffer::StandardToPipelineIndex(converted_channel_config, in_uChannelIdx);
}

WWISEC_AkSampleType* WWISEC_AkAudioBuffer_GetChannel(WWISEC_AkAudioBuffer* instance, AkUInt32 in_uIndex)
{
    return reinterpret_cast<WWISEC_AkSampleType*>(reinterpret_cast<AkAudioBuffer*>(instance)->GetChannel(in_uIndex));
}

WWISEC_AkSampleType* WWISEC_AkAudioBuffer_GetLFE(WWISEC_AkAudioBuffer* instance)
{
    return reinterpret_cast<WWISEC_AkSampleType*>(reinterpret_cast<AkAudioBuffer*>(instance)->GetLFE());
}

void WWISEC_AkAudioBuffer_ZeroPadToMaxFrames(WWISEC_AkAudioBuffer* instance)
{
    reinterpret_cast<AkAudioBuffer*>(instance)->ZeroPadToMaxFrames();
}

void WWISEC_AkAudioBuffer_AttachContiguousDeinterleavedData(WWISEC_AkAudioBuffer* instance, void* in_pData, AkUInt16 in_uMaxFrames, AkUInt16 in_uValidFrames, WWISEC_AkChannelConfig in_channelConfig)
{
    AkChannelConfig converted_channel_config;
    converted_channel_config.Deserialize(in_channelConfig);

    reinterpret_cast<AkAudioBuffer*>(instance)->AttachContiguousDeinterleavedData(in_pData, in_uMaxFrames, in_uValidFrames, converted_channel_config);
}

void* WWISEC_AkAudioBuffer_DetachContiguousDeinterleavedData(WWISEC_AkAudioBuffer* instance)
{
    return reinterpret_cast<AkAudioBuffer*>(instance)->DetachContiguousDeinterleavedData();
}

bool WWISEC_AkAudioBuffer_CheckValidSamples(WWISEC_AkAudioBuffer* instance)
{
    return reinterpret_cast<AkAudioBuffer*>(instance)->CheckValidSamples();
}

void WWISEC_AkAudioBuffer_RelocateMedia(WWISEC_AkAudioBuffer* instance, AkUInt8* in_pNewMedia, AkUInt8* in_pOldMedia)
{
    reinterpret_cast<AkAudioBuffer*>(instance)->RelocateMedia(in_pNewMedia, in_pOldMedia);
}

AkUInt16 WWISEC_AkAudioBuffer_MaxFrames(const WWISEC_AkAudioBuffer* instance)
{
    return reinterpret_cast<const AkAudioBuffer*>(instance)->MaxFrames();
}
// END AkCcommonDefs

// BEGIN AkCallback
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_EndOfEvent);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_EndOfDynamicSequenceItem);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_Marker);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_Duration);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_SpeakerVolumeMatrix);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_Starvation);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MusicPlaylistSelect);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MusicPlayStarted);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MusicSyncBeat);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MusicSyncBar);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MusicSyncEntry);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MusicSyncExit);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MusicSyncGrid);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MusicSyncUserCue);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MusicSyncPoint);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MusicSyncAll);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MIDIEvent);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_CallbackBits);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_EnableGetSourcePlayPosition);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_EnableGetMusicPlayPosition);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_EnableGetSourceStreamBuffering);
static_assert(sizeof(WWISEC_AkCallbackInfo) == sizeof(AkCallbackInfo));
static_assert(sizeof(WWISEC_AkEventCallbackInfo) == sizeof(AkEventCallbackInfo));
static_assert(sizeof(WWISEC_AkMarkerCallbackInfo) == sizeof(AkMarkerCallbackInfo));
static_assert(sizeof(WWISEC_AkDurationCallbackInfo) == sizeof(AkDurationCallbackInfo));
static_assert(sizeof(WWISEC_AkDynamicSequenceItemCallbackInfo) == sizeof(AkDynamicSequenceItemCallbackInfo));
static_assert(sizeof(WWISEC_AkSpeakerVolumeMatrixCallbackInfo) == sizeof(AkSpeakerVolumeMatrixCallbackInfo));
static_assert(sizeof(WWISEC_AkBusMeteringCallbackInfo) == sizeof(AkBusMeteringCallbackInfo));
static_assert(sizeof(WWISEC_AkOutputDeviceMeteringCallbackInfo) == sizeof(AkOutputDeviceMeteringCallbackInfo));
static_assert(sizeof(WWISEC_AkMusicPlaylistCallbackInfo) == sizeof(AkMusicPlaylistCallbackInfo));
static_assert(sizeof(WWISEC_AkSegmentInfo) == sizeof(AkSegmentInfo));
static_assert(sizeof(WWISEC_AkMusicSyncCallbackInfo) == sizeof(AkMusicSyncCallbackInfo));
static_assert(sizeof(WWISEC_AkResourceMonitorDataSummary) == sizeof(AkResourceMonitorDataSummary));
// END AkCallback

// BEGIN AkVirtualAcoustics
static_assert(sizeof(WWISEC_AkAcousticTexture) == sizeof(AkAcousticTexture));
// END AkVirtualAcoustics

// BEGIN AkMemoryMgr
WWISEC_ASSERT_ENUM_VALUE_SAME(AkMemID_NUM);
static_assert(sizeof(WWISEC_AK_MemoryMgr_CategoryStats) == sizeof(AK::MemoryMgr::CategoryStats));
static_assert(sizeof(WWISEC_AK_MemoryMgr_GlobalStats) == sizeof(AK::MemoryMgr::GlobalStats));

bool WWISEC_AK_MemoryMgr_IsInitialized()
{
    return AK::MemoryMgr::IsInitialized();
}

void WWISEC_AK_MemoryMgr_Term()
{
    AK::MemoryMgr::Term();
}

void WWISEC_AK_MemoryMgr_InitForThread()
{
    AK::MemoryMgr::InitForThread();
}

void WWISEC_AK_MemoryMgr_TermForThread()
{
    AK::MemoryMgr::TermForThread();
}

void* WWISEC_AK_MemoryMgr_Malloc(WWISEC_AkMemPoolId in_poolId, size_t in_uSize)
{
    return AK::MemoryMgr::Malloc(static_cast<AkMemPoolId>(in_poolId), in_uSize);
}

void* WWISEC_AK_MemoryMgr_ReallocAligned(WWISEC_AkMemPoolId in_poolId, void* in_pAlloc, size_t in_uSize, AkUInt32 in_uAlignment)
{
    return AK::MemoryMgr::ReallocAligned(static_cast<AkMemPoolId>(in_poolId), in_pAlloc, in_uSize, in_uAlignment);
}

void WWISEC_AK_MemoryMgr_Free(WWISEC_AkMemPoolId in_poolId, void* in_pMemAddress)
{
    AK::MemoryMgr::Free(in_poolId, in_pMemAddress);
}

void* WWISEC_AK_MemoryMgr_Malign(WWISEC_AkMemPoolId in_poolId, size_t in_USize, AkUInt32 in_uAlignment)
{
    return AK::MemoryMgr::Malign(in_poolId, in_USize, in_uAlignment);
}

void WWISEC_AK_MemoryMgr_GetCategoryStats(WWISEC_AkMemPoolId in_poolId, WWISEC_AK_MemoryMgr_CategoryStats* out_poolStats)
{
    AK::MemoryMgr::GetCategoryStats(in_poolId, *reinterpret_cast<AK::MemoryMgr::CategoryStats*>(out_poolStats));
}

void WWISEC_AK_MemoryMgr_GetGlobalStats(WWISEC_AK_MemoryMgr_GlobalStats* out_stats)
{
    AK::MemoryMgr::GetGlobalStats(*reinterpret_cast<AK::MemoryMgr::GlobalStats*>(out_stats));
}

void WWISEC_AK_MemoryMgr_StartProfileThreadUsage()
{
    AK::MemoryMgr::StartProfileThreadUsage();
}

AkUInt64 WWISEC_AK_MemoryMgr_StopProfileThreadUsage()
{
    return AK::MemoryMgr::StopProfileThreadUsage();
}

void WWISEC_AK_MemoryMgr_DumpToFile(const AkOSChar* pszFilename)
{
    AK::MemoryMgr::DumpToFile(pszFilename);
}
// END AkMemoryMgr

// BEGIN AkModule
static_assert(sizeof(WWISEC_AkMemSettings) == sizeof(AkMemSettings));

WWISEC_AKRESULT WWISEC_AK_MemoryMgr_Init(WWISEC_AkMemSettings* in_pSettings)
{
    return static_cast<WWISEC_AKRESULT>(AK::MemoryMgr::Init(reinterpret_cast<AkMemSettings*>(in_pSettings)));
}

void WWISEC_AK_MemoryMgr_GetDefaultSettings(WWISEC_AkMemSettings* out_pMemSettings)
{
    AK::MemoryMgr::GetDefaultSettings(*reinterpret_cast<AkMemSettings*>(out_pMemSettings));
}

// END AkModule

// BEGIN IAkPlugin
WWISEC_AK_IAkStreamMgr* WWISEC_AK_IAkGlobalPluginContext_GetStreamMgr(const WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<WWISEC_AK_IAkStreamMgr*>(reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetStreamMgr());
}

AkUInt16 WWISEC_AK_IAkGlobalPluginContext_GetMaxBufferLength(const WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetMaxBufferLength();
}

bool WWISEC_AK_IAkGlobalPluginContext_IsRenderingOffline(const WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->IsRenderingOffline();
}

AkUInt32 WWISEC_AK_IAkGlobalPluginContext_GetSampleRate(const WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetSampleRate();
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_PostMonitorMessage(WWISEC_AK_IAkGlobalPluginContext* self, const char* in_pszError, WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->PostMonitorMessage(in_pszError, static_cast<AK::Monitor::ErrorLevel>(in_eErrorLevel)));
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterPlugin(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreatePluginCallback in_pCreateFunc, WWISEC_AkCreateParamCallback in_pCreateParamFunc)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->RegisterPlugin(
        static_cast<AkPluginType>(in_eType),
        in_ulCompanyID,
        in_ulPluginID,
        reinterpret_cast<AkCreatePluginCallback>(in_pCreateFunc),
        reinterpret_cast<AkCreateParamCallback>(in_pCreateParamFunc)));
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterCodec(WWISEC_AK_IAkGlobalPluginContext* self, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreateFileSourceCallback in_pFileCreateFunc, WWISEC_AkCreateBankSourceCallback in_pBankCreateFunc)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->RegisterCodec(in_ulCompanyID, in_ulPluginID, reinterpret_cast<AkCreateFileSourceCallback>(in_pFileCreateFunc), reinterpret_cast<AkCreateBankSourceCallback>(in_pBankCreateFunc)));
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterGlobalCallback(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->RegisterGlobalCallback(static_cast<AkPluginType>(in_eType), in_ulCompanyID, in_ulPluginID, reinterpret_cast<AkGlobalCallbackFunc>(in_pCallback), in_eLocation, in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_UnregisterGlobalCallback(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->UnregisterGlobalCallback(reinterpret_cast<AkGlobalCallbackFunc>(in_pCallback), in_eLocation));
}

WWISEC_AK_IAkPluginMemAlloc* WWISEC_AK_IAkGlobalPluginContext_GetAllocator(WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<WWISEC_AK_IAkPluginMemAlloc*>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->GetAllocator());
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_SetRTPCValue(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkRtpcID in_rtpcID, WWISEC_AkRtpcValue in_value, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->SetRTPCValue(in_rtpcID, in_value, in_gameObjectID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation));
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_SendPluginCustomGameData(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkUniqueID in_busID, WWISEC_AkGameObjectID in_busObjectID, WWISEC_AkPluginType in_eType, AkUInt32 in_uCompanyID, AkUInt32 in_uPluginID, const void* in_pData, AkUInt32 in_uSizeInBytes)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->SendPluginCustomGameData(in_busID, in_busObjectID, static_cast<AkPluginType>(in_eType), in_uCompanyID, in_uPluginID, in_pData, in_uSizeInBytes));
}

void WWISEC_AK_IAkGlobalPluginContext_ComputeAmbisonicsEncoding(WWISEC_AK_IAkGlobalPluginContext* self, AkReal32 in_fAzimuth, AkReal32 in_fElevation, WWISEC_AkChannelConfig in_cfgAmbisonics, WWISEC_AK_SpeakerVolumes_VectorPtr out_vVolumes)
{
    AkChannelConfig channelConfig;
    channelConfig.Deserialize(in_cfgAmbisonics);

    reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->ComputeAmbisonicsEncoding(in_fAzimuth, in_fElevation, channelConfig, out_vVolumes);
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_ComputeWeightedAmbisonicsDecodingFromSampledSphere(WWISEC_AK_IAkGlobalPluginContext* self, const WWISEC_AkVector* in_samples, AkUInt32 in_uNumSamples, WWISEC_AkChannelConfig in_cfgAmbisonics, WWISEC_AK_SpeakerVolumes_MatrixPtr out_mxVolume)
{
    AkChannelConfig channelConfig;
    channelConfig.Deserialize(in_cfgAmbisonics);

    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->ComputeWeightedAmbisonicsDecodingFromSampledSphere(reinterpret_cast<const AkVector*>(in_samples), in_uNumSamples, channelConfig, out_mxVolume));
}

const WWISEC_AkAcousticTexture* WWISEC_AK_IAkGlobalPluginContext_GetAcousticTexture(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkAcousticTextureID in_AcousticTextureID)
{
    return reinterpret_cast<const WWISEC_AkAcousticTexture*>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->GetAcousticTexture(in_AcousticTextureID));
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_ComputeSphericalCoordinates(const WWISEC_AK_IAkGlobalPluginContext* self, const WWISEC_AkEmitterListenerPair* in_pair, AkReal32* out_fAzimuth, AkReal32* out_fElevation)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->ComputeSphericalCoordinates(*reinterpret_cast<const AkEmitterListenerPair*>(in_pair), *out_fAzimuth, *out_fElevation));
}

const WWISEC_AkPlatformInitSettings* WWISEC_AK_IAkGlobalPluginContext_GetPlatformInitSettings(const WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<const WWISEC_AkPlatformInitSettings*>(reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetPlatformInitSettings());
}

const WWISEC_AkInitSettings* WWISEC_AK_IAkGlobalPluginContext_GetInitSettings(const WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<const WWISEC_AkInitSettings*>(reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetInitSettings());
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_GetAudioSettings(const WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkAudioSettings* out_audioSettings)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetAudioSettings(*reinterpret_cast<AkAudioSettings*>(out_audioSettings)));
}

AkUInt32 WWISEC_AK_IAkGlobalPluginContext_GetIDFromString(const WWISEC_AK_IAkGlobalPluginContext* self, const char* in_pszString)
{
    return reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetIDFromString(in_pszString);
}

WWISEC_AkPlayingID WWISEC_AK_IAkGlobalPluginContext_PostEventSync(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources, WWISEC_AkPlayingID in_PlayingID)
{
    return static_cast<WWISEC_AkPlayingID>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->PostEventSync(in_eventID, in_gameObjectID, in_uFlags, reinterpret_cast<AkCallbackFunc>(in_pfnCallback), in_pCookie, in_cExternals, reinterpret_cast<AkExternalSourceInfo*>(in_pExternalSources), in_PlayingID));
}

WWISEC_AkPlayingID WWISEC_AK_IAkGlobalPluginContext_PostMIDIOnEventSync(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkMIDIPost* in_pPosts, AkUInt16 in_uNumPosts, bool in_bAbsoluteOffsets, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, WWISEC_AkPlayingID in_playingID)
{
    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->PostMIDIOnEventSync(in_eventID, in_gameObjectID, reinterpret_cast<AkMIDIPost*>(in_pPosts), in_uNumPosts, in_bAbsoluteOffsets, in_uFlags, reinterpret_cast<AkCallbackFunc>(in_pfnCallback), in_pCookie, in_playingID);
}

WWISEC_AKRESULT WWISEC_AK_IAkGlobalPluginContext_StopMIDIOnEventSync(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkPlayingID in_playingID)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->StopMIDIOnEventSync(in_eventID, in_gameObjectID, in_playingID));
}

WWISEC_IAkPlatformContext* WWISEC_AK_IAkGlobalPluginContext_GetPlatformContext(const WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<WWISEC_IAkPlatformContext*>(reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetPlatformContext());
}

WWISEC_IAkPluginService* WWISEC_AK_IAkGlobalPluginContext_GetPluginService(const WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AK_AkPluginServiceType in_pluginService)
{
    return reinterpret_cast<WWISEC_IAkPluginService*>(reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetPluginService(static_cast<AK::AkPluginServiceType>(in_pluginService)));
}

AkUInt32 WWISEC_AK_IAkGlobalPluginContext_GetBufferTick(const WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetBufferTick();
}
// END IAkPlugin

// BEGIN AkSoundEngine
static_assert(sizeof(WWISEC_AkOutputSettings) == sizeof(AkOutputSettings));
static_assert(sizeof(WWISEC_AkInitSettings) == sizeof(AkInitSettings));
static_assert(sizeof(WWISEC_AkPlatformInitSettings) == sizeof(AkPlatformInitSettings));
static_assert(sizeof(WWISEC_AkSourceSettings) == sizeof(AkSourceSettings));
static_assert(sizeof(WWISEC_AkSourcePosition) == sizeof(AkSourcePosition));

void WWISEC_AkOutputSettings_Init(WWISEC_AkOutputSettings* outputSettings, const char* in_szDeviceShareSet, WWISEC_AkUniqueID in_idDevice, WWISEC_AkChannelConfig in_channelConfig, WWISEC_AkPanningRule in_ePanning)
{
    ::new (outputSettings) AkOutputSettings(in_szDeviceShareSet, static_cast<AkUniqueID>(in_idDevice), *reinterpret_cast<AkChannelConfig*>(&in_channelConfig), static_cast<AkPanningRule>(in_ePanning));
}

bool WWISEC_AK_SoundEngine_IsInitialized()
{
    return AK::SoundEngine::IsInitialized();
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_Init(WWISEC_AkInitSettings* in_pSettings, WWISEC_AkPlatformInitSettings* in_pPlatformSettings)
{
    WWISEC_HACK_RegisterAllPlugins();

    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::Init(reinterpret_cast<AkInitSettings*>(in_pSettings), reinterpret_cast<AkPlatformInitSettings*>(in_pPlatformSettings)));
}

void WWISEC_AK_SoundEngine_GetDefaultInitSettings(WWISEC_AkInitSettings* out_settings)
{
    AK::SoundEngine::GetDefaultInitSettings(*reinterpret_cast<AkInitSettings*>(out_settings));
}

void WWISEC_AK_SoundEngine_GetDefaultPlatformInitSettings(WWISEC_AkPlatformInitSettings* out_platformSettings)
{
    AK::SoundEngine::GetDefaultPlatformInitSettings(*reinterpret_cast<AkPlatformInitSettings*>(out_platformSettings));
}

void WWISEC_AK_SoundEngine_Term()
{
    AK::SoundEngine::Term();
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetAudioSettings(WWISEC_AkAudioSettings* out_audioSettings)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetAudioSettings(*reinterpret_cast<AkAudioSettings*>(out_audioSettings)));
}

WWISEC_AkChannelConfig WWISEC_AK_SoundEngine_GetSpeakerConfiguration(WWISEC_AkOutputDeviceID in_idOutput)
{
    return static_cast<WWISEC_AkChannelConfig>(AK::SoundEngine::GetSpeakerConfiguration(in_idOutput).Serialize());
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetOutputDeviceConfiguration(WWISEC_AkOutputDeviceID in_idOutput, WWISEC_AkChannelConfig* io_channelConfig, WWISEC_Ak3DAudioSinkCapabilities* io_capabilities)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetOutputDeviceConfiguration(in_idOutput, *reinterpret_cast<AkChannelConfig*>(io_channelConfig), *reinterpret_cast<Ak3DAudioSinkCapabilities*>(io_capabilities)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetPanningRule(WWISEC_AkPanningRule* out_ePanningRule, WWISEC_AkOutputDeviceID in_idOutput)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetPanningRule(*reinterpret_cast<AkPanningRule*>(out_ePanningRule), in_idOutput));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetPanningRule(WWISEC_AkPanningRule in_ePanningRule, WWISEC_AkOutputDeviceID in_idOutput)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetPanningRule(static_cast<AkPanningRule>(in_ePanningRule), in_idOutput));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetSpeakerAngles(AkReal32* io_pfSpeakerAngles, AkUInt32* io_uNumAngles, AkReal32* out_fHeightAngle, WWISEC_AkOutputDeviceID in_idOutput)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetSpeakerAngles(io_pfSpeakerAngles, *io_uNumAngles, *out_fHeightAngle, in_idOutput));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetSpeakerAngles(const AkReal32* in_pfSpeakerAngles, AkUInt32 in_uNumAngles, AkReal32 in_fHeightAngle, WWISEC_AkOutputDeviceID in_idOutput)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetSpeakerAngles(in_pfSpeakerAngles, in_uNumAngles, in_fHeightAngle, in_idOutput));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetVolumeThreshold(AkReal32 in_fVolumeThresholdDB)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetVolumeThreshold(in_fVolumeThresholdDB));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMaxNumVoicesLimit(AkUInt16 in_maxNumberVoices)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetMaxNumVoicesLimit(in_maxNumberVoices));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetJobMgrMaxActiveWorkers(WWISEC_AkJobType in_jobType, AkUInt32 in_uNewMaxActiveWorkers)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetJobMgrMaxActiveWorkers(in_jobType, in_uNewMaxActiveWorkers));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RenderAudio(bool in_bAllowSyncRender)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RenderAudio(in_bAllowSyncRender));
}

WWISEC_AK_IAkGlobalPluginContext* WWISEC_AK_SoundEngine_GetGlobalPluginContext()
{
    return reinterpret_cast<WWISEC_AK_IAkGlobalPluginContext*>(AK::SoundEngine::GetGlobalPluginContext());
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterPlugin(WWISEC_AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreatePluginCallback in_pCreateFunc, WWISEC_AkCreateParamCallback in_pCreateParamFunc)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterPlugin(static_cast<AkPluginType>(in_eType), in_ulCompanyID, in_ulPluginID, reinterpret_cast<AkCreatePluginCallback>(in_pCreateFunc), reinterpret_cast<AkCreateParamCallback>(in_pCreateParamFunc)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterPluginDLL(const AkOSChar* in_DllName, const AkOSChar* in_DllPath)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterPluginDLL(in_DllName, in_DllPath));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterGlobalCallback(WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation, void* in_pCookie, WWISEC_AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterGlobalCallback(reinterpret_cast<AkGlobalCallbackFunc>(in_pCallback), in_eLocation, in_pCookie, static_cast<AkPluginType>(in_eType), in_ulCompanyID, in_ulPluginID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterGlobalCallback(WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnregisterGlobalCallback(reinterpret_cast<AkGlobalCallbackFunc>(in_pCallback), in_eLocation));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterResourceMonitorCallback(WWISEC_AkResourceMonitorCallbackFunc in_pCallback)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterResourceMonitorCallback(reinterpret_cast<AkResourceMonitorCallbackFunc>(in_pCallback)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterResourceMonitorCallback(WWISEC_AkResourceMonitorCallbackFunc in_pCallback)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnregisterResourceMonitorCallback(reinterpret_cast<AkResourceMonitorCallbackFunc>(in_pCallback)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterAudioDeviceStatusCallback(WWISEC_AK_AkDeviceStatusCallbackFunc in_pCallback)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterAudioDeviceStatusCallback(reinterpret_cast<AK::AkDeviceStatusCallbackFunc>(in_pCallback)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterAudioDeviceStatusCallback()
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnregisterAudioDeviceStatusCallback());
}

AkUInt32 WWISEC_AK_SoundEngine_GetIDFromString(const char* in_pszString)
{
    return AK::SoundEngine::GetIDFromString(in_pszString);
}

WWISEC_AkPlayingID WWISEC_AK_SoundEngine_PostEvent_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources, WWISEC_AkPlayingID in_PlayingID)
{
    return AK::SoundEngine::PostEvent(
        in_eventID,
        in_gameObjectID,
        in_uFlags,
        reinterpret_cast<AkCallbackFunc>(in_pfnCallback),
        in_pCookie,
        in_cExternals,
        reinterpret_cast<AkExternalSourceInfo*>(in_pExternalSources),
        in_PlayingID);
}

WWISEC_AkPlayingID WWISEC_AK_SoundEngine_PostEvent_String(const char* in_pszEventName, WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources, WWISEC_AkPlayingID in_PlayingID)
{
    return AK::SoundEngine::PostEvent(
        in_pszEventName,
        in_gameObjectID,
        in_uFlags,
        reinterpret_cast<AkCallbackFunc>(in_pfnCallback),
        in_pCookie,
        in_cExternals,
        reinterpret_cast<AkExternalSourceInfo*>(in_pExternalSources),
        in_PlayingID);
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_ExecuteActionOnEvent_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkActionOnEventType in_ActionType, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, WWISEC_AkPlayingID in_PlayingID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::ExecuteActionOnEvent(
        in_eventID,
        static_cast<AK::SoundEngine::AkActionOnEventType>(in_ActionType),
        in_gameObjectID,
        in_uTransitionDuration,
        static_cast<AkCurveInterpolation>(in_eFadeCurve),
        in_PlayingID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_ExecuteActionOnEvent_String(const char* in_pszEventName, WWISEC_AkActionOnEventType in_ActionType, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, WWISEC_AkPlayingID in_PlayingID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::ExecuteActionOnEvent(
        in_pszEventName,
        static_cast<AK::SoundEngine::AkActionOnEventType>(in_ActionType),
        in_gameObjectID,
        in_uTransitionDuration,
        static_cast<AkCurveInterpolation>(in_eFadeCurve),
        in_PlayingID));
}

WWISEC_AkPlayingID WWISEC_AK_SoundEngine_PostMIDIOnEvent(WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkMIDIPost* in_pPosts, AkUInt16 in_uNumPosts, bool in_bAbsoluteOffsets, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, WWISEC_AkPlayingID in_playingID)
{
    return AK::SoundEngine::PostMIDIOnEvent(
        in_eventID,
        in_gameObjectID,
        reinterpret_cast<AkMIDIPost*>(in_pPosts),
        in_uNumPosts,
        in_bAbsoluteOffsets,
        in_uFlags,
        reinterpret_cast<AkCallbackFunc>(in_pfnCallback),
        in_pCookie,
        in_playingID);
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_StopMIDIOnEvent(WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkPlayingID in_playingID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::StopMIDIOnEvent(in_eventID, in_gameObjectID, in_playingID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PinEventInStreamCache_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkPriority in_uActivePriority, WWISEC_AkPriority in_uInactivePriority)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PinEventInStreamCache(in_eventID, in_uActivePriority, in_uInactivePriority));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PinEventInStreamCache_String(const char* in_pszEventName, WWISEC_AkPriority in_uActivePriority, WWISEC_AkPriority in_uInactivePriority)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PinEventInStreamCache(in_pszEventName, in_uActivePriority, in_uInactivePriority));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnpinEventInStreamCache_ID(WWISEC_AkUniqueID in_eventID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnpinEventInStreamCache(in_eventID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnpinEventInStreamCache_String(const char* in_pszEventName)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnpinEventInStreamCache(in_pszEventName));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetBufferStatusForPinnedEvent_ID(WWISEC_AkUniqueID in_eventID, AkReal32* out_fPercentBuffered, bool* out_bCachePinnedMemoryFull)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetBufferStatusForPinnedEvent(in_eventID, *out_fPercentBuffered, *out_bCachePinnedMemoryFull));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetBufferStatusForPinnedEvent_String(const char* in_pszEventName, AkReal32* out_fPercentBuffered, bool* out_bCachePinnedMemoryFull)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetBufferStatusForPinnedEvent(in_pszEventName, *out_fPercentBuffered, *out_bCachePinnedMemoryFull));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Time_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_iPosition, bool in_bSeekToNearestMarker, WWISEC_AkPlayingID in_PlayingID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SeekOnEvent(in_eventID, in_gameObjectID, in_iPosition, in_bSeekToNearestMarker, in_PlayingID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Time_String(const char* in_pszEventName, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_iPosition, bool in_bSeekToNearestMarker, WWISEC_AkPlayingID in_PlayingID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SeekOnEvent(in_pszEventName, in_gameObjectID, in_iPosition, in_bSeekToNearestMarker, in_PlayingID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Percent_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkGameObjectID in_gameObjectID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker, WWISEC_AkPlayingID in_PlayingID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SeekOnEvent(in_eventID, in_gameObjectID, in_fPercent, in_bSeekToNearestMarker, in_PlayingID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Percent_String(const char* in_pszEventName, WWISEC_AkGameObjectID in_gameObjectID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker, WWISEC_AkPlayingID in_PlayingID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SeekOnEvent(in_pszEventName, in_gameObjectID, in_fPercent, in_bSeekToNearestMarker, in_PlayingID));
}

void WWISEC_AK_SoundEngine_CancelEventCallbackCookie(void* in_pCookie)
{
    AK::SoundEngine::CancelEventCallbackCookie(in_pCookie);
}

void WWISEC_AK_SoundEngine_CancelEventCallbackGameObject(WWISEC_AkGameObjectID in_gameObjectID)
{
    AK::SoundEngine::CancelEventCallbackGameObject(in_gameObjectID);
}

void WWISEC_AK_SoundEngine_CancelEventCallback(WWISEC_AkPlayingID in_playingID)
{
    AK::SoundEngine::CancelEventCallback(in_playingID);
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetSourcePlayPosition(WWISEC_AkPlayingID in_PlayingID, WWISEC_AkTimeMs* out_puPosition, bool in_bExtrapolate)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetSourcePlayPosition(in_PlayingID, reinterpret_cast<AkTimeMs*>(out_puPosition), in_bExtrapolate));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetSourcePlayPositions(WWISEC_AkPlayingID in_PlayingID, WWISEC_AkSourcePosition* out_puPositions, AkUInt32* io_pcPositions, bool in_bExtrapolate)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetSourcePlayPositions(in_PlayingID, reinterpret_cast<AkSourcePosition*>(out_puPositions), io_pcPositions, in_bExtrapolate));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetSourceStreamBuffering(WWISEC_AkPlayingID in_PlayingID, WWISEC_AkTimeMs* out_buffering, bool* out_bIsBuffering)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetSourceStreamBuffering(in_PlayingID, *out_buffering, *out_bIsBuffering));
}

void WWISEC_AK_SoundEngine_StopAll(WWISEC_AkGameObjectID in_gameObjectID)
{
    AK::SoundEngine::StopAll(in_gameObjectID);
}

void WWISEC_AK_SoundEngine_StopPlayingID(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve)
{
    AK::SoundEngine::StopPlayingID(in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve));
}

void WWISEC_AK_SoundEngine_ExecuteActionOnPlayingID(WWISEC_AkActionOnEventType in_ActionType, WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve)
{
    AK::SoundEngine::ExecuteActionOnPlayingID(static_cast<AK::SoundEngine::AkActionOnEventType>(in_ActionType), in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve));
}

void WWISEC_AK_SoundEngine_SetRandomSeed(AkUInt32 in_uSeed)
{
    AK::SoundEngine::SetRandomSeed(in_uSeed);
}

void WWISEC_AK_SoundEngine_MuteBackgroundMusic(bool in_bMute)
{
    AK::SoundEngine::MuteBackgroundMusic(in_bMute);
}

bool WWISEC_AK_SoundEngine_GetBackgroundMusicMute()
{
    return AK::SoundEngine::GetBackgroundMusicMute();
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SendPluginCustomGameData(WWISEC_AkUniqueID in_busID, WWISEC_AkGameObjectID in_busObjectID, WWISEC_AkPluginType in_eType, AkUInt32 in_uCompanyID, AkUInt32 in_uPluginID, const void* in_pData, AkUInt32 in_uSizeInBytes)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SendPluginCustomGameData(in_busID, in_busObjectID, static_cast<AkPluginType>(in_eType), in_uCompanyID, in_uPluginID, in_pData, in_uSizeInBytes));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterGameObj(WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterGameObj(in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterGameObjWithName(WWISEC_AkGameObjectID in_gameObjectID, const char* in_pszObjName)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterGameObj(in_gameObjectID, in_pszObjName));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterGameObj(WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnregisterGameObj(in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterAllGameObj()
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnregisterAllGameObj());
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetPosition(WWISEC_AkGameObjectID in_GameObjectID, const WWISEC_AkSoundPosition* in_Position, WWISEC_AkSetPositionFlags in_eFlags)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetPosition(in_GameObjectID, *reinterpret_cast<const AkSoundPosition*>(in_Position), static_cast<AkSetPositionFlags>(in_eFlags)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMultiplePositions_SoundPosition(WWISEC_AkGameObjectID in_GameObjectID, const WWISEC_AkSoundPosition* in_pPositions, AkUInt16 in_NumPositions, WWISEC_AK_SoundEngine_MultiPositionType in_eMultiPositionType, WWISEC_AkSetPositionFlags in_eFlags)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetMultiplePositions(in_GameObjectID, reinterpret_cast<const AkSoundPosition*>(in_pPositions), in_NumPositions, static_cast<AK::SoundEngine::MultiPositionType>(in_eMultiPositionType), static_cast<AkSetPositionFlags>(in_eFlags)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMultiplePositions_ChannelEmitter(WWISEC_AkGameObjectID in_GameObjectID, const WWISEC_AkChannelEmitter* in_pPositions, AkUInt16 in_NumPositions, WWISEC_AK_SoundEngine_MultiPositionType in_eMultiPositionType, WWISEC_AkSetPositionFlags in_eFlags)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetMultiplePositions(in_GameObjectID, reinterpret_cast<const AkChannelEmitter*>(in_pPositions), in_NumPositions, static_cast<AK::SoundEngine::MultiPositionType>(in_eMultiPositionType), static_cast<AkSetPositionFlags>(in_eFlags)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetScalingFactor(WWISEC_AkGameObjectID in_GameObjectID, AkReal32 in_fAttenuationScalingFactor)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetScalingFactor(in_GameObjectID, in_fAttenuationScalingFactor));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetDistanceProbe(WWISEC_AkGameObjectID in_listenerGameObjectID, WWISEC_AkGameObjectID in_distanceProbeGameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetDistanceProbe(in_listenerGameObjectID, in_distanceProbeGameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_ClearBanks()
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::ClearBanks());
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBankLoadIOSettings(AkReal32 in_fThroughput, WWISEC_AkPriority in_priority)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetBankLoadIOSettings(in_fThroughput, in_priority));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBank_String(const char* in_pszString, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBank(in_pszString, *out_bankID, in_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBank_ID(WWISEC_AkBankID in_bankID, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBank(in_bankID, in_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankID* out_bankID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBankMemoryView(in_pInMemoryBankPtr, in_uInMemoryBankSize, *out_bankID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType* out_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBankMemoryView(in_pInMemoryBankPtr, in_uInMemoryBankSize, *out_bankID, *out_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankID* out_bankID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBankMemoryCopy(in_pInMemoryBankPtr, in_uInMemoryBankSize, *out_bankID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType* out_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBankMemoryCopy(in_pInMemoryBankPtr, in_uInMemoryBankSize, *out_bankID, *out_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DecodeBank(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkMemPoolId in_uPoolForDecodedBank, void** out_pDecodedBankPtr, AkUInt32* out_uDecodedBankSize)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DecodeBank(in_pInMemoryBankPtr, in_uInMemoryBankSize, in_uPoolForDecodedBank, *out_pDecodedBankPtr, *out_uDecodedBankSize));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBank_Async_String(const char* in_pszString, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBank(in_pszString, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, *out_bankID, in_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBank_Async_ID(WWISEC_AkBankID in_bankID, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBank(in_bankID, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, in_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_Async(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankID* out_bankID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBankMemoryView(in_pInMemoryBankPtr, in_uInMemoryBankSize, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, *out_bankID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_Async_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType* out_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBankMemoryView(in_pInMemoryBankPtr, in_uInMemoryBankSize, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, *out_bankID, *out_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy_Async(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankID* out_bankID, WWISEC_AkBankType* out_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::LoadBankMemoryCopy(in_pInMemoryBankPtr, in_uInMemoryBankSize, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, *out_bankID, *out_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnloadBank_String(const char* in_pszString, const void* in_pInMemoryBankPtr, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnloadBank(in_pszString, in_pInMemoryBankPtr, in_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnloadBank_ID(WWISEC_AkBankID in_bankID, const void* in_pInMemoryBankPtr, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnloadBank(in_bankID, in_pInMemoryBankPtr, in_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnloadBank_Async_String(const char* in_pszString, const void* in_pInMemoryBankPtr, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnloadBank(in_pszString, in_pInMemoryBankPtr, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, in_bankType));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnloadBank_Async_ID(WWISEC_AkBankID in_bankID, const void* in_pInMemoryBankPtr, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnloadBank(in_bankID, in_pInMemoryBankPtr, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, in_bankType));
}

void WWISEC_AK_SoundEngine_CancelBankCallbackCookie(void* in_pCookie)
{
    AK::SoundEngine::CancelBankCallbackCookie(in_pCookie);
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareBank_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char* in_pszString, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareBank(static_cast<AK::SoundEngine::PreparationType>(in_PreparationType), in_pszString, static_cast<AK::SoundEngine::AkBankContent>(in_uFlags), static_cast<AkBankType>(in_bankType)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareBank_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkBankID in_bankID, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareBank(static_cast<AK::SoundEngine::PreparationType>(in_PreparationType), static_cast<AkBankID>(in_bankID), static_cast<AK::SoundEngine::AkBankContent>(in_uFlags), static_cast<AkBankType>(in_bankType)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareBank_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char* in_pszString, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareBank(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        in_pszString,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie,
        static_cast<AK::SoundEngine::AkBankContent>(in_uFlags),
        static_cast<AkBankType>(in_bankType)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareBank_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkBankID in_bankID, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, WWISEC_AkBankType in_bankType)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareBank(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        in_bankID,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie,
        static_cast<AK::SoundEngine::AkBankContent>(in_uFlags),
        static_cast<AkBankType>(in_bankType)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_ClearPreparedEvents()
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::ClearPreparedEvents());
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uNumEvent)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareEvent(static_cast<AK::SoundEngine::PreparationType>(in_PreparationType), in_ppszString, in_uNumEvent));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkUniqueID* in_pEventID, AkUInt32 in_uNumEvent)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareEvent(static_cast<AK::SoundEngine::PreparationType>(in_PreparationType), in_pEventID, in_uNumEvent));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uNumEvent, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareEvent(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        in_ppszString,
        in_uNumEvent,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkUniqueID* in_pEventID, AkUInt32 in_uNumEvent, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareEvent(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        in_pEventID,
        in_uNumEvent,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMedia(WWISEC_AkSourceSettings* in_pSourceSettings, AkUInt32 in_uNumSourceSettings)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetMedia(reinterpret_cast<AkSourceSettings*>(in_pSourceSettings), in_uNumSourceSettings));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnsetMedia(WWISEC_AkSourceSettings* in_pSourceSettings, AkUInt32 in_uNumSourceSettings)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnsetMedia(reinterpret_cast<AkSourceSettings*>(in_pSourceSettings), in_uNumSourceSettings));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_TryUnsetMedia(WWISEC_AkSourceSettings* in_pSourceSettings, AkUInt32 in_uNumSourceSettings, WWISEC_AKRESULT* out_pUnsetResults)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::TryUnsetMedia(reinterpret_cast<AkSourceSettings*>(in_pSourceSettings), in_uNumSourceSettings, reinterpret_cast<AKRESULT*>(out_pUnsetResults)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkGroupType in_eGameSyncType, const char* in_pszGroupName, const char** in_ppszGameSyncName, AkUInt32 in_uNumGameSyncs)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareGameSyncs(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        static_cast<AkGroupType>(in_eGameSyncType),
        in_pszGroupName,
        in_ppszGameSyncName,
        in_uNumGameSyncs));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkGroupType in_eGameSyncType, AkUInt32 in_GroupID, AkUInt32* in_paGameSyncID, AkUInt32 in_uNumGameSyncs)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareGameSyncs(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        static_cast<AkGroupType>(in_eGameSyncType),
        in_GroupID,
        in_paGameSyncID,
        in_uNumGameSyncs));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkGroupType in_eGameSyncType, const char* in_pszGroupName, const char** in_ppszGameSyncName, AkUInt32 in_uNumGameSyncs, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareGameSyncs(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        static_cast<AkGroupType>(in_eGameSyncType),
        in_pszGroupName,
        in_ppszGameSyncName,
        in_uNumGameSyncs,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, WWISEC_AkGroupType in_eGameSyncType, AkUInt32 in_GroupID, AkUInt32* in_paGameSyncID, AkUInt32 in_uNumGameSyncs, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PrepareGameSyncs(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        static_cast<AkGroupType>(in_eGameSyncType),
        in_GroupID,
        in_paGameSyncID,
        in_uNumGameSyncs,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetListeners(WWISEC_AkGameObjectID in_emitterGameObj, const WWISEC_AkGameObjectID* in_pListenerGameObjs, AkUInt32 in_uNumListeners)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetListeners(in_emitterGameObj, reinterpret_cast<const AkGameObjectID*>(in_pListenerGameObjs), in_uNumListeners));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddListener(WWISEC_AkGameObjectID in_emitterGameObj, WWISEC_AkGameObjectID in_listenerGameObj)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::AddListener(in_emitterGameObj, in_listenerGameObj));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RemoveListener(WWISEC_AkGameObjectID in_emitterGameObj, WWISEC_AkGameObjectID in_listenerGameObj)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RemoveListener(in_emitterGameObj, in_listenerGameObj));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetDefaultListeners(const WWISEC_AkGameObjectID* in_pListenerObjs, AkUInt32 in_uNumListeners)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetDefaultListeners(reinterpret_cast<const AkGameObjectID*>(in_pListenerObjs), in_uNumListeners));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddDefaultListener(WWISEC_AkGameObjectID in_listenerGameObj)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::AddDefaultListener(in_listenerGameObj));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RemoveDefaultListener(WWISEC_AkGameObjectID in_listenerGameObj)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RemoveDefaultListener(in_listenerGameObj));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_ResetListenersToDefault(WWISEC_AkGameObjectID in_emitterGameObj)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::ResetListenersToDefault(in_emitterGameObj));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetListenerSpatialization(WWISEC_AkGameObjectID in_uListenerID, bool in_bSpatialized, WWISEC_AkChannelConfig in_channelConfig, WWISEC_AK_SpeakerVolumes_VectorPtr in_pVolumeOffsets)
{
    AkChannelConfig converted_channel_config;
    converted_channel_config.Deserialize(in_channelConfig);

    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetListenerSpatialization(in_uListenerID, in_bSpatialized, converted_channel_config, reinterpret_cast<AK::SpeakerVolumes::VectorPtr>(in_pVolumeOffsets)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetRTPCValue_ID(WWISEC_AkRtpcID in_rtpcID, WWISEC_AkRtpcValue in_value, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetRTPCValue(in_rtpcID, in_value, in_gameObjectID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetRTPCValue_String(const char* in_pszRtpcName, WWISEC_AkRtpcValue in_value, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetRTPCValue(in_pszRtpcName, in_value, in_gameObjectID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetRTPCValueByPlayingID_ID(WWISEC_AkRtpcID in_rtpcID, WWISEC_AkRtpcValue in_value, WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetRTPCValueByPlayingID(in_rtpcID, in_value, in_playingID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetRTPCValueByPlayingID_String(const char* in_pszRtpcName, WWISEC_AkRtpcValue in_value, WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetRTPCValueByPlayingID(in_pszRtpcName, in_value, in_playingID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValue_ID(WWISEC_AkRtpcID in_rtpcID, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::ResetRTPCValue(in_rtpcID, in_gameObjectID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValue_String(const char* in_pszRtpcName, WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkTimeMs in_uValueChangeDuration, WWISEC_AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::ResetRTPCValue(in_pszRtpcName, in_gameObjectID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetSwitch_ID(WWISEC_AkSwitchGroupID in_switchGroup, WWISEC_AkSwitchStateID in_switchState, WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetSwitch(in_switchGroup, in_switchState, in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetSwitch_String(const char* in_pszSwitchGroup, const char* in_pszSwitchState, WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetSwitch(in_pszSwitchGroup, in_pszSwitchState, in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PostTrigger_ID(WWISEC_AkTriggerID in_triggerID, WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PostTrigger(in_triggerID, in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_PostTrigger_String(const char* in_pszTrigger, WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::PostTrigger(in_pszTrigger, in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetState_ID(WWISEC_AkStateGroupID in_stateGroup, WWISEC_AkStateID in_state)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetState(in_stateGroup, in_state));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetState_String(const char* in_pszStateGroup, const char* in_pszState)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetState(in_pszStateGroup, in_pszState));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetGameObjectAuxSendValues(WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkAuxSendValue* in_aAuxSendValues, AkUInt32 in_uNumSendValues)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetGameObjectAuxSendValues(in_gameObjectID, reinterpret_cast<AkAuxSendValue*>(in_aAuxSendValues), in_uNumSendValues));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterBusVolumeCallback(WWISEC_AkUniqueID in_busID, WWISEC_AkBusCallbackFunc in_pfnCallback, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterBusVolumeCallback(in_busID, reinterpret_cast<AkBusCallbackFunc>(in_pfnCallback), in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterBusMeteringCallback(WWISEC_AkUniqueID in_busID, WWISEC_AkBusMeteringCallbackFunc in_pfnCallback, WWISEC_AkMeteringFlags in_eMeteringFlags, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterBusMeteringCallback(in_busID, reinterpret_cast<AkBusMeteringCallbackFunc>(in_pfnCallback), static_cast<AkMeteringFlags>(in_eMeteringFlags), in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterOutputDeviceMeteringCallback(WWISEC_AkOutputDeviceID in_idOutput, WWISEC_AkOutputDeviceMeteringCallbackFunc in_pfnCallback, WWISEC_AkMeteringFlags in_eMeteringFlags, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterOutputDeviceMeteringCallback(in_idOutput, reinterpret_cast<AkOutputDeviceMeteringCallbackFunc>(in_pfnCallback), static_cast<AkMeteringFlags>(in_eMeteringFlags), in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetGameObjectOutputBusVolume(WWISEC_AkGameObjectID in_emitterObjID, WWISEC_AkGameObjectID in_listenerObjID, AkReal32 in_fControlValue)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetGameObjectOutputBusVolume(in_emitterObjID, in_listenerObjID, in_fControlValue));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetActorMixerEffect(WWISEC_AkUniqueID in_audioNodeID, AkUInt32 in_uFXIndex, WWISEC_AkUniqueID in_shareSetID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetActorMixerEffect(in_audioNodeID, in_uFXIndex, in_shareSetID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusEffect_ID(WWISEC_AkUniqueID in_audioNodeID, AkUInt32 in_uFXIndex, WWISEC_AkUniqueID in_shareSetID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetBusEffect(in_audioNodeID, in_uFXIndex, in_shareSetID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusEffect_String(const char* in_pszBusName, AkUInt32 in_uFXIndex, WWISEC_AkUniqueID in_shareSetID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetBusEffect(in_pszBusName, in_uFXIndex, in_shareSetID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetOutputDeviceEffect(WWISEC_AkOutputDeviceID in_outputDeviceID, AkUInt32 in_uFXIndex, WWISEC_AkUniqueID in_FXShareSetID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetOutputDeviceEffect(in_outputDeviceID, in_uFXIndex, in_FXShareSetID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMixer_ID(WWISEC_AkUniqueID in_audioNodeID, WWISEC_AkUniqueID in_shareSetID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetMixer(in_audioNodeID, in_shareSetID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMixer_String(const char* in_pszBusName, WWISEC_AkUniqueID in_shareSetID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetMixer(in_pszBusName, in_shareSetID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusConfig_ID(WWISEC_AkUniqueID in_audioNodeID, WWISEC_AkChannelConfig in_channelConfig)
{
    AkChannelConfig converted_channel_config;
    converted_channel_config.Deserialize(in_channelConfig);

    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetBusConfig(in_audioNodeID, converted_channel_config));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusConfig_String(const char* in_pszBusName, WWISEC_AkChannelConfig in_channelConfig)
{
    AkChannelConfig converted_channel_config;
    converted_channel_config.Deserialize(in_channelConfig);

    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetBusConfig(in_pszBusName, converted_channel_config));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetObjectObstructionAndOcclusion(WWISEC_AkGameObjectID in_EmitterID, WWISEC_AkGameObjectID in_ListenerID, AkReal32 in_fObstructionLevel, AkReal32 in_fOcclusionLevel)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetObjectObstructionAndOcclusion(in_EmitterID, in_ListenerID, in_fObstructionLevel, in_fOcclusionLevel));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetMultipleObstructionAndOcclusion(WWISEC_AkGameObjectID in_EmitterID, WWISEC_AkGameObjectID in_uListenerID, WWISEC_AkObstructionOcclusionValues* in_fObstructionOcclusionValues, AkUInt32 in_uNumOcclusionObstruction)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetMultipleObstructionAndOcclusion(in_EmitterID, in_uListenerID, reinterpret_cast<AkObstructionOcclusionValues*>(in_fObstructionOcclusionValues), in_uNumOcclusionObstruction));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetContainerHistory(WWISEC_AK_IWriteBytes* in_pBytes)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetContainerHistory(reinterpret_cast<AK::IWriteBytes*>(in_pBytes)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetContainerHistory(WWISEC_AK_IReadBytes* in_pBytes)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetContainerHistory(reinterpret_cast<AK::IReadBytes*>(in_pBytes)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_StartOutputCapture(const AkOSChar* in_CaptureFileName)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::StartOutputCapture(in_CaptureFileName));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_StopOutputCapture()
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::StopOutputCapture());
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddOutputCaptureMarker(const char* in_MarkerText)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::AddOutputCaptureMarker(in_MarkerText));
}

AkUInt32 WWISEC_AK_SoundEngine_GetSampleRate()
{
    return AK::SoundEngine::GetSampleRate();
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RegisterCaptureCallback(WWISEC_AkCaptureCallbackFunc in_pfnCallback, WWISEC_AkOutputDeviceID in_idOutput, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RegisterCaptureCallback(reinterpret_cast<AkCaptureCallbackFunc>(in_pfnCallback), in_idOutput, in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_UnregisterCaptureCallback(WWISEC_AkCaptureCallbackFunc in_pfnCallback, WWISEC_AkOutputDeviceID in_idOutput, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::UnregisterCaptureCallback(reinterpret_cast<AkCaptureCallbackFunc>(in_pfnCallback), in_idOutput, in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_StartProfilerCapture(const AkOSChar* in_CaptureFileName)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::StartProfilerCapture(in_CaptureFileName));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_StopProfilerCapture()
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::StopProfilerCapture());
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetOfflineRenderingFrameTime(AkReal32 in_fFrameTimeInSeconds)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetOfflineRenderingFrameTime(in_fFrameTimeInSeconds));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetOfflineRendering(bool in_bEnableOfflineRendering)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetOfflineRendering(in_bEnableOfflineRendering));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddOutput(const WWISEC_AkOutputSettings* in_Settings, WWISEC_AkOutputDeviceID* out_pDeviceID, const WWISEC_AkGameObjectID* in_pListenerIDs, AkUInt32 in_uNumListeners)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::AddOutput(*reinterpret_cast<const AkOutputSettings*>(in_Settings), reinterpret_cast<AkOutputDeviceID*>(out_pDeviceID), reinterpret_cast<const AkGameObjectID*>(in_pListenerIDs), in_uNumListeners));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RemoveOutput(WWISEC_AkOutputDeviceID in_idOutput)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RemoveOutput(in_idOutput));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_ReplaceOutput(const WWISEC_AkOutputSettings* in_Settings, WWISEC_AkOutputDeviceID in_outputDeviceId, WWISEC_AkOutputDeviceID* out_pOutputDeviceId)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::ReplaceOutput(*reinterpret_cast<const AkOutputSettings*>(in_Settings), in_outputDeviceId, reinterpret_cast<AkOutputDeviceID*>(out_pOutputDeviceId)));
}

WWISEC_AkOutputDeviceID WWISEC_AK_SoundEngine_GetOutputID_ID(WWISEC_AkUniqueID in_idShareset, AkUInt32 in_idDevice)
{
    return static_cast<WWISEC_AkOutputDeviceID>(AK::SoundEngine::GetOutputID(in_idShareset, in_idDevice));
}

WWISEC_AkOutputDeviceID WWISEC_AK_SoundEngine_GetOutputID_String(const char* in_szShareSet, AkUInt32 in_idDevice)
{
    return static_cast<WWISEC_AkOutputDeviceID>(AK::SoundEngine::GetOutputID(in_szShareSet, in_idDevice));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusDevice_ID(WWISEC_AkUniqueID in_idBus, WWISEC_AkUniqueID in_idNewDevice)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetBusDevice(in_idBus, in_idNewDevice));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetBusDevice_String(const char* in_BusName, const char* in_DeviceName)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetBusDevice(in_BusName, in_DeviceName));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetDeviceList_Plugin(AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, AkUInt32* io_maxNumDevices, WWISEC_AkDeviceDescription* out_deviceDescriptions)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetDeviceList(in_ulCompanyID, in_ulPluginID, *io_maxNumDevices, reinterpret_cast<AkDeviceDescription*>(out_deviceDescriptions)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetDeviceList_ShareSet(WWISEC_AkUniqueID in_audioDeviceShareSetID, AkUInt32* io_maxNumDevices, WWISEC_AkDeviceDescription* out_deviceDescriptions)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetDeviceList(in_audioDeviceShareSetID, *io_maxNumDevices, reinterpret_cast<AkDeviceDescription*>(out_deviceDescriptions)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_SetOutputVolume(WWISEC_AkOutputDeviceID in_idOutput, AkReal32 in_fVolume)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::SetOutputVolume(in_idOutput, in_fVolume));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_GetDeviceSpatialAudioSupport(AkUInt32 in_idDevice)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::GetDeviceSpatialAudioSupport(in_idDevice));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_Suspend(bool in_bRenderAnyway, bool in_bFadeOut)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::Suspend(in_bRenderAnyway, in_bFadeOut));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_WakeupFromSuspend(AkUInt32 in_uDelayMs)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::WakeupFromSuspend(in_uDelayMs));
}

AkUInt32 WWISEC_AK_SoundEngine_GetBufferTick()
{
    return AK::SoundEngine::GetBufferTick();
}

AkUInt64 WWISEC_AK_SoundEngine_GetSampleTick()
{
    return AK::SoundEngine::GetSampleTick();
}
// END AkSoundEngine

// BEGIN IAkStreamMgr
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_StmStatusError);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MoveEnd);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_OpenModeReadWrite);
static_assert(sizeof(WWISEC_AkFileSystemFlags) == sizeof(AkFileSystemFlags));
static_assert(sizeof(WWISEC_AkStreamInfo) == sizeof(AkStreamInfo));
static_assert(sizeof(WWISEC_AkAutoStmHeuristics) == sizeof(AkAutoStmHeuristics));
static_assert(sizeof(WWISEC_AkAutoStmBufSettings) == sizeof(WWISEC_AkAutoStmBufSettings));
static_assert(sizeof(WWISEC_AkDeviceDesc) == sizeof(AkDeviceDesc));
static_assert(sizeof(WWISEC_AkDeviceData) == sizeof(AkDeviceData));
static_assert(sizeof(WWISEC_AkStreamRecord) == sizeof(AkStreamRecord));
static_assert(sizeof(WWISEC_AkStreamData) == sizeof(AkStreamData));

WWISEC_AK_IAkStreamMgr* WWISEC_AK_IAkStreamMgr_Get()
{
    return reinterpret_cast<WWISEC_AK_IAkStreamMgr*>(AK::IAkStreamMgr::Get());
}
// END IAkStreamMgr

// BEGIN StreamMgrModule
static_assert(sizeof(WWISEC_AkStreamMgrSettings) == sizeof(AkStreamMgrSettings));
static_assert(sizeof(WWISEC_AkDeviceSettings) == sizeof(AkDeviceSettings));
static_assert(sizeof(WWISEC_AkFileDesc) == sizeof(AkFileDesc));
static_assert(sizeof(WWISEC_AkIOTransferInfo) == sizeof(AkIOTransferInfo));
static_assert(sizeof(WWISEC_AkAsyncIOTransferInfo) == sizeof(AkAsyncIOTransferInfo));
static_assert(sizeof(WWISEC_AkIoHeuristics) == sizeof(WWISEC_AkIoHeuristics));
static_assert(sizeof(WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem) == sizeof(AK::StreamMgr::IAkIOHookDeferredBatch::BatchIoTransferItem));

class WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Wrapper : public AK::StreamMgr::IAkLowLevelIOHook
{
  public:
    WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Wrapper(void* instance, const WWISEC_AK_StreamMgr_IAkLowLevelIOHook_FunctionTable* functionTable)
        : _instance(instance), _functions(*functionTable)
    {
    }

    ~WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Wrapper()
    {
        _functions.Destructor(_instance);
    }

    AKRESULT Close(AkFileDesc& in_fileDesc) override
    {
        return static_cast<AKRESULT>(_functions.Close(_instance, reinterpret_cast<WWISEC_AkFileDesc*>(&in_fileDesc)));
    }

    AkUInt32 GetBlockSize(AkFileDesc& in_fileDesc) override
    {
        return _functions.GetBlockSize(_instance, reinterpret_cast<WWISEC_AkFileDesc*>(&in_fileDesc));
    }

    void GetDeviceDesc(AkDeviceDesc& out_deviceDesc) override
    {
        _functions.GetDeviceDesc(_instance, reinterpret_cast<WWISEC_AkDeviceDesc*>(&out_deviceDesc));
    }

    AkUInt32 GetDeviceData() override
    {
        return _functions.GetDeviceData(_instance);
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_StreamMgr_IAkLowLevelIOHook_FunctionTable _functions;
};

WWISEC_AK_StreamMgr_IAkLowLevelIOHook* WWISEC_AK_StreamMgr_IAkLowLevelIOHook_CreateInstance(void* instance, const WWISEC_AK_StreamMgr_IAkLowLevelIOHook_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_StreamMgr_IAkLowLevelIOHook*>(AkNew(AkMemID_Integration, WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Wrapper)(instance, functionTable));
}

void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_DestroyInstance(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance)
{
    WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Wrapper*>(instance);
    wrapper->~WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Wrapper();
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Close(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, WWISEC_AkFileDesc* in_fileDesc)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(instance)->Close(*reinterpret_cast<AkFileDesc*>(in_fileDesc)));
}

AkUInt32 WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetBlockSize(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, WWISEC_AkFileDesc* in_fileDesc)
{
    return reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(instance)->GetBlockSize(*reinterpret_cast<AkFileDesc*>(in_fileDesc));
}

void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetDeviceDesc(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, WWISEC_AkDeviceDesc* out_deviceDesc)
{
    reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(instance)->GetDeviceDesc(*reinterpret_cast<AkDeviceDesc*>(out_deviceDesc));
}

AkUInt32 WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetDeviceData(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance)
{
    return reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(instance)->GetDeviceData();
}

class WWISEC_AK_StreamMgr_IAkIOHookBlocking_Wrapper : public AK::StreamMgr::IAkIOHookBlocking
{
  public:
    WWISEC_AK_StreamMgr_IAkIOHookBlocking_Wrapper(void* instance, const WWISEC_AK_StreamMgr_IAkIOHookBlocking_FunctionTable* functionTable)
        : _instance(instance), _functions(*functionTable)
    {
    }

    ~WWISEC_AK_StreamMgr_IAkIOHookBlocking_Wrapper()
    {
        _functions.Destructor(_instance);
    }

    AKRESULT Close(AkFileDesc& in_fileDesc) override
    {
        return static_cast<AKRESULT>(_functions.Close(_instance, reinterpret_cast<WWISEC_AkFileDesc*>(&in_fileDesc)));
    }

    AkUInt32 GetBlockSize(AkFileDesc& in_fileDesc) override
    {
        return _functions.GetBlockSize(_instance, reinterpret_cast<WWISEC_AkFileDesc*>(&in_fileDesc));
    }

    void GetDeviceDesc(AkDeviceDesc& out_deviceDesc) override
    {
        _functions.GetDeviceDesc(_instance, reinterpret_cast<WWISEC_AkDeviceDesc*>(&out_deviceDesc));
    }

    AkUInt32 GetDeviceData() override
    {
        return _functions.GetDeviceData(_instance);
    }

    AKRESULT Read(AkFileDesc& in_fileDesc, const AkIoHeuristics& in_heuristics, void* out_pBuffer, AkIOTransferInfo& in_transferInfo) override
    {
        return static_cast<AKRESULT>(_functions.Read(
            _instance,
            reinterpret_cast<WWISEC_AkFileDesc*>(&in_fileDesc),
            reinterpret_cast<const WWISEC_AkIoHeuristics*>(&in_heuristics),
            out_pBuffer,
            reinterpret_cast<WWISEC_AkIOTransferInfo*>(&in_transferInfo)));
    }

    AKRESULT Write(AkFileDesc& in_fileDesc, const AkIoHeuristics& in_heuristics, void* in_pData, AkIOTransferInfo& io_transferInfo) override
    {
        return static_cast<AKRESULT>(_functions.Write(
            _instance,
            reinterpret_cast<WWISEC_AkFileDesc*>(&in_fileDesc),
            reinterpret_cast<const WWISEC_AkIoHeuristics*>(&in_heuristics),
            in_pData,
            reinterpret_cast<WWISEC_AkIOTransferInfo*>(&io_transferInfo)));
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_StreamMgr_IAkIOHookBlocking_FunctionTable _functions;
};

WWISEC_AK_StreamMgr_IAkIOHookBlocking* WWISEC_AK_StreamMgr_IAkIOHookBlocking_CreateInstance(void* instance, const WWISEC_AK_StreamMgr_IAkIOHookBlocking_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_StreamMgr_IAkIOHookBlocking*>(AkNew(AkMemID_Integration, WWISEC_AK_StreamMgr_IAkIOHookBlocking_Wrapper)(instance, functionTable));
}

void WWISEC_AK_StreamMgr_IAkIOHookBlocking_DestroyInstance(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance)
{
    WWISEC_AK_StreamMgr_IAkIOHookBlocking_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_StreamMgr_IAkIOHookBlocking_Wrapper*>(instance);
    wrapper->~WWISEC_AK_StreamMgr_IAkIOHookBlocking_Wrapper();
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookBlocking_Close(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance, WWISEC_AkFileDesc* in_fileDesc)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::StreamMgr::IAkIOHookBlocking*>(instance)->Close(*reinterpret_cast<AkFileDesc*>(in_fileDesc)));
}

AkUInt32 WWISEC_AK_StreamMgr_IAkIOHookBlocking_GetBlockSize(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance, WWISEC_AkFileDesc* in_fileDesc)
{
    return reinterpret_cast<AK::StreamMgr::IAkIOHookBlocking*>(instance)->GetBlockSize(*reinterpret_cast<AkFileDesc*>(in_fileDesc));
}

void WWISEC_AK_StreamMgr_IAkIOHookBlocking_GetDeviceDesc(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance, WWISEC_AkDeviceDesc* out_deviceDesc)
{
    reinterpret_cast<AK::StreamMgr::IAkIOHookBlocking*>(instance)->GetDeviceDesc(*reinterpret_cast<AkDeviceDesc*>(out_deviceDesc));
}

AkUInt32 WWISEC_AK_StreamMgr_IAkIOHookBlocking_GetDeviceData(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance)
{
    return reinterpret_cast<AK::StreamMgr::IAkIOHookBlocking*>(instance)->GetDeviceData();
}

WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookBlocking_Read(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance, WWISEC_AkFileDesc* in_fileDesc, const WWISEC_AkIoHeuristics* in_heuristics, void* out_pBuffer, WWISEC_AkIOTransferInfo* in_transferInfo)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::StreamMgr::IAkIOHookBlocking*>(instance)->Read(*reinterpret_cast<AkFileDesc*>(in_fileDesc), *reinterpret_cast<const AkIoHeuristics*>(in_heuristics), out_pBuffer, *reinterpret_cast<AkIOTransferInfo*>(in_transferInfo)));
}

WWISEC_AKRESULT WWISEC_AK_StreamMgr_IAkIOHookBlocking_Write(WWISEC_AK_StreamMgr_IAkIOHookBlocking* instance, WWISEC_AkFileDesc* in_fileDesc, const WWISEC_AkIoHeuristics* in_heuristics, void* in_pData, WWISEC_AkIOTransferInfo* io_transferInfo)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::StreamMgr::IAkIOHookBlocking*>(instance)->Write(*reinterpret_cast<AkFileDesc*>(in_fileDesc), *reinterpret_cast<const AkIoHeuristics*>(in_heuristics), in_pData, *reinterpret_cast<AkIOTransferInfo*>(io_transferInfo)));
}

void* WWISEC_AK_StreamMgr_Create(WWISEC_AkStreamMgrSettings* in_settings)
{
    return AK::StreamMgr::Create(*reinterpret_cast<AkStreamMgrSettings*>(in_settings));
}

void WWISEC_AK_StreamMgr_GetDefaultSettings(WWISEC_AkStreamMgrSettings* out_settings)
{
    AK::StreamMgr::GetDefaultSettings(*reinterpret_cast<AkStreamMgrSettings*>(out_settings));
}

void* WWISEC_AK_StreamMgr_GetFileLocationResolver()
{
    return AK::StreamMgr::GetFileLocationResolver();
}

void WWISEC_AK_StreamMgr_SetFileLocationResolver(void* in_pFileLocationResolver)
{
    AK::StreamMgr::SetFileLocationResolver(reinterpret_cast<AK::StreamMgr::IAkFileLocationResolver*>(in_pFileLocationResolver));
}

WWISEC_AkDeviceID WWISEC_AK_StreamMgr_CreateDevice(const WWISEC_AkDeviceSettings* in_settings, void* in_pLowLevelHook)
{
    return AK::StreamMgr::CreateDevice(*reinterpret_cast<const AkDeviceSettings*>(in_settings), reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(in_pLowLevelHook));
}

WWISEC_AKRESULT WWISEC_AK_StreamMgr_DestroyDevice(WWISEC_AkDeviceID in_deviceID)
{
    return static_cast<WWISEC_AKRESULT>(AK::StreamMgr::DestroyDevice(static_cast<AkDeviceID>(in_deviceID)));
}

WWISEC_AKRESULT WWISEC_AK_StreamMgr_PerformIO()
{
    return static_cast<WWISEC_AKRESULT>(AK::StreamMgr::PerformIO());
}

void WWISEC_AK_StreamMgr_GetDefaultDeviceSettings(WWISEC_AkDeviceSettings* out_settings)
{
    AK::StreamMgr::GetDefaultDeviceSettings(*reinterpret_cast<AkDeviceSettings*>(out_settings));
}

WWISEC_AKRESULT WWISEC_AK_StreamMgr_SetCurrentLanguage(const AkOSChar* in_pszLanguageName)
{
    return WWISEC_AKRESULT(AK::StreamMgr::SetCurrentLanguage(in_pszLanguageName));
}

const AkOSChar* WWISEC_AK_StreamMgr_GetCurrentLanguage()
{
    return AK::StreamMgr::GetCurrentLanguage();
}

WWISEC_AKRESULT WWISEC_AK_StreamMgr_AddLanguageChangeObserver(WWISEC_AK_StreamMgr_AkLanguageChangeHandler in_handler, void* in_pCookie)
{
    return static_cast<WWISEC_AKRESULT>(AK::StreamMgr::AddLanguageChangeObserver(reinterpret_cast<AK::StreamMgr::AkLanguageChangeHandler>(in_handler), in_pCookie));
}

void WWISEC_AK_StreamMgr_RemoveLanguageChangeObserver(void* in_pCookie)
{
    AK::StreamMgr::RemoveLanguageChangeObserver(in_pCookie);
}

void WWISEC_AK_StreamMgr_FlushAllCaches()
{
    AK::StreamMgr::FlushAllCaches();
}

// END StreamMgrModule

// BEGIN AkMusicEngine
static_assert(sizeof(WWISEC_AkMusicSettings) == sizeof(AkMusicSettings));

WWISEC_AKRESULT WWISEC_AK_MusicEngine_Init(WWISEC_AkMusicSettings* in_pSettings)
{
    return static_cast<WWISEC_AKRESULT>(AK::MusicEngine::Init(reinterpret_cast<AkMusicSettings*>(in_pSettings)));
}

void WWISEC_AK_MusicEngine_GetDefaultInitSettings(WWISEC_AkMusicSettings* out_settings)
{
    AK::MusicEngine::GetDefaultInitSettings(*reinterpret_cast<AkMusicSettings*>(out_settings));
}

void WWISEC_AK_MusicEngine_Term()
{
    AK::MusicEngine::Term();
}

WWISEC_AKRESULT WWISEC_AK_MusicEngine_GetPlayingSegmentInfo(WWISEC_AkPlayingID in_PlayingID, WWISEC_AkSegmentInfo* out_segmentInfo, bool in_bExtrapolate)
{
    return static_cast<WWISEC_AKRESULT>(AK::MusicEngine::GetPlayingSegmentInfo(in_PlayingID, *reinterpret_cast<AkSegmentInfo*>(out_segmentInfo), in_bExtrapolate));
}
// END AkMusicEngine

// BEGIN AkCommunication
#if defined(WWISEC_USE_COMMUNICATION)
#include <AK/Comm/AkCommunication.h>

static_assert(sizeof(WWISEC_AkCommSettings_Ports) == sizeof(AkCommSettings::Ports));
static_assert(sizeof(WWISEC_AkCommSettings) == sizeof(AkCommSettings));
static_assert(WWISEC_AK_COMM_SETTINGS_MAX_STRING_SIZE == AK_COMM_SETTINGS_MAX_STRING_SIZE);
static_assert(WWISEC_AK_COMM_SETTINGS_MAX_URL_SIZE == AK_COMM_SETTINGS_MAX_URL_SIZE);

WWISEC_AKRESULT WWISEC_AK_Comm_Init(const WWISEC_AkCommSettings* in_settings)
{
    return static_cast<WWISEC_AKRESULT>(AK::Comm::Init(*reinterpret_cast<const AkCommSettings*>(in_settings)));
}

void WWISEC_AK_Comm_GetDefaultInitSettings(WWISEC_AkCommSettings* out_settings)
{
    AK::Comm::GetDefaultInitSettings(*reinterpret_cast<AkCommSettings*>(out_settings));
}

void WWISEC_AK_Comm_Term()
{
    AK::Comm::Term();
}

WWISEC_AKRESULT WWISEC_AK_Comm_Reset()
{
    return static_cast<WWISEC_AKRESULT>(AK::Comm::Reset());
}

const WWISEC_AkCommSettings* WWISEC_AK_Comm_GetCurrentSettings()
{
    return reinterpret_cast<const WWISEC_AkCommSettings*>(&AK::Comm::GetCurrentSettings());
}
#endif
// END AkCommunication

// BEGIN AkDynamicDialogue
WWISEC_AkUniqueID WWISEC_AK_SoundEngine_DynamicDialogue_ResolveDialogueEvent_ID(WWISEC_AkUniqueID in_eventID, WWISEC_AkArgumentValueID* in_aArgumentValues, AkUInt32 in_uNumArguments, WWISEC_AkPlayingID in_idSequence, WWISEC_AkCandidateCallbackFunc in_candidateCallbackFunc, void* in_pCookie)
{
    return static_cast<WWISEC_AkUniqueID>(AK::SoundEngine::DynamicDialogue::ResolveDialogueEvent(in_eventID, reinterpret_cast<AkArgumentValueID*>(in_aArgumentValues), in_uNumArguments, in_idSequence, reinterpret_cast<AkCandidateCallbackFunc>(in_candidateCallbackFunc), in_pCookie));
}

WWISEC_AkUniqueID WWISEC_AK_SoundEngine_DynamicDialogue_ResolveDialogueEvent_String(const char* in_pszEventName, const char** in_aArgumentValueNames, AkUInt32 in_uNumArguments, WWISEC_AkPlayingID in_idSequence, WWISEC_AkCandidateCallbackFunc in_candidateCallbackFunc, void* in_pCookie)
{
    return static_cast<WWISEC_AkUniqueID>(AK::SoundEngine::DynamicDialogue::ResolveDialogueEvent(in_pszEventName, in_aArgumentValueNames, in_uNumArguments, in_idSequence, reinterpret_cast<AkCandidateCallbackFunc>(in_candidateCallbackFunc), in_pCookie));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicDialogue_GetDialogueEventCustomPropertyValue(WWISEC_AkUniqueID in_eventID, AkUInt32 in_uPropID, AkInt32* out_iValue)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicDialogue::GetDialogueEventCustomPropertyValue(in_eventID, in_uPropID, *out_iValue));
}
// END AkDynamicDialogue

// BEGIN AkDynamicSequence
static_assert(sizeof(WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem) == sizeof(AK::SoundEngine::DynamicSequence::PlaylistItem));

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem_SetExternalSources(WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* self, AkUInt32 in_nExternalSrc, WWISEC_AkExternalSourceInfo* in_pExternalSrc)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::SoundEngine::DynamicSequence::PlaylistItem*>(self)->SetExternalSources(in_nExternalSrc, reinterpret_cast<AkExternalSourceInfo*>(in_pExternalSrc)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Enqueue(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, WWISEC_AkUniqueID in_audioNodeID, WWISEC_AkTimeMs in_msDelay, void* in_pCustomInfo, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Enqueue(in_audioNodeID, in_msDelay, in_pCustomInfo, in_cExternals, reinterpret_cast<AkExternalSourceInfo*>(in_pExternalSources)));
}

void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Erase(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uIndex)
{
    reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Erase(in_uIndex);
}

void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_EraseSwap(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uIndex)
{
    reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->EraseSwap(in_uIndex);
}

bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_IsGrowingAllowed(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->IsGrowingAllowed();
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Reserve(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_ulReserve)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Reserve(in_ulReserve));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_ReserveExtra(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_ulReserve)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->ReserveExtra(in_ulReserve));
}

AkUInt32 WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Reserved(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Reserved();
}

void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Term(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Term();
}

AkUInt32 WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Length(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Length();
}

WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Data(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    return reinterpret_cast<WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem*>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Data());
}

bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_IsEmpty(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->IsEmpty();
}

WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Exists(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item)
{
    return reinterpret_cast<WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem*>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Exists(*reinterpret_cast<const AK::SoundEngine::DynamicSequence::PlaylistItem*>(in_Item)));
}

WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_AddLast(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    return reinterpret_cast<WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem*>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->AddLast());
}

WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_AddLastItem(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item)
{
    return reinterpret_cast<WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem*>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->AddLast(*reinterpret_cast<const AK::SoundEngine::DynamicSequence::PlaylistItem*>(in_Item)));
}

WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Last(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    return reinterpret_cast<WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem*>(&reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Last());
}

void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveLast(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->RemoveLast();
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Remove(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Remove(*reinterpret_cast<const AK::SoundEngine::DynamicSequence::PlaylistItem*>(in_Item)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveSwap(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->RemoveSwap(*reinterpret_cast<const AK::SoundEngine::DynamicSequence::PlaylistItem*>(in_Item)));
}

void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveAll(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->RemoveAll();
}

WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_At(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uiIndex)
{
    return reinterpret_cast<WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem*>(&reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->operator[](in_uiIndex));
}

WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Insert(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, unsigned int in_uIndex)
{
    return reinterpret_cast<WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem*>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Insert(in_uIndex));
}

bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_GrowArray(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->GrowArray();
}

bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_GrowArraySize(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_uGrowBy)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->GrowArray(in_uGrowBy);
}

bool WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Resize(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_uiSize)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Resize(in_uiSize);
}

void WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Transfer(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, WWISEC_AK_SoundEngine_DynamicSequence_Playlist* in_rSource)
{
    reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Transfer(*reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(in_rSource));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Copy(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_Playlist* in_rSource)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Copy(*reinterpret_cast<const AK::SoundEngine::DynamicSequence::Playlist*>(in_rSource)));
}

WWISEC_AkPlayingID WWISEC_AK_SoundEngine_DynamicSequence_Open(WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, WWISEC_AK_SoundEngine_DynamicSequence_DynamicSequenceType in_eDynamicSequenceType)
{
    return static_cast<WWISEC_AkPlayingID>(AK::SoundEngine::DynamicSequence::Open(in_gameObjectID, in_uFlags, reinterpret_cast<AkCallbackFunc>(in_pfnCallback), in_pCookie, static_cast<AK::SoundEngine::DynamicSequence::DynamicSequenceType>(in_eDynamicSequenceType)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Close(WWISEC_AkPlayingID in_playingID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::Close(in_playingID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Play(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::Play(in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Pause(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::Pause(in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Resume(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::Resume(in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Stop(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_uTransitionDuration, WWISEC_AkCurveInterpolation in_eFadeCurve)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::Stop(in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Break(WWISEC_AkPlayingID in_playingID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::Break(in_playingID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Seek_Time(WWISEC_AkPlayingID in_playingID, WWISEC_AkTimeMs in_iPosition, bool in_bSeekToNearestMarker)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::Seek(in_playingID, in_iPosition, in_bSeekToNearestMarker));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Seek_Percent(WWISEC_AkPlayingID in_playingID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::Seek(in_playingID, in_fPercent, in_bSeekToNearestMarker));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_GetPauseTimes(WWISEC_AkPlayingID in_playingID, AkUInt32* out_uTime, AkUInt32* out_uDuration)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::GetPauseTimes(in_playingID, *out_uTime, *out_uDuration));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_GetPlayingItem(WWISEC_AkPlayingID in_playingID, WWISEC_AkUniqueID* out_audioNodeID, void** out_pCustomInfo)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::GetPlayingItem(in_playingID, *out_audioNodeID, *out_pCustomInfo));
}

WWISEC_AK_SoundEngine_DynamicSequence_Playlist* WWISEC_AK_SoundEngine_DynamicSequence_LockPlaylist(WWISEC_AkPlayingID in_playingID)
{
    return reinterpret_cast<WWISEC_AK_SoundEngine_DynamicSequence_Playlist*>(AK::SoundEngine::DynamicSequence::LockPlaylist(in_playingID));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_UnlockPlaylist(WWISEC_AkPlayingID in_playingID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::DynamicSequence::UnlockPlaylist(in_playingID));
}
// END AkDynamicSequence

// BEGIN IO Hooks
#if defined(WWISEC_INCLUDE_DEFAULT_IO_HOOK_BLOCKING)
#include <AkDefaultIOHookBlocking.h>

size_t WWISEC_AK_CAkDefaultIOHookBlocking_Sizeof()
{
    return sizeof(CAkDefaultIOHookBlocking);
}

void* WWISEC_AK_CAkDefaultIOHookBlocking_Create(char* in_ioHookBuffer)
{
    ::new (in_ioHookBuffer) CAkDefaultIOHookBlocking();
    return reinterpret_cast<CAkDefaultIOHookBlocking*>(in_ioHookBuffer);
}

void WWISEC_AK_CAkDefaultIOHookBlocking_Destroy(void* in_ioHook)
{
#if defined(AK_WIN)
    reinterpret_cast<CAkDefaultIOHookBlocking*>(in_ioHook)->~CAkDefaultIOHookBlocking();
#endif
}

WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookBlocking_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkDefaultIOHookBlocking*>(in_ioHook)->Init(*reinterpret_cast<const AkDeviceSettings*>(in_deviceSettings), in_bAsyncOpen));
}

void WWISEC_AK_CAkDefaultIOHookBlocking_Term(void* in_ioHook)
{
    reinterpret_cast<CAkDefaultIOHookBlocking*>(in_ioHook)->Term();
}

WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookBlocking_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkDefaultIOHookBlocking*>(in_ioHook)->SetBasePath(in_pszBasePath));
}

WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookBlocking_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkDefaultIOHookBlocking*>(in_ioHook)->AddBasePath(in_pszBasePath));
}

void WWISEC_CAkDefaultIOHookBlocking_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering)
{
    reinterpret_cast<CAkDefaultIOHookBlocking*>(in_ioHook)->SetUseSubfoldering(bUseSubFoldering);
}
#endif

#if defined(WWISEC_INCLUDE_DEFAULT_IO_HOOK_DEFERRED)
#include <AkDefaultIOHookDeferred.h>

size_t WWISEC_AK_CAkDefaultIOHookDeferred_Sizeof()
{
    return sizeof(CAkDefaultIOHookDeferred);
}

void* WWISEC_AK_CAkDefaultIOHookDeferred_Create(char* in_ioHookBuffer)
{
    new (in_ioHookBuffer) CAkDefaultIOHookDeferred();
    return reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHookBuffer);
}

void WWISEC_AK_CAkDefaultIOHookDeferred_Destroy(void* in_ioHook)
{
#if defined(AK_WIN)
    reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->~CAkDefaultIOHookDeferred();
#endif
}

WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->Init(*reinterpret_cast<const AkDeviceSettings*>(in_deviceSettings), in_bAsyncOpen));
}

void WWISEC_AK_CAkDefaultIOHookDeferred_Term(void* in_ioHook)
{
    reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->Term();
}

WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->SetBasePath(in_pszBasePath));
}

WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->AddBasePath(in_pszBasePath));
}

void WWISEC_CAkDefaultIOHookDeferred_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering)
{
    reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->SetUseSubfoldering(bUseSubFoldering);
}
#endif

#if defined(WWISEC_INCLUDE_FILE_PACKAGE_IO_BLOCKING)
#include <AkFilePackageLowLevelIOBlocking.h>

size_t WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Sizeof()
{
    return sizeof(CAkFilePackageLowLevelIOBlocking);
}

void* WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Create(char* in_ioHookBuffer)
{
    new (in_ioHookBuffer) CAkFilePackageLowLevelIOBlocking();
    return reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHookBuffer);
}

void WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Destroy(void* in_ioHook)
{
#if defined(AK_WIN)
    reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->~CAkFilePackageLowLevelIOBlocking();
#endif
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->Init(*reinterpret_cast<const AkDeviceSettings*>(in_deviceSettings), in_bAsyncOpen));
}

void WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Term(void* in_ioHook)
{
    reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->Term();
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->SetBasePath(in_pszBasePath));
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->AddBasePath(in_pszBasePath));
}

void WWISEC_CAkFilePackageLowLevelIOBlocking_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering)
{
    reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->SetUseSubfoldering(bUseSubFoldering);
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_LoadFilePackage(void* in_ioHook, const AkOSChar* in_pszFilePackageName, AkUInt32* out_uPackageID)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->LoadFilePackage(in_pszFilePackageName, *out_uPackageID));
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_UnloadFilePackage(void* in_ioHook, AkUInt32 in_uPackageID)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->UnloadFilePackage(in_uPackageID));
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_UnloadAllFilePackages(void* in_ioHook)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->UnloadAllFilePackages());
}

void WWISEC_AK_CAkFilePackageLowLevelIOBlocking_SetPackageFallbackBehavior(void* in_ioHook, bool bFallback)
{
    reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->SetPackageFallbackBehavior(bFallback);
}
#endif

#if defined(WWISEC_INCLUDE_FILE_PACKAGE_IO_DEFERRED)
#include <AkFilePackageLowLevelIODeferred.h>

size_t WWISEC_AK_CAkFilePackageLowLevelIODeferred_Sizeof()
{
    return sizeof(CAkFilePackageLowLevelIODeferred);
}

void* WWISEC_AK_CAkFilePackageLowLevelIODeferred_Create(char* in_ioHookBuffer)
{
    ::new (in_ioHookBuffer) CAkFilePackageLowLevelIODeferred();
    return reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHookBuffer);
}

void WWISEC_AK_CAkFilePackageLowLevelIODeferred_Destroy(void* in_ioHook)
{
#if defined(AK_WIN)
    reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->~CAkFilePackageLowLevelIODeferred();
#endif
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->Init(*reinterpret_cast<const AkDeviceSettings*>(in_deviceSettings), in_bAsyncOpen));
}

void WWISEC_AK_CAkFilePackageLowLevelIODeferred_Term(void* in_ioHook)
{
    reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->Term();
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->SetBasePath(in_pszBasePath));
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->AddBasePath(in_pszBasePath));
}

void WWISEC_CAkFilePackageLowLevelIODeferred_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering)
{
    reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->SetUseSubfoldering(bUseSubFoldering);
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_LoadFilePackage(void* in_ioHook, const AkOSChar* in_pszFilePackageName, AkUInt32* out_uPackageID)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->LoadFilePackage(in_pszFilePackageName, *out_uPackageID));
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadFilePackage(void* in_ioHook, AkUInt32 in_uPackageID)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->UnloadFilePackage(in_uPackageID));
}

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadAllFilePackages(void* in_ioHook)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->UnloadAllFilePackages());
}

void WWISEC_AK_CAkFilePackageLowLevelIODeferred_SetPackageFallbackBehavior(void* in_ioHook, bool bFallback)
{
    reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->SetPackageFallbackBehavior(bFallback);
}

#endif
// END IO Hooks

// BEGIN AkJobWorkerMgr
#if defined(WWISEC_USE_DEFAULT_JOB_WORKER)
#include <AkJobWorkerMgr.h>

static_assert(sizeof(WWISEC_AK_JobWorkerMgr_InitSettings) == sizeof(AK::JobWorkerMgr::InitSettings));

void WWISEC_AK_JobWorkerMgr_InitSettings_GetJobMgrSettings(WWISEC_AK_JobWorkerMgr_InitSettings* self, WWISEC_AkJobMgrSettings* out_JobMgrSettings)
{
    *reinterpret_cast<AkJobMgrSettings*>(out_JobMgrSettings) = reinterpret_cast<AK::JobWorkerMgr::InitSettings*>(self)->GetJobMgrSettings();
}

void WWISEC_AK_JobWorkerMgr_GetDefaultInitSettings(WWISEC_AK_JobWorkerMgr_InitSettings* out_initSettings)
{
    AK::JobWorkerMgr::GetDefaultInitSettings(*reinterpret_cast<AK::JobWorkerMgr::InitSettings*>(out_initSettings));
}

bool WWISEC_AK_JobWorkerMgr_IsInitialized()
{
    return AK::JobWorkerMgr::IsInitialized();
}

WWISEC_AKRESULT WWISEC_AK_JobWorkerMgr_InitWorkers(const WWISEC_AK_JobWorkerMgr_InitSettings* in_implInitSettings)
{
    return static_cast<WWISEC_AKRESULT>(AK::JobWorkerMgr::InitWorkers(*reinterpret_cast<const AK::JobWorkerMgr::InitSettings*>(in_implInitSettings)));
}

void WWISEC_AK_JobWorkerMgr_TermWorkers()
{
    AK::JobWorkerMgr::TermWorkers();
}
#endif
// END AkJobWorkerMgr

#if defined(WWISEC_USE_SPATIAL_AUDIO)
#include <AK/SpatialAudio/Common/AkReverbEstimation.h>
#include <AK/SpatialAudio/Common/AkSpatialAudio.h>
#include <AK/SpatialAudio/Common/AkSpatialAudioTypes.h>

// BEGIN AkSpatialAudioTypes
static_assert(sizeof(WWISEC_AkSpatialAudioID) == sizeof(AkSpatialAudioID));
static_assert(sizeof(WWISEC_AkRoomID) == sizeof(AkRoomID));

const WWISEC_AkRoomID WWISEC_AK_SpatialAudio_kOutdoorRoomID{AK::SpatialAudio::kOutdoorRoomID};
// END AkSpatialAudioTypes

// BEGIN AkReflectGameData
static_assert(WWISEC_AK_MAX_NUM_TEXTURE == AK_MAX_NUM_TEXTURE);
static_assert(sizeof(WWISEC_AkImageSourceName) == sizeof(AkImageSourceName));
static_assert(sizeof(WWISEC_AkImageSourceTexture) == sizeof(AkImageSourceTexture));
static_assert(sizeof(WWISEC_AkImageSourceParams) == sizeof(AkImageSourceParams));
static_assert(sizeof(WWISEC_AkReflectImageSource) == sizeof(AkReflectImageSource));
static_assert(sizeof(WWISEC_AkReflectGameData) == sizeof(AkReflectGameData));
// END AkReflectGameData

// BEGIN AkSpatialAudio
static_assert(sizeof(WWISEC_AkSpatialAudioInitSettings) == sizeof(AkSpatialAudioInitSettings));
static_assert(sizeof(WWISEC_AkImageSourceSettings) == sizeof(AkImageSourceSettings));
static_assert(sizeof(WWISEC_AkVertex) == sizeof(AkVertex));
static_assert(sizeof(WWISEC_AkExtent) == sizeof(AkExtent));
static_assert(sizeof(WWISEC_AkTriangle) == sizeof(AkTriangle));
static_assert(sizeof(WWISEC_AkAcousticSurface) == sizeof(AkAcousticSurface));
static_assert(sizeof(WWISEC_AkReflectionPathInfo) == sizeof(WWISEC_AkReflectionPathInfo));
static_assert(sizeof(WWISEC_AkDiffractionPathInfo) == sizeof(AkDiffractionPathInfo));
static_assert(sizeof(WWISEC_AkPortalParams) == sizeof(AkPortalParams));
static_assert(sizeof(WWISEC_AkRoomParams) == sizeof(AkRoomParams));
static_assert(sizeof(WWISEC_AkGeometryParams) == sizeof(AkGeometryParams));
static_assert(WWISEC_AK_DEFAULT_GEOMETRY_POSITION_X == AK_DEFAULT_GEOMETRY_POSITION_X);
static_assert(WWISEC_AK_DEFAULT_GEOMETRY_POSITION_Y == AK_DEFAULT_GEOMETRY_POSITION_Y);
static_assert(WWISEC_AK_DEFAULT_GEOMETRY_POSITION_Z == AK_DEFAULT_GEOMETRY_POSITION_Z);
static_assert(WWISEC_AK_DEFAULT_GEOMETRY_FRONT_X == AK_DEFAULT_GEOMETRY_FRONT_X);
static_assert(WWISEC_AK_DEFAULT_GEOMETRY_FRONT_Y == AK_DEFAULT_GEOMETRY_FRONT_Y);
static_assert(WWISEC_AK_DEFAULT_GEOMETRY_FRONT_Z == AK_DEFAULT_GEOMETRY_FRONT_Z);
static_assert(WWISEC_AK_DEFAULT_GEOMETRY_TOP_X == AK_DEFAULT_GEOMETRY_TOP_X);
static_assert(WWISEC_AK_DEFAULT_GEOMETRY_TOP_Y == AK_DEFAULT_GEOMETRY_TOP_Y);
static_assert(WWISEC_AK_DEFAULT_GEOMETRY_TOP_Z == AK_DEFAULT_GEOMETRY_TOP_Z);
static_assert(sizeof(WWISEC_AkGeometryInstanceParams) == sizeof(AkGeometryInstanceParams));

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_Init(const WWISEC_AkSpatialAudioInitSettings* in_initSettings)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::Init(*reinterpret_cast<const AkSpatialAudioInitSettings*>(in_initSettings)));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RegisterListener(WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::RegisterListener(in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_UnregisterListener(WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::UnregisterListener(in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectRadius(WWISEC_AkGameObjectID in_gameObjectID, AkReal32 in_outerRadius, AkReal32 in_innerRadius)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetGameObjectRadius(in_gameObjectID, in_outerRadius, in_innerRadius));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetImageSource(WWISEC_AkImageSourceID in_srcID, const WWISEC_AkImageSourceSettings* in_info, const char* in_name, WWISEC_AkUniqueID in_AuxBusID, WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetImageSource(in_srcID, *reinterpret_cast<const AkImageSourceSettings*>(in_info), in_name, in_AuxBusID, in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RemoveImageSource(WWISEC_AkImageSourceID in_srcID, WWISEC_AkUniqueID in_AuxBusID, WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::RemoveImageSource(in_srcID, in_AuxBusID, in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_ClearImageSources(WWISEC_AkUniqueID in_AuxBusID, WWISEC_AkGameObjectID in_gameObjectID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::ClearImageSources(in_AuxBusID, in_gameObjectID));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetGeometry(WWISEC_AkGeometrySetID in_GeomSetID, const WWISEC_AkGeometryParams* in_params)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetGeometry(in_GeomSetID.id, *reinterpret_cast<const AkGeometryParams*>(in_params)));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RemoveGeometry(WWISEC_AkGeometrySetID in_SetID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::RemoveGeometry(in_SetID.id));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetGeometryInstance(WWISEC_AkGeometryInstanceID in_GeometryInstanceID, const WWISEC_AkGeometryInstanceParams* in_params)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetGeometryInstance(in_GeometryInstanceID.id, *reinterpret_cast<const AkGeometryInstanceParams*>(in_params)));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RemoveGeometryInstance(WWISEC_AkGeometryInstanceID in_GeometryInstanceID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::RemoveGeometryInstance(in_GeometryInstanceID.id));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_QueryReflectionPaths(WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_positionIndex, WWISEC_AkVector64* out_listenerPos, WWISEC_AkVector64* out_emitterPos, WWISEC_AkReflectionPathInfo* out_aPaths, AkUInt32* io_uArraySize)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::QueryReflectionPaths(in_gameObjectID, in_positionIndex, *reinterpret_cast<AkVector64*>(out_listenerPos), *reinterpret_cast<AkVector64*>(out_emitterPos), reinterpret_cast<AkReflectionPathInfo*>(out_aPaths), *io_uArraySize));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetRoom(WWISEC_AkRoomID in_RoomID, const WWISEC_AkRoomParams* in_Params, const char* in_RoomName)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetRoom(in_RoomID.id, *reinterpret_cast<const AkRoomParams*>(in_Params), in_RoomName));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RemoveRoom(WWISEC_AkRoomID in_RoomID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::RemoveRoom(in_RoomID.id));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetPortal(WWISEC_AkPortalID in_PortalID, const WWISEC_AkPortalParams* in_Params, const char* in_PortalName)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetPortal(in_PortalID.id, *reinterpret_cast<const AkPortalParams*>(in_Params), in_PortalName));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_RemovePortal(WWISEC_AkPortalID in_PortalID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::RemovePortal(in_PortalID.id));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectInRoom(WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkRoomID in_CurrentRoomID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetGameObjectInRoom(in_gameObjectID, in_CurrentRoomID.id));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetReflectionsOrder(AkUInt32 in_uReflectionsOrder, bool in_bUpdatePaths)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetReflectionsOrder(in_uReflectionsOrder, in_bUpdatePaths));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetDiffractionOrder(AkUInt32 in_uDiffractionOrder, bool in_bUpdatePaths)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetDiffractionOrder(in_uDiffractionOrder, in_bUpdatePaths));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetNumberOfPrimaryRays(AkUInt32 in_uNbPrimaryRays)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetNumberOfPrimaryRays(in_uNbPrimaryRays));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetLoadBalancingSpread(AkUInt32 in_uNbFrames)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetLoadBalancingSpread(in_uNbFrames));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetEarlyReflectionsAuxSend(WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkAuxBusID in_auxBusID)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetEarlyReflectionsAuxSend(in_gameObjectID, in_auxBusID));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetEarlyReflectionsVolume(WWISEC_AkGameObjectID in_gameObjectID, AkReal32 in_fSendVolume)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetEarlyReflectionsVolume(in_gameObjectID, in_fSendVolume));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetPortalObstructionAndOcclusion(WWISEC_AkPortalID in_PortalID, AkReal32 in_fObstruction, AkReal32 in_fOcclusion)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetPortalObstructionAndOcclusion(in_PortalID.id, in_fObstruction, in_fOcclusion));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectToPortalObstruction(WWISEC_AkGameObjectID in_gameObjectID, WWISEC_AkPortalID in_PortalID, AkReal32 in_fObstruction)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetGameObjectToPortalObstruction(in_gameObjectID, in_PortalID.id, in_fObstruction));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_SetPortalToPortalObstruction(WWISEC_AkPortalID in_PortalID0, WWISEC_AkPortalID in_PortalID1, AkReal32 in_fObstruction)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::SetPortalToPortalObstruction(in_PortalID0.id, in_PortalID1.id, in_fObstruction));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_QueryWetDiffraction(WWISEC_AkPortalID in_portal, AkReal32* out_wetDiffraction)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::QueryWetDiffraction(in_portal.id, *out_wetDiffraction));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_QueryDiffractionPaths(WWISEC_AkGameObjectID in_gameObjectID, AkUInt32 in_positionIndex, WWISEC_AkVector64* out_listenerPos, WWISEC_AkVector64* out_emitterPos, WWISEC_AkDiffractionPathInfo* out_aPaths, AkUInt32* io_uArraySize)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::QueryDiffractionPaths(in_gameObjectID, in_positionIndex, *reinterpret_cast<AkVector64*>(out_listenerPos), *reinterpret_cast<AkVector64*>(out_emitterPos), reinterpret_cast<AkDiffractionPathInfo*>(out_aPaths), *io_uArraySize));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_ResetStochasticEngine()
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::ResetStochasticEngine());
}
// END AkSpatialAudio

// BEGIN AkReverbEstimation
float WWISEC_AK_SpatialAudio_ReverbEstimation_CalculateSlope(const WWISEC_AkAcousticTexture* texture)
{
    return AK::SpatialAudio::ReverbEstimation::CalculateSlope(*reinterpret_cast<const AkAcousticTexture*>(texture));
}

void WWISEC_AK_SpatialAudio_ReverbEstimation_GetAverageAbsorptionValues(WWISEC_AkAcousticTexture* in_textures, float* in_surfaceAreas, int in_numTextures, WWISEC_AkAcousticTexture* out_average)
{
    AK::SpatialAudio::ReverbEstimation::GetAverageAbsorptionValues(reinterpret_cast<AkAcousticTexture*>(in_textures), in_surfaceAreas, in_numTextures, *reinterpret_cast<AkAcousticTexture*>(out_average));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateT60Decay(AkReal32 in_volumeCubicMeters, AkReal32 in_surfaceAreaSquaredMeters, AkReal32 in_environmentAverageAbsorption, AkReal32* out_decayEstimate)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::ReverbEstimation::EstimateT60Decay(in_volumeCubicMeters, in_surfaceAreaSquaredMeters, in_environmentAverageAbsorption, *out_decayEstimate));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateTimeToFirstReflection(WWISEC_AkVector in_environmentExtentMeters, AkReal32* out_timeToFirstReflectionMs, AkReal32 in_speedOfSound)
{
    AkVector convertedAkVector;
    convertedAkVector.X = in_environmentExtentMeters.X;
    convertedAkVector.Y = in_environmentExtentMeters.Y;
    convertedAkVector.Z = in_environmentExtentMeters.Z;

    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::ReverbEstimation::EstimateTimeToFirstReflection(convertedAkVector, *out_timeToFirstReflectionMs, in_speedOfSound));
}

WWISEC_AKRESULT WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateHFDamping(WWISEC_AkAcousticTexture* in_textures, float* in_surfaceAreas, int in_numTextures, AkReal32* out_hfDamping)
{
    return static_cast<WWISEC_AKRESULT>(AK::SpatialAudio::ReverbEstimation::EstimateHFDamping(reinterpret_cast<AkAcousticTexture*>(in_textures), in_surfaceAreas, in_numTextures, *out_hfDamping));
}
// END AkReverbEstimation
#endif