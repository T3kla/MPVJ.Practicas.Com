#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "AIEnemyTargetPoint.generated.h"

UCLASS()
class COM_03_PART3_API AAIEnemyTargetPoint : public ATargetPoint
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ejercicio")
    int32 m_iPosition;
};
