// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class GAM_415_V2_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();
	
	// variable for XSize that is clamped to a minimum of 0
	UPROPERTY(EditAnywhere, Meta = (ClampMin =0))
	int XSize = 0;

	// variable for YSize that is clamped to a minimum of 0
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int YSize = 0;

	// variable for Scale that is clamped to a minimum of 0; multiplier for the height of the noise
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
	float ZMultiplier = 1.0f;

	// variable for NoiseScale that is clamped to a minimum of 0; affects the "frequency" of the noise
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
	float NoiseScale = 1.0f;

	// variable for Scale that is clamped to a minimum of 0.000001; affects the "zoom" of the noise
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0.000001))
	float Scale = 0;

	// varialbe for UVScale that is clamped to a minimum of 0; affects the tiling of the texture
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
	float UVScale = 0;

	// variable for radius that affects the size of the circular area of the terrain
	UPROPERTY(EditAnywhere)
	float radius;

	// variable for Depth that affects the depth of the terrain
	UPROPERTY(EditAnywhere)
	FVector Depth;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// a material that can be applied to the class
	UPROPERTY(EditAnywhere)
	UMaterialInstance* Mat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// function to create the procedural mesh
	UFUNCTION()
	void AlterMesh(FVector impactPoint);

private:
	UProceduralMeshComponent* procMesh;
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;

	int sectionID = 0;

	void CreateVertices();
	void CreateTriangles();

};
