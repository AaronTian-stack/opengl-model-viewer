#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh
{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

    unsigned int texture;

public:
	float *vertices;
	unsigned int *indices;

    Mesh(GLuint drawMode,
                  float *vertices, unsigned int vert_count,
                  unsigned int *indices, unsigned int ind_count, const char *texture_path)
    : Mesh(drawMode, vertices, vert_count, indices, ind_count, false, texture_path){};
	
	Mesh(GLuint drawMode,
         float *vertices, unsigned int vert_count,
         unsigned int *indices, unsigned int ind_count,
         bool color = false, const char *texture_path = nullptr);
	
	void draw() const;
};
