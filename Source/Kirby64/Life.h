// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Life.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KIRBY64_API ULife : public UActorComponent
{
	GENERATED_BODY()

public:	

	ULife();

  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	  void DoDamage(const int32 _Amount)
	  {
	    m_Health -= _Amount;

			if (m_Health <= 0) { RemoveChance(); }
	  }

	UFUNCTION(BlueprintCallable)
	  int32 GetHealth()
	  {
	  	return m_Health;
	  }

	UFUNCTION(BlueprintCallable)
	  void SetHealth(const int32 _Health)
	  {
	  	m_Health = _Health;
	  }

	FORCEINLINE void AddHealth(const int32& _Health)
	{
		m_Health += _Health;
		if (m_Health > m_MaxHealth) { m_Health = m_MaxHealth; }
	}

  UFUNCTION(BlueprintCallable)
    int32 GetChances()
    {
      return m_Chances;
    }

  void RemoveChance();

protected:
	virtual void BeginPlay() override;
		
private:

	UPROPERTY(EditAnywhere, Category = Life, DisplayName = "Health")
    int32 m_Health;

	UPROPERTY(EditAnywhere, Category = Life, DisplayName = "Chances")
    int32 m_Chances;

  UPROPERTY(EditAnywhere, Category = Life, DisplayName = "Max Health")
    int32 m_MaxHealth;
};
