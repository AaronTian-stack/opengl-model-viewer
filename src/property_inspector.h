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

    bool wireframe;
    bool hideReticle = true;
    bool turntable;

    void render(Window windowObj, Camera& camera, DrawableModel& model);

};


#endif //OPENGL_MODEL_VIEWER_IMGUI_INSPECTOR_H
