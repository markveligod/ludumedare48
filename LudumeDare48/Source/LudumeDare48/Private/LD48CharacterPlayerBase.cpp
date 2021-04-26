// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/LD48CharacterPlayerBase.h"

#include "LD48GameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/LD48OxygenActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Items/LD48BaseItemsActor.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

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

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ALD48CharacterPlayerBase::OnOverlapComponent);

	//Create for socket
	this->FirstStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Top");
	this->SecondStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Middle");
	this->ThirdStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Low");
	this->FourStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Four");

	
}

void ALD48CharacterPlayerBase::SetIsDeadTrue()
{
	this->IsDead = true;
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

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);

	this->FirstStaticMesh->SetSimulatePhysics(false);
	this->FirstStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->FirstStaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	this->FirstStaticMesh->AttachToComponent(GetMesh(), AttachmentRules, this->SocketFirstName);

	this->SecondStaticMesh->SetSimulatePhysics(false);
	this->SecondStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->SecondStaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	this->SecondStaticMesh->AttachToComponent(GetMesh(), AttachmentRules, this->SocketSecondName);

	this->ThirdStaticMesh->SetSimulatePhysics(false);
	this->ThirdStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->ThirdStaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	this->ThirdStaticMesh->AttachToComponent(GetMesh(), AttachmentRules, this->SocketThirdName);

	this->FourStaticMesh->SetSimulatePhysics(false);
	this->FourStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->FourStaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	this->FourStaticMesh->AttachToComponent(GetMesh(), AttachmentRules, this->SocketFourName);

	this->StartLocationX = GetActorLocation().X;
	this->StartLocationZ = GetActorLocation().Z;
	GetCharacterMovement()->Buoyancy = this->DefaultPowerBuoyancy;
	GetWorld()->GetTimerManager().SetTimer(this->TimerHandleDepth, this, &ALD48CharacterPlayerBase::UpdateTimerDepth, this->DefaultRateUpdateDepth, true);
	this->GameMode = Cast<ALD48GameModeBase>(GetWorld()->GetAuthGameMode());
	this->OnChangeOxygen.Broadcast(this->OxygenActorComponent->GetCurrentOxygen());
	this->OnChangeKeys.Broadcast(this->CountKeys);
	this->GameMode->OnGameState.AddUObject(this, &ALD48CharacterPlayerBase::UpdateCaScene);
	GetWorld()->GetTimerManager().SetTimer(this->TimerHandleEnv, this, &ALD48CharacterPlayerBase::RandomPlayEnv, 5.f, true);
	
}



// Called every frame
void ALD48CharacterPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->bIsKeyZero)
	{

		auto CurrentLocationThird = this->ThirdStaticMesh->GetRelativeLocation();
		auto CurrentLocationFour = this->FourStaticMesh->GetRelativeLocation();
		CurrentLocationThird.Z += (-150.f * DeltaTime);
		CurrentLocationFour.Z += (-150.f * DeltaTime);
		this->ThirdStaticMesh->SetRelativeLocation(CurrentLocationThird);
		this->FourStaticMesh->SetRelativeLocation(CurrentLocationFour);
	}
  if (GetActorLocation().X != this->StartLocationX)
  {
	  auto CurrentLocal = GetActorLocation();
	  CurrentLocal.X = this->StartLocationX;
	  SetActorLocation(CurrentLocal);
  }
}

// Called to bind functionality to input
void ALD48CharacterPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("MoveHold", IE_Pressed, this, &ALD48CharacterPlayerBase::PushUpMove);
		PlayerInputComponent->BindAction("MoveBoost", IE_Pressed, this, &ALD48CharacterPlayerBase::PushDownMove);
		PlayerInputComponent->BindAxis("MoveRight", this, &ALD48CharacterPlayerBase::RightMove);
	}
	else
	{
		UE_LOG(LogLD48CharacterPlayerBase, Error, TEXT("Player input component is nullptr"));
	}
}

