#pragma once

#include "WindSpeedData.h"

class WindSpeedSlider {
private:
    WindSpeedData* m_WindSpeedData;

    WindSpeedSlider() = delete;

    WindSpeedSlider(
        const WindSpeedSlider&
    ) = delete;

    WindSpeedSlider& operator=(
        const WindSpeedSlider&
    ) = delete;

public:

    WindSpeedSlider(
        WindSpeedData* windSpeedData
    );
    ~WindSpeedSlider() = default;

    bool Render();
    float GetWindSpeed() const;
};
