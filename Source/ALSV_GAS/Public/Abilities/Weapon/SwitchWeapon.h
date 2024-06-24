// 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseGameplayAbility.h"
#include "SwitchWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ALSV_GAS_API USwitchWeapon : public UBaseGameplayAbility
{
	GENERATED_BODY()

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) override;

protected:

	UFUNCTION()
	void SwitchWeapon(ACharacterBase* Character);
};
