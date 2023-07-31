#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "MyInterfaceActor.generated.h"

UCLASS()
class MYPROJECT_API AMyInterfaceActor : public AActor, public IMyInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMyInterfaceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Kill_Implementation() override;
};
