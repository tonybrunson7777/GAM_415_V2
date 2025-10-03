// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Portal.generated.h"

class GAM_415_V2Character;

UCLASS()
class GAM_415_V2_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// variable for the mesh component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	// variable for the scene capture component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* sceneCapture;

	// variable for the arrow component
	UPROPERTY(EditAnywhere)
	UArrowComponent* rootArrow;

	// variable for the render target
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* renderTarget;

	// variable for the box component
	UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp;

	// variable for the other portal; will determine which portal in the scene that it is connected to
	UPROPERTY(EditAnywhere)
	APortal* OtherPortal;

	// variable for the material
	UPROPERTY(EditAnywhere)
	UMaterialInterface* mat;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SetBool(AGAM_415_V2Character* playerChar);

	UFUNCTION()
	void UpdatePortals();

};
