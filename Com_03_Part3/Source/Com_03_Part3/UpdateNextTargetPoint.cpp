#include "UpdateNextTargetPoint.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIEnemyCppController.h"

EBTNodeResult::Type UUpdateNextTargetPoint::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    AAIEnemyCppController *AIEnemyController = Cast<AAIEnemyCppController>(OwnerComp.GetOwner());

    AIEnemyController->UpdateNextTargetPoint();

    return EBTNodeResult::Succeeded;
}

FString UUpdateNextTargetPoint::GetStaticDescription() const
{
    return TEXT("Actualiza el siguiente punto en el recorrido");
}
