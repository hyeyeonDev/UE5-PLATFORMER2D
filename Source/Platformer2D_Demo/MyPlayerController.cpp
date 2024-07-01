// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "MyPaperCharacter.h"
#include "PaperFlipbookComponent.h"

AMyPlayerController::AMyPlayerController()
{
    // Load Input Mapping Context
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultMappingContextObject(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprints/IMC_Default.IMC_Default'"));
    if (DefaultMappingContextObject.Succeeded())
    {
        DefaultMappingContext = DefaultMappingContextObject.Object;
    }

    // Load Input Actions
    static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionObject(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/IA_Movement.IA_Movement'"));
    if (MoveActionObject.Succeeded())
    {
        MoveAction = MoveActionObject.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionObject(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/IA_Jump.IA_Jump'"));
    if (JumpActionObject.Succeeded())
    {
        JumpAction = JumpActionObject.Object;
    }
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyPlayerController::Idle);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Jump);
    }
    
    if(UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        SubSystem->AddMappingContext(DefaultMappingContext, 1);
    }
}

void AMyPlayerController::Idle(const FInputActionValue& Value)
{
  AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(GetPawn());
  UPaperFlipbookComponent* FlipbookComponent = MyCharacter->GetSprite();
  FlipbookComponent->SetFlipbook(MyCharacter->IdleFlipbook);
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
    if (AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(GetPawn())) 
    {
        float MovementValue = Value.Get<float>();
        MyCharacter->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovementValue);

        UPaperFlipbookComponent* FlipbookComponent = MyCharacter->GetSprite();
        if(MovementValue < 0.0f)
        {
            FlipbookComponent->SetWorldRotation(FRotator(0.0f, -180.0f, -0.0f));
        } 
        else 
        {
            FlipbookComponent->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
        }

        FlipbookComponent->SetFlipbook(MyCharacter->RunFlipbook);
    }
}

void AMyPlayerController::Jump(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        if (AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(GetPawn())) 
        {
            MyCharacter->Jump();

            MyCharacter->JumpFlipbook->SetLooping(false);
            
            UPaperFlipbookComponent* FlipbookComponent = MyCharacter->GetSprite();
            FlipbookComponent->SetFlipbook(MyCharacter->JumpFlipbook);
        }
    }
}