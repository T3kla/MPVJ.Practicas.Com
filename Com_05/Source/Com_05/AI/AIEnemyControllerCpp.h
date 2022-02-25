#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyControllerCpp.generated.h"

class UAIPerceptionComponent;

UCLASS()
class COM_05_API AAIEnemyControllerCpp : public AAIController
{
    GENERATED_BODY()

    AAIEnemyControllerCpp();

    UPROPERTY()
    UAIPerceptionComponent *PerceptionCompCpp;

    UPROPERTY()
    UAISenseConfig_Sight *SenseSightCompCpp;

    void PerceptionUpdated();
};
