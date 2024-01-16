

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Attributes/BaseAttributeSet.h"
#include "UI/MainAttributesWidget.h"
#include "Abilities/AbilitiesInputComponent.h"

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
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	const UBaseAttributeSet* BaseAttributeSet;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Input")
	UAbilitiesInputComponent* AbilitiesInputComponent;
	
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

};
