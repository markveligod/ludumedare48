// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Widgets/GamePauseUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Public/LD48GameModeBase.h"
#include "MSBJGameInstance.h"
#include "Components/Button.h"


void UGamePauseUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	this->ContinueButton->OnClicked.AddDynamic(this, &UGamePauseUserWidget::CallContinueGame);
	this->MainMenuButton->OnClicked.AddDynamic(this, &UGamePauseUserWidget::CallMainMenu);
}

void UGamePauseUserWidget::CallContinueGame()
{
	const auto GameMode = Cast<ALD48GameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->ClearPause();
		GameMode->ChangeGameState(EGameState::InProgress);
	}
}

void UGamePauseUserWidget::CallMainMenu()
{
	const auto GameInst = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		UGameplayStatics::OpenLevel(GetWorld(), GameInst->NameMenuLevel);
	}
}
