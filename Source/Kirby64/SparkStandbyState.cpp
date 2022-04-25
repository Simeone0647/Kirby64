#include "SparkStandbyState.h"

#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"

SparkStandbyState::SparkStandbyState()
  : m_Desicion(-1),
    m_Delay(0.0f)
{}

eENEMYSTATES SparkStandbyState::CheckState(ACharacter* _Enemy)
{
  if (0 == m_Desicion)
  {
    return eENEMYSTATES::kSparkJump;
  }
  else if (1 == m_Desicion)
  {
    return eENEMYSTATES::kESpark;
  }

  return eENEMYSTATES::kSparkStandby;
}

void SparkStandbyState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  m_Delay += _DeltaTime;

  if (m_Delay >= m_MaxDelay)
  {
    m_Desicion = FMath::RandRange(0, 1);
  }
}

void SparkStandbyState::Enter(ACharacter* _Char)
{
}

void SparkStandbyState::Exit(ACharacter* _Char)
{
  m_Desicion = -1;
  m_Delay = 0.0f;
}