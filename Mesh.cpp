#include "Mesh.h"

#include <iostream>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

/**
 * @brief Construct a new Mesh:: Mesh object with vertex and index data.
*/
Mesh::Mesh(GLuint drawMode, float *vertices, unsigned int vert_count, unsigned int *indices, unsigned int ind_count, bool color, const char *texture_path)
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
	const unsigned int v_attribute = 0;
    const unsigned int c_attribute = 1;
    const unsigned int t_attribute = 2;
	// tell OpenGL how to interpret vertex array (for the vertex shader). send vertices of format float3 (size arg)

    if (texture_path != nullptr)
    {
        std::cout << "Texture Loaded" << std::endl;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // texture wrapping in the s and t axis (x and y)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // min mag filers
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        unsigned char *data = stbi_load(texture_path, &width, &height, &nrChannels, 0);
        if (data)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    int vertex_color_stride = 6;
    if (color)
	{
        if (texture_path != nullptr)
        {
            vertex_color_stride = 8;
            // size 2 for xy texture coordinates
            // move 8 each times stride, start at 6 since position and color are 6 floats
            glVertexAttribPointer(t_attribute, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(t_attribute);
        }

        glVertexAttribPointer(c_attribute, 3, GL_FLOAT, GL_FALSE, vertex_color_stride * sizeof(float), (void*)(3 * sizeof(float)));
        // for color attribute in the shader
        glEnableVertexAttribArray(c_attribute);
	}
    else
	{
		// assumes tightly packed 0 index (offset) 3 indexes per triangle (stride). vertex attribute 0 (first arg)
		vertex_color_stride = 3;
        if (texture_path != nullptr)
        {
            // move 5 each times stride, start at 3
            glVertexAttribPointer(t_attribute, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(t_attribute);
        }
	}

	// enable vertex attribute (tell which location we send our data to in the vertex shader)
    // assuming this is 0 it is the aPos attribute
    glVertexAttribPointer(v_attribute, 3, GL_FLOAT, GL_FALSE, vertex_color_stride * sizeof(float), (void*)0);
	glEnableVertexAttribArray(v_attribute);
}

void Mesh::draw() const
{
    glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO); // note: unbind by using 0
	glDrawElements(GL_TRIANGLES, sizeof(vertices), GL_UNSIGNED_INT, 0);
}