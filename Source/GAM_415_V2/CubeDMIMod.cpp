// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMod.h"
#include "GAM_415_V2Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");

	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);

}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
	Super::BeginPlay();

	// bind the overlap event
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverlapBegin);

	// check to see if baseMat is valid, then create the dynamic material instance
	if (baseMat)
	{
		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
	}
	
	// check to see if cubeMesh is valid, then set the material to the dynamic material instance
	if (cubeMesh)
	{
		cubeMesh->SetMaterial(0, dmiMat);
	}
}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeDMIMod::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// cast to player character
	AGAM_415_V2Character* overlappedActor = Cast<AGAM_415_V2Character>(OtherActor);

	// check to see if overlappedActor is valid
	if (overlappedActor)
	{
		// generate random color values
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);

		// create a new FVector4 with the random color values and alpha of 1.0f
		FLinearColor randColor = FLinearColor(ranNumX, ranNumY, ranNumZ, 1.0f);

		// check to see if dmiMat is valid
		if (dmiMat)
		{
			// set the color parameter of the dynamic material instance
			dmiMat->SetVectorParameterValue("Color", randColor);

			// set the darkness parameter of the dynamic material instance
			dmiMat->SetScalarParameterValue("Darkness", ranNumX);

			// set the opacity parameter of the dynamic material instance
			dmiMat->SetScalarParameterValue("Opacity", ranNumY);

			if (colorP)
			{
				UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, OtherComp, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);

				particleComp->SetNiagaraVariableLinearColor(FString("RandColor"), randColor);
			}
		}
	}
}

