/*
===========================================================================
This code is part of the "Source Code" content in
Discord GameSDK Plugin by David Palacios (Hevedy) <https://github.com/Hevedy>
<https://github.com/Hevedy/DiscordGameSDK/tree/hevedy>

The MIT License (MIT)
Copyright (c) 2018-2020 David Palacios (Hevedy) <https://github.com/Hevedy>
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
===========================================================================
*/


#include "HevedyDiscord.h"
#include "CoreMinimal.h"
#include "HAL/PlatformProcess.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/MessageDialog.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FHevedyDiscordModule"

void FHevedyDiscordModule::StartupModule()
{
#if !PLATFORM_LINUX
#if defined(DISCORD_DYNAMIC_LIB)
    // Get the base directory of this plugin
    FString BaseDir = IPluginManager::Get().FindPlugin("HevedyDiscord")->GetBaseDir();
    const FString SDKDir = FPaths::Combine(*BaseDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("DiscordLibrary"));
#if PLATFORM_WINDOWS
    const FString LibName = TEXT("discord_game_sdk");
    const FString LibDir = FPaths::Combine(*SDKDir, TEXT("Win64"));
    if (!LoadDependency(LibDir, LibName, DiscordLibraryHandle)) {
        FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT(LOCTEXT_NAMESPACE, "Failed to load HevedyDiscord plugin. Plug-in will not be functional."));
        FreeDependency(DiscordLibraryHandle);
    }
#elif PLATFORM_MAC
    const FString LibName = TEXT("discord_game_sdk");
    const FString LibDir = FPaths::Combine(*SDKDir, TEXT("Mac"));
    if (!LoadDependency(LibDir, LibName, DiscordLibraryHandle)) {
        FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT(LOCTEXT_NAMESPACE, "Failed to load HevedyDiscord plugin. Plug-in will not be functional."));
        FreeDependency(DiscordLibraryHandle);
    }
#endif
#endif
#endif
}

void FHevedyDiscordModule::ShutdownModule()
{
    // Free the dll handle
#if !PLATFORM_LINUX
#if defined(DISCORD_DYNAMIC_LIB)
    FreeDependency(DiscordLibraryHandle);
#endif
#endif
}

bool FHevedyDiscordModule::LoadDependency(const FString& Dir, const FString& Name, void*& Handle)
{
    FString Lib = Name + TEXT(".") + FPlatformProcess::GetModuleExtension();
    FString Path = Dir.IsEmpty() ? *Lib : FPaths::Combine(*Dir, *Lib);

    Handle = FPlatformProcess::GetDllHandle(*Path);

    if (Handle == nullptr)
    {
        return false;
    }

    return true;
}

void FHevedyDiscordModule::FreeDependency(void*& Handle)
{
    if (Handle != nullptr)
    {
        FPlatformProcess::FreeDllHandle(Handle);
        Handle = nullptr;
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHevedyDiscordModule, HevedyDiscord)