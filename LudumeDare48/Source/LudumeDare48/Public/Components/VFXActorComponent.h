// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VFXActorComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUDUMEDARE48_API UVFXActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void PlayVFXboom(FVector Location);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* EffectBoom;
};
