// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMeshFromStatic.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AProcMeshFromStatic::AProcMeshFromStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// create default subobject for procedural mesh component
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");

	// create default subobject for static mesh component
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");

	// set the root component to procMesh
	RootComponent = procMesh;

	// attach baseMesh to root component
	baseMesh->SetupAttachment(procMesh);

}

// Called when the game starts or when spawned
void AProcMeshFromStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProcMeshFromStatic::PostActorCreated()
{
	Super::PostActorCreated();
	GetMeshData();
}

void AProcMeshFromStatic::PostLoad()
{
	Super::PostLoad();
	GetMeshData();
}

void AProcMeshFromStatic::GetMeshData()
{
	// create new local static mesh variable and pull the static mesh from the component
	UStaticMesh* mesh = baseMesh->GetStaticMesh();
	if (mesh)
	{
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UV0, Tangents);

		// use the data to create procedural mesh section
		procMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertexColors, Tangents);
		CreateMesh();
	}
}

void AProcMeshFromStatic::CreateMesh()
{
	if (baseMesh)
	{
		procMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true);
	}
}

// Called every frame
void AProcMeshFromStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


