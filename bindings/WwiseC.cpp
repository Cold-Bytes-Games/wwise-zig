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
static_assert(WWISEC_AK_COMM_DEFAULT_DISCOVERY_PORT == AK_COMM_DEFAULT_DISCOVERY_PORT);
// END AkTypes

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

WWISEC_AKRESULT WWISEC_AK_SoundEngine_AddOutput(WWISEC_AkOutputSettings* in_Settings, WWISEC_AkOutputDeviceID* out_pDeviceID, const WWISEC_AkGameObjectID* in_pListenerIDs, AkUInt32 in_uNumListeners)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::AddOutput(*reinterpret_cast<AkOutputSettings*>(in_Settings), reinterpret_cast<AkOutputDeviceID*>(out_pDeviceID), reinterpret_cast<const AkGameObjectID*>(in_pListenerIDs), in_uNumListeners));
}

void WWISEC_AK_SoundEngine_GetDefaultInitSettings(WWISEC_AkInitSettings* out_settings)
{
    AK::SoundEngine::GetDefaultInitSettings(*reinterpret_cast<AkInitSettings*>(out_settings));
}

void WWISEC_AK_SoundEngine_GetDefaultPlatformInitSettings(WWISEC_AkPlatformInitSettings* out_platformSettings)
{
    AK::SoundEngine::GetDefaultPlatformInitSettings(*reinterpret_cast<AkPlatformInitSettings*>(out_platformSettings));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_Init(WWISEC_AkInitSettings* in_pSettings, WWISEC_AkPlatformInitSettings* in_pPlatformSettings)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::Init(reinterpret_cast<AkInitSettings*>(in_pSettings), reinterpret_cast<AkPlatformInitSettings*>(in_pPlatformSettings)));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_RemoveOutput(WWISEC_AkOutputDeviceID in_idOutput)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::RemoveOutput(in_idOutput));
}

WWISEC_AKRESULT WWISEC_AK_SoundEngine_ReplaceOutput(WWISEC_AkOutputSettings* in_Settings, WWISEC_AkOutputDeviceID in_outputDeviceId, WWISEC_AkOutputDeviceID* out_pOutputDeviceId)
{
    return static_cast<WWISEC_AKRESULT>(AK::SoundEngine::ReplaceOutput(*reinterpret_cast<AkOutputSettings*>(in_Settings), in_outputDeviceId, reinterpret_cast<AkOutputDeviceID*>(out_pOutputDeviceId)));
}

void WWISEC_AK_SoundEngine_Term()
{
    AK::SoundEngine::Term();
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

WWISEC_AkDeviceID WWISEC_AK_StreamMgr_CreateDevice(WWISEC_AkDeviceSettings* in_settings, void* in_pLowLevelHook)
{
    return AK::StreamMgr::CreateDevice(*reinterpret_cast<AkDeviceSettings*>(in_settings), reinterpret_cast<AK::StreamMgr::IAkLowLevelIOHook*>(in_pLowLevelHook));
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

// BEGIN AkCommunication
#if defined(WWISEC_USE_COMMUNICATION)
#include <AK/Comm/AkCommunication.h>

static_assert(sizeof(WWISEC_AkCommSettings_Ports) == sizeof(AkCommSettings::Ports));
static_assert(sizeof(WWISEC_AkCommSettings) == sizeof(AkCommSettings));
static_assert(WWISEC_AK_COMM_SETTINGS_MAX_STRING_SIZE == AK_COMM_SETTINGS_MAX_STRING_SIZE);
static_assert(WWISEC_AK_COMM_SETTINGS_MAX_URL_SIZE == AK_COMM_SETTINGS_MAX_URL_SIZE);

WWISEC_AKRESULT WWISEC_AK_Comm_Init(WWISEC_AkCommSettings* in_settings)
{
    return static_cast<WWISEC_AKRESULT>(AK::Comm::Init(*reinterpret_cast<AkCommSettings*>(in_settings)));
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

WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookBlocking_Init(void* in_ioHook, WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkDefaultIOHookBlocking*>(in_ioHook)->Init(*reinterpret_cast<AkDeviceSettings*>(in_deviceSettings), in_bAsyncOpen));
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

WWISEC_AKRESULT WWISEC_AK_CAkDefaultIOHookDeferred_Init(void* in_ioHook, WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkDefaultIOHookDeferred*>(in_ioHook)->Init(*reinterpret_cast<AkDeviceSettings*>(in_deviceSettings), in_bAsyncOpen));
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

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Init(void* in_ioHook, WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIOBlocking*>(in_ioHook)->Init(*reinterpret_cast<AkDeviceSettings*>(in_deviceSettings), in_bAsyncOpen));
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

WWISEC_AKRESULT WWISEC_AK_CAkFilePackageLowLevelIODeferred_Init(void* in_ioHook, WWISEC_AkDeviceSettings* in_deviceSettings, bool in_bAsyncOpen)
{
    return static_cast<WWISEC_AKRESULT>(reinterpret_cast<CAkFilePackageLowLevelIODeferred*>(in_ioHook)->Init(*reinterpret_cast<AkDeviceSettings*>(in_deviceSettings), in_bAsyncOpen));
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