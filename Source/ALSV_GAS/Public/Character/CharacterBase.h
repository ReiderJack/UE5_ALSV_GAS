

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Attributes/BaseAttributeSet.h"
#include "UI/MainAttributesWidget.h"
#include "Abilities/AbilitiesInputComponent.h"
#include "Character/ALSCharacter.h"

#include "CharacterBase.generated.h"

enum class EWeaponType : uint8;
class AWeaponActor;
class UWeaponWidget;

UCLASS()
class ALSV_GAS_API ACharacterBase : public AALSCharacter, public IAbilitySystemInterface
{
public:
	// IAbilitySystemInterface function
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	GENERATED_BODY()

public:
	ACharacterBase(const FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(BlueprintReadWrite)
	EWeaponType CurrentWeaponType;
	
	UPROPERTY(BlueprintReadWrite, Replicated)
	AWeaponActor* MainWeapon;

	UPROPERTY(BlueprintReadWrite, Replicated)
	AWeaponActor* SecondWeapon;

	UFUNCTION(BlueprintCallable)
	AWeaponActor* GetCurrentWeaponActor();

	UPROPERTY()
	const UBaseAttributeSet* BaseAttributeSet;

	UFUNCTION(BlueprintCallable)
	void UpdateWeaponWidget(AWeaponActor* WeaponActor);
	
protected:
	
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	// Attribute delegates for widget update
	// TODO:: Make a MainUI to which all effects, abilities are added
	// TODO:: Make a base widget for scalable attribute which has a current and max
	FDelegateHandle HealthChangedDelegateHandle;
	void HealthChanged(const FOnAttributeChangeData & Data);

	FDelegateHandle HealthMaxChangedDelegateHandle;
	void HealthMaxChanged(const FOnAttributeChangeData & Data);

	FDelegateHandle StaminaChangedDelegateHandle;
	void StaminaChanged(const FOnAttributeChangeData & Data);

	FDelegateHandle StaminaMaxChangedDelegateHandle;
	void StaminaMaxChanged(const FOnAttributeChangeData & Data);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Input")
	UAbilitiesInputComponent* AbilitiesInputComponent;
	
	// Widget related
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<UMainAttributesWidget> MainAttributesWidgetClass;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UMainAttributesWidget* MainAttributesWidget;
	
	// Widget related
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UWeaponWidget> WeaponWidgetClass;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UWeaponWidget* WeaponWidget;

	UFUNCTION(BlueprintImplementableEvent)
	void Die();
		
	//========================================================

	// Ability system
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	void InitAbilitySystemComponentRelated();
	void InitDefaultEffects();
	
	UFUNCTION(Client, Reliable)
	void InitUI();
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

};
