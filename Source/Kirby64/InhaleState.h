#pragma once

#include "CoreMinimal.h"
#include "State.h"

class ACharacter;

class KIRBY64_API InhaleState : public State
{
public:

	InhaleState();

	~InhaleState() = default;

  virtual eSTATES CheckState(ACharacter* _Char) override
  {
    return eSTATES::kInhale;
  }

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;

private:

  class USoundWave* m_pInhaleStartSound;

  class USoundWave* m_pInhaleEndSound;

  bool m_SetLoop;

  float m_Timer;
};
