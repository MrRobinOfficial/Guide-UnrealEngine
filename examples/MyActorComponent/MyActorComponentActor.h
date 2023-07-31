#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorComponent.h"
#include "MyActorComponentActor.generated.h"

UCLASS()
class MYPROJECT_API AMyActorComponentActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMyActorComponentActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMyActorComponent> ActorComp = nullptr;
};
