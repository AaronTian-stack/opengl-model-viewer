//
// Created by Aaron Tian on 8/5/23.
//

#ifndef OPENGL_MODEL_VIEWER_IMGUI_INSPECTOR_H
#define OPENGL_MODEL_VIEWER_IMGUI_INSPECTOR_H

#include "window.h"
#include "imgui/imgui.h"
#include "camera.h"
#include "drawable_model.h"

struct PropertyInspector {

    float position[3] = {0, 0, 0};
    float rotation[3] = {0, 0, 0};
    float scale[3] = {1, 1, 1};

    float background_color[3] = {0.2f, 0.3f, 0.3f};

    bool wireframe = false;
    bool hideReticle = true;
    bool turntable = false;

    int m_current = 0;
    int s_current = 0;

    void render(Window windowObj, Camera &camera, std::vector<DrawableModel*> &models);
};


#endif //OPENGL_MODEL_VIEWER_IMGUI_INSPECTOR_H
