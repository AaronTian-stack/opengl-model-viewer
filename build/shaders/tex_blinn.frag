#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 normal;
in vec3 light;

uniform sampler2D ourTexture;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    if(texColor.a < 0.1)
        discard;
    float dot = dot(normalize(normal), normalize(light));
    float diffuse = clamp(dot, 0.0, 1.0) + 0.2;
    // specular
    float spec = max(pow(dot, 6000), 0);
    vec3 specular = vec3(247, 250, 202) / 255 * spec;

    FragColor = vec4(texColor.rgb * diffuse + specular, 1.0);
}