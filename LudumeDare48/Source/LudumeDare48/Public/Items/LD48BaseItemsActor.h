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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Status Editor")
		bool bIsKey = false;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Status Editor")
		bool bIsOxygen = false;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Status Editor", meta = (EditCondition = "bIsOxygen"))
		float HealValueOxygen = 25.f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Status Editor")
		bool bIsOther = false;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Status Editor", meta = (EditCondition = "bIsOther"))
		float DamageValueOxygen = 10.f;


private:
	UFUNCTION()
	void OnHitActor(UPrimitiveComponent* HitComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	

};
