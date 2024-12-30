// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxData.generated.h"

USTRUCT(BlueprintType)
struct FBoxType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FLinearColor Color;

	UPROPERTY(BlueprintReadOnly)
	int32 Health;

	UPROPERTY(BlueprintReadOnly)
	int32 Score;
};

USTRUCT(BlueprintType)
struct FBoxObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Type;

	UPROPERTY(BlueprintReadOnly)
	FVector Location;

	UPROPERTY(BlueprintReadOnly)
	FRotator Rotation;

	UPROPERTY(BlueprintReadOnly)
	FVector Scale;
};

USTRUCT(BlueprintType)
struct FBoxData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FBoxType> Types;

	UPROPERTY(BlueprintReadOnly)
	TArray<FBoxObject> Objects;
};
