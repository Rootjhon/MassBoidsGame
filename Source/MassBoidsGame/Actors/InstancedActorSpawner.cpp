// Copyright Dennis Andersson. All Rights Reserved.


#include "MoveActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Actors/InstancedActorSpawner.h"

// Sets default values
AInstancedActorSpawner::AInstancedActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInstancedActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnActors();
}

// Called every frame
void AInstancedActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveActors(DeltaTime);
}

void AInstancedActorSpawner::SpawnActors()
{
    for (const auto& ActorEntry : ActorsToSpawn)
    {
        TSubclassOf<AActor> ActorClass = ActorEntry.Key;
        int32 NumberOfActors = ActorEntry.Value;

        if (!ActorClass) continue;
		AMoveActor* SpawnedActor = GetWorld()->SpawnActor<AMoveActor>(ActorClass, FVector::ZeroVector, FRotator::ZeroRotator);

        if (!SpawnedActor->InstancedStaticMesh) continue;

        TArray<FTransform> tempInsTRS;
        for (int32 i = 0; i < NumberOfActors; ++i)
        {
            FTransform tempVal = FTransform::Identity;
            tempVal.SetLocation(GetActorLocation() + UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, SpawnArea));
            tempInsTRS.Add(tempVal);
        }

		SpawnedActors.Emplace(SpawnedActor, tempInsTRS);
		SpawnedActor->InstancedStaticMesh->AddInstances(tempInsTRS, false, false);
    }
}

void AInstancedActorSpawner::MoveActors(float DeltaTime)
{
    TArray<AMoveActor*> tempInsActors;
    TArray<FTransform*> tempTrans;

    for (auto&& PairIt : SpawnedActors)
    {
        tempInsActors.Add(PairIt.Key);

		for (FTransform& tempV : PairIt.Value)
        {
			tempTrans.Add(&tempV);
        }
    }

	ParallelFor(tempTrans.Num(), [this, &tempTrans, &DeltaTime](int32 Ndx)
        {
            FTransform* tempTran = tempTrans[Ndx];

            FVector ForwardVector = tempTran->GetRotation().Rotator().Vector();

            FVector NewLocation = tempTran->GetLocation() + ForwardVector * MovementSpeed * DeltaTime;

            if (NewLocation.X < MovementBoundsMin.X || NewLocation.X > MovementBoundsMax.X ||
                NewLocation.Y < MovementBoundsMin.Y || NewLocation.Y > MovementBoundsMax.Y ||
                NewLocation.Z < MovementBoundsMin.Z || NewLocation.Z > MovementBoundsMax.Z)
            {
                float CurrentRotation = tempTran->GetRotation().Y;
                CurrentRotation += RotationSpeed;
                tempTran->SetRotation(FRotator(0, CurrentRotation, 0).Quaternion());
            }
            else
            {
                tempTran->SetLocation(NewLocation);
            }
        });

	for (AMoveActor* tempMoveActor : tempInsActors)
    {
        if (!tempMoveActor->InstancedStaticMesh) continue;

        tempMoveActor->InstancedStaticMesh->BatchUpdateInstancesTransforms(
            0,
            SpawnedActors[tempMoveActor],
            true,
            true,
            true
        );
    }
}

