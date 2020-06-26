// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnemyProjectile.generated.h"

UCLASS()

class FPSDEMO_API AEnemyProjectile : public AActor {
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AEnemyProjectile();

protected:
    UPROPERTY()
    UProjectileMovementComponent *ProjectileMovementComponent;

    UPROPERTY()
    UCapsuleComponent *CapsuleComponent;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    // Ensure components exist on Actor
    void EnsureComponents();

};
