// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UIWidget.generated.h"

/**
 * 
 */
UCLASS()
class CYRUSASSIGNMENT_API UUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void UpdateScore(int32 Score);

private:
    int32 CurrentScore;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;
};
