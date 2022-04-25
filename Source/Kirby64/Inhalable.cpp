#include "Inhalable.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Components/BoxComponent.h"

#include "Enemy.h"

UInhalable::UInhalable()
{
  PrimaryComponentTick.bCanEverTick = true;

	m_pPlayerRef = nullptr;
}


// Called when the game starts
void UInhalable::BeginPlay()
{
	Super::BeginPlay();

	m_InhaledScale = FVector(0.1f, 0.1f, 0.1f);
	// ...
	
}

// Called every frame
void UInhalable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_BeingAbsorbed) { return; }

	const auto& ActorOwner = GetOwner();

	auto LPosition =  FMath::Lerp(ActorOwner->GetActorLocation(), m_pPlayerRef->GetActorLocation(), 0.1f);
	auto LScale = FMath::Lerp(ActorOwner->GetActorScale(), m_InhaledScale, 0.1f);

  ActorOwner->SetActorLocation(LPosition);
	ActorOwner->SetActorScale3D(LScale);
}

void UInhalable::OnAbsorb(AActor* _pPlayer)
{
  auto pOwner = GetOwner();
  m_pPlayerRef = _pPlayer;
	m_BeingAbsorbed = true;

  TArray<USphereComponent*> SphereComps;
  pOwner->GetComponents(SphereComps);
  for (auto& pSphereComp : SphereComps)
  {
    if ("Body" != pSphereComp->GetName())
    {
      pSphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
  }

  TArray<UCapsuleComponent*> CapsuleColliders;
  pOwner->GetComponents(CapsuleColliders);
  for (auto& pCapsuleComp : CapsuleColliders)
  {
    if ("Hitbox" == pCapsuleComp->GetName())
    {
      pCapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
    else
    {
      pCapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
  }

  TArray<UBoxComponent*> BoxColliders;
  pOwner->GetComponents(BoxColliders);
  for (auto& pBoxComp : BoxColliders)
  {
    pBoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
  }

  TArray<UNiagaraComponent*> NiagaraComps;
  pOwner->GetComponents(NiagaraComps);
  for (auto& pNiagaraComp : NiagaraComps)
  {
    pNiagaraComp->Deactivate();
  }

  auto Enemy = Cast<AEnemy>(pOwner);
  if (Enemy) { Enemy->SetState(eENEMYSTATES::kEUnknown); }
}