// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIRandomBTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UAIRandomBTTaskNode::UAIRandomBTTaskNode()
{
	NodeName = "Task Aim Location";
}

EBTNodeResult::Type UAIRandomBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Blackboard || !Controller)
		return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn)
		return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);

	if (!NavSys)
		return EBTNodeResult::Failed;

	FNavLocation TempNewLocation;
	const auto Found = NavSys->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), this->Radius, TempNewLocation);
	if (!Found)
		return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(this->AimLocationKey.SelectedKeyName, TempNewLocation);
	return EBTNodeResult::Succeeded;
}
