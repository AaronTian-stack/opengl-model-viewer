//
// Created by Aaron Tian on 8/5/23.
//

#include "property_inspector.h"
#include "window.h"

#include "imgui/imgui.h"

void PropertyInspector::render(Window windowObj) {
    bool info = false;
    ImGui::SetNextWindowPos(ImVec2(0, 18));
    auto flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowFocus();

    ImGui::Begin("Model Viewer", nullptr, flags);

    ImGui::Text("Press ~ to toggle first person camera");
    ImGui::Text("Use WASDQE and mouse to control camera");

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::MenuItem("Quit"))
        {
            glfwSetWindowShouldClose(windowObj.window, true);
        }
        if (ImGui::MenuItem("Info")) {
            info = true;
        }
        ImGui::EndMainMenuBar();
    }

    if (info)
    {
        ImGui::OpenPopup("popup");
    }

    if (ImGui::BeginPopup("popup"))
    {
        ImGui::Text("Made by Aaron Tian \n2023");
        ImGui::EndPopup();
    }

    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat3("Position", &*position, 0.05f);
        ImGui::DragFloat3("Rotation", &*rotation, 0.1f);
        ImGui::DragFloat3("Scale", &*scale, 0.1f);
    }

    // TODO: camera controls
    ImGui::End();
}
