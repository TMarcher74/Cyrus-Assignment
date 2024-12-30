// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "BoxData.h"

#include "HttpCommunication.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDataFetchedDelegate);

UCLASS()
class CYRUSASSIGNMENT_API UHttpCommunication : public UObject
{
	GENERATED_BODY()

public:
    // Constructor
    UHttpCommunication();

    // Method to fetch JSON data
    void FetchJSONData();

    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

private:
	FBoxData ParsedData;

public:
	const FBoxData& GetParsedData() const;

    UFUNCTION()
    void OnDataFetched();

public:
    // Delegate that gets broadcasted when data is fetched
    UPROPERTY(BlueprintAssignable, Category = "Delegates")
    FOnDataFetchedDelegate OnDataFetchedDelegate;

    // Simulate data fetching and broadcast the delegate
    void SimulateDataFetch();
};
