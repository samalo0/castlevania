//----------------------------------------------------------------------------------------------------------------------
// Copyright 2019 Stephen Maloney
// Owner: Stephen Maloney
// Created: 12/22/2020
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"

#include "CastlevaniaPawn.h"
#include "Camera/CameraActor.h"
#include "CastlevaniaCameraActor.generated.h"

UCLASS()
class CASTLEVANIA_API ACastlevaniaCameraActor : public ACameraActor
{

	GENERATED_BODY()

public:

	ACastlevaniaCameraActor();
	
	FORCEINLINE UBoxComponent* GetBoxComponent() const { return BoxComponent; }
	
	FVector GetCameraViewportExtent() const;

	bool IsLocationInViewport(FVector Location) const;
	
	void SetMinimumAndMaximumX(float MinX, float MaxX);
	
protected:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(Transient, VisibleInstanceOnly)
	ACastlevaniaPawn* Pawn;

	UPROPERTY(EditAnywhere)
	bool bIgnoreMinAndMaxAndTrackPlayer = false;
	
	UPROPERTY(EditAnywhere)
	float MinimumX = 120.0f;

	UPROPERTY(EditAnywhere)
	float MaximumX = 2000.0f;
	
};
