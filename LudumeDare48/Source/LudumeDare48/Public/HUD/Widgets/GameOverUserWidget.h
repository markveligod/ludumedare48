// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUserWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API UGameOverUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UButton* MainMenuButton;
private:
	UFUNCTION()
	void OnExitLevel();
};
