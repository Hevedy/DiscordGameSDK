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
#include <iostream>
#include <sstream>

DEFINE_LOG_CATEGORY_STATIC( LogDiscord, All, All )

static discord::Core* Core = nullptr;
static uint64_t AppValue;

bool UDiscordRpc::Initialize( int64 _ClientID, bool _DiscordRequired ) {
	discord::Result result = discord::Core::Create( _ClientID, _DiscordRequired ? DiscordCreateFlags_Default : DiscordCreateFlags_NoRequireDiscord, &Core );
	if ( result != discord::Result::Ok || Core == nullptr ) {
		UE_LOG( LogDiscord, Error, TEXT( "Failed to create Discord Core" ) );
		return false;
	}

	return true;
}

bool UDiscordRpc::UpdatePlayActivity( const FString& _State, const FString& _Details, const FString& _Image ) {
	if ( !Core ) {
		UE_LOG( LogDiscord, Warning, TEXT( "Discord Activity Core Fail" ) );
		return false;
	}

	discord::Activity activity{};
	activity.SetType( discord::ActivityType::Playing );
	activity.SetState( TCHAR_TO_ANSI( *_State ) );
	activity.SetDetails( TCHAR_TO_ANSI( *_Details ) );
	activity.GetAssets().SetLargeImage( TCHAR_TO_ANSI( *_Image ) );
	activity.SetInstance( true );
	Core->ActivityManager().UpdateActivity( activity, []( discord::Result result ) {
		if ( result != discord::Result::Ok ) {
			UE_LOG( LogDiscord, Warning, TEXT( "Discord Activity Fail" ) );
			return;
		}

		UE_LOG( LogDiscord, Log, TEXT( "Discord Activity Set" ) );
	} );

	return true;
}

bool UDiscordRpc::RunCallbacks() {
	if ( Core )
		return Core->RunCallbacks() == discord::Result::Ok;

	return false;
}

void UDiscordRpc::Shutdown() {
	if ( Core ) {
		UE_LOG( LogDiscord, Warning, TEXT( "Discord Shutdown" ) );
		Core->ActivityManager().ClearActivity( []( discord::Result ) {} );
		Core->~Core();
		Core = nullptr;
	}
}