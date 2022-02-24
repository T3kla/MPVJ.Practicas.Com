#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UpdateNextTargetPointBTTaskNode.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class COM_03_PART3_API UUpdateNextTargetPointBTTaskNode : public UBTTaskNode
{
    GENERATED_BODY()

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory);
    virtual FString GetStaticDescription() const override;
};
