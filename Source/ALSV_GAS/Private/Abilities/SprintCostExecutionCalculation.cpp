#include "Abilities/SprintCostExecutionCalculation.h"
#include "Abilities/Attributes/BaseAttributeSet.h"
#include "GameFramework/PawnMovementComponent.h"

USprintCostExecutionCalculation::USprintCostExecutionCalculation()
{
	StaminaAttributeCaptureDefinition = FGameplayEffectAttributeCaptureDefinition(
		UBaseAttributeSet::GetStaminaAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true);

	RelevantAttributesToCapture.Add(StaminaAttributeCaptureDefinition);
}

void USprintCostExecutionCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	
	AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	
	UE_LOG(LogTemp, Warning, TEXT("Sprint Cost Calculation"));
	
	float SprintCost = 0.f;
	
	FAggregatorEvaluateParameters EvaluationParameters;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(StaminaAttributeCaptureDefinition, EvaluationParameters, SprintCost);

	APawn* Instigator = TargetActor->GetInstigator();

	if (Instigator->GetMovementComponent()->IsMovingOnGround() == false) return;
	
	float MovementSpeed = Instigator->GetMovementComponent()->Velocity.Size();

	if (MovementSpeed < MinMovementSpeed) return;
	
	const FGameplayAttribute StaminaAttr = UBaseAttributeSet::GetStaminaAttribute();
	const FGameplayModifierEvaluatedData Modifier = FGameplayModifierEvaluatedData(
		StaminaAttr, EGameplayModOp::Additive, SprintCost);

	OutExecutionOutput.AddOutputModifier(Modifier);
}
