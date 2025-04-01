#version 330

layout (location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 uProj;
uniform mat4 uView;

void main() {
    texCoords = aPos;
    gl_Position = uProj * uView * vec4(aPos, 1.0);
}