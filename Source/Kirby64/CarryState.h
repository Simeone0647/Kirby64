#pragma once

#include "State.h"
#include "CoreMinimal.h"

class KIRBY64_API CarryState : public State
{
public:

	CarryState() = default;

	~CarryState() = default;

  eSTATES CheckState(ACharacter* _Char) override
  {
    return eSTATES::kCarry;
  }

  void Update(const float& _DeltaTime, ACharacter* _Char) override;

  void Enter(ACharacter* _Char) override;

  void Exit(ACharacter* _Char) override;
};
