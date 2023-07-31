#include "MyInterfaceActor.h"

// Sets default values
AMyInterfaceActor::AMyInterfaceActor()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyInterfaceActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyInterfaceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyInterfaceActor::Kill_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Killed!"));

	Destroy();
}