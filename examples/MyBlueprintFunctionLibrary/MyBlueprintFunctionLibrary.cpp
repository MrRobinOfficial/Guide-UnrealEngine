// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

#pragma region Random Functions

FVector UMyBlueprintFunctionLibrary::GetRandomVector(FVector MinVector, FVector MaxVector)
{
	FVector SpawnVector;

	SpawnVector.X = FMath::FRandRange(MinVector.X, MaxVector.X);
	SpawnVector.Y = FMath::FRandRange(MinVector.Y, MaxVector.Y);
	SpawnVector.Z = FMath::FRandRange(MinVector.Z, MaxVector.Z);

	return SpawnVector;
}

FRotator UMyBlueprintFunctionLibrary::GetRandomRotator(FRotator MinRotator, FRotator MaxRotator)
{
	float Pitch = FMath::FRandRange(MinRotator.Pitch, MaxRotator.Pitch);
	float Yaw = FMath::FRandRange(MinRotator.Yaw, MaxRotator.Yaw);
	float Roll = FMath::FRandRange(MinRotator.Roll, MaxRotator.Roll);

	return FRotator(Pitch, Yaw, Roll);
}

float UMyBlueprintFunctionLibrary::GetRandomFloatFromRange(FFloatRange Range)
{
	const float& LowerBound = Range.GetLowerBound().GetValue();
	const float& UpperBound = Range.GetUpperBound().GetValue();

	return FMath::FRandRange(LowerBound, UpperBound);
}

#pragma endregion