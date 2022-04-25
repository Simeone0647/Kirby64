#include "FireState.h"

#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

#include "CopyCat.h"
#include "Kirby64Character.h"

FireState::FireState()
{
  static ConstructorHelpers::FObjectFinder<USoundWave>SoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Abilities/Fire.Fire'"));
  if (SoundAsset.Succeeded()) { m_pFireSound = SoundAsset.Object; }
}

void FireState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  m_ActiveTime += _DeltaTime;

  if (m_ActiveTime >= m_MaxActiveTime)
  {
    Stop(_Char);
  }

  auto MovementComp = _Char->FindComponentByClass<UCharacterMovementComponent>();
  if (MovementComp)
  {
    auto PawnOwner = Cast<APawn>(_Char);
    PawnOwner->AddMovementInput(FVector(0.f, -1.0f, 0.f), -PawnOwner->GetActorForwardVector().Y);
  }
}

void FireState::Enter(ACharacter* _Char)
{
  auto Hitbox = _Char->FindComponentByClass<UBoxComponent>();
  auto MovementComp = _Char->FindComponentByClass<UCharacterMovementComponent>();//Must deactivate hurtbox.

  if (!Hitbox || !MovementComp) { return; }

  auto pAudioComp = _Char->FindComponentByClass<UAudioComponent>();
  if (pAudioComp)
  {
    pAudioComp->SetSound(m_pFireSound);
    pAudioComp->SetVolumeMultiplier(1.8f);
    pAudioComp->Play();
  }

  Hitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  Hitbox->SetBoxExtent(FVector(120.0f, 70.0f, 70.0f));
  MovementComp->MaxWalkSpeed = 900.0f;
  MovementComp->GravityScale = 0.0f;
  MovementComp->StopMovementImmediately();

  _Char->DisableInput(UGameplayStatics::GetPlayerController(_Char->GetWorld(), 0));

  TArray<USkeletalMeshComponent*> SkeletalMeshComps;
  _Char->GetComponents(SkeletalMeshComps);
  for (auto& pSMComp : SkeletalMeshComps)
  {
    if ("KirbyFire" == pSMComp->GetName())
    {
      pSMComp->SetHiddenInGame(false);
    }
    else
    {
      pSMComp->SetHiddenInGame(true);
    }
  }
}

void FireState::Stop(ACharacter* _Char)
{
  auto Hitbox = _Char->FindComponentByClass<UBoxComponent>();
  auto MovementComp = _Char->FindComponentByClass<UCharacterMovementComponent>();
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();
  auto KirbyChar = Cast<AKirby64Character>(_Char);
  if (!Hitbox || !CopyComp || !MovementComp) { return; }

  auto pAudioComp = _Char->FindComponentByClass<UAudioComponent>();
  if (pAudioComp)
  {
    pAudioComp->Stop();
    pAudioComp->SetVolumeMultiplier(1.0f);
  }

  Hitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
  Hitbox->SetBoxExtent(FVector(25.0f, 25.0f, 25.0f));
  MovementComp->MaxWalkSpeed = 600.0f;
  MovementComp->GravityScale = 2.0f;
  m_ActiveTime = 0.0f;

  KirbyChar->ExitAbility(CopyComp);
  _Char->EnableInput(UGameplayStatics::GetPlayerController(_Char->GetWorld(), 0));

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
}