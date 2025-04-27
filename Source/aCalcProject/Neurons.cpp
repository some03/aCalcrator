// Fill out your copyright notice in the Description page of Project Settings.

#include"UObject/ConstructorHelpers.h"
#include "Neurons.h"

// Sets default values
ANeurons::ANeurons()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// メッシュ作成とルート化
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NeuronMesh"));
	RootComponent = Mesh;

	// デフォルトの形状として球体メッシュをセット（Engineにある球体を使用）
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Sphere"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
		Mesh->SetWorldScale3D(FVector(0.2f)); // 直径を30%に縮小
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/SimBlank/Materials/BaseMaterial"));
	if (MaterialAsset.Succeeded())
	{
		Mesh->SetMaterial(0, MaterialAsset.Object);
	}

}

// Called when the game starts or when spawned
void ANeurons::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANeurons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ANeurons::Initialize(FVector LogicalPosition,
	double tau_, double tau_a_, double tau_b_,
	double gB_, double gL_,
	double W_b_, double W_hb_,
	double W_a_, double W_ha_,
	double W_s_, double beta_, double V_th_)
{
	//SetActorLocation(LogicalPosition);

	x = LogicalPosition.X;
	y = LogicalPosition.Y;
	z = LogicalPosition.Z;


	tau = tau_;
	tau_a = tau_a_;
	tau_b = tau_b_;
	gB = gB_;
	gL = gL_;
	W_b = W_b_;
	W_hb = W_hb_;
	W_a = W_a_;
	W_ha = W_ha_;
	W_s = W_s_;
	beta = beta_;
	V_th = V_th_;
}
int ANeurons::Heviside(double r, double threshold)
{
	return (r >= threshold) ? 1 : 0;
}

double ANeurons::Sigmoid(double o, double b)
{
	return 1.0 / (1.0 + exp(-b * o));
}
void ANeurons::Update(double S_in_basal, double S_in_apical, double rec, double dt)
{
	V_b += (W_b * S_in_basal + W_hb * rec - V_b) / tau_b;
	V_a += (W_a * S_in_apical + W_ha * rec - V_a) / tau_a;
	double z_signal = Sigmoid(V_a, beta);

	double h = (gB / gL) * (V_b - U) + W_s * S_in_basal;
	U += (z_signal * h - U) / tau;

	S_h = Heviside(U, V_th);
	if (S_h == 1) stdptime = dt;

	UpdateVisuals(0);
}
void ANeurons::UpdateVisuals(bool ext)
{
	auto Mat = Mesh->CreateAndSetMaterialInstanceDynamic(0);
	if (Mat)
	{

		if(S_h == 1){
			FLinearColor Color=FLinearColor::Red;
			if (sensor)Color = FLinearColor::Blue;

			Color.A = 0.3f;
			Mat->SetVectorParameterValue("Color", Color);
		}
		if (ext) {
			FLinearColor Color = FLinearColor::Green;

			Color.A = 0.3f;
			Mat->SetVectorParameterValue("Color", Color);
		}
	}
}

