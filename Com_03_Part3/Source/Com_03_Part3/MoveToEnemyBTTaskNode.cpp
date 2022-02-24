#include "MoveToEnemyBTTaskNode.h"
#include "AIEnemyCppController.h"

UMoveToEnemyBTTaskNode::UMoveToEnemyBTTaskNode()
{
    bNotifyTick = true;
}

EBTNodeResult::Type UMoveToEnemyBTTaskNode::ExecuteTask(UBehaviorTreeComponent &OwnerComp,
                                                        uint8 *NodeMemory)
{
    return EBTNodeResult::InProgress;
}

void UMoveToEnemyBTTaskNode::TickTask(class UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory,
                                      float DeltaSeconds)
{
    AAIEnemyCppController *AIEnemyCppController = Cast<AAIEnemyCppController>(OwnerComp.GetOwner());

    EPathFollowingRequestResult::Type MoveToActorResult = AIEnemyCppController->MoveToEnemy();

    if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal)
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

FString UMoveToEnemyBTTaskNode::GetStaticDescription() const
{
    return TEXT("Persigue al personaje principal");
}
