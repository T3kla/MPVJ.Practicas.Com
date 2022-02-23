#include "AIEnemyCppController.h"

#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIEnemyTargetPoint.h"
#include "EngineUtils.h"

void AAIEnemyCppController::UpdateNextTargetPoint()
{
    UBlackboardComponent *pBlackboardComponent = BrainComponent->GetBlackboardComponent();
    int32 iTargetPointIndex = pBlackboardComponent->GetValueAsInt("TargetPointIndex");

    if (iTargetPointIndex >= 4)
    {
        iTargetPointIndex = 0;
        pBlackboardComponent->SetValueAsInt("TargetPointIndex", iTargetPointIndex);
    }

    for (TActorIterator<AAIEnemyTargetPoint> It(GetWorld()); It; ++It)
    {
        AAIEnemyTargetPoint *pTargetPoint = *It;

        if (iTargetPointIndex == pTargetPoint->m_iPosition)
        {
            pBlackboardComponent->SetValueAsVector("TargetPointPosition", pTargetPoint->GetActorLocation());
            break;
        }
    }

    pBlackboardComponent->SetValueAsInt("TargetPointIndex", iTargetPointIndex + 1);
}
