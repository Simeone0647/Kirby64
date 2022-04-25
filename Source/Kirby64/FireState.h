#pragma once

#include "CoreMinimal.h"

#include "State.h"

class KIRBY64_API FireState : public State
{
public:

	FireState();

	~FireState() = default;

  virtual eSTATES CheckState(ACharacter* _Char) override
  {
    return eSTATES::kFire;
  }

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override {}

  void Stop(ACharacter* _Char);

private:

 float m_ActiveTime = 0.0f;

 const float m_MaxActiveTime = 1.0f;

 class USoundWave* m_pFireSound;
};
