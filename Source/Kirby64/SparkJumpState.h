#pragma once

#include "EnemyState.h"
#include "CoreMinimal.h"

class KIRBY64_API SparkJumpState : public EnemyState
{
public:

	SparkJumpState();

	~SparkJumpState() = default;

  virtual eENEMYSTATES CheckState(ACharacter* _Char) override;

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;

private:

  int32 m_Direction;
};
