// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Widgets/PlayerUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Public/LD48CharacterPlayerBase.h"
#include "Components/Button.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerUserWidget, All, All);

void UPlayerUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const auto TempCharacter = Cast<ALD48CharacterPlayerBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (TempCharacter)
	{
		TempCharacter->OnChangeOxygen.AddUObject(this, &UPlayerUserWidget::UpdateProgressBarOxygen);
		TempCharacter->OnChangeDepth.AddUObject(this, &UPlayerUserWidget::UpdateDepthValue);
		TempCharacter->OnChangeKeys.AddUObject(this, &UPlayerUserWidget::UpdateKeysValue);
	}
	else
		UE_LOG(LogPlayerUserWidget, Error, TEXT("Character is nullptr"));
	
}

void UPlayerUserWidget::UpdateProgressBarOxygen(float NewValueOxygen)
{
	int TempValue = NewValueOxygen;
	this->OxygenProgressBar->SetPercent(NewValueOxygen / 100.f);
	this->OxygenValueTextBlock->SetText(FText::FromString(FString::FromInt(TempValue)));
}

void UPlayerUserWidget::UpdateDepthValue(int32 NewValueDepth)
{
	this->DepthValueTextBlock->SetText(FText::FromString(FString(FString::FromInt(NewValueDepth) + FString("m"))));
}

void UPlayerUserWidget::UpdateKeysValue(int32 NewValueKeys)
{
	this->ValueKeysTextBlock->SetText(FText::FromString(FString::FromInt(NewValueKeys)));
}

