#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Model
{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

public:
	float *vertices;
	unsigned int *indices;

	Model(GLuint drawMode, float vertices[], unsigned int vert_count, unsigned int indices[], unsigned int ind_count) 
	: Model(drawMode, vertices, vert_count, indices, ind_count, false){};
	
	Model(GLuint drawMode, float vertices[], unsigned int vert_count, unsigned int indices[], unsigned int ind_count, bool color);
	
	void draw();
};
