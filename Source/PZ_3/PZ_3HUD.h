// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserWidget.h"
#include "PZ_3HUD.generated.h"

UCLASS()
class APZ_3HUD : public AHUD
{
	GENERATED_BODY()

public:
	APZ_3HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	//for setting up the widget class int HUD Blueprint
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> WidgetClass;

	class UUserWidget * MyWidget;
};

