// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) return;

	if (PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->SetTargetLocationAndRotation(GetComponentLocation() + GetForwardVector() * Reach, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	
	if (!PhysicsHandle) return;
	FHitResult HitResult;
	if (GetGrabbableInReach(HitResult))
	{
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		HitResult.GetActor()->Tags.Add("Grabbed");
		ComponentToGrab->WakeAllRigidBodies();
		HitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		ComponentToGrab->SetSimulatePhysics(true);
		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, HitResult.Location, GetComponentRotation());
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle) return;
	if (!PhysicsHandle->GetGrabbedComponent()) return;
	PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
	PhysicsHandle->ReleaseComponent();
}

bool UGrabber::GetGrabbableInReach(FHitResult& HitResult)
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * Reach;

	return GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(SphereRadius));
}

