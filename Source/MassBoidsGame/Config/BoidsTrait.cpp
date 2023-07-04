﻿// Copyright Dennis Andersson. All Rights Reserved.


#include "BoidsTrait.h"
#include "Fragments/BoidsLocationFragment.h"
#include "Fragments/BoidsSpawnTag.h"

// Engine
#include "MassEntitySubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "MassMovementFragments.h"
#include "Engine/World.h"


void UBoidsTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	//UMassEntitySubsystem* EntitySubsystem = UWorld::GetSubsystem<UMassEntitySubsystem>(&World);
	//check(EntitySubsystem);

	TSharedPtr<FMassEntityManager> EntityManager = World.GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager().AsShared();

	BuildContext.AddTag<FBoidsSpawnTag>();
	BuildContext.AddFragment<FBoidsLocationFragment>();
	BuildContext.AddFragment<FMassVelocityFragment>();
	BuildContext.AddFragment(FConstStructView::Make(Speed));

	// Mesh Shared Fragment
	{
		const uint32 SharedHash = UE::StructUtils::GetStructCrc32(FConstStructView::Make(Mesh));
		//const FConstSharedStruct SharedFragment = EntitySubsystem->GetOrCreateConstSharedFragment(SharedHash, Mesh);
		const FConstSharedStruct SharedFragment = EntityManager->GetOrCreateConstSharedFragmentByHash(SharedHash, Mesh);

		BuildContext.AddConstSharedFragment(SharedFragment);
	}
}
