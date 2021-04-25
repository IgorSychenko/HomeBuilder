// Copyright Epic Games, Inc. All Rights Reserved.

#include "HomeBuilderCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "HomeBuilder/Components/BuildingComponent.h"
#include "HomeBuilder/Components/ResourceComponent.h"
#include "HomeBuilder/Interfaces/ResourceComponentSupport.h"

//////////////////////////////////////////////////////////////////////////
// AHomeBuilderCharacter

AHomeBuilderCharacter::AHomeBuilderCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	ResourceComponent = CreateDefaultSubobject<UResourceComponent>(TEXT("ResourceComponent"));
	BuildingComponent = CreateDefaultSubobject<UBuildingComponent>(TEXT("BuildingComponent"));
	ContactSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ContactSphereComponent"));
	ContactSphereComponent->SetupAttachment(RootComponent); 
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHomeBuilderCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHomeBuilderCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHomeBuilderCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHomeBuilderCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHomeBuilderCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AHomeBuilderCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AHomeBuilderCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AHomeBuilderCharacter::OnResetVR);
	
	PlayerInputComponent->BindAction("TakeResource", IE_Pressed, this, &AHomeBuilderCharacter::TakeResource);
	PlayerInputComponent->BindAction("ConstructHome", IE_Pressed, this, &AHomeBuilderCharacter::ConstructHome);
}


void AHomeBuilderCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AHomeBuilderCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (GetBuildingComponent()->IsInProgress()) return;
		
	Jump();
}

void AHomeBuilderCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (GetBuildingComponent()->IsInProgress()) return;
	
	StopJumping();
}

void AHomeBuilderCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHomeBuilderCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHomeBuilderCharacter::MoveForward(float Value)
{
	if (GetBuildingComponent()->IsInProgress()) return;
	
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHomeBuilderCharacter::MoveRight(float Value)
{
	if (GetBuildingComponent()->IsInProgress()) return;
	
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AHomeBuilderCharacter::BeginPlay()
{
	Super::BeginPlay();

	ContactSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AHomeBuilderCharacter::OnContactOverlapBegin);
	ContactSphereComponent->OnComponentEndOverlap.AddDynamic(this, &AHomeBuilderCharacter::OnContactOverlapEnd);
}

UResourceComponent* AHomeBuilderCharacter::GetResourceComponent_Implementation() const
{
	return ResourceComponent;
}

void AHomeBuilderCharacter::OnContactOverlapBegin(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit)
{
	if (OtherActor != this && OtherActor->GetClass()->ImplementsInterface(UResourceComponentSupport::StaticClass()))
	{
		ContactActors.AddUnique(OtherActor);
		OnContactArrayChanged.Broadcast();
	}
}

void AHomeBuilderCharacter::OnContactOverlapEnd(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex)
{
	ContactActors.Remove(OtherActor);
	OnContactArrayChanged.Broadcast();
}

void AHomeBuilderCharacter::TakeResource()
{
	for (auto actor : ContactActors)
	{
		if (actor->GetClass()->ImplementsInterface(UResourceComponentSupport::StaticClass()))
		{
			auto ActorResourceComponent = IResourceComponentSupport::Execute_GetResourceComponent(actor);
			auto OwnerResourceComponent = IResourceComponentSupport::Execute_GetResourceComponent(this);
			const int32 MaxRes = ActorResourceComponent->GetCurrentResource();
			if (MaxRes > OwnerResourceComponent->GetMaxResource() - OwnerResourceComponent->GetCurrentResource())
			{
				const int32 Delta = OwnerResourceComponent->GetMaxResource() - OwnerResourceComponent->GetCurrentResource();
				ActorResourceComponent->ChangeCurrentResource(-Delta);
				OwnerResourceComponent->ChangeCurrentResource(Delta);
			}
			else
			{
				ActorResourceComponent->ChangeCurrentResource(-MaxRes);
				OwnerResourceComponent->ChangeCurrentResource(MaxRes);
			}
		}
	}
}

void AHomeBuilderCharacter::ConstructHome()
{
	GetBuildingComponent()->StartConstruct();
}