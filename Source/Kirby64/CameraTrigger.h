#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraTrigger.generated.h"

UCLASS()
class KIRBY64_API ACameraTrigger : public AActor
{
	GENERATED_BODY()
	
public:	

  ACameraTrigger();

protected:

  virtual void BeginPlay() override;

public:	

  virtual void Tick(float DeltaTime) override;

};
