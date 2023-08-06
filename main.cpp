#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "frame_counter.h"
#include "mesh.h"
#include "shader.h"
#include "window.h"
#include "camera.h"
#include "property_inspector.h"

using namespace std;

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
bool cursorLocked;

int main()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(windowObj.window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

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
            // positions                        //colors                                    // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,    // top left
    };
    unsigned int indices_rect[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    //Mesh rectBasic(GL_STATIC_COPY, vertices_rect_basic, sizeof(vertices_rect_basic),
    //               indices_rect, sizeof(indices_rect));

    Mesh rect(GL_STATIC_COPY, vertices_rect_tex, sizeof(vertices_rect_tex),
              indices_rect, sizeof(indices_rect), true, "resources/sacrasliceicon.png");

    Mesh rect2(GL_STATIC_COPY, vertices_rect_tex, sizeof(vertices_rect_tex),
              indices_rect, sizeof(indices_rect), true, "resources/sacrasliceicon.png");

    float vertices_tri[] = {
    // positions TRIANGLE           // colors
    -0.8f, -0.8f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,
     0.8f, -0.8f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f,
     0.0f,  0.8f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,
    };
    unsigned int indices_tri[] = {
        0, 1, 2,   // first triangle
    };

    //Mesh tri(GL_STATIC_COPY, vertices_tri, sizeof(vertices_tri), indices_tri, sizeof(indices_tri), true);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    PropertyInspector propertyInspector;

    while (!glfwWindowShouldClose(windowObj.window))
    {
        glfwSetWindowTitle(windowObj.window, ("OpenGL Mesh Viewer | FPS: " + to_string(frameCounter.fps)).c_str());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        propertyInspector.render(windowObj);

        processInput(windowObj.window);
        frameCounter.update(false);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //colorShader.use();
        //tri.draw();

        glm::mat4 model = glm::mat4(1.0f);
        auto position = propertyInspector.position;
        model = glm::translate(model, glm::vec3(position[0], position[1], position[2]));
        auto rotation = propertyInspector.rotation;
        model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
        auto scale = propertyInspector.scale;
        model = glm::scale(model, glm::vec3(scale[0], scale[1], scale[2]));

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), windowObj.getAspectRatio(), 0.1f, 100.0f);

        texColorShader.use();
        texColorShader.setMat4("model", model);
        texColorShader.setMat4("view", camera.GetViewMatrix());
        texColorShader.setMat4("projection", projection);
        rect.draw();

        //basicShader.use();
        //basicShader.setVec4("color", color[0], color[1], color[2], color[3]);
        //rectBasic.draw();

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

void toggleCursor(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
        cursorLocked = !cursorLocked;
        if (cursorLocked)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, frameCounter.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, frameCounter.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, frameCounter.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, frameCounter.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, frameCounter.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, frameCounter.deltaTime);
}

bool firstMouse = true;
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

    if (cursorLocked)
        camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
};
