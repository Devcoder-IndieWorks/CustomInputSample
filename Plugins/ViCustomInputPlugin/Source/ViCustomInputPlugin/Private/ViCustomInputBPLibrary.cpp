#include "ViCustomInputBPLibrary.h"
#include "ViCustomInputPluginPCH.h"
#include "ViCustomKeyMap.h"
#include "ViLog.h"

void UViCustomInputBPLibrary::PressButtonByID( int32 InButtonID )
{
    VILOG( Log, TEXT( "Called press button function. ButtonID: [%i]" ), InButtonID );
    ViCustomInput::PressButton( InButtonID );
}

void UViCustomInputBPLibrary::ReleaseButtonByID( int32 InButtonID )
{
    VILOG( Log, TEXT( "Called release button function. ButtonID: [%i]" ), InButtonID );
    ViCustomInput::ReleaseButton( InButtonID );
}

void UViCustomInputBPLibrary::SetAxisValueByID( int32 InAxisID, float InValue )
{
    VILOG( Log, TEXT( "Called set axis value function. AxisID: [%i] Value: [%f]" ), InAxisID, InValue );
    ViCustomInput::SetAxisValue( InAxisID, InValue );
}

//-----------------------------------------------------------------------------

static void __UpdateCustomInputAxisBinding( const FViCustomInputAxis& InSrcInputAxis, FInputAxisKeyMapping& OutDstInputAxis )
{
    OutDstInputAxis.Key = InSrcInputAxis.Key;
    OutDstInputAxis.Scale = InSrcInputAxis.Scale;
}

static void __UpdateCustomInputActionBinding( const FViCustomInputAction& InSrcInputAction, FInputActionKeyMapping& OutDstInputAction )
{
    OutDstInputAction.Key = InSrcInputAction.Key;
    OutDstInputAction.bShift = InSrcInputAction.Shift;
    OutDstInputAction.bCtrl = InSrcInputAction.Ctrl;
    OutDstInputAction.bAlt = InSrcInputAction.Alt;
    OutDstInputAction.bCmd = InSrcInputAction.Cmd;
}

static UInputSettings* __GetInputSettings()
{
    return const_cast<UInputSettings*>( GetDefault<UInputSettings>() );
}

static TArray<FInputActionKeyMapping>& __GetActionMappingsFromInputSettings( UInputSettings* InSettings )
{
    return const_cast<TArray<FInputActionKeyMapping>&>( InSettings->GetActionMappings() );
}

static TArray<FInputAxisKeyMapping>& __GetAxisMappingsFromInputSettings( UInputSettings* InSettings )
{
    return const_cast<TArray<FInputAxisKeyMapping>&>( InSettings->GetAxisMappings() );
}

static void __SaveAndRebuildKeyMappings( UInputSettings* InSettings )
{
    InSettings->SaveKeyMappings();
    for ( TObjectIterator<UPlayerInput> it; it; ++it )
        it->ForceRebuildingKeyMaps( true );
}

FViCustomInputAxis UViCustomInputBPLibrary::GetInputAxisFromMouseButtonEvent( const FPointerEvent& InMouseEvent )
{
    FViCustomInputAxis inputAxis;

    inputAxis.Key = InMouseEvent.GetEffectingButton();
    inputAxis.KeyAsString = inputAxis.Key.GetDisplayName().ToString();
    inputAxis.Scale = 1.0f;

    return inputAxis;
}

FViCustomInputAxis UViCustomInputBPLibrary::GetInputAxisFromMouseAxisEvent( const FPointerEvent& InMouseEvent )
{
    FViCustomInputAxis inputAxis;
    auto currentHorizontalDistance = FMath::Abs( InMouseEvent.GetCursorDelta().X );
    auto currentVerticalDistance = FMath::Abs( InMouseEvent.GetCursorDelta().Y );

    if ( currentHorizontalDistance > currentVerticalDistance ) {
        inputAxis.Key = FKey( TEXT( "MouseX" ) );
        inputAxis.Scale = InMouseEvent.GetCursorDelta().X >= 0.0f ? 1.0f : -1.0f;
    }
    else {
        inputAxis.Key = FKey( TEXT( "MouseY" ) );
        inputAxis.Scale = InMouseEvent.GetCursorDelta().Y >= 0.0f ? 1.0f : -1.0f;
    }

    inputAxis.KeyAsString = inputAxis.Key.GetDisplayName().ToString();

    return inputAxis;
}

FViCustomInputAction UViCustomInputBPLibrary::GetInputActionFromMouseButtonEvent( const FPointerEvent& InMouseEvent )
{
    FViCustomInputAction inputAction;

    inputAction.Key = InMouseEvent.GetEffectingButton();
    inputAction.KeyAsString = inputAction.Key.GetDisplayName().ToString();
    inputAction.Alt = InMouseEvent.IsAltDown();
    inputAction.Ctrl = InMouseEvent.IsControlDown();
    inputAction.Shift = InMouseEvent.IsShiftDown();
    inputAction.Cmd = InMouseEvent.IsCommandDown();

    return inputAction;
}

