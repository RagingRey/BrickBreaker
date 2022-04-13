// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBound.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABallBound::ABallBound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	this->RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void ABallBound::BeginPlay()
{
	Super::BeginPlay();

	this->BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABallBound::OnBeginOverlap);

	PlayerController = Cast<ABrickBreaker_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void ABallBound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallBound::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Ball"))
	{
		SpawnNewBall();
	}
}

void ABallBound::SpawnNewBall()
{
	if(PlayerController->Chances > 0)
	{
		PlayerController->SpawnBall();
		PlayerController->Chances--;
	}
}