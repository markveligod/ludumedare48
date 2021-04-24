// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/LD48PlayerHUD.h"
#include "Widgets/PlayerUserWidget.h"
#include "Public/LD48GameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogLD48PlayerHUD, All, All);

void ALD48PlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!this->PlayerHudWidgetClass)
	{
		UE_LOG(LogLD48PlayerHUD, Error, TEXT("Widgets is nullptr"));
	}

	this->GameWidgets.Add(EGameState::InProgress, CreateWidget<UUserWidget>(GetWorld(), this->PlayerHudWidgetClass));

    for (auto TempGameWidgetPair : this->GameWidgets)
    {
        const auto TempGameValueWidget = TempGameWidgetPair.Value;
        if (!TempGameValueWidget) continue;

        TempGameValueWidget->AddToViewport();
        TempGameValueWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<ALD48GameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnGameState.AddUObject(this, &ALD48PlayerHUD::OnStateChanged);
        }
    }
}

void ALD48PlayerHUD::OnStateChanged(EGameState NewState)
{
    if (this->CurrentWidget)
    {
        this->CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (this->GameWidgets.Contains(NewState))
    {
        this->CurrentWidget = this->GameWidgets[NewState];
    }

    if (this->CurrentWidget)
    {
        this->CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }

    UE_LOG(LogLD48PlayerHUD, Display, TEXT("Game State: %s"), *UEnum::GetValueAsString(NewState))
}
