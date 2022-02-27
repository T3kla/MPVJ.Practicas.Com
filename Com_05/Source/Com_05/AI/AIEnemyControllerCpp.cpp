#include "AIEnemyControllerCpp.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
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

    CanChase = true;
    Chasing = false;
    ChaseTarget = nullptr;

    FollowRoute();
}

void AAIEnemyControllerCpp::OnMoveCompleted(FAIRequestID RequestID,
                                            const FPathFollowingResult &Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    auto Success = Result.IsSuccess();

    if (Success)
    {
        if (Chasing) // Caught player
        {
            StopChase();
            BlockChasing();
        }
        else // Reached waypoint
        {
            AllowChasing();
        }

        FollowRoute();
    }
}

void AAIEnemyControllerCpp::OnPerceptionUpdated(const TArray<AActor *> &UpdatedActors)
{
    TArray<AActor *> Perceived;
    PerceptionCompCpp->GetCurrentlyPerceivedActors(SenseSightCompCpp->GetSenseImplementation(),
                                                   Perceived);

    GEngine->AddOnScreenDebugMessage(1, 100.f, FColor::Orange,
                                     FString::Printf(TEXT("Perceived Actors: %d"), Perceived.Num()),
                                     true, {2.f, 2.f});

    if (!CanChase)
        return;

    if (Perceived.Num() > 0) // Perceived player
    {
        ChaseTarget = Perceived[0];
        StartChase();
    }
    else // Lost player
    {
        StopChase();
        FollowRoute();
    }
}

void AAIEnemyControllerCpp::FollowRoute()
{
    if (WaypointNum <= 0)
        return;

    FTimerHandle Handle;
    GetWorldTimerManager().SetTimer(Handle, this, &AAIEnemyControllerCpp::FollowRouteDelay,
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

void AAIEnemyControllerCpp::StartChase()
{
    if (!CanChase || !ChaseTarget)
        return;

    SetChasing(true);
    StopMovement();
    MoveToActor(ChaseTarget, -1.0f, true, true, false, 0, true);
}

void AAIEnemyControllerCpp::StopChase()
{
    ChaseTarget = nullptr;

    SetChasing(false);
    StopMovement();
}

void AAIEnemyControllerCpp::AllowChasing()
{
    CanChase = true;
}

void AAIEnemyControllerCpp::BlockChasing()
{
    CanChase = false;
}

void AAIEnemyControllerCpp::SetChasing(bool State)
{
    if (State)
        GEngine->AddOnScreenDebugMessage(2, 100.f, FColor::Cyan, TEXT("Chasing: true"), true,
                                         {2.f, 2.f});
    else
        GEngine->AddOnScreenDebugMessage(2, 100.f, FColor::Cyan, TEXT("Chasing: false"), true,
                                         {2.f, 2.f});

    Chasing = State;
}