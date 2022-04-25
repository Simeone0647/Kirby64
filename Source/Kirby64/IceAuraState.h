#pragma once

#include "EnemyState.h"
#include "CoreMinimal.h"

class KIRBY64_API IceAuraState : public EnemyState
{
public:

	IceAuraState();

	~IceAuraState() = default;

  virtual eENEMYSTATES CheckState(ACharacter* _Enemy) override;

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;

private:

  float m_IceTime;

  const float m_MaxIceTime = 3.0f;
};
