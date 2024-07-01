// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbook.h"
#include "Engine/GameEngine.h"
#include "MyPaperCharacter.generated.h"

/**
 *
 */
UCLASS()
class PLATFORMER2D_DEMO_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMyPaperCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// SpringArm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	// Animation Flipbooks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbook")
	class UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbook")
	class UPaperFlipbook* RunFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbook")
	class UPaperFlipbook* JumpFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;

 	void UpdateAnimation();
	void SetIdleFlipbook();
    void SetRunFlipbook(bool isNegative);
    void SetJumpFlipbook();

private:
// 	void Move(const FInputActionValue& Value);
//     void Jump(const FInputActionValue& Value);
// 	void UpdateCharacterState();
};
