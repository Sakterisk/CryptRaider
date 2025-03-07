// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	FVector StartLocation = Owner->GetActorLocation();
	Speed = FVector::Dist(StartLocation, StartLocation + OffsetLocation) / TimeToReachTarget;
	EndLocation = StartLocation + OffsetLocation;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Owner && bIsMoving)
	{
		FVector CurrentLocation = Owner->GetActorLocation();
		Owner->SetActorLocation(FMath::VInterpConstantTo(CurrentLocation, EndLocation, DeltaTime, Speed));
	}
}

