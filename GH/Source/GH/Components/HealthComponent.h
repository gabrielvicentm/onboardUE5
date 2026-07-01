#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
    FOnHealthChangedSignature,
    UHealthComponent*, HealthComponent,
    float, CurrentHealth,
    float, Delta,
    AActor*, DamageCauser
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnDeathSignature,
    UHealthComponent*, HealthComponent,
    AActor*, DamageCauser
);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GH_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHealthComponent();

    UFUNCTION(BlueprintCallable, Category="Health")
    void ApplyDamage(float DamageAmount, AActor* DamageCauser);

    UFUNCTION(BlueprintCallable, Category="Health")
    void Heal(float HealAmount);

    UFUNCTION(BlueprintPure, Category="Health")
    float GetCurrentHealth() const { return CurrentHealth; }

    UFUNCTION(BlueprintPure, Category="Health")
    float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintPure, Category="Health")
    bool IsDead() const { return bIsDead; }

    UPROPERTY(BlueprintAssignable, Category="Health")
    FOnHealthChangedSignature OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category="Health")
    FOnDeathSignature OnDeath;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health")
    float MaxHealth = 100.0f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Health")
    float CurrentHealth = 0.0f;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Health")
    bool bIsDead = false;
};