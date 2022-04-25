#pragma once

#include "AbilityState.h"
#include "CoreMinimal.h"

class KIRBY64_API AbilityThrowedState : public AbilityState
{
public:

	AbilityThrowedState();

	~AbilityThrowedState() = default;

  eABILITYSTATES CheckState(AActor* _Ability) override
  {
    return eABILITYSTATES::kThrowed;
  }

  void Update(const float& _DeltaTime, AActor* _Ability) override;

  void Enter(AActor* _Ability) override;

  void Exit(AActor* _Ability) {}

private:
  
  float m_Direction;
};
