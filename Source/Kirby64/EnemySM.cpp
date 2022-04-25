#include "EnemySM.h"

#include "FireBreathState.h"
#include "FireStandbyState.h"
#include "SparkJumpState.h"
#include "SparkStandbyState.h"
#include "EnemySparkState.h"
#include "IceAuraState.h"
#include "IceStandbyState.h"
#include "IceEnemyMovingState.h"
#include "SpittedState.h"
#include "StandbyNeutralEnemyState.h"
#include "NeutralMoveEnemyState.h"

EnemySM::EnemySM()
{
  m_States.Emplace(eENEMYSTATES::kFireStandby, new FireStandbyState());
  m_States.Emplace(eENEMYSTATES::kFireBreath, new FireBreathState());
  m_States.Emplace(eENEMYSTATES::kSparkJump, new SparkJumpState());
  m_States.Emplace(eENEMYSTATES::kSparkStandby, new SparkStandbyState());
  m_States.Emplace(eENEMYSTATES::kESpark, new EnemySparkState());
  m_States.Emplace(eENEMYSTATES::kIceStandby, new IceStandbyState());
  m_States.Emplace(eENEMYSTATES::kIceMoving, new IceEnemyMovingState());
  m_States.Emplace(eENEMYSTATES::kIceAura, new IceAuraState());
  m_States.Emplace(eENEMYSTATES::kSpitted, new SpittedState());
  m_States.Emplace(eENEMYSTATES::kNeutralStandby, new StandbyNeutralEnemyState());
  m_States.Emplace(eENEMYSTATES::kNeutralMoving, new NeutralMoveEnemyState());
}

EnemySM::~EnemySM()
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

EnemyState* EnemySM::GetState(const eENEMYSTATES& _State)
{
  for (auto& Elem : m_States)
  {
    if (Elem.Key == _State) { return Elem.Value; }
  }

  return nullptr;
}
