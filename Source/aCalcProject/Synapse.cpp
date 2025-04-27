// Fill out your copyright notice in the Description page of Project Settings.


#include "Synapse.h"
#include "Components/SplineMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASynapse::ASynapse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
        Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
        Spline->SetMobility(EComponentMobility::Movable);
        RootComponent = Spline;
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/SimBlank/Materials/BaseMaterial"));
	if (MaterialAsset.Succeeded())
	{
		LineMaterial=MaterialAsset.Object;
	}

}


// Called when the game starts or when spawned
void ASynapse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASynapse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASynapse::SynapseLineInit(FVector Start, FVector End, bool apical)
{
	Spline->ClearSplinePoints();
	Spline->AddSplinePoint(Start, ESplineCoordinateSpace::World);
	Spline->AddSplinePoint(End, ESplineCoordinateSpace::World);
	Spline->SetSplinePointType(0, ESplinePointType::Linear);
	Spline->SetSplinePointType(1, ESplinePointType::Linear);

	USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
	SplineMesh->SetMobility(EComponentMobility::Movable);
	SplineMesh->SetStaticMesh(LineMesh);
	SplineMesh->SetMaterial(0, LineMaterial);
	SplineMesh->RegisterComponentWithWorld(GetWorld());
	SplineMesh->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);

	FVector StartTangent = Spline->GetTangentAtSplinePoint(0, ESplineCoordinateSpace::World);
	FVector EndTangent = Spline->GetTangentAtSplinePoint(1, ESplineCoordinateSpace::World);

	SplineMesh->SetStartAndEnd(Start, StartTangent, End, EndTangent);
	UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(LineMaterial, this);


	if (apical)
	{
		DynMat->SetVectorParameterValue(FName("Color"), FLinearColor::Yellow);
	}
	else
	{
		DynMat->SetVectorParameterValue(FName("Color"), FLinearColor::Gray);
	}
	SplineMesh->SetMaterial(0, DynMat);
}

