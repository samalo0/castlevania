//----------------------------------------------------------------------------------------------------------------------
// Copyright 2021 Stephen Maloney
// Owner: Stephen Maloney
// Created: 1/16/2021
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatformActor.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;

UCLASS(HideCategories = (Replication, Rendering, Actor, Input, LOD, Cooking))
class CASTLEVANIA_API AMovingPlatformActor : public AActor
{

	GENERATED_BODY()
	
public:	

	AMovingPlatformActor();

	virtual void Tick(float DeltaSeconds) override;
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OnStageChanged(int32& Stage);
	
	UPROPERTY(Transient, VisibleInstanceOnly)
	float Acceleration;

	// The stage in which the platform is active. This prevents it from ticking when it is in the world but the player
	// is not currently at that stage.
	UPROPERTY(EditInstanceOnly)
	int32 ActiveStage = 3;
	
	UPROPERTY(VisibleInstanceOnly)
	bool bHeadingRight = false;
	
	UPROPERTY(Transient, VisibleInstanceOnly)
	FVector InitialWorldLocation;

	UPROPERTY(Transient, VisibleInstanceOnly)
	float MaximumVelocity = 32.0f;

	UPROPERTY(VisibleInstanceOnly)
	bool bSecondaryIsOnRight = false;
	
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FTransform SecondaryRelativeTransform;

	UPROPERTY(Transient, VisibleInstanceOnly)
	FVector SecondaryWorldLocation;

	UPROPERTY(EditAnywhere)
	float TurnAroundDistance = 8.0f;
	
	UPROPERTY(EditAnywhere)
	float TurnAroundTime = 0.5f;

	UPROPERTY(VisibleInstanceOnly)
	float Velocity = 0.0f;
	
#pragma region Components

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootSceneComponent;
	
#pragma endregion
	
};

