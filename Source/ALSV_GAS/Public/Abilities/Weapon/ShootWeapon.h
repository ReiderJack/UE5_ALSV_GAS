#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseGameplayAbility.h"
#include "ShootWeapon.generated.h"

class UAbilityTask_WaitInputRelease;

UCLASS()
class ALSV_GAS_API UShootWeapon : public UBaseGameplayAbility
{
	GENERATED_BODY()
	
	UPROPERTY()
	UAbilityTask_WaitInputRelease* TaskInputRelease = nullptr;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UFUNCTION()
	void OnInputReleased(float TimeHeld);

	UPROPERTY()
	AWeaponActor* WeaponActor;
};
