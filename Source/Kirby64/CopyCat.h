#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "State.h"
#include "CopyCat.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KIRBY64_API UCopyCat : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCopyCat();

	~UCopyCat() = default;

  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  bool AssignAbility(TArray<FName> _Tags);

  eSTATES GetActiveAbilityState();

	void SetActiveAbility(const FString& _NewAbility)
	{
	  m_ActiveAbility = _NewAbility;
	}

	UFUNCTION(BlueprintCallable)
	  FString GetActiveAbility()
	  {
	  	return m_ActiveAbility;
	  }

	FORCEINLINE void StoreAbility()
	{
		if ("Spit" == m_ActiveAbility) { return; }

    m_StoredAbility = m_ActiveAbility;
	}

	FORCEINLINE void RestoreAbility()
	{
		m_ActiveAbility = m_StoredAbility;
		m_StoredAbility = "";
	}

	FORCEINLINE bool IsAbilityStored()
	{
		return ("" == m_StoredAbility) ? false : true;
	}

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> IceHitbox;

private:

  UPROPERTY(EditAnywhere, Category = Copycat, DisplayName = "Active Ability")
    FString m_ActiveAbility = "Inhale";

  FString m_StoredAbility;

	TMap<FString, eSTATES> m_Abilities;
};
