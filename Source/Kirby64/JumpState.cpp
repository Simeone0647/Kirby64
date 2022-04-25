#include "JumpState.h"

#include "Kirby64Character.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"

JumpState::JumpState()
{
  static ConstructorHelpers::FObjectFinder<USoundWave>SoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Kirby/Jump.Jump'"));
  if (SoundAsset.Succeeded()) { m_pJumpSound = SoundAsset.Object; }
}

eSTATES JumpState::CheckState(ACharacter* _Char)
{
  auto movementComp = _Char->GetCharacterMovement();
  
  if (movementComp)
  {
    if (movementComp->GetLastUpdateVelocity().Z < 0.0f)
    {
      return eSTATES::kFalling;
    }
    else if (movementComp->GetLastUpdateVelocity().Z == 0.0f)
    {
      return eSTATES::kIdle;
    }
    else if (_Char->JumpCurrentCount > 1)
    {
      return eSTATES::kFlying;
    }
  }

  return eSTATES::kJumping;
}

void JumpState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  State::Update(_DeltaTime, _Char);

  UE_LOG(LogTemp, Warning, TEXT("In Jump State"));
}

void JumpState::Enter(ACharacter* _Char)
{
  UGameplayStatics::PlaySound2D(_Char->GetWorld(), m_pJumpSound, 0.8f);
}