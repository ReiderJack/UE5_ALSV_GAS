

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Attributes/BaseAttributeSet.h"
#include "UI/MainAttributesWidget.h"
#include "Abilities/Data/AbilitySet.h"
#include "CharacterBase.generated.h"


UCLASS()
class ALSV_GAS_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
public:
	// IAbilitySystemInterface function
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	GENERATED_BODY()

public:
	ACharacterBase();
	
	UPROPERTY()
	const UBaseAttributeSet* BaseAttributeSet;

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	UAbilitySet* InitialAbilitySet { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Binding")
	FAbilityInputBindings AbilityInputBindings;
	
	// Begin Input Bindings
	void AbilityInputBindingPressedHandler(EAbilityInput abilityInput);
	void AbilityInputBindingReleasedHandler(EAbilityInput abilityInput);
	
	// Widget related
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<UMainAttributesWidget> MainAttributesWidgetClass;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UMainAttributesWidget* MainAttributesWidget;

	// Ability system
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	FDelegateHandle HealthChangedDelegateHandle;
	void HealthChanged(const FOnAttributeChangeData & Data);

	FDelegateHandle HealthMaxChangedDelegateHandle;
	void HealthMaxChanged(const FOnAttributeChangeData & Data);

private:
	UPROPERTY(Transient)
	TArray<FGameplayAbilitySpecHandle> InitiallyGrantedAbilitySpecHandles;
};
