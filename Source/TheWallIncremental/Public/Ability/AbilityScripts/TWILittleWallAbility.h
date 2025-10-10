// Public/Ability/TWILittleWallAbility.h
#pragma once
#include "Ability/TWIAbility.h"
#include "TWILittleWallAbility.generated.h"

UCLASS()
class ATWILittleWallAbility : public ATWIAbility
{
	GENERATED_BODY()
public:
	ATWILittleWallAbility();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wall")
	float MaxHP = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	float CurrentHP = 300.f;

	virtual void OnActivate() override;
	virtual void OnEnd() override;

public:
	UFUNCTION(BlueprintCallable, Category="Wall")
	void ApplyDamage(float Amount);
};
