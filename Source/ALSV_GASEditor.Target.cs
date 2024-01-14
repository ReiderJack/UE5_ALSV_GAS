

using UnrealBuildTool;
using System.Collections.Generic;

public class ALSV_GASEditorTarget : TargetRules
{
	public ALSV_GASEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ALSV_GAS" } );
	}
}
