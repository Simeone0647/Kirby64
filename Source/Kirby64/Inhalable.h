// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inhalable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KIRBY64_API UInhalable : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInhalable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  void OnAbsorb(AActor* _pPlayer);

	void SetIsBeingAbsorbed(const bool& _Value)
	{
		m_BeingAbsorbed = _Value;
	}

	UFUNCTION(BlueprintCallable)
	  bool IsBeingAbsorbed()
	  {
	  	return m_BeingAbsorbed;
	  }

private:

  FVector m_PositionToMove;

	bool m_BeingAbsorbed;

	FVector m_InhaledScale;

	AActor* m_pPlayerRef;
};
