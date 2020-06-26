// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "EnemyProjectile.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	EnsureComponents();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::EnsureComponents() {
    WeaponMesh = FindComponentByClass<USkeletalMeshComponent>();
    if (!ensure(WeaponMesh)) {
        return;
    }

    if (!ensure(MuzzleFlash)) {
        return;
    }

    if (!ensure(ShootingSound)) {
        return;
    }

    if (!ensure(ProjectileBlueprint)) {
        return;
    }
}

void AWeapon::Fire() {
    FName MuzzleSocketName = FName("Muzzle");
    FVector MuzzleLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);
    FRotator MuzzleRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    FTransform MuzzleTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

    GetWorld()->SpawnActor<AEnemyProjectile>(ProjectileBlueprint, MuzzleTransform);
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, MuzzleLocation, MuzzleRotation, FVector(.1f, .1f, .1f));
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootingSound, MuzzleLocation, .1f);
}

