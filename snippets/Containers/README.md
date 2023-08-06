```cpp
#include "Containers/Array.h"
#include "Containers/Set.h"
#include "Containers/Map.h"

// Using TArray to create an array of integers
TArray<int32> IntArray;
IntArray.Add(1);
IntArray.Add(2);
IntArray.Add(3);

// Using TSet to create a set of strings
TSet<FString> StringSet;
StringSet.Add(TEXT("Apple"));
StringSet.Add(TEXT("Banana"));
StringSet.Add(TEXT("Orange"));

// Using TMap to create a map of integers and strings
TMap<int32, FString> IntStringMap;
IntStringMap.Add(1, TEXT("One"));
IntStringMap.Add(2, TEXT("Two"));
IntStringMap.Add(3, TEXT("Three"));
```
