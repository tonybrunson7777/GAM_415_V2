// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM_415_V2Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PerlinProcTerrain.h"
#include "PerlinProcTerrain_V2.h"


AGAM_415_V2Projectile::AGAM_415_V2Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGAM_415_V2Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Create the mesh component
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");
   
	// Set as root component
	RootComponent = CollisionComp;

	// Attach ballMesh to root component
	ballMesh->SetupAttachment(RootComponent);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AGAM_415_V2Projectile::BeginPlay()
{
	Super::BeginPlay();

	// generate a random color
	randColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), 1.f);

	// create a dynamic material instance and apply it to the ball mesh
	dmiMat = UMaterialInstanceDynamic::Create(projMat, this);
	ballMesh->SetMaterial(0, dmiMat);

	// apply the random color to the dynamic material instance
	dmiMat->SetVectorParameterValue("ProjColor", randColor);
}

void AGAM_415_V2Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	// check to see if other actor is not null
	if (OtherActor != nullptr)
	{	
		if (colorP)
		{
			// spawn niagara particle system at hit location and apply random color to the particle system
			UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, HitComp, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);

			// apply random color to the particle system
			particleComp->SetNiagaraVariableLinearColor(FString("RandomColor"), randColor);

			// destroy the projectile
			ballMesh->DestroyComponent();

			// destroy the projectile actor after 0.1 seconds to allow time for the particle system to play
			CollisionComp->BodyInstance.SetCollisionProfileName("NoCollision");
		}
		float frameNum = UKismetMathLibrary::RandomFloatInRange(0.f, 3.f);

		// spawn decal at hit location and apply random color and frame to the decal material instance
		auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), baseMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.f, 40.f)), Hit.Location, Hit.Normal.Rotation(), 0.f);
		auto MatInstance = Decal->CreateDynamicMaterialInstance();

		// apply random color and frame to decal material instance
		MatInstance->SetVectorParameterValue("Color", randColor);

		// apply random frame to decal material instance
		MatInstance->SetScalarParameterValue("Frame", frameNum);
		
		// cast the other actor to a procedural terrain actor
		APerlinProcTerrain* procTerrain = Cast<APerlinProcTerrain>(OtherActor);
		APerlinProcTerrain_V2* procTerrainV2 = Cast<APerlinProcTerrain_V2>(OtherActor);

		// if the other actor is a procedural terrain, call the AlterMesh function to deform the terrain
		if (procTerrain)
		{
			procTerrain->AlterMesh(Hit.ImpactPoint);
		}

		if (procTerrainV2)
		{
			procTerrainV2->AlterMesh(Hit.ImpactPoint);
		}

	}
}