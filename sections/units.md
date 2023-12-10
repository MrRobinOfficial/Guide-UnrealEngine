## 🦄 Units

With UHT[^2], you can specify a specific unit for UPROPERTY values. Epic has already provided some of the basic units. Which it includes both metric and imperial system.

Here's a list of units, that Epic has provided:

```cpp
/** Enum *must* be zero-indexed and sequential. Must be grouped by relevance and ordered by magnitude. */
/** Enum *must* match the mirrored enum that exists in CoreUObject/Classes/Object.h for the purposes of UObject reflection */
enum class EUnit : uint8
{
    /** Scalar distance/length units */
    Micrometers, Millimeters, Centimeters, Meters, Kilometers,
    Inches, Feet, Yards, Miles,
    Lightyears,

    /** Angular units */
    Degrees, Radians,

    /** Speed units */
    CentimetersPerSecond, MetersPerSecond, KilometersPerHour, MilesPerHour,

    /** Temperature units */
    Celsius, Farenheit, Kelvin,

    /** Mass units */
    Micrograms, Milligrams, Grams, Kilograms, MetricTons,
    Ounces, Pounds, Stones,

    /** Force units */
    Newtons, PoundsForce, KilogramsForce, KilogramCentimetersPerSecondSquared,

    /** Torque Units */
    NewtonMeters, KilogramCentimetersSquaredPerSecondSquared,

    /** Frequency units */
    Hertz, Kilohertz, Megahertz, Gigahertz, RevolutionsPerMinute,

    /** Data Size units */
    Bytes, Kilobytes, Megabytes, Gigabytes, Terabytes,

    /** Luminous flux units, luminous intensity, illuminance, luminance, exposure value */
    Lumens, Candela, Lux, CandelaPerMeter2, ExposureValue,

    /** Time units */
    Nanoseconds, Microseconds, Milliseconds, Seconds, Minutes, Hours, Days, Months, Years,

    /** Pixel density units */
    PixelsPerInch,

    /** Arbitrary multipliers */
    Percentage,	Multiplier,

    /** Stress units */
    Pascals, KiloPascals, MegaPascals, GigaPascals,

    /** Symbolic entry, not specifiable on meta data */
    Unspecified
};
```

Enumeration that specifies particular classes of unit:

```cpp
enum class EUnitType
{
    Distance, Angle, Speed, Temperature, Mass, Force, Torque, Frequency, DataSize, LuminousFlux, LuminousIntensity, Illuminance, Luminance, Time, PixelDensity, Multipliers, ExposureValue, Stress,

    // Symbolic entry - do not use directly
    NumberOf,
};
```

### Use cases with UHT

Now, we know what types of units there are. We can now use them inside our code.

First we can use them with UHT[^2], by specifying with meta tag.

```cpp
UPROPERTY(meta = (Units = "kg"))
float MassInKg{ 10.0f };
```

By default, Unreal will override your unit with the respective unit for that category. For an example, if I specified my mass variable to use **pounds**, Unreal will overwrite and use **kg** instead.

If you want to disable this feature, then you can use the specifier `ForceUnits` instead.

```cpp
UPROPERTY(meta = (Units = "lbs"))
float MassInPounds{ 22.0f };
```

### Use cases with code

Unreal also have a class for handling the unit conversion.

Here's an example, on how to use conversion class:

```cpp
float Distance = 15.535f; // Unit: Miles

// Miles -> Kilometers
Distance = FUnitConversion::Convert(Distance, EUnit::Miles, EUnit::Kilometers);

// Distance: 25 [km]
```

You can also get the specified unit category:

```cpp
EUnitType UnitType = FUnitConversion::GetUnitType(EUnit::Lumens);
// UnitType: LuminousFlux
```

You can also automatic change a unit to fit the best:

```cpp
float Distance = 300000.0f; // Units: Centimeters
FNumericUnit<float> DistanceUnit = FUnitConversion::QuantizeUnitsToBestFit(Distance, EUnit::Centimeters); // Will auto select a better unit

EUnit NewUnit = DistanceUnit.Units;
float NewDistance = DistanceUnit.Value;

// NewDistance: 3.0 [km]
```
