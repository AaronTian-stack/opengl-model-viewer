#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "src/frame_counter.h"
#include "src/shader.h"
#include "src/window.h"
#include "src/camera.h"
#include "src/property_inspector.h"
#include "src/drawable_mesh.h"
#include "src/primitives.h"
#include "src/drawable_model.h"
#include "src/interpolation.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void toggleCursor(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);

Window windowObj(1024, 768,
                 framebuffer_size_callback,
                 mouse_callback,
                 scroll_callback,
                 toggleCursor);
Camera camera(glm::vec3(0.0f, 0.0f, 1.0f));
FrameCounter frameCounter;
bool fpsMode;

const float reticleSizeMax = 0.01f;
float reticleSizeTarget = reticleSizeMax;
float reticleSize;

int main()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(windowObj.window, true);
    ImGui_ImplOpenGL3_Init();

    Shader basicShader("shaders/basic.vert", "shaders/basic.frag");
    Shader texShader("shaders/tex.vert", "shaders/tex.frag");

    objl::Loader loader;
    loader.LoadFile("resources/ball.obj");
    DrawableMesh ball(GL_STATIC_DRAW, loader.LoadedMeshes[0]);

    DrawableModel drawableModel(GL_STATIC_DRAW,
                                "resources/kind/kind.obj", "resources/kind/textures/");

    //DrawableModel drawableModel(GL_STATIC_DRAW,
    //                            "resources/oshi/oshi.obj", "resources/oshi/textures/");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    PropertyInspector propertyInspector;

    while (!glfwWindowShouldClose(windowObj.window))
    {
        glfwSetWindowTitle(windowObj.window, ("OpenGL Model Viewer | FPS: " + std::to_string(frameCounter.fps)).c_str());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        processInput(windowObj.window);

        propertyInspector.render(windowObj, camera, drawableModel);

        camera.Update(frameCounter.deltaTime);

        frameCounter.update(false);

        auto color = propertyInspector.background_color;
        glClearColor(color[0], color[1], color[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        reticleSize = Interpolation::Linear(reticleSize, reticleSizeTarget, 0.1f);

        glm::mat4 model = glm::mat4(1.0f);
        auto position = propertyInspector.position;
        model = glm::translate(model, glm::vec3(position[0], position[1], position[2]));
        auto rotation = propertyInspector.rotation;
        model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
        if (propertyInspector.turntable)
            rotation[1] += frameCounter.deltaTime * 10.0f;
        rotation[1] = std::fmodf(rotation[1], 360.0f);
        model = glm::rotate(model, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
        auto scale = propertyInspector.scale;
        model = glm::scale(model, glm::vec3(scale[0], scale[1], scale[2]));

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), windowObj.getAspectRatio(), 0.1f, 100.0f);

        texShader.use();
        texShader.setMat4("model", model);
        texShader.setMat4("view", camera.GetViewMatrix(!fpsMode));
        texShader.setMat4("projection", projection);
        const glm::vec3 camPos = fpsMode ? camera.Position : camera.OrbitPosition;
        texShader.setVec3("camPos", camPos);
        drawableModel.Draw();

        basicShader.use();
        basicShader.setMat4("view", camera.GetViewMatrix(!fpsMode));
        basicShader.setMat4("projection", projection);
        model = glm::mat4(1.0f);
        model = glm::translate(model, camera.TargetSmooth);

        float factor = propertyInspector.hideReticle ? 0 : 1;
        model = glm::scale(model, glm::vec3(reticleSize * factor));
        basicShader.setVec4("color", 1, 0, 0, 1.0f);
        basicShader.setMat4("model", model);
        ball.Draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(windowObj.window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

bool firstMouse = true;

void focus(GLFWwindow* window)
{
    reticleSizeTarget = 0;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void unfocus(GLFWwindow* window)
{
    reticleSizeTarget = reticleSizeMax;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    firstMouse = true;
}

void toggleCursor(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
        fpsMode = !fpsMode;
        if (fpsMode)
            focus(window);
        else
            unfocus(window);
    }
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    ImGuiIO& io = ImGui::GetIO();
    if (!fpsMode && !io.WantCaptureMouse)
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2))
            focus(window);
        else if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
            unfocus(window);
    }

    if (fpsMode)
    {
        float dt = frameCounter.deltaTime;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            dt *= 2.5f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, dt);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, dt);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, dt);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, dt);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            camera.ProcessKeyboard(DOWN, dt);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            camera.ProcessKeyboard(UP, dt);
    }
}

float lastX, lastY;
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    auto pan = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2);

    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        camera.ProcessMouseMovement(xoffset, yoffset, !fpsMode, pan);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset, !fpsMode);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
};
