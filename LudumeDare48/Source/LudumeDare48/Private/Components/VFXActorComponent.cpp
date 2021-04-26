// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VFXActorComponent.h"
#include "NiagaraFunctionLibrary.h"


void UVFXActorComponent::PlayVFXboom(FVector Location)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), this->EffectBoom, Location);
}
