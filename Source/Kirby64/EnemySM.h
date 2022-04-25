#pragma once

#include "CoreMinimal.h"
#include "EnemyState.h"

class KIRBY64_API EnemySM
{
public:

	EnemySM();

	~EnemySM();

  EnemyState* GetState(const eENEMYSTATES& _State);

  FORCEINLINE
  bool StateExist(const eENEMYSTATES& _State)
  {
    return (m_States.Contains(_State)) ? true : false;
  }

private:

  TMap<eENEMYSTATES, EnemyState*> m_States;
};
