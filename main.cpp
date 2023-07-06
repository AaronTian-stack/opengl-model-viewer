#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "FrameCounter.h"
#include "Model.h"
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

    float vertices[] = {
    // positions RECTANGLE           // colors
     0.5f,  0.5f, 0.0f,     //1.0f, 0.0f, 0.0f,   // top right
     0.5f, -0.5f, 0.0f,     //0.0f, 1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,     //0.0f, 0.0f, 1.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,     //1.0f, 0.0f, 0.0f,   // top left
    };
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    Model rect(GL_STATIC_COPY, vertices, sizeof(vertices), indices, sizeof(indices));

    float vertices1[] = {
    // positions TRIANGLE           // colors
    -0.8f, -0.8f, 0.0f,     1.0f, 0.0f, 0.0f,
     0.8f, -0.8f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.0f,  0.8f, 0.0f,     0.0f, 0.0f, 1.0f,
};  
    unsigned int indices1[] = {
        0, 1, 2,   // first triangle
    };

    Model tri(GL_STATIC_COPY, vertices1, sizeof(vertices1), indices1, sizeof(indices1), true);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window.window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool info = false;
        ImGui::Begin("Model Viewer", nullptr, ImGuiWindowFlags_AlwaysUseWindowPadding);
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::MenuItem("Quit")) {
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

        ImGui::Text("FPS: %0.0lf", ImGui::GetIO().Framerate);
        ImGui::End();

        processInput(window.window);
        frameCounter.update(false);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        colorShader.use();
        tri.draw();

        basicShader.use();
        basicShader.setVec4("color", 1.0f, 0.0f, 0.0f, 0.5f);
        rect.draw();

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
