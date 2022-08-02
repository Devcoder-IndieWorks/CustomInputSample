#include "ViCustomKeyMap.h"
#include "ViCustomInputPluginPCH.h"

const FKey FViCustomKeyMap::CustomButton01( "CustomButton01" );
const FKey FViCustomKeyMap::CustomButton02( "CustomButton02" );
const FKey FViCustomKeyMap::CustomButton03( "CustomButton03" );
const FKey FViCustomKeyMap::CustomButton04( "CustomButton04" );
const FKey FViCustomKeyMap::CustomButton05( "CustomButton05" );
const FKey FViCustomKeyMap::CustomButton06( "CustomButton06" );
const FKey FViCustomKeyMap::CustomButton07( "CustomButton07" );
const FKey FViCustomKeyMap::CustomButton08( "CustomButton08" );
const FKey FViCustomKeyMap::CustomButton09( "CustomButton09" );
const FKey FViCustomKeyMap::CustomButton10( "CustomButton10" );
const FKey FViCustomKeyMap::CustomButton11( "CustomButton11" );
const FKey FViCustomKeyMap::CustomButton12( "CustomButton12" );

const FKey FViCustomKeyMap::CustomAxis01( "CustomAxis01" );
const FKey FViCustomKeyMap::CustomAxis02( "CustomAxis02" );
const FKey FViCustomKeyMap::CustomAxis03( "CustomAxis03" );
const FKey FViCustomKeyMap::CustomAxis04( "CustomAxis04" );
const FKey FViCustomKeyMap::CustomAxis05( "CustomAxis05" );
const FKey FViCustomKeyMap::CustomAxis06( "CustomAxis06" );

const FKey FViCustomKeyMap::CustomAxisX( "CustomAxisX" );
const FKey FViCustomKeyMap::CustomAxisY( "CustomAxisY" );
const FKey FViCustomKeyMap::CustomAxisZ( "CustomAxisZ" );

const FKey FViCustomKeyMap::CustomAxisPitch( "CustomAxisPitch" );
const FKey FViCustomKeyMap::CustomAxisYaw( "CustomAxisYaw" );
const FKey FViCustomKeyMap::CustomAxisRoll( "CustomAxisRoll" );

const FKey FViCustomKeyMap::Unknown( "Unknown" );

namespace ViCustomInput
{
    bool __EmitKeyUpEvent( FKey InKey, int32 InUser, bool InRepeat )
    {
        FKeyEvent keyEvent( InKey, FSlateApplication::Get().GetModifierKeys(), InUser, InRepeat, 0, 0 );
        return FSlateApplication::Get().ProcessKeyUpEvent( keyEvent );
    }

    bool __EmitKeyDownEvent( FKey InKey, int32 InUser, bool InRepeat )
    {
        FKeyEvent keyEvent( InKey, FSlateApplication::Get().GetModifierKeys(), InUser, InRepeat, 0, 0 );
        return FSlateApplication::Get().ProcessKeyDownEvent( keyEvent );
    }

    bool __EmitAnalogInputEvent( FKey InKey, float InValue, int32 InUser, bool InRepeat )
    {
        FAnalogInputEvent analogInputEvent( InKey, FSlateApplication::Get().GetModifierKeys(), InUser, InRepeat, 0, 0, InValue );
        return FSlateApplication::Get().ProcessAnalogInputEvent( analogInputEvent );
    }

    //-------------------------------------------------------------------------

    FKey __GetKeyFromButtonID( int32 InButtonID )
    {
        switch ( InButtonID ) {
            case 1:
                return FViCustomKeyMap::CustomButton01;
            case 2:
                return FViCustomKeyMap::CustomButton02;
            case 3:
                return FViCustomKeyMap::CustomButton03;
            case 4:
                return FViCustomKeyMap::CustomButton04;
            case 5:
                return FViCustomKeyMap::CustomButton05;
            case 6:
                return FViCustomKeyMap::CustomButton06;
            case 7:
                return FViCustomKeyMap::CustomButton07;
            case 8:
                return FViCustomKeyMap::CustomButton08;
            case 9:
                return FViCustomKeyMap::CustomButton09;
            case 10:
                return FViCustomKeyMap::CustomButton10;
            case 11:
                return FViCustomKeyMap::CustomButton11;
            case 12:
                return FViCustomKeyMap::CustomButton12;
            default:
                return FViCustomKeyMap::Unknown;
        }
    }

    FKey __GetKeyFromAxisID( int32 InAxisID )
    {
        switch ( InAxisID ) {
            case 1:
                return FViCustomKeyMap::CustomAxis01;
            case 2:
                return FViCustomKeyMap::CustomAxis02;
            case 3:
                return FViCustomKeyMap::CustomAxis03;
            case 4:
                return FViCustomKeyMap::CustomAxis04;
            case 5:
                return FViCustomKeyMap::CustomAxis05;
            case 6:
                return FViCustomKeyMap::CustomAxis06;
            case 7:
                return FViCustomKeyMap::CustomAxisX;
            case 8:
                return FViCustomKeyMap::CustomAxisY;
            case 9:
                return FViCustomKeyMap::CustomAxisZ;
            case 10:
                return FViCustomKeyMap::CustomAxisPitch;
            case 11:
                return FViCustomKeyMap::CustomAxisYaw;
            case 12:
                return FViCustomKeyMap::CustomAxisRoll;
            default:
                return FViCustomKeyMap::Unknown;
        }
    }

    //-------------------------------------------------------------------------

    void PressButton( int32 InButtonID )
    {
        auto key = __GetKeyFromButtonID( InButtonID );
        if ( key != FViCustomKeyMap::Unknown )
            __EmitKeyDownEvent( key, 0, 0 );
    }

    void ReleaseButton( int32 InButtonID )
    {
        auto key = __GetKeyFromButtonID( InButtonID );
        if ( key != FViCustomKeyMap::Unknown )
            __EmitKeyUpEvent( key, 0, 0 );
    }

    void SetAxisValue( int32 InAxisID, float InValue )
    {
        auto key = __GetKeyFromAxisID( InAxisID );
        if ( key != FViCustomKeyMap::Unknown )
            __EmitAnalogInputEvent( key, InValue, 0, 0 );
    }
}
