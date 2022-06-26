#pragma once

constexpr static const float defaultWindSpeed = 5.0f;
constexpr static const float defaultMinWindSpeed = 0.0f;
constexpr static const float defaultMaxWindSpeed = 15.0f;
constexpr static const float defaultBladeLength = 52.0f;
constexpr static const float minBladeLength = 52.0f;
constexpr static const float maxBladeLength = 107.0f;
constexpr static const unsigned int defaultNumOfGenerators = 4;

/// <summary>
/// Wrapper for wind speed data,
/// so it can be used throught UI components
/// </summary>
struct WindSpeedData {
    float WindSpeed;
    float MinSpeed;
    float MaxSpeed;
    float BladeLength;
    float MinBladeLength;
    float MaxBladeLength;
    unsigned int NumOfGenerators;

    WindSpeedData(
        float bladeLen = defaultBladeLength,
        float minBladeLen = minBladeLength,
        float maxBladeLen = maxBladeLength,
        float windSpeed = defaultWindSpeed,
        float minSpeed = defaultMinWindSpeed,
        float maxSpeed = defaultMaxWindSpeed,
        float numOfGens = defaultNumOfGenerators
    );

    WindSpeedData(
        const WindSpeedData& ref
    );

    WindSpeedData& operator=(
        const WindSpeedData& rhs
    );

    float GetBladePercentageIncrease() const;
};
