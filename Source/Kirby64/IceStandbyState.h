#pragma once

#include "EnemyState.h"
#include "CoreMinimal.h"

class KIRBY64_API IceStandbyState : public EnemyState
{
public:

	IceStandbyState();

	~IceStandbyState() = default;

  virtual eENEMYSTATES CheckState(ACharacter* _Char) override;

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;

private:

  int32 m_Desicion;

  float m_Delay;

  const float m_MaxDelay = 1.0f;
};
