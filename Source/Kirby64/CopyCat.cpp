#include "CopyCat.h"

#include "Components/CapsuleComponent.h"

UCopyCat::UCopyCat()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCopyCat::BeginPlay()
{
	Super::BeginPlay();

	m_Abilities.Emplace("Spark", eSTATES::kElectric);
  m_Abilities.Emplace("Fire", eSTATES::kFire);
  m_Abilities.Emplace("Ice", eSTATES::kIce);
	m_Abilities.Emplace("Inhale", eSTATES::kInhale);
	m_Abilities.Emplace("Spit", eSTATES::kSpit);
	m_Abilities.Emplace("SpitEnemy", eSTATES::kSpitEnemy);
	m_Abilities.Emplace("Throw", eSTATES::kThrow);
}

void UCopyCat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

eSTATES UCopyCat::GetActiveAbilityState()
{
  for (auto& Ability : m_Abilities)
  {
    if (m_ActiveAbility == Ability.Key)
    {
      return Ability.Value;
    }
  }

	return eSTATES::kUnknown;
}

bool UCopyCat::AssignAbility(TArray<FName> _Tags)
{
	for (auto& Tag : _Tags)
	{
		for (auto& Ability : m_Abilities)
		{
			if (Tag.ToString() == Ability.Key)
			{
			  m_ActiveAbility = Ability.Key;

				return true;
			}
		}
	}

	return false;
}
