#pragma once

#include "EnemyState.h"
#include "CoreMinimal.h"

class KIRBY64_API FireStandbyState : public EnemyState
{
public:

	FireStandbyState() = default;

	~FireStandbyState() = default;

  eENEMYSTATES CheckState(ACharacter* _Enemy) override { return eENEMYSTATES::kFireStandby; }

  void Update(const float& _DeltaTime, ACharacter* _Char) override {}

  void Enter(ACharacter* _Char) override {}

  void Exit(ACharacter* _Char) override {}
};
