#include "AIEnemyControllerCpp.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIEnemyControllerCpp::AAIEnemyControllerCpp()
{
    PerceptionCompCpp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("UIPerceptionCompCpp"));
    SenseSightCompCpp = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSightCompCpp"));

    PerceptionCompCpp->ConfigureSense(*SenseSightCompCpp);
    PerceptionCompCpp->SetDominantSense(SenseSightCompCpp->GetSenseImplementation());

    PerceptionCompCpp->OnPerceptionUpdated.__Internal_AddDynamic(this, )
}
