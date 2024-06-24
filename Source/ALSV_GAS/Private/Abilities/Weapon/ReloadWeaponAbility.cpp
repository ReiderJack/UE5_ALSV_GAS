#include "Abilities/Weapon/ReloadWeaponAbility.h"

void UReloadWeaponAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	EquippedWeaponActor = GetCharacterBase()->GetCurrentWeaponActor();

	if (EquippedWeaponActor == nullptr)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	EquippedWeaponActor->Reload();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	/*
	const UWeaponAttributeSet* WeaponAttributeSet = EquippedWeaponActor->WeaponAttributes;

	// If ammo is still full, cancel the ability
	if (WeaponAttributeSet->GetAmmo() >= WeaponAttributeSet->GetClipSize())
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	// if there are no more spare ammo, then cancel the ability
	if (WeaponAttributeSet->GetSpareAmmo() <= 0.f)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	// Get the montage of the weapon from the firearm settings reload montage
	UAnimMontage* ReloadMontage = EquippedWeaponActor->ReloadMontage;

	// If the reload montage is not set, then complete the reload
	if (ReloadMontage == nullptr)
	{
		ReloadWeapon();
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	const float ReloadRate = RPGCharacter->AttributeSet->GetReloadRate();
	UAbilityTask_PlayMontageAndWait* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, NAME_None, ReloadMontage, ReloadRate, NAME_None, false, 1.f);

	Task->OnCompleted.AddDynamic(this, &UReloadAbility::OnMontageComplete);
	Task->ReadyForActivation();

	UAbilityTask_WaitGameplayEvent* TaskWaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, TAG_Event_Reload, nullptr, false, false);
	TaskWaitGameplayEvent->EventReceived.AddDynamic(this, &UReloadAbility::OnReloadEvent);
	TaskWaitGameplayEvent->ReadyForActivation();
	*/
}

void UReloadWeaponAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UReloadWeaponAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayTagContainer* SourceTags,
                                        const FGameplayTagContainer* TargetTags,
                                        FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) return false;
/*
	const AWeaponActor* WeaponActor = Cast<ACharacterBase>(ActorInfo->OwnerActor)->GetCurrentWeaponActor();
	if (!WeaponActor) return false;

	const UWeaponAttributeSet* WeaponAttributeSet = WeaponActor->WeaponAttributes;
	if (!WeaponAttributeSet) return false;

	if (WeaponAttributeSet->GetAmmo() >= WeaponAttributeSet->GetClipSize()) return false;

	if (WeaponAttributeSet->GetSpareAmmo() <= 0.f) return false;

	// Check if the reload montage is set
	// if (WeaponActor->FirearmSettings.CharacterReloadMontage == nullptr) return false;
*/
	return true;
}

// AmmoToReload is the desired ammo to be reloaded to the magazine
void UReloadWeaponAbility::ReloadWeapon_Implementation(const float AmmoToReload) const
{
	const UWeaponAttributeSet* WeaponAttributeSet = EquippedWeaponActor->WeaponAttributes;
	const float MaxClipSize = WeaponAttributeSet->GetClipSize();
	const float CurrentSpareAmmo = WeaponAttributeSet->GetSpareAmmo();
	const float CurrentAmmo = WeaponAttributeSet->GetAmmo();
	
	float AmmoToReloadToClip = MaxClipSize - CurrentAmmo;

	if (AmmoToReload > 0.f)
	{
		AmmoToReloadToClip = AmmoToReload;
	}

	AmmoToReloadToClip = FMath::Min(AmmoToReloadToClip, CurrentSpareAmmo);

	const float NewAmmoInClip = CurrentAmmo + AmmoToReloadToClip;

	const float NewSpareAmmo = CurrentSpareAmmo - AmmoToReloadToClip;

	//WeaponAttributeSet->SetAmmo(NewAmmoInClip);
	//WeaponAttributeSet->SetSpareAmmo(NewSpareAmmo);
}

void UReloadWeaponAbility::OnMontageComplete()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UReloadWeaponAbility::OnReloadEvent(FGameplayEventData Payload)
{
	ReloadWeapon(Payload.EventMagnitude);
}
