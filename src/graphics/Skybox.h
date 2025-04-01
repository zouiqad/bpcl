#pragma once


#include "Shader.h"
#include <vector>
#include <string>


class Skybox {
public:
    Skybox (const std::vector<std::string>& texPaths);

    ~Skybox ();

    void draw (Shader& skyboxShader,
        const glm::mat4& view,
        const glm::mat4& projection);

private:
    GLuint cubemapTexture;
    GLuint vao, vbo;

    void loadCubemap (const std::vector<std::string>& faces);

    void setup ();
};

