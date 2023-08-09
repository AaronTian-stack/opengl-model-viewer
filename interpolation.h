//
// Created by Aaron Tian on 8/7/23.
//

#ifndef OPENGL_MODEL_VIEWER_INTERPOLATION_H
#define OPENGL_MODEL_VIEWER_INTERPOLATION_H

class Interpolation
{
public:
    static float Linear(float start, float end, float a)
    {
        return start + (end - start) * a;
    }
};

#endif //OPENGL_MODEL_VIEWER_INTERPOLATION_H
