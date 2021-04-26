// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/LD48GameModeBase.h"
#include "Public/LD48CharacterPlayerBase.h"
#include "Public/LD48PlayerController.h"
#include "Public/HUD/LD48PlayerHUD.h"
#include "MSBJGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogLD48GameModeBase, All, All);

ALD48GameModeBase::ALD48GameModeBase()
{
	DefaultPawnClass = ALD48CharacterPlayerBase::StaticClass();
	HUDClass = ALD48PlayerHUD::StaticClass();
	PlayerControllerClass = ALD48PlayerController::StaticClass();
}

int32 ALD48GameModeBase::GetCountDepthEnd() const
{
	return (this->DepthCountEnd);
}

void ALD48GameModeBase::StartPlay()
{
	Super::StartPlay();

	this->GameInst = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
	check(this->GameInst);
	//inprogress is temp
	this->OnDeath.AddUObject(this, &ALD48GameModeBase::CallGameOverDeath);
	this->ChangeGameState(EGameState::Welcome);
}

void ALD48GameModeBase::UpdateTotalDepth()
{
	const auto TempCharacter = Cast<ALD48CharacterPlayerBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	this->DepthCountEnd = TempCharacter->GetCountDepth();
	if (this->GameInst->TotalDepth < TempCharacter->GetCountDepth())
	{
		this->GameInst->TotalDepth = TempCharacter->GetCountDepth();
	}
}

void ALD48GameModeBase::ChangeGameState(EGameState NewState)
{
	if (this->CurrentState == NewState)
		return;
	if (NewState == EGameState::GameOver)
		this->UpdateTotalDepth();
	if (NewState == EGameState::Welcome)
	{
		this->StartMusic = this->GameInst->MusicMenuClass->Properties.Volume;
		this->StartSound = this->GameInst->SoundMenuClass->Properties.Volume;
		this->GameInst->MusicMenuClass->Properties.Volume = 0.f;
		this->GameInst->SoundMenuClass->Properties.Volume = 0.f;
	}
	if (NewState == EGameState::InProgress)
	{
		this->GameInst->MusicMenuClass->Properties.Volume = this->StartMusic;
		this->GameInst->SoundMenuClass->Properties.Volume = this->StartSound;
	}
	this->CurrentState = NewState;
	this->OnGameState.Broadcast(NewState);
}

void ALD48GameModeBase::CallGameOverDeath()
{
	const auto TempCharacter = Cast<ALD48CharacterPlayerBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (TempCharacter)
		TempCharacter->SetIsDeadTrue();
	this->ChangeGameState(EGameState::GameOver);
}



