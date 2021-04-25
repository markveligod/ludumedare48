// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LD48OxygenActorComponent.h"

#include "Camera/CameraComponent.h"
#include "Public/LD48CharacterPlayerBase.h"
#include "Public/LD48GameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogLD48OxygenComponent, All, All);

// Sets default values for this component's properties
ULD48OxygenActorComponent::ULD48OxygenActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void ULD48OxygenActorComponent::BeginPlay()
{
	Super::BeginPlay();

	check(GetWorld());
	
	this->CurrentOxygen = this->DefaultOxygen;
	GetWorld()->GetTimerManager().SetTimer(TimerHandleOxygen, this, &ULD48OxygenActorComponent::DecreaseOxygen, this->DecreaseOxygenRateTime, true);
	this->GameMode = Cast<ALD48GameModeBase>(GetWorld()->GetAuthGameMode());
	check(this->GameMode);
	
}

void ULD48OxygenActorComponent::AppEndOxygen(float Amount)
{
	this->CurrentOxygen = FMath::Clamp(this->CurrentOxygen + Amount, 0.f, this->DefaultOxygen);
	const auto TempCharacter = Cast<ALD48CharacterPlayerBase>(GetOwner());
	if (TempCharacter)
		TempCharacter->OnChangeOxygen.Broadcast(this->CurrentOxygen);
	else
		UE_LOG(LogLD48OxygenComponent, Error, TEXT("Character is nullptr"));
	//if current oxygen == 0 is death
	if (this->CurrentOxygen == 0)
	{
		this->GameMode->OnDeath.Broadcast();
		GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleOxygen);
	}

}

float ULD48OxygenActorComponent::GetCurrentOxygen() const
{
	return (this->CurrentOxygen);
}

void ULD48OxygenActorComponent::DecreaseOxygen()
{
	this->CurrentOxygen = FMath::Clamp(this->CurrentOxygen - this->ExpenseOxygen, 0.f, this->DefaultOxygen);
	const auto TempCharacter = Cast<ALD48CharacterPlayerBase>(GetOwner());
	if (TempCharacter)
		TempCharacter->OnChangeOxygen.Broadcast(this->CurrentOxygen);
	else
		UE_LOG(LogLD48OxygenComponent, Error, TEXT("Character is nullptr"));
	//if current oxygen == 0 is death
	if (this->CurrentOxygen == 0)
	{
		TempCharacter->CameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		this->GameMode->OnDeath.Broadcast();
		GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleOxygen);
	}
}



