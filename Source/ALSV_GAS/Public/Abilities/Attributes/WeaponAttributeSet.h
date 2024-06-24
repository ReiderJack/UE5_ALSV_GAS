// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "WeaponAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)           \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)               \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)               \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class ALSV_GAS_API UWeaponAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Damage)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Headshot)
	FGameplayAttributeData Headshot = 0.5f;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Headshot)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Ammo)
	FGameplayAttributeData Ammo;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Ammo)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ClipSize)
	FGameplayAttributeData ClipSize = 0.f;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, ClipSize)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_SpareAmmo)
	FGameplayAttributeData SpareAmmo = 0.f;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, SpareAmmo)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxSpareAmmo)
	FGameplayAttributeData MaxSpareAmmo = 0.f;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxSpareAmmo)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RoundsPerMinute)
	FGameplayAttributeData RoundsPerMinute = 0.f;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, RoundsPerMinute)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Range)
	FGameplayAttributeData Range = 1000.f;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Range)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_HipFireAccuracy)
	FGameplayAttributeData HipFireAccuracy = 1.f;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, HipFireAccuracy)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_AimedAccuracy)
	FGameplayAttributeData AimedAccuracy = 1.f;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, AimedAccuracy)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxSpreadAngle)
	FGameplayAttributeData MaxSpreadAngle = 0.f;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxSpreadAngle)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LastShotTime)
	FGameplayAttributeData LastShotTime = 0.f;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, LastShotTime)

protected:
	UFUNCTION()
	virtual void OnRep_Ammo(const FGameplayAttributeData& OldAmmo);

	UFUNCTION()
	virtual void OnRep_SpareAmmo(const FGameplayAttributeData& OldSpareAmmo);

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldDamage);

	UFUNCTION()
	virtual void OnRep_Headshot(const FGameplayAttributeData& OldHeadshot);

	UFUNCTION()
	virtual void OnRep_ClipSize(const FGameplayAttributeData& OldClipSize);

	UFUNCTION()
	virtual void OnRep_MaxSpareAmmo(const FGameplayAttributeData& OldMaxSpareAmmo);

	UFUNCTION()
	virtual void OnRep_RoundsPerMinute(const FGameplayAttributeData& OldRoundsPerMinute);

	UFUNCTION()
	virtual void OnRep_Range(const FGameplayAttributeData& OldRange);

	UFUNCTION()
	virtual void OnRep_HipFireAccuracy(const FGameplayAttributeData& OldHipFireAccuracy);

	UFUNCTION()
	virtual void OnRep_AimedAccuracy(const FGameplayAttributeData& OldAimedAccuracy);
	
	UFUNCTION()
	virtual void OnRep_MaxSpreadAngle(const FGameplayAttributeData& OldMaxSpreadAngle);

	UFUNCTION()
	virtual void OnRep_LastShotTime(const FGameplayAttributeData& OldLastShotTime);
};
