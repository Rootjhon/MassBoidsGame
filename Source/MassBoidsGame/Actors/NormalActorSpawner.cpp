// Copyright Dennis Andersson. All Rights Reserved.


#include "Actors/NormalActorSpawner.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ANormalActorSpawner::ANormalActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANormalActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnActors();
	
}

// Called every frame
void ANormalActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ANormalActorSpawner::SpawnActors()
{
    for (const auto& ActorEntry : ActorsToSpawn)
    {
        TSubclassOf<AActor> ActorClass = ActorEntry.Key;
        int32 NumberOfActors = ActorEntry.Value;

        if (!ActorClass) continue;

        for (int32 i = 0; i < NumberOfActors; ++i)
        {
            FVector SpawnLocation = GetActorLocation() + UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, SpawnArea);
            FRotator SpawnRotation = FRotator::ZeroRotator;

            AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass, SpawnLocation, SpawnRotation);
            if (SpawnedActor)
            {
                SpawnedActors.Add(SpawnedActor);
                ActorRotations.Add(SpawnedActor, 0.0f);
            }
        }
    }
}

void ANormalActorSpawner::MoveActors(float DeltaTime)
{
    for (AActor* Actor : SpawnedActors)
    {
        if (Actor)
        {
            FVector NewLocation = Actor->GetActorLocation() + Actor->GetActorForwardVector() * MovementSpeed * DeltaTime;

            if (NewLocation.X < MovementBoundsMin.X || NewLocation.X > MovementBoundsMax.X ||
                NewLocation.Y < MovementBoundsMin.Y || NewLocation.Y > MovementBoundsMax.Y ||
                NewLocation.Z < MovementBoundsMin.Z || NewLocation.Z > MovementBoundsMax.Z)
            {
                float& CurrentRotation = ActorRotations[Actor];
                CurrentRotation += RotationSpeed * DeltaTime;
                Actor->SetActorRotation(FRotator(0, CurrentRotation, 0));
            }
            else
            {
                Actor->SetActorLocation(NewLocation);
            }
        }
    }
}

