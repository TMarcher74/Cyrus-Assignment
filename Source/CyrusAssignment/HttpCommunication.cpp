// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpCommunication.h"

UHttpCommunication::UHttpCommunication() {}

void UHttpCommunication::FetchJSONData()
{
    const FString URL = TEXT("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");

    // Create the HTTP request
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(URL);
    Request->SetVerb(TEXT("GET"));
    Request->OnProcessRequestComplete().BindUObject(this, &UHttpCommunication::OnResponseReceived);

    Request->ProcessRequest();
}

void UHttpCommunication::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    UE_LOG(LogTemp, Warning, TEXT("OnResponseReceived called"));
    if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to fetch JSON data!"));
		return;
	}

	FString JsonString = Response->GetContentAsString();
    UE_LOG(LogTemp, Warning, TEXT("JSON Fetched: %s"), *JsonString);
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		// Parse types
		TArray<TSharedPtr<FJsonValue>> TypesArray = JsonObject->GetArrayField("types");
		for (const auto& TypeValue : TypesArray)
		{
			TSharedPtr<FJsonObject> TypeObject = TypeValue->AsObject();
			FBoxType BoxType;
			BoxType.Name = TypeObject->GetStringField("name");

			TArray<TSharedPtr<FJsonValue>> ColorArray = TypeObject->GetArrayField("color");
			BoxType.Color = FLinearColor(
				ColorArray[0]->AsNumber() / 255.0f,
				ColorArray[1]->AsNumber() / 255.0f,
				ColorArray[2]->AsNumber() / 255.0f
			);
			BoxType.Health = TypeObject->GetIntegerField("health");
			BoxType.Score = TypeObject->GetIntegerField("score");

			ParsedData.Types.Add(BoxType);
		}

		// Parse the objects
		TArray<TSharedPtr<FJsonValue>> ObjectsArray = JsonObject->GetArrayField("objects");
		for (const auto& ObjectValue : ObjectsArray)
		{
			TSharedPtr<FJsonObject> ObjectObject = ObjectValue->AsObject();
			FBoxObject BoxObject;
			BoxObject.Type = ObjectObject->GetStringField("type");

			TSharedPtr<FJsonObject> TransformObject = ObjectObject->GetObjectField("transform");
			TArray<TSharedPtr<FJsonValue>> LocationArray = TransformObject->GetArrayField("location");
			BoxObject.Location = FVector(
				LocationArray[0]->AsNumber(),
				LocationArray[1]->AsNumber(),
				LocationArray[2]->AsNumber()
			);

			TArray<TSharedPtr<FJsonValue>> RotationArray = TransformObject->GetArrayField("rotation");
			BoxObject.Rotation = FRotator(
				RotationArray[0]->AsNumber(),
				RotationArray[1]->AsNumber(),
				RotationArray[2]->AsNumber()
			);

			TArray<TSharedPtr<FJsonValue>> ScaleArray = TransformObject->GetArrayField("scale");
			BoxObject.Scale = FVector(
				ScaleArray[0]->AsNumber(),
				ScaleArray[1]->AsNumber(),
				ScaleArray[2]->AsNumber()
			);

			ParsedData.Objects.Add(BoxObject);
		}
		UE_LOG(LogTemp, Warning, TEXT("Directly after Parsing \nTypes: %d\nObjects: %d\n"), ParsedData.Types.Num(), ParsedData.Objects.Num());
		UE_LOG(LogTemp, Log, TEXT("JSON data successfully parsed!"));

		// Broadcast the delegate to notify listeners
        OnDataFetchedDelegate.Broadcast();
	}
	else UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON data!"));
}

void UHttpCommunication::OnDataFetched()
{
    UE_LOG(LogTemp, Log, TEXT("Data fetched successfully in UHttpCommunication."));
    // This function will be called after the data is fetched
}

void UHttpCommunication::SimulateDataFetch()
{
    UE_LOG(LogTemp, Log, TEXT("Simulating data fetch..."));

    // Broadcast the delegate to notify listeners
    OnDataFetchedDelegate.Broadcast();
}

const FBoxData& UHttpCommunication::GetParsedData() const
{
    return ParsedData;
}