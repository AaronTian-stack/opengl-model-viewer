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
    float d = max(dot(normalize(normal), normalize(light)), 0);
    vec3 grad = vec3(0.5) + vec3(0.5) * cos(6.28 * (vec3(2, 1, 0) * d + vec3(0.5, 0.2, 0.25)) + time * 3.0);
    FragColor = vec4(mix(texColor.rgb, grad, 0.2), 1.0);
}