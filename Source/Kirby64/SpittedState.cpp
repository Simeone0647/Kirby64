#include "SpittedState.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "Kirby64Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CopyCat.h"

SpittedState::SpittedState()
  : m_Direction(0.0f)
{}

void SpittedState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  FVector NewLocation = _Char->GetActorLocation();
  NewLocation.Y += 7.0f * m_Direction;

  _Char->SetActorLocation(NewLocation);
  FRotator NewRotation = _Char->GetActorRotation();
  NewRotation.Yaw += 4.0f;
  _Char->SetActorRotation(NewRotation);
}

void SpittedState::Enter(ACharacter* _Char)
{
  auto MovementComp = _Char->FindComponentByClass<UCharacterMovementComponent>();
  if (MovementComp) { MovementComp->GravityScale = 0.0f; }

  _Char->SetActorRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

  EDetachmentRule InLocationRule = EDetachmentRule::KeepWorld;
  EDetachmentRule InRotationRule = EDetachmentRule::KeepRelative;
  EDetachmentRule InScaleRule = EDetachmentRule::KeepWorld;

  FDetachmentTransformRules DetachRules(InLocationRule, InRotationRule, InScaleRule, false);
  _Char->DetachFromActor(DetachRules);

  _Char->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));

  auto StaticMesh = _Char->FindComponentByClass<UStaticMeshComponent>();
  if (StaticMesh)
  {
    StaticMesh->SetVisibility(true);
  }
  else
  {
    auto SkeletalMesh = _Char->FindComponentByClass<USkeletalMeshComponent>();
    if (SkeletalMesh)
    {
      SkeletalMesh->SetVisibility(true);
    }
  }

  auto CapsuleComp = _Char->FindComponentByClass<UCapsuleComponent>();
  CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


  auto pPlayerController = _Char->GetWorld()->GetFirstPlayerController();
  auto pPawn = Cast<AKirby64Character>(pPlayerController->GetPawn());
  if (pPawn)
  {
    m_Direction = (pPawn->GetActorForwardVector().Y >= 0) ? 1.0f : -1.0f;
  }
}