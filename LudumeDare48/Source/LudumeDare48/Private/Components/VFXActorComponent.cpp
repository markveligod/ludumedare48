// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VFXActorComponent.h"
#include "NiagaraFunctionLibrary.h"


void UVFXActorComponent::PlayVFXBoom(FVector Location)
{
	this->PlayVFXAnim(this->EffectBoom, Location);
}

void UVFXActorComponent::PlayVFXBubble(FVector Location)
{
	this->PlayVFXAnim(this->EffectBubble, Location);
}

void UVFXActorComponent::PlayVFXKeys(FVector Location)
{
	this->PlayVFXAnim(this->EffectKeys, Location);
}

void UVFXActorComponent::PlayVFXAnim(UNiagaraSystem* Effect, FVector Location)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Location);
}

