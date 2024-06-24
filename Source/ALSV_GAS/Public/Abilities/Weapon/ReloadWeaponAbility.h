#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseGameplayAbility.h"
#include "Character/WeaponActor.h"
#include "ReloadWeaponAbility.generated.h"

UCLASS()
class ALSV_GAS_API UReloadWeaponAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY()
	AWeaponActor* EquippedWeaponActor = nullptr;

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
							bool bWasCancelled) override;
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
									const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
									FGameplayTagContainer* OptionalRelevantTags) const override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void ReloadWeapon(const float AmmoToReload = 0.f) const;
	void ReloadWeapon_Implementation(const float AmmoToReload = 0.f) const;

private:
	UFUNCTION()
	void OnMontageComplete();

	UFUNCTION()
	void OnReloadEvent(FGameplayEventData Payload);
};
