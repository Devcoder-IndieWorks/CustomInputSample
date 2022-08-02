// Copyright Devcoder. All Rights Reserved.
#pragma once
#include <CoreMinimal.h>

DECLARE_LOG_CATEGORY_EXTERN( LogCustomInput, Log, All )

#define VILOG_CALLINFO                              FString::Printf( TEXT( "[%s(%i)]" ), TEXT( __FUNCTION__ ), __LINE__ )
#define VILOG_CALLONLY( Verbosity )                 UE_LOG( LogCustomInput, Verbosity, TEXT( "%s" ), *VILOG_CALLINFO )
#define VILOG( Verbosity, Format, ... )             UE_LOG( LogCustomInput, Verbosity, TEXT( "%s LOG: %s" ), *VILOG_CALLINFO, *FString::Printf( Format, ##__VA_ARGS__ ) )
#define VICLOG( Condition, Verbosity, Format, ... ) UE_CLOG( Condition, LogCustomInput, Verbosity, TEXT( "%s LOG: %s" ), *VILOG_CALLINFO, *FString::Printf( Format, ##__VA_ARGS__ ) )
