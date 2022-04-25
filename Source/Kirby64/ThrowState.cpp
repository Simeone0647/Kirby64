#include "ThrowState.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Enemy.h"
#include "AbilityObject.h"
#include "CopyCat.h"

ThrowState::ThrowState()
  : m_Delay(0.0f)
{}

eSTATES ThrowState::CheckState(ACharacter* _Char)
{
  if (m_Delay >= m_MaxDelay) { return eSTATES::kLagThrow; }

  return eSTATES::kThrow;
}

void ThrowState::Enter(ACharacter* _Char)
{
  auto MovementComp = _Char->FindComponentByClass<UCharacterMovementComponent>();
  if (!MovementComp) { return; }

  MovementComp->GravityScale = 0.0f;
  MovementComp->StopMovementImmediately();
  
  _Char->DisableInput(UGameplayStatics::GetPlayerController(_Char->GetWorld(), 0));
}

void ThrowState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  m_Delay += _DeltaTime;

  TArray<AActor*> Childs;
  _Char->GetAttachedActors(Childs);

  if (m_Delay >= m_MaxDelay)
  {
    if (0 != Childs.Num())
    {
      auto& pChild = Childs[0];
      if (pChild->ActorHasTag("Enemy"))
      {
        auto pObjectInside = Cast<AEnemy>(pChild);
        pObjectInside->SetState(eENEMYSTATES::kSpitted);
      }
      else
      {
        auto pObjectInside = Cast<AAbilityObject>(pChild);
        pObjectInside->ChangeState(eABILITYSTATES::kThrowed);
      }
    }
  }
}

void ThrowState::Exit(ACharacter* _Char)
{
  auto CopyComp = _Char->FindComponentByClass<UCopyCat>();
  auto MovementComp = _Char->FindComponentByClass<UCharacterMovementComponent>();
  if (!CopyComp || !MovementComp) { return; }

  CopyComp->RestoreAbility();

  MovementComp->GravityScale = 2.0f;
  m_Delay = 0.0f;
}