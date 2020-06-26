// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Sound/SoundWave.h"
#include "EnemyProjectile.h"
#include "Weapon.generated.h"

UCLASS()
class FPSDEMO_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
    // Particle system to spawn at muzzle when weapon is fired
    UPROPERTY(EditAnywhere)
    UParticleSystem* MuzzleFlash;

    // Sound to play when projectile is fired
    UPROPERTY(EditAnywhere)
    USoundWave* ShootingSound;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AEnemyProjectile> ProjectileBlueprint;

    // Delay between firing projectiles
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FireRate = .1f;

    // Tracks whether parent holding the weapon is dead
    UPROPERTY(BlueprintReadWrite, Category = "Default")
    bool IsParentDead = false;

    UPROPERTY()
    USkeletalMeshComponent* WeaponMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Fire weapon
	UFUNCTION(BlueprintCallable)
	void Fire();

private:
	// Ensure Components are set
	void EnsureComponents();

};