void ALD48CharacterPlayerBase::DecreaseCountKey()
{
	this->CountKeys--;
	this->FreeStaticMesh(this->CountKeys);
	this->OnChangeKeys.Broadcast(this->CountKeys);
	//if count keys == 0 win
	if (this->CountKeys == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleDepth);
		GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleBuoyancy);
		this->CameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		GetCharacterMovement()->Buoyancy = 1.1f;
		this->bIsKeyZero = true;
		this->GameMode->OnDeath.Broadcast();

	}
}

int32 ALD48CharacterPlayerBase::GetCountKeys() const
{
	return (this->CountKeys);
}

int32 ALD48CharacterPlayerBase::GetCountDepth() const
{
	return (this->CountDepth);
}

void ALD48CharacterPlayerBase::CallChangeOxygen(float Amount)
{
	this->OxygenActorComponent->AppEndOxygen(Amount);
}

void ALD48CharacterPlayerBase::RightMove(float Amount)
{
	if (Amount == 0 || this->IsDead)
		return;
	if (GetCharacterMovement()->IsSwimming())
		AddMovementInput(GetActorRightVector(), Amount);
	this->bIsPushing = true;
}

void ALD48CharacterPlayerBase::PushUpMove()
{
	if (!this->bIsBuoyancyDone && GetCharacterMovement()->IsSwimming() && !this->IsDead)
	{
		GetCharacterMovement()->Buoyancy = this->HoldPowerBuoyancy;
		this->bIsBuoyancyDone = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandleBuoyancy, this, &ALD48CharacterPlayerBase::ChangeDefaultBuoyancy, 5.f, false);

	}

}

void ALD48CharacterPlayerBase::PushDownMove()
{
	if (!this->bIsBuoyancyDone && GetCharacterMovement()->IsSwimming() && !this->IsDead)
	{
		GetCharacterMovement()->Buoyancy = this->BoostPowerBuoyancy;
		this->bIsBuoyancyDone = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandleBuoyancy, this, &ALD48CharacterPlayerBase::ChangeDefaultBuoyancy, 2.f, false);
	}
}

void ALD48CharacterPlayerBase::ChangeDefaultBuoyancy()
{
	GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleBuoyancy);
	this->bIsBuoyancyDone = false;
	GetCharacterMovement()->Buoyancy = this->DefaultPowerBuoyancy;
}

void ALD48CharacterPlayerBase::UpdateTimerDepth()
{
	if (GetCharacterMovement()->IsSwimming())
	{
		this->CountDepth = (this->StartLocationZ - GetActorLocation().Z) / 100;
		this->OnChangeDepth.Broadcast(this->CountDepth);
	}
}

void ALD48CharacterPlayerBase::UpdateCaScene(EGameState NewState)
{
	if(NewState == EGameState::Welcome)
	{
		GetCharacterMovement()->Buoyancy = 1.f;
	}
	else if (NewState == EGameState::InProgress)
	{
		GetCharacterMovement()->Buoyancy = this->DefaultPowerBuoyancy;
	}
}

void ALD48CharacterPlayerBase::FreeStaticMesh(int Key)
{
	if (Key == 2)
	{
		this->FirstStaticMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	}
	else if (Key == 1)
	{
		this->SecondStaticMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	}
	else if (Key == 0)
	{
		this->ThirdStaticMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		this->FourStaticMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	}
}

void ALD48CharacterPlayerBase::RandomPlayEnv()
{
	UGameplayStatics::PlaySound2D(GetWorld(), this->EnvSound);
}

void ALD48CharacterPlayerBase::OnOverlapComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto TempItem = Cast<ALD48BaseItemsActor>(OtherActor);
	if (TempItem)
	{
		if (TempItem->bIsKey)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), this->KeySound);
			DecreaseCountKey();
		}
		else if (TempItem->bIsOxygen)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), this->OxygenSound);
			CallChangeOxygen(TempItem->HealValueOxygen);
		}
		else if (TempItem->bIsOther)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), this->BoomSound);
			CallChangeOxygen(-TempItem->DamageValueOxygen);
		}
		else
		{
			UE_LOG(LogLD48CharacterPlayerBase, Error, TEXT("bool variable is all false"))
		}
		TempItem->Destroy();
	}
	else
	{
		UE_LOG(LogLD48CharacterPlayerBase, Error, TEXT("Character is nullptr"));
	}

}

