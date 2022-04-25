#pragma once

#include "CoreMinimal.h"

#include "State.h"

class KIRBY64_API SpitEnemyState : public State
{
public:

	SpitEnemyState();

	~SpitEnemyState() = default;

  eSTATES CheckState(ACharacter* _Char) override
  {
    return eSTATES::kLagThrow;
  }

  void Update(const float& _DeltaTime, ACharacter* _Char) override {}

  void Enter(ACharacter* _Char) override;

  void Exit(ACharacter* _Char) override;

private:

  class USoundWave* m_pSpitSound;
};
