// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/LD48DataTypes.h"
#include "LD48GameModeBase.generated.h"

class UMSBJGameInstance;
/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API ALD48GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	FOnGameState OnGameState;
	FOnDeath OnDeath;
	void ChangeGameState(EGameState NewState);
	ALD48GameModeBase();
	int32 GetCountDepthEnd() const;
protected:
	virtual void StartPlay() override;
	
private:
	UMSBJGameInstance* GameInst;
	float StartSound;
	float StartMusic;
	void UpdateTotalDepth();
	EGameState CurrentState = EGameState::WaitingToStart;
	void CallGameOverDeath();
	int32 DepthCountEnd;
};
