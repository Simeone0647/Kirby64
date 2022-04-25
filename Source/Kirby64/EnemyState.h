#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class eENEMYSTATES : uint8
{
  kFireStandby = 0 UMETA(DisplayName = "Fire Standby"),
  kFireBreath UMETA(DisplayName = "Fire Breath"),
  kSparkStandby UMETA(DisplayName = "Spark Standby"),
  kESpark UMETA(DisplayName = "Spark Attack"),
  kSparkJump UMETA(DisplayName = "Spark Jump"),
  kIceStandby UMETA(DisplayName = "Frost Standby"),
  kIceMoving UMETA(DisplayName = "Frost Moving"),
  kIceAura UMETA(DisplayName = "Frost Attack"),
  kSpitted UMETA(DisplayName = "Spitted"),
  kNeutralStandby UMETA(DisplayName = "Neutral Standby"),
  kNeutralMoving UMETA(DisplayName = "Neutral Moving"),
  kEUnknown UMETA(DisplayName = "Unknown"),
  kENumStates UMETA(DisplayName = "States Count")
};

class KIRBY64_API EnemyState
{
public:

	EnemyState() = default;

	virtual ~EnemyState() = default;

  virtual eENEMYSTATES CheckState(ACharacter* _Enemy)
  {
    return eENEMYSTATES::kEUnknown;
  }

  virtual void Update(const float& _DeltaTime, ACharacter* _Char) {}

  virtual void Enter(ACharacter* _Char) {}

  virtual void Exit(ACharacter* _Char) {}

};
