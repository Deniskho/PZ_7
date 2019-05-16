// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "ShooterMode.h"
#include "Turret.generated.h"

DECLARE_EVENT(ATurret, FOnTurretKilled);

UCLASS()
class PZ_3_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurret();

	UPROPERTY(EditAnywhere, Category = TurretSettings)
	float Health;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent * TurretBody;

protected:
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FOnTurretKilled OnTurretKilled;
	
};
