#pragma once

#include "LD48DataTypes.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
    WaitingToStart = 0,
    Welcome,
    InProgress,
    Pause,
    GameOver
};

// Delegat for call change State
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameState, EGameState);


