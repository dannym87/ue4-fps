// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerProjectile.h"
#include "EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter() {
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay() {
    Super::BeginPlay();
    EnsureComponents();
    OnActorHit.AddDynamic(this, &AEnemyCharacter::OnHit);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::OnHit(AActor *Actor, AActor *Other, FVector NormalImpulse, const FHitResult &Hit) {
    auto *Projectile = Cast<APlayerProjectile>(Other);
    if (!Projectile || IsDead) {
        return;
    }

    Health -= .2f;

    if (Health <= 0) {
        Capsule->DestroyComponent();
        SkeletalMesh->SetSimulatePhysics(true);
        IsDead = true;
    } else {

    }
}

void AEnemyCharacter::EnsureComponents() {
    Capsule = FindComponentByClass<UCapsuleComponent>();
    if (!ensure(Capsule)) {
        return;
    }

    SkeletalMesh = FindComponentByClass<USkeletalMeshComponent>();
    if (!ensure(SkeletalMesh)) {
        return;
    }
}
