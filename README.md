# OpenGL Model Viewer
A 3D model viewer written in C++ that renders .obj files using OpenGL.

## Features
* Model loading from `.obj` files
* Smooth orbital camera
* ImGui control interface
    * Model translation, rotation, scale
        * Model turntable animation
    * Camera controls (aiming reticle, FOV)
    * Background color
    * Wireframe mode

## Video / Screenshots

https://github.com/AaronTian-stack/opengl-model-viewer/assets/84607804/f7866b1e-c228-41c0-bba3-767dffbf1c9d

<table>
  <tr>
    <td valign="center"><img width="1136" alt="oshi" src="https://github.com/AaronTian-stack/opengl-model-viewer/assets/84607804/4ef46a4a-2b7f-4dd2-836c-218f1259a221"></td>
    <td valign="center"><img width="1136" alt="preview2" src="https://github.com/AaronTian-stack/opengl-model-viewer/assets/84607804/4fa93e69-b3cd-40f7-b43d-35b2526a5149"></td>
    <td valign="center"><img width="1136" alt="oshi_squash" src="https://github.com/AaronTian-stack/opengl-model-viewer/assets/84607804/533c0cb2-a65e-4730-b6c3-bdbdca3717c0"> <p align="center"> <sub>squish</sub> </p></td>
  </tr>
 </table>

## Credits

| Models                 | Link | License |
|------------------------| --- | --- |
| Spirit Blossom Kindred | [Sketchfab](https://skfb.ly/6UFIA) | CC Attribution |
| Oshi No Ko             | [Sketchfab](https://skfb.ly/oHxLA) | CC Attribution |

The other bundled models (`cubt.obj` and `plane.obj`) are debug models created by myself.

`shader.cpp` is taken from the [LearnOpenGL](https://learnopengl.com/) tutorial. 

`camera.cpp` is a heavily modified version of the camera class from the same tutorial.

## Dependencies

| Library    | Link                                         |
|------------|----------------------------------------------|
| GLFW       | [Website](https://www.glfw.org/)             |
| glad       | [Website](https://glad.dav1d.de/)            |
| GLM        | [Github](https://github.com/g-truc/glm)      |
| OBJ-Loader | [Github](https://github.com/Bly7/OBJ-Loader) |
| ImGui      | [Github](https://github.com/ocornut/imgui)   |

This project uses macOS OpenGL 4.1

## Limitations
* Only supports diffuse materials/textures (no lighting)
