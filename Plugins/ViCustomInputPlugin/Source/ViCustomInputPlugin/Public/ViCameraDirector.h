// Copyright Devcoder. All Rights Reserved.
#pragma once
#include <GameFramework/Actor.h>
#include "ViCameraDirector.generated.h"

UCLASS() 
class VICUSTOMINPUTPLUGIN_API AViCameraDirector : public AActor
{
    GENERATED_BODY()

public:
    AViCameraDirector();

    virtual void BeginPlay() override;
    virtual void Tick( float InDeltaSeconds ) override;

public:
    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void StartChangeCamera();
    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void StopChangeCamera();
    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void NextChangeCamera();
    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void RestoreCamera();

private:
    void ChangeCamera( AActor* InCamera );
    AActor* GetNextCamera();

private:
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings", meta=(AllowPrivateAccess = "true") )
    TArray<AActor*> Cameras;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings", meta=(AllowPrivateAccess = "true") )
    float SmoothBlendTime;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings", meta=(AllowPrivateAccess = "true") )
    float TimeBetweenCameraChanges;

private:
    int32 NextIndex;
    bool ChangingCamera;
    TSharedPtr<class FViDelayExecutor> DelayExecutor;
    TWeakObjectPtr<AActor> SavedCamera;
};
