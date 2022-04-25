#pragma once

#include "CoreMinimal.h"

#include "State.h"

class ACharacter;

class KIRBY64_API WalkState : public State
{
public:

	WalkState() = default;

	~WalkState() = default;

  virtual eSTATES CheckState(ACharacter* _Char) override;

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;
};
