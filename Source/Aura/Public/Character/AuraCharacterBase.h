// Copyright Me :)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//TObjectPtrs are being used more. Allow lazy loading. Typically used for member variables
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
