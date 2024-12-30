// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"
#include "BoxClass.h"


ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Loads the default mesh and material
    static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultBoxMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (DefaultBoxMesh.Succeeded())
    {
        BoxMesh = DefaultBoxMesh.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultMaterial(TEXT("/Game/FPWeapon/Materials/BaseMaterial.BaseMaterial"));
    if (DefaultMaterial.Succeeded())
    {
        BoxMaterial = DefaultMaterial.Object;
    }

	HttpComm = CreateDefaultSubobject<UHttpCommunication>(TEXT("HttpCommunication"));
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay called"));

	// Placeholder code to test the spawner
    // TArray<FBoxType> BoxTypes;
    // TArray<FBoxObject> BoxObjects;
    // SpawnBoxes(BoxTypes, BoxObjects);

    if (HttpComm) {
        HttpComm->OnDataFetchedDelegate.AddDynamic(this, &ASpawner::OnDataReady);
        //HttpComm->SimulateDataFetch();
        HttpComm->FetchJSONData();
    }
    else UE_LOG(LogTemp, Warning, TEXT("HttpComm is null!"));
	
}

void ASpawner::OnDataReady()
{
	const FBoxData& ParsedData = HttpComm->GetParsedData();
    UE_LOG(LogTemp, Warning, TEXT("Types: %d\nObjects: %d\n"), ParsedData.Types.Num(), ParsedData.Objects.Num());

	if (ParsedData.Types.Num() > 0 && ParsedData.Objects.Num() > 0)
	{
		SpawnBoxes(ParsedData.Types, ParsedData.Objects);
	}
	else UE_LOG(LogTemp, Warning, TEXT("No data available for spawning boxes."));
}

void ASpawner::SpawnBoxes(const TArray<FBoxType>& BoxTypes, const TArray<FBoxObject>& BoxObjects)
{
    if (!BoxMesh || !BoxMaterial)
    {
        UE_LOG(LogTemp, Warning, TEXT("BoxMesh or BoxMaterial is not set!"));
        return;
    }

    for (const FBoxObject& BoxObject : BoxObjects)
    {
        // Find the corresponding type
        const FBoxType* BoxType = BoxTypes.FindByPredicate([&](const FBoxType& Type)
        {
            return Type.Name == BoxObject.Type;
        });

        if (!BoxType)
        {
            UE_LOG(LogTemp, Warning, TEXT("Box type '%s' not found!"), *BoxObject.Type);
            continue;
        }

        // Spawn the box actor
        FTransform BoxTransform;
        BoxTransform.SetLocation(BoxObject.Location);
        BoxTransform.SetRotation(FRotator(BoxObject.Rotation.Pitch, BoxObject.Rotation.Yaw, BoxObject.Rotation.Roll).Quaternion());
        //UE_LOG(LogTemp, Log, TEXT("Applied Rotation - Pitch: %f, Yaw: %f, Roll: %f"), BoxTransform.GetRotation().Rotator().Pitch, BoxTransform.GetRotation().Rotator().Yaw, BoxTransform.GetRotation().Rotator().Roll);
        BoxTransform.SetScale3D(BoxObject.Scale);

        ABoxClass* SpawnedBox = GetWorld()->SpawnActor<ABoxClass>(ABoxClass::StaticClass(), BoxTransform);
        if (SpawnedBox)
        {
            SpawnedBox->InitializeBox(*BoxType);
            // Set the mobility to Movable
            // SpawnedBox->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
            
            // Set the mesh
            // SpawnedBox->GetStaticMeshComponent()->SetStaticMesh(BoxMesh);

            // if (!BoxMaterial) {
            //     UE_LOG(LogTemp, Error, TEXT("BoxMaterial is not assigned!"));
            //     return;
            // }

            // // Create a dynamic material instance and set the color
            // UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(BoxMaterial, SpawnedBox);
            // if (MaterialInstance)
            // {
            //     MaterialInstance->SetVectorParameterValue(FName("BaseColor"), BoxType->Color);
            //     SpawnedBox->GetStaticMeshComponent()->SetMaterial(0, MaterialInstance);
            // }

            // Log the spawned box's details
            UE_LOG(LogTemp, Log, TEXT("Spawned box of type '%s' with health %d and score %d"),
                   *BoxType->Name, BoxType->Health, BoxType->Score);
        }
    }
}

