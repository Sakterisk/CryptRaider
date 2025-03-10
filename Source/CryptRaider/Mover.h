// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetIsMoving(bool bIsMovingToSet);

private:
	AActor* Owner = nullptr;

	UPROPERTY(EditAnywhere)
	FVector OffsetLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	float TimeToReachTarget = 1;

	UPROPERTY(EditAnywhere)
	bool bIsMoving = false;

	FVector StartLocation;
	FVector EndLocation;
	float Speed;
};
