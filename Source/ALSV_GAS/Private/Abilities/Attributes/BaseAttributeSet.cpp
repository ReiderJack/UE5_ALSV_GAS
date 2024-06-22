


#include "Abilities/Attributes/BaseAttributeSet.h"
#include "GameplayEffectExtension.h"

bool UBaseAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float LocalDamageDone = GetDamage();
		SetDamage(0.f);

		if (LocalDamageDone > 0.0f)
		{
			const float NewHealth = GetHealth() - LocalDamageDone;
			SetHealth(FMath::Clamp(NewHealth, 0.0f, GetHealthMax()));
		}
	}
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	
	if(Attribute == GetHealthAttribute())
	{
		float healthMax = GetHealthMax();
		NewValue = FMath::Clamp(NewValue, 0.f, healthMax);
	}

	if(Attribute == GetStaminaAttribute())
	{
		float staminaMax = GetStaminaMax();
		NewValue = FMath::Clamp(NewValue, 0.f, staminaMax);
	}
}

void UBaseAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}
