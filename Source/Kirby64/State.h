#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class eSTATES : uint8
{
  kIdle = 0 UMETA(DisplayName = "Idle"),
  kWalking UMETA(DisplayName = "Walk"),
  kJumping UMETA(DisplayName = "Jump"),
  kFloating UMETA(DisplayName = "Float"),
	kFlying UMETA(DisplayName = "Fly"),
	kFalling UMETA(DisplayName = "Fall"),
  kAbsorbing UMETA(DisplayName = "Absorb"),
  kEating UMETA(DisplayName = "Eat"),
	kInhale UMETA(DisplayName = "Inhale"),
	kIce UMETA(DisplayName = "Ice Attack"),
	kFire UMETA(DisplayName = "Fire Attack"),
	kElectric UMETA(DisplayName = "Spark Attack"),
	kSpit UMETA(DisplayName = "Spit"),
	kSpitEnemy UMETA(DisplayName = "SpitEnemy"),
	kCarry UMETA(DisplayName = "Carry"),
	kThrow UMETA(DisplayName = "Throw"),
	kLagThrow UMETA(DisplayName = "LagThrow"),
  kUnknown UMETA(DisplayName = "Unknown"),
  kNumStates UMETA(DisplayName = "States Number")
};

class KIRBY64_API State
{

public:

	State() = default;

	virtual ~State() = default;

	virtual eSTATES CheckState(ACharacter* _Char)
	{
	  return eSTATES::kUnknown;
	}

	virtual void Update(const float& _DeltaTime, ACharacter* _Char);

	virtual void Enter(ACharacter* _Char) {}

	virtual void Exit(ACharacter* _Char) {}

};
