// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/LD48GameModeBase.h"
#include "Public/LD48CharacterPlayerBase.h"
#include "Public/LD48PlayerController.h"
#include "Public/HUD/LD48PlayerHUD.h"
#include "MSBJGameInstance.h"
#include "Kismet/GameplayStatics.h"

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

	//inprogress is temp
	this->OnDeath.AddUObject(this, &ALD48GameModeBase::CallGameOverDeath);
	this->ChangeGameState(EGameState::Welcome);
}

void ALD48GameModeBase::UpdateTotalDepth()
{
	const auto GameInst = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		const auto TempCharacter = Cast<ALD48CharacterPlayerBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (TempCharacter && GameInst->TotalDepth < TempCharacter->GetCountDepth())
		{
			GameInst->TotalDepth = TempCharacter->GetCountDepth();
			this->DepthCountEnd = TempCharacter->GetCountDepth();
		}
		  UE_LOG(LogLD48GameModeBase, Display, TEXT("Total Game Mode LD48: %d"), TempCharacter->GetCountDepth());
	}
}

void ALD48GameModeBase::ChangeGameState(EGameState NewState)
{
	if (this->CurrentState == NewState)
		return;
	if (NewState == EGameState::GameOver)
		this->UpdateTotalDepth();
	this->CurrentState = NewState;
	this->OnGameState.Broadcast(NewState);
}

void ALD48GameModeBase::CallGameOverDeath()
{
	this->ChangeGameState(EGameState::GameOver);
}



