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

class UWeaponWidget;
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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage = 15;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxMagazineAmmo = 20;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxTotalAmmo = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EFireMode FireMode = EFireMode::SemiAutomatic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TimeBetweenShots = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ShootRange = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool AutoReloadOnMagazineAmmoDepleted = true;

	UFUNCTION(BlueprintCallable)
	void StartShoot();
	
	void OnWeaponUpdate();

	UFUNCTION(BlueprintCallable)
	void Shoot();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_Shoot(FVector StartLocation, FRotator ViewRotation);

	UFUNCTION(BlueprintCallable)
	void StopShoot();

	UFUNCTION(BlueprintCallable)
	void Reload();

	FOnMagazineAmmoDepleted OnMagazineAmmoDepleted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName WeaponName = "Gun";
	
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
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int32 GetCurrentMagazineAmmo() { return CurrentMagazineAmmo; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int32 GetCurrentSpareAmmo() { return CurrentSpareAmmo; }

protected:
	UPROPERTY(ReplicatedUsing=OnRep_MagazineAmmo)
	int32 CurrentMagazineAmmo = 0;

	UFUNCTION()
	void OnRep_MagazineAmmo(int32 NewMagazineAmmo);

	UPROPERTY(ReplicatedUsing=OnRep_SpareAmmo)
	int32 CurrentSpareAmmo = 100;

	UFUNCTION()
	void OnRep_SpareAmmo(int32 NewSpareAmmo);
	
	FTimerHandle ShootTimerHandle;
	bool bIsShooting = false;
	
	// Ability system
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	ACharacterBase* WeaponOwner;
	
	FHitResult LineTraceShot(FVector StartLocation, FVector EndLocation);
	
	UFUNCTION()
	void TryApplyDamageToHit(FHitResult HitResult);
};
