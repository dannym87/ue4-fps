// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
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
    bool IsShooting = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    bool IsDead = false;

    UPROPERTY(VisibleAnywhere, Category = "Collision")
    UCapsuleComponent *Capsule;

    UPROPERTY(VisibleAnywhere, Category = "Rendering")
    USkeletalMeshComponent *SkeletalMesh;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()

    void OnHit(AActor *Actor, AActor *Other, FVector NormalImpulse, const FHitResult &Hit);

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

private:
    void EnsureComponents();

};
