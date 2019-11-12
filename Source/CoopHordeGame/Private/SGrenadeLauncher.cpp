// Fill out your copyright notice in the Description page of Project Settings.


#include "SGrenadeLauncher.h"
#include "..\Public\SGrenadeLauncher.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"



void ASGrenadeLauncher::Fire()
{

	AActor* MyOwner = GetOwner();
	if (MyOwner && ProjectileClass)
	{

		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

		FRotator EyeRotation;
		FVector EyeLocation; // Not Used
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		// spawn the projectile at the muzzle
		GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, EyeRotation, ActorSpawnParams);
	}
}
