//
// Created by Aaron Tian on 8/7/23.
//

#ifndef OPENGL_MODEL_VIEWER_DRAWABLE_MODEL_H
#define OPENGL_MODEL_VIEWER_DRAWABLE_MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "drawable_mesh.h"

class DrawableModel {

public:
    std::vector<DrawableMesh> meshes;
    unsigned int mesh_count;
    unsigned int vertex_count;
    unsigned int material_count;
    DrawableModel(GLuint drawMode, const char * objPath, const char * texturesFolder = nullptr);
    void Draw();
};


#endif //OPENGL_MODEL_VIEWER_DRAWABLE_MODEL_H
