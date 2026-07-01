#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = MaxHealth;
    bIsDead = false;
}

void UHealthComponent::ApplyDamage(float DamageAmount, AActor* DamageCauser)
{
    if (bIsDead || DamageAmount <= 0.0f)
    {
        return;
    }

    const float PreviousHealth = CurrentHealth;
    CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
    const float Delta = CurrentHealth - PreviousHealth;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("%s recebeu %.1f de dano. Vida: %.1f / %.1f"),
        *GetOwner()->GetName(),
        DamageAmount,
        CurrentHealth,
        MaxHealth
    );

    OnHealthChanged.Broadcast(this, CurrentHealth, Delta, DamageCauser);

    if (CurrentHealth <= 0.0f)
    {
        bIsDead = true;
        UE_LOG(LogTemp, Error, TEXT("%s morreu"), *GetOwner()->GetName());
        OnDeath.Broadcast(this, DamageCauser);
    }
}

void UHealthComponent::Heal(float HealAmount)
{
    if (bIsDead || HealAmount <= 0.0f)
    {
        return;
    }

    const float PreviousHealth = CurrentHealth;
    CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
    const float Delta = CurrentHealth - PreviousHealth;

    OnHealthChanged.Broadcast(this, CurrentHealth, Delta, nullptr);
}