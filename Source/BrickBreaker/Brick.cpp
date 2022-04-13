// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"

#include "BrickBreaker_PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetEnableGravity(false);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionProfileName(TEXT("Pawn"));

	this->RootComponent = MeshComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();

	this->BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABrick::OnBeginOverlap);

	PlayerController = Cast<ABrickBreaker_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrick::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Ball"))
	{
		FTimerHandle DestroyBrick_TimeHandle;
		GetWorldTimerManager().SetTimer(DestroyBrick_TimeHandle, this, &ABrick::DestroyBrick, 0.1f, false);
	}
}

void ABrick::DestroyBrick()
{
	this->Destroy();
	PlayerController->BricksRemaining--;
}