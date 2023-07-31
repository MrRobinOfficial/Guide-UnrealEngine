#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

// Forward declarations
class UAudioComponent;

UCLASS()
class MYPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "MyActor")
	TObjectPtr<UAudioComponent> BarkComponent;

	UPROPERTY(EditAnywhere, Category = "MyActor", meta = (ClampMin = 0.0f, ClampMax = 3.0f))
	float BarkStartTime = 0.0f;

public:
	UFUNCTION(BlueprintCallable, Category = "MyActor")
	void Bark();
};
