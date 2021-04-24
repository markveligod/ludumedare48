// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LD48BaseItemsActor.h"
#include "Components/StaticMeshComponent.h"
#include "Public/LD48CharacterPlayerBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogLD48BaseItemsActor, All, All);

// Sets default values
ALD48BaseItemsActor::ALD48BaseItemsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create static mesh components
	this->StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	this->StaticMeshComponent->SetupAttachment(GetRootComponent());
	this->StaticMeshComponent->OnComponentHit.AddDynamic(this, &ALD48BaseItemsActor::OnHitActor);
}

// Called when the game starts or when spawned
void ALD48BaseItemsActor::BeginPlay()
{
	Super::BeginPlay();
	check(this->StaticMeshComponent);
}

void ALD48BaseItemsActor::OnHitActor(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const auto TempCharacter = Cast<ALD48CharacterPlayerBase>(OtherActor);
	if (TempCharacter)
	{
		if (this->bIsKey)
		{
			
		}
		else if (this->bIsOxygen)
		{
			
		}
		else if (this->bIsOther)
		{
			
		}
		else
		{
			UE_LOG(LogLD48BaseItemsActor, Error, TEXT("bool variable is all false"))
		}
	}
	else
	{
		UE_LOG(LogLD48BaseItemsActor, Error, TEXT("Character is nullptr"));
	}
}

// Called every frame
void ALD48BaseItemsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

