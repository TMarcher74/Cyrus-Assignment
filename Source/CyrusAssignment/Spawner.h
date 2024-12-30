// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxData.h" // To access FBoxType and FBoxObject
#include "HttpCommunication.h" // To access UHttpCommunication

#include "Spawner.generated.h"

UCLASS()
class CYRUSASSIGNMENT_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SpawnBoxes(const TArray<FBoxType>& BoxTypes, const TArray<FBoxObject>& BoxObjects);

protected:
    // static mesh to use for boxes
    UPROPERTY(EditAnywhere, Category = "Spawner")
    UStaticMesh* BoxMesh;

    // Material template for box materials
    UPROPERTY(EditAnywhere, Category = "Spawner")
    UMaterialInterface* BoxMaterial;

    // Function to create a material instance for a given color
    //UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor Color);

private:
    UPROPERTY()
    UHttpCommunication* HttpComm;

public:
	UFUNCTION()
	void OnDataReady();

};
