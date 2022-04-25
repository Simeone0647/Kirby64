#include "EatState.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"

#include "CopyCat.h"

EatState::EatState()
{
  static ConstructorHelpers::FObjectFinder<USoundWave>SoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Kirby/Eat.Eat'"));
  if (SoundAsset.Succeeded()) { m_pEatSound = SoundAsset.Object; }
}

eSTATES EatState::CheckState(ACharacter* _Char)
{
  TArray<AActor*> Childs;
  _Char->GetAttachedActors(Childs);

  if (0 == Childs.Num())
  {
    return eSTATES::kIdle;
  }

  return eSTATES::kEating;
}

void EatState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  State::Update(_DeltaTime, _Char);
}

void EatState::Enter(ACharacter* _Char)
{
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();
  if (!CopyComp) { return; }

  UGameplayStatics::PlaySound2D(_Char->GetWorld(), m_pEatSound, 2.5f);

  CopyComp->StoreAbility();
  CopyComp->SetActiveAbility("SpitEnemy");

  TArray<USkeletalMeshComponent*> SkeletalMeshes;
  _Char->GetComponents(SkeletalMeshes);
  for (auto& Mesh : SkeletalMeshes)
  {
    if ("FatKirby" == Mesh->GetName())
    {
      Mesh->SetHiddenInGame(false);
    }
    else
    {
      Mesh->SetHiddenInGame(true);
    }
  }

  _Char->JumpMaxCount = 1;
}

void EatState::Exit(ACharacter* _Char)
{
  _Char->JumpMaxCount = 6;
}