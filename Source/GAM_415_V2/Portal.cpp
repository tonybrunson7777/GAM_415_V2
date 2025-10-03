// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "GAM_415_V2Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create the mesh component
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	// create the box component
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");

	// create the capture component
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");

	// create the arrow component
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");

	// set the box component as the root component
	RootComponent = boxComp;

	// attach the mesh to the root component
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent);

	// set the collision to ignore
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	// set the render target to the scene capture component
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);

	// set the render target to the scene capture component
	mesh->SetHiddenInSceneCapture(true);

	// check to see if mat is valid before applying it
	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// call the update portals function
	UpdatePortals();

}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGAM_415_V2Character* playerChar = Cast<AGAM_415_V2Character>(OtherActor);

	// if the player character is valid, and the other portal is valid, teleport the player to the other portal
	if (playerChar)
	{
		if (OtherPortal)
		{
			if (!playerChar->isTeleporting)
			{
				playerChar->isTeleporting = true;
				FVector loc = OtherPortal->rootArrow->GetComponentLocation();
				playerChar->SetActorLocation(loc);

				// set a timer to reset the isTeleporting variable after 1 second
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);
			}
		}
	}
}

void APortal::SetBool(AGAM_415_V2Character* playerChar)
{
	if (playerChar)
	{
		playerChar->isTeleporting = false;
	}
}


void APortal::UpdatePortals()  
{  
	// get the difference between the two portal locations 
   FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();  

   // get the camera location
   FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();

   // get the camera rotation
   FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();

   // calculate the combined location 
   FVector CombinedLocation = camLocation + Location;

   // set the scene capture location and rotation
   sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);
}

