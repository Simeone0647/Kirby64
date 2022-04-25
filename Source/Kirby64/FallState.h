// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "State.h"

class ACharacter;

class KIRBY64_API FallState : public State
{
public:

	FallState() = default;

	~FallState() = default;

  virtual eSTATES CheckState(ACharacter* _Char) override;

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) override;

  virtual void Enter(ACharacter* _Char) override;

  virtual void Exit(ACharacter* _Char) override;
};
