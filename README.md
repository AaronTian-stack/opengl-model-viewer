# OpenGL Model Viewer
A 3D model viewer written in C++ that renders `.obj` files using OpenGL.

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

https://github.com/AaronTian-stack/opengl-model-viewer/assets/84607804/6abf0c46-8ba4-4e96-8ccb-f5b8738f8b19

<table>
  <tr>
    <td valign="center"> <img width="1136" alt="oshi" src="https://github.com/AaronTian-stack/opengl-model-viewer/assets/84607804/a869b98b-30f8-47b4-9d9b-1d1ae0646086"> </td>
    <td valign="center"> <img width="1136" alt="preview" src="https://github.com/AaronTian-stack/opengl-model-viewer/assets/84607804/322d2d3e-1615-41c7-8504-17d649190e3e"> </td>
    <td valign="center"> <img width="1136" alt="oshi_squash" src="https://github.com/AaronTian-stack/opengl-model-viewer/assets/84607804/6aecdeb5-e630-4633-b0b6-b2a235612727"> <p align="center"> <sub>squish</sub> </p> </td>
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
