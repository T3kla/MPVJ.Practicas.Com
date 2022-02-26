#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyControllerCpp.generated.h"

UCLASS()
class COM_05_API AAIEnemyControllerCpp : public AAIController
{
    GENERATED_BODY()

  public:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    float TravelDelay = 1.f;

  protected:
    AAIEnemyControllerCpp();

    virtual void BeginPlay() override;

    virtual void OnMoveCompleted(FAIRequestID RequestID,
                                 const FPathFollowingResult &Result) override;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UAIPerceptionComponent *PerceptionCompCpp;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UAISenseConfig_Sight *SenseSightCompCpp;

  private:
    TArray<AActor *> Waypoints;
    int WaypointNum;
    AActor *CurrentWaypoint;
    int CurrentWaypointIdx;

    bool Chasing;

    UFUNCTION()
    void OnPerceptionUpdated(const TArray<AActor *> &UpdatedActors);

    void FollowRoute(bool Success = true);
    void FollowRouteDelay();
};
