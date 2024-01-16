


#include "Abilities/AbilitiesInputComponent.h"

#include "AbilitySystemComponent.h"

UAbilitiesInputComponent::UAbilitiesInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbilitiesInputComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(UEnhancedInputComponent* playerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		for(const FAbilityInputToInputActionBinding& binding : AbilityInputBindings.Bindings)
		{
			playerEnhancedInputComponent->BindAction(binding.InputAction, ETriggerEvent::Triggered, this, &ThisClass::AbilityInputBindingPressedHandler, binding.AbilityInput);
			playerEnhancedInputComponent->BindAction(binding.InputAction, ETriggerEvent::Completed, this, &ThisClass::AbilityInputBindingReleasedHandler, binding.AbilityInput);
		}
	}
}

// Called when the game starts
void UAbilitiesInputComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent = GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
	
	if(IsValid(InitialAbilitySet))
	{
		InitiallyGrantedAbilitySpecHandles.Append(InitialAbilitySet->GrantAbilitiesToAbilitySystem(AbilitySystemComponent));
	}
	
}

void UAbilitiesInputComponent::AbilityInputBindingPressedHandler(EAbilityInput abilityInput)
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<uint8>(abilityInput));
}

void UAbilitiesInputComponent::AbilityInputBindingReleasedHandler(EAbilityInput abilityInput)
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<uint8>(abilityInput));
}

