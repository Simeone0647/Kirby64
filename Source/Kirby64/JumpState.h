#pragma once

#include "CoreMinimal.h"

#include "State.h"

class ACharacter;

class KIRBY64_API JumpState : public State
{
public:

	JumpState();

	~JumpState() = default;

  virtual eSTATES CheckState(ACharacter* _Char) override;

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override {}

private:

  class USoundWave* m_pJumpSound;
};
