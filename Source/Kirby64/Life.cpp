#include "Life.h"

#include "Kismet/GameplayStatics.h"

#include "Kirby64Character.h"

ULife::ULife()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULife::BeginPlay()
{
	Super::BeginPlay();
}


void ULife::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULife::RemoveChance()
{
  if (m_Chances >= 0)
  {
    m_Chances--;
    if (m_Chances < 0)
    {
      auto pOwner = GetOwner();
      if (pOwner->ActorHasTag("Player"))
      {
        UGameplayStatics::OpenLevel(pOwner, "GameOverMenu");
      }
      else
      {
        pOwner->Destroy();
      }
    }
    else
    {
      auto pOwner = GetOwner();
      if (!pOwner->ActorHasTag("Player")) { return; }
      auto pPlayer = Cast<AKirby64Character>(pOwner);
      if (!pPlayer) { return; }

      SetHealth(6);
      pPlayer->ResetPlayerLocation();
    }
  }
}