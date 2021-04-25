// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/LD48DataTypes.h"
#include "LD48CharacterPlayerBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULD48OxygenActorComponent;
class ALD48GameModeBase;

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
	int32 GetCountDepth() const;

	void CallChangeOxygen(float Amount);

	FOnChangeOxygen OnChangeOxygen;
	FOnChangeDepth OnChangeDepth;
	FOnChangeKeys OnChangeKeys;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		ULD48OxygenActorComponent* OxygenActorComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Editor")
		float PowerPush = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buoyancy Editor")
		float DefaultPowerBuoyancy = 0.8f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buoyancy Editor")
		float BoostPowerBuoyancy = 0.7f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buoyancy Editor")
		float HoldPowerBuoyancy = 0.9f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Depth Editor")
		float DefaultRateUpdateDepth = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Depth Editor")
		float BoostRateUpdateDepth = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Depth Editor")
		float HoldRateUpdateDepth = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Depth Editor")
		int32 DefaultCountDepth = 4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Depth Editor")
		int32 HoldCountDepth = 2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Depth Editor")
		int32 BoostCountDepth = 6;
		


private:
	int32 CountKeys = 3;
	int32 CountDepth = 0;
	int32 CurrentCountDepth;
	bool bIsBuoyancyDone = false;
	FTimerHandle TimerHandleBuoyancy;
	FTimerHandle TimerHandleDepth;
	ALD48GameModeBase* GameMode;
	
	void PushRightMove();
	void PushLeftMove();
	void PushUpMove();
	void PushDownMove();
	void ChangeDefaultBuoyancy();
	void UpdateTimerDepth();

	UFUNCTION()
		void OnOverlapComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
