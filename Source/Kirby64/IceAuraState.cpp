#include "IceAuraState.h"

#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Niagara/Public/NiagaraComponent.h"

IceAuraState::IceAuraState()
  : m_IceTime(0.0f)
{}

eENEMYSTATES IceAuraState::CheckState(ACharacter* _Enemy)
{
  if (m_IceTime >= m_MaxIceTime) { return eENEMYSTATES::kIceStandby; }

  return eENEMYSTATES::kIceAura;
}

void IceAuraState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  m_IceTime += _DeltaTime;
}

void IceAuraState::Enter(ACharacter* _Char)
{

  TArray<USphereComponent*> SphereComps;
  _Char->GetComponents(SphereComps);
  for (auto& pSphereComp : SphereComps)
  {
    if ("Hitbox" == pSphereComp->GetName())
    {
      pSphereComp->SetSphereRadius(120.0f);
      pSphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

      break;
    }
  }

  auto IceEmitter = _Char->FindComponentByClass<UNiagaraComponent>();
  if (IceEmitter)
  {
    IceEmitter->Activate();
  }
}

void IceAuraState::Exit(ACharacter* _Char)
{
  m_IceTime = 0.0f;

  TArray<USphereComponent*> SphereComps;
  _Char->GetComponents(SphereComps);
  for (auto& pSphereComp : SphereComps)
  {
    if ("Hitbox" == pSphereComp->GetName())
    {
      pSphereComp->SetSphereRadius(36.0f);
      pSphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

      break;
    }
  }

  auto IceEmitter = _Char->FindComponentByClass<UNiagaraComponent>();
  if (IceEmitter) { IceEmitter->Deactivate(); }
}