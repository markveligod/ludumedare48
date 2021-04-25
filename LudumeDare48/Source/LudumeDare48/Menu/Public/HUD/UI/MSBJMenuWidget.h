/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "CoreMinimal.h"
#include "HUD/UI/MSBJBaseWidget.h"
#include "MSBJMenuWidget.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LUDUMEDARE48_API UMSBJMenuWidget : public UMSBJBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ResultTotalDepthTextBlock;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* EndAnimation;

	virtual void NativeOnInitialized() override;
private:
	UFUNCTION()
		void OnStartGame();

	UFUNCTION()
		void OnOptionsGame();

	UFUNCTION()
		void OnCreditsGame();

	UFUNCTION()
		void OnQuitGame();

	void UpdateResultDepth();
};
