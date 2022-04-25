#include "AbilityObject.h"

#include "Components/CapsuleComponent.h"

#include "Life.h"

AAbilityObject::AAbilityObject()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Comp"));
	m_pCapsuleComp->SetupAttachment(GetRootComponent());
	m_pCapsuleComp->SetCapsuleHalfHeight(24.0f);
	m_pCapsuleComp->SetCapsuleRadius(24.0f);
	m_pCapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AAbilityObject::OnThrowed);
	m_pCapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_pSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StarMesh"));
	m_pSM->SetupAttachment(m_pCapsuleComp);
  static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Models/Ability/Single_Star_Nemu_0_0_342.Single_Star_Nemu_0_0_342'"));
	if (MeshAsset.Succeeded())
	{
    UStaticMesh* pAsset = MeshAsset.Object;
    m_pSM->SetStaticMesh(pAsset);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Mat(TEXT("Material'/Game/Materials/Ability/AbilityMat.AbilityMat'"));
	if (Mat.Succeeded())
	{
	  m_pStoredMaterial = Mat.Object;
		m_pDynamicMaterialInst = UMaterialInstanceDynamic::Create(m_pStoredMaterial, m_pSM);
		m_pSM->SetMaterial(0, m_pDynamicMaterialInst);
	}

  static ConstructorHelpers::FObjectFinder<UTexture2D>FireTex(TEXT("Texture2D'/Game/Textures/Ability/star_Fire.star_Fire'"));
	if (FireTex.Succeeded())
	{
	  m_mTextures.Emplace("Fire", FireTex.Object);
	}

  static ConstructorHelpers::FObjectFinder<UTexture2D>IceTex(TEXT("Texture2D'/Game/Textures/Ability/star_Ice.star_Ice'"));
  if (IceTex.Succeeded())
  {
    m_mTextures.Emplace("Ice", IceTex.Object);
  }
  static ConstructorHelpers::FObjectFinder<UTexture2D>SparkTex(TEXT("Texture2D'/Game/Textures/Ability/star_Spark.star_Spark'"));
  if (SparkTex.Succeeded())
  {
    m_mTextures.Emplace("Spark", SparkTex.Object);
  }

	m_CurrentState = eABILITYSTATES::kUnknown;
}

void AAbilityObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAbilityObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto& pState = m_SM.GetState(m_CurrentState);
	if (!pState) { return; }

	auto NewLogicState = pState->CheckState(this);
  if (NewLogicState != m_CurrentState) { ChangeState(NewLogicState); }
  m_SM.GetState(m_CurrentState)->Update(DeltaTime, this);
}

void AAbilityObject::Init(const FString& _AbilityName)
{
	if (m_mTextures.Contains(_AbilityName))
	{
	  m_pDynamicMaterialInst->SetTextureParameterValue(TEXT("Albedo"), m_mTextures[_AbilityName]);
  }

	Tags.Add(*_AbilityName);
}

void AAbilityObject::ChangeState(const eABILITYSTATES& _NewState)
{
	const auto& pOldState = m_SM.GetState(m_CurrentState);
	if (pOldState) { pOldState->Exit(this); }

	m_CurrentState = _NewState;

	const auto& pNewState = m_SM.GetState(m_CurrentState);
	if (pNewState) { pNewState->Enter(this); }
}

void AAbilityObject::OnThrowed(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
															int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (eABILITYSTATES::kThrowed == m_CurrentState)
  {
  //  if (!OtherActor->ActorHasTag("CameraTrigger") && !OtherActor->ActorHasTag("Player"))
  //  {
  //    Destroy();
	//
  //    if (OtherActor->ActorHasTag("Enemy")) { OtherActor->Destroy(); }
  //  }
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
  }
}