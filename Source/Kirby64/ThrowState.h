#pragma once

#include "State.h"
#include "CoreMinimal.h"

class KIRBY64_API ThrowState : public State 
{
public:

	ThrowState();

	~ThrowState() = default;

  eSTATES CheckState(ACharacter* _Char) override;

  void Update(const float& _DeltaTime, ACharacter* _Char) override;

  void Enter(ACharacter* _Char) override;

  void Exit(ACharacter* _Char) override;

private:

  float m_Delay;

  const float m_MaxDelay = 0.2f;
};
