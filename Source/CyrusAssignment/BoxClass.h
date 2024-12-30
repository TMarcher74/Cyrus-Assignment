// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxData.h"
#include "BoxClass.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoxDestroyed, int32, Score);
UCLASS()
class CYRUSASSIGNMENT_API ABoxClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
    FOnBoxDestroyed OnBoxDestroyed;

    void TakeDamage(int32 Damage);

    void InitializeBox(const FBoxType& BoxType);

protected:
	void DestroyBox();

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaticMeshComponent;
	
    UPROPERTY()
    UStaticMesh* BoxMesh;

    UPROPERTY()
    UMaterialInterface* BoxMaterial;

    UPROPERTY()
    int32 Health;

    UPROPERTY()
    int32 Score;

};
