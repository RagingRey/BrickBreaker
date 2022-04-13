// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(false);

	this->RootComponent = MeshComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(MeshComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->Bounciness = 1.0f;

	bIsLaunched = false;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::Launch()
{
	if(!bIsLaunched)
	{
		MeshComponent->AddImpulse(FVector(130.0f, 0.0f, 250.0f));
		bIsLaunched = true;
	}
}
