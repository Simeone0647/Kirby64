#include "IceStandbyState.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

IceStandbyState::IceStandbyState()
  : m_Desicion(-1),
    m_Delay(0.0f)
{}

eENEMYSTATES IceStandbyState::CheckState(ACharacter* _Enemy)
{
  if (0 == m_Desicion)
  {
    return eENEMYSTATES::kIceAura;
  }
  else if (1 == m_Desicion)
  {
    return eENEMYSTATES::kIceMoving;
  }

  return eENEMYSTATES::kIceStandby;
}

void IceStandbyState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  m_Delay += _DeltaTime;

  if (m_Delay >= m_MaxDelay)
  {
    m_Desicion = FMath::RandRange(0, 1);
  }
}

void IceStandbyState::Enter(ACharacter* _Char)
{
  auto CapsuleComp = _Char->FindComponentByClass<UCapsuleComponent>();
  if (!CapsuleComp) { return; }

  CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void IceStandbyState::Exit(ACharacter* _Char)
{
  m_Desicion = -1;
  m_Delay = 0.0f;
}