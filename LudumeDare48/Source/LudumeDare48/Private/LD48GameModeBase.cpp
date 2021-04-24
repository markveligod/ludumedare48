// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/LD48GameModeBase.h"
#include "Public/LD48CharacterPlayerBase.h"
#include "Public/LD48PlayerController.h"
#include "Public/HUD/LD48PlayerHUD.h"

ALD48GameModeBase::ALD48GameModeBase()
{
	DefaultPawnClass = ALD48CharacterPlayerBase::StaticClass();
	HUDClass = ALD48PlayerHUD::StaticClass();
	PlayerControllerClass = ALD48PlayerController::StaticClass();
}

void ALD48GameModeBase::StartPlay()
{
	Super::StartPlay();

	this->ChangeGameState(EGameState::Welcome);
}

void ALD48GameModeBase::ChangeGameState(EGameState NewState)
{
	if (this->CurrentState == NewState)
		return;
	this->CurrentState = NewState;
	this->OnGameState.Broadcast(NewState);
}



