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
    ImGui::Text("Minimum operable speed:4 m/s");
    ImGui::NewLine();
    ImGui::Text("Maximum operable speed:24 m/s");

    bool speedUpdated = ImGui::SliderFloat(
        "Wind speed [m/s]",
        &(m_WindSpeedData->WindSpeed),
        m_WindSpeedData->MinSpeed,
        m_WindSpeedData->MaxSpeed,
        "%.2f",
        ImGuiSliderFlags_None
    );

    ImGui::NewLine();

    ImGui::SliderFloat(
        "Blade length[m]:",
        &(m_WindSpeedData->BladeLength),
        m_WindSpeedData->MinBladeLength,
        m_WindSpeedData->MaxBladeLength,
        "%.2f",
        ImGuiSliderFlags_None
    );

    return speedUpdated;
}
