// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "Trigger.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* MoverToSet);

private:
	UPROPERTY(EditAnywhere, Category = "Actor Tag")
	FName ActorTag;

	AActor* GetAcceptableActor();

	UMover* Mover;

};
