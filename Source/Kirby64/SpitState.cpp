#include "SpitState.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"

#include "CopyCat.h"
#include "Spit.h"

SpitState::SpitState()
  : m_TimeActive(0.0f)
{
  static ConstructorHelpers::FObjectFinder<USoundWave>SoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Kirby/Spit.Spit'"));
  if (SoundAsset.Succeeded()) { m_pSpitSound = SoundAsset.Object; }
}

eSTATES SpitState::CheckState(ACharacter* _Char)
{
  if (m_TimeActive >= m_MaxTimeActive)
  {
    return eSTATES::kFalling;
  }

  return eSTATES::kSpit;
}

void SpitState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  m_TimeActive += _DeltaTime;
}

void SpitState::Enter(ACharacter* _Char)
{
  auto MovementComp = _Char->GetCharacterMovement();
  if (!MovementComp) { return; }

  MovementComp->GravityScale = 0.0f;
  MovementComp->StopMovementImmediately();

  auto pSpit = _Char->GetWorld()->SpawnActor<ASpit>(ASpit::StaticClass());
  if (pSpit)
  {
    auto Dir = (_Char->GetActorForwardVector().Y >= 0) ? 1.0f : -1.0f;
    pSpit->SetDirection(Dir);
    const auto& PlayerLocation = _Char->GetActorLocation();
    pSpit->SetActorLocation(FVector(PlayerLocation.X, PlayerLocation.Y + (5.0f * Dir), PlayerLocation.Z));
    pSpit->SetActorRotation(FRotator(0.0f, 90.0f, -90.0f));
    pSpit->SetActorScale3D(FVector(1.3f, 1.3f, 1.3f));
  }

  UGameplayStatics::PlaySound2D(_Char->GetWorld(), m_pSpitSound);
}

void SpitState::Exit(ACharacter* _Char)
{
  m_TimeActive = 0.0f;

  auto MovementComp = _Char->GetCharacterMovement();
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();
  if (!CopyComp || !MovementComp) { return; }

  MovementComp->GravityScale = 2.0f;
  CopyComp->RestoreAbility();
}
