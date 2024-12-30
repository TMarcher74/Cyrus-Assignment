// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidget.h"

// Initialising the CurrentScore to 0
void UUIWidget::NativeConstruct()
{
    Super::NativeConstruct();
    CurrentScore = 0;

    if (ScoreText)
    {
        ScoreText->SetText(FText::AsNumber(CurrentScore));
    }
}

// Update the score and is called by the BoxClass when a box is destroyed
void UUIWidget::UpdateScore(int32 Score)
{
    CurrentScore += Score;
    if (ScoreText)
    {
        ScoreText->SetText(FText::AsNumber(CurrentScore));
    }
    UE_LOG(LogTemp, Log, TEXT("Widget Current Score: %d"), CurrentScore);
}

