#include "Skybox.h"

#include <iostream>
#include <stb_image.h>

// positions
float skyboxVertices[] = {
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
};

Skybox::Skybox (const std::vector<std::string>& texPaths) {
    setup ();
    loadCubemap (texPaths);
}

void Skybox::setup () {
    glGenVertexArrays (1, &vao);
    glGenBuffers (1, &vbo);

    glBindVertexArray (vao);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices,
        GL_STATIC_DRAW);

    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float),
        (void*)0);

    glBindVertexArray (0);
}

void Skybox::loadCubemap (const std::vector<std::string>& texPaths) {
    glActiveTexture (GL_TEXTURE0);
    glGenTextures (1, &cubemapTexture);
    glBindTexture (GL_TEXTURE_CUBE_MAP, cubemapTexture);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < texPaths.size (); i++) {
        unsigned char* data = stbi_load (texPaths[i].c_str (), &width, &height,
            &nrChannels, 0);
        if (data) {
            glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free (data);
        } else {
            std::cerr << "Cubemap tex failed to load at path: " << texPaths[i]
                <<
                std::endl;
            stbi_image_free (data);
        }
    }

    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_CUBE_MAP, 0);
}

void Skybox::draw (Shader& skyboxShader,
    const glm::mat4& view,
    const glm::mat4& projection) {
    glDepthMask (GL_FALSE);

    skyboxShader.use ();

    glm::mat4 viewNoTranslation = glm::mat4 (glm::mat3 (view));

    skyboxShader.setUniform ("u_view", viewNoTranslation);
    skyboxShader.setUniform ("u_projection", projection);
    skyboxShader.setUniform ("skybox", 0);

    glBindVertexArray (vao);
    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays (GL_TRIANGLES, 0, 36);
    glBindVertexArray (0);

    glDepthMask (GL_TRUE);

    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_CUBE_MAP, 0);
}

Skybox::~Skybox () {
    glDeleteVertexArrays (1, &vao);
    glDeleteBuffers (1, &vbo);
    glDeleteTextures (1, &cubemapTexture);
}
