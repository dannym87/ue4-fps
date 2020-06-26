// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	EnsureComponents();
	UE_LOG(LogTemp, Warning, TEXT("spawning enemy projectile"));
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Ensure components exist on Actor
void AEnemyProjectile::EnsureComponents() {
    ProjectileMovementComponent = FindComponentByClass<UProjectileMovementComponent>();
    if (!ProjectileMovementComponent) {
        return;
    }

    CapsuleComponent = FindComponentByClass<UCapsuleComponent>();
    if (!CapsuleComponent) {
        return;
    }
}

