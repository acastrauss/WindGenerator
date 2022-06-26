#include "UIComponents/EnergyDisplay.h"

#include "imgui.h"

#include <math.h>

// maybe creat config for parameters
constexpr const float airDensity = 1.23f;
constexpr const float PI = 3.14f;
constexpr const float efficiencyCoefficient = 0.4f;

float GetActivePower(float windSpeed, float bladeLength) {
    return 1.0f / 2.0f * airDensity * powf(bladeLength, 2.0f)
        * PI * powf(windSpeed, 3.0f) * efficiencyCoefficient;
}

EnergyDisplay::EnergyDisplay(WindSpeedData* wsd):
    m_WindSpeedData(wsd)
{}

void EnergyDisplay::Render()
{
    float activePower = GetActivePower(m_WindSpeedData->WindSpeed, m_WindSpeedData->BladeLength);
    float reactivePower = activePower * 0.05f;

    ImGui::Text("Active power: %.2f * %d = %.2f [MW]",
        activePower / pow(10, 3), m_WindSpeedData->NumOfGenerators,
        activePower / pow(10, 3) * m_WindSpeedData->NumOfGenerators);
    ImGui::NewLine();
    ImGui::Text("Reactive power: %.2f * %d = %.2f [MW]",
        reactivePower / pow(10, 3), m_WindSpeedData->NumOfGenerators,
        reactivePower / pow(10, 3) * m_WindSpeedData->NumOfGenerators);
}
