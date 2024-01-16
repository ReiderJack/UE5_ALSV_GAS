

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Abilities/Data/AbilitySet.h"
#include "AbilitiesInputComponent.generated.h"

// The bridge between enhanced input system
// and gameplay ability input
USTRUCT()
struct FAbilityInputBindings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TArray<FAbilityInputToInputActionBinding> Bindings;
	
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALSV_GAS_API UAbilitiesInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilitiesInputComponent();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

protected:
	virtual void BeginPlay() override;
	
	// Ability system
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	UAbilitySet* InitialAbilitySet { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Binding")
	FAbilityInputBindings AbilityInputBindings;
	
	// Begin Input Bindings
	void AbilityInputBindingPressedHandler(EAbilityInput abilityInput);
	void AbilityInputBindingReleasedHandler(EAbilityInput abilityInput);

		
private:
	UPROPERTY(Transient)
	TArray<FGameplayAbilitySpecHandle> InitiallyGrantedAbilitySpecHandles;
};
