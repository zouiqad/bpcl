#version 330 core

in vec3 vFragPos;       // Fragment position in world space
in vec3 vColor;
in vec3 vNormal;        // Normal vector in world space
in vec2 vTexCoord;      // Texture coordinates

uniform sampler2D uTexture;  // Diffuse texture
uniform bool uHasTexture; // To check if model has texture

out vec4 FragColor;

void main()
{
    vec3 norm = normalize(vNormal);

    // If model doesnt have texture use color
    vec3 baseColor = uHasTexture ? texture(uTexture, vTexCoord).rgb : vColor;

    FragColor = vec4(baseColor, 1.0);
}