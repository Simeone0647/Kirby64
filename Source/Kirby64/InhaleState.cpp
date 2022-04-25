#include "InhaleState.h"

#include "Kirby64Character.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

#include "CopyCat.h"

InhaleState::InhaleState()
  : m_SetLoop(false),
    m_Timer(0.0f)
{
  static ConstructorHelpers::FObjectFinder<USoundWave>StartSoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Abilities/Inhale.Inhale'"));
  if (StartSoundAsset.Succeeded()) { m_pInhaleStartSound = StartSoundAsset.Object; }

  static ConstructorHelpers::FObjectFinder<USoundWave>EndSoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Abilities/Inhale2.Inhale2'"));
  if (EndSoundAsset.Succeeded()) { m_pInhaleEndSound = EndSoundAsset.Object; }
}

void InhaleState::Enter(ACharacter* _Char)
{
  auto MovementComp = _Char->FindComponentByClass<UCharacterMovementComponent>();
  if (!MovementComp) { return; }

  auto pAudioComp = _Char->FindComponentByClass<UAudioComponent>();
  if (pAudioComp)
  {
    pAudioComp->SetSound(m_pInhaleStartSound);
    pAudioComp->Play();
    pAudioComp->SetVolumeMultiplier(3.5f);
  }

  TArray<UCapsuleComponent*> CapsulesComps;
  _Char->GetComponents(CapsulesComps);
  for (auto& CapsuleComp : CapsulesComps)
  {
    if ("InhaleTrigger" == CapsuleComp->GetName())
    {
      CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

      break;
    }
  }

  TArray<USkeletalMeshComponent*> SkeletalMeshComps;
  _Char->GetComponents(SkeletalMeshComps);
  for (auto& pSMComp : SkeletalMeshComps)
  {
    if ("InhaleKirby" == pSMComp->GetName())
    {
      pSMComp->SetHiddenInGame(false);
    }
    else
    {
      pSMComp->SetHiddenInGame(true);
    }
  }

  TArray<USphereComponent*> SphereComps;
  _Char->GetComponents(SphereComps);
  for (auto& pSphereComp : SphereComps)
  {
    if ("InnerCollision" == pSphereComp->GetName())
    {
      pSphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

      break;
    }
  }

  MovementComp->MaxWalkSpeed = 70.0f;
  _Char->JumpMaxCount = 1;
}

void InhaleState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  if (m_SetLoop) { return; }

  m_Timer += _DeltaTime;
  auto pAudioComp = _Char->FindComponentByClass<UAudioComponent>();
  if (pAudioComp)
  {
    if (m_Timer >= 0.9f)
    {
      m_SetLoop = true;
      pAudioComp->SetSound(m_pInhaleEndSound);
      pAudioComp->Play();
    }
  }
}

void InhaleState::Exit(ACharacter* _Char)
{
  State::Exit(_Char);

  auto MovementComp = _Char->FindComponentByClass<UCharacterMovementComponent>();
  if (!MovementComp) { return; }

  auto pAudioComp = _Char->FindComponentByClass<UAudioComponent>();
  if (pAudioComp)
  {
    pAudioComp->Stop();
    pAudioComp->SetVolumeMultiplier(1.0f);
  }

  TArray<UCapsuleComponent*> CapsulesComps;
  _Char->GetComponents(CapsulesComps);
  for (auto& CapsuleComp : CapsulesComps)
  {
    if ("InhaleTrigger" == CapsuleComp->GetName())
    {
      CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

      break;
    }
  }

  TArray<USkeletalMeshComponent*> SkeletalMeshComps;
  _Char->GetComponents(SkeletalMeshComps);
  for (auto& pSMComp : SkeletalMeshComps)
  {
    if ("CharacterMesh0" == pSMComp->GetName())
    {
      pSMComp->SetHiddenInGame(false);
    }
    else
    {
      pSMComp->SetHiddenInGame(true);
    }
  }

  TArray<USphereComponent*> SphereComps;
  _Char->GetComponents(SphereComps);
  for (auto& pSphereComp : SphereComps)
  {
    if ("InnerCollision" == pSphereComp->GetName())
    {
      pSphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

      break;
    }
  }

  MovementComp->MaxWalkSpeed = 600.0f;
  _Char->JumpMaxCount = 6;
  m_SetLoop = false;
  m_Timer = 0.0f;
}