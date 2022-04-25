#pragma once

#include "CoreMinimal.h"
#include "State.h"

class KIRBY64_API StateMachine
{
public:

	StateMachine();

	~StateMachine();
	
	State* GetState(const eSTATES& _State);

	FORCEINLINE
	bool StateExist(const eSTATES& _State)
	{
		return (m_States.Contains(_State)) ? true : false;
	}

private:

  TMap<eSTATES, State*> m_States;
};
