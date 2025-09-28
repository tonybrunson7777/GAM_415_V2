// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAM_415_V2Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AGAM_415_V2Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	// a static mesh component that can be applied to the class
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ballMesh;

	// variable for a material that can be applied to the class
	UPROPERTY(EditAnywhere)
	UMaterial* baseMat;

	// variable for a random color that can be applied to the decal material instance
	UPROPERTY()
	FLinearColor randColor;

	// variable for a decal material that can be applied to the class
	UPROPERTY(EditAnywhere)
	UMaterialInterface* projMat;

	// variable for a dynamic material instance that can be applied to the decal material
	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

public:
	AGAM_415_V2Projectile();

protected:
	virtual void BeginPlay();

public:
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

