// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrickBreaker_PlayerController.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BallBound.generated.h"

UCLASS()
class BRICKBREAKER_API ABallBound : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallBound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* BoxComponent;

	TObjectPtr<ABrickBreaker_PlayerController> PlayerController;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SpawnNewBall();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};