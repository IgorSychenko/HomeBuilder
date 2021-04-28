// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HomeBuilder/Interfaces/ResourceComponentSupport.h"
#include "HomeBuilder/Interfaces/BuildingComponentSupport.h"
#include "HomeBuilderCharacter.generated.h"

class UBuildingGhostComponent;
class USphereComponent;
class UBuildingComponent;
class UResourceComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FContactArrayChanged);

UCLASS(config=Game)
class AHomeBuilderCharacter
	: public ACharacter
	, public IResourceComponentSupport
	, public IBuildingComponentSupport
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AHomeBuilderCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	virtual void BeginPlay() override;

	// IResourceComponentSupport Begin
	virtual UResourceComponent* GetResourceComponent_Implementation() const override;
	// IResourceComponentSupport End

	// IBuildingComponentSupport Begin
	virtual UBuildingComponent* GetBuildingComponent_Implementation() const override;
	virtual UBuildingGhostComponent* GetBuildingGhostComponent_Implementation() const override;
	// IBuildingComponentSupport End
	
	UFUNCTION(BlueprintCallable, Category = "HomeBuilderCharacter|ResourceComponent")
	void TakeResource();
	
	UFUNCTION(BlueprintCallable, Category = "HomeBuilderCharacter|ResourceComponent")
	void ConstructHome();
	
	UFUNCTION(BlueprintCallable, Category = "HomeBuilderCharacter|ResourceComponent")
	FORCEINLINE bool CanTakeResource() { return ContactActors.Num() > 0; }

	UPROPERTY(BlueprintAssignable, Category = "ContactSphereComponent")
	FContactArrayChanged OnContactArrayChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ResourceComponent")
	UResourceComponent* ResourceComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildingComponent")
	UBuildingComponent* BuildingComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuildingGhostComponent")
	UBuildingGhostComponent* BuildingGhostComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ContactSphereComponent")
	USphereComponent* ContactSphereComponent;

	UPROPERTY()
	TArray<AActor*> ContactActors;

	UFUNCTION() 
	void OnContactOverlapBegin(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit);

	UFUNCTION() 
	void OnContactOverlapEnd(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex);
};

