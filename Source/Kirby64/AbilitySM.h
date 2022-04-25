#pragma once

#include "AbilityState.h"
#include "CoreMinimal.h"

class KIRBY64_API AbilitySM
{
public:
	AbilitySM();

	~AbilitySM();

  AbilityState* GetState(const eABILITYSTATES& _State);

  FORCEINLINE
  bool StateExist(const eABILITYSTATES& _State)
  {
    return (m_States.Contains(_State)) ? true : false;
  }

private:

  TMap<eABILITYSTATES, AbilityState*> m_States;
};
