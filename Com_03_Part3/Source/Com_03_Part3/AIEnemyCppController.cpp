#include "AIEnemyCppController.h"

#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIEnemyTargetPoint.h"
#include "EngineUtils.h"
#include "Containers/EnumAsByte.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

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
            pBlackboardComponent->SetValueAsVector("TargetPointPosition",
                                                   pTargetPoint->GetActorLocation());
            break;
        }
    }

    pBlackboardComponent->SetValueAsInt("TargetPointIndex", iTargetPointIndex + 1);
}

void AAIEnemyCppController::CheckNearbyEnemy()
{
    APawn *pPawn = GetPawn();

    FVector MultiSphereStart = pPawn->GetActorLocation();

    FVector MultiSphereEnd = MultiSphereStart + FVector(0.f, 0.f, 15.f);

    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

    TArray<AActor *> ActorsToIgnore;
    ActorsToIgnore.Add(pPawn);

    TArray<FHitResult> OutHits;

    bool bResult = UKismetSystemLibrary::SphereTraceMultiForObjects(
        GetWorld(), MultiSphereStart, MultiSphereEnd, 700, ObjectTypes, false, ActorsToIgnore,
        EDrawDebugTrace::ForDuration, OutHits, true, FLinearColor::Red, FLinearColor::Green, 0.5f);

    UBlackboardComponent *pBlackboardComponent = BrainComponent->GetBlackboardComponent();

    if (bResult)
    {
        for (int32 i = 0; i < OutHits.Num(); i++)
        {
            FHitResult Hit = OutHits[i];

            ACharacter *pCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

            if (Hit.GetActor() == pCharacter)
            {
                pBlackboardComponent->SetValueAsObject("TargetActorToFollow", pCharacter);
                break;
            }
        }
    }
    else
    {
        pBlackboardComponent->SetValueAsObject("TargetActorToFollow", nullptr);
    }
}

EPathFollowingRequestResult::Type AAIEnemyCppController::MoveToEnemy()
{
    UBlackboardComponent *pBlackboardComponent = BrainComponent->GetBlackboardComponent();

    AActor *pHeroCharacterActor =
        Cast<AActor>(pBlackboardComponent->GetValueAsObject("TargetActorToFollow"));

    EPathFollowingRequestResult::Type MoveToActorResult = MoveToActor(pHeroCharacterActor);

    return MoveToActorResult;
}
