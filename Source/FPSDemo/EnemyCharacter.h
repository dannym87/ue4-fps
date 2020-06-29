// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequence.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Sound/SoundWave.h"
#include "Weapons/Weapon.h"
#include "EnemyCharacter.generated.h"

UCLASS()

class FPSDEMO_API AEnemyCharacter : public ACharacter {
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AEnemyCharacter();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    float Health = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    USoundWave *DyingSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    USoundWave *ReloadSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    UAnimSequence *ReloadAnimation;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    bool IsShooting = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
    bool IsDead = false;

    UPROPERTY(BlueprintReadWrite, Category = "Default")
    AWeapon *AIEquippedWeapon;

    UPROPERTY(VisibleAnywhere, Category = "Collision")
    UCapsuleComponent *Capsule;

    UPROPERTY(VisibleAnywhere, Category = "Rendering")
    USkeletalMeshComponent *SkeletalMesh;

    UPROPERTY()
    bool IsReloading = false;

    UFUNCTION(BlueprintCallable)
    void StartFiringWeapon();

    UFUNCTION(BlueprintCallable)
    void StopFiringWeapon();

    UFUNCTION()
    void OnHit(AActor *Actor, AActor *Other, FVector NormalImpulse, const FHitResult &Hit);

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called when actor takes damage
    virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

private:
    // Ensure all Components exist
    void EnsureComponents();

    // Kills an Enemy Player
    void Die();

    // Moves the Enemy Player to the Player Character location
    void MoveToPlayerCharacterLocation();

    // Fire Weapon
    void FireWeapon();

    // Reloading finished callback
    void ReloadComplete();
};
