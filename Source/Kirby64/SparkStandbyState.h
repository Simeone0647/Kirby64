#pragma once

#include "EnemyState.h"
#include "CoreMinimal.h"

class KIRBY64_API SparkStandbyState : public EnemyState
{
public:

	SparkStandbyState();

	~SparkStandbyState() = default;

  eENEMYSTATES CheckState(ACharacter* _Enemy) override;

  void Update(const float& _DeltaTime, ACharacter* _Char) override;

  void Enter(ACharacter* _Char) override;

  void Exit(ACharacter* _Char) override;

private:

  int32 m_Desicion; 

  float m_Delay;

  const float m_MaxDelay = 1.0f;
};
