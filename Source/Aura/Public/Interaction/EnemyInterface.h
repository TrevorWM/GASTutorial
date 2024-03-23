// Copyright Me :)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// The = 0 at the end makes it a pure virtual function. Basically says the thing implementing
	// the interface has to make it's own implementation.
	virtual void HighlightActor() = 0;

	virtual void UnHighlightActor() = 0;
};
