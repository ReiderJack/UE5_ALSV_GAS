

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainAttributesWidget.generated.h"

/**
 * 
 */
UCLASS()
class ALSV_GAS_API UMainAttributesWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnHealthChanged(float NewHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnHealthMaxChanged(float NewHealthMax);
};
