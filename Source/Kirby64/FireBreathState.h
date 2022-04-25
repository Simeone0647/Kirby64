#pragma once

#include "EnemyState.h"
#include "CoreMinimal.h"

class KIRBY64_API FireBreathState : public EnemyState
{
public:

	FireBreathState();

	~FireBreathState() = default;

  eENEMYSTATES CheckState(ACharacter * _Enemy) override;

  void Update(const float& _DeltaTime, ACharacter * _Char) override;

  void Enter(ACharacter * _Char) override;

  void Exit(ACharacter * _Char) override;

private:

  float m_TimeActive;
  
  const float m_MaxTimeActive = 2.0f;

  bool m_CollisionSet;
};
