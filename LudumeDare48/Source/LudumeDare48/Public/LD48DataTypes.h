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

//Delegat for change progress bar oxygen
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeOxygen, float);

//Delegat for change depth value
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeDepth, int32);

//Delegat for change depth value
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeKeys, int32);

//Delegat for on death
DECLARE_MULTICAST_DELEGATE(FOnDeath);

