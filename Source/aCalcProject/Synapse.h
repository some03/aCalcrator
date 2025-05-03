// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Synapse.generated.h"

UCLASS()
class ACALCPROJECT_API ASynapse : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASynapse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SynapseLineInit(FVector Start, FVector End,bool apical);
	void CurveLineInit(FVector Start, FVector End, FVector Control);

	int w = 0;

	UPROPERTY(EditAnywhere)
	USplineComponent* Spline;

	UPROPERTY(EditAnywhere)
	UStaticMesh* LineMesh;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* LineMaterial;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* LineMaterialInstance;

};
