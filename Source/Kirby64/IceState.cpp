#include "IceState.h"

#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

#include "CopyCat.h"

IceState::IceState()
{
  static ConstructorHelpers::FObjectFinder<USoundWave>SoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Abilities/Ice.Ice'"));
  if (SoundAsset.Succeeded()) { m_pIceSound = SoundAsset.Object; }
}

void IceState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  FRotator NewRotation = FRotator(0.0f, 2.0f, 0.0f);
  FQuat QuatRotation = FQuat(NewRotation);
  _Char->AddActorWorldRotation(QuatRotation);
}

void IceState::Enter(ACharacter* _Char)
{
  auto Hitbox = _Char->FindComponentByClass<UBoxComponent>();
  auto Movement = _Char->FindComponentByClass<UCharacterMovementComponent>();
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();

  if (!Hitbox || !Movement || !CopyComp) { return; }

  auto pAudioComp = _Char->FindComponentByClass<UAudioComponent>();
  if (pAudioComp)
  {
    pAudioComp->SetSound(m_pIceSound);
    pAudioComp->SetVolumeMultiplier(1.8f);
    pAudioComp->Play();
  }


  Hitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  Hitbox->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
  Movement->MaxWalkSpeed *= 0.25f;

  FVector Location = _Char->GetActorLocation();
  auto ForwardVec = _Char->GetActorForwardVector();
  FVector Offset(100.0f, 0.0f, 0.0f);

  for (uint32 i = 0; i < 3; ++i)
  {
    auto IceHitbox = (_Char->GetWorld()->SpawnActor<AActor>(CopyComp->IceHitbox, Location, FRotator::ZeroRotator));

    EAttachmentRule LocationRule = EAttachmentRule::SnapToTarget;
    EAttachmentRule RotationRule = EAttachmentRule::SnapToTarget;
    EAttachmentRule ScaleRule = EAttachmentRule::SnapToTarget;
    FAttachmentTransformRules AttachRule(LocationRule, RotationRule, ScaleRule, false);

    IceHitbox->AttachToActor(_Char, AttachRule);
    IceHitbox->SetActorRelativeLocation(Offset);
    m_Hitboxes.Add(IceHitbox);

    Offset.X += 100.0f;
  }

  TArray<USkeletalMeshComponent*> SkeletalMeshComps;
  _Char->GetComponents(SkeletalMeshComps);
  for (auto& pSMComp : SkeletalMeshComps)
  {
    if ("KirbyIce" == pSMComp->GetName())
    {
      pSMComp->SetHiddenInGame(false);
    }
    else
    {
      pSMComp->SetHiddenInGame(true);
    }
  }

  m_PreRotation = _Char->GetActorRotation();
  _Char->JumpMaxCount = 1;
}

void IceState::Exit(ACharacter* _Char)
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
  Hitbox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
  Movement->MaxWalkSpeed *= 4.0f;
  m_RotationSpeed = 0.0f;

  for (auto& IceHitbox : m_Hitboxes)
  {
    IceHitbox->Destroy();
  }
  m_Hitboxes.Empty();

  _Char->SetActorRotation(m_PreRotation);

  _Char->JumpMaxCount = 6;

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