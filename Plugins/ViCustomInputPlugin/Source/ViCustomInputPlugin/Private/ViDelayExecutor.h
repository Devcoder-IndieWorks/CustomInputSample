// Copyright Devcoder. All Rights Reserved.
#pragma once
#include <CoreMinimal.h>
#include <Engine/EngineTypes.h>

class FViDelayExecutor final
{
public:
    FViDelayExecutor();
    FViDelayExecutor( class UWorld* InWorld, float InDelayTime, TFunction<void()>&& InAction );

    bool Execute();

private:
    TWeakObjectPtr<class UWorld> World;
    float DelayTime;
    TFunction<void()> Action;
    FTimerHandle TimerHandle;
};

