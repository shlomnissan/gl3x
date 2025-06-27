/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "utilities/performance_graph.hpp"

#include <imgui/imgui.h>

namespace gleam {

auto PerformanceGraph::RenderGraph(const float viewport_width) const -> void {
    static const float kWindowWidth {250.0f};
    static const float kWindowHeight {195.0f};
    ImGui::SetNextWindowSize({kWindowWidth, kWindowHeight});
    ImGui::SetNextWindowPos({viewport_width - kWindowWidth - 10.0f, 10.0f});
    ImGui::Begin("##Stats", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar
    );

    // frames per second
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {0.68f, 0.07f, 0.35f, 1.0f});
    ImGui::Text("FPS: %.0f", frames_per_second_.LastValue());
    ImGui::PlotHistogram(
        "##FPS",
        frames_per_second_.Buffer(), 150, 0, nullptr, 0.0f, 120.0f, {235, 40}
    );
    ImGui::PopStyleColor();

    // frame time
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {0.40f, 0.70f, 0.20f, 1.0f});
    ImGui::Text("Frame Time: %.0fms", frame_time_.LastValue());
    ImGui::PlotHistogram(
        "##Frame Time",
        frame_time_.Buffer(), 150, 0, nullptr, 0.0f, 10.0f, {235, 40}
    );
    ImGui::PopStyleColor();

    // rendered objects
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {0.20f, 0.40f, 0.70f, 1.0f});
    ImGui::Text("Rendered objects: %.0f", rendered_objects_.LastValue());
    ImGui::PlotHistogram(
        "##Rendered Objects",
        rendered_objects_.Buffer(), 150, 0, nullptr, 0.0f, 1000.0f, {235, 40}
    );
    ImGui::PopStyleColor();

    ImGui::End();
}

}