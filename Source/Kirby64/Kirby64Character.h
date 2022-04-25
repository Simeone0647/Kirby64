// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StateMachine.h"
#include "Kirby64Character.generated.h"

UCLASS(config=Game)
class AKirby64Character : public ACharacter
{
	GENERATED_BODY()

public:
  
  AKirby64Character();

  void BeginPlay();

  FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }

  FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

  FORCEINLINE float GetDirection() { return m_Direction; }

  FORCEINLINE bool FinishedRotating() { return m_FinishedRotating; }

  FORCEINLINE void ToggleFinishedRotating(const bool& _Value) { m_FinishedRotating = _Value; }

  FORCEINLINE uint32 GetJumpCount() { return m_JumpCount; }

  FORCEINLINE void SetJumpCount(const uint32& _NumJumps) { m_JumpCount = _NumJumps; }

  FORCEINLINE void UpdateFloatingTime(const float& _DeltaTime) { m_FloatingTime += _DeltaTime; }

  FORCEINLINE void ResetFloatingTime() { m_FloatingTime = 0.0f; }

  FORCEINLINE float GetFloatingTime() { return m_FloatingTime; }

  FORCEINLINE float GetMaxFloatingTime() { return m_MaxFloatingTime; }

  void ExitAbility(class UCopyCat* _CopyComp);

  UFUNCTION(BlueprintCallable)
  FORCEINLINE eSTATES GetCurrentState() { return m_CurrentState; }

  UFUNCTION(BlueprintCallable)
  void SetBoomRotationAndSocketOffset(const FRotator& _NewRotator, const FVector& _NewSocketOffset);

  FORCEINLINE void
  ResetPlayerLocation()
  {
    SetActorLocation(m_InitialPosition);
  }

protected:

	void MoveRight(float Val);

	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

  void DoAction();

  void CancelAction();

	void Tick(float DeltaTime);

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

  UFUNCTION()
  void OnInhale(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                bool bFromSweep, const FHitResult& SweepResult);

  UFUNCTION()
  void OnEating(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							  bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnJump();

	UFUNCTION()
	void OnSwallow();

  UFUNCTION()
  void OnDestroy(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								 bool bFromSweep, const FHitResult& SweepResult);

  UFUNCTION()
  void OnQuitAbility();

private:

  FORCEINLINE void ChangeState(const eSTATES& _NewState)
  {
    const auto& pOldState = m_SM.GetState(m_CurrentState);
    if (pOldState) { pOldState->Exit(this); }

    m_CurrentState = _NewState;

    const auto& pNewState = m_SM.GetState(m_CurrentState);
    if (pNewState) { pNewState->Enter(this); }
  }

private:

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* SideViewCameraComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

  float m_Direction;

  bool m_FinishedRotating;

  StateMachine m_SM;

  eSTATES m_CurrentState;

  uint32 m_JumpCount;

  float m_FloatingTime;

  const float m_MaxFloatingTime = 20.0f;

  TMap<FString, class UNiagaraComponent*> m_AbilitiesParticles;

  class USoundWave* m_pFlySound;

  class USoundWave* m_pSwallowSound;

  FVector m_InitialPosition;

  bool m_InhalingObject;
};
