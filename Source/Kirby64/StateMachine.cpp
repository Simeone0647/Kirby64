#include "StateMachine.h"

#include "IdleState.h"
#include "WalkState.h"
#include "JumpState.h"
#include "FlyState.h"
#include "FloatState.h"
#include "FallState.h"
#include "EatState.h"
#include "IceState.h"
#include "InhaleState.h"
#include "ElectricState.h"
#include "FireState.h"
#include "SpitState.h"
#include "SpitEnemyState.h"
#include "CarryState.h"
#include "ThrowState.h"
#include "LagThrowState.h"

StateMachine::StateMachine()
{
  m_States.Emplace(eSTATES::kIdle, new IdleState());
  m_States.Emplace(eSTATES::kWalking, new WalkState());
  m_States.Emplace(eSTATES::kJumping, new JumpState());
  m_States.Emplace(eSTATES::kFloating, new FloatState());
  m_States.Emplace(eSTATES::kFlying, new FlyState());
  m_States.Emplace(eSTATES::kFalling, new FallState());
  m_States.Emplace(eSTATES::kEating, new EatState());
  m_States.Emplace(eSTATES::kIce, new IceState());
  m_States.Emplace(eSTATES::kInhale, new InhaleState());
  m_States.Emplace(eSTATES::kElectric, new ElectricState());
  m_States.Emplace(eSTATES::kFire, new FireState());
  m_States.Emplace(eSTATES::kSpit, new SpitState());
  m_States.Emplace(eSTATES::kSpitEnemy, new SpitEnemyState());
  m_States.Emplace(eSTATES::kCarry, new CarryState());
  m_States.Emplace(eSTATES::kThrow, new ThrowState());
  m_States.Emplace(eSTATES::kLagThrow, new LagThrowState());
}

StateMachine::~StateMachine()
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

State* StateMachine::GetState(const eSTATES& _State)
{
  for (auto& Elem : m_States)
  {
    if (Elem.Key == _State) { return Elem.Value; }
  }

  return nullptr;
}
