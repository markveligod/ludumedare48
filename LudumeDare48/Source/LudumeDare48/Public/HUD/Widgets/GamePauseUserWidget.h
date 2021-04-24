// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePauseUserWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API UGamePauseUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UButton* ContinueButton;
	UPROPERTY(meta = (BindWidget))
		UButton* MainMenuButton;
private:
	UFUNCTION()
		void CallContinueGame();

	UFUNCTION()
		void CallMainMenu();
};
