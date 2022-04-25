#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spit.generated.h"

UCLASS()
class KIRBY64_API ASpit : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpit();


  UFUNCTION()
  void OnCollide(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                 bool bFromSweep, const FHitResult& SweepResult);

  virtual void Tick(float DeltaTime) override;


  void SetDirection(const float& _Direction);

protected:

	virtual void BeginPlay() override;

private:

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"), DisplayName = "MeshComp")
    UStaticMeshComponent* m_pSM;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"), DisplayName = "Capsule Component")
    class UCapsuleComponent* m_pCapsuleComp;

  UMaterial* m_pStoredMaterial;

  //UMaterialInstanceDynamic* m_pDynamicMaterialInst;
  UTexture2D* m_pTex;

  float m_Direction;

  float m_TimeAlive;

  const float m_MaxTimeAlive = 0.18f;
};
