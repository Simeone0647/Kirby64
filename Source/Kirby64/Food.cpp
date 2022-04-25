#include "Food.h"

#include "Components/CapsuleComponent.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Life.h"

AFood::AFood()
{
	PrimaryActorTick.bCanEverTick = true;

  m_pCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Comp"));
  m_pCapsuleComp->SetupAttachment(GetRootComponent());
  m_pCapsuleComp->SetCapsuleHalfHeight(24.0f);
  m_pCapsuleComp->SetCapsuleRadius(24.0f);
  m_pCapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AFood::OnTaked);
  m_pCapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  
  m_pSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StarMesh"));
  m_pSM->SetupAttachment(m_pCapsuleComp);

  static ConstructorHelpers::FObjectFinder<USoundWave>SoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Misc/GrabItem.GrabItem'"));
  if (SoundAsset.Succeeded()) { m_pGrabSound = SoundAsset.Object; }
}

void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  auto NewRotation = GetActorRotation();
  NewRotation.Yaw += 0.8f;
  SetActorRotation(NewRotation);
}

void AFood::OnTaked(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor->ActorHasTag("Player") && "Hurtbox" == OtherComp->GetName())
  {
    auto pLifeComp = OtherActor->FindComponentByClass<ULife>();
    if (pLifeComp)
    {
      UGameplayStatics::PlaySound2D(this->GetWorld(), m_pGrabSound, 2.0f);
      pLifeComp->AddHealth(m_Health);
      Destroy();
    }
  }
}
