// Copyright Devcoder. All Rights Reserved.
#pragma once
#include <GameFramework/Actor.h>
#include "ViControllableActor.generated.h"

UCLASS() 
class VICUSTOMINPUTPLUGIN_API AViControllableActor : public AActor
{
    GENERATED_BODY()

public:
    AViControllableActor();

    virtual void BeginPlay() override;
    virtual void EndPlay( const EEndPlayReason::Type InEndPlayReason ) override;

public:
    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void SetTargetActor( AActor* InTargetActor );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void AddXPositionOfLocation( float InValue );
    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void AddYPositionOfLocation( float InValue );
    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void AddZPositionOfLocation( float InValue );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void AddPitchOfRotation( float InValue );
    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void AddYawOfRotation( float InValue );
    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    void AddRollOfRotation( float InValue );

private:
    void InitializeDefaultInputBindings();
    void SetSavedMobility();
    void RestoreMobility();

private:
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings", meta=(AllowPrivateAccess = "true") )
    bool EnableDefaultInputBindings;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings", meta=(AllowPrivateAccess = "true") )
    float MovementSpeed;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings", meta=(AllowPrivateAccess = "true") )
    float RotationSpeed;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings", meta=(AllowPrivateAccess = "true") )
    AActor* TargetActor;

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey ForwardKey;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey BackwardKey;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey RightKey;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey LeftKey;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey UpKey;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey DownKey;

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey PitchUpKey;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey PitchDownKey;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey YawRightKey;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey YawLeftKey;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey RollCWKey;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="VCIP|Settings|Keys", meta=(AllowPrivateAccess = "true") )
    FKey RollCCWKey;

    bool IsSavedMobility;
    TEnumAsByte<EComponentMobility::Type> SavedMobility;
};
