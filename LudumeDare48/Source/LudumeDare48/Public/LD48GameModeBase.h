// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/LD48DataTypes.h"
#include "LD48GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API ALD48GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	FOnGameState OnGameState;
	
	ALD48GameModeBase();
	
protected:
	virtual void StartPlay() override;
	
private:
	EGameState CurrentState = EGameState::WaitingToStart;
	void ChangeGameState(EGameState NewState);
};