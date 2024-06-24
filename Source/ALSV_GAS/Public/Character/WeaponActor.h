// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
//#include "CharacterBase.h"
#include "Abilities/Attributes/WeaponAttributeSet.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Library/ALSCharacterEnumLibrary.h"
#include "WeaponActor.generated.h"

class ACharacterBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMagazineAmmoDepleted);

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	SemiAutomatic UMETA(DisplayName = "Semi-Automatic"),
	Automatic UMETA(DisplayName = "Automatic")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	NoWeapon UMETA(DisplayName = "No Weapon"),
	MainWeapon UMETA(DisplayName = "Main Weapon"),
	SecondaryWeapon UMETA(DisplayName = "Secondary Weapon"),
	// Add more weapon types if needed
};

UCLASS()
class ALSV_GAS_API AWeaponActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ArrowComponent;
	
public:
	// Sets default values for this actor's properties
	AWeaponActor();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	void InitializeAttributes();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	int32 MaxMagazineAmmo = 20;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	int32 MaxTotalAmmo = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	float ShootDistance = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	EFireMode FireMode = EFireMode::SemiAutomatic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	float TimeBetweenShots = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	bool AutoReloadOnMagazineAmmoDepleted = true;

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void StartShoot();
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Shoot();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void StopShoot();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Reload();

	FOnMagazineAmmoDepleted OnMagazineAmmoDepleted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ShootRange = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName WeaponHolsterSocket = "pistol_holster_socket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName WeaponHandSocket = "gun_hand_socket";
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponType WeaponType = EWeaponType::SecondaryWeapon;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EALSOverlayState AnimationState = EALSOverlayState::PistolOneHanded;

	UPROPERTY(BlueprintReadOnly)
	const UWeaponAttributeSet* WeaponAttributes;

	UPROPERTY(BlueprintReadWrite)
	UAnimMontage* ReloadMontage;

	UFUNCTION(BlueprintCallable)
	void PressShoot(bool IsPressed);

	UFUNCTION(BlueprintCallable)
	void PickUpWeapon(ACharacterBase* NewWeaponOwner);

	UFUNCTION(BlueprintCallable)
	void HolsterWeapon();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	int32 CurrentMagazineAmmo = 0;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	int32 CurrentTotalAmmo = 100;
	
	FTimerHandle ShootTimerHandle;
	bool bIsShooting = false;
	
	// Ability system
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Abilities")
	ACharacterBase* WeaponOwner;
};
