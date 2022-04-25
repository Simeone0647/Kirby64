#include "SpitEnemyState.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

#include "Enemy.h"
#include "CopyCat.h"
#include "AbilityObject.h"
#include "Inhalable.h"

SpitEnemyState::SpitEnemyState()
{
  static ConstructorHelpers::FObjectFinder<USoundWave>SoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Kirby/SpitSomething.SpitSomething'"));
  if (SoundAsset.Succeeded()) { m_pSpitSound = SoundAsset.Object; }
}

void SpitEnemyState::Enter(ACharacter* _Char)
{
  UGameplayStatics::PlaySound2D(_Char->GetWorld(), m_pSpitSound);
  TArray<AActor*> Childs;
  _Char->GetAttachedActors(Childs);

  if (0 != Childs.Num())
  {
    if (Childs[0]->ActorHasTag("Enemy"))
    {
      auto pObjectInside = Cast<AEnemy>(Childs[0]);
      pObjectInside->SetState(eENEMYSTATES::kSpitted);
    }
    else
    {
      auto pObjectInside = Cast<AAbilityObject>(Childs[0]);
      pObjectInside->ChangeState(eABILITYSTATES::kThrowed);
    }

    auto pInhalableComp = Childs[0]->FindComponentByClass<UInhalable>();
    pInhalableComp->SetIsBeingAbsorbed(false);
  }

  _Char->DisableInput(UGameplayStatics::GetPlayerController(_Char->GetWorld(), 0));
}

void SpitEnemyState::Exit(ACharacter* _Char)
{
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();
  if (!CopyComp) { return; }

  CopyComp->RestoreAbility();

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