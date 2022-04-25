#include "ElectricState.h"

#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

ElectricState::ElectricState()
{
  static ConstructorHelpers::FObjectFinder<USoundWave>SoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Abilities/Sparks.Sparks'"));
  if (SoundAsset.Succeeded()) { m_pElectricSound = SoundAsset.Object; }
}

void ElectricState::Enter(ACharacter* _Char)
{
  auto Hitbox = _Char->FindComponentByClass<UBoxComponent>();
  auto Movement = _Char->FindComponentByClass<UCharacterMovementComponent>();
  if (!Hitbox || !Movement) { return; }

  auto pAudioComp = _Char->FindComponentByClass<UAudioComponent>();
  if (pAudioComp)
  {
    pAudioComp->SetSound(m_pElectricSound);
    pAudioComp->SetVolumeMultiplier(1.8f);
    pAudioComp->Play();
  }

  Hitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  Hitbox->SetBoxExtent(FVector(90.0f, 90.0f, 90.0f));
  Movement->MaxWalkSpeed /= 4.0f;
  _Char->JumpMaxCount = 0;
}

void ElectricState::Exit(ACharacter* _Char)
{
  auto Hitbox = _Char->FindComponentByClass<UBoxComponent>();
  auto Movement = _Char->FindComponentByClass<UCharacterMovementComponent>();
  if (!Hitbox || !Movement) { return; }

  auto pAudioComp = _Char->FindComponentByClass<UAudioComponent>();
  if (pAudioComp)
  {
    pAudioComp->SetVolumeMultiplier(1.0f);
    pAudioComp->Stop();
  }

  Hitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
  Hitbox->SetBoxExtent(FVector(25.0f, 25.0f, 25.0f));
  Movement->MaxWalkSpeed *= 4.0f;
  _Char->JumpMaxCount = 6;
}