#include "ViCameraDirector.h"
#include "ViCustomInputPluginPCH.h"
#include "ViDelayExecutor.h"
#include "ViLog.h"

AViCameraDirector::AViCameraDirector()
{
    SmoothBlendTime = 0.0f;
    TimeBetweenCameraChanges = 2.0f;
    NextIndex = 0;
    ChangingCamera = false;

    PrimaryActorTick.bCanEverTick = true;
}

void AViCameraDirector::BeginPlay()
{
    Super::BeginPlay();

    auto playerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
    if ( ensure ( playerController->IsValidLowLevelFast() ) ) {
        EnableInput( playerController );
        SavedCamera = playerController->GetViewTarget();
    }

    DelayExecutor = MakeShareable( new FViDelayExecutor( GetWorld(), TimeBetweenCameraChanges, 
        [this]{ NextChangeCamera(); } ) );
}

void AViCameraDirector::Tick( float InDeltaSeconds )
{
    Super::Tick( InDeltaSeconds );

    if ( ChangingCamera )
        DelayExecutor->Execute();
}

void AViCameraDirector::StartChangeCamera()
{
    ChangingCamera = true;
}

void AViCameraDirector::StopChangeCamera()
{
    ChangingCamera = false;
}

void AViCameraDirector::NextChangeCamera()
{
    auto camera = GetNextCamera();
    if ( ensure( camera != nullptr ) )
        ChangeCamera( camera );
}

AActor* AViCameraDirector::GetNextCamera()
{
    if ( NextIndex >= Cameras.Num() )
        NextIndex = 0;

    if ( Cameras.Num() == 0 )
        return nullptr;

    return Cameras[ NextIndex++ ];
}

void AViCameraDirector::ChangeCamera( AActor* InCamera )
{
    auto playerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
    if ( ensure( playerController->IsValidLowLevelFast() ) )
        playerController->SetViewTargetWithBlend( InCamera, SmoothBlendTime );
}

void AViCameraDirector::RestoreCamera()
{
    if ( ensure( SavedCamera.IsValid() ) )
        ChangeCamera( SavedCamera.Get() );
}
