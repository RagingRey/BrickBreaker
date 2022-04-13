// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle_Pawn.h"

// Sets default values
APaddle_Pawn::APaddle_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetEnableGravity(false);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionProfileName(TEXT("Pawn"));

	this->RootComponent = MeshComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(MeshComponent);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	PawnMovement->MaxSpeed = 500.0f;
}

// Called when the game starts or when spawned
void APaddle_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaddle_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APaddle_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APaddle_Pawn::MoveHorizontal(float Axis)
{
	const FVector Direction(1.0f, 0, 0);
	AddMovementInput(Direction, Axis);
}