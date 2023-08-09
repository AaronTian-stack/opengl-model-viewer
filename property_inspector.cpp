//
// Created by Aaron Tian on 8/5/23.
//

#include "property_inspector.h"
#include "window.h"
#include "camera.h"

#include "imgui/imgui.h"
#include "drawable_model.h"

void PropertyInspector::render(Window windowObj, Camera& camera, DrawableModel& model) {
    bool info = false;
    ImGui::SetNextWindowPos(ImVec2(0, 18));
    auto flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;

    ImGui::Begin("Model Viewer", nullptr, flags);

    ImGui::Text("Press ~ to toggle camera mode\n(Orbit / First Person)");

    ImGui::Checkbox("Hide Reticle", &hideReticle);

    if (ImGui::Checkbox("Wireframe", &wireframe))
    {
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }

    ImGui::SliderFloat("FOV", &camera.Zoom, 5.0f, 90.0f);

    if (ImGui::Button("Reset Camera"))
    {
        camera.Reset(glm::vec3(0.0f, 0.0f, 1.0f));
    }

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::MenuItem("Quit"))
        {
            glfwSetWindowShouldClose(windowObj.window, true);
        }
        if (ImGui::MenuItem("Model Info")) {
            info = true;
        }
        // dirty hack to get the menu to the right
        ImGui::SameLine(ImGui::GetWindowWidth() - 126);
        ImGui::Text("Aaron Tian 2023");
        ImGui::EndMainMenuBar();
    }

    if (info)
    {
        ImGui::OpenPopup("popup");
    }

    if (ImGui::BeginPopup("popup"))
    {
        ImGui::Text("Meshes: %d", model.mesh_count);
        ImGui::Text("Vertex Count: %d", model.vertex_count);
        ImGui::Text("Material Count: %d", model.material_count);
        ImGui::EndPopup();
    }

    if (ImGui::CollapsingHeader("Model Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat3("Position", &*position, 0.05f);
        ImGui::DragFloat3("Rotation", &*rotation, 0.1f);
        ImGui::DragFloat3("Scale", &*scale, 0.1f);
        ImGui::Checkbox("Turntable", &turntable);
    }

    ImGui::End();
}
