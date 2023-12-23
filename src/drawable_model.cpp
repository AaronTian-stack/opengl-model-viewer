//
// Created by Aaron Tian on 8/7/23.
//

#include "obj/OBJ_Loader.h"
#include "drawable_model.h"

DrawableModel::DrawableModel(GLuint drawMode, const char * objPath, const char * texturesFolder)
{
    // load the model
    objl::Loader loader;
    if (loader.LoadFile(objPath))
    {
        this->mesh_count = loader.LoadedMeshes.size();
        this->vertex_count = loader.LoadedVertices.size();
        this->material_count = loader.LoadedMaterials.size();
        std::cout << "Number of Meshes in Model: " << loader.LoadedMeshes.size() << std::endl;
        // make drawable mesh for each
        for (const auto &mesh : loader.LoadedMeshes)
        {
            for (const auto &vert : mesh.Vertices)
            {
                const auto &v = vert.Position;
                avg_pos += glm::vec3(v.X, v.Y, v.Z);
            }
            this->meshes.emplace_back(drawMode, mesh, texturesFolder);
        }
        avg_pos /= this->vertex_count;
    }
    else
    {
        std::cout << "FAILED TO LOAD MODEL AT " << objPath << std::endl;
    }
}

void DrawableModel::Draw() {
    for (const auto& mesh : this->meshes)
    {
        mesh.Draw();
    }
}
