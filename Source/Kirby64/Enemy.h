#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemySM.h"
#include "EnemyState.h"
#include "Enemy.generated.h"

UCLASS()
class KIRBY64_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:

	AEnemy();

  virtual void Tick(float DeltaTime) override;

  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  UFUNCTION(BlueprintCallable)
  void SetState(const eENEMYSTATES _NewState)
  {
    if (_NewState == m_CurrentState) { return; }

    auto PrevStateInst = m_SM.GetState(m_CurrentState);
    if (PrevStateInst) { PrevStateInst->Exit(this); }
    
    m_CurrentState = _NewState;

    auto StateInstance = m_SM.GetState(m_CurrentState);
    if (StateInstance) { StateInstance->Enter(this); }
  }

  UFUNCTION(BlueprintCallable)
  eENEMYSTATES GetCurrentState()
  {
    return m_CurrentState;
  }

  UFUNCTION()
  void OnSpitted(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                 bool bFromSweep, const FHitResult& SweepResult);

protected:

	virtual void BeginPlay() override;

private:

  EnemySM m_SM;

  UPROPERTY(EditAnywhere, DisplayName = "Current State")
    eENEMYSTATES m_CurrentState;

  class USoundWave* m_pClashSound;
};
