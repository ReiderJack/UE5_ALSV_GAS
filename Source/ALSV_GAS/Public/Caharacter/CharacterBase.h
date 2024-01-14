

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Attributes/BaseAttributeSet.h"
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

protected:
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	virtual void BeginPlay() override;
};
