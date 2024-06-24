// 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Character/CharacterBase.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ALSV_GAS_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UFUNCTION(Blueprintpure)
	ACharacterBase* GetCharacterBase();
	
	UPROPERTY()
	ACharacterBase* CharacterBase;
};
