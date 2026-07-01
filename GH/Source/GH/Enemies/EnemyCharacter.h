// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UHealthComponent;

UCLASS()
class GH_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	float AttackDamage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	float AttackRange = 140.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	float AttackCooldown = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
	float MoveSpeed = 250.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Debug")
	bool bDrawDebug = true;

	UFUNCTION()
	void HandleHealthChanged(UHealthComponent* ChangedHealthComponent, float CurrentHealth, float Delta, AActor* DamageCauser);

	UFUNCTION()
	void HandleDeath(UHealthComponent* DeadHealthComponent, AActor* DamageCauser);

private:
	float LastAttackTime = -999.0f;

	ACharacter* GetPlayerTarget() const;
	void TryAttackPlayer(ACharacter* PlayerTarget);
};
