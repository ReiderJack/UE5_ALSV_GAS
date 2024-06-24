#include "Abilities/Attributes/WeaponAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UWeaponAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, Ammo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, SpareAmmo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, Headshot, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, ClipSize, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, SpareAmmo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, MaxSpareAmmo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, RoundsPerMinute, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, Range, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, HipFireAccuracy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, AimedAccuracy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, MaxSpreadAngle, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, LastShotTime, COND_None, REPNOTIFY_Always);
}

void UWeaponAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetAmmoAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetClipSize());
	}
	else if (Attribute == GetSpareAmmoAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxSpareAmmo());
	}
}

void UWeaponAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetAmmoAttribute())
	{
		SetAmmo(FMath::Clamp<float>(GetAmmo(), 0.0f, GetClipSize()));
	}

	if (Data.EvaluatedData.Attribute == GetSpareAmmoAttribute())
	{
		SetSpareAmmo(FMath::Clamp<float>(GetSpareAmmo(), 0.0f, GetMaxSpareAmmo()));
	}
}


void UWeaponAttributeSet::OnRep_Ammo(const FGameplayAttributeData& OldAmmo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, Ammo, OldAmmo);
}

void UWeaponAttributeSet::OnRep_SpareAmmo(const FGameplayAttributeData& OldSpareAmmo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, SpareAmmo, OldSpareAmmo);
}

void UWeaponAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, Damage, OldDamage);
}

void UWeaponAttributeSet::OnRep_Headshot(const FGameplayAttributeData& OldHeadshot)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, Headshot, OldHeadshot);
}

void UWeaponAttributeSet::OnRep_ClipSize(const FGameplayAttributeData& OldClipSize)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, ClipSize, OldClipSize);	
}

void UWeaponAttributeSet::OnRep_MaxSpareAmmo(const FGameplayAttributeData& OldMaxSpareAmmo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, MaxSpareAmmo, OldMaxSpareAmmo);	
}

void UWeaponAttributeSet::OnRep_RoundsPerMinute(const FGameplayAttributeData& OldRoundsPerMinute)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, RoundsPerMinute, OldRoundsPerMinute);
}

void UWeaponAttributeSet::OnRep_Range(const FGameplayAttributeData& OldRange)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, Range, OldRange);	
}

void UWeaponAttributeSet::OnRep_HipFireAccuracy(const FGameplayAttributeData& OldHipFireAccuracy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, HipFireAccuracy, OldHipFireAccuracy);
}

void UWeaponAttributeSet::OnRep_AimedAccuracy(const FGameplayAttributeData& OldAimedAccuracy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, AimedAccuracy, OldAimedAccuracy);
}

void UWeaponAttributeSet::OnRep_MaxSpreadAngle(const FGameplayAttributeData& OldMaxSpreadAngle)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, MaxSpreadAngle, OldMaxSpreadAngle);
}

void UWeaponAttributeSet::OnRep_LastShotTime(const FGameplayAttributeData& OldLastShotTime)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, LastShotTime, OldLastShotTime);	
}
