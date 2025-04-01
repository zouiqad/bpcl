#pragma once

#include "Shader.h"
#include "core/Types.h"
#include <string>
#include <vector>

#include "core/Drawable.h"

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh : public Drawable {
public:
    Mesh() = default;

    virtual ~Mesh() = default;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void draw(Shader &shader) const;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    void setup();
    void estimateNormals();
};

