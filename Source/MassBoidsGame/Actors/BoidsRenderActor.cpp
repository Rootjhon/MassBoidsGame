// Copyright Dennis Andersson. All Rights Reserved.


#include "BoidsRenderActor.h"

// Engine
#include "Components/InstancedStaticMeshComponent.h"
#include "MassAgentComponent.h"

ABoidsRenderActor::ABoidsRenderActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	SetRootComponent(SceneRootComponent);
}

void ABoidsRenderActor::CreateNewRenderComponent(const FBoidsMeshFragment* MeshFragment)
{
	if (MeshFragment)
	{
		UStaticMesh* tempMesh = MeshFragment->BoidMesh;
		if (!RenderComponents.Contains(tempMesh))
		{
			UInstancedStaticMeshComponent* Component = NewObject<UInstancedStaticMeshComponent>(this);
			Component->SetStaticMesh(tempMesh);
			Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Component->SetupAttachment(GetRootComponent());
			Component->RegisterComponent();
			RenderComponents.Emplace(tempMesh, Component);
		}
	}
}

UInstancedStaticMeshComponent* ABoidsRenderActor::GetRenderComponent(const FBoidsMeshFragment* MeshFragment)
{
	if (MeshFragment)
	{
		UStaticMesh* tempMesh = MeshFragment->BoidMesh;
		if (RenderComponents.Contains(tempMesh))
		{
			UInstancedStaticMeshComponent* Component = RenderComponents[tempMesh];
			return Component;
		}
	}

	return nullptr;
}
