#include "Character/CharacterBase.h"


UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
		return AbilitySystemComponent;
}

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AbilitiesInputComponent = CreateDefaultSubobject<UAbilitiesInputComponent>(TEXT("AbilitiesInputComponent"));
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(AbilitiesInputComponent)
	{
		AbilitiesInputComponent->SetupPlayerInputComponent(PlayerInputComponent);
	}
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

void ACharacterBase::InitAbilitySystemComponentRelated()
{
			
	if (!AbilitySystemComponent) return;
	// instruct the Ability System Component to instantiate the Attribute Set, which will then register it automatically
	BaseAttributeSet = AbilitySystemComponent->GetSet<UBaseAttributeSet>();

	if(GetLocalRole() < ROLE_Authority)
	{
		// Health
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &ACharacterBase::HealthChanged);
		HealthMaxChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthMaxAttribute()).AddUObject(this, &ACharacterBase::HealthMaxChanged);

		// Stamina
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetStaminaAttribute()).AddUObject(this, &ACharacterBase::StaminaChanged);
		StaminaMaxChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetStaminaMaxAttribute()).AddUObject(this, &ACharacterBase::StaminaMaxChanged);
	
		if (auto const controller = Cast<APlayerController>(GetController()))
		{
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

	InitDefaultEffects();
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

