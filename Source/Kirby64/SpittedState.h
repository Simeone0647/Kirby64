#pragma once

#include "EnemyState.h"
#include "CoreMinimal.h"

class KIRBY64_API SpittedState : public EnemyState
{
public:

	SpittedState();

	~SpittedState() = default;

  eENEMYSTATES CheckState(ACharacter* _Char) override
  {
    return eENEMYSTATES::kSpitted;
  }

  void Update(const float& _DeltaTime, ACharacter* _Char) override;

  void Enter(ACharacter* _Char) override;

  void Exit(ACharacter* _Char) override {}

private:

 float m_Direction;
};
