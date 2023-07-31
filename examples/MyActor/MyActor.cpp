#include "MyActor.h"

#include "Components/AudioComponent.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarkComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BarkComponent"));

	checkf(BarkComponent, TEXT("BarkComponent cannot be null!"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyActor::Bark()
{
	BarkComponent->Play(BarkStartTime);
}