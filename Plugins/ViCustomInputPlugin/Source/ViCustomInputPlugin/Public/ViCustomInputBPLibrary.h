// Copyright Devcoder. All Rights Reserved.
#pragma once
#include <Kismet/BlueprintFunctionLibrary.h>
#include "ViCustomKeyBind.h"
#include "ViCustomInputBPLibrary.generated.h"

UCLASS()
class VICUSTOMINPUTPLUGIN_API UViCustomInputBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static void PressButtonByID( int32 InButtonID = 1 );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static void ReleaseButtonByID( int32 InButtonID = 1 );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static void SetAxisValueByID( int32 InAxisID = 1, float InValue = 0.0f );

    //-------------------------------------------------------------------------

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static FViCustomInputAxis GetInputAxisFromMouseButtonEvent( const FPointerEvent& InMouseEvent );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static FViCustomInputAxis GetInputAxisFromMouseAxisEvent( const FPointerEvent& InMouseEvent );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static FViCustomInputAction GetInputActionFromMouseButtonEvent( const FPointerEvent& InMouseEvent );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static FViCustomInputAxis GetInputAxisFromKeyEvent( const FKeyEvent& InKeyEvent );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static FViCustomInputAction GetInputActionFromKeyEvent( const FKeyEvent& InKeyEvent );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static void GetAllBindedInputActions( TArray<FViCustomInputAction>& OutInputActions );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static void GetAllBindedInputAxises( TArray<FViCustomInputAxis>& OutInputAxises );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static bool ReBindAxisKey( const FViCustomInputAxis& InCurrent, const FViCustomInputAxis& InNew );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static bool ReBindActionKey( const FViCustomInputAction& InCurrent, const FViCustomInputAction& InNew );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static bool AddAxisBinding( const FViCustomInputAxis& InNew, FName InAxisName );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static bool AddActionBinding( const FViCustomInputAction& InNew, FName InActionName );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static bool RemoveAxisBinding( FKey InKey );

    UFUNCTION( BlueprintCallable, Category="ViCustomInputPlugin" )
    static bool RemoveActionBinding( FKey InKey );
};
