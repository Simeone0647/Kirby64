#include "Kirby64Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"

#include "Enemy.h"
#include "Inhalable.h"
#include "FlyState.h"
#include "CopyCat.h"
#include "Life.h"

AKirby64Character::AKirby64Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	
	m_FinishedRotating = true;

  static ConstructorHelpers::FObjectFinder<USoundWave>FlySoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Kirby/Fly.Fly'"));
  if (FlySoundAsset.Succeeded()) { m_pFlySound = FlySoundAsset.Object; }

  static ConstructorHelpers::FObjectFinder<USoundWave>SwallowSoundAsset(TEXT("SoundWave'/Game/Sounds/Effects/Kirby/Swallow.Swallow'"));
  if (SwallowSoundAsset.Succeeded()) { m_pSwallowSound = SwallowSoundAsset.Object; }
}

void AKirby64Character::BeginPlay()
{
  Super::BeginPlay();

  TArray<UCapsuleComponent*> CapsulesComps;
  GetComponents(CapsulesComps);

  for (auto& CapsuleComp : CapsulesComps)
  {
    if ("InhaleTrigger" == CapsuleComp->GetName())
    {
      CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AKirby64Character::OnInhale);
			CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			break;
    }
  }

	TArray<USphereComponent*> SphereComps;
	GetComponents(SphereComps);

	for (auto& pSphereComp : SphereComps)
	{
		if ("InnerCollision" == pSphereComp->GetName())
		{
      pSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AKirby64Character::OnEating);
      pSphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			break;
		}
	}

	auto pHitBox = FindComponentByClass<UBoxComponent>();
	if (pHitBox)
	{
		pHitBox->OnComponentBeginOverlap.AddDynamic(this, &AKirby64Character::OnDestroy);
		pHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	TArray<UNiagaraComponent*> ParticlesComps;
	GetComponents(ParticlesComps);

	for (auto& ParticleComp : ParticlesComps)
	{
		ParticleComp->Deactivate();
		m_AbilitiesParticles.Emplace(ParticleComp->GetName(), ParticleComp);
	}

	m_CurrentState = eSTATES::kIdle;
	m_JumpCount = 0;
	m_FloatingTime = 0.0f;
	m_Direction = 0.0f;

	m_InitialPosition = GetActorLocation();
	m_InhalingObject = false;
}

void AKirby64Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const auto& CurrentLocation = GetActorLocation();
	if (CurrentLocation.X != m_InitialPosition.X)
	{
	  SetActorLocation(FVector(m_InitialPosition.X, CurrentLocation.Y, CurrentLocation.Z));
  }

	auto pCurrentState = m_SM.GetState(m_CurrentState);
	if (pCurrentState)
	{
		auto NewLogicState = pCurrentState->CheckState(this);
    if (NewLogicState != m_CurrentState) { ChangeState(NewLogicState); }
    m_SM.GetState(m_CurrentState)->Update(DeltaTime, this);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AKirby64Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKirby64Character::OnJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Swallow", IE_Pressed, this, &AKirby64Character::OnSwallow);
	PlayerInputComponent->BindAction("MainAction", IE_Pressed, this, &AKirby64Character::DoAction);
	PlayerInputComponent->BindAction("MainAction", IE_Released, this, &AKirby64Character::CancelAction);
	PlayerInputComponent->BindAction("QuitAbility", IE_Pressed, this, &AKirby64Character::OnQuitAbility);

	PlayerInputComponent->BindAxis("MoveRight", this, &AKirby64Character::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AKirby64Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AKirby64Character::TouchStopped);
}

void AKirby64Character::MoveRight(float Value)
{	
	if (m_FinishedRotating)
	{
    m_Direction = Value;

		if (0.0f != m_Direction)
		{
			m_FinishedRotating = false;
		}
	}

	AddMovementInput(FVector(0.f,-1.0f,0.f), Value);
}

void AKirby64Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AKirby64Character::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AKirby64Character::OnInhale(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto InhalableComp = OtherActor->FindComponentByClass<UInhalable>();
	if (!InhalableComp || "Body" != OtherComp->GetName()) { return; }

	InhalableComp->OnAbsorb(this);

	m_InhalingObject = true;
}

void AKirby64Character::OnEating(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
															   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  auto InhaleComponent = OtherActor->FindComponentByClass<UInhalable>();
	auto CopyComp = FindComponentByClass<UCopyCat>();

	if (!InhaleComponent || !CopyComp || "Body" != OtherComp->GetName()) { return; }
	
	InhaleComponent->SetIsBeingAbsorbed(false);

  TArray<UCapsuleComponent*> CapsuleColliders;
  OtherActor->GetComponents(CapsuleColliders);
  for (auto& CapsuleColl : CapsuleColliders)
  {
    CapsuleColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
  }

	auto StaticMesh = OtherActor->FindComponentByClass<UStaticMeshComponent>();
	if (StaticMesh)
	{
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		StaticMesh->SetVisibility(false);
	}
	else
	{
		auto SkeletalMesh = OtherActor->FindComponentByClass<USkeletalMeshComponent>();
		if (SkeletalMesh)
		{
		  SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			SkeletalMesh->SetVisibility(false);
	  }
	}

  EAttachmentRule LocationRule = EAttachmentRule::SnapToTarget;
  EAttachmentRule RotationRule = EAttachmentRule::SnapToTarget;
  EAttachmentRule ScaleRule = EAttachmentRule::SnapToTarget;

  FAttachmentTransformRules AttachRule(LocationRule, RotationRule, ScaleRule, false);

	OtherActor->AttachToActor(this, AttachRule);

	m_SM.GetState(m_CurrentState)->Exit(this);
	m_CurrentState = eSTATES::kEating;
	if (m_AbilitiesParticles.Contains(CopyComp->GetActiveAbility()))
	{
		m_AbilitiesParticles[CopyComp->GetActiveAbility()]->Deactivate();
	}
	m_SM.GetState(m_CurrentState)->Enter(this);

	m_InhalingObject = false;
}

