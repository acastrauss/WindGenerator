#include "UIComponents/WindSpeedSlider.h"

#include "imgui.h"

WindSpeedSlider::WindSpeedSlider(WindSpeedData* windSpeedData):
    m_WindSpeedData(windSpeedData)
{}

float WindSpeedSlider::GetWindSpeed() const
{
    return m_WindSpeedData->WindSpeed;
}

bool WindSpeedSlider::Render()
{
    bool retVal = true;

    retVal &= ImGui::SliderFloat(
        "Wind speed [m/s]",
        &(m_WindSpeedData->WindSpeed),
        m_WindSpeedData->MinSpeed,
        m_WindSpeedData->MaxSpeed,
        "%.2f",
        ImGuiSliderFlags_None
    );

    ImGui::NewLine();

    retVal &= ImGui::SliderFloat(
        "Blade length[m]:",
        &(m_WindSpeedData->BladeLength),
        m_WindSpeedData->MinBladeLength,
        m_WindSpeedData->MaxBladeLength,
        "%.2f",
        ImGuiSliderFlags_None
    );

    return retVal;
}
