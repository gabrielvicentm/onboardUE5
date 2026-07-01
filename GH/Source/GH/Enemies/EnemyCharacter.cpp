// Copyright Epic Games, Inc. All Rights Reserved.

#include "Enemies/EnemyCharacter.h"

#include "Components/HealthComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddDynamic(this, &AEnemyCharacter::HandleHealthChanged);
		HealthComponent->OnDeath.AddDynamic(this, &AEnemyCharacter::HandleDeath);
	}
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HealthComponent || HealthComponent->IsDead())
	{
		return;
	}

	ACharacter* PlayerTarget = GetPlayerTarget();
	if (!PlayerTarget)
	{
		return;
	}

	const FVector ToPlayer = PlayerTarget->GetActorLocation() - GetActorLocation();
	const float DistanceToPlayer = ToPlayer.Size();

	if (DistanceToPlayer > AttackRange)
	{
		AddMovementInput(ToPlayer.GetSafeNormal(), 1.0f);
	}
	else
	{
		TryAttackPlayer(PlayerTarget);
	}
}

ACharacter* AEnemyCharacter::GetPlayerTarget() const
{
	return UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void AEnemyCharacter::TryAttackPlayer(ACharacter* PlayerTarget)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const float CurrentTime = World->GetTimeSeconds();
	if (CurrentTime - LastAttackTime < AttackCooldown)
	{
		return;
	}

	LastAttackTime = CurrentTime;

	UHealthComponent* PlayerHealth = PlayerTarget->FindComponentByClass<UHealthComponent>();
	if (!PlayerHealth || PlayerHealth->IsDead())
	{
		return;
	}

	PlayerHealth->ApplyDamage(AttackDamage, this);

	UE_LOG(LogTemp, Warning, TEXT("%s attacked %s for %.1f damage."), *GetName(), *PlayerTarget->GetName(), AttackDamage);

	if (bDrawDebug)
	{
		DrawDebugSphere(World, GetActorLocation(), AttackRange, 16, FColor::Red, false, 0.5f);
		DrawDebugLine(World, GetActorLocation(), PlayerTarget->GetActorLocation(), FColor::Red, false, 0.5f, 0, 2.0f);
	}
}

void AEnemyCharacter::HandleHealthChanged(
	UHealthComponent* ChangedHealthComponent,
	float CurrentHealth,
	float Delta,
	AActor* DamageCauser
)
{
	UE_LOG(LogTemp, Warning, TEXT("%s health changed: %.1f"), *GetName(), CurrentHealth);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.0f,
			FColor::Yellow,
			FString::Printf(TEXT("Enemy hit: %.1f HP"), CurrentHealth)
		);
	}
}

void AEnemyCharacter::HandleDeath(UHealthComponent* DeadHealthComponent, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Error, TEXT("%s died."), *GetName());

	SetActorEnableCollision(false);

	if (GetMesh())
	{
		GetMesh()->SetVisibility(false);
	}

	Destroy();
}
