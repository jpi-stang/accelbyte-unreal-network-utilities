// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using UnrealBuildTool;

public class AccelByteNetworkUtilities : ModuleRules
{
	public AccelByteNetworkUtilities(ReadOnlyTargetRules Target) : base(Target)
	{
		bAllowConfidentialPlatformDefines = true;
		PrivateDefinitions.Add("ACCELBYTE_NETWORK_UTILITIES_PACKAGE=1");
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		/*
		 * Use platform string because Platform_PS5 not available on Unreal installed from Epic Launcher
		 */
		String PlatformString = Target.Platform.ToString().ToUpper();

		if (PlatformString == "PS5")
		{
			bAllowConfidentialPlatformDefines = true;
		}
		
		/*
		 * LibJuice is library that handle the nat punch connection.
		 */
		if (PlatformString == "WIN64" || 
		    PlatformString == "XBOXONEGDK" ||
		    PlatformString == "XSX" ||
		    PlatformString == "PS4" ||
		    PlatformString == "PS5" ||
		    PlatformString == "SWITCH" ||
		    PlatformString == "LINUX")
		{
			PrivateDefinitions.Add("LIBJUICE");
		}

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"OnlineSubsystemUtils"
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"LibJuice",
				"CoreUObject",
				"Projects",
				"WebSockets",
				"NetCore",
				"Engine",
				"Sockets",
				"OnlineSubsystem",
				"PacketHandler",
				"Json",
				"JsonUtilities",
				"AccelByteUe4Sdk"
			}
		);
	}
}
