// Copyright Epic Games, Inc. All Rights Reserved.

/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Menu/Public/MSBJDataTypes.h"
#include "MenuSystemByJamGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API AMenuSystemByJamGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	FOnGameMenuStateChangedSignature OnGameMenuStateChangedSignature;
	FOnSetCountTotalDepthResult OnSetCountTotalDepthResult;
	
	AMenuSystemByJamGameModeBase();
	
	virtual void StartPlay() override;
	const EMSBJGameMenuState& GetCurrentState() const;
	void SetGameState(EMSBJGameMenuState NewState);

protected:
	
private:
	EMSBJGameMenuState CurrentState = EMSBJGameMenuState::InProgress;

	void SetStartPlaySettings();
};