void AKirby64Character::OnJump()
{
  if (eSTATES::kFlying == m_CurrentState && JumpCurrentCount < JumpMaxCount)
	{
    static_cast<FlyState*>(m_SM.GetState(m_CurrentState))->ResetFlyTime();
    UGameplayStatics::PlaySound2D(this->GetWorld(), m_pFlySound, 0.7f);
  }
	else if (eSTATES::kFloating == m_CurrentState && JumpCurrentCount < JumpMaxCount)
	{
	  UGameplayStatics::PlaySound2D(this->GetWorld(), m_pFlySound, 0.7f);
	}
	else if (JumpCurrentCount > 0 && JumpCurrentCount < JumpMaxCount)
	{
		UGameplayStatics::PlaySound2D(this->GetWorld(), m_pFlySound, 0.7f);
	}

  m_JumpCount++;

	Jump();
}

void AKirby64Character::OnSwallow()
{
	TArray<AActor*> ChildActors;
	GetAttachedActors(ChildActors);

	//If do not have an enemy inside...
	if (0 == ChildActors.Num()) { return; }

	const auto& pChild = ChildActors[0];
	if (eSTATES::kEating == m_CurrentState)
	{
    auto pCopyComp = FindComponentByClass<UCopyCat>();
		if (!pCopyComp) { return; }

    if (!pCopyComp->AssignAbility(pChild->Tags)) { pCopyComp->RestoreAbility(); }

    pChild->Destroy();
		UGameplayStatics::PlaySound2D(this->GetWorld(), m_pSwallowSound);
	}
	else if (eSTATES::kCarry == m_CurrentState)
	{
    auto StaticMesh = pChild->FindComponentByClass<UStaticMeshComponent>();
    if (StaticMesh) { StaticMesh->SetVisibility(false); }
    else
    {
      auto SkeletalMesh = pChild->FindComponentByClass<USkeletalMeshComponent>();
      if (SkeletalMesh) { SkeletalMesh->SetVisibility(false); }
    }

    pChild->SetActorScale3D(FVector(0.1f, 0.1f, 0.1f));
    pChild->SetActorRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

    ChangeState(eSTATES::kEating);
	}
}

void AKirby64Character::OnDestroy(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
																	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag("Enemy") || OtherActor == this) { return; }
	if ("Body" != OtherComp->GetName()) { return; }

	auto pLifeComp = OtherActor->FindComponentByClass<ULife>();
	if (!pLifeComp) { return; }

	pLifeComp->DoDamage(15);
}

void AKirby64Character::OnQuitAbility()
{
	if (eSTATES::kIdle == m_CurrentState ||
	    eSTATES::kWalking == m_CurrentState || 
			eSTATES::kEating == m_CurrentState)
	{
    const auto& pCopyComp = FindComponentByClass<UCopyCat>();
    if (!pCopyComp) { return; }

    const auto& ActiveAbility = pCopyComp->GetActiveAbility();
    if ("Inhale" != ActiveAbility && "Spit" != ActiveAbility &&
		    "Throw" != ActiveAbility)
    {
		  ChangeState(eSTATES::kCarry);
    }
	}
}

void AKirby64Character::DoAction()
{
  if (90 == FMath::RoundToInt(GetActorRotation().Yaw) ||
	    -90 == FMath::RoundToInt(GetActorRotation().Yaw))
	{
    auto CopyComp = FindComponentByClass<UCopyCat>();
	  if (!CopyComp) { return; }
	 
	  UNiagaraComponent* ActiveAbilityParticles = nullptr;
		if (m_AbilitiesParticles.Contains(CopyComp->GetActiveAbility()))
		{
			 ActiveAbilityParticles = m_AbilitiesParticles[CopyComp->GetActiveAbility()];
			 ActiveAbilityParticles->Activate();
		}
	  
		ChangeState(CopyComp->GetActiveAbilityState());
	}
}

void AKirby64Character::ExitAbility(UCopyCat* _CopyComp)
{
	if (m_AbilitiesParticles.Contains(_CopyComp->GetActiveAbility()))
	{
		m_AbilitiesParticles[_CopyComp->GetActiveAbility()]->Deactivate();
	}
	else
	{
		return;
	}

	ChangeState(eSTATES::kIdle);
}

void AKirby64Character::CancelAction()
{
  auto CopyComp = FindComponentByClass<UCopyCat>();
  if (!CopyComp) { return; }
  if ("Fire" == CopyComp->GetActiveAbility() || m_InhalingObject || "Spit" == CopyComp->GetActiveAbility()) { return; }

  TArray<AActor*> Childs;
  GetAttachedActors(Childs);
  if (Childs.Num() != 0 && "Inhale" == CopyComp->GetActiveAbility()) { return; }

	ExitAbility(CopyComp);
}

void AKirby64Character::SetBoomRotationAndSocketOffset(const FRotator& _NewRotator,
																											const FVector& _NewSocketOffset)
{
  CameraBoom->SetWorldRotation(_NewRotator);
	CameraBoom->SocketOffset = _NewSocketOffset;
}