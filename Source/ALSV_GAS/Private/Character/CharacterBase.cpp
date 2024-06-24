#include "Character/CharacterBase.h"
#include "UI/WeaponWidget.h"
#include "Character/WeaponActor.h"
#include "Net/UnrealNetwork.h"


UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
		return AbilitySystemComponent;
}

ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AbilitiesInputComponent = CreateDefaultSubobject<UAbilitiesInputComponent>(TEXT("AbilitiesInputComponent"));

	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(AbilitiesInputComponent)
	{
		AbilitiesInputComponent->SetupPlayerInputComponent(PlayerInputComponent);
	}
}

AWeaponActor* ACharacterBase::GetCurrentWeaponActor()
{
	switch (CurrentWeaponType)
	{
	case EWeaponType::MainWeapon:
		return MainWeapon;

	case EWeaponType::SecondaryWeapon:
		return SecondWeapon;

		// Add more cases for additional weapon types if needed
	default:
		return nullptr;
	}
}

void ACharacterBase::UpdateWeaponWidget(AWeaponActor* WeaponActor)
{
	if(HasAuthority()) return;
	
	if(!WeaponWidget)
	{
		WeaponWidget = CreateWidget<UWeaponWidget>(Cast<APlayerController>(GetController()), WeaponWidgetClass);
		WeaponWidget->AddToViewport();
	}
	
	WeaponWidget->OnWeaponUpdate(WeaponActor);
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponentRelated();
	InitUI();
}

void ACharacterBase::InitAbilitySystemComponentRelated()
{
	if (!AbilitySystemComponent) return;
	// instruct the Ability System Component to instantiate the Attribute Set, which will then register it automatically
	BaseAttributeSet = AbilitySystemComponent->GetSet<UBaseAttributeSet>();
	
	InitDefaultEffects();
}

void ACharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACharacterBase, MainWeapon);
	DOREPLIFETIME(ACharacterBase, SecondWeapon);
}

void ACharacterBase::InitDefaultEffects()
{
	if (!HasAuthority()) return;

	// Apply default effects
	for (TSubclassOf<UGameplayEffect> Effect : DefaultEffects)
	{
		if (Effect == nullptr)
			continue;

		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ACharacterBase::InitUI_Implementation()
{
	if(GetLocalRole() < ROLE_Authority)
	{
		if (!AbilitySystemComponent) return;
		// instruct the Ability System Component to instantiate the Attribute Set, which will then register it automatically
		BaseAttributeSet = AbilitySystemComponent->GetSet<UBaseAttributeSet>();
		
		// Health
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &ACharacterBase::HealthChanged);
		HealthMaxChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthMaxAttribute()).AddUObject(this, &ACharacterBase::HealthMaxChanged);

		// Stamina
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetStaminaAttribute()).AddUObject(this, &ACharacterBase::StaminaChanged);
		StaminaMaxChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetStaminaMaxAttribute()).AddUObject(this, &ACharacterBase::StaminaMaxChanged);
	
		if (auto const controller = Cast<APlayerController>(GetController()))
		{
			if(!MainAttributesWidgetClass) return;
			
			MainAttributesWidget = CreateWidget<UMainAttributesWidget>(controller, MainAttributesWidgetClass);
			MainAttributesWidget->AddToViewport();
			// Health
			MainAttributesWidget->OnHealthMaxChanged(BaseAttributeSet->GetHealthMax());
			MainAttributesWidget->OnHealthChanged(BaseAttributeSet->GetHealth());
			// Stamina
			MainAttributesWidget->OnStaminaMaxChanged(BaseAttributeSet->GetStaminaMax());
			MainAttributesWidget->OnStaminaChanged(BaseAttributeSet->GetStamina());
		}
	}
}

void ACharacterBase::HealthChanged(const FOnAttributeChangeData& Data)
{
	if (MainAttributesWidget)
	{
		MainAttributesWidget->OnHealthChanged(Data.NewValue);
	}
}

void ACharacterBase::HealthMaxChanged(const FOnAttributeChangeData& Data)
{
	if (MainAttributesWidget)
	{
		MainAttributesWidget->OnHealthMaxChanged(Data.NewValue);
	}
}

void ACharacterBase::StaminaChanged(const FOnAttributeChangeData& Data)
{
	if (MainAttributesWidget)
	{
		MainAttributesWidget->OnStaminaChanged(Data.NewValue);
	}
}

void ACharacterBase::StaminaMaxChanged(const FOnAttributeChangeData& Data)
{
	if (MainAttributesWidget)
	{
		MainAttributesWidget->OnStaminaMaxChanged(Data.NewValue);
	}
}

