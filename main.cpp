#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
        processInput(window.window);
        frameCounter.update();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        colorShader.use();
        tri.draw();

        basicShader.use();
        basicShader.setVec4("color", 1.0f, 0.0f, 0.0f, 0.5f);
        rect.draw();

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }

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
