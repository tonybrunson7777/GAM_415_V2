// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain_V2.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class GAM_415_V2_API APerlinProcTerrain_V2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain_V2();

	// Variables for terrain generation
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int XSize = 0;
	
	// Variables for terrain generation
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int YSize = 0;

	// variable for the z height multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
	float ZMultiplier = 1.0f;

	// variable for the noise scale
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	float NoiseScale = 1.0f;

	// variable for the number of octaves
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float Scale = 0;

	// variable for the UV scale
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float UVScale = 0;

	// variable for the radius of the impact
	UPROPERTY(EditAnywhere)
	float radius;

	// variable for the depth of the impact
	UPROPERTY(EditAnywhere)
	FVector Depth;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// material for the procedural mesh
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Mat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// function to alter the mesh at the impact point
	UFUNCTION()
	void AlterMesh(FVector impactPoint);

private:
	UProceduralMeshComponent* ProcMesh;
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;

	int sectionID = 0;

	void CreateVertices();
	void CreateTriangles();

};
