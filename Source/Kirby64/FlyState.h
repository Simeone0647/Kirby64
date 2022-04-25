#pragma once

#include "CoreMinimal.h"

#include "State.h"

class ACharacter;

class KIRBY64_API FlyState : public State
{
public:

	FlyState();

	~FlyState() = default;

  virtual eSTATES CheckState(ACharacter* _Char) override;

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;

  FORCEINLINE void ResetFlyTime() { m_FlyTime = 0.0f; }

private:

  float m_FlyTime;

  const float m_MaxFlyTime = 0.5f;
};
