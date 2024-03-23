// Copyright Me :)


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Assert to make sure that we have our InputMappingContext set
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//CastChecked is a cast with an assert built into it.
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//Gets the forward direction of a given Rotator
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//Check with if here because Move may be called before the player is valid
	//Don't want the game to crash from assert if that happens
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	LastEnemyActor = CurrentEnemyActor;
	CurrentEnemyActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	/**
	 *Line trace from cursor:
	 * A. Last is null, and current is null
	 *		- Do nothing
	 * B. Last is null, and current is valid
	 *		- Highlight current actor
	 * C. Last is valid, and current is null
	 *		- UnHighlight last actor
	 * D. Both are valid, but last != current
	 *		- Unhighlight last, Highlight current
	 * E. Both are valid and the same
	 *		- Do nothing
	 */

	if (LastEnemyActor == nullptr)
	{
		if (CurrentEnemyActor != nullptr)
		{
			// Case B
			CurrentEnemyActor->HighlightActor();
		}
		else
		{
			//Both null, Case A
		}
	}
	else //Last Actor is valid
	{
		if (CurrentEnemyActor == nullptr)
		{
			//Case C
			LastEnemyActor->UnHighlightActor();
		}
		else // Both are valid
		{
			if (LastEnemyActor != CurrentEnemyActor)
			{
				//Case D
				LastEnemyActor->UnHighlightActor();
				CurrentEnemyActor->HighlightActor();
			}
			else
			{
				//Case E - Do nothing
			}
		}
	}
}
