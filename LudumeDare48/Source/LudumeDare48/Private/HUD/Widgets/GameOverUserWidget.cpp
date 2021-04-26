// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Widgets/GameOverUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MSBJGameInstance.h"
#include "Public/LD48GameModeBase.h"
#include "Components/TextBlock.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameOverUserWidget, All, All);

void UGameOverUserWidget::SetNewTotal(FString NewTotal)
{
	this->TotalTextBlock->SetText(FText::FromString(NewTotal));
}

void UGameOverUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	this->MainMenuButton->OnClicked.AddDynamic(this, &UGameOverUserWidget::OnExitLevel);
}

void UGameOverUserWidget::OnExitLevel()
{
	if (GetWorld() && GetWorld()->GetGameInstance())
	{
		const auto TempGameInstance = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
		if (TempGameInstance)
			UGameplayStatics::OpenLevel(GetWorld(), TempGameInstance->NameMenuLevel);
		else
			UE_LOG(LogGameOverUserWidget, Error, TEXT("GameInstance is nullptr"));
	}
}
