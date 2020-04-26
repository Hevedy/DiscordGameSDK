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

#include "DiscordBlueprint.h"
#include "discord.h"

DEFINE_LOG_CATEGORY(Discord)

#include <iostream>
#include <sstream>

static discord::Core* Core{};

static discord::ActivityManager* ActivityManager{};

static discord::User User;

static uint64_t AppValue;

struct DiscordState {
	discord::User user;

	std::unique_ptr<discord::Core> core;
};

void UDiscordRpc::Initialize( const FString& _ApplicationId, const FString& _State, const FString& _Details ) {
	std::string inStr = TCHAR_TO_UTF8( *_ApplicationId );
	uint64_t value;
	char* end;
	value = strtoull( inStr.c_str(), &end, 10 );
	AppValue = value;

	DiscordState state{};

	
	discord::Core* core{};
	auto result = discord::Core::Create( AppValue, DiscordCreateFlags_NoRequireDiscord, &core);
	Core = core;
	if ( !Core ) {
		UE_LOG( Discord, Log, TEXT( "Discord Failed at create core" ) );
	} else {
		UE_LOG( Discord, Log, TEXT( "Discord Created Core" ) );
	}

	UpdateActivity( _State, _Details );

}

void UDiscordRpc::UpdateActivity( const FString& _State, const FString& _Details ) {
	if ( !Core ) {
		return;
	}
	discord::Activity activity{};
	activity.SetApplicationId( AppValue );
	activity.SetState(TCHAR_TO_ANSI( *_State));
	activity.SetDetails(TCHAR_TO_ANSI( *_Details));
	activity.SetType( discord::ActivityType::Playing );

    Core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
		if ( result == discord::Result::Ok ) {
			UE_LOG( Discord, Log, TEXT( "Discord Activity Set" ) );
		} else {
			UE_LOG( Discord, Log, TEXT( "Discord Activity Fail" ) );
		}
    });
}

void UDiscordRpc::VirtualBeginPlay() {
	
}

void UDiscordRpc::VirtualTickObject() {
	if ( Core ) {
		Core->RunCallbacks();
	}
}

void UDiscordRpc::VirtualEndPlay() {
	
}

void UDiscordRpc::Shutdown() {
	if ( Core ) {
		Core->ActivityManager().ClearActivity( []( discord::Result ) {} );
		Core->~Core();
		Core = nullptr;
	}
}