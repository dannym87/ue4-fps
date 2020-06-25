// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAiController.h"
#include "PlayerCharacter.h"

void AEnemyAiController::BeginPlay() {
    Super::BeginPlay();
    EnsureAiComponents();
}

void AEnemyAiController::EnsureAiComponents() {
    if (!ensure(BlackboardToUse)) {
        return;
    }
    UseBlackboard(BlackboardToUse, BB);

    if (!ensure(BehaviourTree)) {
        return;
    }
    RunBehaviorTree(BehaviourTree);

    AIPerceptionComponent = FindComponentByClass<UAIPerceptionComponent>();
    if (!ensure(AIPerceptionComponent)) {
        return;
    }

    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAiController::AIStimilusTrigger);
}

void AEnemyAiController::AIStimilusTrigger(AActor *Actor, FAIStimulus Stimulus) {
    APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(Actor);

    if (!PlayerCharacter) {
        return;
    }

    if (Stimulus.WasSuccessfullySensed()) {
        if (Stimulus.Tag == FName("Sound")) {
            BB->SetValueAsVector(FName("TargetLocation"), Stimulus.StimulusLocation);
            BB->SetValueAsBool(FName("CanHearPlayer"), true);
        } else {
            BB->SetValueAsBool(FName("SeenPlayerPreviously"), true);
            BB->SetValueAsBool(FName("CanSeePlayer"), true);
        }
    } else {
        BB->SetValueAsBool(FName("CanSeePlayer"), false);
    }
}
