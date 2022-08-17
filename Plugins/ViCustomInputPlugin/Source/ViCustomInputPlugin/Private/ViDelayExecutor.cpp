#include "ViDelayExecutor.h"
#include "ViCustomInputPluginPCH.h"

FViDelayExecutor::FViDelayExecutor()
{
    DelayTime = 0.0f;
}

FViDelayExecutor::FViDelayExecutor( UWorld* InWorld, float InDelayTime, TFunction<void()>&& InAction )
    : World( InWorld )
    , DelayTime( InDelayTime )
    , Action( MoveTemp( InAction ) )
{
}

bool FViDelayExecutor::Execute()
{
    if ( ensure( World.IsValid() ) ) {
        auto& tm = World->GetTimerManager();
        if ( tm.IsTimerActive( TimerHandle ) )
            return false;

        tm.SetTimer( TimerHandle, [this]{ Action(); }, DelayTime, false );
    }

    return false;
}
