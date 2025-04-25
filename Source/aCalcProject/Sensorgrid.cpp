// Fill out your copyright notice in the Description page of Project Settings.


#include "Sensorgrid.h"

// Sets default values
ASensorgrid::ASensorgrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponent の作成

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneAsset(TEXT("/Engine/BasicShapes/Plane"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatAsset(TEXT("/Game/SimBlank/Materials/BaseMaterial"));
	
	if (MatAsset.Succeeded())
	{
		BaseMaterial = MatAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Material not found!"));
	}

	if (PlaneAsset.Succeeded())
	{
		PlaneMeshAsset = PlaneAsset.Object;

	}

}

// Called when the game starts or when spawned
void ASensorgrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASensorgrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASensorgrid::setCellColor(int32 z, int32 y, const FLinearColor& Color)
{
	int index = z * Cols + y;
	if (CellMaterials.IsValidIndex(index))
	{
		CellMaterials[index]->SetVectorParameterValue("Color", Color);
	}
}
void ASensorgrid::OnConstruction(const FTransform& Transform)
{ 

	Super::OnConstruction(Transform);

	// 既存セルの削除
	for (UStaticMeshComponent* Comp : CellComponents)
	{
		if (Comp) Comp->DestroyComponent();
	}
	CellComponents.Empty();
	CellMaterials.Empty();

	// セル生成
	for (int z = 0; z < Rows; ++z)
	{
		for (int y = 0; y < Cols; ++y)
		{
			FString Name = FString::Printf(TEXT("Cell_%d_%d"), z, y);
			UStaticMeshComponent* Cell = NewObject<UStaticMeshComponent>(this, *Name);

			if (Cell)
			{
				Cell->SetStaticMesh(PlaneMeshAsset);
				Cell->SetRelativeScale3D(FVector(CellSize / 100.0f));
				Cell->SetRelativeRotation(FRotator(0.f, 0.f, 0.f)); // Z軸平行（ZY面）
				Cell->SetRelativeLocation(FVector(y * CellSize, z * CellSize,0.f));
				Cell->SetupAttachment(RootComponent);
				Cell->RegisterComponent();

				if (BaseMaterial)
				{
					UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(BaseMaterial, this);
					DynMat->SetVectorParameterValue("Color", FLinearColor::Black);
					DynMat->SetScalarParameterValue("Opacity", 0.4f);
					Cell->SetMaterial(0, DynMat);
					CellMaterials.Add(DynMat);
				}
				CellComponents.Add(Cell);
			}
		}
	}
}

