#version 330 core

in vec3 vFragPos;    // Fragment position in world space
in vec3 vColor;      // Vertex color
in vec3 vNormal;     // Normal vector in world space
in vec2 vTexCoord;   // Texture coordinates

uniform sampler2D uTexture;   // Diffuse texture
uniform bool uHasTexture;     // Does the model have a texture?

// Directional light uniforms for "global" illumination (e.g. the sun)
uniform vec3 uSunDirection;   // Direction of the sun (normalized)
uniform vec3 uSunColor;       // Color/intensity of the sun

// Global ambient light
uniform vec3 uAmbientColor;

// Camera uniform for specular calculations
uniform vec3 uViewPos;

uniform float uSpecularStrength; // Specular intensity factor
uniform float uSpecularPower;    // Shininess (specular exponent)

out vec4 FragColor;

void main()
{
    // Base color comes from texture if available, otherwise from vertex color.
    vec3 baseColor = uHasTexture ? texture(uTexture, vTexCoord).rgb : vColor;

    // --- Ambient Lighting (global illumination) ---
    vec3 ambient = uAmbientColor * baseColor;

    // --- Diffuse Lighting using directional sun light ---
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uSunDirection); // Directional light
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uSunColor * baseColor;

    // --- Specular Lighting (Blinn-Phong) ---
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfDir), 0.0), uSpecularPower);
    vec3 specular = uSpecularStrength * spec * uSunColor;

    // Since this is a directional light (sun), no attenuation is used.
    vec3 finalColor = ambient + diffuse + specular;
    FragColor = vec4(finalColor, 1.0);
}
