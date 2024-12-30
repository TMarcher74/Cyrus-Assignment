// Copyright Epic Games, Inc. All Rights Reserved.

#include "CyrusAssignmentCharacter.h"
#include "CyrusAssignmentProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "BoxClass.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACyrusAssignmentCharacter

ACyrusAssignmentCharacter::ACyrusAssignmentCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	bHasRifle = false;

}

//////////////////////////////////////////////////////////////////////////// Input

void ACyrusAssignmentCharacter::OnRiflePickedUp()
{
    bHasRifle = true;
}

void ACyrusAssignmentCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACyrusAssignmentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACyrusAssignmentCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACyrusAssignmentCharacter::Look);

		// Shooting
		//EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ACyrusAssignmentCharacter::Shoot);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ACyrusAssignmentCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ACyrusAssignmentCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

// Called in the BP_FirstPersonCharacter blueprint
void ACyrusAssignmentCharacter::Shoot()
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController || !bHasRifle) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector End = CameraLocation + CameraRotation.Vector() * 10000.0f; // Adjust trace range

	// Perform a line trace
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Ignore the player character

	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, End, ECC_Visibility, Params))
	{
		// Check if the hit actor is a box
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->IsA(ABoxClass::StaticClass()))
		{
			ABoxClass* HitBox = Cast<ABoxClass>(HitActor);
			if (HitBox)
			{
				// Apply damage to the box
				HitBox->TakeDamage(1);

				// Log hit details (optional)
				UE_LOG(LogTemp, Log, TEXT("Hit box: %s"), *HitBox->GetName());
			}
		}

		// Optional: Draw a debug line
		// DrawDebugLine(GetWorld(), CameraLocation, HitResult.ImpactPoint, FColor::Red, false, 1.0f, 0, 1.0f);
	}
	else
	{
		// Draw a debug line for a miss
		// DrawDebugLine(GetWorld(), CameraLocation, End, FColor::Blue, false, 1.0f, 0, 1.0f);
	}
}