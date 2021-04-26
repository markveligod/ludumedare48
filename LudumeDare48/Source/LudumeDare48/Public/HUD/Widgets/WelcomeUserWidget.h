// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WelcomeUserWidget.generated.h"

class ALD48CharacterPlayerBase;
/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API UWelcomeUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void CallGameStateInprogress();
};
