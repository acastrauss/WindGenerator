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
    return ImGui::SliderFloat(
        "Wind speed [m/s]",
        &(m_WindSpeedData->WindSpeed),
        m_WindSpeedData->MinSpeed,
        m_WindSpeedData->MaxSpeed,
        "%.2f",
        ImGuiSliderFlags_None
    );
}
