// Copyright Dennis Andersson. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fragments/BoidsMeshFragment.h"
#include "BoidsRenderActor.generated.h"

class UInstancedStaticMeshComponent;
class UMassAgentComponent;
class UStaticMeshComponent;

/**
 * Actor responsible for Instanced Rendering of the Boids
 */
UCLASS()
class MASSBOIDSGAME_API ABoidsRenderActor : public AActor
{
	GENERATED_BODY()

public:

	/**
	 * Instanced StaticMesh Component that renders all the boids
	 */
	TMap<const UStaticMesh*, UInstancedStaticMeshComponent*> RenderComponents;
	
	ABoidsRenderActor(const FObjectInitializer& ObjectInitializer);

	void CreateNewRenderComponent(const FBoidsMeshFragment* MeshFragment);
	//UInstancedStaticMeshComponent* GetRenderComponent(const FBoidsMeshFragment* MeshFragment);
	UInstancedStaticMeshComponent* GetRenderComponent(const FBoidsMeshFragment* MeshFragment);
	
};
