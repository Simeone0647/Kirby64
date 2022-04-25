#include "IceEnemyMovingState.h"


#include "GameFramework/Character.h"

IceEnemyMovingState::IceEnemyMovingState()
  : m_Direction(0.0f)
{}

eENEMYSTATES IceEnemyMovingState::CheckState(ACharacter* _Char)
{
  if (FMath::RoundToFloat(_Char->GetActorLocation().Y) == m_NewLocation.Y)
  {
    return eENEMYSTATES::kIceStandby;
  }

  return eENEMYSTATES::kIceMoving;
}

void IceEnemyMovingState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  auto CurrentLocation = _Char->GetActorLocation();

  _Char->SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y + (0.5f * m_Direction), CurrentLocation.Z));
}

void IceEnemyMovingState::Enter(ACharacter* _Char)
{
  m_NewLocation = _Char->GetActorLocation();
  m_NewLocation.Y = FMath::RoundToFloat(FMath::RandRange(m_NewLocation.Y - 150.0f, m_NewLocation.Y + 150.0f));

  m_Direction = (m_NewLocation.Y <= _Char->GetActorLocation().Y) ? -1.0f : 1.0f;
}

void IceEnemyMovingState::Exit(ACharacter* _Char)
{
  m_NewLocation = FVector::ZeroVector;
}
