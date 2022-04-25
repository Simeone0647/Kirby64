#include "EnemySparkState.h"

#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Niagara/Public/NiagaraComponent.h"

EnemySparkState::EnemySparkState()
  : m_SparkTime(0.0f)
{}

eENEMYSTATES EnemySparkState::CheckState(ACharacter* _Enemy)
{
  if (m_SparkTime >= m_MaxSparkTime) { return eENEMYSTATES::kSparkStandby; }

  return eENEMYSTATES::kESpark;
}

void EnemySparkState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  m_SparkTime += _DeltaTime;
}

void EnemySparkState::Enter(ACharacter* _Char)
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

  auto SparksEmitter = _Char->FindComponentByClass<UNiagaraComponent>();
  if (SparksEmitter)
  {
    SparksEmitter->Activate();
  }
}

void EnemySparkState::Exit(ACharacter* _Char)
{
  m_SparkTime = 0.0f;

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

  auto SparksEmitter = _Char->FindComponentByClass<UNiagaraComponent>();
  if (SparksEmitter) { SparksEmitter->Deactivate(); }
}
