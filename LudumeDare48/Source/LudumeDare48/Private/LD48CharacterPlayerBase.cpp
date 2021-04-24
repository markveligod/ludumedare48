// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/LD48CharacterPlayerBase.h"

#include "LD48GameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/LD48OxygenActorComponent.h"
#include "Public/LD48GameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogLD48CharacterPlayerBase, All, All);

// Sets default values
ALD48CharacterPlayerBase::ALD48CharacterPlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Default spring arm
	this->SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring arm");
	this->SpringArmComponent->SetupAttachment(GetRootComponent());

	//CreateCameraComponent
	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	this->CameraComponent->SetupAttachment(this->SpringArmComponent);

	//create oxygen component
	this->OxygenActorComponent = CreateDefaultSubobject<ULD48OxygenActorComponent>("Oxygen Component");
}

// Called when the game starts or when spawned
void ALD48CharacterPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	check(this->SpringArmComponent);
	check(this->CameraComponent)
	check(GetCharacterMovement());
	check(this->OxygenActorComponent);
	check(GetWorld());

	GetCharacterMovement()->Buoyancy = this->DefaultPowerBuoyancy;
	this->CurrentCountDepth = this->DefaultCountDepth;
	GetWorld()->GetTimerManager().SetTimer(this->TimerHandleDepth, this, &ALD48CharacterPlayerBase::UpdateTimerDepth, this->DefaultRateUpdateDepth, true);
	this->GameMode = Cast<ALD48GameModeBase>(GetWorld()->GetAuthGameMode());
}



// Called every frame
void ALD48CharacterPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALD48CharacterPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("PushRight", IE_Pressed, this, &ALD48CharacterPlayerBase::PushRightMove);
		PlayerInputComponent->BindAction("PushLeft", IE_Pressed, this, &ALD48CharacterPlayerBase::PushLeftMove);
		PlayerInputComponent->BindAction("MoveHold", IE_Pressed, this, &ALD48CharacterPlayerBase::PushUpMove);
		PlayerInputComponent->BindAction("MoveBoost", IE_Pressed, this, &ALD48CharacterPlayerBase::PushDownMove);
	}
	else
	{
		UE_LOG(LogLD48CharacterPlayerBase, Error, TEXT("Player input component is nullptr"));
	}
}

void ALD48CharacterPlayerBase::DecreaseCountKey()
{
	this->CountKeys--;
	//if count keys == 0 win
	if (this->CountDepth == 0)
		this->GameMode->OnDeath.Broadcast();
}

int32 ALD48CharacterPlayerBase::GetCountKeys() const
{
	return (this->CountKeys);
}

int32 ALD48CharacterPlayerBase::GetCountDepth() const
{
	return (this->CountDepth);
}

void ALD48CharacterPlayerBase::PushRightMove()
{
	if (GetCharacterMovement()->IsSwimming())
		AddMovementInput(GetActorRightVector(), this->PowerPush);
}

void ALD48CharacterPlayerBase::PushLeftMove()
{
	if (GetCharacterMovement()->IsSwimming())
		AddMovementInput(GetActorRightVector(), -this->PowerPush);
}

void ALD48CharacterPlayerBase::PushUpMove()
{
	if (!this->bIsBuoyancyDone && GetCharacterMovement()->IsSwimming())
	{
		GetCharacterMovement()->Buoyancy = this->HoldPowerBuoyancy;
		this->bIsBuoyancyDone = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandleBuoyancy, this, &ALD48CharacterPlayerBase::ChangeDefaultBuoyancy, 5.f, false);

		this->CurrentCountDepth = this->HoldCountDepth;
		GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleDepth);
		GetWorld()->GetTimerManager().SetTimer(this->TimerHandleDepth, this, &ALD48CharacterPlayerBase::UpdateTimerDepth, this->HoldRateUpdateDepth, true);

	}
}

void ALD48CharacterPlayerBase::PushDownMove()
{
	if (!this->bIsBuoyancyDone && GetCharacterMovement()->IsSwimming())
	{
		GetCharacterMovement()->Buoyancy = this->BoostPowerBuoyancy;
		this->bIsBuoyancyDone = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandleBuoyancy, this, &ALD48CharacterPlayerBase::ChangeDefaultBuoyancy, 5.f, false);
		this->CurrentCountDepth = this->BoostCountDepth;
		GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleDepth);
		GetWorld()->GetTimerManager().SetTimer(this->TimerHandleDepth, this, &ALD48CharacterPlayerBase::UpdateTimerDepth, this->BoostRateUpdateDepth, true);
	}
}

void ALD48CharacterPlayerBase::ChangeDefaultBuoyancy()
{
	GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleBuoyancy);
	this->bIsBuoyancyDone = false;
	GetCharacterMovement()->Buoyancy = this->DefaultPowerBuoyancy;
	
	this->CurrentCountDepth = this->DefaultCountDepth;
	GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleDepth);
	GetWorld()->GetTimerManager().SetTimer(this->TimerHandleDepth, this, &ALD48CharacterPlayerBase::UpdateTimerDepth, this->DefaultRateUpdateDepth, true);
}

void ALD48CharacterPlayerBase::UpdateTimerDepth()
{
	if (GetCharacterMovement()->IsSwimming())
	{
		this->CountDepth += this->CurrentCountDepth;
		this->OnChangeDepth.Broadcast(this->CountDepth);
	}
}

