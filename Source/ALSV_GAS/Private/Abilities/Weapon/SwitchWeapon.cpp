// 


#include "Abilities/Weapon/SwitchWeapon.h"

#include "Character/WeaponActor.h"

void USwitchWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacterBase* Character = Cast<ACharacterBase>(ActorInfo->OwnerActor);
	if(!Character) CancelAbility(Handle, ActorInfo, ActivationInfo, false);
	
	SwitchWeapon(Character);
	
	CommitAbility(Handle, ActorInfo, ActivationInfo);
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void USwitchWeapon::SwitchWeapon(ACharacterBase* Character)
{
	switch (Character->CurrentWeaponType)
	{
	case EWeaponType::MainWeapon:
		UE_LOG(LogTemp, Log, TEXT("Equipping Main Weapon"));
		Character->CurrentWeaponType = EWeaponType::SecondaryWeapon;
		if(Character->SecondWeapon)
		{
			if(Character->MainWeapon)
			{
				Character->MainWeapon->HolsterWeapon();
			}
			Character->SecondWeapon->EquipWeapon();
		}
		break;

	case EWeaponType::SecondaryWeapon:
		UE_LOG(LogTemp, Log, TEXT("Equipping Secondary Weapon"));
		Character->CurrentWeaponType = EWeaponType::MainWeapon;
		if(Character->MainWeapon)
		{
			if(Character->SecondWeapon)
			{
				Character->SecondWeapon->HolsterWeapon();
			}
			Character->MainWeapon->EquipWeapon();
		}
		break;

		// Add more cases for additional weapon types if needed
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown Weapon Type"));
		Character->CurrentWeaponType = EWeaponType::MainWeapon;
		if(Character->MainWeapon)
		{
			if(Character->SecondWeapon)
			{
				Character->SecondWeapon->HolsterWeapon();
			}
			Character->MainWeapon->EquipWeapon();
		}
		break;
	}
}
