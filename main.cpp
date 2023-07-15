#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "FrameCounter.h"
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

Window window(800, 600, framebuffer_size_callback);

int main()
{

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    FrameCounter frameCounter;
    Shader colorShader("shaders/color.vert", "shaders/color.frag");
    Shader basicShader("shaders/basic.vert", "shaders/basic.frag");
    Shader texColorShader("shaders/tex_color.vert", "shaders/tex_color.frag");

    float vertices_rect_basic[] = {
    // positions RECTANGLE
     0.7f,  0.7f, 0.0f,
     0.7f, -0.3f, 0.0f,
    -0.3f, -0.3f, 0.0f,
    -0.3f,  0.7f, 0.0f,
    };

    float vertices_rect_tex[] = {
            // positions                        // colors                       // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left
    };
    unsigned int indices_rect[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    Mesh rectBasic(GL_STATIC_COPY, vertices_rect_basic, sizeof(vertices_rect_basic),
                   indices_rect, sizeof(indices_rect));

    Mesh rect(GL_STATIC_COPY, vertices_rect_tex, sizeof(vertices_rect_tex),
              indices_rect, sizeof(indices_rect), true, "resources/brick.jpg");

    float vertices_tri[] = {
    // positions TRIANGLE           // colors
    -0.8f, -0.8f, 0.0f,     1.0f, 0.0f, 0.0f,
     0.8f, -0.8f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.0f,  0.8f, 0.0f,     0.0f, 0.0f, 1.0f,
    };
    unsigned int indices_tri[] = {
        0, 1, 2,   // first triangle
    };

    Mesh tri(GL_STATIC_COPY, vertices_tri, sizeof(vertices_tri), indices_tri, sizeof(indices_tri), true);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float color[4] = { 0, 0, 0, 0.5f};

    while (!glfwWindowShouldClose(window.window))
    {
        glfwSetWindowTitle(window.window, ("OpenGL Mesh Viewer | FPS: " + to_string(frameCounter.fps)).c_str());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool info = false;
        ImGui::Begin("Mesh Viewer", nullptr);
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::MenuItem("Quit"))
            {
                glfwSetWindowShouldClose(window.window, true);
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

        if (ImGui::CollapsingHeader("Color"))
        {
            ImGui::ColorPicker4("Color", color);
        }
        
        ImGui::End();

        processInput(window.window);
        frameCounter.update(false);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        colorShader.use();
        tri.draw();

        texColorShader.use();
        rect.draw();

        basicShader.use();
        basicShader.setVec4("color", color[0], color[1], color[2], color[3]);
        rectBasic.draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
};
