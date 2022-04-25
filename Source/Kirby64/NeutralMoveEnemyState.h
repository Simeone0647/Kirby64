#pragma once

#include "CoreMinimal.h"
#include "EnemyState.h"

class KIRBY64_API NeutralMoveEnemyState : public EnemyState
{
public:
	NeutralMoveEnemyState();

	~NeutralMoveEnemyState() = default;

  virtual eENEMYSTATES CheckState(ACharacter* _Char) override;

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;

private:

  float m_Direction;

  FVector m_NewLocation;
};
