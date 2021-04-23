/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MSBJMenuController.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API AMSBJMenuController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
};
