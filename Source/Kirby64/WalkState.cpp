#include "WalkState.h"

#include "Kirby64Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CopyCat.h"

eSTATES WalkState::CheckState(ACharacter* _Char)
{
  auto movementComp = _Char->GetCharacterMovement();
  if (movementComp)
  {
    if (0.0f == movementComp->GetLastInputVector().Y)
    {
      return eSTATES::kIdle;
    }
    else if (movementComp->GetLastUpdateVelocity().Z > 0.0f)
    {
      return eSTATES::kJumping;
    }
    else if (movementComp->GetLastUpdateVelocity().Z < 0.0f)
    {
      return eSTATES::kFalling;
    }
  }

  return eSTATES::kWalking;
}

void WalkState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  State::Update(_DeltaTime, _Char);
}

void WalkState::Enter(ACharacter* _Char)
{
}

void WalkState::Exit(ACharacter* _Char)
{

}