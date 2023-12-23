#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 normal;
in vec3 light;

uniform sampler2D ourTexture;
uniform float time;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);

    float alpha = abs(sin(time));

    float dot = dot(normalize(normal), normalize(light));
    const vec3 a  = vec3(0.5);
    const vec3 b = vec3(0.5);
    const vec3 c = vec3(2, 1, 0);
    const vec3 d = vec3(0.5, 0.2, 0.25);

    FragColor = vec4(a + b * cos(6.28 * (c * dot + d) + time), 1.0);
}