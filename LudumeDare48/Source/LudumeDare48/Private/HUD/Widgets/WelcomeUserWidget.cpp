// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Widgets/WelcomeUserWidget.h"
#include "Public/LD48GameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogWelcomeUserWidget, All, All);

void UWelcomeUserWidget::CallGameStateInprogress()
{
	const auto GameMode = GetWorld()->GetAuthGameMode<ALD48GameModeBase>();
	if (GameMode)
	{
		UE_LOG(LogWelcomeUserWidget, Warning, TEXT("Call BP Welcome to in progress"));
		GameMode->ChangeGameState(EGameState::InProgress);
	}
}
