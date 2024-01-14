


#include "Caharacter/CharacterBase.h"

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
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		// instruct the Ability System Component to instantiate the Attribute Set, which will then register it automatically
		BaseAttributeSet = AbilitySystemComponent->GetSet<UBaseAttributeSet>();
	}
}

