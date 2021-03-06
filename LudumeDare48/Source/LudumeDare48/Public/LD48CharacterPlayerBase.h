// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/LD48DataTypes.h"
#include "LD48CharacterPlayerBase.generated.h"

class USoundCue;
class UCameraComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class ULD48OxygenActorComponent;
class ALD48GameModeBase;
class UVFXActorComponent;

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
	UFUNCTION(BlueprintCallable)
	int32 GetCountKeys() const;
	int32 GetCountDepth() const;

	UPROPERTY(BlueprintReadWrite)
	bool bIsPushing = false;

	void CallChangeOxygen(float Amount);

	FOnChangeOxygen OnChangeOxygen;
	FOnChangeDepth OnChangeDepth;
	FOnChangeKeys OnChangeKeys;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		UVFXActorComponent* VFXComponent;
	FTimerHandle TimerHandleBuoyancy;
	FTimerHandle TimerHandleDepth;
	void SetIsDeadTrue();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* FirstStaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* SecondStaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* ThirdStaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* FourStaticMesh;
	
	
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
		float DefaultRateUpdateDepth = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
		FName SocketFirstName = "FirstSocket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
		FName SocketSecondName = "SecondSocket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
		FName SocketThirdName = "ThirdSocket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
		FName SocketFourName = "FourSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* BoomSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* KeySound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* OxygenSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* EnvSound;



private:
	bool IsDead = false;
	int32 CountKeys = 3;
	bool bIsKeyZero = false;
	float CountDepth = 0.f;
	bool bIsBuoyancyDone = false;	
	ALD48GameModeBase* GameMode;

	FTimerHandle TimerHandleEnv;

	float StartLocationX;
	float StartLocationZ;

	void RightMove(float Amount);
	void PushUpMove();
	void PushDownMove();
	void ChangeDefaultBuoyancy();
	void UpdateTimerDepth();
	void UpdateCaScene(EGameState NewState);

	void FreeStaticMesh(int32 Key);

	void RandomPlayEnv();
	
	UFUNCTION()
		void OnOverlapComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
