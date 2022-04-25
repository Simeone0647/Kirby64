#include "SparkJumpState.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

SparkJumpState::SparkJumpState()
  : m_Direction(0)
{}

eENEMYSTATES SparkJumpState::CheckState(ACharacter* _Char)
{
  auto MovementComp = _Char->GetCharacterMovement();
  if (MovementComp)
  {
    if (MovementComp->GetLastUpdateVelocity().Z == 0.0f)
    {
      return eENEMYSTATES::kSparkStandby;
    }
  }

  return eENEMYSTATES::kSparkJump;
}

void SparkJumpState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  _Char->AddMovementInput(FVector(0.0f, m_Direction, 0.0f));
}

void SparkJumpState::Enter(ACharacter* _Char)
{
  _Char->Jump();

  m_Direction = FMath::RandRange(0, 1);
  if (0 == m_Direction) { m_Direction = -1; }
}

void SparkJumpState::Exit(ACharacter* _Char)
{
  m_Direction = 0;
}
