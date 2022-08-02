#include "ViControllableActor.h"
#include "ViCustomInputPluginPCH.h"
#include "ViLog.h"

AViControllableActor::AViControllableActor()
{
    EnableDefaultInputBindings = true;
    MovementSpeed = 100.0f;
    RotationSpeed = 50.0f;
    TargetActor = nullptr;

    ForwardKey = EKeys::Up;
    BackwardKey = EKeys::Down;
    RightKey = EKeys::Right;
    LeftKey = EKeys::Left;
    UpKey = EKeys::U;
    DownKey = EKeys::I;

    PitchUpKey = EKeys::O;
    PitchDownKey = EKeys::P;
    YawLeftKey = EKeys::K;
    YawRightKey = EKeys::L;
    RollCCWKey = EKeys::N;
    RollCWKey = EKeys::M;
}

void AViControllableActor::BeginPlay()
{
    Super::BeginPlay();

    InitializeDefaultInputBindings();
    SetSavedMobility();

    auto playerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
    if ( ensure( playerController != nullptr ) ) {
        EnableInput( playerController );

        if ( EnableDefaultInputBindings ) {
            InputComponent->BindAxis( TEXT( "ControllableActor_MoveRight" ), this, &AViControllableActor::AddYPositionOfLocation );
            InputComponent->BindAxis( TEXT( "ControllableActor_MoveUp" ), this, &AViControllableActor::AddZPositionOfLocation );
            InputComponent->BindAxis( TEXT( "ControllableActor_MoveForward" ), this, &AViControllableActor::AddXPositionOfLocation );

            InputComponent->BindAxis( TEXT( "ControllableActor_Pitch" ), this, &AViControllableActor::AddPitchOfRotation );
            InputComponent->BindAxis( TEXT( "ControllableActor_Yaw" ), this, &AViControllableActor::AddYawOfRotation );
            InputComponent->BindAxis( TEXT( "ControllableActor_Roll" ), this, &AViControllableActor::AddRollOfRotation );
        }
    }
}

void AViControllableActor::InitializeDefaultInputBindings()
{
    if ( !EnableDefaultInputBindings )
        return;

    static bool bindingsAdded = false;
    if ( bindingsAdded )
        return;

    bindingsAdded = true;

    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_MoveForward", ForwardKey, 1.0f ) );
    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_MoveForward", BackwardKey, -1.0f ) );
    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_MoveRight", RightKey, 1.0f ) );
    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_MoveRight", LeftKey, -1.0f ) );
    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_MoveUp", UpKey, 1.0f ) );
    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_MoveUp", DownKey, -1.0f ) );

    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_Pitch", PitchUpKey, 1.0f ) );
    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_Pitch", PitchDownKey, -1.0f ) );
    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_Yaw", YawRightKey, 1.0f ) );
    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_Yaw", YawLeftKey, -1.0f ) );
    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_Roll", RollCWKey, 1.0f ) );
    UPlayerInput::AddEngineDefinedAxisMapping( FInputAxisKeyMapping( "ControllableActor_Roll", RollCCWKey, -1.0f ) );
}

void AViControllableActor::AddXPositionOfLocation( float InValue )
{
    if ( TargetActor != nullptr ) {
        auto loc = TargetActor->GetActorLocation();
        FVector newLoc( loc.X + (InValue * MovementSpeed * GetWorld()->GetDeltaSeconds()), loc.Y, loc.Z );
        TargetActor->SetActorLocation( newLoc );
    }
}

void AViControllableActor::AddYPositionOfLocation( float InValue )
{
    if ( TargetActor != nullptr ) {
        auto loc = TargetActor->GetActorLocation();
        FVector newLoc( loc.X, loc.Y + (InValue * MovementSpeed * GetWorld()->GetDeltaSeconds()), loc.Z );
        TargetActor->SetActorLocation( newLoc );
    }
}

void AViControllableActor::AddZPositionOfLocation( float InValue )
{
    if ( TargetActor != nullptr ) {
        auto loc = TargetActor->GetActorLocation();
        FVector newLoc( loc.X, loc.Y, loc.Z + (InValue * MovementSpeed * GetWorld()->GetDeltaSeconds()) );
        TargetActor->SetActorLocation( newLoc );
    }
}

void AViControllableActor::AddPitchOfRotation( float InValue )
{
    if ( TargetActor != nullptr ) {
        auto rot = TargetActor->GetActorRotation();
        FRotator newRot( rot.Pitch + (InValue * RotationSpeed * GetWorld()->GetDeltaSeconds()), rot.Yaw, rot.Roll );
        TargetActor->SetActorRotation( newRot );
    }
}

void AViControllableActor::AddYawOfRotation( float InValue )
{
    if ( TargetActor != nullptr ) {
        auto rot = TargetActor->GetActorRotation();
        FRotator newRot( rot.Pitch, rot.Yaw + (InValue * RotationSpeed * GetWorld()->GetDeltaSeconds()), rot.Roll );
        TargetActor->SetActorRotation( newRot );
    }
}

void AViControllableActor::AddRollOfRotation( float InValue )
{
    if ( TargetActor != nullptr ) {
        auto rot = TargetActor->GetActorRotation();
        FRotator newRot( rot.Pitch, rot.Yaw, rot.Roll + (InValue * RotationSpeed * GetWorld()->GetDeltaSeconds()) );
        TargetActor->SetActorRotation( newRot );
    }
}

void AViControllableActor::EndPlay( const EEndPlayReason::Type InEndPlayReason )
{
    RestoreMobility();

    Super::EndPlay( InEndPlayReason );
}

void AViControllableActor::SetTargetActor( AActor* InTargetActor )
{
    if ( InTargetActor != nullptr ) {
        RestoreMobility();

        TargetActor = InTargetActor;

        SetSavedMobility();
    }
}

void AViControllableActor::SetSavedMobility()
{
    auto valid = TargetActor != nullptr && TargetActor->GetRootComponent() != nullptr;
    VICLOG( !valid, Warning, TEXT( "TargetActor or RootComponent is nullptr." ) );

    if ( valid ) {
        IsSavedMobility = false;

        if ( !TargetActor->IsRootComponentMovable() ) {
            SavedMobility = TargetActor->GetRootComponent()->Mobility;
            IsSavedMobility = true;

            TargetActor->GetRootComponent()->Mobility = EComponentMobility::Movable;
        }
    }
}

void AViControllableActor::RestoreMobility()
{
    if ( TargetActor != nullptr && TargetActor->GetRootComponent() != nullptr ) {
        if ( IsSavedMobility ) {
            IsSavedMobility = false;
            TargetActor->GetRootComponent()->Mobility = SavedMobility;
        }
    }
}
