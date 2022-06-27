#pragma once

#include "WindSpeedSlider.h"
#include "EnergyDisplay.h"

constexpr static const unsigned int wewWidth = 400;
constexpr static const unsigned int wewHeight = 250;

class WindEnergyWindow {
private:
    WindSpeedData m_WindSpeedData;
    WindSpeedSlider m_WindSpeedSlider;
    EnergyDisplay m_EnergyDisplay;

    const unsigned int m_Width;
    const unsigned int m_Height;

    WindEnergyWindow(
        const WindEnergyWindow&
    ) = delete;
    WindEnergyWindow& operator=(
        const WindEnergyWindow&
    ) = delete;

public:

    WindEnergyWindow(
        unsigned int width = wewWidth,
        unsigned int height = wewHeight,
        WindSpeedData wsd = WindSpeedData()
    );

    float getWindSpeed() const;

    float GetBladePercentageIncrease() const;

    WindSpeedData* GetWindSpeedData();

    bool Render();
};
