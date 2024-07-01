// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */

class UEnhancedInputComponent;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class PLATFORMER2D_DEMO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();
	virtual void SetupInputComponent() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* IdleAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

private:
    void Idle(const FInputActionValue& Value);
    void Move(const FInputActionValue& Value);
    void Jump(const FInputActionValue& Value);
};