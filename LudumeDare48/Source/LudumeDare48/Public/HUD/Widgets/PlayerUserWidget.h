// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUserWidget.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API UPlayerUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* OxygenProgressBar;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* OxygenValueTextBlock;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* DepthValueTextBlock;

	virtual void NativeOnInitialized() override;

private:
	void UpdateProgressBarOxygen(float NewValueOxygen);
	void UpdateDepthValue(int32 NewValueDepth);
};


