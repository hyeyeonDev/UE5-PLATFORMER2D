// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPaperCharacter.h"
// #include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
// #include "GameFramework/SpringArmComponent.h"
// #include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


AMyPaperCharacter::AMyPaperCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Load the default sprite asset using ConstructorHelpers
    ConstructorHelpers::FObjectFinder<UPaperFlipbook> FB_Idle(TEXT("PaperFlipbook'/Game/Assets/FB_Idle.FB_Idle'"));
    if (FB_Idle.Succeeded())
    {
        IdleFlipbook = FB_Idle.Object;
        GetSprite()->SetFlipbook(FB_Idle.Object);
        GetSprite()->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load flipbook asset."));
    }

    GetCapsuleComponent()->SetCapsuleSize(12.0f, 12.0f);  // Adjust these values as needed

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.0f;
    SpringArm->bUsePawnControlRotation = false;

    SpringArm->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

    ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Default(TEXT("InputMappingContext'/Game/Blueprints/IMC_Default.IMC_Default'"));
    if(IMC_Default.Succeeded())
    {
        DefaultMappingContext = IMC_Default.Object;
    }

    ConstructorHelpers::FObjectFinder<UPaperFlipbook> FB_Run(TEXT("PaperFlipbook'/Game/Assets/FB_Run.FB_Run'"));
    ConstructorHelpers::FObjectFinder<UPaperFlipbook> FB_Jump(TEXT("PaperFlipbook'/Game/Assets/FB_Jump.FB_Jump'"));

    if (FB_Run.Succeeded())
    {
        RunFlipbook = FB_Run.Object;
    }
    if (FB_Jump.Succeeded())
    {
        JumpFlipbook = FB_Jump.Object;
    }
}

void AMyPaperCharacter::BeginPlay()
{
    Super::BeginPlay();
    if(GEngine)
    {
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Hellow")));
    }
}

void AMyPaperCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateAnimation();

    // printf()
}

void AMyPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyPaperCharacter::UpdateAnimation()
{
    // UE_LOG(LogTemp, Warning, TEXT("The vector value is: %f"), GetVelocity().Size());

    // if (GetMove()->IsFalling())
    // {
    //     // Character is jumping
    //     GetSprite()->SetFlipbook(JumpFlipbook);
    // }
    // else if (GetVelocity().Size() > 0)
    // {
    //     // Character is running
    //     GetSprite()->SetFlipbook(RunFlipbook);
    // }
    // else
    // {
    //     // Character is idle
    //     GetSprite()->SetFlipbook(IdleFlipbook);
    // }
}

void AMyPaperCharacter::SetIdleFlipbook()
{
    if (UPaperFlipbookComponent* FlipbookComponent = GetSprite())
    {
        FlipbookComponent->SetFlipbook(IdleFlipbook);
    }
}

void AMyPaperCharacter::SetRunFlipbook(bool isNegative)
{
    if (UPaperFlipbookComponent* FlipbookComponent = GetSprite())
    {
        if(isNegative)
        {
            FlipbookComponent->SetWorldRotation(FRotator(0.0f, -180.0f, 0.0f));
        }
        else
        {
            FlipbookComponent->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
        }
        FlipbookComponent->SetFlipbook(RunFlipbook);
    }
}

void AMyPaperCharacter::SetJumpFlipbook()
{
    if (UPaperFlipbookComponent* FlipbookComponent = GetSprite())
    {
        FlipbookComponent->SetFlipbook(JumpFlipbook);
    }
}