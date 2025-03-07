// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"

void UTrigger::BeginPlay()
{
	Super::BeginPlay();
	
    UE_LOG(LogTemp, Display, TEXT("Trigger Begin Play"));
}