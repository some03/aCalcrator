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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cylinder"));
	if (MeshAsset.Succeeded())
	{
		LineMesh = MeshAsset.Object;
	}
	W.SetNum(8 * 8);

}


// Called when the game starts or when spawned
void ASynapse::BeginPlay()
{
	Super::BeginPlay();
	Spline->SetVisibility(false /*bNewVisibility*/, false /*bPropagateToChildren*/);

	
}

// Called every frame
void ASynapse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASynapse::SynapseLineInit(FVector Start, FVector End, bool apical)
{
	// 1) Spline を Local 座標で設定
	Spline->ClearSplinePoints();
	FVector LocalStart = Start - GetActorLocation();
	FVector LocalEnd = End - GetActorLocation();
	Spline->AddSplinePoint(LocalStart, ESplineCoordinateSpace::Local);
	Spline->AddSplinePoint(LocalEnd, ESplineCoordinateSpace::Local);
	Spline->UpdateSpline();

	// 2) SplineMeshComponent を生成
	USplineMeshComponent* Mesh = NewObject<USplineMeshComponent>(this);
	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->SetStaticMesh(LineMesh);
	Mesh->SetForwardAxis(ESplineMeshAxis::Z);
	Mesh->SetAbsolute(false, false, true);  // スケールはワールド固定

	// マテリアル設定

	FLinearColor CyanColor(0.3f, 0.3f, 0.3f, 0.1f);;
	auto DynMat = UMaterialInstanceDynamic::Create(LineMaterial, this);
	DynMat->SetVectorParameterValue("Color", apical ? CyanColor: FLinearColor::White);
	Mesh->SetMaterial(0, DynMat);

	// アタッチ＆登録
	Mesh->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->RegisterComponentWithWorld(GetWorld());

	// 3) タンジェントを自前計算してセット
	FVector Dir = LocalEnd - LocalStart;
	FVector Tangent = Dir * 0.5f;  // 長すぎず短すぎず
	Mesh->SetStartAndEnd(LocalStart, Tangent, LocalEnd, Tangent, true);

	// 4) 太さ設定
	Mesh->SetStartScale(FVector2D(0.02f, 0.02f));
	Mesh->SetEndScale(FVector2D(0.02f, 0.02f));
}
void ASynapse::CurveLineInit(FVector Start, FVector End, FVector Control)
{
	// 1) Spline を Local 座標で初期化
	Spline->ClearSplinePoints();
	FVector LocalStart = Start - GetActorLocation();
	FVector LocalControl = Control - GetActorLocation();
	FVector LocalEnd = End - GetActorLocation();
	Spline->AddSplinePoint(LocalStart, ESplineCoordinateSpace::Local);
	Spline->AddSplinePoint(LocalControl, ESplineCoordinateSpace::Local);
	Spline->AddSplinePoint(LocalEnd, ESplineCoordinateSpace::Local);
	Spline->UpdateSpline();

	// 共通設定用ラムダ
	auto CreateMeshSegment = [&](int32 PointIndex, bool bApical)
		{
			USplineMeshComponent* Mesh = NewObject<USplineMeshComponent>(this);
			Mesh->SetMobility(EComponentMobility::Movable);
			Mesh->SetStaticMesh(LineMesh);
			Mesh->SetForwardAxis(ESplineMeshAxis::Z);
			// 親（Spline）のスケールを拾わない
			Mesh->SetAbsolute(false, /*bAbsRot=*/false, /*bAbsScale=*/true);

			// マテリアル
			UMaterialInstanceDynamic* Dyn = UMaterialInstanceDynamic::Create(LineMaterial, this);

			FLinearColor Color(1.0f, 1.0f, 1.0f, 0.8f);;
			Dyn->SetVectorParameterValue(FName("Color"), Color);
			Mesh->SetMaterial(0, Dyn);

			// Attach → Register
			Mesh->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
			Mesh->RegisterComponentWithWorld(GetWorld());

			// セグメントの開始/終了位置とタンジェントを取得
			FVector StartPos = Spline->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::Local);
			FVector EndPos = Spline->GetLocationAtSplinePoint(PointIndex + 1, ESplineCoordinateSpace::Local);
			FVector StartTan = Spline->GetTangentAtSplinePoint(PointIndex, ESplineCoordinateSpace::Local);
			FVector EndTan = Spline->GetTangentAtSplinePoint(PointIndex + 1, ESplineCoordinateSpace::Local);

			Mesh->SetStartAndEnd(
				StartPos, StartTan,
				EndPos, EndTan,
				/*bUpdateSpline=*/true
			);

			// 太さ
			Mesh->SetStartScale(FVector2D(0.02f, 0.02f));
			Mesh->SetEndScale(FVector2D(0.02f, 0.02f));
		};

	// 2セグメント分それぞれ生成
	CreateMeshSegment(0, true);  // Start → Control
	CreateMeshSegment(1, true);  // Control → End

}


