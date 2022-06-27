#include "UIComponents/WindSpeedData.h"

WindSpeedData::WindSpeedData(
    float bladeLen, float minBladeLen, float maxBladeLen,
    float windSpeed, float minSpeed, float maxSpeed,
    float numOfGens
):
    WindSpeed(windSpeed), MinSpeed(minSpeed), MaxSpeed(maxSpeed),
    BladeLength(bladeLen), MinBladeLength(minBladeLen), MaxBladeLength(maxBladeLen),
    NumOfGenerators(numOfGens)
{
}

WindSpeedData::WindSpeedData(const WindSpeedData& ref):
    WindSpeed(ref.WindSpeed),
    MinSpeed(ref.MinSpeed),
    MaxSpeed(ref.MaxSpeed),
    BladeLength(ref.BladeLength),
    MinBladeLength(ref.MinBladeLength),
    MaxBladeLength(ref.MaxBladeLength),
    NumOfGenerators(ref.NumOfGenerators)
{}

WindSpeedData& WindSpeedData::operator=(const WindSpeedData& rhs)
{
    WindSpeed = rhs.WindSpeed;
    MinSpeed = rhs.MinSpeed;
    MaxSpeed = rhs.MaxSpeed;
    BladeLength = rhs.BladeLength;
    MinBladeLength = rhs.MinBladeLength;
    MaxBladeLength = rhs.MaxBladeLength;
    NumOfGenerators = rhs.NumOfGenerators;
    return *this;
}

float WindSpeedData::GetBladePercentageIncrease() const
{
    return BladeLength / defaultBladeLength;
}

