// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Public/LD48DataTypes.h"
#include "LD48PlayerHUD.generated.h"

class UMediaSoundComponent;
/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API ALD48PlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool GetIsWelcome() const;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHudWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> WelcomeHudWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameOverWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GamePauseWidgetClass;
	

    virtual void BeginPlay() override;
private:
	bool bIsWelcome = false;
    UPROPERTY()
        TMap<EGameState, UUserWidget*> GameWidgets;

    UPROPERTY()
        UUserWidget* CurrentWidget;

	void OnStateChanged(EGameState NewState);
};
