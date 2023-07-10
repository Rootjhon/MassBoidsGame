// Copyright Dennis Andersson. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstancedActorSpawner.generated.h"

UCLASS()
class MASSBOIDSGAME_API AInstancedActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInstancedActorSpawner();

    UPROPERTY(EditAnywhere, Category = "Spawning")
    TMap<TSubclassOf<class AMoveActor>, int32> ActorsToSpawn;

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
    TMap<class AMoveActor*, TArray<FTransform>> SpawnedActors;
    TMap<class AMoveActor*, float> ActorRotations;
    void SpawnActors();
    void MoveActors(float DeltaTime);

};
