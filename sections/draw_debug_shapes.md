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
    <img src="static/img/debugging/draw_point.png" alt="Draw Debug Point" />
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
FColor Color = FColor(255, 0, 0);

DrawDebugSphere(GetWorld(), Center, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/debugging/draw_sphere.png" alt="Draw Debug Sphere" />
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
    <img src="static/img/debugging/draw_circle.png" alt="Draw Circle" />
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
    <img src="static/img/debugging/draw_circle_arc.png" alt="Draw Cricle Arc" />
    <figcaption>Result</figcaption>
</figure>

Draw a 2D donut:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 10.0f;

const FVector Location = FVector(-400, -600, 600);
const FTransform Transform = FTransform(FQuat::Identity, Location);
FMatrix TransformMatrix = Transform.ToMatrixNoScale();

float InnerRadius = 100.0f;
float OuterRadius = 300.0f;
int32 Segments = 26;
FColor Color = FColor::Cyan;

DrawDebug2DDonut(GetWorld(), TransformMatrix, InnerRadius, OuterRadius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/debugging/draw_2d_donut.png" alt="Draw Debug 2D Donut" />
    <figcaption>Result</figcaption>
</figure>

Draw a solid box:

```cpp
bool bPersistentLines = true;

// Draw a solid box
FVector MinPoint = FVector(0, 0, 0);
FVector MaxPoint = FVector(200, 200, 200);
FBox MyBox = FBox(MinPoint, MaxPoint);
FTransform MyTransform = FTransform(FQuat::Identity, FVector(-400, -600, 600));

DrawDebugSolidBox(GetWorld(), MyBox, FColor(200, 100, 50), MyTransform, bPersistentLines);
```

<figure>
    <img src="static/img/debugging/draw_solid_box.png" alt="Draw Debug Soild Box" />
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
FColor Color = FColor::Red;

DrawDebugBox(GetWorld(), Center, Extent, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/debugging/draw_wired_box.png" alt="Draw Debug Wired Box" />
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
FColor Color = FColor(255, 0, 0);

DrawDebugCylinder(GetWorld(), Start, End, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/debugging/draw_cylinder.png" alt="Draw Debug Cylinder" />
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
FColor Color = FColor(255, 0, 0);

DrawDebugCapsule(GetWorld(), Center, HalfHeight, Radius, Rotation, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/debugging/draw_capsule.png" alt="Draw Debug Capsule" />
    <figcaption>Result</figcaption>
</figure>

Draw a cone:

```cpp
bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 0.0f;

FVector Origin = FVector(0, -600, 0);
FVector Direction = FVector(0, 0, -600);
float Length = 100.0f;
float AngleWidth = 45.0f;
float AngleHeight = 45.0f;
int32 NumSides = 12;
FColor Color = FColor::Yellow;

DrawDebugCone(
    GetWorld(),
    Origin,
    Direction,
    Length,
    FMath::DegreesToRadians(AngleWidth),
    FMath::DegreesToRadians(AngleHeight),
    NumSides,
    Color,
    bPersistentLines,
    LifeTime,
    DepthPriority,
    Thickness
);
```

<figure>
    <img src="static/img/debugging/draw_cone.png" alt="Draw Debug Cone" />
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
FColor Color = FColor(255, 0, 0);

float Size = 100.0f;
DrawDebugSolidPlane(GetWorld(), Plane, Location, Size, Color, bPersistentLines, LifeTime, DepthPriority);

FVector2D Extents = FVector2D::One();
DrawDebugSolidPlane(GetWorld(), Plane, Location, Extents, Color, bPersistentLines, LifeTime, DepthPriority);
```

<figure>
    <img src="static/img/debugging/draw_plane.png" alt="Draw Debug Plane" />
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
    <img src="static/img/debugging/draw_line.png" alt="Draw Debug Line" />
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
    <img src="static/img/debugging/draw_arrow.png" alt="Draw Debug Arrow" />
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
    <img src="static/img/debugging/draw_crosshair.png" alt="Draw Debug Crosshair" />
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
FColor Color = FColor::White;

DrawDebugCamera(GetWorld(), Location, Rotation, FOVDeg, Scale, Color, bPersistentLines, LifeTime, DepthPriority);
```

<figure>
    <img src="static/img/debugging/draw_camera.png" alt="Draw Debug Camera" />
    <figcaption>Result</figcaption>
</figure>

Draw a mesh:

```cpp
FVector Offset = FVector(-300, 600, 600); // Example offset values

// Vertices for a cube with offset
const TArray<FVector> Verts = {
    FVector(-50, 50, 50) + Offset,  // 0
    FVector(50, 50, 50) + Offset,   // 1
    FVector(50, -50, 50) + Offset,  // 2
    FVector(-50, -50, 50) + Offset, // 3
    FVector(-50, 50, -50) + Offset, // 4
    FVector(50, 50, -50) + Offset,  // 5
    FVector(50, -50, -50) + Offset, // 6
    FVector(-50, -50, -50) + Offset // 7
};

// Indices for a cube
const TArray<int32> Indices = {
    0, 1, 2, 2, 3, 0, // Front face
    1, 5, 6, 6, 2, 1, // Right face
    5, 4, 7, 7, 6, 5, // Back face
    4, 0, 3, 3, 7, 4, // Left face
    4, 5, 1, 1, 0, 4, // Top face
    3, 2, 6, 6, 7, 3  // Bottom face
};

bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
FColor Color = FColor(255, 0, 0);

DrawDebugMesh(GetWorld(), Verts, Indices, Color, bPersistentLines, LifeTime, DepthPriority);
```

<figure>
    <img src="static/img/debugging/draw_mesh.png" alt="Draw Debug Mesh" />
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
float FontScale = 5.0f;

DrawDebugString(GetWorld(), TextLocation, Str, TestBaseActor, TextColor, Duration, bDrawShadow, FontScale);
```

<figure>
    <img src="static/img/debugging/draw_string.png" alt="Draw Debug String" />
    <figcaption>Result</figcaption>
</figure>

Draw a centripetal catmull-rom spline:

```cpp
FVector Offset = FVector(-300, 600, 600); // Example offset values

TArray<FVector> Points;
Points.Emplace(FVector(0, 0, 0) + Offset); // Add the starting point with offset
Points.Emplace(FVector(100, 50, 0) + Offset); // Add the first control point with offset
Points.Emplace(FVector(200, 100, 0) + Offset); // Add the second control point with offset
Points.Emplace(FVector(300, 0, 0) + Offset); // Add the ending point with offset

float Alpha = 0.5f;
int32 NumSamplesPerSegment = 8;

bool bPersistentLines = true;
float LifeTime = -1.0f;
uint8 DepthPriority = 0;
float Thickness = 2.0f;

FColor Color = FColor(255, 0, 0);
DrawCentripetalCatmullRomSpline(GetWorld(), Points, Color, Alpha, NumSamplesPerSegment, bPersistentLines, LifeTime, DepthPriority, Thickness);

TConstArrayView<FColor> Colors;
DrawCentripetalCatmullRomSpline(GetWorld(), Points, Colors, Alpha, NumSamplesPerSegment, bPersistentLines, LifeTime, DepthPriority, Thickness);
```

<figure>
    <img src="static/img/debugging/draw_centripetal_catmull_rom_spline.png" alt="Draw Debug Centripetal catmull-rom spline" />
    <figcaption>Result</figcaption>
</figure>

---

You can read more about [drawing shapes by Harrison McGuire](https://unrealcpp.com/draw-debug-helpers/).

You can also watch a [video about it from Ryan Sweeney](https://www.youtube.com/watch?v=FQQmdirfVYg).
