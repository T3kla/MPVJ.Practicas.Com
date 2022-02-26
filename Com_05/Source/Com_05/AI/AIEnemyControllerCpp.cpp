#include "AIEnemyControllerCpp.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "Waypoint.h"

// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
//                                  FString::Printf(TEXT("Waypoints.Num(): %d"), Waypoints.Num()));

AAIEnemyControllerCpp::AAIEnemyControllerCpp()
{
    PerceptionCompCpp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("UIPerceptionCompCpp"));
    SenseSightCompCpp = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSightCompCpp"));

    PerceptionCompCpp->ConfigureSense(*SenseSightCompCpp);
    PerceptionCompCpp->SetDominantSense(SenseSightCompCpp->GetSenseImplementation());

    PerceptionCompCpp->OnPerceptionUpdated.AddDynamic(this,
                                                      &AAIEnemyControllerCpp::OnPerceptionUpdated);
}

void AAIEnemyControllerCpp::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), Waypoints);

    WaypointNum = Waypoints.Num();
    CurrentWaypoint = Waypoints[0];
    CurrentWaypointIdx = 0;
    Chasing = false;

    FollowRoute();
}

void AAIEnemyControllerCpp::OnMoveCompleted(FAIRequestID RequestID,
                                            const FPathFollowingResult &Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    FollowRoute(Result.IsSuccess());
}

void AAIEnemyControllerCpp::OnPerceptionUpdated(const TArray<AActor *> &UpdatedActors)
{
    GEngine->AddOnScreenDebugMessage(
        1, 100.f, FColor::Orange,
        FString::Printf(TEXT("Perceived Actors: %d"), UpdatedActors.Num()), true, {2.f, 2.f});

    if (UpdatedActors.Num() > 0)
    {
        if (!Chasing)
        {
            StopMovement();
            MoveToActor(UpdatedActors[0], -1.0f, true, true, false, 0, true);
        }

        Chasing = true;
    }
    else
    {
        Chasing = false;
        FollowRoute();
    }
}

void AAIEnemyControllerCpp::FollowRoute(bool Success)
{
    if (!Success)
        return;

    if (WaypointNum <= 0)
        return;

    FTimerHandle UnusedHandle;
    GetWorldTimerManager().SetTimer(UnusedHandle, this, &AAIEnemyControllerCpp::FollowRouteDelay,
                                    TravelDelay, false);
}

void AAIEnemyControllerCpp::FollowRouteDelay()
{
    MoveToActor(CurrentWaypoint, -1.0f, true, true, false, 0, true);

    CurrentWaypointIdx++;
    if (CurrentWaypointIdx >= WaypointNum)
        CurrentWaypointIdx = 0;
    CurrentWaypoint = Waypoints[CurrentWaypointIdx];
}
