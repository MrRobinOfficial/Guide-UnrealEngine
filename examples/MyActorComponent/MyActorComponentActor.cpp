#include "MyActorComponentActor.h"

// Sets default values
AMyActorComponentActor::AMyActorComponentActor()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorComp = CreateDefaultSubobject<UMyActorComponent>(TEXT("ActorComp"));

	checkf(ActorComp, TEXT("ActorComp cannot be null!"));
}

// Called when the game starts or when spawned
void AMyActorComponentActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyActorComponentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}