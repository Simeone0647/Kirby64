// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class KIRBY64_API Ability
{
public:

	Ability() = default;

	~Ability() = default;

	virtual void EnterAction(AActor* _Owner) {}

	virtual void ExitAction(AActor* _Owner, bool& _AbilityActive) {}

	virtual void Update(const float& _DeltaTime, AActor* _Owner) {}
};
