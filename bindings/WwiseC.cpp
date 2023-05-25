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
#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/AkModule.h>
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/SoundEngine/Common/AkTypes.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>

#include <new>

#define WWISEC_ASSERT_ENUM_VALUE_SAME(name) static_assert(static_cast<std::size_t>(WWISEC_##name) == static_cast<std::size_t>(name))

// BEGIN AkTypes
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_UnknownFileError);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_NUM_JOB_TYPES);
WWISEC_ASSERT_ENUM_VALUE_SAME(AkDeviceState_All);
static_assert(sizeof(WWISEC_AkAudioSettings) == sizeof(AkAudioSettings));
static_assert(sizeof(WWISEC_AkDeviceDescription) == sizeof(AkDeviceDescription));
static_assert(sizeof(WWISEC_AkExternalSourceInfo) == sizeof(AkExternalSourceInfo));
static_assert(WWISEC_AK_COMM_DEFAULT_DISCOVERY_PORT == AK_COMM_DEFAULT_DISCOVERY_PORT);
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
// END AkMidiTypes

// BEGIN AkCommonDefs
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

// BEGIN AkSoundEngine
static_assert(sizeof(WWISEC_AkOutputSettings) == sizeof(AkOutputSettings));
static_assert(sizeof(WWISEC_AkInitSettings) == sizeof(AkInitSettings));
static_assert(sizeof(WWISEC_AkPlatformInitSettings) == sizeof(AkPlatformInitSettings));

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

void* WWISEC_AK_IAkStreamMgr_Get()
{
    return AK::IAkStreamMgr::Get();
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

#if defined(WWISEC_INCLUDE_DEFAULT_IO_HOOK_BLOCKING) || defined(WWISEC_INCLUDE_DEFAULT_IO_HOOK_DEFERRED) || defined(WWISEC_INCLUDE_FILE_PACKAGE_IO_BLOCKING) || defined(WWISEC_INCLUDE_FILE_PACKAGE_IO_DEFERRED)
WWISEC_AKRESULT WWISEC_AK_CAkMultipleFileLocation_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkMultipleFileLocation*>(in_ioHook)->SetBasePath(in_pszBasePath));
}

WWISEC_AKRESULT WWISEC_AK_CAkMultipleFileLocation_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkMultipleFileLocation*>(in_ioHook)->AddBasePath(in_pszBasePath));
}

void WWISEC_CAkMultipleFileLocation_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering)
{
    reinterpret_cast<CAkMultipleFileLocation*>(in_ioHook)->SetUseSubfoldering(bUseSubFoldering);
}
#endif
// END IO Hooks
