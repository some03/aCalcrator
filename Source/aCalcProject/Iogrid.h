// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Iogrid.generated.h"

UCLASS()
class ACALCPROJECT_API AIogrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIogrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int32 Rows = 8;

	UPROPERTY(EditAnywhere)
	int32 Cols = 8;

	UPROPERTY(EditAnywhere)
	float CellSize = 100.f; // 各セルのサイズ（Unreal単位）

	UPROPERTY(EditAnywhere)
	UStaticMesh* PlaneMeshAsset;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UStaticMeshComponent> MeshComponentClass;

	UPROPERTY()
	UMaterialInterface* BaseMaterial;
	UPROPERTY()
	TArray<UStaticMeshComponent*> CellComponents;
	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> CellMaterials;
	void setCellColor(int32 x, int32 y, const FLinearColor& color);
	virtual void OnConstruction(const FTransform& Transform) override;
	

};
