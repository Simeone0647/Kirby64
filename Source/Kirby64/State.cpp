#include "State.h"

#include "Kirby64Character.h"
#include "GameFramework/Character.h"
#include "CopyCat.h"

void State::Update(const float& _DeltaTime, ACharacter* _Char)
{
  auto KirbyChar = Cast<AKirby64Character>(_Char);

  if (KirbyChar->GetDirection() < 0.0f)
  {
    if (!KirbyChar->FinishedRotating())
    { 
      const auto YawRotation = FMath::Lerp(KirbyChar->GetActorRotation().Yaw, 90.0f, 0.3f);
      FRotator NewRotation(0.0f, YawRotation, 0.0f);

      KirbyChar->SetActorRotation(NewRotation);

      if (90 == FMath::RoundToInt(YawRotation))
      {
        KirbyChar->ToggleFinishedRotating(true);
        NewRotation.Yaw = 90.0f;
        KirbyChar->SetActorRotation(NewRotation);
      }
    }
  }
  else if (KirbyChar->GetDirection() > 0.0f)
  {
    if (!KirbyChar->FinishedRotating())
    {
      const auto YawRotation = FMath::Lerp(KirbyChar->GetActorRotation().Yaw, -90.0f, 0.3f);
      FRotator NewRotation(0.0f, YawRotation, 0.0f);

      KirbyChar->SetActorRotation(NewRotation);

      if (-90 == FMath::RoundToInt(YawRotation))
      {
        KirbyChar->ToggleFinishedRotating(true);
        NewRotation.Yaw = -90.0f;
        KirbyChar->SetActorRotation(NewRotation);
      }
    }
  }
}

///void State::Exit(ACharacter* _Char)
///{
///  auto KirbyChar = Cast<AKirby64Character>(_Char);
///  KirbyChar->ExitAbility();
///}