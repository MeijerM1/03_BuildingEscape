// Copyright Max Meijer 2017.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	UE_LOG(LogTemp, Warning, TEXT("Actor is %s"), *ActorThatOpens->GetName());
}

void UOpenDoor::OpenDoor()
{


	// Find the owning Actor
	AActor* Owner = GetOwner();

	// Create a rotator
	FRotator NewRotation = FRotator(0.0f, -75.0f, 0.0f);

	// Set the rotation
	Owner->SetActorRotation(NewRotation);

	UE_LOG(LogTemp, Warning, TEXT("Opening door %s"), *Owner->GetName());
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Make sure none of the pointers is a null pointer
	if (ActorThatOpens != nullptr && PressurePlate != nullptr)
	{
		// Poll the trigger volume
		// If the actor that opens is in the volume
		if (PressurePlate->IsOverlappingActor(ActorThatOpens))
		{
			OpenDoor();
		}
	}
}

