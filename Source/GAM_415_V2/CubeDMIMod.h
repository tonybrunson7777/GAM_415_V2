// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubeDMIMod.generated.h"

class UNiagaraSystem;

UCLASS()
class GAM_415_V2_API ACubeDMIMod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeDMIMod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// box component for overlap detection
	UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp;

	// static mesh component for cube visual
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cubeMesh;

	// material to be used for dynamic material instance
	UPROPERTY(EditAnywhere)
	UMaterialInterface* baseMat;

	// dynamic material instance to modify color at runtime
	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

	// variable for the Niagara particle system
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* colorP;

	// function to handle overlap event
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
