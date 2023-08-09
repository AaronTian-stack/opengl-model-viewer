#include <iostream>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "drawable_mesh.h"
#include "obj/OBJ_Loader.h"

/**
 * @brief Construct a new Mesh object with vertex and index data.
*/
DrawableMesh::DrawableMesh(GLuint drawMode, float *vertices, unsigned int vert_count, unsigned int *indices, unsigned int ind_count, bool color, const char *texture_path)
{
    this->vert_count = vert_count;
    this->ind_count = ind_count;

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
        LoadTexture(texture_path);
    }

    // stride for just vertex on its own
    int vertex_color_stride = 3;

    if (color)
	{
        // vertex + color = 3 + 4 = 7
        vertex_color_stride = 7;
        if (texture_path != nullptr)
        {
            vertex_color_stride += 2;
            // size 2 for xy texture coordinates
            // move 8 each times stride, start at 6 since position and color are 6 floats
            glVertexAttribPointer(t_attribute, 2, GL_FLOAT, GL_FALSE, vertex_color_stride * sizeof(float), (void*)(7 * sizeof(float)));
            glEnableVertexAttribArray(t_attribute);
        }

        // rgba
        glVertexAttribPointer(c_attribute, 4, GL_FLOAT, GL_FALSE, vertex_color_stride * sizeof(float), (void*)(3 * sizeof(float)));
        // for color attribute in the shader
        glEnableVertexAttribArray(c_attribute);
	}
    else
	{
		// assumes tightly packed 0 index (offset) 3 indexes per triangle (stride). vertex attribute 0 (first arg)
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

DrawableMesh::DrawableMesh(GLuint drawMode, objl::Mesh mesh, const char * texturesFolder)
{
    // unfortunate code duplication :(

    // position (vec3), normal (vec3), tex coord (vec2)
    this->vert_count = mesh.Vertices.size();
    // index number (unsigned int)
    this->ind_count = mesh.Indices.size();

    std::cout << mesh.Vertices.at(0).TextureCoordinate.X << std::endl;

    glGenVertexArrays(1, &VAO); // create vertex array object
    glBindVertexArray(VAO); // bind vertex array object.

    // ALWAYS BIND THE VAO FIRST

    glGenBuffers(1, &VBO); // create vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind vertex buffer
    glBufferData(GL_ARRAY_BUFFER, vert_count * sizeof(objl::Vertex), &mesh.Vertices[0], drawMode); // send vertex data to buffer

    glGenBuffers(1, &EBO); // create index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // bind index buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_count * sizeof(unsigned int), &mesh.Indices[0], drawMode); // send index data to buffer

    const unsigned int v_attribute = 0;
    const unsigned int t_attribute = 1;

    auto file = mesh.MeshMaterial.map_Kd;
    // for now only use the diffuse texture. since the setup can only support one texture
    std::cout << "Mesh: " << mesh.MeshName << " Material Texture: " << file << std::endl;

    if (texturesFolder != nullptr)
    {
        if (!file.empty())
        {
            auto true_path = std::string(texturesFolder) + file;
            // Convert std::string to char array
            char charArray[true_path.size() + 1];
            strcpy(charArray, true_path.c_str());

            std::cout << "True Path: " << charArray << std::endl;
            LoadTexture(charArray);
        }
        else
        {
            std::cout << "No texture specified" << std::endl;
            LoadTexture("resources/black.png");
        }
    }
    else
    {
        std::cout << "No texture folder specified" << std::endl;
        LoadTexture("resources/wall.png");
    }

    glVertexAttribPointer(t_attribute, 2, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (void*)offsetof(objl::Vertex, TextureCoordinate));
    glEnableVertexAttribArray(t_attribute);

    glVertexAttribPointer(v_attribute, 3, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (void*)0);
    glEnableVertexAttribArray(v_attribute);
}

void DrawableMesh::Draw() const
{
    glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO); // note: unbind by using 0
	glDrawElements(GL_TRIANGLES, ind_count, GL_UNSIGNED_INT, 0);
}

void DrawableMesh::LoadTexture(const char *texture_path) {
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // texture wrapping in the s and t axis (x and y)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // min mag filers
    // GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(texture_path, &width, &height, &nrChannels, 0);
    if (data)
    {
        std::cout << "Texture Loaded Successfully" << std::endl;
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
