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

#include <AK/IBytes.h>

#include <AK/MusicEngine/Common/AkMusicEngine.h>

#include <AK/SoundEngine/Common/AkCallback.h>
#include <AK/SoundEngine/Common/AkDynamicDialogue.h>
#include <AK/SoundEngine/Common/AkDynamicSequence.h>
#include <AK/SoundEngine/Common/AkErrorMessageTranslator.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/AkMemoryMgrModule.h>
#include <AK/SoundEngine/Common/AkQueryParameters.h>
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/SoundEngine/Common/AkTypes.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <Ak/SoundEngine/Common/AkVirtualAcoustics.h>
#include <Ak/SoundEngine/Common/IAkPlugin.h>

#include <AK/Tools/Common/AkMonitorError.h>

#include <new>

extern "C" void WWISEC_HACK_RegisterAllPlugins();

#define WWISEC_ASSERT_ENUM_VALUE_SAME(name) static_assert(static_cast<std::size_t>(WWISEC_##name) == static_cast<std::size_t>(name))

// BEGIN AkTypes
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
static_assert(static_cast<int32_t>(WWISEC_ConnectionType_Last) == static_cast<int32_t>(ConnectionType_Last));
// END AkTypes

// BEGIN AkSpeakerConfig
static_assert(WWISEC_AK_DEFAULT_HEIGHT_ANGLE == AK_DEFAULT_HEIGHT_ANGLE);
// END AkSpeakerConfig

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

// BEGIN AkErrorMessageTranslator
static_assert(WWISEC_AK_TRANSLATOR_MAX_NAME_SIZE == AK_TRANSLATOR_MAX_NAME_SIZE);
static_assert(WWISEC_AK_MAX_ERROR_LENGTH == AK_MAX_ERROR_LENGTH);

class WWISEC_AkErrorMessageTranslator_Wrapper : public AkErrorMessageTranslator
{
  public:
    WWISEC_AkErrorMessageTranslator_Wrapper(void* instance, const WWISEC_AkErrorMessageTranslator_FunctionTable* functions)
        : _instance(instance), _functions(*functions)
    {
    }

    ~WWISEC_AkErrorMessageTranslator_Wrapper()
    {
        _functions.Destructor(_instance);
    }

    void Term() override
    {
        _functions.Term(_instance);
    }

    bool Translate(const AkOSChar* in_pszError, AkOSChar* out_translatedPszError, AkInt32 in_maxPszErrorSize, char* in_args, AkUInt32 in_uArgSize) override
    {
        return _functions.Translate(_instance, in_pszError, out_translatedPszError, in_maxPszErrorSize, in_args, in_uArgSize);
    }

  protected:
    bool GetInfo(TagInformation* in_pTagList, AkUInt32 in_uCount, AkUInt32& out_uTranslated) override
    {
        return _functions.GetInfo(_instance, reinterpret_cast<WWISEC_AkErrorMessageTranslator_TagInformation*>(in_pTagList), in_uCount, &out_uTranslated);
    }

  private:
    void* _instance = nullptr;
    WWISEC_AkErrorMessageTranslator_FunctionTable _functions;
};

WWISEC_AkErrorMessageTranslator* WWISEC_AkErrorMessageTranslator_CreateInstance(void* instance, const WWISEC_AkErrorMessageTranslator_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AkErrorMessageTranslator*>(AkNew(AkMemID_Integration, WWISEC_AkErrorMessageTranslator_Wrapper)(instance, functionTable));
}

