// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"
#include "..\Public\SWeapon.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASWeapon::Fire()
{
	// Trace the world from pawn eyes to crosshair location (center screen)
	AActor* MyOwner = GetOwner();
	if (MyOwner) 
	{
		// Retrieves the eye location and rotation of actor
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		// Get the vector end of a line trace
		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

		/* Used for more accurate collision detection. 
		Useful for getting specific hit sections for things liek a headshot */
		FCollisionQueryParams QueryParams;
		//Ignore Character & Weapon
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;


		// A struct of hit result data
		FHitResult Hit;

		// if there was a hit
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams)) 
		{
			// Blocking hit! Process damage


		}

		// Draw A line for the shot
		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
	}
	
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

