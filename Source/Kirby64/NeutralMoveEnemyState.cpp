#include "NeutralMoveEnemyState.h"

#include "GameFramework/Character.h"

NeutralMoveEnemyState::NeutralMoveEnemyState()
  : m_Direction(0.0f)
{}

eENEMYSTATES NeutralMoveEnemyState::CheckState(ACharacter* _Char)
{
  if (FMath::RoundToFloat(_Char->GetActorLocation().Y) == m_NewLocation.Y)
  {
    return eENEMYSTATES::kNeutralStandby;
  }

  return eENEMYSTATES::kNeutralMoving;
}

void NeutralMoveEnemyState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  auto CurrentLocation = _Char->GetActorLocation();

  _Char->SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y + (0.5f * m_Direction), CurrentLocation.Z));
}

void NeutralMoveEnemyState::Enter(ACharacter* _Char)
{
  m_NewLocation = _Char->GetActorLocation();
  m_NewLocation.Y = FMath::RoundToFloat(FMath::RandRange(m_NewLocation.Y - 150.0f, m_NewLocation.Y + 150.0f));

  m_Direction = (m_NewLocation.Y <= _Char->GetActorLocation().Y) ? -1.0f : 1.0f;
}

void NeutralMoveEnemyState::Exit(ACharacter* _Char)
{
  m_NewLocation = FVector::ZeroVector;
}
