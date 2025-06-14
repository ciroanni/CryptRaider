// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor *overlappingActor = GetAcceptableActor();
    if (overlappingActor)
    {
        UPrimitiveComponent *Component = Cast<UPrimitiveComponent>(overlappingActor->GetRootComponent());
        if (Component)
        {
            Component->SetSimulatePhysics(false);
        }
        overlappingActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);
    }
    else
    {
        Mover->SetShouldMove(false);
    }
}

AActor *UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor *> Actors;
    GetOverlappingActors(Actors);

    for (AActor *Actor : Actors)
    {
        bool HasAcceptableTag = Actor->ActorHasTag(TriggerTag);
        bool IsGrabbed = Actor->ActorHasTag("Grabbed");
        if (HasAcceptableTag && !IsGrabbed)
        {
            return Actor;
        }
    }
    return nullptr;
}

void UTriggerComponent::SetMover(UMover *NewMover)
{
    Mover = NewMover;
}