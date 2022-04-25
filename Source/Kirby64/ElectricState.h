#pragma once

#include "CoreMinimal.h"

#include "State.h"

class KIRBY64_API ElectricState : public State
{
public:

	ElectricState();

	~ElectricState() = default;

  virtual eSTATES CheckState(ACharacter* _Char) override
  {
    return eSTATES::kElectric;
  }

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override {}

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;

private:

  class USoundWave* m_pElectricSound;
};
