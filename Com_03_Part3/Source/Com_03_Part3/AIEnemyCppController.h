#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyCppController.generated.h"

UCLASS()
class COM_03_PART3_API AAIEnemyCppController : public AAIController
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "Ejercicio")
    void UpdateNextTargetPoint();

    UFUNCTION(BlueprintCallable, Category = "Ejercicio")
    void CheckNearbyEnemy();
};
