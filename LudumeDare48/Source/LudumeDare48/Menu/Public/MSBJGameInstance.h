/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MSBJGameInstance.generated.h"

class USoundClass;
/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API UMSBJGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels Editor")
		FName NameStartLevel = NAME_None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels Editor")
		FName NameMenuLevel = NAME_None;
	UPROPERTY(BlueprintReadOnly, Category = "Count Total")
		int32 TotalDepth = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound classes Editor")
		USoundClass* MusicMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound classes Editor")
		USoundClass* SoundMenuClass;
};
