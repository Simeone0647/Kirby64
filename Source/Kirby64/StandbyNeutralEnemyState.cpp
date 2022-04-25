#include "StandbyNeutralEnemyState.h"

#include "Components/CapsuleComponent.h"

StandbyNeutralEnemyState::StandbyNeutralEnemyState()
  : m_Delay(0.0f)
{}

eENEMYSTATES StandbyNeutralEnemyState::CheckState(ACharacter* _Char)
{
  if (m_Delay >= m_MaxDelay)
  {
    return eENEMYSTATES::kNeutralMoving;
  }

  return eENEMYSTATES::kNeutralStandby;
}

void StandbyNeutralEnemyState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  m_Delay += _DeltaTime;
}

void StandbyNeutralEnemyState::Enter(ACharacter* _Char)
{
  auto CapsuleComp = _Char->FindComponentByClass<UCapsuleComponent>();
  if (!CapsuleComp) { return; }

  CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void StandbyNeutralEnemyState::Exit(ACharacter* _Char)
{
  m_Delay = 0.0f;
}
