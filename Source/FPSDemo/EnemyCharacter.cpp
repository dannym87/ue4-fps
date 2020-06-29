// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerProjectile.h"
#include "PlayerCharacter.h"
#include "AI/EnemyAiController.h"

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

void AEnemyCharacter::EnsureComponents() {
    Capsule = FindComponentByClass<UCapsuleComponent>();
    if (!ensure(Capsule)) {
        return;
    }

    SkeletalMesh = FindComponentByClass<USkeletalMeshComponent>();
    if (!ensure(SkeletalMesh)) {
        return;
    }

    if (!ensure(DyingSound)) {
        return;
    }
}

void AEnemyCharacter::OnHit(AActor *Actor, AActor *Other, FVector NormalImpulse, const FHitResult &Hit) {
    auto *Projectile = Cast<APlayerProjectile>(Other);
    if (!Projectile || IsDead) {
        return;
    }

    Health -= .25f;

    if (Health <= 0) {
        Die();
    } else {
        MoveToPlayerCharacterLocation();
    }
}

float AEnemyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
    if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID)) {
        Health -= Damage;

        if (Health <= 0) {
            Die();
        }
    }

    return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemyCharacter::Die() {
    Capsule->DestroyComponent();
    SkeletalMesh->SetSimulatePhysics(true);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DyingSound, GetActorLocation(), GetActorRotation(), .2f);
    IsDead = true;
    AIEquippedWeapon->SetIsParentDead(true);
}

void AEnemyCharacter::MoveToPlayerCharacterLocation() {
    AEnemyAiController *AIController = Cast<AEnemyAiController>(GetController());
    if (!AIController) {
        return;
    }

    ACharacter *PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!PlayerCharacter) {
        return;
    }

    AIController->MoveToLocation(PlayerCharacter->GetActorLocation());
}

void AEnemyCharacter::StartFiringWeapon() {
    IsShooting = true;
    FireWeapon();
}

void AEnemyCharacter::StopFiringWeapon() {
    IsShooting = false;
}

void AEnemyCharacter::FireWeapon() {
    if (!IsShooting || IsDead || IsReloading) {
        return;
    }

    FTimerHandle FireDelay;
    int32 Ammo = AIEquippedWeapon->Fire();

    if (Ammo <= 0) {
        IsReloading = true;
        AIEquippedWeapon->Reload();
        // todo: Make this more intelligent and find cover
        GetCharacterMovement()->MaxWalkSpeed = 0.f;
        GetMesh()->PlayAnimation(ReloadAnimation, false);
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, GetActorLocation(), GetActorRotation(), .2f);
        GetWorldTimerManager().SetTimer(FireDelay, this, &AEnemyCharacter::ReloadComplete, 2.3f);
        return;
    }

    GetWorldTimerManager().SetTimer(FireDelay, this, &AEnemyCharacter::FireWeapon, AIEquippedWeapon->GetFireRate());
}

void AEnemyCharacter::ReloadComplete() {
    IsReloading = false;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    FireWeapon();
}
