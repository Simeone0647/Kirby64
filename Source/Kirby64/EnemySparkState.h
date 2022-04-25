#pragma once

#include "EnemyState.h"
#include "CoreMinimal.h"

class KIRBY64_API EnemySparkState : public EnemyState
{
public:

	EnemySparkState();

	~EnemySparkState() = default;

  virtual eENEMYSTATES CheckState(ACharacter* _Enemy) override;

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;

private:

  float m_SparkTime;

  const float m_MaxSparkTime = 3.0f;
};
