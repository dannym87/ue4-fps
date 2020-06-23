// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AiPerceptionComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAiController.generated.h"

/**
 * 
 */
UCLASS()
class FPSDEMO_API AEnemyAiController : public AAIController
{
	GENERATED_BODY()
protected:
    void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category="Blackboard")
    UBlackboardData* BlackboardToUse;

	UPROPERTY(EditDefaultsOnly, Category="Blackboard")
    UBehaviorTree* BehaviourTree;

	UPROPERTY()
	UBlackboardComponent* BB;

	UPROPERTY(VisibleAnywhere, Category="AI")
    UAIPerceptionComponent* AIPerceptionComponent;

private:
    UFUNCTION()
    void EnsureAiComponents();

    UFUNCTION()
    void AIStimilusTrigger(AActor* Actor, FAIStimulus Stimulus);
};
