// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Neurons.generated.h"

UCLASS()
class ACALCPROJECT_API ANeurons : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANeurons();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Initialize(FVector LogicalPosition,
		double tau_, double tau_a_, double tau_b_,
		double gB_, double gL_,
		double W_b_, double W_hb_,
		double W_a_, double W_ha_,
		double W_s_, double beta_, double V_th_);

	void SimulateStep(double S_in_basal, double S_in_apical, double rec, double dt);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	// 演算用の値
	double x, y, z;
	double tau, tau_a, tau_b;
	double gB, gL;
	double W_b, W_hb, W_a, W_ha, W_s;
	double beta, V_th;

	double V_b = 0.0, V_a = 0.0, U = 0.0;
	double S_h = 0;
	double stdptime = 0.0;

	int Heviside(double r, double threshold);
	double Sigmoid(double o, double b);
	void UpdateVisuals(); // 色やスケール変化


};
