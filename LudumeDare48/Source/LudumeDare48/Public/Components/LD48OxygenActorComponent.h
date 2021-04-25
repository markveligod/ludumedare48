// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Public/LD48DataTypes.h"
#include "LD48OxygenActorComponent.generated.h"

class ALD48GameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUDUMEDARE48_API ULD48OxygenActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULD48OxygenActorComponent();
	void AppEndOxygen(float Amount);
	float GetCurrentOxygen() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Oxygen Editor");
	float DefaultOxygen = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Oxygen Editor")
	float ExpenseOxygen = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Oxygen Editor")
	float DecreaseOxygenRateTime = 1.f;

	

private:
	ALD48GameModeBase* GameMode;
	float CurrentOxygen;
	FTimerHandle TimerHandleOxygen;

	void DecreaseOxygen();
};
