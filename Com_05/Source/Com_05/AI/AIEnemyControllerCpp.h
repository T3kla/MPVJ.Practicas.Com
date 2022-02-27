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

    UPROPERTY(VisibleAnywhere)
    class UAIPerceptionComponent *PerceptionCompCpp;

    UPROPERTY(VisibleAnywhere)
    class UAISenseConfig_Sight *SenseSightCompCpp;

  private:
    UFUNCTION()
    void OnPerceptionUpdated(const TArray<AActor *> &UpdatedActors);

    TArray<AActor *> Waypoints;
    int WaypointNum;
    AActor *CurrentWaypoint;
    int CurrentWaypointIdx;

    bool Chasing;
    bool CanChase;
    AActor *ChaseTarget;

    void FollowRoute();
    void FollowRouteDelay();

    void StartChase();
    void StopChase();

    void AllowChasing();
    void BlockChasing();

    void SetChasing(bool State);
};
