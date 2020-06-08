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

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "DiscordBlueprint.generated.h"


UCLASS()
class HEVEDYDISCORD_API UDiscordRpc : public UBlueprintFunctionLibrary { //public UObject { //UObject
    GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Discord")
		static bool Initialize( int64 _ClientID, bool _DiscordRequired = false );
	
	UFUNCTION(BlueprintCallable, Category = "Discord")
		static bool UpdatePlayActivity( const FString& _State, const FString& _Details, const FString& _Image = "none" );
	
	UFUNCTION(BlueprintCallable, Category = "Discord")
		static bool RunCallbacks();
		
	UFUNCTION( BlueprintCallable, Category = "Discord" )
		static void Shutdown();
	
};