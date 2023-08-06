//
// Created by Aaron Tian on 8/5/23.
//

#ifndef OPENGL_MODEL_VIEWER_IMGUI_INSPECTOR_H
#define OPENGL_MODEL_VIEWER_IMGUI_INSPECTOR_H

#include "window.h"

struct PropertyInspector {

    float position[3] = {0, 0, 0};
    float rotation[3] = {0, 0, 0};
    float scale[3] = {1, 1, 1};

    void render(Window windowObj);

};


#endif //OPENGL_MODEL_VIEWER_IMGUI_INSPECTOR_H
