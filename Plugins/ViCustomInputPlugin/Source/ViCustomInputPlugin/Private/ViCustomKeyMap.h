// Copyright Devcoder. All Rights Reserved.
#pragma once
#include <CoreMinimal.h>
#include <SlateBasics.h>

struct FViCustomKeyMap
{
    // Buttons
    static const FKey CustomButton01;
    static const FKey CustomButton02;
    static const FKey CustomButton03;
    static const FKey CustomButton04;
    static const FKey CustomButton05;
    static const FKey CustomButton06;
    static const FKey CustomButton07;
    static const FKey CustomButton08;
    static const FKey CustomButton09;
    static const FKey CustomButton10;
    static const FKey CustomButton11;
    static const FKey CustomButton12;

    // Axis
    static const FKey CustomAxis01;
    static const FKey CustomAxis02;
    static const FKey CustomAxis03;
    static const FKey CustomAxis04;
    static const FKey CustomAxis05;
    static const FKey CustomAxis06;

    static const FKey CustomAxisX;
    static const FKey CustomAxisY;
    static const FKey CustomAxisZ;

    static const FKey CustomAxisPitch;
    static const FKey CustomAxisYaw;
    static const FKey CustomAxisRoll;

    // Unknown
    static const FKey Unknown;
};

namespace ViCustomInput
{
    void PressButton( int32 InButtonID );
    void ReleaseButton( int32 InButtonID );
    void SetAxisValue( int32 InAxisID, float InValue );
}
