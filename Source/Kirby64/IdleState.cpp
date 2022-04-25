#include "IdleState.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "CopyCat.h"

eSTATES IdleState::CheckState(ACharacter* _Char)
{
  auto movementComp = _Char->GetCharacterMovement();
  if (movementComp)
  {
    if (0.0f != movementComp->GetLastInputVector().Y)
    {
      return eSTATES::kWalking;
    }
    else if ( movementComp->GetLastUpdateVelocity().Z > 0.0f)
    {
      return eSTATES::kJumping;
    }
  }

  return eSTATES::kIdle;
}

void IdleState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  State::Update(_DeltaTime, _Char);
}

void IdleState::Enter(ACharacter* _Char)
{
  auto MovementComp = _Char->GetCharacterMovement();
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();
  if (!MovementComp || !CopyComp) { return; }

  MovementComp->JumpZVelocity = 1000.0f;
  //if (CopyComp->IsAbilityStored()) { CopyComp->RestoreAbility(); }

  TArray<USkeletalMeshComponent*> SkeletalMeshes;
  _Char->GetComponents(SkeletalMeshes);

  for (auto& pMesh : SkeletalMeshes)
  {
    if ("CharacterMesh0" == pMesh->GetName())
    {
      pMesh->SetHiddenInGame(false);
    }
    else
    {
      pMesh->SetHiddenInGame(true);
    }
  }
}

void IdleState::Exit(ACharacter* _Char)
{

}
