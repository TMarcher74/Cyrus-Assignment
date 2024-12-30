// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxClass.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UIWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"


// Sets default values
ABoxClass::ABoxClass()
{
 	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;

    // Load default mesh and material
    static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (DefaultMesh.Succeeded())
    {
        BoxMesh = DefaultMesh.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultMaterial(TEXT("/Game/FPWeapon/Materials/BaseMaterial.BaseMaterial"));
    if (DefaultMaterial.Succeeded())
    {
        BoxMaterial = DefaultMaterial.Object;
    }

    // Initialize default values
    Health = 100;
    Score = 10;

}

// Called when the game starts or when spawned
void ABoxClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxClass::InitializeBox(const FBoxType& BoxType)
{
    // Set the type's properties
    Health = BoxType.Health;
    Score = BoxType.Score;

    if (BoxMesh)
    {
        StaticMeshComponent->SetStaticMesh(BoxMesh);
    }

    // Apply a dynamic material instance
    if (BoxMaterial)
    {
        UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(BoxMaterial, this);
        if (MaterialInstance)
        {
            MaterialInstance->SetVectorParameterValue(FName("BaseColor"), BoxType.Color);
            StaticMeshComponent->SetMaterial(0, MaterialInstance);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Initialized box: Health = %d, Score = %d"), Health, Score);
}

void ABoxClass::TakeDamage(int32 Damage)
{
    Health -= Damage;

    UE_LOG(LogTemp, Log, TEXT("Box took %d damage, remaining health: %d"), Damage, Health);

    if (Health <= 0)
    {
        DestroyBox();
    }
}

void ABoxClass::DestroyBox()
{
    UE_LOG(LogTemp, Log, TEXT("Box destroyed! Score awarded: %d"), Score);

    //OnBoxDestroyed.Broadcast(Score);
    TArray<UUserWidget*> Widgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, UUIWidget::StaticClass(), false);
    if (Widgets.Num() > 0)
    {
        UUIWidget* UIWidget = Cast<UUIWidget>(Widgets[0]);
        if (UIWidget)
        {
            UIWidget->UpdateScore(Score);
        }
    }

    // Destroy the actor
    Destroy();
}
