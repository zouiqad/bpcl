// Vertex Shader
#version 330 core

layout (location = 0) in vec3 aPosition; // Vertex position
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;   // Vertex normal
layout (location = 3) in vec2 aTexCoord; // Texture coordinates

uniform mat4 uModel;      // Model matrix
uniform mat4 uView;       // View matrix
uniform mat4 uProj;       // Projection matrix

out vec3 vFragPos;       // Fragment position in world space
out vec3 vColor;
out vec3 vNormal;        // Normal vector in world space
out vec2 vTexCoord;      // Pass texture coordinates to fragment shader

void main()
{
    vFragPos = vec3(uModel * vec4(aPosition, 1.0));
    vNormal = aNormal;
    vTexCoord = aTexCoord;
    vColor = aColor;

    gl_Position = uProj * uView * vec4(vFragPos, 1.0);
}
