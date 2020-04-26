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

using System.IO;
using UnrealBuildTool;

public class DiscordLibrary : ModuleRules
{
	public DiscordLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		PublicDefinitions.Add("DISCORD_DYNAMIC_LIB=1");
		
        string BaseDirectory = Path.GetFullPath( System.IO.Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "DiscordLibrary"));

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string lib = Path.Combine(BaseDirectory, "Win64");

            // Include headers
            PublicIncludePaths.Add( Path.Combine(BaseDirectory, "Include"));

            // Add the import library
            PublicLibraryPaths.Add(lib);
            PublicAdditionalLibraries.Add( Path.Combine(lib, "discord_game_sdk.dll.lib"));

            // Dynamic
            RuntimeDependencies.Add( Path.Combine(lib, "discord_game_sdk.dll"));
			//RuntimeDependencies.Add( Path.Combine(lib, "send-presence.exe"));
            PublicDelayLoadDLLs.Add("discord_game_sdk.dll");
			//RuntimeDependencies.Add(new RuntimeDependency( System.IO.Path.Combine(lib, "send-presence.exe")));
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            string lib = Path.Combine(BaseDirectory, "Linux");

            // Include headers
            PublicIncludePaths.Add( Path.Combine(BaseDirectory, "Include"));

            // Add the import library
            PublicLibraryPaths.Add(lib);
            PublicAdditionalLibraries.Add( System.IO.Path.Combine(lib, "discord_game_sdk.so"));
            RuntimeDependencies.Add( Path.Combine(lib, "discord_game_sdk.so"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            string lib = Path.Combine(BaseDirectory, "Mac");

            // Include headers
            PublicIncludePaths.Add( Path.Combine(BaseDirectory, "Include"));

            // Add the import library
            PublicLibraryPaths.Add(lib);
            PublicAdditionalLibraries.Add( Path.Combine(lib, "discord_game_sdk.dylib"));
            RuntimeDependencies.Add( Path.Combine(lib, "discord_game_sdk.dylib"));
        }
		
	}
}