FViCustomInputAction UViCustomInputBPLibrary::GetInputActionFromKeyEvent( const FKeyEvent& InKeyEvent )
{
    FViCustomInputAction inputAction;

    inputAction.Key = InKeyEvent.GetKey();
    inputAction.KeyAsString = inputAction.Key.GetDisplayName().ToString();
    inputAction.Alt = InKeyEvent.IsAltDown();
    inputAction.Ctrl = InKeyEvent.IsControlDown();
    inputAction.Shift = InKeyEvent.IsShiftDown();
    inputAction.Cmd = InKeyEvent.IsCommandDown();

    return inputAction;
}

FViCustomInputAxis UViCustomInputBPLibrary::GetInputAxisFromKeyEvent( const FKeyEvent& InKeyEvent )
{
    FViCustomInputAxis inputAxis;

    inputAxis.Key = InKeyEvent.GetKey();
    inputAxis.KeyAsString = inputAxis.Key.GetDisplayName().ToString();
    inputAxis.Scale = 1.0f;

    return inputAxis;
}

void UViCustomInputBPLibrary::GetAllBindedInputActions( TArray<FViCustomInputAction>& OutInputActions )
{
    OutInputActions.Empty();

    auto settings = GetDefault<UInputSettings>();
    if ( settings == nullptr )
        return;

    auto& actions = settings->GetActionMappings();
    for ( auto& each : actions )
        OutInputActions.Add( FViCustomInputAction( each ) );
}

void UViCustomInputBPLibrary::GetAllBindedInputAxises( TArray<FViCustomInputAxis>& OutInputAxises )
{
    OutInputAxises.Empty();

    auto settings = GetDefault<UInputSettings>();
    if ( settings == nullptr )
        return;

    auto& axises = settings->GetAxisMappings();
    for ( auto& each : axises )
        OutInputAxises.Add( FViCustomInputAxis( each ) );
}

bool UViCustomInputBPLibrary::ReBindAxisKey( const FViCustomInputAxis& InCurrent, const FViCustomInputAxis& InNew )
{
    auto settings = __GetInputSettings();
    if ( settings == nullptr )
        return false;

    auto& axises = __GetAxisMappingsFromInputSettings( settings );
    auto find = axises.FindByPredicate( [&InCurrent]( FInputAxisKeyMapping& each ){
                    return each.AxisName.ToString().Equals( InCurrent.AxisName ) && each.Key == InCurrent.Key;
                } );
    if ( find == nullptr )
        return false;

    __UpdateCustomInputAxisBinding( InNew, *find );
    __SaveAndRebuildKeyMappings( settings );

    return true;
}

bool UViCustomInputBPLibrary::ReBindActionKey( const FViCustomInputAction& InCurrent, const FViCustomInputAction& InNew )
{
    auto settings = __GetInputSettings();
    if ( settings == nullptr )
        return false;

    auto& actions = __GetActionMappingsFromInputSettings( settings );
    auto find = actions.FindByPredicate( [&InCurrent]( FInputActionKeyMapping& each ){
                    return each.ActionName.ToString().Equals( InCurrent.ActionName ) && each.Key == InCurrent.Key;
                } );
    if ( find == nullptr )
        return false;

    __UpdateCustomInputActionBinding( InNew, *find );
    __SaveAndRebuildKeyMappings( settings );

    return true;
}

bool UViCustomInputBPLibrary::AddAxisBinding( const FViCustomInputAxis& InNew, FName InAxisName )
{
    auto settings = __GetInputSettings();
    if ( settings == nullptr )
        return false;

    auto& axises = __GetAxisMappingsFromInputSettings( settings );
    auto axisIndex = axises.AddUnique( FInputAxisKeyMapping( InAxisName, InNew.Key, InNew.Scale ) );
    if ( axisIndex <= 0 )
        return false;

    __SaveAndRebuildKeyMappings( settings );

    return true;
}


bool UViCustomInputBPLibrary::AddActionBinding( const FViCustomInputAction& InNew, FName InActionName )
{
    auto settings = __GetInputSettings();
    if ( settings == nullptr )
        return false;

    auto& actions = __GetActionMappingsFromInputSettings( settings );
    auto actionIndex = actions.AddUnique( FInputActionKeyMapping( InActionName, InNew.Key, InNew.Shift, InNew.Ctrl, InNew.Alt, InNew.Cmd ) );
    if ( actionIndex <= 0 )
        return false;

    __SaveAndRebuildKeyMappings( settings );

    return true;
}

bool UViCustomInputBPLibrary::RemoveAxisBinding( FKey InKey )
{
    auto settings = __GetInputSettings();
    if ( settings == nullptr )
        return false;

    auto& axises = __GetAxisMappingsFromInputSettings( settings );
    auto found = false;
    for ( int32 i = axises.Num() - 1; i >= 0; i-- ) {
        if ( axises[ i ].Key == InKey ) {
            found = true;
            axises.RemoveAt( i );
        }
    }

    if ( found )
        __SaveAndRebuildKeyMappings( settings );

    return found;
}

bool UViCustomInputBPLibrary::RemoveActionBinding( FKey InKey )
{
    auto settings = __GetInputSettings();
    if ( settings == nullptr )
        return false;

    auto& actions = __GetActionMappingsFromInputSettings( settings );
    auto found = false;
    for ( int32 i = actions.Num() - 1; i >= 0; i-- ) {
        if ( actions[ i ].Key == InKey ) {
            found = true;
            actions.RemoveAt( i );
        }
    }

    if ( found )
        __SaveAndRebuildKeyMappings( settings );

    return found;
}
