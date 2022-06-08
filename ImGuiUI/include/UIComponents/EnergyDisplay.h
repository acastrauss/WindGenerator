#pragma once

#include "WindSpeedData.h"

class EnergyDisplay {
private:
    WindSpeedData* m_WindSpeedData;

    EnergyDisplay() = delete;
    EnergyDisplay(
        const EnergyDisplay&
    ) = delete;
    EnergyDisplay& operator=(
        const EnergyDisplay&
    ) = delete;

public:
    EnergyDisplay(WindSpeedData* wsd);

    void Render();
};
