#include "FallState.h"

#include "GameFramework/Character.h"
#include "Kirby64Character.h"
#include "GameFramework/CharacterMovementComponent.h"

eSTATES FallState::CheckState(ACharacter* _Char)
{
  auto movementComp = _Char->GetCharacterMovement();

  if (movementComp)
  {
    if (0.0f == movementComp->GetLastUpdateVelocity().Z)
    {
      return eSTATES::kIdle;
    }
    else if (movementComp->GetLastUpdateVelocity().Z > 0.0f && _Char->JumpCurrentCount > 1)
    {
      return eSTATES::kFlying;
    }
  }

  return eSTATES::kFalling;
}

void FallState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  State::Update(_DeltaTime, _Char);
  UE_LOG(LogTemp, Warning, TEXT("In Fall State"));
}

void FallState::Enter(ACharacter* _Char)
{
   TArray<USkeletalMeshComponent*> SkeletalMeshes;
  _Char->GetComponents(SkeletalMeshes);

  for (auto& Mesh : SkeletalMeshes)
  {
    if ("CharacterMesh0" == Mesh->GetName())
    {
      Mesh->SetHiddenInGame(false);
    }
    else
    {
      Mesh->SetHiddenInGame(true);
    }
  }
}

void FallState::Exit(ACharacter* _Char)
{
  auto KirbyChar = Cast<AKirby64Character>(_Char);
  if (KirbyChar) { KirbyChar->SetJumpCount(0); }
}