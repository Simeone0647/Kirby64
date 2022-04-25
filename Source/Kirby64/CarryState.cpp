#include "CarryState.h"

#include "GameFramework/Character.h"

#include "CopyCat.h"
#include "AbilityObject.h"
#include "Inhalable.h"

void CarryState::Enter(ACharacter* _Char)
{
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();
  if (!CopyComp) { return; }

  TArray<AActor*> ChildActors;
  _Char->GetAttachedActors(ChildActors);
  if (0 == ChildActors.Num())
  {
    const auto& CurrentAbility = CopyComp->GetActiveAbility();
    if ("Inhale" == CurrentAbility ||
        "Spit" == CurrentAbility ||
        "SpitEnemy" == CurrentAbility)
    {
      return;
    }

    auto pAbility = Cast<AAbilityObject>(_Char->GetWorld()->SpawnActor(AAbilityObject::StaticClass()));
    pAbility->Init(CopyComp->GetActiveAbility());

    EAttachmentRule LocationRule = EAttachmentRule::SnapToTarget;
    EAttachmentRule RotationRule = EAttachmentRule::SnapToTarget;
    EAttachmentRule ScaleRule = EAttachmentRule::SnapToTarget;
    FAttachmentTransformRules AttachRule(LocationRule, RotationRule, ScaleRule, false);

    pAbility->AttachToActor(_Char, AttachRule);
    pAbility->SetActorRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
    pAbility->SetActorRelativeRotation(FRotator(90.0f, 90.0f, 0.0f));
  }
  else
  {
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

    auto& pChild = ChildActors[0];
    auto pInhalableComp = pChild->FindComponentByClass<UInhalable>();
    if (pInhalableComp) { pInhalableComp->SetIsBeingAbsorbed(false); }

    pChild->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
    pChild->SetActorRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

    auto StaticMesh = pChild->FindComponentByClass<UStaticMeshComponent>();
    if (StaticMesh)
    {
      StaticMesh->SetVisibility(true);
    }
    else
    {
      auto SkeletalMesh = pChild->FindComponentByClass<USkeletalMeshComponent>();
      if (SkeletalMesh)
      {
        SkeletalMesh->SetVisibility(true);
      }
    }
  }

  _Char->JumpMaxCount = 1;
  CopyComp->SetActiveAbility("Throw");
}

void CarryState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  State::Update(_DeltaTime, _Char);

  TArray<AActor*> ChildActors;
  _Char->GetAttachedActors(ChildActors);

  if (0 == ChildActors.Num()) { return; }

  auto& pChild = ChildActors[0];

  pChild->SetActorRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
}

void CarryState::Exit(ACharacter* _Char)
{
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();
  if (!CopyComp) { return; }

  _Char->JumpMaxCount = 6;
  CopyComp->SetActiveAbility("Inhale");
}
