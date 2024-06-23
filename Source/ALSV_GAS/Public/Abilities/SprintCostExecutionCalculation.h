#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "SprintCostExecutionCalculation.generated.h"

UCLASS()
class ALSV_GAS_API USprintCostExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	USprintCostExecutionCalculation();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinMovementSpeed = 500.f;

private:
	FGameplayEffectAttributeCaptureDefinition StaminaAttributeCaptureDefinition;
};
