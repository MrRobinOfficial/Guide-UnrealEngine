## 🎨 Draw Debug Shapes

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

<!-- TODO: Fix images -->

Include the header file:

```cpp
#include "DrawDebugHelpers.h"
```

Draw a point:

```cpp
bool bPersistentLines = true;

FVector Location = FVector(0, 0, 600);
float Size = 200.0f;
FColor Color = FColor(52, 220, 239);

DrawDebugPoint(GetWorld(), Location, Size, Color, bPersistentLines);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Point" />
    <figcaption>Result</figcaption>
</figure>

Draw a sphere:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 2.0f;

FVector Center = FVector(0, -600, 600);
float Radius = 200.0f;
int32 Segments = 26;
FColor Color = FColor(181, 0, 0);

DrawDebugSphere(GetWorld(), Center, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Sphere" />
    <figcaption>Result</figcaption>
</figure>

Draw a circle:

```cpp
float Radius = 200.0f;
int32 Segments = 50;
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 10.0f;

// Draw a circle via matrix
FMatrix TransformMatrix = FMatrix();
DrawDebugCircle(GetWorld(), TransformMatrix, Radius, Segments, FColor(0, 104, 167), bPersistentLines, LifeTime, DepthPriority, Thickness);

// Draw a circle via location
FVector Center = FVector(-300, 0, 600);
DrawDebugCircle(GetWorld(), Center, Radius, Segments, FColor(0, 0, 0), bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Circle" />
    <figcaption>Result</figcaption>
</figure>

Draw a circle arc:

```cpp

bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 10.0f;

FVector Center = FVector(-400, -600, 600);
float Radius = 200.0f;
FVector Direction = FVector::ForwardVector;
float AngleWidth = 500.0;
int32 Segments = 50;
FColor Color = FColor::Yellow;

DrawDebugCircleArc(GetWorld(), Center, Radius, Direction, AngleWidth, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Cricle Arc" />
    <figcaption>Result</figcaption>
</figure>

Draw a 2D donut:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 10.0f;

FMatrix TransformMatrix = FMatrix();
float InnerRadius = 100.0f;
float OuterRadius = 300.0f;
int32 Segments = 26;
FColor Color = FColor::Cyan;

DrawDebug2DDonut(GetWorld(), TransformMatrix, InnerRadius, OuterRadius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug 2D Donut" />
    <figcaption>Result</figcaption>
</figure>

Draw a solid box:

```cpp
bool bPersistentLines = true;

// Draw a solid box
FVector MinPoint = FVector(0, 0, 0);
FVector MaxPoint = FVector(200, 200, 200);
FBox MyBox = FBox(MinPoint, MaxPoint);
FTransform MyTransform = FTransform(FVector(400, 600, 900));

DrawDebugSolidBox(GetWorld(), MyBox, FColor(20, 100, 240), MyTransform, bPersistentLines);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Soild Box" />
    <figcaption>Result</figcaption>
</figure>

Draw a wired box:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 10.0f;

// Draw a wired box
FVector Center = FVector(-400, -600, 600);
FVector Extent = FVector(100, 100, 100);
FColor Color = FColor::Purple;

DrawDebugBox(GetWorld(), Center, Extent, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Wired Box" />
    <figcaption>Result</figcaption>
</figure>

Draw a cylinder:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 2.0f;

FVector Start = FVector(0, -600, 600);
FVector End = FVector(0, -1800, 600);
float Radius = 200.0f;
int32 Segments = 26;
FColor Color = FColor(181, 0, 0);

DrawDebugCylinder(GetWorld(), Start, End, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Cylinder" />
    <figcaption>Result</figcaption>
</figure>

Draw a capsule:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 2.0f;

FVector Center = FVector(0, -600, 600);
float HalfHeight = 400.0f;
float Radius = 200.0f;
FQuat Rotation = FQuat::Identity;
FColor Color = FColor(181, 0, 0);

DrawDebugCapsule(GetWorld(), Center, HalfHeight, Radius, Rotation, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Capsule" />
    <figcaption>Result</figcaption>
</figure>

Draw a cone:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 2.0f;

FVector Origin = FVector(0, -600, 600);
FVector Direction = FVector(0, -600, 600);
float Length = 200.0f;
float AngleWidth = 100.0f;
float AngleHeight = 300.0f;
int32 NumSides = 26;
FColor Color = FColor::Yellow;

DrawDebugCone(GetWorld(), Origin, Direction, Length, AngleWidth, AngleHeight, NumSides, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Cone" />
    <figcaption>Result</figcaption>
</figure>

Draw a plane:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 2.0f;

FVector NormalVector = FVector::UpVector;
FPlane Plane = FPlane(NormalVector);
FVector Location = FVector(0, -600, 600);
FColor Color = FColor(181, 0, 0);

float Size = 100.0f;
DrawDebugSolidPlane(GetWorld(), Plane, Location, float Size, Color, bPersistent, LifeTime, DepthPriority);

FVector2D Extents = FVector2D::One();
DrawDebugSolidPlane(GetWorld(), Plane, Location, Extents, Color, bPersistent, LifeTime, DepthPriority);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Plane" />
    <figcaption>Result</figcaption>
</figure>

Draw a line:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 10.0f;

FVector LocationFrom = FVector(0, -600, 600);
FVector LocationTo = FVector(0, 600, 600);
FColor Color = FColor::Emerald;

DrawDebugLine(GetWorld(), LocationFrom, LocationTo, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Line" />
    <figcaption>Result</figcaption>
</figure>

Draw an arrow:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 5.0f;

FVector LocationFrom =  FVector(-300, 600, 600);
FVector LocationTo = FVector(-300, -600, 600);
float ArrowSize = 120.0f;
FColor Color = FColor::Magenta;

DrawDebugDirectionalArrow(GetWorld(), LocationFrom, LocationTo, ArrowSize, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Arrow" />
    <figcaption>Result</figcaption>
</figure>

Draw a crosshair:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;

FVector AxisLocation = FVector(0, 0, 1000);
FRotator AxisRotation = FRotator::ZeroRotator;
float Scale = 500.0f;
FColor Color = FColor::White;

DrawDebugCrosshairs(GetWorld(), AxisLocation, AxisRotation, Scale, Color, bPersistentLines, LifeTime, DepthPriority);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Crosshair" />
    <figcaption>Result</figcaption>
</figure>

Draw a camera:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;

FVector Location = FVector(0, -600, 600);
FRotator Rotation = FRotator::ZeroRotator;
float FOVDeg = 45.0f;
float Scale = 1.0f;
FColor Color = FColor::White

DrawDebugCamera(GetWorld(), Location, Rotation, FOVDeg, Scale, Color, bPersistentLines, LifeTime, DepthPriority);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Camera" />
    <figcaption>Result</figcaption>
</figure>

Draw a mesh:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;

const TArray<FVector> Verts;
const TArray<int32> Indices;
FColor Color = FColor(181, 0, 0);

DrawDebugMesh(GetWorld(), Verts, Indices, Color, bPersistent, LifeTime, DepthPriority);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Mesh" />
    <figcaption>Result</figcaption>
</figure>

Draw a string:

```cpp
FVector TextLocation = FVector(0, -600, 600);
FString Str = TEXT("Hello, World!");
AActor* TestBaseActor = NULL;
FColor TextColor = FColor::White;
float Duration = -1.0f;
bool bDrawShadow = false;
float FontScale = 1.0f;

DrawDebugString(GetWorld(), TextLocation, Str, TestBaseActor, TextColor, Duration, bDrawShadow, FontScale);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug String" />
    <figcaption>Result</figcaption>
</figure>

Draw a centripetal catmull-rom spline:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 2.0f;

TConstArrayView<FVector> Points;
float Alpha = 0.5f;
int32 NumSamplesPerSegment = 8;

FColor Color = FColor(181, 0, 0);
DrawCentripetalCatmullRomSpline(GetWorld(), Points, Color, Alpha, NumSamplesPerSegment, bPersistentLines, LifeTime, DepthPriority, Thickness);

TConstArrayView<FColor> Colors;
DrawCentripetalCatmullRomSpline(GetWorld(), Points, Colors, Alpha, NumSamplesPerSegment, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Draw Debug Centripetal catmull-rom spline" />
    <figcaption>Result</figcaption>
</figure>

---

You can read more about [drawing shapes by Harrison McGuire](https://unrealcpp.com/draw-debug-helpers/).

You can also watch a [video about it from Ryan Sweeney](https://www.youtube.com/watch?v=FQQmdirfVYg).
