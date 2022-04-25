#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySM.h"
#include "AbilityObject.generated.h"

UCLASS()
class KIRBY64_API AAbilityObject : public AActor
{
	GENERATED_BODY()
	
public:

	AAbilityObject();

  virtual void Tick(float DeltaTime) override;

	void Init(const FString& _AbilityName);

	void ChangeState(const eABILITYSTATES& _NewState);

  UFUNCTION()
  void OnThrowed(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                 bool bFromSweep, const FHitResult& SweepResult);
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"), DisplayName = "MeshComp")
  UStaticMeshComponent* m_pSM;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"), DisplayName = "Capsule Component")
  class UCapsuleComponent* m_pCapsuleComp;

  UMaterial* m_pStoredMaterial;

  UMaterialInstanceDynamic* m_pDynamicMaterialInst;

	TMap<FString, UTexture*> m_mTextures;

	AbilitySM m_SM;

	eABILITYSTATES m_CurrentState;
};
