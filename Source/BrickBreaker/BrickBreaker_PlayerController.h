// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "Brick.h"
#include "GameFramework/PlayerController.h"
#include "BrickBreaker_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BRICKBREAKER_API ABrickBreaker_PlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	ABrickBreaker_PlayerController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Brick)
		TSubclassOf<ABrick> Brick;
	TArray<AActor*> Bricks;

	UPROPERTY(EditDefaultsOnly, Category = Ball)
		TSubclassOf<ABall> Ball_Class;
	TObjectPtr<ABall> Ball;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUserWidget> BrickBreaker_UI_Class;
	TObjectPtr<UUserWidget> BrickBreaker_UI;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUserWidget> YouWin_UI_Class;
	TObjectPtr<UUserWidget> YouWin_UI;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUserWidget> YouLoose_UI_Class;
	TObjectPtr<UUserWidget> YouLoose_UI;

	UFUNCTION()
		virtual void SetupInputComponent() override;

	void LocateCamera();
	void MoveHorizontal(float Axis);
	void Launch();
	void AddWidgetUI();
	
	void RestartGame() const;

public:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int Chances;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int BricksRemaining;

	void SpawnBall();
	void Instantiate_YouWin_Widget();
	void Instantiate_YouLoose_Widget();
};
