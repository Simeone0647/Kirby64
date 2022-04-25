#include "LagThrowState.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

LagThrowState::LagThrowState()
  : m_Delay(0.0f)
{}

eSTATES LagThrowState::CheckState(ACharacter* _Char)
{
  if (m_Delay >= m_MaxDelay) { return eSTATES::kIdle; }

  return eSTATES::kLagThrow;
}

void LagThrowState::Update(const float& _DeltaTime, ACharacter* _Char)
{
  m_Delay += _DeltaTime;
}

void LagThrowState::Exit(ACharacter* _Char)
{
  _Char->EnableInput(UGameplayStatics::GetPlayerController(_Char->GetWorld(), 0));
  m_Delay = 0.0f;
}