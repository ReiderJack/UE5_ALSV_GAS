// 

#pragma once
#include "Character/WeaponActor.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class ALSV_GAS_API UWeaponWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnWeaponUpdate(AWeaponActor* WeaponActor);

};
