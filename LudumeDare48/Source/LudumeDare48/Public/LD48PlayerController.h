// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/LD48DataTypes.h"
#include "LD48PlayerController.generated.h"

class ALD48GameModeBase;
/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API ALD48PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	ALD48GameModeBase* GameMode;
	void OnGameState(EGameState GameState);
	void OnPauseGame();
};
