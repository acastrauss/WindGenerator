#include "UIComponents/WindEnergyWindow.h"

#include "imgui.h"

WindEnergyWindow::WindEnergyWindow(
    unsigned int width,
    unsigned int height,
    WindSpeedData wsd
):
    m_WindSpeedData(wsd),
    m_WindSpeedSlider(&m_WindSpeedData),
    m_EnergyDisplay(&m_WindSpeedData),
    m_Width(width),
    m_Height(height)
{}

bool WindEnergyWindow::Render()
{
    static bool show = false;

    ImGui::SetNextWindowSize(
        ImVec2(m_Width, m_Height),
        ImGuiCond_Always
    );

    ImGui::Begin(
        "Wind energy",
        &show,
        //ImGuiWindowFlags_NoMove |
        //ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_AlwaysAutoResize
    );

    bool speedChanged = m_WindSpeedSlider.Render();

    ImGui::NewLine();

    // no need to update, it uses pointer to data
    m_EnergyDisplay.Render();

    ImGui::End();

    return speedChanged;
}


float WindEnergyWindow::getWindSpeed() const
{
    return m_WindSpeedSlider.GetWindSpeed();
}

float WindEnergyWindow::GetBladePercentageIncrease() const
{
    return m_WindSpeedData.GetBladePercentageIncrease();
}

WindSpeedData* WindEnergyWindow::GetWindSpeedData()
{
    return &m_WindSpeedData;
}
