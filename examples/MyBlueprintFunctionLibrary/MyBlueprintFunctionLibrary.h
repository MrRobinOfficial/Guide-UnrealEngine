// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Math")
	static float GetRandomFloatFromRange(FFloatRange Range);

	UFUNCTION(BlueprintPure, Category = "Math")
	static FVector GetRandomVector(FVector MinVector, FVector MaxVector);

	UFUNCTION(BlueprintPure, Category = "Math")
	static FRotator GetRandomRotator(FRotator MinRotator, FRotator MaxRotator);
};
