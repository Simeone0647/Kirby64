#include "FireBreathState.h"

#include "Niagara/Public/NiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

FireBreathState::FireBreathState()
  : m_TimeActive(0.0f),
    m_CollisionSet(false)
{}

eENEMYSTATES FireBreathState::CheckState(ACharacter* _Enemy)
{
  if (m_TimeActive >= m_MaxTimeActive) { return eENEMYSTATES::kFireStandby; }

  return eENEMYSTATES::kFireBreath;
}

void FireBreathState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  m_TimeActive += _DeltaTime;

  if (m_TimeActive >= m_MaxTimeActive * 0.1f && !m_CollisionSet)
  {
    TArray<UCapsuleComponent*> CapsuleCollisions;
    _Char->GetComponents(CapsuleCollisions);

    for (auto& CapsuleColl : CapsuleCollisions)
    {
      if ("Hitbox" == CapsuleColl->GetName())
      {
        m_CollisionSet = true;
        CapsuleColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        CapsuleColl->SetCapsuleHalfHeight(240.0f);
        CapsuleColl->SetCapsuleRadius(77.0f);
        CapsuleColl->SetRelativeLocation(FVector(0.0f, 320.0f, 0.0f));

        break;
      }
    }
  }
}

void FireBreathState::Enter(ACharacter* _Char)
{
  auto FireParticles = _Char->FindComponentByClass<UNiagaraComponent>();
  if (FireParticles) { FireParticles->Activate(); }
}

void FireBreathState::Exit(ACharacter* _Char)
{
  m_TimeActive = 0.0f;
  m_CollisionSet = false;

  auto FireParticles = _Char->FindComponentByClass<UNiagaraComponent>();
  if (FireParticles) { FireParticles->Deactivate(); }

  TArray<UCapsuleComponent*> CapsuleCollisions;
  _Char->GetComponents(CapsuleCollisions);

  for (auto& CapsuleColl : CapsuleCollisions)
  {
    if ("Hitbox" == CapsuleColl->GetName())
    {
      CapsuleColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
      CapsuleColl->SetCapsuleHalfHeight(77.0f);
      CapsuleColl->SetCapsuleRadius(72.0f);
      CapsuleColl->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

      break;
    }
  }
}