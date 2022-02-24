#include "CheckNearbyEnemyBTService.h"
#include "AIEnemyCppController.h"

void UCheckNearbyEnemyBTService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory,
                                          float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIEnemyCppController *AIEnemyController = Cast<AAIEnemyCppController>(OwnerComp.GetOwner());
    AIEnemyController->CheckNearbyEnemy();
}
