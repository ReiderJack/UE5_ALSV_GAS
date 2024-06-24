#include "Character/WeaponActor.h"

#include "Character/CharacterBase.h"
#include "Net/UnrealNetwork.h"

AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Scene comp
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	// Skeletal mesh comp
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(SceneComponent);

	// Arrow comp
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponwnt"));
	ArrowComponent->SetupAttachment(RootComponent);

	// Ability system comp
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	WeaponAttributes = CreateDefaultSubobject<UWeaponAttributeSet>(TEXT("WeaponAttributes"));

	// Ammo
	CurrentMagazineAmmo = MaxMagazineAmmo;

	if(AutoReloadOnMagazineAmmoDepleted) OnMagazineAmmoDepleted.AddDynamic(this, &AWeaponActor::Reload);
	
	bReplicates = true;
}

void AWeaponActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeaponActor, WeaponOwner);
}

UAbilitySystemComponent* AWeaponActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWeaponActor::PressShoot(bool IsPressed)
{
	UE_LOG(LogTemp, Log, TEXT("Weapon: PressFire: %s"), IsPressed ? TEXT("true") : TEXT("false"));

	if(!WeaponOwner) return;
	if(IsPressed)
	{
		StartShoot();
	}
	else
	{
		StopShoot();
	}
}

void AWeaponActor::PickUpWeapon(ACharacterBase* NewWeaponOwner)
{
	WeaponOwner = NewWeaponOwner;

	HolsterWeapon();
}

void AWeaponActor::HolsterWeapon()
{
	if(!WeaponOwner) return;

	AttachToComponent(WeaponOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponHolsterSocket);
	WeaponOwner->SetOverlayState(EALSOverlayState::Default, true);
}

void AWeaponActor::EquipWeapon()
{
	if(!WeaponOwner) return;
	// Equip new 
	AttachToComponent(WeaponOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponHandSocket);
	// Change character animation
	WeaponOwner->SetOverlayState(AnimationState, true);
}

void AWeaponActor::InitializeAttributes()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	WeaponAttributes = AbilitySystemComponent->GetSet<UWeaponAttributeSet>();
}

void AWeaponActor::StartShoot()
{
	if (!bIsShooting)
	{
		bIsShooting = true;
		Shoot(); // Immediately fire the first shot

		// Start firing timer for automatic mode
		if (FireMode == EFireMode::Automatic)
		{
			GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &AWeaponActor::Shoot, TimeBetweenShots, true);
		}
	}
}

void AWeaponActor::Shoot()
{
	if(CurrentMagazineAmmo == 0 )
	{
		OnMagazineAmmoDepleted.Broadcast();
		return;
	}

	CurrentMagazineAmmo--;
	CurrentTotalAmmo--;

	if (HasAuthority())
	{
		// Code running on the server
		UE_LOG(LogTemp, Log, TEXT("TotalAmmo: %i (Server)"), CurrentTotalAmmo);
		UE_LOG(LogTemp, Log, TEXT("MagazineAmmo: %i (Server)"), CurrentMagazineAmmo);
	}
	else
	{
		// Code running on a client
		UE_LOG(LogTemp, Log, TEXT("TotalAmmo: %i (Client)"), CurrentTotalAmmo);
		UE_LOG(LogTemp, Log, TEXT("MagazinelAmmo: %i (Client)"), CurrentMagazineAmmo);
	}
	
	// Get player viewpoint
	FVector StartLocation;
	FRotator ViewRotation;
	WeaponOwner->GetController()->GetPlayerViewPoint(StartLocation, ViewRotation);
	StartLocation = ArrowComponent->GetComponentLocation();

	// Calculate end location (trace to the player's view point)
	FVector EndLocation = StartLocation + (ViewRotation.Vector() * ShootRange);

	// Setup trace parameters
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, GetOwner());
	TraceParams.bReturnPhysicalMaterial = true; // Optional: to get material information

	// Perform line trace
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility,
		TraceParams
	);

	// Optional: Draw debug line for visualization
	if (bHit)
	{
		if(GetLocalRole() < ROLE_Authority)
		{
			DrawDebugLine(
				GetWorld(),
				StartLocation,
				HitResult.ImpactPoint,
				FColor::Green,
				false, -1, 0,
				1.0f);
		}
		else
		{
			DrawDebugLine(
				GetWorld(),
				StartLocation,
				HitResult.ImpactPoint,
				FColor::Purple,
				false, -1, 0,
				1.0f);
		}

	}
	else
	{
		if(GetLocalRole() < ROLE_Authority)
		{
			DrawDebugLine(
				GetWorld(),
				StartLocation,
				EndLocation,
				FColor::Red,
				false, -1, 0,
				1.0f
			);
		}
		else
		{
			DrawDebugLine(
				GetWorld(),
				StartLocation,
				EndLocation,
				FColor::Yellow,
				false, -1, 0,
				1.0f
			);
		}
	}

	// Process HitResult if needed (e.g., apply damage, interact with objects, etc.)
}

void AWeaponActor::StopShoot()
{
	if (bIsShooting)
	{
		bIsShooting = false;
		GetWorldTimerManager().ClearTimer(ShootTimerHandle);
	}
}

void AWeaponActor::Reload()
{
	int32 AmmoNeeded = MaxMagazineAmmo - CurrentMagazineAmmo;
	if (AmmoNeeded > 0 && CurrentTotalAmmo > 0)
	{
		int32 AmmoToReload = FMath::Min(AmmoNeeded, CurrentTotalAmmo);
		
		if (HasAuthority())
		{
			// Code running on the server
			UE_LOG(LogTemp, Log, TEXT("AmmoToReload: %i (Server)"), AmmoToReload);
			UE_LOG(LogTemp, Log, TEXT("TotalAmmo Before: %i (Server)"), CurrentTotalAmmo);
			UE_LOG(LogTemp, Log, TEXT("MagazineAmmo Before: %i (Server)"), CurrentMagazineAmmo);
		}
		else
		{
			// Code running on a client
			UE_LOG(LogTemp, Log, TEXT("AmmoToReload: %i (Client)"), AmmoToReload);
			UE_LOG(LogTemp, Log, TEXT("TotalAmmo Before: %i (Client)"), CurrentTotalAmmo);
			UE_LOG(LogTemp, Log, TEXT("MagazinelAmmo Before: %i (Client)"), CurrentMagazineAmmo);
		}
		
		CurrentMagazineAmmo += AmmoToReload;
		CurrentTotalAmmo -= AmmoToReload;

		if (HasAuthority())
		{
			// Code running on the server
			UE_LOG(LogTemp, Log, TEXT("TotalAmmo Before: %i (Server)"), CurrentTotalAmmo);
			UE_LOG(LogTemp, Log, TEXT("MagazineAmmo Before: %i (Server)"), CurrentMagazineAmmo);
		}
		else
		{
			// Code running on a client
			UE_LOG(LogTemp, Log, TEXT("TotalAmmo After: %i (Client)"), CurrentTotalAmmo);
			UE_LOG(LogTemp, Log, TEXT("MagazinelAmmo After: %i (Client)"), CurrentMagazineAmmo);
		}
	}
}