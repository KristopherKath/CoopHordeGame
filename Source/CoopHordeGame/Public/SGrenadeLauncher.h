// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "SGrenadeLauncher.generated.h"

class ALauncherProjectile;


UCLASS()
class COOPHORDEGAME_API ASGrenadeLauncher : public ASWeapon
{
	GENERATED_BODY()
	
public:

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;

	

protected:

	virtual void Fire() override;

};
