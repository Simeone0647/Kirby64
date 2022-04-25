// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatState.h"

#include "Kirby64Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "CopyCat.h"

eSTATES FloatState::CheckState(ACharacter* _Char)
{
  auto MovementComp = _Char->GetCharacterMovement();
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();
  auto KirbyChar = Cast<AKirby64Character>(_Char);

  if (!MovementComp || !CopyComp || !KirbyChar) { return eSTATES::kFloating; }

  if (0.0f == MovementComp->GetLastUpdateVelocity().Z)
  {
    CopyComp->RestoreAbility();
    return eSTATES::kIdle;
  }
  else if (KirbyChar->GetFloatingTime() >= KirbyChar->GetMaxFloatingTime())
  {
    KirbyChar->ResetFloatingTime();
    return eSTATES::kSpit;
  }
  else if (m_CurrentJumpCount != _Char->JumpCurrentCount)
  {
    return eSTATES::kFlying;
  }

  return eSTATES::kFloating;
}

void FloatState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  State::Update(_DeltaTime, _Char);

  auto KirbyChar = Cast<AKirby64Character>(_Char);
  KirbyChar->UpdateFloatingTime(_DeltaTime);
}

void FloatState::Enter(ACharacter* _Char)
{
  auto MovementComp = _Char->GetCharacterMovement();
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();
  if (!CopyComp || !MovementComp) { return; }

  MovementComp->MaxAcceleration = 0.1f;
  MovementComp->GravityScale = 0.1f;
  m_CurrentJumpCount = _Char->JumpCurrentCount;

  TArray<USkeletalMeshComponent*> SkeletalMeshes;
  _Char->GetComponents(SkeletalMeshes);
  for (auto& Mesh : SkeletalMeshes)
  {
    if ("FlyKirby" == Mesh->GetName())
    {
      Mesh->SetHiddenInGame(false);
    }
    else
    {
      Mesh->SetHiddenInGame(true);
    }
  }
}

void FloatState::Exit(ACharacter* _Char)
{
  auto MovementComp = _Char->GetCharacterMovement();
  if (!MovementComp) { return; }

  MovementComp->MaxAcceleration = 2048.0f;
  MovementComp->GravityScale = 2.0f;
}