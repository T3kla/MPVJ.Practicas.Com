#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToEnemyBTTaskNode.generated.h"

UCLASS()
class COM_03_PART3_API UMoveToEnemyBTTaskNode : public UBTTaskNode
{
    GENERATED_BODY()

    UMoveToEnemyBTTaskNode();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp,
                                            uint8 *NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory,
                          float DeltaSeconds) override;
    virtual FString GetStaticDescription() const override;
};
