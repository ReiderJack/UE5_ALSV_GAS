


#include "Abilities/Data/AbilitySet.h"

#include "AbilitySystemComponent.h"


TArray<FGameplayAbilitySpecHandle> UAbilitySet::GrantAbilitiesToAbilitySystem(
	UAbilitySystemComponent* AbilitySystemComponent) const
{
	
	check(AbilitySystemComponent);

	TArray<FGameplayAbilitySpecHandle> handles;

	// Go over all defined abilities in data asset
	// and give those abilities directly into the ability system
	// and binding the input ID
	for (const auto abilitySetItem : AbilitySetItems)
	{
		auto test = FGameplayAbilitySpec(abilitySetItem.GameplayAbility,0,static_cast<uint32>(abilitySetItem.InputKey));
		handles.AddUnique(AbilitySystemComponent->GiveAbility(test));
	}

	return handles;
}
