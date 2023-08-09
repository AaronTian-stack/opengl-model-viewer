//
// Created by Aaron Tian on 8/7/23.
//

#include "primitives.h"

DrawableMesh Primitives::GenerateCube()
{
    float vertices[] = {
            // Front face
            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            // Back face
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f
    };

    unsigned int indices[] = {
            0, 1, 2,  // Front face
            2, 3, 0,
            1, 5, 6,  // Right face
            6, 2, 1,
            7, 6, 5,  // Back face
            5, 4, 7,
            4, 0, 3,  // Left face
            3, 7, 4,
            4, 5, 1,  // Top face
            1, 0, 4,
            3, 2, 6,  // Bottom face
            6, 7, 3
    };

    return DrawableMesh(GL_STATIC_COPY, vertices, sizeof(vertices), indices, sizeof(indices));

}