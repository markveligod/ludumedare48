// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/LD48DataTypes.h"
#include "LD48CharacterPlayerBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULD48OxygenActorComponent;


UCLASS()
class LUDUMEDARE48_API ALD48CharacterPlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALD48CharacterPlayerBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DecreaseCountKey();
	int32 GetCountKeys() const;

	FOnChangeOxygen OnChangeOxygen;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		ULD48OxygenActorComponent* OxygenActorComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power Editor")
		float PowerPush = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power Editor")
		float DefaultPowerBuoyancy = 0.8f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power Editor")
		float BoostPowerBuoyancy = 0.7f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power Editor")
		float HoldPowerBuoyancy = 0.9f;

private:
	int32 CountKeys = 3;
	bool bIsBuoyancyDone = false;
	FTimerHandle TimerHandleBuoyancy;
	
	void PushRightMove();
	void PushLeftMove();
	void PushUpMove();
	void PushDownMove();
	void ChangeDefaultBuoyancy();
};
