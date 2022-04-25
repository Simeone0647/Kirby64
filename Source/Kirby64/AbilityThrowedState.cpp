#include "AbilityThrowedState.h"

#include "Kirby64Character.h"
#include "Components/CapsuleComponent.h"

AbilityThrowedState::AbilityThrowedState()
  : m_Direction(0.0f)
{}

void AbilityThrowedState::Enter(AActor* _Ability)
{
  _Ability->SetActorRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

  EDetachmentRule InLocationRule = EDetachmentRule::KeepWorld;
  EDetachmentRule InRotationRule = EDetachmentRule::KeepRelative;
  EDetachmentRule InScaleRule = EDetachmentRule::KeepWorld;

  FDetachmentTransformRules DetachRules(InLocationRule, InRotationRule, InScaleRule, false);
  _Ability->DetachFromActor(DetachRules);
  _Ability->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
  auto StaticMesh = _Ability->FindComponentByClass<UStaticMeshComponent>();
  if (StaticMesh)
  {
    StaticMesh->SetVisibility(true);
  }

  auto CapsuleComp = _Ability->FindComponentByClass<UCapsuleComponent>();
  CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


  auto pPlayerController = _Ability->GetWorld()->GetFirstPlayerController();
  auto pPawn = Cast<AKirby64Character>(pPlayerController->GetPawn());
  if (pPawn)
  {
    m_Direction = (pPawn->GetActorForwardVector().Y >= 0) ? 1.0f : -1.0f;
  }
}

void AbilityThrowedState::Update(const float& _DeltaTime, AActor* _Ability)
{
  FVector NewLocation = _Ability->GetActorLocation();
  NewLocation.Y += 7.0f * m_Direction;

  _Ability->SetActorLocation(NewLocation);
  FRotator NewRotation = _Ability->GetActorRotation();
  NewRotation.Yaw += 4.0f;
  _Ability->SetActorRotation(NewRotation);
}