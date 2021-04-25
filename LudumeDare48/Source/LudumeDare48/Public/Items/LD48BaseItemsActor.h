// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LD48BaseItemsActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class LUDUMEDARE48_API ALD48BaseItemsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALD48BaseItemsActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (ClampMin = "0.1", ClampMax = "100.0"))
		float PowerRotator = 50.f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Status Editor")
		bool bIsKey = false;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Status Editor")
		bool bIsOxygen = false;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Status Editor", meta = (EditCondition = "bIsOxygen", ClampMin = "0.1", ClampMax = "50.0"))
		float HealValueOxygen = 25.f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Status Editor")
		bool bIsOther = false;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Status Editor", meta = (EditCondition = "bIsOther", ClampMin = "0.1", ClampMax = "50.0"))
		float DamageValueOxygen = 10.f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

private:

};
