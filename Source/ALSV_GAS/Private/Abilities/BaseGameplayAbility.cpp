// 


#include "Abilities/BaseGameplayAbility.h"

void UBaseGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

ACharacterBase* UBaseGameplayAbility::GetCharacterBase()
{
	if(!CharacterBase)
	{
		CharacterBase = Cast<ACharacterBase>(GetOwningActorFromActorInfo());
	}
	return CharacterBase;
}
