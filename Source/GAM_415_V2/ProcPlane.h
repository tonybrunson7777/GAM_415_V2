// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcPlane.generated.h"

// Forward declaration
class UProceduralMeshComponent;

UCLASS()
class GAM_415_V2_API AProcPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// variable to hold the procedural mesh component for Vertices
	UPROPERTY(EditAnywhere)
	TArray<FVector> Vertices;

	// variable to hold the procedural mesh component for Triangles
	UPROPERTY(EditAnywhere)
	TArray<int> Triangles;

	// variable to hold the procedural mesh component for UV0
	UPROPERTY(EditAnywhere)
	TArray<FVector2D> UV0;

	// variable to hold the procedural mesh component for Material
	UPROPERTY(EditAnywhere)
	UMaterialInterface* PlaneMat;

	// function to hold the procedural mesh component for Normals
	UFUNCTION()
	void CreateMesh();

private:
	// create a procedural mesh component named ProcMesh
	UProceduralMeshComponent* procMesh;

};
