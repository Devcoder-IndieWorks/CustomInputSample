// Copyright Devcoder. All Rights Reserved.
#pragma once
#include <CoreMinimal.h>
#include <SlateBasics.h>
#include <UObject/ObjectMacros.h>
#include "ViCustomKeyBind.generated.h"

USTRUCT( BlueprintType ) 
struct FViCustomInputAction
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    FString ActionName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    FKey Key;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    FString KeyAsString;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    uint32 Shift:1;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    uint32 Ctrl:1;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    uint32 Alt:1;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    uint32 Cmd:1;

    //-------------------------------------------------------------------------

    FViCustomInputAction()
    {
    }

    FViCustomInputAction( const FString& InActionName, FKey InKey, bool InShift, bool InCtrl, bool InAlt, bool InCmd )
        : ActionName( InActionName )
        , Key( InKey )
        , KeyAsString( Key.GetDisplayName().ToString() )
        , Shift( InShift )
        , Ctrl( InCtrl )
        , Alt( InAlt )
        , Cmd( InCmd )
    {
    }

    FViCustomInputAction( const FInputActionKeyMapping& InAction )
        : ActionName( InAction.ActionName.ToString() )
        , Key( InAction.Key )
        , KeyAsString( InAction.Key.GetDisplayName().ToString() )
        , Shift( InAction.bShift )
        , Ctrl( InAction.bCtrl )
        , Alt( InAction.bAlt )
        , Cmd( InAction.bCmd )
    {
    }
};

USTRUCT( BlueprintType )
struct FViCustomInputAxis
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    FString AxisName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    FString KeyAsString;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    FKey Key;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="VCIP|Settings" )
    float Scale = 1.0f;

    //-------------------------------------------------------------------------

    FViCustomInputAxis()
    {
    }

    FViCustomInputAxis( const FString& InAxisName, FKey InKey, float InScale )
        : AxisName( InAxisName )
        , KeyAsString( InKey.GetDisplayName().ToString() )
        , Key( InKey )
        , Scale( InScale )
    {
    }

    FViCustomInputAxis( const FInputAxisKeyMapping& InAxis )
        : AxisName( InAxis.AxisName.ToString() )
        , KeyAsString( InAxis.Key.GetDisplayName().ToString() )
        , Key( InAxis.Key )
        , Scale( InAxis.Scale )
    {
    }
};
