#include "Enemy.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

#include "Life.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

  static ConstructorHelpers::FObjectFinder<USoundWave>SoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Misc/Clash.Clash'"));
  if (SoundAsset.Succeeded()) { m_pClashSound = SoundAsset.Object; }
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
  GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnSpitted);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  auto StateInstance = m_SM.GetState(m_CurrentState);
  if (!StateInstance) { return; }

  auto NewLogicState = StateInstance->CheckState(this);

  if (NewLogicState != m_CurrentState)
  {
    StateInstance->Exit(this);

    if (m_SM.StateExist(NewLogicState)) { m_CurrentState = NewLogicState; }

    m_SM.GetState(m_CurrentState)->Enter(this);
  }
  
  StateInstance = m_SM.GetState(m_CurrentState);
  if (!StateInstance) { return; }
  m_SM.GetState(m_CurrentState)->Update(DeltaTime, this);
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnSpitted(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (eENEMYSTATES::kSpitted == m_CurrentState)
  {
    if (OtherActor->ActorHasTag("CameraTrigger") || OtherActor->ActorHasTag("Player") || OtherActor == this) { return; }

    if (OtherActor->ActorHasTag("Enemy"))
    {
      if ("Body" == OtherComp->GetName())
      {
        Destroy();
        auto pLifeComp = OtherActor->FindComponentByClass<ULife>();
        if (!pLifeComp) { return; }

        pLifeComp->DoDamage(15);
      }
    }
    else
    {
      Destroy();
    }

    UGameplayStatics::PlaySound2D(this->GetWorld(), m_pClashSound);
  }
}
