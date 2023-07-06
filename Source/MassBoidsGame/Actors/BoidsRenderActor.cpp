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
	if (MeshFragment && MeshFragment->BoidMesh->HasValidRenderData(false) && !RenderComponents.Contains(MeshFragment->BoidMesh))
	{
		UInstancedStaticMeshComponent* Component = NewObject<UInstancedStaticMeshComponent>(this);
		Component->SetStaticMesh(MeshFragment->BoidMesh);
		Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Component->SetupAttachment(GetRootComponent());
		Component->RegisterComponent();
		Component->CalcLocalBounds();
		RenderComponents.Emplace(MeshFragment->BoidMesh, Component);
	}
}

UInstancedStaticMeshComponent* ABoidsRenderActor::GetRenderComponent(const FBoidsMeshFragment* MeshFragment)
{
	if (MeshFragment && MeshFragment->BoidMesh->HasValidRenderData(false) && RenderComponents.Contains(MeshFragment->BoidMesh))
	{
		UInstancedStaticMeshComponent* Component = RenderComponents[MeshFragment->BoidMesh];
		//return RenderComponents[MeshFragment];
		if (Component->Bounds.ContainsNaN())
		{
			UE_LOG(LogTemp, Log, TEXT("Fuck!"));
		}
		return Component;
	}

	return nullptr;
}
