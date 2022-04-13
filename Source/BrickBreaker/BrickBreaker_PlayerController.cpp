// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaker_PlayerController.h"

#include "Brick.h"
#include "Paddle_Pawn.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

ABrickBreaker_PlayerController::ABrickBreaker_PlayerController()
{
	Chances = 3;
}

void ABrickBreaker_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (Brick)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Brick, Bricks);
		BricksRemaining = Bricks.Num();
	}

	LocateCamera();
	SpawnBall();
	AddWidgetUI();
}

void ABrickBreaker_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Instantiate_YouLoose_Widget();
	Instantiate_YouWin_Widget();
}

void ABrickBreaker_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Move Horizontal", this, &ABrickBreaker_PlayerController::MoveHorizontal);
	InputComponent->BindAction("Launch", IE_Pressed ,this, &ABrickBreaker_PlayerController::Launch);
}

void ABrickBreaker_PlayerController::LocateCamera()
{
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);

	const FViewTargetTransitionParams ViewTargetTransitionParams;
	SetViewTarget(CameraActors[0], ViewTargetTransitionParams);
}

void ABrickBreaker_PlayerController::SpawnBall()
{
	if(Ball_Class)
	{
		const FVector BallSpawnLocation = FVector(0, 0, 35);
		const FRotator BallSpawnRotation = FRotator::ZeroRotator;

		Ball = GetWorld()->SpawnActor<ABall>(Ball_Class, BallSpawnLocation, BallSpawnRotation);
	}
}

void ABrickBreaker_PlayerController::MoveHorizontal(float Axis)
{
	APaddle_Pawn* Paddle_Pawn = Cast<APaddle_Pawn>(GetPawn());
	Paddle_Pawn->MoveHorizontal(Axis);
}

void ABrickBreaker_PlayerController::Launch()
{
	if(Ball)
		Ball->Launch();
}

void ABrickBreaker_PlayerController::AddWidgetUI()
{
	if(BrickBreaker_UI_Class)
	{
		BrickBreaker_UI = CreateWidget(this, BrickBreaker_UI_Class);
		BrickBreaker_UI->AddToViewport();
	}
}

void ABrickBreaker_PlayerController::Instantiate_YouWin_Widget()
{
	if(BricksRemaining < 1 && YouWin_UI_Class)
	{
		YouWin_UI = CreateWidget(this, YouWin_UI_Class);
		YouWin_UI->AddToViewport();
		BrickBreaker_UI->RemoveFromViewport();

		if(YouLoose_UI)
		{
			YouLoose_UI->RemoveFromViewport();
		}

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABrickBreaker_PlayerController::RestartGame, 3.0f, false);
	}
}

void ABrickBreaker_PlayerController::Instantiate_YouLoose_Widget()
{
	if (Chances < 1 && YouLoose_UI_Class)
	{
		YouLoose_UI = CreateWidget(this, YouLoose_UI_Class);
		YouLoose_UI->AddToViewport();
		BrickBreaker_UI->RemoveFromViewport();

		if(YouWin_UI)
		{
			YouWin_UI->RemoveFromViewport();
		}

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABrickBreaker_PlayerController::RestartGame, 3.0f, false);
	}
}

void ABrickBreaker_PlayerController::RestartGame() const
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(GetWorld()->GetName()));
}