void WWISEC_AkErrorMessageTranslator_DestroyInstance(WWISEC_AkErrorMessageTranslator* instance)
{
    WWISEC_AkErrorMessageTranslator_Wrapper* wrapper = reinterpret_cast<WWISEC_AkErrorMessageTranslator_Wrapper*>(instance);
    wrapper->~WWISEC_AkErrorMessageTranslator_Wrapper();
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

void WWISEC_AkErrorMessageTranslator_Term(WWISEC_AkErrorMessageTranslator* instance)
{
    reinterpret_cast<AkErrorMessageTranslator*>(instance)->Term();
}

void WWISEC_AkErrorMessageTranslator_SetFallBackTranslator(WWISEC_AkErrorMessageTranslator* instance, WWISEC_AkErrorMessageTranslator* in_fallBackTranslator)
{
    reinterpret_cast<AkErrorMessageTranslator*>(instance)->SetFallBackTranslator(reinterpret_cast<AkErrorMessageTranslator*>(in_fallBackTranslator));
}

bool WWISEC_AkErrorMessageTranslator_Translate(WWISEC_AkErrorMessageTranslator* instance, const AkOSChar* in_pszError, AkOSChar* out_translatedPszError, AkInt32 in_maxPszErrorSize, char* in_args, AkUInt32 in_uArgSize)
{
    return reinterpret_cast<AkErrorMessageTranslator*>(instance)->Translate(in_pszError, out_translatedPszError, in_maxPszErrorSize, in_args, in_uArgSize);
}
// END AkErrorMessageTranslator

// BEGIN AkMonitor
static_assert(sizeof(WWISEC_AK_Monitor_MsgContext) == sizeof(AK::Monitor::MsgContext));
static_assert(static_cast<std::size_t>(WWISEC_AK_Monitor_Num_ErrorCodes) == static_cast<std::size_t>(AK::Monitor::Num_ErrorCodes));

AKRESULT WWISEC_AK_Monitor_PostCode(WWISEC_AK_Monitor_ErrorCode in_eError, WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel, AkPlayingID in_playingID, AkGameObjectID in_gameObjID, AkUniqueID in_audioNodeID, bool in_bIsBus)
{
    return AK::Monitor::PostCode(static_cast<AK::Monitor::ErrorCode>(in_eError), static_cast<AK::Monitor::ErrorLevel>(in_eErrorLevel), in_playingID, in_gameObjID, in_audioNodeID, in_bIsBus);
}

AKRESULT WWISEC_AK_Monitor_PostString(const char* in_pszError, WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel, AkPlayingID in_playingID, AkGameObjectID in_gameObjID, AkUniqueID in_audioNodeID, bool in_bIsBus)
{
    return AK::Monitor::PostString(in_pszError, static_cast<AK::Monitor::ErrorLevel>(in_eErrorLevel), in_playingID, in_gameObjID, in_audioNodeID, in_bIsBus);
}

AKRESULT WWISEC_AK_Monitor_SetLocalOutput(AkUInt32 in_uErrorLevel, WWISEC_AK_Monitor_LocalOutputFunc in_pMonitorFunc)
{
    return AK::Monitor::SetLocalOutput(in_uErrorLevel, reinterpret_cast<AK::Monitor::LocalOutputFunc>(in_pMonitorFunc));
}

AKRESULT WWISEC_AK_Monitor_AddTranslator(WWISEC_AkErrorMessageTranslator* translator, bool overridePreviousTranslators)
{
    return AK::Monitor::AddTranslator(reinterpret_cast<AkErrorMessageTranslator*>(translator), overridePreviousTranslators);
}

AKRESULT WWISEC_AK_Monitor_ResetTranslator()
{
    return AK::Monitor::ResetTranslator();
}

AkTimeMs WWISEC_AK_Monitor_GetTimeStamp()
{
    return AK::Monitor::GetTimeStamp();
}

void WWISEC_AK_Monitor_MonitorStreamMgrInit(const WWISEC_AkStreamMgrSettings* in_streamMgrSettings)
{
    AK::Monitor::MonitorStreamMgrInit(*reinterpret_cast<const AkStreamMgrSettings*>(in_streamMgrSettings));
}

void WWISEC_AK_Monitor_MonitorStreamingDeviceInit(AkDeviceID in_deviceID, const WWISEC_AkDeviceSettings* in_deviceSettings)
{
    AK::Monitor::MonitorStreamingDeviceInit(in_deviceID, *reinterpret_cast<const AkDeviceSettings*>(in_deviceSettings));
}

void WWISEC_AK_Monitor_MonitorStreamingDeviceDestroyed(AkDeviceID in_deviceID)
{
    AK::Monitor::MonitorStreamingDeviceDestroyed(in_deviceID);
}

void WWISEC_AK_Monitor_MonitorStreamMgrTerm()
{
    AK::Monitor::MonitorStreamMgrTerm();
}
// END AkMonitor

// BEGIN IBytes
class WWISEC_AK_IReadBytes_Wrapper : public AK::IReadBytes
{
  public:
    WWISEC_AK_IReadBytes_Wrapper(void* instance, const WWISEC_AK_IReadBytes_FunctionTable* functions)
        : _instance(instance), _functions(*functions)
    {
    }

    bool ReadBytes(
        void* in_pData,
        AkInt32 in_cBytes,
        AkInt32& out_cRead) override
    {
        return _functions.ReadBytes(_instance, in_pData, in_cBytes, &out_cRead);
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_IReadBytes_FunctionTable _functions;
};

WWISEC_AK_IReadBytes* WWISEC_AK_IReadBytes_CreateInstance(void* instance, const WWISEC_AK_IReadBytes_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_IReadBytes*>(AkNew(AkMemID_Integration, WWISEC_AK_IReadBytes_Wrapper)(instance, functionTable));
}

void WWISEC_AK_IReadBytes_DestroyInstance(WWISEC_AK_IReadBytes* instance)
{
    WWISEC_AK_IReadBytes_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_IReadBytes_Wrapper*>(instance);
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

bool WWISEC_AK_IReadBytes_ReadBytes(WWISEC_AK_IReadBytes* instance, void* in_pData, AkInt32 in_cBytes, AkInt32* out_cRead)
{
    return reinterpret_cast<AK::IReadBytes*>(instance)->ReadBytes(in_pData, in_cBytes, *out_cRead);
}

class WWISEC_AK_IWriteBytes_Wrapper : public AK::IWriteBytes
{
  public:
    WWISEC_AK_IWriteBytes_Wrapper(void* instance, const WWISEC_AK_IWriteBytes_FunctionTable* functions)
        : _instance(instance), _functions(*functions)
    {
    }

    bool WriteBytes(
        const void* in_pData,
        AkInt32 in_cBytes,
        AkInt32& out_cWritten) override
    {
        return _functions.WriteBytes(_instance, in_pData, in_cBytes, &out_cWritten);
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_IWriteBytes_FunctionTable _functions;
};

WWISEC_AK_IWriteBytes* WWISEC_AK_IWriteBytes_CreateInstance(void* instance, const WWISEC_AK_IWriteBytes_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_IWriteBytes*>(AkNew(AkMemID_Integration, WWISEC_AK_IWriteBytes_Wrapper)(instance, functionTable));
}

void WWISEC_AK_IWriteBytes_DestroyInstance(WWISEC_AK_IWriteBytes* instance)
{
    WWISEC_AK_IWriteBytes_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_IWriteBytes_Wrapper*>(instance);
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

bool WWISE_AK_IWriteBytes_WriteBytes(WWISEC_AK_IWriteBytes* instance, const void* in_pData, AkInt32 in_cBytes, AkInt32* out_cWritten)
{
    return reinterpret_cast<AK::IWriteBytes*>(instance)->WriteBytes(in_pData, in_cBytes, *out_cWritten);
}
// END IBytes

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
static_assert(static_cast<std::size_t>(WWISEC_AK_TempAlloc_Type_NUM) == static_cast<std::size_t>(AK::TempAlloc::Type_NUM));
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

void* WWISEC_AK_MemoryMgr_Malloc(AkMemPoolId in_poolId, size_t in_uSize)
{
    return AK::MemoryMgr::Malloc(static_cast<AkMemPoolId>(in_poolId), in_uSize);
}

void* WWISEC_AK_MemoryMgr_ReallocAligned(AkMemPoolId in_poolId, void* in_pAlloc, size_t in_uSize, AkUInt32 in_uAlignment)
{
    return AK::MemoryMgr::ReallocAligned(static_cast<AkMemPoolId>(in_poolId), in_pAlloc, in_uSize, in_uAlignment);
}

void WWISEC_AK_MemoryMgr_Free(AkMemPoolId in_poolId, void* in_pMemAddress)
{
    AK::MemoryMgr::Free(in_poolId, in_pMemAddress);
}

void* WWISEC_AK_MemoryMgr_Malign(AkMemPoolId in_poolId, size_t in_USize, AkUInt32 in_uAlignment)
{
    return AK::MemoryMgr::Malign(in_poolId, in_USize, in_uAlignment);
}

void WWISEC_AK_MemoryMgr_GetCategoryStats(AkMemPoolId in_poolId, WWISEC_AK_MemoryMgr_CategoryStats* out_poolStats)
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

// BEGIN AkTempAllocDefs
static_assert(sizeof(WWISEC_AK_TempAlloc_Stats) == sizeof(AK::TempAlloc::Stats));
static_assert(sizeof(WWISEC_AK_TempAlloc_InitSettings) == sizeof(AK::TempAlloc::InitSettings));
static_assert(sizeof(WWISEC_AK_BookmarkAlloc_Stats) == sizeof(AK::BookmarkAlloc::Stats));
static_assert(sizeof(WWISEC_AK_BookmarkAlloc_InitSettings) == sizeof(AK::BookmarkAlloc::InitSettings));

void WWISEC_AK_TempAlloc_GetStats(WWISEC_AK_TempAlloc_Type in_eType, WWISEC_AK_TempAlloc_Stats* out_stats)
{
    AK::TempAlloc::GetStats(static_cast<AK::TempAlloc::Type>(in_eType), *reinterpret_cast<AK::TempAlloc::Stats*>(out_stats));
}

void WWISEC_AK_TempAlloc_DumpTempAllocsToFile(WWISEC_AK_TempAlloc_Type in_eType, const AkOSChar* pszFilename)
{
    AK::TempAlloc::DumpTempAllocsToFile(static_cast<AK::TempAlloc::Type>(in_eType), pszFilename);
}

void WWISEC_AK_BookmarkAlloc_GetStats(WWISEC_AK_BookmarkAlloc_Stats* out_stats)
{
    AK::BookmarkAlloc::GetStats(*reinterpret_cast<AK::BookmarkAlloc::Stats*>(out_stats));
}
// END AkTempAllocDefs

// BEGIN AkMemoryArenaTypes
static_assert(sizeof(WWISEC_AK_MemoryArea_AkMemoryArenaSettings) == sizeof(AK::MemoryArena::AkMemoryArenaSettings));
// END AkMemoryArenaTypes

// BEGIN AkMemoryMgrModule
static_assert(static_cast<int32_t>(WWISEC_AkMemoryMgrArena_NUM) == static_cast<int32_t>(AkMemoryMgrArena_NUM));
static_assert(sizeof(WWISEC_AkMemSettings) == sizeof(AkMemSettings));

AKRESULT WWISEC_AK_MemoryMgr_Init(WWISEC_AkMemSettings* in_pSettings)
{
    return AK::MemoryMgr::Init(reinterpret_cast<AkMemSettings*>(in_pSettings));
}

void WWISEC_AK_MemoryMgr_GetDefaultSettings(WWISEC_AkMemSettings* out_pMemSettings)
{
    AK::MemoryMgr::GetDefaultSettings(*reinterpret_cast<AkMemSettings*>(out_pMemSettings));
}

void WWISEC_AK_MemoryMgr_VerifyMemoryArenaIntegrity(WWISEC_AkMemoryMgrArena in_eArena)
{
    AK::MemoryMgr::VerifyMemoryArenaIntegrity(static_cast<AkMemoryMgrArena>(in_eArena));
}

WWISEC_AK_MemoryArea_AkMemoryArea* WWISEC_AK_MemoryMgr_GetMemoryArena(WWISEC_AkMemoryMgrArena in_eArena)
{
    return reinterpret_cast<WWISEC_AK_MemoryArea_AkMemoryArea*>(AK::MemoryMgr::GetMemoryArena(static_cast<AkMemoryMgrArena>(in_eArena)));
}
// END AkMemoryMgrModule

// BEGIN IAkPlugin
static_assert(static_cast<std::size_t>(WWISEC_AK_PluginServiceType_MAX) == static_cast<std::size_t>(AK::PluginServiceType_MAX));

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

AKRESULT WWISEC_AK_IAkGlobalPluginContext_PostMonitorMessage(WWISEC_AK_IAkGlobalPluginContext* self, const char* in_pszError, WWISEC_AK_Monitor_ErrorLevel in_eErrorLevel)
{
    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->PostMonitorMessage(in_pszError, static_cast<AK::Monitor::ErrorLevel>(in_eErrorLevel));
}

AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterPlugin(WWISEC_AK_IAkGlobalPluginContext* self, enum AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreatePluginCallback in_pCreateFunc, WWISEC_AkCreateParamCallback in_pCreateParamFunc)
{
    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->RegisterPlugin(
        static_cast<AkPluginType>(in_eType),
        in_ulCompanyID,
        in_ulPluginID,
        reinterpret_cast<AkCreatePluginCallback>(in_pCreateFunc),
        reinterpret_cast<AkCreateParamCallback>(in_pCreateParamFunc));
}

AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterCodec(WWISEC_AK_IAkGlobalPluginContext* self, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreateFileSourceCallback in_pFileCreateFunc, WWISEC_AkCreateBankSourceCallback in_pBankCreateFunc)
{
    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->RegisterCodec(in_ulCompanyID, in_ulPluginID, reinterpret_cast<AkCreateFileSourceCallback>(in_pFileCreateFunc), reinterpret_cast<AkCreateBankSourceCallback>(in_pBankCreateFunc));
}

AKRESULT WWISEC_AK_IAkGlobalPluginContext_RegisterGlobalCallback(WWISEC_AK_IAkGlobalPluginContext* self, enum AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation, void* in_pCookie)
{
    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->RegisterGlobalCallback(static_cast<AkPluginType>(in_eType), in_ulCompanyID, in_ulPluginID, reinterpret_cast<AkGlobalCallbackFunc>(in_pCallback), in_eLocation, in_pCookie);
}

AKRESULT WWISEC_AK_IAkGlobalPluginContext_UnregisterGlobalCallback(WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation)
{
    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->UnregisterGlobalCallback(reinterpret_cast<AkGlobalCallbackFunc>(in_pCallback), in_eLocation);
}

WWISEC_AK_IAkPluginMemAlloc* WWISEC_AK_IAkGlobalPluginContext_GetAllocator(WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<WWISEC_AK_IAkPluginMemAlloc*>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->GetAllocator());
}

AKRESULT WWISEC_AK_IAkGlobalPluginContext_SetRTPCValue(WWISEC_AK_IAkGlobalPluginContext* self, AkRtpcID in_rtpcID, AkRtpcValue in_value, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->SetRTPCValue(in_rtpcID, in_value, in_gameObjectID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation);
}

AKRESULT WWISEC_AK_IAkGlobalPluginContext_SendPluginCustomGameData(WWISEC_AK_IAkGlobalPluginContext* self, AkUniqueID in_busID, AkGameObjectID in_busObjectID, enum AkPluginType in_eType, AkUInt32 in_uCompanyID, AkUInt32 in_uPluginID, const void* in_pData, AkUInt32 in_uSizeInBytes)
{
    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->SendPluginCustomGameData(in_busID, in_busObjectID, static_cast<AkPluginType>(in_eType), in_uCompanyID, in_uPluginID, in_pData, in_uSizeInBytes);
}

void WWISEC_AK_IAkGlobalPluginContext_ComputeAmbisonicsEncoding(WWISEC_AK_IAkGlobalPluginContext* self, AkReal32 in_fAzimuth, AkReal32 in_fElevation, WWISEC_AkChannelConfig in_cfgAmbisonics, WWISEC_AK_SpeakerVolumes_VectorPtr out_vVolumes)
{
    AkChannelConfig channelConfig;
    channelConfig.Deserialize(in_cfgAmbisonics);

    reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->ComputeAmbisonicsEncoding(in_fAzimuth, in_fElevation, channelConfig, out_vVolumes);
}

AKRESULT WWISEC_AK_IAkGlobalPluginContext_ComputeWeightedAmbisonicsDecodingFromSampledSphere(WWISEC_AK_IAkGlobalPluginContext* self, const WWISEC_AkVector* in_samples, AkUInt32 in_uNumSamples, WWISEC_AkChannelConfig in_cfgAmbisonics, WWISEC_AK_SpeakerVolumes_MatrixPtr out_mxVolume)
{
    AkChannelConfig channelConfig;
    channelConfig.Deserialize(in_cfgAmbisonics);

    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->ComputeWeightedAmbisonicsDecodingFromSampledSphere(reinterpret_cast<const AkVector*>(in_samples), in_uNumSamples, channelConfig, out_mxVolume);
}

const WWISEC_AkAcousticTexture* WWISEC_AK_IAkGlobalPluginContext_GetAcousticTexture(WWISEC_AK_IAkGlobalPluginContext* self, AkAcousticTextureID in_AcousticTextureID)
{
    return reinterpret_cast<const WWISEC_AkAcousticTexture*>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->GetAcousticTexture(in_AcousticTextureID));
}

AKRESULT WWISEC_AK_IAkGlobalPluginContext_ComputeSphericalCoordinates(const WWISEC_AK_IAkGlobalPluginContext* self, const WWISEC_AkEmitterListenerPair* in_pair, AkReal32* out_fAzimuth, AkReal32* out_fElevation)
{
    return reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->ComputeSphericalCoordinates(*reinterpret_cast<const AkEmitterListenerPair*>(in_pair), *out_fAzimuth, *out_fElevation);
}

const WWISEC_AkPlatformInitSettings* WWISEC_AK_IAkGlobalPluginContext_GetPlatformInitSettings(const WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<const WWISEC_AkPlatformInitSettings*>(reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetPlatformInitSettings());
}

const WWISEC_AkInitSettings* WWISEC_AK_IAkGlobalPluginContext_GetInitSettings(const WWISEC_AK_IAkGlobalPluginContext* self)
{
    return reinterpret_cast<const WWISEC_AkInitSettings*>(reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetInitSettings());
}

AKRESULT WWISEC_AK_IAkGlobalPluginContext_GetAudioSettings(const WWISEC_AK_IAkGlobalPluginContext* self, WWISEC_AkAudioSettings* out_audioSettings)
{
    return reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetAudioSettings(*reinterpret_cast<AkAudioSettings*>(out_audioSettings));
}

AkUInt32 WWISEC_AK_IAkGlobalPluginContext_GetIDFromString(const WWISEC_AK_IAkGlobalPluginContext* self, const char* in_pszString)
{
    return reinterpret_cast<const AK::IAkGlobalPluginContext*>(self)->GetIDFromString(in_pszString);
}

AkPlayingID WWISEC_AK_IAkGlobalPluginContext_PostEventSync(WWISEC_AK_IAkGlobalPluginContext* self, AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources, AkPlayingID in_PlayingID)
{
    return static_cast<AkPlayingID>(reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->PostEventSync(in_eventID, in_gameObjectID, in_uFlags, reinterpret_cast<AkCallbackFunc>(in_pfnCallback), in_pCookie, in_cExternals, reinterpret_cast<AkExternalSourceInfo*>(in_pExternalSources), in_PlayingID));
}

AkPlayingID WWISEC_AK_IAkGlobalPluginContext_PostMIDIOnEventSync(WWISEC_AK_IAkGlobalPluginContext* self, AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, WWISEC_AkMIDIPost* in_pPosts, AkUInt16 in_uNumPosts, bool in_bAbsoluteOffsets, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkPlayingID in_playingID)
{
    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->PostMIDIOnEventSync(in_eventID, in_gameObjectID, reinterpret_cast<AkMIDIPost*>(in_pPosts), in_uNumPosts, in_bAbsoluteOffsets, in_uFlags, reinterpret_cast<AkCallbackFunc>(in_pfnCallback), in_pCookie, in_playingID);
}

AKRESULT WWISEC_AK_IAkGlobalPluginContext_StopMIDIOnEventSync(WWISEC_AK_IAkGlobalPluginContext* self, AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkPlayingID in_playingID)
{
    return reinterpret_cast<AK::IAkGlobalPluginContext*>(self)->StopMIDIOnEventSync(in_eventID, in_gameObjectID, in_playingID);
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
static_assert(static_cast<int32_t>(WWISEC_AK_SoundEngine_Preparation_Last) == static_cast<int32_t>(AK::SoundEngine::Preparation_Last));
static_assert(static_cast<int32_t>(WWISEC_AK_SoundEngine_AkBankContent_Last) == static_cast<int32_t>(AK::SoundEngine::AkBankContent_Last));

void WWISEC_AkOutputSettings_Init(WWISEC_AkOutputSettings* outputSettings, const char* in_szDeviceShareSet, AkUniqueID in_idDevice, WWISEC_AkChannelConfig in_channelConfig, enum AkPanningRule in_ePanning)
{
    ::new (outputSettings) AkOutputSettings(in_szDeviceShareSet, static_cast<AkUniqueID>(in_idDevice), *reinterpret_cast<AkChannelConfig*>(&in_channelConfig), static_cast<AkPanningRule>(in_ePanning));
}

bool WWISEC_AK_SoundEngine_IsInitialized()
{
    return AK::SoundEngine::IsInitialized();
}

AKRESULT WWISEC_AK_SoundEngine_Init(WWISEC_AkInitSettings* in_pSettings, WWISEC_AkPlatformInitSettings* in_pPlatformSettings)
{
    WWISEC_HACK_RegisterAllPlugins();

    return AK::SoundEngine::Init(reinterpret_cast<AkInitSettings*>(in_pSettings), reinterpret_cast<AkPlatformInitSettings*>(in_pPlatformSettings));
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

AKRESULT WWISEC_AK_SoundEngine_GetAudioSettings(WWISEC_AkAudioSettings* out_audioSettings)
{
    return AK::SoundEngine::GetAudioSettings(*reinterpret_cast<AkAudioSettings*>(out_audioSettings));
}

WWISEC_AkChannelConfig WWISEC_AK_SoundEngine_GetSpeakerConfiguration(AkOutputDeviceID in_idOutput)
{
    return static_cast<WWISEC_AkChannelConfig>(AK::SoundEngine::GetSpeakerConfiguration(in_idOutput).Serialize());
}

AKRESULT WWISEC_AK_SoundEngine_GetOutputDeviceConfiguration(AkOutputDeviceID in_idOutput, WWISEC_AkChannelConfig* io_channelConfig, WWISEC_Ak3DAudioSinkCapabilities* io_capabilities)
{
    return AK::SoundEngine::GetOutputDeviceConfiguration(in_idOutput, *reinterpret_cast<AkChannelConfig*>(io_channelConfig), *reinterpret_cast<Ak3DAudioSinkCapabilities*>(io_capabilities));
}

AKRESULT WWISEC_AK_SoundEngine_GetPanningRule(enum AkPanningRule* out_ePanningRule, AkOutputDeviceID in_idOutput)
{
    return AK::SoundEngine::GetPanningRule(*reinterpret_cast<AkPanningRule*>(out_ePanningRule), in_idOutput);
}

AKRESULT WWISEC_AK_SoundEngine_SetPanningRule(enum AkPanningRule in_ePanningRule, AkOutputDeviceID in_idOutput)
{
    return AK::SoundEngine::SetPanningRule(static_cast<AkPanningRule>(in_ePanningRule), in_idOutput);
}

AKRESULT WWISEC_AK_SoundEngine_GetSpeakerAngles(AkReal32* io_pfSpeakerAngles, AkUInt32* io_uNumAngles, AkReal32* out_fHeightAngle, AkOutputDeviceID in_idOutput)
{
    return AK::SoundEngine::GetSpeakerAngles(io_pfSpeakerAngles, *io_uNumAngles, *out_fHeightAngle, in_idOutput);
}

AKRESULT WWISEC_AK_SoundEngine_SetSpeakerAngles(const AkReal32* in_pfSpeakerAngles, AkUInt32 in_uNumAngles, AkReal32 in_fHeightAngle, AkOutputDeviceID in_idOutput)
{
    return AK::SoundEngine::SetSpeakerAngles(in_pfSpeakerAngles, in_uNumAngles, in_fHeightAngle, in_idOutput);
}

AKRESULT WWISEC_AK_SoundEngine_SetVolumeThreshold(AkReal32 in_fVolumeThresholdDB)
{
    return AK::SoundEngine::SetVolumeThreshold(in_fVolumeThresholdDB);
}

AKRESULT WWISEC_AK_SoundEngine_SetMaxNumVoicesLimit(AkUInt16 in_maxNumberVoices)
{
    return AK::SoundEngine::SetMaxNumVoicesLimit(in_maxNumberVoices);
}

AKRESULT WWISEC_AK_SoundEngine_SetJobMgrMaxActiveWorkers(AkJobType in_jobType, AkUInt32 in_uNewMaxActiveWorkers)
{
    return AK::SoundEngine::SetJobMgrMaxActiveWorkers(in_jobType, in_uNewMaxActiveWorkers);
}

AKRESULT WWISEC_AK_SoundEngine_RenderAudio(bool in_bAllowSyncRender)
{
    return AK::SoundEngine::RenderAudio(in_bAllowSyncRender);
}

WWISEC_AK_IAkGlobalPluginContext* WWISEC_AK_SoundEngine_GetGlobalPluginContext()
{
    return reinterpret_cast<WWISEC_AK_IAkGlobalPluginContext*>(AK::SoundEngine::GetGlobalPluginContext());
}

AKRESULT WWISEC_AK_SoundEngine_RegisterPlugin(enum AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, WWISEC_AkCreatePluginCallback in_pCreateFunc, WWISEC_AkCreateParamCallback in_pCreateParamFunc)
{
    return AK::SoundEngine::RegisterPlugin(static_cast<AkPluginType>(in_eType), in_ulCompanyID, in_ulPluginID, reinterpret_cast<AkCreatePluginCallback>(in_pCreateFunc), reinterpret_cast<AkCreateParamCallback>(in_pCreateParamFunc));
}

AKRESULT WWISEC_AK_SoundEngine_RegisterPluginDLL(const AkOSChar* in_DllName, const AkOSChar* in_DllPath)
{
    return AK::SoundEngine::RegisterPluginDLL(in_DllName, in_DllPath);
}

bool WWISEC_AK_SoundEngine_IsPluginRegistered(enum AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID)
{
    return AK::SoundEngine::IsPluginRegistered(static_cast<AkPluginType>(in_eType), in_ulCompanyID, in_ulPluginID);
}

AKRESULT WWISEC_AK_SoundEngine_RegisterGlobalCallback(WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation, void* in_pCookie, enum AkPluginType in_eType, AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID)
{
    return AK::SoundEngine::RegisterGlobalCallback(reinterpret_cast<AkGlobalCallbackFunc>(in_pCallback), in_eLocation, in_pCookie, static_cast<AkPluginType>(in_eType), in_ulCompanyID, in_ulPluginID);
}

AKRESULT WWISEC_AK_SoundEngine_UnregisterGlobalCallback(WWISEC_AkGlobalCallbackFunc in_pCallback, AkUInt32 in_eLocation)
{
    return AK::SoundEngine::UnregisterGlobalCallback(reinterpret_cast<AkGlobalCallbackFunc>(in_pCallback), in_eLocation);
}

AKRESULT WWISEC_AK_SoundEngine_RegisterResourceMonitorCallback(WWISEC_AkResourceMonitorCallbackFunc in_pCallback)
{
    return AK::SoundEngine::RegisterResourceMonitorCallback(reinterpret_cast<AkResourceMonitorCallbackFunc>(in_pCallback));
}

AKRESULT WWISEC_AK_SoundEngine_UnregisterResourceMonitorCallback(WWISEC_AkResourceMonitorCallbackFunc in_pCallback)
{
    return AK::SoundEngine::UnregisterResourceMonitorCallback(reinterpret_cast<AkResourceMonitorCallbackFunc>(in_pCallback));
}

AKRESULT WWISEC_AK_SoundEngine_RegisterAudioDeviceStatusCallback(WWISEC_AK_AkDeviceStatusCallbackFunc in_pCallback)
{
    return AK::SoundEngine::RegisterAudioDeviceStatusCallback(reinterpret_cast<AK::AkDeviceStatusCallbackFunc>(in_pCallback));
}

AKRESULT WWISEC_AK_SoundEngine_UnregisterAudioDeviceStatusCallback()
{
    return AK::SoundEngine::UnregisterAudioDeviceStatusCallback();
}

AkUInt32 WWISEC_AK_SoundEngine_GetIDFromString(const char* in_pszString)
{
    return AK::SoundEngine::GetIDFromString(in_pszString);
}

AkPlayingID WWISEC_AK_SoundEngine_PostEvent_ID(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources, AkPlayingID in_PlayingID)
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

AkPlayingID WWISEC_AK_SoundEngine_PostEvent_String(const char* in_pszEventName, AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources, AkPlayingID in_PlayingID)
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

AKRESULT WWISEC_AK_SoundEngine_ExecuteActionOnEvent_ID(AkUniqueID in_eventID, enum AkActionOnEventType in_ActionType, AkGameObjectID in_gameObjectID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve, AkPlayingID in_PlayingID)
{
    return static_cast<AKRESULT>(AK::SoundEngine::ExecuteActionOnEvent(
        in_eventID,
        static_cast<AK::SoundEngine::AkActionOnEventType>(in_ActionType),
        in_gameObjectID,
        in_uTransitionDuration,
        static_cast<AkCurveInterpolation>(in_eFadeCurve),
        in_PlayingID));
}

AKRESULT WWISEC_AK_SoundEngine_ExecuteActionOnEvent_String(const char* in_pszEventName, enum AkActionOnEventType in_ActionType, AkGameObjectID in_gameObjectID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve, AkPlayingID in_PlayingID)
{
    return static_cast<AKRESULT>(AK::SoundEngine::ExecuteActionOnEvent(
        in_pszEventName,
        static_cast<AK::SoundEngine::AkActionOnEventType>(in_ActionType),
        in_gameObjectID,
        in_uTransitionDuration,
        static_cast<AkCurveInterpolation>(in_eFadeCurve),
        in_PlayingID));
}

AkPlayingID WWISEC_AK_SoundEngine_PostMIDIOnEvent(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, WWISEC_AkMIDIPost* in_pPosts, AkUInt16 in_uNumPosts, bool in_bAbsoluteOffsets, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, AkPlayingID in_playingID)
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

AKRESULT WWISEC_AK_SoundEngine_StopMIDIOnEvent(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkPlayingID in_playingID)
{
    return AK::SoundEngine::StopMIDIOnEvent(in_eventID, in_gameObjectID, in_playingID);
}

AKRESULT WWISEC_AK_SoundEngine_PinEventInStreamCache_ID(AkUniqueID in_eventID, AkPriority in_uActivePriority, AkPriority in_uInactivePriority)
{
    return AK::SoundEngine::PinEventInStreamCache(in_eventID, in_uActivePriority, in_uInactivePriority);
}

AKRESULT WWISEC_AK_SoundEngine_PinEventInStreamCache_String(const char* in_pszEventName, AkPriority in_uActivePriority, AkPriority in_uInactivePriority)
{
    return AK::SoundEngine::PinEventInStreamCache(in_pszEventName, in_uActivePriority, in_uInactivePriority);
}

AKRESULT WWISEC_AK_SoundEngine_UnpinEventInStreamCache_ID(AkUniqueID in_eventID)
{
    return AK::SoundEngine::UnpinEventInStreamCache(in_eventID);
}

AKRESULT WWISEC_AK_SoundEngine_UnpinEventInStreamCache_String(const char* in_pszEventName)
{
    return AK::SoundEngine::UnpinEventInStreamCache(in_pszEventName);
}

AKRESULT WWISEC_AK_SoundEngine_GetBufferStatusForPinnedEvent_ID(AkUniqueID in_eventID, AkReal32* out_fPercentBuffered, bool* out_bCachePinnedMemoryFull)
{
    return AK::SoundEngine::GetBufferStatusForPinnedEvent(in_eventID, *out_fPercentBuffered, *out_bCachePinnedMemoryFull);
}

AKRESULT WWISEC_AK_SoundEngine_GetBufferStatusForPinnedEvent_String(const char* in_pszEventName, AkReal32* out_fPercentBuffered, bool* out_bCachePinnedMemoryFull)
{
    return AK::SoundEngine::GetBufferStatusForPinnedEvent(in_pszEventName, *out_fPercentBuffered, *out_bCachePinnedMemoryFull);
}

AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Time_ID(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkTimeMs in_iPosition, bool in_bSeekToNearestMarker, AkPlayingID in_PlayingID)
{
    return AK::SoundEngine::SeekOnEvent(in_eventID, in_gameObjectID, in_iPosition, in_bSeekToNearestMarker, in_PlayingID);
}

AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Time_String(const char* in_pszEventName, AkGameObjectID in_gameObjectID, AkTimeMs in_iPosition, bool in_bSeekToNearestMarker, AkPlayingID in_PlayingID)
{
    return AK::SoundEngine::SeekOnEvent(in_pszEventName, in_gameObjectID, in_iPosition, in_bSeekToNearestMarker, in_PlayingID);
}

AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Percent_ID(AkUniqueID in_eventID, AkGameObjectID in_gameObjectID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker, AkPlayingID in_PlayingID)
{
    return AK::SoundEngine::SeekOnEvent(in_eventID, in_gameObjectID, in_fPercent, in_bSeekToNearestMarker, in_PlayingID);
}

AKRESULT WWISEC_AK_SoundEngine_SeekOnEvent_Percent_String(const char* in_pszEventName, AkGameObjectID in_gameObjectID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker, AkPlayingID in_PlayingID)
{
    return AK::SoundEngine::SeekOnEvent(in_pszEventName, in_gameObjectID, in_fPercent, in_bSeekToNearestMarker, in_PlayingID);
}

void WWISEC_AK_SoundEngine_CancelEventCallbackCookie(void* in_pCookie)
{
    AK::SoundEngine::CancelEventCallbackCookie(in_pCookie);
}

void WWISEC_AK_SoundEngine_CancelEventCallbackGameObject(AkGameObjectID in_gameObjectID)
{
    AK::SoundEngine::CancelEventCallbackGameObject(in_gameObjectID);
}

void WWISEC_AK_SoundEngine_CancelEventCallback(AkPlayingID in_playingID)
{
    AK::SoundEngine::CancelEventCallback(in_playingID);
}

AKRESULT WWISEC_AK_SoundEngine_GetSourcePlayPosition(AkPlayingID in_PlayingID, AkTimeMs* out_puPosition, bool in_bExtrapolate)
{
    return AK::SoundEngine::GetSourcePlayPosition(in_PlayingID, reinterpret_cast<AkTimeMs*>(out_puPosition), in_bExtrapolate);
}

AKRESULT WWISEC_AK_SoundEngine_GetSourcePlayPositions(AkPlayingID in_PlayingID, WWISEC_AkSourcePosition* out_puPositions, AkUInt32* io_pcPositions, bool in_bExtrapolate)
{
    return AK::SoundEngine::GetSourcePlayPositions(in_PlayingID, reinterpret_cast<AkSourcePosition*>(out_puPositions), io_pcPositions, in_bExtrapolate);
}

AKRESULT WWISEC_AK_SoundEngine_GetSourceStreamBuffering(AkPlayingID in_PlayingID, AkTimeMs* out_buffering, bool* out_bIsBuffering)
{
    return AK::SoundEngine::GetSourceStreamBuffering(in_PlayingID, *out_buffering, *out_bIsBuffering);
}

void WWISEC_AK_SoundEngine_StopAll(AkGameObjectID in_gameObjectID)
{
    AK::SoundEngine::StopAll(in_gameObjectID);
}

void WWISEC_AK_SoundEngine_StopPlayingID(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve)
{
    AK::SoundEngine::StopPlayingID(in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve));
}

void WWISEC_AK_SoundEngine_ExecuteActionOnPlayingID(enum AkActionOnEventType in_ActionType, AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve)
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

AKRESULT WWISEC_AK_SoundEngine_SendPluginCustomGameData(AkUniqueID in_busID, AkGameObjectID in_busObjectID, enum AkPluginType in_eType, AkUInt32 in_uCompanyID, AkUInt32 in_uPluginID, const void* in_pData, AkUInt32 in_uSizeInBytes)
{
    return AK::SoundEngine::SendPluginCustomGameData(in_busID, in_busObjectID, static_cast<AkPluginType>(in_eType), in_uCompanyID, in_uPluginID, in_pData, in_uSizeInBytes);
}

AKRESULT WWISEC_AK_SoundEngine_RegisterGameObj(AkGameObjectID in_gameObjectID)
{
    return AK::SoundEngine::RegisterGameObj(in_gameObjectID);
}

AKRESULT WWISEC_AK_SoundEngine_RegisterGameObjWithName(AkGameObjectID in_gameObjectID, const char* in_pszObjName)
{
    return AK::SoundEngine::RegisterGameObj(in_gameObjectID, in_pszObjName);
}

AKRESULT WWISEC_AK_SoundEngine_UnregisterGameObj(AkGameObjectID in_gameObjectID)
{
    return AK::SoundEngine::UnregisterGameObj(in_gameObjectID);
}

AKRESULT WWISEC_AK_SoundEngine_UnregisterAllGameObj()
{
    return AK::SoundEngine::UnregisterAllGameObj();
}

AKRESULT WWISEC_AK_SoundEngine_SetPosition(AkGameObjectID in_GameObjectID, const WWISEC_AkSoundPosition* in_Position, enum AkSetPositionFlags in_eFlags)
{
    return AK::SoundEngine::SetPosition(in_GameObjectID, *reinterpret_cast<const AkSoundPosition*>(in_Position), static_cast<AkSetPositionFlags>(in_eFlags));
}

AKRESULT WWISEC_AK_SoundEngine_SetMultiplePositions_SoundPosition(AkGameObjectID in_GameObjectID, const WWISEC_AkSoundPosition* in_pPositions, AkUInt16 in_NumPositions, enum AkMultiPositionType in_eMultiPositionType, enum AkSetPositionFlags in_eFlags)
{
    return AK::SoundEngine::SetMultiplePositions(in_GameObjectID, reinterpret_cast<const AkSoundPosition*>(in_pPositions), in_NumPositions, static_cast<AK::SoundEngine::MultiPositionType>(in_eMultiPositionType), static_cast<AkSetPositionFlags>(in_eFlags));
}

AKRESULT WWISEC_AK_SoundEngine_SetMultiplePositions_ChannelEmitter(AkGameObjectID in_GameObjectID, const WWISEC_AkChannelEmitter* in_pPositions, AkUInt16 in_NumPositions, enum AkMultiPositionType in_eMultiPositionType, enum AkSetPositionFlags in_eFlags)
{
    return AK::SoundEngine::SetMultiplePositions(in_GameObjectID, reinterpret_cast<const AkChannelEmitter*>(in_pPositions), in_NumPositions, static_cast<AK::SoundEngine::MultiPositionType>(in_eMultiPositionType), static_cast<AkSetPositionFlags>(in_eFlags));
}

AKRESULT WWISEC_AK_SoundEngine_SetScalingFactor(AkGameObjectID in_GameObjectID, AkReal32 in_fAttenuationScalingFactor)
{
    return AK::SoundEngine::SetScalingFactor(in_GameObjectID, in_fAttenuationScalingFactor);
}

AKRESULT WWISEC_AK_SoundEngine_SetDistanceProbe(AkGameObjectID in_listenerGameObjectID, AkGameObjectID in_distanceProbeGameObjectID)
{
    return AK::SoundEngine::SetDistanceProbe(in_listenerGameObjectID, in_distanceProbeGameObjectID);
}

AKRESULT WWISEC_AK_SoundEngine_ClearBanks()
{
    return AK::SoundEngine::ClearBanks();
}

AKRESULT WWISEC_AK_SoundEngine_SetBankLoadIOSettings(AkReal32 in_fThroughput, AkPriority in_priority)
{
    return AK::SoundEngine::SetBankLoadIOSettings(in_fThroughput, in_priority);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBank_String(const char* in_pszString, AkBankID* out_bankID, AkBankType in_bankType)
{
    return AK::SoundEngine::LoadBank(in_pszString, *out_bankID, in_bankType);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBank_ID(AkBankID in_bankID, AkBankType in_bankType)
{
    return AK::SoundEngine::LoadBank(in_bankID, in_bankType);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, AkBankID* out_bankID)
{
    return AK::SoundEngine::LoadBankMemoryView(in_pInMemoryBankPtr, in_uInMemoryBankSize, *out_bankID);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, AkBankID* out_bankID, AkBankType* out_bankType)
{
    return AK::SoundEngine::LoadBankMemoryView(in_pInMemoryBankPtr, in_uInMemoryBankSize, *out_bankID, *out_bankType);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, AkBankID* out_bankID)
{
    return AK::SoundEngine::LoadBankMemoryCopy(in_pInMemoryBankPtr, in_uInMemoryBankSize, *out_bankID);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, AkBankID* out_bankID, AkBankType* out_bankType)
{
    return AK::SoundEngine::LoadBankMemoryCopy(in_pInMemoryBankPtr, in_uInMemoryBankSize, *out_bankID, *out_bankType);
}

AKRESULT WWISEC_AK_SoundEngine_DecodeBank(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, AkMemPoolId in_uPoolForDecodedBank, void** out_pDecodedBankPtr, AkUInt32* out_uDecodedBankSize)
{
    return AK::SoundEngine::DecodeBank(in_pInMemoryBankPtr, in_uInMemoryBankSize, in_uPoolForDecodedBank, *out_pDecodedBankPtr, *out_uDecodedBankSize);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBank_Async_String(const char* in_pszString, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankID* out_bankID, AkBankType in_bankType)
{
    return AK::SoundEngine::LoadBank(in_pszString, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, *out_bankID, in_bankType);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBank_Async_ID(AkBankID in_bankID, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankType in_bankType)
{
    return AK::SoundEngine::LoadBank(in_bankID, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, in_bankType);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_Async(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankID* out_bankID)
{
    return AK::SoundEngine::LoadBankMemoryView(in_pInMemoryBankPtr, in_uInMemoryBankSize, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, *out_bankID);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryView_Async_OutBankType(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankID* out_bankID, AkBankType* out_bankType)
{
    return AK::SoundEngine::LoadBankMemoryView(in_pInMemoryBankPtr, in_uInMemoryBankSize, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, *out_bankID, *out_bankType);
}

AKRESULT WWISEC_AK_SoundEngine_LoadBankMemoryCopy_Async(const void* in_pInMemoryBankPtr, AkUInt32 in_uInMemoryBankSize, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankID* out_bankID)
{
    return AK::SoundEngine::LoadBankMemoryCopy(in_pInMemoryBankPtr, in_uInMemoryBankSize, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, *out_bankID);
}

AKRESULT WWISEC_AK_SoundEngine_UnloadBank_String(const char* in_pszString, const void* in_pInMemoryBankPtr, AkBankType in_bankType)
{
    return AK::SoundEngine::UnloadBank(in_pszString, in_pInMemoryBankPtr, in_bankType);
}

AKRESULT WWISEC_AK_SoundEngine_UnloadBank_ID(AkBankID in_bankID, const void* in_pInMemoryBankPtr, AkBankType in_bankType)
{
    return AK::SoundEngine::UnloadBank(in_bankID, in_pInMemoryBankPtr, in_bankType);
}

AKRESULT WWISEC_AK_SoundEngine_UnloadBank_Async_String(const char* in_pszString, const void* in_pInMemoryBankPtr, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankType in_bankType)
{
    return AK::SoundEngine::UnloadBank(in_pszString, in_pInMemoryBankPtr, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, in_bankType);
}

AKRESULT WWISEC_AK_SoundEngine_UnloadBank_Async_ID(AkBankID in_bankID, const void* in_pInMemoryBankPtr, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, AkBankType in_bankType)
{
    return AK::SoundEngine::UnloadBank(in_bankID, in_pInMemoryBankPtr, reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback), in_pCookie, in_bankType);
}

void WWISEC_AK_SoundEngine_CancelBankCallbackCookie(void* in_pCookie)
{
    AK::SoundEngine::CancelBankCallbackCookie(in_pCookie);
}

AKRESULT WWISEC_AK_SoundEngine_PrepareBank_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char* in_pszString, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, AkBankType in_bankType)
{
    return AK::SoundEngine::PrepareBank(static_cast<AK::SoundEngine::PreparationType>(in_PreparationType), in_pszString, static_cast<AK::SoundEngine::AkBankContent>(in_uFlags), static_cast<AkBankType>(in_bankType));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareBank_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkBankID in_bankID, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, AkBankType in_bankType)
{
    return AK::SoundEngine::PrepareBank(static_cast<AK::SoundEngine::PreparationType>(in_PreparationType), static_cast<AkBankID>(in_bankID), static_cast<AK::SoundEngine::AkBankContent>(in_uFlags), static_cast<AkBankType>(in_bankType));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareBank_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char* in_pszString, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, AkBankType in_bankType)
{
    return static_cast<AKRESULT>(AK::SoundEngine::PrepareBank(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        in_pszString,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie,
        static_cast<AK::SoundEngine::AkBankContent>(in_uFlags),
        static_cast<AkBankType>(in_bankType)));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareBank_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkBankID in_bankID, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie, WWISEC_AK_SoundEngine_AkBankContent in_uFlags, AkBankType in_bankType)
{
    return static_cast<AKRESULT>(AK::SoundEngine::PrepareBank(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        in_bankID,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie,
        static_cast<AK::SoundEngine::AkBankContent>(in_uFlags),
        static_cast<AkBankType>(in_bankType)));
}

AKRESULT WWISEC_AK_SoundEngine_ClearPreparedEvents()
{
    return AK::SoundEngine::ClearPreparedEvents();
}

AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uNumEvent)
{
    return AK::SoundEngine::PrepareEvent(static_cast<AK::SoundEngine::PreparationType>(in_PreparationType), in_ppszString, in_uNumEvent);
}

AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkUniqueID* in_pEventID, AkUInt32 in_uNumEvent)
{
    return AK::SoundEngine::PrepareEvent(static_cast<AK::SoundEngine::PreparationType>(in_PreparationType), in_pEventID, in_uNumEvent);
}

AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uNumEvent, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie)
{
    return static_cast<AKRESULT>(AK::SoundEngine::PrepareEvent(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        in_ppszString,
        in_uNumEvent,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareEvent_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkUniqueID* in_pEventID, AkUInt32 in_uNumEvent, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie)
{
    return static_cast<AKRESULT>(AK::SoundEngine::PrepareEvent(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        in_pEventID,
        in_uNumEvent,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareBus_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uBusses)
{
    return static_cast<AKRESULT>(
        AK::SoundEngine::PrepareBus(
            static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
            in_ppszString,
            in_uBusses));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareBus_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkUniqueID* in_pBusID, AkUInt32 in_uBusses)
{
    return static_cast<AKRESULT>(
        AK::SoundEngine::PrepareBus(
            static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
            reinterpret_cast<AkUniqueID*>(in_pBusID),
            in_uBusses));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareBus_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, const char** in_ppszString, AkUInt32 in_uBusses, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie)
{
    return static_cast<AKRESULT>(
        AK::SoundEngine::PrepareBus(
            static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
            in_ppszString,
            in_uBusses,
            reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
            in_pCookie));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareBus_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, AkUniqueID* in_pBusID, AkUInt32 in_uBusses, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie)
{
    return static_cast<AKRESULT>(
        AK::SoundEngine::PrepareBus(
            static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
            reinterpret_cast<AkUniqueID*>(in_pBusID),
            in_uBusses,
            reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
            in_pCookie));
}

AKRESULT WWISEC_AK_SoundEngine_SetMedia(WWISEC_AkSourceSettings* in_pSourceSettings, AkUInt32 in_uNumSourceSettings)
{
    return AK::SoundEngine::SetMedia(reinterpret_cast<AkSourceSettings*>(in_pSourceSettings), in_uNumSourceSettings);
}

AKRESULT WWISEC_AK_SoundEngine_TryUnsetMedia(WWISEC_AkSourceSettings* in_pSourceSettings, AkUInt32 in_uNumSourceSettings, AKRESULT* out_pUnsetResults)
{
    return AK::SoundEngine::TryUnsetMedia(reinterpret_cast<AkSourceSettings*>(in_pSourceSettings), in_uNumSourceSettings, reinterpret_cast<AKRESULT*>(out_pUnsetResults));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, enum AkGroupType in_eGameSyncType, const char* in_pszGroupName, const char** in_ppszGameSyncName, AkUInt32 in_uNumGameSyncs)
{
    return static_cast<AKRESULT>(AK::SoundEngine::PrepareGameSyncs(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        static_cast<AkGroupType>(in_eGameSyncType),
        in_pszGroupName,
        in_ppszGameSyncName,
        in_uNumGameSyncs));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, enum AkGroupType in_eGameSyncType, AkUInt32 in_GroupID, AkUInt32* in_paGameSyncID, AkUInt32 in_uNumGameSyncs)
{
    return static_cast<AKRESULT>(AK::SoundEngine::PrepareGameSyncs(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        static_cast<AkGroupType>(in_eGameSyncType),
        in_GroupID,
        in_paGameSyncID,
        in_uNumGameSyncs));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_Async_String(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, enum AkGroupType in_eGameSyncType, const char* in_pszGroupName, const char** in_ppszGameSyncName, AkUInt32 in_uNumGameSyncs, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie)
{
    return static_cast<AKRESULT>(AK::SoundEngine::PrepareGameSyncs(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        static_cast<AkGroupType>(in_eGameSyncType),
        in_pszGroupName,
        in_ppszGameSyncName,
        in_uNumGameSyncs,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie));
}

AKRESULT WWISEC_AK_SoundEngine_PrepareGameSyncs_Async_ID(WWISEC_AK_SoundEngine_PreparationType in_PreparationType, enum AkGroupType in_eGameSyncType, AkUInt32 in_GroupID, AkUInt32* in_paGameSyncID, AkUInt32 in_uNumGameSyncs, WWISEC_AkBankCallbackFunc in_pfnBankCallback, void* in_pCookie)
{
    return static_cast<AKRESULT>(AK::SoundEngine::PrepareGameSyncs(
        static_cast<AK::SoundEngine::PreparationType>(in_PreparationType),
        static_cast<AkGroupType>(in_eGameSyncType),
        in_GroupID,
        in_paGameSyncID,
        in_uNumGameSyncs,
        reinterpret_cast<AkBankCallbackFunc>(in_pfnBankCallback),
        in_pCookie));
}

AKRESULT WWISEC_AK_SoundEngine_SetListeners(AkGameObjectID in_emitterGameObj, const AkGameObjectID* in_pListenerGameObjs, AkUInt32 in_uNumListeners)
{
    return AK::SoundEngine::SetListeners(in_emitterGameObj, reinterpret_cast<const AkGameObjectID*>(in_pListenerGameObjs), in_uNumListeners);
}

AKRESULT WWISEC_AK_SoundEngine_AddListener(AkGameObjectID in_emitterGameObj, AkGameObjectID in_listenerGameObj)
{
    return AK::SoundEngine::AddListener(in_emitterGameObj, in_listenerGameObj);
}

AKRESULT WWISEC_AK_SoundEngine_RemoveListener(AkGameObjectID in_emitterGameObj, AkGameObjectID in_listenerGameObj)
{
    return AK::SoundEngine::RemoveListener(in_emitterGameObj, in_listenerGameObj);
}

AKRESULT WWISEC_AK_SoundEngine_SetDefaultListeners(const AkGameObjectID* in_pListenerObjs, AkUInt32 in_uNumListeners)
{
    return AK::SoundEngine::SetDefaultListeners(reinterpret_cast<const AkGameObjectID*>(in_pListenerObjs), in_uNumListeners);
}

AKRESULT WWISEC_AK_SoundEngine_AddDefaultListener(AkGameObjectID in_listenerGameObj)
{
    return AK::SoundEngine::AddDefaultListener(in_listenerGameObj);
}

AKRESULT WWISEC_AK_SoundEngine_RemoveDefaultListener(AkGameObjectID in_listenerGameObj)
{
    return AK::SoundEngine::RemoveDefaultListener(in_listenerGameObj);
}

AKRESULT WWISEC_AK_SoundEngine_ResetListenersToDefault(AkGameObjectID in_emitterGameObj)
{
    return AK::SoundEngine::ResetListenersToDefault(in_emitterGameObj);
}

AKRESULT WWISEC_AK_SoundEngine_SetListenerSpatialization(AkGameObjectID in_uListenerID, bool in_bSpatialized, WWISEC_AkChannelConfig in_channelConfig, WWISEC_AK_SpeakerVolumes_VectorPtr in_pVolumeOffsets)
{
    AkChannelConfig converted_channel_config;
    converted_channel_config.Deserialize(in_channelConfig);

    return AK::SoundEngine::SetListenerSpatialization(in_uListenerID, in_bSpatialized, converted_channel_config, reinterpret_cast<AK::SpeakerVolumes::VectorPtr>(in_pVolumeOffsets));
}

AKRESULT WWISEC_AK_SoundEngine_SetRTPCValue_ID(AkRtpcID in_rtpcID, AkRtpcValue in_value, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return AK::SoundEngine::SetRTPCValue(in_rtpcID, in_value, in_gameObjectID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation);
}

AKRESULT WWISEC_AK_SoundEngine_SetRTPCValue_String(const char* in_pszRtpcName, AkRtpcValue in_value, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return AK::SoundEngine::SetRTPCValue(in_pszRtpcName, in_value, in_gameObjectID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation);
}

AKRESULT WWISEC_AK_SoundEngine_SetRTPCValueByPlayingID_ID(AkRtpcID in_rtpcID, AkRtpcValue in_value, AkPlayingID in_playingID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return AK::SoundEngine::SetRTPCValueByPlayingID(in_rtpcID, in_value, in_playingID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation);
}

AKRESULT WWISEC_AK_SoundEngine_SetRTPCValueByPlayingID_String(const char* in_pszRtpcName, AkRtpcValue in_value, AkPlayingID in_playingID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return AK::SoundEngine::SetRTPCValueByPlayingID(in_pszRtpcName, in_value, in_playingID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation);
}

AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValue_ID(AkRtpcID in_rtpcID, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return AK::SoundEngine::ResetRTPCValue(in_rtpcID, in_gameObjectID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation);
}

AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValue_String(const char* in_pszRtpcName, AkGameObjectID in_gameObjectID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return AK::SoundEngine::ResetRTPCValue(in_pszRtpcName, in_gameObjectID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation);
}

AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValueByPlayingID_ID(AkRtpcID in_rtpcID, AkPlayingID in_playingID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return AK::SoundEngine::ResetRTPCValueByPlayingID(in_rtpcID, in_playingID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation);
}

AKRESULT WWISEC_AK_SoundEngine_ResetRTPCValueByPlayingID_String(const char* in_pszRtpcName, AkPlayingID in_playingID, AkTimeMs in_uValueChangeDuration, enum AkCurveInterpolation in_eFadeCurve, bool in_bBypassInternalValueInterpolation)
{
    return AK::SoundEngine::ResetRTPCValueByPlayingID(in_pszRtpcName, in_playingID, in_uValueChangeDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve), in_bBypassInternalValueInterpolation);
}

AKRESULT WWISEC_AK_SoundEngine_SetSwitch_ID(AkSwitchGroupID in_switchGroup, AkSwitchStateID in_switchState, AkGameObjectID in_gameObjectID)
{
    return AK::SoundEngine::SetSwitch(in_switchGroup, in_switchState, in_gameObjectID);
}

AKRESULT WWISEC_AK_SoundEngine_SetSwitch_String(const char* in_pszSwitchGroup, const char* in_pszSwitchState, AkGameObjectID in_gameObjectID)
{
    return AK::SoundEngine::SetSwitch(in_pszSwitchGroup, in_pszSwitchState, in_gameObjectID);
}

AKRESULT WWISEC_AK_SoundEngine_PostTrigger_ID(AkTriggerID in_triggerID, AkGameObjectID in_gameObjectID)
{
    return AK::SoundEngine::PostTrigger(in_triggerID, in_gameObjectID);
}

AKRESULT WWISEC_AK_SoundEngine_PostTrigger_String(const char* in_pszTrigger, AkGameObjectID in_gameObjectID)
{
    return AK::SoundEngine::PostTrigger(in_pszTrigger, in_gameObjectID);
}

AKRESULT WWISEC_AK_SoundEngine_SetState_ID(AkStateGroupID in_stateGroup, AkStateID in_state)
{
    return AK::SoundEngine::SetState(in_stateGroup, in_state);
}

AKRESULT WWISEC_AK_SoundEngine_SetState_String(const char* in_pszStateGroup, const char* in_pszState)
{
    return AK::SoundEngine::SetState(in_pszStateGroup, in_pszState);
}

AKRESULT WWISEC_AK_SoundEngine_SetGameObjectAuxSendValues(AkGameObjectID in_gameObjectID, WWISEC_AkAuxSendValue* in_aAuxSendValues, AkUInt32 in_uNumSendValues)
{
    return AK::SoundEngine::SetGameObjectAuxSendValues(in_gameObjectID, reinterpret_cast<AkAuxSendValue*>(in_aAuxSendValues), in_uNumSendValues);
}

AKRESULT WWISEC_AK_SoundEngine_RegisterBusVolumeCallback(AkUniqueID in_busID, WWISEC_AkBusCallbackFunc in_pfnCallback, void* in_pCookie)
{
    return AK::SoundEngine::RegisterBusVolumeCallback(in_busID, reinterpret_cast<AkBusCallbackFunc>(in_pfnCallback), in_pCookie);
}

AKRESULT WWISEC_AK_SoundEngine_RegisterBusMeteringCallback(AkUniqueID in_busID, WWISEC_AkBusMeteringCallbackFunc in_pfnCallback, enum AkMeteringFlags in_eMeteringFlags, void* in_pCookie)
{
    return AK::SoundEngine::RegisterBusMeteringCallback(in_busID, reinterpret_cast<AkBusMeteringCallbackFunc>(in_pfnCallback), static_cast<AkMeteringFlags>(in_eMeteringFlags), in_pCookie);
}

AKRESULT WWISEC_AK_SoundEngine_RegisterOutputDeviceMeteringCallback(AkOutputDeviceID in_idOutput, WWISEC_AkOutputDeviceMeteringCallbackFunc in_pfnCallback, enum AkMeteringFlags in_eMeteringFlags, void* in_pCookie)
{
    return AK::SoundEngine::RegisterOutputDeviceMeteringCallback(in_idOutput, reinterpret_cast<AkOutputDeviceMeteringCallbackFunc>(in_pfnCallback), static_cast<AkMeteringFlags>(in_eMeteringFlags), in_pCookie);
}

AKRESULT WWISEC_AK_SoundEngine_SetGameObjectOutputBusVolume(AkGameObjectID in_emitterObjID, AkGameObjectID in_listenerObjID, AkReal32 in_fControlValue)
{
    return AK::SoundEngine::SetGameObjectOutputBusVolume(in_emitterObjID, in_listenerObjID, in_fControlValue);
}

AKRESULT WWISEC_AK_SoundEngine_SetActorMixerEffect(AkUniqueID in_audioNodeID, AkUInt32 in_uFXIndex, AkUniqueID in_shareSetID)
{
    return AK::SoundEngine::SetActorMixerEffect(in_audioNodeID, in_uFXIndex, in_shareSetID);
}

AKRESULT WWISEC_AK_SoundEngine_SetBusEffect_ID(AkUniqueID in_audioNodeID, AkUInt32 in_uFXIndex, AkUniqueID in_shareSetID)
{
    return AK::SoundEngine::SetBusEffect(in_audioNodeID, in_uFXIndex, in_shareSetID);
}

AKRESULT WWISEC_AK_SoundEngine_SetBusEffect_String(const char* in_pszBusName, AkUInt32 in_uFXIndex, AkUniqueID in_shareSetID)
{
    return AK::SoundEngine::SetBusEffect(in_pszBusName, in_uFXIndex, in_shareSetID);
}

AKRESULT WWISEC_AK_SoundEngine_SetOutputDeviceEffect(AkOutputDeviceID in_outputDeviceID, AkUInt32 in_uFXIndex, AkUniqueID in_FXShareSetID)
{
    return AK::SoundEngine::SetOutputDeviceEffect(in_outputDeviceID, in_uFXIndex, in_FXShareSetID);
}

AKRESULT WWISEC_AK_SoundEngine_SetBusConfig_ID(AkUniqueID in_audioNodeID, WWISEC_AkChannelConfig in_channelConfig)
{
    AkChannelConfig converted_channel_config;
    converted_channel_config.Deserialize(in_channelConfig);

    return AK::SoundEngine::SetBusConfig(in_audioNodeID, converted_channel_config);
}

AKRESULT WWISEC_AK_SoundEngine_SetBusConfig_String(const char* in_pszBusName, WWISEC_AkChannelConfig in_channelConfig)
{
    AkChannelConfig converted_channel_config;
    converted_channel_config.Deserialize(in_channelConfig);

    return AK::SoundEngine::SetBusConfig(in_pszBusName, converted_channel_config);
}

AKRESULT WWISEC_AK_SoundEngine_SetObjectObstructionAndOcclusion(AkGameObjectID in_EmitterID, AkGameObjectID in_ListenerID, AkReal32 in_fObstructionLevel, AkReal32 in_fOcclusionLevel)
{
    return AK::SoundEngine::SetObjectObstructionAndOcclusion(in_EmitterID, in_ListenerID, in_fObstructionLevel, in_fOcclusionLevel);
}

AKRESULT WWISEC_AK_SoundEngine_SetMultipleObstructionAndOcclusion(AkGameObjectID in_EmitterID, AkGameObjectID in_uListenerID, WWISEC_AkObstructionOcclusionValues* in_fObstructionOcclusionValues, AkUInt32 in_uNumOcclusionObstruction)
{
    return AK::SoundEngine::SetMultipleObstructionAndOcclusion(in_EmitterID, in_uListenerID, reinterpret_cast<AkObstructionOcclusionValues*>(in_fObstructionOcclusionValues), in_uNumOcclusionObstruction);
}

AKRESULT WWISEC_AK_SoundEngine_GetContainerHistory(WWISEC_AK_IWriteBytes* in_pBytes)
{
    return AK::SoundEngine::GetContainerHistory(reinterpret_cast<AK::IWriteBytes*>(in_pBytes));
}

AKRESULT WWISEC_AK_SoundEngine_SetContainerHistory(WWISEC_AK_IReadBytes* in_pBytes)
{
    return AK::SoundEngine::SetContainerHistory(reinterpret_cast<AK::IReadBytes*>(in_pBytes));
}

AKRESULT WWISEC_AK_SoundEngine_StartOutputCapture(const AkOSChar* in_CaptureFileName)
{
    return AK::SoundEngine::StartOutputCapture(in_CaptureFileName);
}

AKRESULT WWISEC_AK_SoundEngine_StopOutputCapture()
{
    return AK::SoundEngine::StopOutputCapture();
}

AKRESULT WWISEC_AK_SoundEngine_AddOutputCaptureMarker(const char* in_MarkerText)
{
    return AK::SoundEngine::AddOutputCaptureMarker(in_MarkerText);
}

AKRESULT WWISEC_AK_SoundEngine_AddOutputCaptureBinaryMarker(void* in_pMarkerData, AkUInt32 in_uMarkerDataSize)
{
    return AK::SoundEngine::AddOutputCaptureBinaryMarker(in_pMarkerData, in_uMarkerDataSize);
}

AkUInt32 WWISEC_AK_SoundEngine_GetSampleRate()
{
    return AK::SoundEngine::GetSampleRate();
}

AKRESULT WWISEC_AK_SoundEngine_RegisterCaptureCallback(WWISEC_AkCaptureCallbackFunc in_pfnCallback, AkOutputDeviceID in_idOutput, void* in_pCookie)
{
    return AK::SoundEngine::RegisterCaptureCallback(reinterpret_cast<AkCaptureCallbackFunc>(in_pfnCallback), in_idOutput, in_pCookie);
}

AKRESULT WWISEC_AK_SoundEngine_UnregisterCaptureCallback(WWISEC_AkCaptureCallbackFunc in_pfnCallback, AkOutputDeviceID in_idOutput, void* in_pCookie)
{
    return AK::SoundEngine::UnregisterCaptureCallback(reinterpret_cast<AkCaptureCallbackFunc>(in_pfnCallback), in_idOutput, in_pCookie);
}

AKRESULT WWISEC_AK_SoundEngine_StartProfilerCapture(const AkOSChar* in_CaptureFileName)
{
    return AK::SoundEngine::StartProfilerCapture(in_CaptureFileName);
}

AKRESULT WWISEC_AK_SoundEngine_StopProfilerCapture()
{
    return AK::SoundEngine::StopProfilerCapture();
}

AKRESULT WWISEC_AK_SoundEngine_SetOfflineRenderingFrameTime(AkReal32 in_fFrameTimeInSeconds)
{
    return AK::SoundEngine::SetOfflineRenderingFrameTime(in_fFrameTimeInSeconds);
}

AKRESULT WWISEC_AK_SoundEngine_SetOfflineRendering(bool in_bEnableOfflineRendering)
{
    return AK::SoundEngine::SetOfflineRendering(in_bEnableOfflineRendering);
}

AKRESULT WWISEC_AK_SoundEngine_AddOutput(const WWISEC_AkOutputSettings* in_Settings, AkOutputDeviceID* out_pDeviceID, const AkGameObjectID* in_pListenerIDs, AkUInt32 in_uNumListeners)
{
    return AK::SoundEngine::AddOutput(*reinterpret_cast<const AkOutputSettings*>(in_Settings), reinterpret_cast<AkOutputDeviceID*>(out_pDeviceID), reinterpret_cast<const AkGameObjectID*>(in_pListenerIDs), in_uNumListeners);
}

AKRESULT WWISEC_AK_SoundEngine_RemoveOutput(AkOutputDeviceID in_idOutput)
{
    return AK::SoundEngine::RemoveOutput(in_idOutput);
}

AKRESULT WWISEC_AK_SoundEngine_ReplaceOutput(const WWISEC_AkOutputSettings* in_Settings, AkOutputDeviceID in_outputDeviceId, AkOutputDeviceID* out_pOutputDeviceId)
{
    return AK::SoundEngine::ReplaceOutput(*reinterpret_cast<const AkOutputSettings*>(in_Settings), in_outputDeviceId, reinterpret_cast<AkOutputDeviceID*>(out_pOutputDeviceId));
}

AkOutputDeviceID WWISEC_AK_SoundEngine_GetOutputID_ID(AkUniqueID in_idShareset, AkUInt32 in_idDevice)
{
    return static_cast<AkOutputDeviceID>(AK::SoundEngine::GetOutputID(in_idShareset, in_idDevice));
}

AkOutputDeviceID WWISEC_AK_SoundEngine_GetOutputID_String(const char* in_szShareSet, AkUInt32 in_idDevice)
{
    return static_cast<AkOutputDeviceID>(AK::SoundEngine::GetOutputID(in_szShareSet, in_idDevice));
}

AKRESULT WWISEC_AK_SoundEngine_SetBusDevice_ID(AkUniqueID in_idBus, AkUniqueID in_idNewDevice)
{
    return AK::SoundEngine::SetBusDevice(in_idBus, in_idNewDevice);
}

AKRESULT WWISEC_AK_SoundEngine_SetBusDevice_String(const char* in_BusName, const char* in_DeviceName)
{
    return AK::SoundEngine::SetBusDevice(in_BusName, in_DeviceName);
}

AKRESULT WWISEC_AK_SoundEngine_GetDeviceList_Plugin(AkUInt32 in_ulCompanyID, AkUInt32 in_ulPluginID, AkUInt32* io_maxNumDevices, WWISEC_AkDeviceDescription* out_deviceDescriptions)
{
    return AK::SoundEngine::GetDeviceList(in_ulCompanyID, in_ulPluginID, *io_maxNumDevices, reinterpret_cast<AkDeviceDescription*>(out_deviceDescriptions));
}

AKRESULT WWISEC_AK_SoundEngine_GetDeviceList_ShareSet(AkUniqueID in_audioDeviceShareSetID, AkUInt32* io_maxNumDevices, WWISEC_AkDeviceDescription* out_deviceDescriptions)
{
    return AK::SoundEngine::GetDeviceList(in_audioDeviceShareSetID, *io_maxNumDevices, reinterpret_cast<AkDeviceDescription*>(out_deviceDescriptions));
}

AKRESULT WWISEC_AK_SoundEngine_SetOutputVolume(AkOutputDeviceID in_idOutput, AkReal32 in_fVolume)
{
    return AK::SoundEngine::SetOutputVolume(in_idOutput, in_fVolume);
}

AKRESULT WWISEC_AK_SoundEngine_GetDeviceSpatialAudioSupport(AkUInt32 in_idDevice)
{
    return AK::SoundEngine::GetDeviceSpatialAudioSupport(in_idDevice);
}

AKRESULT WWISEC_AK_SoundEngine_Suspend(bool in_bRenderAnyway, bool in_bFadeOut)
{
    return AK::SoundEngine::Suspend(in_bRenderAnyway, in_bFadeOut);
}

AKRESULT WWISEC_AK_SoundEngine_WakeupFromSuspend(AkUInt32 in_uDelayMs)
{
    return AK::SoundEngine::WakeupFromSuspend(in_uDelayMs);
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

// BEGIN AkFileSystemFlags
static_assert(sizeof(WWISEC_AkFileSystemFlags) == sizeof(AkFileSystemFlags));
// END AkFileSystemFlags

// BEGIN IAkStreamMgr
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_StmStatusError);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_MoveEnd);
WWISEC_ASSERT_ENUM_VALUE_SAME(AK_OpenModeReadWrite);
static_assert(sizeof(WWISEC_AkStreamInfo) == sizeof(AkStreamInfo));
static_assert(sizeof(WWISEC_AkAutoStmHeuristics) == sizeof(AkAutoStmHeuristics));
static_assert(sizeof(WWISEC_AkAutoStmBufSettings) == sizeof(WWISEC_AkAutoStmBufSettings));
static_assert(sizeof(WWISEC_AkDeviceDesc) == sizeof(AkDeviceDesc));
static_assert(sizeof(WWISEC_AkDeviceData) == sizeof(AkDeviceData));
static_assert(sizeof(WWISEC_AkStreamRecord) == sizeof(AkStreamRecord));
static_assert(sizeof(WWISEC_AkStreamData) == sizeof(AkStreamData));
static_assert(sizeof(WWISEC_AkFileOpenData) == sizeof(AkFileOpenData));
class WWISEC_AK_IAkStreamProfile_Wrapper : public AK::IAkStreamProfile
{
  public:
    WWISEC_AK_IAkStreamProfile_Wrapper(void* instance, const WWISEC_AK_IAkStreamProfile_FunctionTable* functionTable)
        : _instance(instance), _functions(*functionTable)
    {
    }

    ~WWISEC_AK_IAkStreamProfile_Wrapper()
    {
        _functions.Destructor(_instance);
    }

    void GetStreamRecord(AkStreamRecord& out_streamRecord) override
    {
        _functions.GetStreamRecord(_instance, reinterpret_cast<WWISEC_AkStreamRecord*>(&out_streamRecord));
    }

    void GetStreamData(AkStreamData& out_streamData) override
    {
        _functions.GetStreamData(_instance, reinterpret_cast<WWISEC_AkStreamData*>(&out_streamData));
    }

    bool IsNew() override
    {
        return _functions.IsNew(_instance);
    }

    void ClearNew() override
    {
        return _functions.ClearNew(_instance);
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_IAkStreamProfile_FunctionTable _functions;
};

WWISEC_AK_IAkStreamProfile* WWISEC_AK_IAkStreamProfile_CreateInstance(void* instance, const WWISEC_AK_IAkStreamProfile_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_IAkStreamProfile*>(AkNew(AkMemID_Integration, WWISEC_AK_IAkStreamProfile_Wrapper)(instance, functionTable));
}

void WWISEC_AK_IAkStreamProfile_DestroyInstance(WWISEC_AK_IAkStreamProfile* instance)
{
    WWISEC_AK_IAkStreamProfile_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_IAkStreamProfile_Wrapper*>(instance);
    wrapper->~WWISEC_AK_IAkStreamProfile_Wrapper();
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

void WWISEC_AK_IAkStreamProfile_GetStreamRecord(WWISEC_AK_IAkStreamProfile* instance, WWISEC_AkStreamRecord* out_streamRecord)
{
    reinterpret_cast<AK::IAkStreamProfile*>(instance)->GetStreamRecord(*reinterpret_cast<AkStreamRecord*>(out_streamRecord));
}

void WWISEC_AK_IAkStreamProfile_GetStreamData(WWISEC_AK_IAkStreamProfile* instance, WWISEC_AkStreamData* out_streamData)
{
    reinterpret_cast<AK::IAkStreamProfile*>(instance)->GetStreamData(*reinterpret_cast<AkStreamData*>(out_streamData));
}
bool WWISEC_AK_IAkStreamProfile_IsNew(WWISEC_AK_IAkStreamProfile* instance)
{
    return reinterpret_cast<AK::IAkStreamProfile*>(instance)->IsNew();
}

void WWISEC_AK_IAkStreamProfile_ClearNew(WWISEC_AK_IAkStreamProfile* instance)
{
    reinterpret_cast<AK::IAkStreamProfile*>(instance)->ClearNew();
}

class WWISEC_AK_IAkDeviceProfile_Wrapper : public AK::IAkDeviceProfile
{
  public:
    WWISEC_AK_IAkDeviceProfile_Wrapper(void* instance, const WWISEC_AK_IAkDeviceProfile_FunctionTable* functionTable)
        : _instance(instance), _functions(*functionTable)
    {
    }

    ~WWISEC_AK_IAkDeviceProfile_Wrapper()
    {
        _functions.Destructor(_instance);
    }

    void OnProfileStart() override
    {
        _functions.OnProfileStart(_instance);
    }

    void OnProfileEnd() override
    {
        _functions.OnProfileEnd(_instance);
    }

    void GetDesc(AkDeviceDesc& out_deviceDesc) override
    {
        _functions.GetDesc(_instance, reinterpret_cast<WWISEC_AkDeviceDesc*>(&out_deviceDesc));
    }

    void GetData(AkDeviceData& out_deviceData) override
    {
        _functions.GetData(_instance, reinterpret_cast<WWISEC_AkDeviceData*>(&out_deviceData));
    }

    bool IsNew() override
    {
        return _functions.IsNew(_instance);
    }

    void ClearNew() override
    {
        _functions.ClearNew(_instance);
    }

    AkUInt32 GetNumStreams() override
    {
        return _functions.GetNumStreams(_instance);
    }

    AK::IAkStreamProfile* GetStreamProfile(AkUInt32 in_uStreamIndex) override
    {
        return reinterpret_cast<AK::IAkStreamProfile*>(_functions.GetStreamProfile(_instance, in_uStreamIndex));
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_IAkDeviceProfile_FunctionTable _functions;
};

WWISEC_AK_IAkDeviceProfile* WWISEC_AK_IAkDeviceProfile_CreateInstance(void* instance, const WWISEC_AK_IAkDeviceProfile_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_IAkDeviceProfile*>(AkNew(AkMemID_Integration, WWISEC_AK_IAkDeviceProfile_Wrapper)(instance, functionTable));
}

void WWISEC_AK_IAkDeviceProfile_DestroyInstance(WWISEC_AK_IAkStreamProfile* instance)
{
    WWISEC_AK_IAkDeviceProfile_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_IAkDeviceProfile_Wrapper*>(instance);
    wrapper->~WWISEC_AK_IAkDeviceProfile_Wrapper();
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

void WWISEC_AK_IAkDeviceProfile_OnProfileStart(WWISEC_AK_IAkDeviceProfile* instance)
{
    reinterpret_cast<AK::IAkDeviceProfile*>(instance)->OnProfileStart();
}

void WWISEC_AK_IAkDeviceProfile_OnProfileEnd(WWISEC_AK_IAkDeviceProfile* instance)
{
    reinterpret_cast<AK::IAkDeviceProfile*>(instance)->OnProfileEnd();
}

void WWISEC_AK_IAkDeviceProfile_GetDesc(WWISEC_AK_IAkDeviceProfile* instance, WWISEC_AkDeviceDesc* out_deviceDesc)
{
    reinterpret_cast<AK::IAkDeviceProfile*>(instance)->GetDesc(*reinterpret_cast<AkDeviceDesc*>(out_deviceDesc));
}

void WWISEC_AK_IAkDeviceProfile_GetData(WWISEC_AK_IAkDeviceProfile* instance, WWISEC_AkDeviceData* out_deviceData)
{
    reinterpret_cast<AK::IAkDeviceProfile*>(instance)->GetData(*reinterpret_cast<AkDeviceData*>(out_deviceData));
}

bool WWISEC_AK_IAkDeviceProfile_IsNew(WWISEC_AK_IAkDeviceProfile* instance)
{
    return reinterpret_cast<AK::IAkDeviceProfile*>(instance)->IsNew();
}

void WWISEC_AK_IAkDeviceProfile_ClearNew(WWISEC_AK_IAkDeviceProfile* instance)
{
    reinterpret_cast<AK::IAkDeviceProfile*>(instance)->ClearNew();
}

AkUInt32 WWISEC_AK_IAkDeviceProfile_GetNumStreams(WWISEC_AK_IAkDeviceProfile* instance)
{
    return reinterpret_cast<AK::IAkDeviceProfile*>(instance)->GetNumStreams();
}

WWISEC_AK_IAkStreamProfile* WWISEC_AK_IAkDeviceProfile_GetStreamProfile(WWISEC_AK_IAkDeviceProfile* instance, AkUInt32 in_uStreamIndex)
{
    return reinterpret_cast<WWISEC_AK_IAkStreamProfile*>(reinterpret_cast<AK::IAkDeviceProfile*>(instance)->GetStreamProfile(in_uStreamIndex));
}

class WWISEC_AK_IAkStreamMgrProfile_Wrapper : public AK::IAkStreamMgrProfile
{
  public:
    WWISEC_AK_IAkStreamMgrProfile_Wrapper(void* instance, const WWISEC_AK_IAkStreamMgrProfile_FunctionTable* functionTable)
        : _instance(instance), _functions(*functionTable)
    {
    }

    ~WWISEC_AK_IAkStreamMgrProfile_Wrapper()
    {
        _functions.Destructor(_instance);
    }

    AKRESULT StartMonitoring() override
    {
        return _functions.StartMonitoring(_instance);
    }

    void StopMonitoring() override
    {
        _functions.StopMonitoring(_instance);
    }

    AkUInt32 GetNumDevices() override
    {
        return _functions.GetNumDevices(_instance);
    }

    AK::IAkDeviceProfile* GetDeviceProfile(AkUInt32 in_uDeviceIndex) override
    {
        return reinterpret_cast<AK::IAkDeviceProfile*>(_functions.GetDeviceProfile(_instance, in_uDeviceIndex));
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_IAkStreamMgrProfile_FunctionTable _functions;
};

WWISEC_AK_IAkStreamMgrProfile* WWISEC_AK_IAkStreamMgrProfile_CreateInstance(void* instance, const WWISEC_AK_IAkStreamMgrProfile_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_IAkStreamMgrProfile*>(AkNew(AkMemID_Integration, WWISEC_AK_IAkStreamMgrProfile_Wrapper)(instance, functionTable));
}

void WWISEC_AK_IAkStreamMgrProfile_DestroyInstance(WWISEC_AK_IAkStreamMgrProfile* instance)
{
    WWISEC_AK_IAkStreamMgrProfile_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_IAkStreamMgrProfile_Wrapper*>(instance);
    wrapper->~WWISEC_AK_IAkStreamMgrProfile_Wrapper();
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

AKRESULT WWISEC_AK_IAkStreamMgrProfile_StartMonitoring(WWISEC_AK_IAkStreamMgrProfile* instance)
{
    return reinterpret_cast<AK::IAkStreamMgrProfile*>(instance)->StartMonitoring();
}

void WWISEC_AK_IAkStreamMgrProfile_StopMonitoring(WWISEC_AK_IAkStreamMgrProfile* instance)
{
    reinterpret_cast<AK::IAkStreamMgrProfile*>(instance)->StopMonitoring();
}

AkUInt32 WWISEC_AK_IAkStreamMgrProfile_GetNumDevices(WWISEC_AK_IAkStreamMgrProfile* instance)
{
    return reinterpret_cast<AK::IAkStreamMgrProfile*>(instance)->GetNumDevices();
}

WWISEC_AK_IAkDeviceProfile* WWISEC_AK_IAkStreamMgrProfile_GetDeviceProfile(WWISEC_AK_IAkStreamMgrProfile* instance, AkUInt32 in_uDeviceIndex)
{
    return reinterpret_cast<WWISEC_AK_IAkDeviceProfile*>(reinterpret_cast<AK::IAkStreamMgrProfile*>(instance)->GetDeviceProfile(in_uDeviceIndex));
}

class WWISEC_AK_IAkStdStream_Wrapper : public AK::IAkStdStream
{
  public:
    WWISEC_AK_IAkStdStream_Wrapper(void* instance, const WWISEC_AK_IAkStdStream_FunctionTable* functionTable)
        : _instance(instance), _functions(*functionTable)
    {
    }

    ~WWISEC_AK_IAkStdStream_Wrapper()
    {
        _functions.Destructor(_instance);
    }

    void Destroy() override
    {
        _functions.Destroy(_instance);
    }

    void GetInfo(AkStreamInfo& out_info) override
    {
        _functions.GetInfo(_instance, reinterpret_cast<WWISEC_AkStreamInfo*>(&out_info));
    }

    void* GetFileDescriptor() override
    {
        return _functions.GetFileDescriptor(_instance);
    }

    AKRESULT SetStreamName(const AkOSChar* in_pszStreamName) override
    {
        return _functions.SetStreamName(_instance, in_pszStreamName);
    }

    AkUInt32 GetBlockSize() override
    {
        return _functions.GetBlockSize(_instance);
    }

    AKRESULT Read(void* in_pBuffer, AkUInt32 in_uReqSize, bool in_bWait, AkPriority in_priority, AkReal32 in_fDeadline, AkUInt32& out_uSize) override
    {
        return _functions.Read(_instance, in_pBuffer, in_uReqSize, in_bWait, static_cast<AkPriority>(in_priority), in_fDeadline, &out_uSize);
    }

    AKRESULT Write(void* in_pBuffer, AkUInt32 in_uReqSize, bool in_bWait, AkPriority in_priority, AkReal32 in_fDeadline, AkUInt32& out_uSize) override
    {
        return _functions.Write(_instance, in_pBuffer, in_uReqSize, in_bWait, static_cast<AkPriority>(in_priority), in_fDeadline, &out_uSize);
    }

    AkUInt64 GetPosition(bool* out_pbEndOfStream) override
    {
        return _functions.GetPosition(_instance, out_pbEndOfStream);
    }

    AKRESULT SetPosition(AkInt64 in_iMoveOffset, AkMoveMethod in_eMoveMethod) override
    {
        return _functions.SetPosition(_instance, in_iMoveOffset, static_cast<WWISEC_AkMoveMethod>(in_eMoveMethod));
    }

    void Cancel() override
    {
        _functions.Cancel(_instance);
    }

    void* GetData(AkUInt32& out_uSize) override
    {
        return _functions.GetData(_instance, &out_uSize);
    }

    AkStmStatus GetStatus() override
    {
        return static_cast<AkStmStatus>(_functions.GetStatus(_instance));
    }

    AkStmStatus WaitForPendingOperation() override
    {
        return static_cast<AkStmStatus>(_functions.WaitForPendingOperation(_instance));
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_IAkStdStream_FunctionTable _functions;
};

WWISEC_AK_IAkStdStream* WWISEC_AK_IAkStdStream_CreateInstance(void* instance, const WWISEC_AK_IAkStdStream_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_IAkStdStream*>(AkNew(AkMemID_Integration, WWISEC_AK_IAkStdStream_Wrapper)(instance, functionTable));
}

void WWISEC_AK_IAkStdStream_DestroyInstance(WWISEC_AK_IAkStdStream* instance)
{
    WWISEC_AK_IAkStdStream_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_IAkStdStream_Wrapper*>(instance);
    wrapper->~WWISEC_AK_IAkStdStream_Wrapper();
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

void WWISEC_AK_IAkStdStream_Destroy(WWISEC_AK_IAkStdStream* instance)
{
    reinterpret_cast<AK::IAkStdStream*>(instance)->Destroy();
}

void WWISEC_AK_IAkStdStream_GetInfo(WWISEC_AK_IAkStdStream* instance, WWISEC_AkStreamInfo* out_info)
{
    reinterpret_cast<AK::IAkStdStream*>(instance)->GetInfo(*reinterpret_cast<AkStreamInfo*>(out_info));
}

void* WWISEC_AK_IAkStdStream_GetFileDescriptor(WWISEC_AK_IAkStdStream* instance)
{
    return reinterpret_cast<AK::IAkStdStream*>(instance)->GetFileDescriptor();
}

AKRESULT WWISEC_AK_IAkStdStream_SetStreamName(WWISEC_AK_IAkStdStream* instance, const AkOSChar* in_pszStreamName)
{
    return reinterpret_cast<AK::IAkStdStream*>(instance)->SetStreamName(in_pszStreamName);
}

AkUInt32 WWISEC_AK_IAkStdStream_GetBlockSize(WWISEC_AK_IAkStdStream* instance)
{
    return reinterpret_cast<AK::IAkStdStream*>(instance)->GetBlockSize();
}

AKRESULT WWISEC_AK_IAkStdStream_Read(WWISEC_AK_IAkStdStream* instance, void* in_pBuffer, AkUInt32 in_uReqSize, bool in_bWait, AkPriority in_priority, AkReal32 in_fDeadline, AkUInt32* out_uSize)
{
    return reinterpret_cast<AK::IAkStdStream*>(instance)->Read(in_pBuffer, in_uReqSize, in_bWait, static_cast<AkPriority>(in_priority), in_fDeadline, *out_uSize);
}

AKRESULT WWISEC_AK_IAkStdStream_Write(WWISEC_AK_IAkStdStream* instance, void* in_pBuffer, AkUInt32 in_uReqSize, bool in_bWait, AkPriority in_priority, AkReal32 in_fDeadline, AkUInt32* out_uSize)
{
    return reinterpret_cast<AK::IAkStdStream*>(instance)->Write(in_pBuffer, in_uReqSize, in_bWait, static_cast<AkPriority>(in_priority), in_fDeadline, *out_uSize);
}

AkUInt64 WWISEC_AK_IAkStdStream_GetPosition(WWISEC_AK_IAkStdStream* instance, bool* out_pbEndOfStream)
{
    return reinterpret_cast<AK::IAkStdStream*>(instance)->GetPosition(out_pbEndOfStream);
}

AKRESULT WWISEC_AK_IAkStdStream_SetPosition(WWISEC_AK_IAkStdStream* instance, AkInt64 in_iMoveOffset, WWISEC_AkMoveMethod in_eMoveMethod)
{
    return reinterpret_cast<AK::IAkStdStream*>(instance)->SetPosition(in_iMoveOffset, static_cast<AkMoveMethod>(in_eMoveMethod));
}

void WWISEC_AK_IAkStdStream_Cancel(WWISEC_AK_IAkStdStream* instance)
{
    reinterpret_cast<AK::IAkStdStream*>(instance)->Cancel();
}

void* WWISEC_AK_IAkStdStream_GetData(WWISEC_AK_IAkStdStream* instance, AkUInt32* out_uSize)
{
    return reinterpret_cast<AK::IAkStdStream*>(instance)->GetData(*out_uSize);
}

WWISEC_AkStmStatus WWISEC_AK_IAkStdStream_GetStatus(WWISEC_AK_IAkStdStream* instance)
{
    return static_cast<WWISEC_AkStmStatus>(reinterpret_cast<AK::IAkStdStream*>(instance)->GetStatus());
}

WWISEC_AkStmStatus WWISEC_AK_IAkStdStream_WaitForPendingOperation(WWISEC_AK_IAkStdStream* instance)
{
    return static_cast<WWISEC_AkStmStatus>(reinterpret_cast<AK::IAkStdStream*>(instance)->WaitForPendingOperation());
}

class WWISEC_AK_IAkAutoStream_Wrapper : public AK::IAkAutoStream
{
  public:
    WWISEC_AK_IAkAutoStream_Wrapper(void* instance, const WWISEC_AK_IAkAutoStream_FunctionTable* functionTable)
        : _instance(instance), _functions(*functionTable)
    {
    }

    ~WWISEC_AK_IAkAutoStream_Wrapper()
    {
        _functions.Destructor(_instance);
    }

    void Destroy() override
    {
        _functions.Destroy(_instance);
    }

    void GetInfo(AkStreamInfo& out_info) override
    {
        _functions.GetInfo(_instance, reinterpret_cast<WWISEC_AkStreamInfo*>(&out_info));
    }

    void* GetFileDescriptor() override
    {
        return _functions.GetFileDescriptor(_instance);
    }

    void GetHeuristics(AkAutoStmHeuristics& out_heuristics) override
    {
        _functions.GetHeuristics(_instance, reinterpret_cast<WWISEC_AkAutoStmHeuristics*>(&out_heuristics));
    }

    AKRESULT SetHeuristics(const AkAutoStmHeuristics& in_heuristics) override
    {
        return _functions.SetHeuristics(_instance, reinterpret_cast<const WWISEC_AkAutoStmHeuristics*>(&in_heuristics));
    }

    AKRESULT SetMinimalBufferSize(AkUInt32 in_uMinBufferSize) override
    {
        return _functions.SetMinimalBufferSize(_instance, in_uMinBufferSize);
    }

    AKRESULT SetStreamName(const AkOSChar* in_pszStreamName) override
    {
        return _functions.SetStreamName(_instance, in_pszStreamName);
    }

    AkUInt32 GetBlockSize() override
    {
        return _functions.GetBlockSize(_instance);
    }

    AKRESULT QueryBufferingStatus(AkUInt32& out_uNumBytesAvailable) override
    {
        return _functions.QueryBufferingStatus(_instance, &out_uNumBytesAvailable);
    }

    AkUInt32 GetNominalBuffering() override
    {
        return _functions.GetNominalBuffering(_instance);
    }

    AKRESULT Start() override
    {
        return _functions.Start(_instance);
    }

    AKRESULT Stop() override
    {
        return _functions.Stop(_instance);
    }

    AkUInt64 GetPosition(bool* out_pbEndOfStream) override
    {
        return _functions.GetPosition(_instance, out_pbEndOfStream);
    }

    AKRESULT SetPosition(AkInt64 in_iMoveOffset, AkMoveMethod in_eMoveMethod) override
    {
        return _functions.SetPosition(_instance, in_iMoveOffset, static_cast<WWISEC_AkMoveMethod>(in_eMoveMethod));
    }

    AKRESULT GetBuffer(void*& out_pBuffer, AkUInt32& out_uSize, bool in_bWait) override
    {
        return _functions.GetBuffer(_instance, &out_pBuffer, &out_uSize, in_bWait);
    }

    AKRESULT ReleaseBuffer() override
    {
        return _functions.ReleaseBuffer(_instance);
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_IAkAutoStream_FunctionTable _functions;
};

WWISEC_AK_IAkAutoStream* WWISEC_AK_IAkAutoStream_CreateInstance(void* instance, const WWISEC_AK_IAkAutoStream_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_IAkAutoStream*>(AkNew(AkMemID_Integration, WWISEC_AK_IAkAutoStream_Wrapper)(instance, functionTable));
}

void WWISEC_AK_IAkAutoStream_DestroyInstance(WWISEC_AK_IAkAutoStream* instance)
{
    WWISEC_AK_IAkAutoStream_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_IAkAutoStream_Wrapper*>(instance);
    wrapper->~WWISEC_AK_IAkAutoStream_Wrapper();
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

void WWISEC_AK_IAkAutoStream_Destroy(WWISEC_AK_IAkAutoStream* instance)
{
    reinterpret_cast<AK::IAkAutoStream*>(instance)->Destroy();
}

void WWISEC_AK_IAkAutoStream_GetInfo(WWISEC_AK_IAkAutoStream* instance, WWISEC_AkStreamInfo* out_info)
{
    reinterpret_cast<AK::IAkAutoStream*>(instance)->GetInfo(*reinterpret_cast<AkStreamInfo*>(out_info));
}

void* WWISEC_AK_IAkAutoStream_GetFileDescriptor(WWISEC_AK_IAkAutoStream* instance)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->GetFileDescriptor();
}

void WWISEC_AK_IAkAutoStream_GetHeuristics(WWISEC_AK_IAkAutoStream* instance, WWISEC_AkAutoStmHeuristics* out_heuristics)
{
    reinterpret_cast<AK::IAkAutoStream*>(instance)->GetHeuristics(*reinterpret_cast<AkAutoStmHeuristics*>(out_heuristics));
}

AKRESULT WWISEC_AK_IAkAutoStream_SetHeuristics(WWISEC_AK_IAkAutoStream* instance, const WWISEC_AkAutoStmHeuristics* in_heuristics)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->SetHeuristics(*reinterpret_cast<const AkAutoStmHeuristics*>(in_heuristics));
}

AKRESULT WWISEC_AK_IAkAutoStream_SetMinimalBufferSize(WWISEC_AK_IAkAutoStream* instance, AkUInt32 in_uMinBufferSize)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->SetMinimalBufferSize(in_uMinBufferSize);
}

AKRESULT WWISEC_AK_IAkAutoStream_SetStreamName(WWISEC_AK_IAkAutoStream* instance, const AkOSChar* in_pszStreamName)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->SetStreamName(in_pszStreamName);
}

AkUInt32 WWISEC_AK_IAkAutoStream_GetBlockSize(WWISEC_AK_IAkAutoStream* instance)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->GetBlockSize();
}

AKRESULT WWISEC_AK_IAkAutoStream_QueryBufferingStatus(WWISEC_AK_IAkAutoStream* instance, AkUInt32* out_uNumBytesAvailable)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->QueryBufferingStatus(*out_uNumBytesAvailable);
}

AkUInt32 WWISEC_AK_IAkAutoStream_GetNominalBuffering(WWISEC_AK_IAkAutoStream* instance)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->GetNominalBuffering();
}

AKRESULT WWISEC_AK_IAkAutoStream_Start(WWISEC_AK_IAkAutoStream* instance)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->Start();
}

AKRESULT WWISEC_AK_IAkAutoStream_Stop(WWISEC_AK_IAkAutoStream* instance)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->Stop();
}

AkUInt64 WWISEC_AK_IAkAutoStream_GetPosition(WWISEC_AK_IAkAutoStream* instance, bool* out_pbEndOfStream)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->GetPosition(out_pbEndOfStream);
}

AKRESULT WWISEC_AK_IAkAutoStream_SetPosition(WWISEC_AK_IAkAutoStream* instance, AkInt64 in_iMoveOffset, WWISEC_AkMoveMethod in_eMoveMethod)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->SetPosition(in_iMoveOffset, static_cast<AkMoveMethod>(in_eMoveMethod));
}

AKRESULT WWISEC_AK_IAkAutoStream_GetBuffer(WWISEC_AK_IAkAutoStream* instance, void** out_pBuffer, AkUInt32* out_uSize, bool in_bWait)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->GetBuffer(*out_pBuffer, *out_uSize, in_bWait);
}

AKRESULT WWISEC_AK_IAkAutoStream_ReleaseBuffer(WWISEC_AK_IAkAutoStream* instance)
{
    return reinterpret_cast<AK::IAkAutoStream*>(instance)->ReleaseBuffer();
}

class WWISEC_AK_IAkStreamMgr_Wrapper : public AK::IAkStreamMgr
{
  public:
    WWISEC_AK_IAkStreamMgr_Wrapper(void* instance, const WWISEC_AK_IAkStreamMgr_FunctionTable* functionTable)
        : _instance(instance), _functions(*functionTable)
    {
        m_pStreamMgr = this;
    }

    ~WWISEC_AK_IAkStreamMgr_Wrapper()
    {
        _functions.Destructor(_instance);
    }

    void Destroy() override
    {
        _functions.Destroy(_instance);
    }

    AK::IAkStreamMgrProfile* GetStreamMgrProfile() override
    {
        return reinterpret_cast<AK::IAkStreamMgrProfile*>(_functions.GetStreamMgrProfile(_instance));
    }

    AKRESULT CreateStd(const AkFileOpenData& in_FileOpen, AK::IAkStdStream*& out_pStream, bool in_bSyncOpen) override
    {
        return _functions.CreateStd(_instance, reinterpret_cast<const WWISEC_AkFileOpenData*>(&in_FileOpen), reinterpret_cast<WWISEC_AK_IAkStdStream**>(&out_pStream), in_bSyncOpen);
    }

    AKRESULT CreateAuto(const AkFileOpenData& in_FileOpen, const AkAutoStmHeuristics& in_heuristics, AkAutoStmBufSettings* in_pBufferSettings, AK::IAkAutoStream*& out_pStream, bool in_bSyncOpen, bool in_bSyncCache) override
    {
        return _functions.CreateAuto_AkFileOpenData(_instance, reinterpret_cast<const WWISEC_AkFileOpenData*>(&in_FileOpen), reinterpret_cast<const WWISEC_AkAutoStmHeuristics*>(&in_heuristics), reinterpret_cast<WWISEC_AkAutoStmBufSettings*>(in_pBufferSettings), reinterpret_cast<WWISEC_AK_IAkAutoStream**>(&out_pStream), in_bSyncOpen, in_bSyncCache);
    }

    AKRESULT CreateAuto(void* in_pBuffer, AkUInt64 in_uSize, const AkAutoStmHeuristics& in_heuristics, AK::IAkAutoStream*& out_pStream) override
    {
        return _functions.CreateAuto_Memory(_instance, in_pBuffer, in_uSize, reinterpret_cast<const WWISEC_AkAutoStmHeuristics*>(&in_heuristics), reinterpret_cast<WWISEC_AK_IAkAutoStream**>(&out_pStream));
    }

    AKRESULT PinFileInCache(AkFileID in_fileID, AkFileSystemFlags* in_pFSFlags, AkPriority in_uPriority) override
    {
        return _functions.PinFileInCache(_instance, in_fileID, reinterpret_cast<WWISEC_AkFileSystemFlags*>(in_pFSFlags), static_cast<AkPriority>(in_uPriority));
    }

    AKRESULT UnpinFileInCache(AkFileID in_fileID, AkPriority in_uPriority) override
    {
        return _functions.UnpinFileInCache(_instance, in_fileID, static_cast<AkPriority>(in_uPriority));
    }

    AKRESULT UpdateCachingPriority(AkFileID in_fileID, AkPriority in_uPriority, AkPriority in_uOldPriority) override
    {
        return _functions.UpdateCachingPriority(_instance, in_fileID, static_cast<AkPriority>(in_uPriority), static_cast<AkPriority>(in_uOldPriority));
    }

    AKRESULT GetBufferStatusForPinnedFile(AkFileID in_fileID, AkReal32& out_fPercentBuffered, bool& out_bCacheFull) override
    {
        return _functions.GetBufferStatusForPinnedFile(_instance, in_fileID, &out_fPercentBuffered, &out_bCacheFull);
    }

    AKRESULT RelocateMemoryStream(AK::IAkAutoStream* in_pStream, AkUInt8* in_pNewStart) override
    {
        return _functions.RelocateMemoryStream(_instance, reinterpret_cast<WWISEC_AK_IAkAutoStream*>(in_pStream), in_pNewStart);
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_IAkStreamMgr_FunctionTable _functions;
};

WWISEC_AK_IAkStreamMgr* WWISEC_AK_IAkStreamMgr_CreateInstance(void* instance, const WWISEC_AK_IAkStreamMgr_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_IAkStreamMgr*>(AkNew(AkMemID_Integration, WWISEC_AK_IAkStreamMgr_Wrapper)(instance, functionTable));
}

void WWISEC_AK_IAkStreamMgr_DestroyInstance(WWISEC_AK_IAkStreamMgr* instance)
{
    WWISEC_AK_IAkStreamMgr_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_IAkStreamMgr_Wrapper*>(instance);
    wrapper->~WWISEC_AK_IAkStreamMgr_Wrapper();
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

void WWISEC_AK_IAkStreamMgr_Destroy(WWISEC_AK_IAkStreamMgr* instance)
{
    reinterpret_cast<AK::IAkStreamMgr*>(instance)->Destroy();
}

WWISEC_AK_IAkStreamMgrProfile* WWISEC_AK_IAkStreamMgr_GetStreamMgrProfile(WWISEC_AK_IAkStreamMgr* instance)
{
    return reinterpret_cast<WWISEC_AK_IAkStreamMgrProfile*>(reinterpret_cast<AK::IAkStreamMgr*>(instance)->GetStreamMgrProfile());
}

AKRESULT WWISEC_AK_IAkStreamMgr_CreateStd(WWISEC_AK_IAkStreamMgr* instance, const WWISEC_AkFileOpenData* in_FileOpen, WWISEC_AK_IAkStdStream** out_pStream, bool in_bSyncOpen)
{
    return reinterpret_cast<AK::IAkStreamMgr*>(instance)->CreateStd(*reinterpret_cast<const AkFileOpenData*>(in_FileOpen), *reinterpret_cast<AK::IAkStdStream**>(out_pStream), in_bSyncOpen);
}

AKRESULT WWISEC_AK_IAkStreamMgr_CreateAuto_AkFileOpenData(WWISEC_AK_IAkStreamMgr* instance, const WWISEC_AkFileOpenData* in_FileOpen, const WWISEC_AkAutoStmHeuristics* in_heuristics, WWISEC_AkAutoStmBufSettings* in_pBufferSettings, WWISEC_AK_IAkAutoStream** out_pStream, bool in_bSyncOpen, bool in_bCaching)
{
    return reinterpret_cast<AK::IAkStreamMgr*>(instance)->CreateAuto(*reinterpret_cast<const AkFileOpenData*>(in_FileOpen), *reinterpret_cast<const AkAutoStmHeuristics*>(in_heuristics), reinterpret_cast<AkAutoStmBufSettings*>(in_pBufferSettings), *reinterpret_cast<AK::IAkAutoStream**>(out_pStream), in_bSyncOpen, in_bCaching);
}

AKRESULT WWISEC_AK_IAkStreamMgr_CreateAuto_Memory(WWISEC_AK_IAkStreamMgr* instance, void* in_pBuffer, AkUInt64 in_uSize, const WWISEC_AkAutoStmHeuristics* in_heuristics, WWISEC_AK_IAkAutoStream** out_pStream)
{
    return reinterpret_cast<AK::IAkStreamMgr*>(instance)->CreateAuto(in_pBuffer, in_uSize, *reinterpret_cast<const AkAutoStmHeuristics*>(in_heuristics), *reinterpret_cast<AK::IAkAutoStream**>(out_pStream));
}

AKRESULT WWISEC_AK_IAkStreamMgr_PinFileInCache(WWISEC_AK_IAkStreamMgr* instance, AkFileID in_fileID, WWISEC_AkFileSystemFlags* in_pFSFlags, AkPriority in_uPriority)
{
    return reinterpret_cast<AK::IAkStreamMgr*>(instance)->PinFileInCache(in_fileID, reinterpret_cast<AkFileSystemFlags*>(in_pFSFlags), static_cast<AkPriority>(in_uPriority));
}

AKRESULT WWISEC_AK_IAkStreamMgr_UnpinFileInCache(WWISEC_AK_IAkStreamMgr* instance, AkFileID in_fileID, AkPriority in_uPriority)
{
    return reinterpret_cast<AK::IAkStreamMgr*>(instance)->UnpinFileInCache(in_fileID, static_cast<AkPriority>(in_uPriority));
}

AKRESULT WWISEC_AK_IAkStreamMgr_UpdateCachingPriority(WWISEC_AK_IAkStreamMgr* instance, AkFileID in_fileID, AkPriority in_uPriority, AkPriority in_uOldPriority)
{
    return reinterpret_cast<AK::IAkStreamMgr*>(instance)->UpdateCachingPriority(in_fileID, static_cast<AkPriority>(in_uPriority), static_cast<AkPriority>(in_uOldPriority));
}

AKRESULT WWISEC_AK_IAkStreamMgr_GetBufferStatusForPinnedFile(WWISEC_AK_IAkStreamMgr* instance, AkFileID in_fileID, AkReal32* out_fPercentBuffered, bool* out_bCacheFull)
{
    return reinterpret_cast<AK::IAkStreamMgr*>(instance)->GetBufferStatusForPinnedFile(in_fileID, *out_fPercentBuffered, *out_bCacheFull);
}

AKRESULT WWISEC_AK_IAkStreamMgr_RelocateMemoryStream(WWISEC_AK_IAkStreamMgr* instance, WWISEC_AK_IAkAutoStream* in_pStream, AkUInt8* in_pNewStart)
{
    return reinterpret_cast<AK::IAkStreamMgr*>(instance)->RelocateMemoryStream(reinterpret_cast<AK::IAkAutoStream*>(in_pStream), in_pNewStart);
}

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
static_assert(sizeof(WWISEC_AkAsyncFileOpenData) == sizeof(AkAsyncFileOpenData));
static_assert(sizeof(WWISEC_AkIoHeuristics) == sizeof(WWISEC_AkIoHeuristics));
static_assert(sizeof(WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem) == sizeof(AK::StreamMgr::IAkLowLevelIOHook::BatchIoTransferItem));

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

    AKRESULT Close(AkFileDesc* in_fileDesc) override
    {
        return _functions.Close(_instance, reinterpret_cast<WWISEC_AkFileDesc*>(in_fileDesc));
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

    void BatchOpen(AkUInt32 in_uNumFiles, AkAsyncFileOpenData** in_ppItems) override
    {
        _functions.BatchOpen(_instance, in_uNumFiles, reinterpret_cast<WWISEC_AkAsyncFileOpenData**>(in_ppItems));
    }

    void BatchRead(AkUInt32 in_uNumTransfers, BatchIoTransferItem* in_pTransferItems) override
    {
        _functions.BatchRead(_instance, in_uNumTransfers, reinterpret_cast<WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem*>(in_pTransferItems));
    }

    void BatchWrite(AkUInt32 in_uNumTransfers, BatchIoTransferItem* in_pTransferItems) override
    {
        _functions.BatchWrite(_instance, in_uNumTransfers, reinterpret_cast<WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem*>(in_pTransferItems));
    }

    AKRESULT OutputSearchedPaths(AKRESULT in_result, const AkFileOpenData& in_FileOpen, AkOSChar* out_searchedPath, AkInt32 in_pathSize) override
    {
        return _functions.OutputSearchedPaths(_instance, in_result, reinterpret_cast<const WWISEC_AkFileOpenData*>(&in_FileOpen), out_searchedPath, in_pathSize);
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

AKRESULT WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Close(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, WWISEC_AkFileDesc* in_fileDesc)
{
    return reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(instance)->Close(reinterpret_cast<AkFileDesc*>(in_fileDesc));
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

void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchOpen(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, AkUInt32 in_uNumFiles, WWISEC_AkAsyncFileOpenData** in_ppItems)
{
    reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(instance)->BatchOpen(in_uNumFiles, reinterpret_cast<AkAsyncFileOpenData**>(in_ppItems));
}

void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchRead(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem* in_pTransferItems)
{
    reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(instance)->BatchRead(in_uNumTransfers, reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook::BatchIoTransferItem*>(in_pTransferItems));
}

void WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchWrite(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, AkUInt32 in_uNumTransfers, WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem* in_pTransferItems)
{
    reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(instance)->BatchWrite(in_uNumTransfers, reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook::BatchIoTransferItem*>(in_pTransferItems));
}

AKRESULT WWISEC_AK_StreamMgr_IAkLowLevelIOHook_OutputSearchedPaths(WWISEC_AK_StreamMgr_IAkLowLevelIOHook* instance, AKRESULT in_result, const WWISEC_AkFileOpenData* in_FileOpen, AkOSChar* out_searchedPath, AkInt32 in_pathSize)
{
    return reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(instance)->OutputSearchedPaths(in_result, *reinterpret_cast<const AkFileOpenData*>(in_FileOpen), out_searchedPath, in_pathSize);
}

class WWISEC_AK_StreamMgr_IAkFileLocationResolver_Wrapper : public AK::StreamMgr::IAkFileLocationResolver
{
  public:
    WWISEC_AK_StreamMgr_IAkFileLocationResolver_Wrapper(void* instance, const WWISEC_AK_StreamMgr_IAkFileLocationResolver_FunctionTable* functionTable)
        : _instance(instance), _functions(*functionTable)
    {
    }

    ~WWISEC_AK_StreamMgr_IAkFileLocationResolver_Wrapper()
    {
        _functions.Destructor(_instance);
    }

    AKRESULT GetNextPreferredDevice(AkAsyncFileOpenData& in_FileOpen, AkDeviceID& io_idDevice) override
    {
        return _functions.GetNextPreferredDevice(_instance, reinterpret_cast<WWISEC_AkAsyncFileOpenData*>(&in_FileOpen), reinterpret_cast<AkDeviceID*>(&io_idDevice));
    }

  private:
    void* _instance = nullptr;
    WWISEC_AK_StreamMgr_IAkFileLocationResolver_FunctionTable _functions;
};

WWISEC_AK_StreamMgr_IAkFileLocationResolver* WWISEC_AK_StreamMgr_IAkFileLocationResolver_CreateInstance(void* instance, const WWISEC_AK_StreamMgr_IAkFileLocationResolver_FunctionTable* functionTable)
{
    return reinterpret_cast<WWISEC_AK_StreamMgr_IAkFileLocationResolver*>(AkNew(AkMemID_Integration, WWISEC_AK_StreamMgr_IAkFileLocationResolver_Wrapper)(instance, functionTable));
}
void WWISEC_AK_StreamMgr_IAkFileLocationResolver_DestroyInstance(WWISEC_AK_StreamMgr_IAkFileLocationResolver* instance)
{
    WWISEC_AK_StreamMgr_IAkFileLocationResolver_Wrapper* wrapper = reinterpret_cast<WWISEC_AK_StreamMgr_IAkFileLocationResolver_Wrapper*>(instance);
    wrapper->~WWISEC_AK_StreamMgr_IAkFileLocationResolver_Wrapper();
    AK::MemoryMgr::Free(AkMemID_Integration, wrapper);
}

AKRESULT WWISEC_AK_StreamMgr_IAkFileLocationResolver_GetNextPreferredDevice(WWISEC_AK_StreamMgr_IAkFileLocationResolver* instance, WWISEC_AkAsyncFileOpenData* in_FileOpen, AkDeviceID* io_idDevice)
{
    return reinterpret_cast<AK::StreamMgr::IAkFileLocationResolver*>(instance)->GetNextPreferredDevice(*reinterpret_cast<AkAsyncFileOpenData*>(in_FileOpen), *reinterpret_cast<AkDeviceID*>(io_idDevice));
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

AKRESULT WWISEC_AK_StreamMgr_CreateDevice(const WWISEC_AkDeviceSettings* in_settings, void* in_pLowLevelHook, AkDeviceID* out_idDevice)
{
    return AK::StreamMgr::CreateDevice(*reinterpret_cast<const AkDeviceSettings*>(in_settings), reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(in_pLowLevelHook), *reinterpret_cast<AkDeviceID*>(out_idDevice));
}

AKRESULT WWISEC_AK_StreamMgr_DestroyDevice(AkDeviceID in_deviceID)
{
    return AK::StreamMgr::DestroyDevice(static_cast<AkDeviceID>(in_deviceID));
}

AKRESULT WWISEC_AK_StreamMgr_PerformIO()
{
    return AK::StreamMgr::PerformIO();
}

void WWISEC_AK_StreamMgr_GetDefaultDeviceSettings(WWISEC_AkDeviceSettings* out_settings)
{
    AK::StreamMgr::GetDefaultDeviceSettings(*reinterpret_cast<AkDeviceSettings*>(out_settings));
}

AKRESULT WWISEC_AK_StreamMgr_SetCurrentLanguage(const AkOSChar* in_pszLanguageName)
{
    return AKRESULT(AK::StreamMgr::SetCurrentLanguage(in_pszLanguageName));
}

const AkOSChar* WWISEC_AK_StreamMgr_GetCurrentLanguage()
{
    return AK::StreamMgr::GetCurrentLanguage();
}

AKRESULT WWISEC_AK_StreamMgr_AddLanguageChangeObserver(WWISEC_AK_StreamMgr_AkLanguageChangeHandler in_handler, void* in_pCookie)
{
    return AK::StreamMgr::AddLanguageChangeObserver(reinterpret_cast<AK::StreamMgr::AkLanguageChangeHandler>(in_handler), in_pCookie);
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

AKRESULT WWISEC_AK_MusicEngine_Init(WWISEC_AkMusicSettings* in_pSettings)
{
    return AK::MusicEngine::Init(reinterpret_cast<AkMusicSettings*>(in_pSettings));
}

void WWISEC_AK_MusicEngine_GetDefaultInitSettings(WWISEC_AkMusicSettings* out_settings)
{
    AK::MusicEngine::GetDefaultInitSettings(*reinterpret_cast<AkMusicSettings*>(out_settings));
}

void WWISEC_AK_MusicEngine_Term()
{
    AK::MusicEngine::Term();
}

AKRESULT WWISEC_AK_MusicEngine_GetPlayingSegmentInfo(AkPlayingID in_PlayingID, WWISEC_AkSegmentInfo* out_segmentInfo, bool in_bExtrapolate)
{
    return AK::MusicEngine::GetPlayingSegmentInfo(in_PlayingID, *reinterpret_cast<AkSegmentInfo*>(out_segmentInfo), in_bExtrapolate);
}
// END AkMusicEngine

// BEGIN AkCommunication
#if defined(WWISEC_USE_COMMUNICATION)
#include <AK/Comm/AkCommunication.h>

static_assert(sizeof(WWISEC_AkCommSettings_Ports) == sizeof(AkCommSettings::Ports));
static_assert(sizeof(WWISEC_AkCommSettings) == sizeof(AkCommSettings));
static_assert(WWISEC_AK_COMM_SETTINGS_MAX_STRING_SIZE == AK_COMM_SETTINGS_MAX_STRING_SIZE);
static_assert(WWISEC_AK_COMM_SETTINGS_MAX_URL_SIZE == AK_COMM_SETTINGS_MAX_URL_SIZE);

AKRESULT WWISEC_AK_Comm_Init(const WWISEC_AkCommSettings* in_settings)
{
    return AK::Comm::Init(*reinterpret_cast<const AkCommSettings*>(in_settings));
}

void WWISEC_AK_Comm_GetDefaultInitSettings(WWISEC_AkCommSettings* out_settings)
{
    AK::Comm::GetDefaultInitSettings(*reinterpret_cast<AkCommSettings*>(out_settings));
}

void WWISEC_AK_Comm_Term()
{
    AK::Comm::Term();
}

AKRESULT WWISEC_AK_Comm_Reset()
{
    return AK::Comm::Reset();
}

const WWISEC_AkCommSettings* WWISEC_AK_Comm_GetCurrentSettings()
{
    return reinterpret_cast<const WWISEC_AkCommSettings*>(&AK::Comm::GetCurrentSettings());
}

AkUInt16 WWISEC_AK_Comm_GetCommandPort()
{
    return AK::Comm::GetCommandPort();
}
#endif
// END AkCommunication

// BEGIN AkDynamicDialogue
AkUniqueID WWISEC_AK_SoundEngine_DynamicDialogue_ResolveDialogueEvent_ID(AkUniqueID in_eventID, AkArgumentValueID* in_aArgumentValues, AkUInt32 in_uNumArguments, AkPlayingID in_idSequence, WWISEC_AkCandidateCallbackFunc in_candidateCallbackFunc, void* in_pCookie)
{
    return static_cast<AkUniqueID>(AK::SoundEngine::DynamicDialogue::ResolveDialogueEvent(in_eventID, reinterpret_cast<AkArgumentValueID*>(in_aArgumentValues), in_uNumArguments, in_idSequence, reinterpret_cast<AkCandidateCallbackFunc>(in_candidateCallbackFunc), in_pCookie));
}

AkUniqueID WWISEC_AK_SoundEngine_DynamicDialogue_ResolveDialogueEvent_String(const char* in_pszEventName, const char** in_aArgumentValueNames, AkUInt32 in_uNumArguments, AkPlayingID in_idSequence, WWISEC_AkCandidateCallbackFunc in_candidateCallbackFunc, void* in_pCookie)
{
    return static_cast<AkUniqueID>(AK::SoundEngine::DynamicDialogue::ResolveDialogueEvent(in_pszEventName, in_aArgumentValueNames, in_uNumArguments, in_idSequence, reinterpret_cast<AkCandidateCallbackFunc>(in_candidateCallbackFunc), in_pCookie));
}

AKRESULT WWISEC_AK_SoundEngine_DynamicDialogue_GetDialogueEventCustomPropertyValue(AkUniqueID in_eventID, AkUInt32 in_uPropID, AkInt32* out_iValue)
{
    return AK::SoundEngine::DynamicDialogue::GetDialogueEventCustomPropertyValue(in_eventID, in_uPropID, *out_iValue);
}
// END AkDynamicDialogue

// BEGIN AkDynamicSequence
static_assert(sizeof(WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem) == sizeof(AK::SoundEngine::DynamicSequence::PlaylistItem));

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem_SetExternalSources(WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* self, AkUInt32 in_nExternalSrc, WWISEC_AkExternalSourceInfo* in_pExternalSrc)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::PlaylistItem*>(self)->SetExternalSources(in_nExternalSrc, reinterpret_cast<AkExternalSourceInfo*>(in_pExternalSrc));
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Enqueue(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUniqueID in_audioNodeID, AkTimeMs in_msDelay, void* in_pCustomInfo, AkUInt32 in_cExternals, WWISEC_AkExternalSourceInfo* in_pExternalSources)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Enqueue(in_audioNodeID, in_msDelay, in_pCustomInfo, in_cExternals, reinterpret_cast<AkExternalSourceInfo*>(in_pExternalSources));
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

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Reserve(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_ulReserve)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Reserve(in_ulReserve);
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_ReserveExtra(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, AkUInt32 in_ulReserve)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->ReserveExtra(in_ulReserve);
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

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Remove(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Remove(*reinterpret_cast<const AK::SoundEngine::DynamicSequence::PlaylistItem*>(in_Item));
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveSwap(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem* in_Item)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->RemoveSwap(*reinterpret_cast<const AK::SoundEngine::DynamicSequence::PlaylistItem*>(in_Item));
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

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Copy(WWISEC_AK_SoundEngine_DynamicSequence_Playlist* self, const WWISEC_AK_SoundEngine_DynamicSequence_Playlist* in_rSource)
{
    return reinterpret_cast<AK::SoundEngine::DynamicSequence::Playlist*>(self)->Copy(*reinterpret_cast<const AK::SoundEngine::DynamicSequence::Playlist*>(in_rSource));
}

AkPlayingID WWISEC_AK_SoundEngine_DynamicSequence_Open(AkGameObjectID in_gameObjectID, AkUInt32 in_uFlags, WWISEC_AkCallbackFunc in_pfnCallback, void* in_pCookie, enum AkDynamicSequenceType in_eDynamicSequenceType)
{
    return AK::SoundEngine::DynamicSequence::Open(in_gameObjectID, in_uFlags, reinterpret_cast<AkCallbackFunc>(in_pfnCallback), in_pCookie, in_eDynamicSequenceType);
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Close(AkPlayingID in_playingID)
{
    return AK::SoundEngine::DynamicSequence::Close(in_playingID);
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Play(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve)
{
    return AK::SoundEngine::DynamicSequence::Play(in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve));
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Pause(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve)
{
    return AK::SoundEngine::DynamicSequence::Pause(in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve));
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Resume(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve)
{
    return AK::SoundEngine::DynamicSequence::Resume(in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve));
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Stop(AkPlayingID in_playingID, AkTimeMs in_uTransitionDuration, enum AkCurveInterpolation in_eFadeCurve)
{
    return AK::SoundEngine::DynamicSequence::Stop(in_playingID, in_uTransitionDuration, static_cast<AkCurveInterpolation>(in_eFadeCurve));
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Break(AkPlayingID in_playingID)
{
    return AK::SoundEngine::DynamicSequence::Break(in_playingID);
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Seek_Time(AkPlayingID in_playingID, AkTimeMs in_iPosition, bool in_bSeekToNearestMarker)
{
    return AK::SoundEngine::DynamicSequence::Seek(in_playingID, in_iPosition, in_bSeekToNearestMarker);
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_Seek_Percent(AkPlayingID in_playingID, AkReal32 in_fPercent, bool in_bSeekToNearestMarker)
{
    return AK::SoundEngine::DynamicSequence::Seek(in_playingID, in_fPercent, in_bSeekToNearestMarker);
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_GetPauseTimes(AkPlayingID in_playingID, AkUInt32* out_uTime, AkUInt32* out_uDuration)
{
    return AK::SoundEngine::DynamicSequence::GetPauseTimes(in_playingID, *out_uTime, *out_uDuration);
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_GetPlayingItem(AkPlayingID in_playingID, AkUniqueID* out_audioNodeID, void** out_pCustomInfo)
{
    return AK::SoundEngine::DynamicSequence::GetPlayingItem(in_playingID, *out_audioNodeID, *out_pCustomInfo);
}

WWISEC_AK_SoundEngine_DynamicSequence_Playlist* WWISEC_AK_SoundEngine_DynamicSequence_LockPlaylist(AkPlayingID in_playingID)
{
    return reinterpret_cast<WWISEC_AK_SoundEngine_DynamicSequence_Playlist*>(AK::SoundEngine::DynamicSequence::LockPlaylist(in_playingID));
}

AKRESULT WWISEC_AK_SoundEngine_DynamicSequence_UnlockPlaylist(AkPlayingID in_playingID)
{
    return AK::SoundEngine::DynamicSequence::UnlockPlaylist(in_playingID);
}
// END AkDynamicSequence

// BEGIN AkQueryParameters
static_assert(sizeof(WWISEC_AkPositioningInfo) == sizeof(AkPositioningInfo));
static_assert(sizeof(WWISEC_AkObjectInfo) == sizeof(AkObjectInfo));
static_assert(sizeof(WWISEC_AK_SoundEngine_Query_AkGameObjectsList) == sizeof(AK::SoundEngine::Query::AkGameObjectsList));
static_assert(sizeof(WWISEC_AK_SoundEngine_Query_GameObjDst) == sizeof(AK::SoundEngine::Query::GameObjDst));
static_assert(sizeof(WWISEC_AK_SoundEngine_Query_AkRadiusList) == sizeof(AK::SoundEngine::Query::AkRadiusList));

AKRESULT WWISEC_AK_SoundEngine_Query_GetPosition(AkGameObjectID in_GameObjectID, WWISEC_AkSoundPosition* out_rPosition)
{
    return AK::SoundEngine::Query::GetPosition(in_GameObjectID, *reinterpret_cast<AkSoundPosition*>(out_rPosition));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetListeners(AkGameObjectID in_GameObjectID, AkGameObjectID* out_ListenerObjectIDs, AkUInt32* oi_uNumListeners)
{
    return AK::SoundEngine::Query::GetListeners(in_GameObjectID, out_ListenerObjectIDs, *oi_uNumListeners);
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetListenerPosition(AkGameObjectID in_uListenerID, WWISEC_AkListenerPosition* out_rPosition)
{
    return AK::SoundEngine::Query::GetListenerPosition(in_uListenerID, *reinterpret_cast<AkListenerPosition*>(out_rPosition));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetListenerSpatialization(AkGameObjectID in_uListenerID, bool* out_rbSpatialized, WWISEC_AK_SpeakerVolumes_VectorPtr* out_pVolumeOffsets, WWISEC_AkChannelConfig* out_channelConfig)
{
    return AK::SoundEngine::Query::GetListenerSpatialization(in_uListenerID, *out_rbSpatialized, *out_pVolumeOffsets, *reinterpret_cast<AkChannelConfig*>(out_channelConfig));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetRTPCValue_ID(AkRtpcID in_rtpcID, AkGameObjectID in_gameObjectID, AkPlayingID in_playingID, AkRtpcValue* out_rValue, WWISEC_AK_SoundEngine_Query_RTPCValue_type* io_rValueType)
{
    return AK::SoundEngine::Query::GetRTPCValue(in_rtpcID, in_gameObjectID, in_playingID, *out_rValue, *reinterpret_cast<AK::SoundEngine::Query::RTPCValue_type*>(io_rValueType));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetRTPCValue_String(const char* in_pszRtpcName, AkGameObjectID in_gameObjectID, AkPlayingID in_playingID, AkRtpcValue* out_rValue, WWISEC_AK_SoundEngine_Query_RTPCValue_type* io_rValueType)
{
    return AK::SoundEngine::Query::GetRTPCValue(in_pszRtpcName, in_gameObjectID, in_playingID, *out_rValue, *reinterpret_cast<AK::SoundEngine::Query::RTPCValue_type*>(io_rValueType));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetSwitch_ID(AkSwitchGroupID in_switchGroup, AkGameObjectID in_gameObjectID, AkSwitchStateID* out_rSwitchState)
{
    return AK::SoundEngine::Query::GetSwitch(in_switchGroup, in_gameObjectID, *reinterpret_cast<AkSwitchStateID*>(out_rSwitchState));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetSwitch_String(const char* in_pstrSwitchGroupName, AkGameObjectID in_GameObj, AkSwitchStateID* out_rSwitchState)
{
    return AK::SoundEngine::Query::GetSwitch(in_pstrSwitchGroupName, in_GameObj, *reinterpret_cast<AkSwitchStateID*>(out_rSwitchState));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetState_ID(AkStateGroupID in_stateGroup, AkStateID* out_rState)
{
    return AK::SoundEngine::Query::GetState(in_stateGroup, *reinterpret_cast<AkStateGroupID*>(out_rState));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetState_String(const char* in_pstrStateGroupName, AkStateID* out_rState)
{
    return AK::SoundEngine::Query::GetState(in_pstrStateGroupName, *reinterpret_cast<AkStateGroupID*>(out_rState));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetGameObjectAuxSendValues(AkGameObjectID in_gameObjectID, WWISEC_AkAuxSendValue* out_paAuxSendValues, AkUInt32* io_ruNumSendValues)
{
    return AK::SoundEngine::Query::GetGameObjectAuxSendValues(in_gameObjectID, reinterpret_cast<AkAuxSendValue*>(out_paAuxSendValues), *io_ruNumSendValues);
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetGameObjectDryLevelValue(AkGameObjectID in_EmitterID, AkGameObjectID in_ListenerID, AkReal32* out_rfControlValue)
{
    return AK::SoundEngine::Query::GetGameObjectDryLevelValue(in_EmitterID, in_ListenerID, *out_rfControlValue);
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetObjectObstructionAndOcclusion(AkGameObjectID in_EmitterID, AkGameObjectID in_ListenerID, AkReal32* out_rfObstructionLevel, AkReal32* out_rfOcclusionLevel)
{
    return AK::SoundEngine::Query::GetObjectObstructionAndOcclusion(in_EmitterID, in_ListenerID, *out_rfObstructionLevel, *out_rfOcclusionLevel);
}

AKRESULT WWISEC_AK_SoundEngine_Query_QueryAudioObjectIDs_ID(AkUniqueID in_eventID, AkUInt32* io_ruNumItems, WWISEC_AkObjectInfo* out_aObjectInfos)
{
    return AK::SoundEngine::Query::QueryAudioObjectIDs(in_eventID, *io_ruNumItems, reinterpret_cast<AkObjectInfo*>(out_aObjectInfos));
}

AKRESULT WWISEC_AK_SoundEngine_Query_QueryAudioObjectIDs_String(const char* in_pszEventName, AkUInt32* io_ruNumItems, WWISEC_AkObjectInfo* out_aObjectInfos)
{
    return AK::SoundEngine::Query::QueryAudioObjectIDs(in_pszEventName, *io_ruNumItems, reinterpret_cast<AkObjectInfo*>(out_aObjectInfos));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetPositioningInfo(AkUniqueID in_ObjectID, WWISEC_AkPositioningInfo* out_rPositioningInfo)
{
    return AK::SoundEngine::Query::GetPositioningInfo(in_ObjectID, *reinterpret_cast<AkPositioningInfo*>(out_rPositioningInfo));
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetActiveGameObjects(WWISEC_AK_SoundEngine_Query_AkGameObjectsList* io_GameObjectList)
{
    return AK::SoundEngine::Query::GetActiveGameObjects(*reinterpret_cast<AK::SoundEngine::Query::AkGameObjectsList*>(io_GameObjectList));
}

bool WWISEC_AK_SoundEngine_Query_GetIsGameObjectActive(AkGameObjectID in_GameObjId)
{
    return AK::SoundEngine::Query::GetIsGameObjectActive(in_GameObjId);
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetMaxRadius_List(WWISEC_AK_SoundEngine_Query_AkRadiusList* io_RadiusList)
{
    return AK::SoundEngine::Query::GetMaxRadius(*reinterpret_cast<AK::SoundEngine::Query::AkRadiusList*>(io_RadiusList));
}

AkReal32 WWISEC_AK_SoundEngine_Query_GetMaxRadius_Single(AkGameObjectID in_GameObjId)
{
    return AK::SoundEngine::Query::GetMaxRadius(in_GameObjId);
}

AkUniqueID WWISEC_AK_SoundEngine_Query_GetEventIDFromPlayingID(AkPlayingID in_playingID)
{
    return AK::SoundEngine::Query::GetEventIDFromPlayingID(in_playingID);
}

AkGameObjectID WWISEC_AK_SoundEngine_Query_GetGameObjectFromPlayingID(AkPlayingID in_playingID)
{
    return AK::SoundEngine::Query::GetGameObjectFromPlayingID(in_playingID);
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetPlayingIDsFromGameObject(AkGameObjectID in_GameObjId, AkUInt32* io_ruNumIDs, AkPlayingID* out_aPlayingIDs)
{
    return AK::SoundEngine::Query::GetPlayingIDsFromGameObject(in_GameObjId, *io_ruNumIDs, out_aPlayingIDs);
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetCustomPropertyValue_Int(AkUniqueID in_ObjectID, AkUInt32 in_uPropID, AkInt32* out_iValue)
{
    return AK::SoundEngine::Query::GetCustomPropertyValue(in_ObjectID, in_uPropID, *out_iValue);
}

AKRESULT WWISEC_AK_SoundEngine_Query_GetCustomPropertyValue_Float(AkUniqueID in_ObjectID, AkUInt32 in_uPropID, AkReal32* out_fValue)
{
    return AK::SoundEngine::Query::GetCustomPropertyValue(in_ObjectID, in_uPropID, *out_fValue);
}
// END AkQueryParameters

// BEGIN IO Hooks
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

AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings)
{
    return reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->Init(*reinterpret_cast<const AkDeviceSettings*>(in_deviceSettings));
}

void WWISEC_AK_CAkDefaultIOHookDeferred_Term(void* in_ioHook)
{
    reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->Term();
}

AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->SetBasePath(in_pszBasePath);
}

AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->AddBasePath(in_pszBasePath);
}

void WWISEC_CAkDefaultIOHookDeferred_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering)
{
    reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->SetUseSubfoldering(bUseSubFoldering);
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

AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_Init(void* in_ioHook, const WWISEC_AkDeviceSettings* in_deviceSettings)
{
    return reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->Init(*reinterpret_cast<const AkDeviceSettings*>(in_deviceSettings));
}

void WWISEC_AK_CAkFilePackageLowLevelIODeferred_Term(void* in_ioHook)
{
    reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->Term();
}

AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_SetBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->SetBasePath(in_pszBasePath);
}

AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_AddBasePath(void* in_ioHook, const AkOSChar* in_pszBasePath)
{
    return reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->AddBasePath(in_pszBasePath);
}

void WWISEC_CAkFilePackageLowLevelIODeferred_SetUseSubfoldering(void* in_ioHook, bool bUseSubFoldering)
{
    reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->SetUseSubfoldering(bUseSubFoldering);
}

AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_LoadFilePackage(void* in_ioHook, const AkOSChar* in_pszFilePackageName, AkUInt32* out_uPackageID)
{
    return reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->LoadFilePackage(in_pszFilePackageName, *out_uPackageID);
}

AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadFilePackage(void* in_ioHook, AkUInt32 in_uPackageID)
{
    return reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->UnloadFilePackage(in_uPackageID);
}

AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadAllFilePackages(void* in_ioHook)
{
    return reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->UnloadAllFilePackages();
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

AKRESULT WWISEC_AK_JobWorkerMgr_InitWorkers(const WWISEC_AK_JobWorkerMgr_InitSettings* in_implInitSettings)
{
    return AK::JobWorkerMgr::InitWorkers(*reinterpret_cast<const AK::JobWorkerMgr::InitSettings*>(in_implInitSettings));
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
static_assert(WWISEC_AK_MAX_SOUND_PROPAGATION_WIDTH == AK_MAX_SOUND_PROPAGATION_WIDTH);
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

AKRESULT WWISEC_AK_SpatialAudio_Init(const WWISEC_AkSpatialAudioInitSettings* in_initSettings)
{
    return AK::SpatialAudio::Init(*reinterpret_cast<const AkSpatialAudioInitSettings*>(in_initSettings));
}

AKRESULT WWISEC_AK_SpatialAudio_RegisterListener(AkGameObjectID in_gameObjectID)
{
    return AK::SpatialAudio::RegisterListener(in_gameObjectID);
}

AKRESULT WWISEC_AK_SpatialAudio_UnregisterListener(AkGameObjectID in_gameObjectID)
{
    return AK::SpatialAudio::UnregisterListener(in_gameObjectID);
}

AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectRadius(AkGameObjectID in_gameObjectID, AkReal32 in_outerRadius, AkReal32 in_innerRadius)
{
    return AK::SpatialAudio::SetGameObjectRadius(in_gameObjectID, in_outerRadius, in_innerRadius);
}

AKRESULT WWISEC_AK_SpatialAudio_SetImageSource(AkImageSourceID in_srcID, const WWISEC_AkImageSourceSettings* in_info, const char* in_name, AkUniqueID in_AuxBusID, AkGameObjectID in_gameObjectID)
{
    return AK::SpatialAudio::SetImageSource(in_srcID, *reinterpret_cast<const AkImageSourceSettings*>(in_info), in_name, in_AuxBusID, in_gameObjectID);
}

AKRESULT WWISEC_AK_SpatialAudio_RemoveImageSource(AkImageSourceID in_srcID, AkUniqueID in_AuxBusID, AkGameObjectID in_gameObjectID)
{
    return AK::SpatialAudio::RemoveImageSource(in_srcID, in_AuxBusID, in_gameObjectID);
}

AKRESULT WWISEC_AK_SpatialAudio_ClearImageSources(AkUniqueID in_AuxBusID, AkGameObjectID in_gameObjectID)
{
    return AK::SpatialAudio::ClearImageSources(in_AuxBusID, in_gameObjectID);
}

AKRESULT WWISEC_AK_SpatialAudio_SetGeometry(WWISEC_AkGeometrySetID in_GeomSetID, const WWISEC_AkGeometryParams* in_params)
{
    return AK::SpatialAudio::SetGeometry(in_GeomSetID.id, *reinterpret_cast<const AkGeometryParams*>(in_params));
}

AKRESULT WWISEC_AK_SpatialAudio_RemoveGeometry(WWISEC_AkGeometrySetID in_SetID)
{
    return AK::SpatialAudio::RemoveGeometry(in_SetID.id);
}

AKRESULT WWISEC_AK_SpatialAudio_SetGeometryInstance(WWISEC_AkGeometryInstanceID in_GeometryInstanceID, const WWISEC_AkGeometryInstanceParams* in_params)
{
    return AK::SpatialAudio::SetGeometryInstance(in_GeometryInstanceID.id, *reinterpret_cast<const AkGeometryInstanceParams*>(in_params));
}

AKRESULT WWISEC_AK_SpatialAudio_RemoveGeometryInstance(WWISEC_AkGeometryInstanceID in_GeometryInstanceID)
{
    return AK::SpatialAudio::RemoveGeometryInstance(in_GeometryInstanceID.id);
}

AKRESULT WWISEC_AK_SpatialAudio_QueryReflectionPaths(AkGameObjectID in_gameObjectID, AkUInt32 in_positionIndex, WWISEC_AkVector64* out_listenerPos, WWISEC_AkVector64* out_emitterPos, WWISEC_AkReflectionPathInfo* out_aPaths, AkUInt32* io_uArraySize)
{
    return AK::SpatialAudio::QueryReflectionPaths(in_gameObjectID, in_positionIndex, *reinterpret_cast<AkVector64*>(out_listenerPos), *reinterpret_cast<AkVector64*>(out_emitterPos), reinterpret_cast<AkReflectionPathInfo*>(out_aPaths), *io_uArraySize);
}

AKRESULT WWISEC_AK_SpatialAudio_SetRoom(WWISEC_AkRoomID in_RoomID, const WWISEC_AkRoomParams* in_Params, const char* in_RoomName)
{
    return AK::SpatialAudio::SetRoom(in_RoomID.id, *reinterpret_cast<const AkRoomParams*>(in_Params), in_RoomName);
}

AKRESULT WWISEC_AK_SpatialAudio_RemoveRoom(WWISEC_AkRoomID in_RoomID)
{
    return AK::SpatialAudio::RemoveRoom(in_RoomID.id);
}

AKRESULT WWISEC_AK_SpatialAudio_SetPortal(WWISEC_AkPortalID in_PortalID, const WWISEC_AkPortalParams* in_Params, const char* in_PortalName)
{
    return AK::SpatialAudio::SetPortal(in_PortalID.id, *reinterpret_cast<const AkPortalParams*>(in_Params), in_PortalName);
}

AKRESULT WWISEC_AK_SpatialAudio_RemovePortal(WWISEC_AkPortalID in_PortalID)
{
    return AK::SpatialAudio::RemovePortal(in_PortalID.id);
}

AKRESULT WWISEC_AK_SpatialAudio_SetReverbZone(WWISEC_AkRoomID in_ReverbZone, WWISEC_AkRoomID in_ParentRoom, AkReal32 in_transitionRegionWidth)
{
    return AK::SpatialAudio::SetReverbZone(in_ReverbZone.id, in_ParentRoom.id, in_transitionRegionWidth);
}

AKRESULT WWISEC_AK_SpatialAudio_RemoveReverbZone(WWISEC_AkRoomID in_ReverbZone)
{
    return AK::SpatialAudio::RemoveReverbZone(in_ReverbZone.id);
}

AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectInRoom(AkGameObjectID in_gameObjectID, WWISEC_AkRoomID in_CurrentRoomID)
{
    return AK::SpatialAudio::SetGameObjectInRoom(in_gameObjectID, in_CurrentRoomID.id);
}

AKRESULT WWISEC_AK_SpatialAudio_UnsetGameObjectInRoom(AkGameObjectID in_gameObjectID)
{
    return AK::SpatialAudio::UnsetGameObjectInRoom(in_gameObjectID);
}

AKRESULT WWISEC_AK_SpatialAudio_SetReflectionsOrder(AkUInt32 in_uReflectionsOrder, bool in_bUpdatePaths)
{
    return AK::SpatialAudio::SetReflectionsOrder(in_uReflectionsOrder, in_bUpdatePaths);
}

AKRESULT WWISEC_AK_SpatialAudio_SetDiffractionOrder(AkUInt32 in_uDiffractionOrder, bool in_bUpdatePaths)
{
    return AK::SpatialAudio::SetDiffractionOrder(in_uDiffractionOrder, in_bUpdatePaths);
}

AKRESULT WWISEC_AK_SpatialAudio_SetMaxGlobalReflectionPaths(AkUInt32 in_uMaxGlobalReflectionPaths)
{
    return AK::SpatialAudio::SetMaxGlobalReflectionPaths(in_uMaxGlobalReflectionPaths);
}

AKRESULT WWISEC_AK_SpatialAudio_SetMaxDiffractionPaths(AkUInt32 in_uMaxDiffractionPaths, AkGameObjectID in_gameObjectID)
{
    return AK::SpatialAudio::SetMaxDiffractionPaths(in_uMaxDiffractionPaths, in_gameObjectID);
}

AKRESULT WWISEC_AK_SpatialAudio_SetMaxEmitterRoomAuxSends(AkUInt32 in_uMaxEmitterRoomAuxSends)
{
    return AK::SpatialAudio::SetMaxEmitterRoomAuxSends(in_uMaxEmitterRoomAuxSends);
}

AKRESULT WWISEC_AK_SpatialAudio_SetNumberOfPrimaryRays(AkUInt32 in_uNbPrimaryRays)
{
    return AK::SpatialAudio::SetNumberOfPrimaryRays(in_uNbPrimaryRays);
}

AKRESULT WWISEC_AK_SpatialAudio_SetLoadBalancingSpread(AkUInt32 in_uNbFrames)
{
    return AK::SpatialAudio::SetLoadBalancingSpread(in_uNbFrames);
}

AKRESULT WWISEC_AK_SpatialAudio_SetSmoothingConstant(AkReal32 in_fSmoothingConstantMs, AkGameObjectID in_gameObjectID)
{
    return AK::SpatialAudio::SetSmoothingConstant(in_fSmoothingConstantMs, in_gameObjectID);
}

AKRESULT WWISEC_AK_SpatialAudio_SetEarlyReflectionsAuxSend(AkGameObjectID in_gameObjectID, WWISEC_AkAuxBusID in_auxBusID)
{
    return AK::SpatialAudio::SetEarlyReflectionsAuxSend(in_gameObjectID, in_auxBusID);
}

AKRESULT WWISEC_AK_SpatialAudio_SetEarlyReflectionsVolume(AkGameObjectID in_gameObjectID, AkReal32 in_fSendVolume)
{
    return AK::SpatialAudio::SetEarlyReflectionsVolume(in_gameObjectID, in_fSendVolume);
}

AKRESULT WWISEC_AK_SpatialAudio_SetPortalObstructionAndOcclusion(WWISEC_AkPortalID in_PortalID, AkReal32 in_fObstruction, AkReal32 in_fOcclusion)
{
    return AK::SpatialAudio::SetPortalObstructionAndOcclusion(in_PortalID.id, in_fObstruction, in_fOcclusion);
}

AKRESULT WWISEC_AK_SpatialAudio_SetGameObjectToPortalObstruction(AkGameObjectID in_gameObjectID, WWISEC_AkPortalID in_PortalID, AkReal32 in_fObstruction)
{
    return AK::SpatialAudio::SetGameObjectToPortalObstruction(in_gameObjectID, in_PortalID.id, in_fObstruction);
}

AKRESULT WWISEC_AK_SpatialAudio_SetPortalToPortalObstruction(WWISEC_AkPortalID in_PortalID0, WWISEC_AkPortalID in_PortalID1, AkReal32 in_fObstruction)
{
    return AK::SpatialAudio::SetPortalToPortalObstruction(in_PortalID0.id, in_PortalID1.id, in_fObstruction);
}

AKRESULT WWISEC_AK_SpatialAudio_QueryWetDiffraction(WWISEC_AkPortalID in_portal, AkReal32* out_wetDiffraction)
{
    return AK::SpatialAudio::QueryWetDiffraction(in_portal.id, *out_wetDiffraction);
}

AKRESULT WWISEC_AK_SpatialAudio_QueryDiffractionPaths(AkGameObjectID in_gameObjectID, AkUInt32 in_positionIndex, WWISEC_AkVector64* out_listenerPos, WWISEC_AkVector64* out_emitterPos, WWISEC_AkDiffractionPathInfo* out_aPaths, AkUInt32* io_uArraySize)
{
    return AK::SpatialAudio::QueryDiffractionPaths(in_gameObjectID, in_positionIndex, *reinterpret_cast<AkVector64*>(out_listenerPos), *reinterpret_cast<AkVector64*>(out_emitterPos), reinterpret_cast<AkDiffractionPathInfo*>(out_aPaths), *io_uArraySize);
}

AKRESULT WWISEC_AK_SpatialAudio_SetTransmissionOperation(WWISEC_AkTransmissionOperation in_eOperation)
{
    return AK::SpatialAudio::SetTransmissionOperation(static_cast<AkTransmissionOperation>(in_eOperation));
}

AKRESULT WWISEC_AK_SpatialAudio_ResetStochasticEngine()
{
    return AK::SpatialAudio::ResetStochasticEngine();
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

AKRESULT WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateT60Decay(AkReal32 in_volumeCubicMeters, AkReal32 in_surfaceAreaSquaredMeters, AkReal32 in_environmentAverageAbsorption, AkReal32* out_decayEstimate)
{
    return AK::SpatialAudio::ReverbEstimation::EstimateT60Decay(in_volumeCubicMeters, in_surfaceAreaSquaredMeters, in_environmentAverageAbsorption, *out_decayEstimate);
}

AKRESULT WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateTimeToFirstReflection(WWISEC_AkVector in_environmentExtentMeters, AkReal32* out_timeToFirstReflectionMs, AkReal32 in_speedOfSound)
{
    AkVector convertedAkVector;
    convertedAkVector.X = in_environmentExtentMeters.X;
    convertedAkVector.Y = in_environmentExtentMeters.Y;
    convertedAkVector.Z = in_environmentExtentMeters.Z;

    return AK::SpatialAudio::ReverbEstimation::EstimateTimeToFirstReflection(convertedAkVector, *out_timeToFirstReflectionMs, in_speedOfSound);
}

AkReal32 WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateHFDamping(WWISEC_AkAcousticTexture* in_textures, float* in_surfaceAreas, int in_numTextures)
{
    return AK::SpatialAudio::ReverbEstimation::EstimateHFDamping(reinterpret_cast<AkAcousticTexture*>(in_textures), in_surfaceAreas, in_numTextures);
}
// END AkReverbEstimation
#endif

// BEGIN Platform-specific AkSoundEngine functions
#if defined(AK_WIN)
AkUInt32 WWISEC_AK_GetDeviceID(IMMDevice* in_pDevice)
{
    return AK::GetDeviceID(in_pDevice);
}

AkUInt32 WWISEC_AK_GetDeviceIDFromName(wchar_t* in_szToken)
{
    return AK::GetDeviceIDFromName(in_szToken);
}

const wchar_t* WWISEC_AK_GetWindowsDeviceName(AkInt32 index, AkUInt32* out_uDeviceID, enum AkAudioDeviceState uDeviceStateMask)
{
    return AK::GetWindowsDeviceName(index, *out_uDeviceID, static_cast<AkAudioDeviceState>(uDeviceStateMask));
}

AkUInt32 WWISEC_AK_GetWindowsDeviceCount(enum AkAudioDeviceState uDeviceStateMask)
{
    return AK::GetWindowsDeviceCount(static_cast<AkAudioDeviceState>(uDeviceStateMask));
}

bool WWISEC_AK_GetWindowsDevice(AkInt32 in_index, AkUInt32* out_uDeviceID, IMMDevice** out_ppDevice, enum AkAudioDeviceState uDeviceStateMask)
{
    return AK::GetWindowsDevice(in_index, *out_uDeviceID, out_ppDevice, static_cast<AkAudioDeviceState>(uDeviceStateMask));
}
#endif

#if defined(AK_ANDROID)
WWISEC_SLObjectItf WWISEC_AK_SoundEngine_GetWwiseOpenSLInterface()
{
    return reinterpret_cast<WWISEC_SLObjectItf>(AK::SoundEngine::GetWwiseOpenSLInterface());
}

AKRESULT WWISEC_AK_SoundEngine_GetFastPathSettings(WWISEC_AkInitSettings* in_settings, WWISEC_AkPlatformInitSettings* in_pfSettings)
{
    return AK::SoundEngine::GetFastPathSettings(*reinterpret_cast<AkInitSettings*>(in_settings), *reintepret_cast<AkPlatformInitSettings*>(in_pfSettings);
}
#endif

#if defined(AK_IOS)
static_assert(WWISEC_AKMOTION_RESIDENT_MODE == AKMOTION_RESIDENT_MODE);

void WWISEC_AK_SoundEngine_iOS_ChangeAudioSessionProperties(const WWISEC_AkAudioSessionProperties* in_properties)
{
    AK::SoundEngine::iOS::ChangeAudioSeessionProperties(*reinterpret_cast<const AkAudioSessionProperties*>(in_properties));
}
#endif

#if defined(AK_MAC)
static_assert(WWISEC_AKMOTION_RESIDENT_MODE == AKMOTION_RESIDENT_MODE);
#endif
// END Platform-specific AkSoundEngine functions
