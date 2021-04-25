// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/LD48PlayerController.h"
#include "Public/LD48GameModeBase.h"

void ALD48PlayerController::BeginPlay()
{
	check(GetWorld());
	this->GameMode = GetWorld()->GetAuthGameMode<ALD48GameModeBase>();
	check(this->GameMode)

	this->GameMode->OnGameState.AddUObject(this, &ALD48PlayerController::OnGameState);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ALD48PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent)
		return;

	InputComponent->BindAction("Pause", IE_Pressed, this, &ALD48PlayerController::OnPauseGame);
}

void ALD48PlayerController::OnGameState(EGameState GameState)
{
	
	if (GameState == EGameState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
		this->GameMode->ClearPause();
	}
	else if (GameState == EGameState::Pause)
	{
		this->GameMode->SetPause(this);
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;
	}
	else
	{
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;
	}
}

void ALD48PlayerController::OnPauseGame()
{
	this->GameMode->ChangeGameState(EGameState::Pause);
}

