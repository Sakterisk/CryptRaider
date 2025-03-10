// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"

UTrigger::UTrigger()
{
    PrimaryComponentTick.bCanEverTick = true;
    UE_LOG(LogTemp, Display, TEXT("Trigger Constructor"));
}

void UTrigger::BeginPlay()
{
    Super::BeginPlay();
    SetActive(true);
    SetComponentTickEnabled(true);
    PrimaryComponentTick.SetTickFunctionEnable(true);
}

void UTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* Actor = GetAcceptableActor();

    if (Actor)
    {
        Actor->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
        Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetIsMoving(true);
    }
    else
    {
        Mover->SetIsMoving(false);
    }

}

AActor* UTrigger::GetAcceptableActor()
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    for (AActor* Actor : Actors)
    {
        if (Actor->ActorHasTag(ActorTag) && !Actor->ActorHasTag("Grabbed"))
        {
            return Actor;
        }
    }
    return nullptr;
}

void UTrigger::SetMover(UMover* MoverToSet)
{
    Mover = MoverToSet;
}