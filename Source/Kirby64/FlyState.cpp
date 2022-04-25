#include "FlyState.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Kirby64Character.h"
#include "CopyCat.h"

FlyState::FlyState()
  : m_FlyTime(0.0f)
{}

eSTATES FlyState::CheckState(ACharacter* _Char)
{
  if (m_FlyTime >= m_MaxFlyTime) { return eSTATES::kFloating; }

  return eSTATES::kFlying;
}

void FlyState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  State::Update(_DeltaTime, _Char);

  auto KirbyChar = Cast<AKirby64Character>(_Char);
  KirbyChar->UpdateFloatingTime(_DeltaTime);
  m_FlyTime += _DeltaTime;

  UE_LOG(LogTemp, Warning, TEXT("In Fly State"));
}

void FlyState::Enter(ACharacter* _Char)
{
  auto pMovementComp = _Char->GetCharacterMovement();
  auto pCopyComp = _Char->FindComponentByClass<UCopyCat>();

  if (!pMovementComp || !pCopyComp) { return; }

  pMovementComp->JumpZVelocity = 600.0f;

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

  pCopyComp->StoreAbility();
  pCopyComp->SetActiveAbility("Spit");
}

void FlyState::Exit(ACharacter* _Char)
{
  m_FlyTime = 0.0f;
}