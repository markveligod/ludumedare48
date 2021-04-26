// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUserWidget.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API UGameOverUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetNewTotal(FString NewTotal);
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TotalTextBlock;
	
private:
	UFUNCTION()
	void OnExitLevel();
};
