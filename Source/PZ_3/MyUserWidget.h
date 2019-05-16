// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "ShooterMode.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PZ_3_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	
	// score text
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))        
	UTextBlock* ScoreToDisplay;
	
	//text when turret is killed
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TurretText;
	
	void SetScoreText();
	void ShowTurretText();

	UFUNCTION()
	void ChangeScoreTurretText();
};
