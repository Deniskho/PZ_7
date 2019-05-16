// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"


void UMyUserWidget::NativeConstruct()
{  
	Super::NativeConstruct();

	SetScoreText();
	TurretText->SetVisibility(ESlateVisibility::Hidden);

	AShooterMode* GameMode = Cast<AShooterMode>(GetWorld()->GetAuthGameMode());
	// for binding ChangeScoreTurretText() to Event int Shooter Mode
	if (GameMode)
	{
		GameMode->ChangeScoreTurretText.AddUFunction(this, "ChangeScoreTurretText");
	}
}

void UMyUserWidget::SetScoreText()
{
	if (ScoreToDisplay)
	{
		AShooterMode * GameMode = Cast<AShooterMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{// gets score from game mode and casts to string
			FString CurrentScore = FString::SanitizeFloat(GameMode->GetScore());
			ScoreToDisplay->SetText(FText::FromString("Current Score - " + CurrentScore));
		}
	}

}

void UMyUserWidget::ShowTurretText()
{
	if (TurretText)
	{// sets visibility on 2 seconds then hids turret text
		TurretText->SetText(FText::FromString("Turret has been destroyed!"));
		TurretText->SetVisibility(ESlateVisibility::Visible);
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, [this] {
			TurretText->SetVisibility(ESlateVisibility::Hidden);
		}, 2, 1);
	}
		
}

void UMyUserWidget::ChangeScoreTurretText()
{// changes score and shows turret text 
	SetScoreText();
	ShowTurretText();
}

