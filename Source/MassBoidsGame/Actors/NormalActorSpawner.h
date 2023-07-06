// Copyright Dennis Andersson. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NormalActorSpawner.generated.h"

UCLASS()
class MASSBOIDSGAME_API ANormalActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANormalActorSpawner();

    UPROPERTY(EditAnywhere, Category = "Spawning")
    TMap<TSubclassOf<class AActor>, int32> ActorsToSpawn;

    UPROPERTY(EditAnywhere, Category = "Spawning")
    FVector SpawnArea;

    UPROPERTY(EditAnywhere, Category = "Movement")
    FVector MovementBoundsMin;

    UPROPERTY(EditAnywhere, Category = "Movement")
    FVector MovementBoundsMax;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MovementSpeed;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float RotationSpeed;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    TArray<AActor*> SpawnedActors;
    TMap<AActor*, float> ActorRotations;
    void SpawnActors();
    void MoveActors(float DeltaTime);
};
