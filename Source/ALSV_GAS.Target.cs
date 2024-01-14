

using UnrealBuildTool;
using System.Collections.Generic;

public class ALSV_GASTarget : TargetRules
{
	public ALSV_GASTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ALSV_GAS" } );
	}
}
