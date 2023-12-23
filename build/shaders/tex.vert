#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 camPos;

out vec2 TexCoord; // output texture coordinates to the fragment shader
out vec3 normal;
out vec3 light;

void main()
{
    vec4 modelt = model * vec4(aPos, 1.0);
    gl_Position = projection * view * modelt;
    TexCoord = aTexCoord;
    normal = transpose(inverse(mat3(model))) * aNor;
    light = camPos - modelt.xyz;
}