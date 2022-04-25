#pragma once

#include "CoreMinimal.h"

enum eABILITYSTATES
{
  kThrowed = 0,
  kFreed,
  kUnknown,
  kNumStates
};

class KIRBY64_API AbilityState
{
public:

  virtual eABILITYSTATES CheckState(AActor* _Ability)
  {
    return eABILITYSTATES::kUnknown;
  }

  virtual void Update(const float& _DeltaTime, AActor* _Ability) {}

  virtual void Enter(AActor* _Ability) {}

  virtual void Exit(AActor* _Ability) {}

};
