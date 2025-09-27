// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcMeshFromStatic.generated.h"

UCLASS()
class GAM_415_V2_API AProcMeshFromStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcMeshFromStatic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// variable for an array of vertices
	UPROPERTY()
	TArray<FVector> Vertices;

	// variable for an array of triangles
	UPROPERTY()
	TArray<int> Triangles;

	// variable for an array of normals
	UPROPERTY()
	TArray<FVector> Normals;

	// variable for an array of UVs
	TArray<FVector2D> UV0;

	// variable for an array of vertex colors
	UPROPERTY()
	TArray<FLinearColor> VertexColors;

	// variable for an array of UP vertex colors
	TArray<FColor> UpVertexColors;

	// variable for an array of tangents (not recognized in forward declaration; must include ProceduralMeshComponent.h)
	TArray<FProcMeshTangent> Tangents;

	// variable for UStaticMeshComponent called baseMesh
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* baseMesh;

private:
	// variable for UProceduralMeshComponent called procMesh
	UProceduralMeshComponent* procMesh;

	// function to get mesh data from baseMesh and populate arrays
	void GetMeshData();

	// function to create procedural mesh from arrays
	void CreateMesh();


};
