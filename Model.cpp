#include "Model.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

/**
 * @brief Construct a new Model:: Model object with vertex and index data.
*/
Model::Model(GLuint drawMode, float vertices[], unsigned int vert_count, unsigned int indices[], unsigned int ind_count, bool color)
{
	this->vertices = vertices;
	this->indices = indices;

	// A VAO is a container for a VBO. Unique objects should have their own VAO (normally 1 to 1) but they can share VBOs.

	glGenVertexArrays(1, &VAO); // create vertex array object (each unique object should have its own VAO)
	glBindVertexArray(VAO); // bind vertex array object.

	// ALWAYS BIND THE VAO FIRST

	glGenBuffers(1, &VBO); // create vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vert_count * sizeof(float), vertices, drawMode); // send vertex data to buffer

	glGenBuffers(1, &EBO); // create index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_count * sizeof(float), indices, drawMode); // send index data to buffer

	// this is the layout (attribute = #) in the shader
	unsigned int v_attribute = 0;
	// tell OpenGL how to interpret vertex array (for the vertex shader). send vertices of format float3 (size arg)

	if (color)
	{
		glVertexAttribPointer(v_attribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	else 
	{
		// assumes tightly packed 0 index (offset) 3 indexes per triangle (stride). vertex attribute 0 (first arg)
		glVertexAttribPointer(v_attribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	}

	// enable vertex attribute (tell which location we send our data to in the vertex shader)
	glEnableVertexAttribArray(v_attribute);
}

void Model::draw()
{
	glBindVertexArray(VAO); // note: unbind by using 0
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}