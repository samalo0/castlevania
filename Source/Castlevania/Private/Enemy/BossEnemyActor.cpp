//----------------------------------------------------------------------------------------------------------------------
// Copyright 2021 Stephen Maloney
// Owner: Stephen Maloney
// Created: 1/23/2021
//----------------------------------------------------------------------------------------------------------------------

#include "Enemy/BossEnemyActor.h"

#include "Components/BoxComponent.h"
#include "Core/CastlevaniaFunctionLibrary.h"
#include "Core/CastlevaniaGameInstance.h"
#include "Core/CastlevaniaGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/HolyWaterActor.h"
#include "PaperFlipbookComponent.h"

void ABossEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if(IsValid(World))
	{
		if(IsValid(GameMode))
		{
			Pawn = GameMode->GetPlayerPawn();
		}
	}
}

void ABossEnemyActor::HitWithWeapon(const int32 Damage, const bool bPlaySound, const FVector WeaponLocation)
{
	UWorld* World = GetWorld();
	if(!IsValid(World))
	{
		return;
	}

	UCastlevaniaGameInstance* GameInstance = Cast<UCastlevaniaGameInstance>(World->GetGameInstance());
	if(!IsValid(GameInstance))
	{
		return;
	}

	if(World->GetTimeSeconds() < HitCooldown || GameInstance->GetEnemyHealth() <= 0)
	{
		return;
	}

	HitCooldown = World->GetTimeSeconds() + HitCooldownTime;
	
	UGameplayStatics::PlaySound2D(this, HitSound);

	const FVector AverageLocation = (WeaponLocation + GetActorLocation()) / 2.0f;
	const FVector SpawnLocation = UCastlevaniaFunctionLibrary::RoundVectorToInt(FVector(AverageLocation.X, GetActorLocation().Y, AverageLocation.Z));
	SpawnHitEffect(SpawnLocation);

	int32 EnemyHealth = GameInstance->GetEnemyHealth();
	EnemyHealth = FMath::Clamp(EnemyHealth - Damage, 0, 16);;

	GameInstance->SetEnemyHealth(EnemyHealth);
	
	if(EnemyHealth == 0)
	{
		BoxComponent->OnComponentEndOverlap.Clear();
		BoxComponent->OnComponentBeginOverlap.Clear();
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FlipbookComponent->SetLooping(false);
		FlipbookComponent->SetFlipbook(BurnOutFlipbook);
		FlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ABossEnemyActor::OnFinishedPlaying);
		FlipbookComponent->PlayFromStart();
	}
}

void ABossEnemyActor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHolyWaterActor* HolyWater = Cast<AHolyWaterActor>(OtherActor);
	if(IsValid(HolyWater))
	{
		bHolyWaterBurning = false;
		TimeStop(false);
		UWorld* World = GetWorld();
		if(IsValid(World))
		{
			World->GetTimerManager().ClearTimer(HolyWaterTimer);
		}
	}
}

void ABossEnemyActor::OnFinishedPlaying()
{
	if(IsValid(GameMode))
	{
		GameMode->StartLevelCompletion();
	}

	Destroy();
}
