// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Public/LD48DataTypes.h"
#include "LD48PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API ALD48PlayerHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHudWidgetClass;

    virtual void BeginPlay() override;
private:
    UPROPERTY()
        TMap<EGameState, UUserWidget*> GameWidgets;

    UPROPERTY()
        UUserWidget* CurrentWidget;

    void OnStateChanged(EGameState NewState);
};
