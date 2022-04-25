#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Food.generated.h"

UCLASS()
class KIRBY64_API AFood : public AActor
{
	GENERATED_BODY()
	
public:	
	AFood();

	virtual void Tick(float DeltaTime) override;

  UFUNCTION()
    void OnTaked(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                 bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:
 
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"), DisplayName = "MeshComp")
    UStaticMeshComponent* m_pSM;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"), DisplayName = "Capsule Component")
    class UCapsuleComponent* m_pCapsuleComp;

	UPROPERTY(EditAnywhere, Category = Food, DisplayName = "Health")
    int32 m_Health;

  class USoundWave* m_pGrabSound;
};
