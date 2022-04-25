#include "AbilitySM.h"

#include "AbilityThrowedState.h"

AbilitySM::AbilitySM()
{
  m_States.Emplace(eABILITYSTATES::kThrowed, new AbilityThrowedState());
}

AbilitySM::~AbilitySM()
{
  for (auto& Elem : m_States)
  {
    if (Elem.Value)
    {
      delete Elem.Value;
      Elem.Value = nullptr;
    }
  }
}

AbilityState* AbilitySM::GetState(const eABILITYSTATES& _State)
{
  for (auto& Elem : m_States)
  {
    if (Elem.Key == _State) { return Elem.Value; }
  }

  return nullptr;
}