#pragma once

constexpr static const float defaultWindSpeed = 10.0f;
constexpr static const float defaultMinWindSpeed = 0.0f;
constexpr static const float defaultMaxWindSpeed = 100.0f;
constexpr static const float defaultBladeLength = 50.0f;

/// <summary>
/// Wrapper for wind speed data,
/// so it can be used throught UI components
/// </summary>
struct WindSpeedData {
    float WindSpeed;
    float MinSpeed;
    float MaxSpeed;
    float bladeLength;

    WindSpeedData(
        float bladeLen = defaultBladeLength,
        float windSpeed = defaultWindSpeed,
        float minSpeed = defaultMinWindSpeed,
        float maxSpeed = defaultMaxWindSpeed
        
    );

    WindSpeedData(
        const WindSpeedData& ref
    );

    WindSpeedData& operator=(
        const WindSpeedData& rhs
    );
};
