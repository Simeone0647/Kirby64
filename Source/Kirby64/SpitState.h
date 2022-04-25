// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "State.h"
#include "CoreMinimal.h"

class KIRBY64_API SpitState : public State
{
public:

	SpitState();

	~SpitState() = default;

  eSTATES CheckState(ACharacter* _Char) override;

  void Update(const float& _DeltaTime, ACharacter* _Char) override;

  void Enter(ACharacter* _Char) override;

  void Exit(ACharacter* _Char) override;

 private:

  float m_TimeActive;

  const float m_MaxTimeActive = 0.2f;

  class USoundWave* m_pSpitSound;
};
