#pragma once

#include "CoreMinimal.h"
#include "State.h"

class ACharacter;

class KIRBY64_API IceState : public State
{
public:
  
  IceState();

  ~IceState() = default;

  virtual eSTATES CheckState(ACharacter* _Char) override
  {
    return eSTATES::kIce;
  }

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;

private:

  const float m_Speed = 3.0f;

  float m_RotationSpeed = 0.0f;

  const float m_Radius = 200.0f;

  TArray<AActor*> m_Hitboxes;

  FRotator m_PreRotation;

  class USoundWave* m_pIceSound;
};
