#include "Abilities/Weapon/ShootWeapon.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character/WeaponActor.h"

void UShootWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacterBase* CharBase = Cast<ACharacterBase>(ActorInfo->OwnerActor);
	WeaponActor = CharBase->GetCurrentWeaponActor();
	if(!WeaponActor)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		return;
	}
	CharBase->AimAction(true);
	WeaponActor->PressShoot(true);
	
	TaskInputRelease = UAbilityTask_WaitInputRelease::WaitInputRelease(this, false);
	TaskInputRelease->OnRelease.AddDynamic(this, &UShootWeapon::OnInputReleased);
	TaskInputRelease->ReadyForActivation();
	
	CommitAbility(Handle, ActorInfo, ActivationInfo);
}

void UShootWeapon::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (TaskInputRelease) TaskInputRelease->EndTask();
	if (WeaponActor) WeaponActor->PressShoot(false);
	GetCharacterBase()->AimAction(false);
}

void UShootWeapon::OnInputReleased(float TimeHeld)
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
