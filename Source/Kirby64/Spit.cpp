#include "Spit.h"

#include "Components/CapsuleComponent.h"

#include "Life.h"

ASpit::ASpit()
{
	PrimaryActorTick.bCanEverTick = true;

  m_pCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Comp"));
  m_pCapsuleComp->SetupAttachment(GetRootComponent());
  m_pCapsuleComp->SetCapsuleHalfHeight(24.0f);
  m_pCapsuleComp->SetCapsuleRadius(24.0f);
  m_pCapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ASpit::OnCollide);
  m_pCapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

  m_pSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontSpitMesh"));
  m_pSM->SetupAttachment(m_pCapsuleComp);
  m_pSM->SetCollisionEnabled(ECollisionEnabled::NoCollision);

  static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
  if (MeshAsset.Succeeded())
  {
    UStaticMesh* pAsset = MeshAsset.Object;
    m_pSM->SetStaticMesh(pAsset);
  }

  static ConstructorHelpers::FObjectFinder<UMaterial>Mat(TEXT("Material'/Game/Materials/Stage/BasicMaskedMat.BasicMaskedMat'"));
  if (Mat.Succeeded())
  {
    m_pStoredMaterial = Mat.Object;
  }

  static ConstructorHelpers::FObjectFinder<UTexture2D>SpitTex(TEXT("Texture2D'/Game/Textures/Ability/Spit.Spit'"));
  if (SpitTex.Succeeded())
  {
    m_pTex = SpitTex.Object;
  }

  m_Direction = 0.0f;
  m_TimeAlive = 0.0f;
}

void ASpit::BeginPlay()
{
	Super::BeginPlay();
	
  if (m_pStoredMaterial)
  {
    auto pDynamicMaterialInst = UMaterialInstanceDynamic::Create(m_pStoredMaterial, m_pSM);
    pDynamicMaterialInst->SetTextureParameterValue(TEXT("Texture"), m_pTex);
    m_pSM->SetMaterial(0, pDynamicMaterialInst);
  }

  m_pCapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASpit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  m_TimeAlive += DeltaTime;

  if (m_TimeAlive >= m_MaxTimeAlive) { Destroy(); }

  const auto& Location = GetActorLocation();
  SetActorLocation(FVector(Location.X, (Location.Y + 8.0f * m_Direction), Location.Z));
}

void ASpit::OnCollide(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                      bool bFromSweep, const FHitResult& SweepResult)
{
  if (!OtherActor->ActorHasTag("Player") && !OtherActor->ActorHasTag("CameraTrigger"))
  {
    auto pLife = OtherActor->FindComponentByClass<ULife>();
    if (!pLife) { return; }

    if (1 == pLife->GetHealth())
    {
      pLife->DoDamage(1);
    }

    Destroy();
  }
}

void ASpit::SetDirection(const float& _Direction)
{
  m_Direction = _Direction;
  if (m_Direction < 0.0f) { m_pSM->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); }
}