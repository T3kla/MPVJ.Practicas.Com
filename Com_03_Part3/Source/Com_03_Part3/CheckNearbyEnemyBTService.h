#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CheckNearbyEnemyBTService.generated.h"

UCLASS()
class COM_03_PART3_API UCheckNearbyEnemyBTService : public UBTService
{
    GENERATED_BODY()

    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory,
                          float DeltaSeconds) override;
};
