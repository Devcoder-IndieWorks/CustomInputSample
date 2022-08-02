#include "ViCustomInputPluginModule.h"
#include "ViCustomInputPluginPCH.h"
#include "ViCustomKeyMap.h"

#define LOCTEXT_NAMESPACE "ViCustomInputPlugin"

class FViCustomInputPluginModule : public IViCustomInputPluginModule
{
public:
    virtual void StartupModule() override
    {
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton01, LOCTEXT( "CustomButton01", "Custom Button 01" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton02, LOCTEXT( "CustomButton02", "Custom Button 02" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton03, LOCTEXT( "CustomButton03", "Custom Button 03" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton04, LOCTEXT( "CustomButton04", "Custom Button 04" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton05, LOCTEXT( "CustomButton05", "Custom Button 05" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton06, LOCTEXT( "CustomButton06", "Custom Button 06" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton07, LOCTEXT( "CustomButton07", "Custom Button 07" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton08, LOCTEXT( "CustomButton08", "Custom Button 08" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton09, LOCTEXT( "CustomButton09", "Custom Button 09" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton10, LOCTEXT( "CustomButton10", "Custom Button 10" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton11, LOCTEXT( "CustomButton11", "Custom Button 11" ), FKeyDetails::GamepadKey ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomButton12, LOCTEXT( "CustomButton12", "Custom Button 12" ), FKeyDetails::GamepadKey ) );

        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxis01, LOCTEXT( "CustomAxis01", "Custom Axis 01" ), FKeyDetails::Axis1D ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxis02, LOCTEXT( "CustomAxis02", "Custom Axis 02" ), FKeyDetails::Axis1D ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxis03, LOCTEXT( "CustomAxis03", "Custom Axis 03" ), FKeyDetails::Axis1D ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxis04, LOCTEXT( "CustomAxis04", "Custom Axis 04" ), FKeyDetails::Axis1D ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxis05, LOCTEXT( "CustomAxis05", "Custom Axis 05" ), FKeyDetails::Axis1D ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxis06, LOCTEXT( "CustomAxis06", "Custom Axis 06" ), FKeyDetails::Axis1D ) );

        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxisX, LOCTEXT( "CustomAxisX", "Custom Axis X" ), FKeyDetails::Axis1D ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxisY, LOCTEXT( "CustomAxisY", "Custom Axis Y" ), FKeyDetails::Axis1D ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxisZ, LOCTEXT( "CustomAxisZ", "Custom Axis Z" ), FKeyDetails::Axis1D ) );

        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxisPitch, LOCTEXT( "CustomAxisPitch", "Custom Axis Pitch" ), FKeyDetails::Axis1D ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxisYaw, LOCTEXT( "CustomAxisYaw", "Custom Axis Yaw" ), FKeyDetails::Axis1D ) );
        EKeys::AddKey( FKeyDetails( FViCustomKeyMap::CustomAxisRoll, LOCTEXT( "CustomAxisRoll", "Custom Axis Roll" ), FKeyDetails::Axis1D ) );
    }

    virtual void ShutdownModule() override {}
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE( FViCustomInputPluginModule, ViCustomInputPlugin );
