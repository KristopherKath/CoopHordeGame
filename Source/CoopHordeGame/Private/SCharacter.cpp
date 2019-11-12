// Fill out your copyright notice in the Description page of Project Settings.



#include "..\Public\SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"


// Constructor
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Spring Arm Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	//Camera Component
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	//Enables Crouching
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	
	ZoomedFOV = 65.0f;
	ZoomInterpSpeed = 20;
}


// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Set Default FOV
	DefaultFOV = CameraComp->FieldOfView;
}

//Movement Input for Right & Left
void ASCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value); 
}

//Movement Input for Forward & Back
void ASCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

//Crouching
void ASCharacter::BeginCrouch()
{
	Crouch();
}

//UnCrouching
void ASCharacter::EndCrouch()
{
	UnCrouch();
}

//Start Jumping
void ASCharacter::StartJump()
{
	Jump();
}

//End Jumping
void ASCharacter::EndJump()
{
	StopJumping();
}

//Start Zooming
void ASCharacter::BeginZoom()
{
	bWantToZoom = true;
}

//End Zooming
void ASCharacter::EndZoom()
{
	bWantToZoom = false;
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TargetFOV = bWantToZoom ? ZoomedFOV : DefaultFOV;

	float NewFOV = FMath::FInterpTo(CameraComp->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);

	CameraComp->SetFieldOfView(NewFOV);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//For Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	//For Rotating Camera
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);

	//Crouch Input
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacter::EndCrouch);

	//Jump Input
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASCharacter::EndJump);

	//Zoom Input
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ASCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ASCharacter::EndZoom);


}

FVector ASCharacter::GetPawnViewLocation() const
{
	//Return the camera component location
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}

	//if previous fails then fallback to
	//original implementation which gets eye height of character
	return Super::GetPawnViewLocation();
}

