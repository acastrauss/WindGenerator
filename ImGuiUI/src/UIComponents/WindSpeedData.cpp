#include "UIComponents/WindSpeedData.h"

WindSpeedData::WindSpeedData(float bladeLen,float windSpeed, float minSpeed, float maxSpeed):
    WindSpeed(windSpeed),
    MinSpeed(minSpeed),
    MaxSpeed(maxSpeed),
    bladeLength(bladeLen)
{}

WindSpeedData::WindSpeedData(const WindSpeedData& ref):
    WindSpeed(ref.WindSpeed),
    MinSpeed(ref.MinSpeed),
    MaxSpeed(ref.MaxSpeed),
    bladeLength(ref.bladeLength)
{}

WindSpeedData& WindSpeedData::operator=(const WindSpeedData& rhs)
{
    WindSpeed = rhs.WindSpeed;
    MinSpeed = rhs.MinSpeed;
    MaxSpeed = rhs.MaxSpeed;
    bladeLength = rhs.bladeLength;
    return *this;
}
