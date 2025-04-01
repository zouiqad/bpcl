#pragma once

#include <iostream>

#include "Mesh.h"
#include <stb/stb_image.h>
#include <glm/ext/scalar_constants.hpp>


inline Mesh createTableMesh() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Helper that creates 6 faces (front, back, left, right, top, bottom) with appropriate normals and texture coordinates.
    auto addCuboid = [&](const glm::vec3& min, const glm::vec3& max) {
        // Keep track of the starting index for this cuboid.
        unsigned int baseIndex = vertices.size();

        // === FRONT FACE (facing +Z) ===
        // Order: bottom-left, top-left, top-right, bottom-right.
        vertices.push_back({ glm::vec3(min.x, min.y, max.z), glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(min.x, max.y, max.z), glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, max.z), glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, min.y, max.z), glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);

        // === BACK FACE (facing -Z) ===
        baseIndex = vertices.size();
        vertices.push_back({ glm::vec3(max.x, min.y, min.z), glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, min.z), glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(min.x, max.y, min.z), glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(min.x, min.y, min.z), glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);

        // === LEFT FACE (facing -X) ===
        baseIndex = vertices.size();
        vertices.push_back({ glm::vec3(min.x, min.y, min.z), glm::normalize(glm::vec3(-1.0f, 0.0f, 0.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(min.x, max.y, min.z), glm::normalize(glm::vec3(-1.0f, 0.0f, 0.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(min.x, max.y, max.z), glm::normalize(glm::vec3(-1.0f, 0.0f, 0.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(min.x, min.y, max.z), glm::normalize(glm::vec3(-1.0f, 0.0f, 0.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);

        // === RIGHT FACE (facing +X) ===
        baseIndex = vertices.size();
        vertices.push_back({ glm::vec3(max.x, min.y, max.z), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, max.z), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, min.z), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, min.y, min.z), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);

        // === TOP FACE (facing +Y) ===
        baseIndex = vertices.size();
        vertices.push_back({ glm::vec3(min.x, max.y, max.z), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(min.x, max.y, min.z), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, min.z), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, max.z), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);

        // === BOTTOM FACE (facing -Y) ===
        baseIndex = vertices.size();
        vertices.push_back({ glm::vec3(min.x, min.y, min.z), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(min.x, min.y, max.z), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, min.y, max.z), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, min.y, min.z), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);
    };

    // --- Table Top ---
    glm::vec3 tableTopMin(-1.0f, 1.0f, -0.6f);
    glm::vec3 tableTopMax( 1.0f, 1.1f,  0.6f);
    addCuboid(tableTopMin, tableTopMax);

    // --- Table Legs ---
    float legWidth  = 0.15f;  // width (and depth) of each leg
    float legHeight = 1.0f;   // height of the leg (from y = 0.0 to y = 1.0)
    float legInset  = 0.2f;   // inset from the table top’s edges

    // Front Left Leg (x: left side, z: front side)
    glm::vec3 legFLMin(-1.0f + legInset, 0.0f,  0.6f - legInset - legWidth);
    glm::vec3 legFLMax(-1.0f + legInset + legWidth, legHeight, 0.6f - legInset);
    addCuboid(legFLMin, legFLMax);

    // Front Right Leg (x: right side, z: front side)
    glm::vec3 legFRMin(1.0f - legInset - legWidth, 0.0f,  0.6f - legInset - legWidth);
    glm::vec3 legFRMax(1.0f - legInset, legHeight, 0.6f - legInset);
    addCuboid(legFRMin, legFRMax);

    // Back Left Leg (x: left side, z: back side)
    glm::vec3 legBLMin(-1.0f + legInset, 0.0f, -0.6f + legInset);
    glm::vec3 legBLMax(-1.0f + legInset + legWidth, legHeight, -0.6f + legInset + legWidth);
    addCuboid(legBLMin, legBLMax);

    // Back Right Leg (x: right side, z: back side)
    glm::vec3 legBRMin(1.0f - legInset - legWidth, 0.0f, -0.6f + legInset);
    glm::vec3 legBRMax(1.0f - legInset, legHeight, -0.6f + legInset + legWidth);
    addCuboid(legBRMin, legBRMax);

    return Mesh(vertices, indices, std::vector<Texture>{});
}


inline Mesh createSphereMesh(unsigned int X_SEGMENTS = 32, unsigned int Y_SEGMENTS = 16) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>());
            float yPos = std::cos(ySegment * glm::pi<float>());
            float zPos = std::sin(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>());

            Vertex vertex{};
            vertex.Position = glm::vec3(xPos, yPos, zPos);
            vertex.Normal   = glm::normalize(vertex.Position);
            vertex.TexCoords = glm::vec2(xSegment, ySegment);
            vertices.push_back(vertex);
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
        for (unsigned int x = 0; x < X_SEGMENTS; ++x) {
            unsigned int first = y * (X_SEGMENTS + 1) + x;
            unsigned int second = first + X_SEGMENTS + 1;
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    return Mesh(vertices, indices, std::vector<Texture>{});
}

inline unsigned int loadTexture (const char* path,
    const std::string& directory,
    bool gamma = false) {
    std::string filename = std::string (path);
    filename             = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures (1, &textureID);

    stbi_set_flip_vertically_on_load (true);

    int width, height, nrComponents;
    unsigned char* data = stbi_load (filename.c_str (), &width, &height,
        &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1) format = GL_RED;
        else if (nrComponents == 3) format = GL_RGB;
        else if (nrComponents == 4) format = GL_RGBA;

        glBindTexture (GL_TEXTURE_2D, textureID);
        glTexImage2D (GL_TEXTURE_2D, 0, format, width, height, 0, format,
            GL_UNSIGNED_BYTE, data);
        glGenerateMipmap (GL_TEXTURE_2D);

        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free (data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free (data);
    }

    return textureID;
}

inline Mesh createDeskLampMesh() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    auto addCuboid = [&](const glm::vec3& min, const glm::vec3& max) {

        unsigned int baseIndex = vertices.size();

        // === FRONT FACE (facing +Z) ===
        vertices.push_back({ glm::vec3(min.x, min.y, max.z), glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(min.x, max.y, max.z), glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, max.z), glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, min.y, max.z), glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);

        // === BACK FACE (facing -Z) ===
        baseIndex = vertices.size();
        vertices.push_back({ glm::vec3(max.x, min.y, min.z), glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, min.z), glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(min.x, max.y, min.z), glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(min.x, min.y, min.z), glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);

        // === LEFT FACE (facing -X) ===
        baseIndex = vertices.size();
        vertices.push_back({ glm::vec3(min.x, min.y, min.z), glm::normalize(glm::vec3(-1.0f, 0.0f, 0.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(min.x, max.y, min.z), glm::normalize(glm::vec3(-1.0f, 0.0f, 0.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(min.x, max.y, max.z), glm::normalize(glm::vec3(-1.0f, 0.0f, 0.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(min.x, min.y, max.z), glm::normalize(glm::vec3(-1.0f, 0.0f, 0.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);

        // === RIGHT FACE (facing +X) ===
        baseIndex = vertices.size();
        vertices.push_back({ glm::vec3(max.x, min.y, max.z), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, max.z), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, min.z), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, min.y, min.z), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);

        // === TOP FACE (facing +Y) ===
        baseIndex = vertices.size();
        vertices.push_back({ glm::vec3(min.x, max.y, max.z), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(min.x, max.y, min.z), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, min.z), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, max.y, max.z), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);

        // === BOTTOM FACE (facing -Y) ===
        baseIndex = vertices.size();
        vertices.push_back({ glm::vec3(min.x, min.y, min.z), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ glm::vec3(min.x, min.y, max.z), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec2(0.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, min.y, max.z), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ glm::vec3(max.x, min.y, min.z), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec2(1.0f, 0.0f) });
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 0);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);
    };

    // --- Desk Lamp Base ---
    glm::vec3 baseMin(-0.5f, 0.0f, -0.5f);
    glm::vec3 baseMax(0.5f, 0.2f, 0.5f);
    addCuboid(baseMin, baseMax);

    // --- Desk Lamp Stem ---
    glm::vec3 stemMin(-0.1f, 0.2f, -0.1f);
    glm::vec3 stemMax(0.1f, 2.2f, 0.1f);
    addCuboid(stemMin, stemMax);

    // --- Desk Lamp Head ---
    glm::vec3 headMin(-0.3f, 2.2f, -0.3f);
    glm::vec3 headMax(0.3f, 2.5f, 0.3f);
    addCuboid(headMin, headMax);

    return Mesh(vertices, indices, std::vector<Texture>{});
}


inline Model createTileModel(const std::string& texturePath, float tileSize)
{
    // Calculate half size for centering.
    float halfSize = tileSize / 2.0f;

    // Define 4 vertices for the quad.
    // Positions are on the XZ-plane (Y = 0).
    // Normals point upward (0, 1, 0).
    // Texture coordinates span the full texture [0,1] x [0,1].
    std::vector<Vertex> vertices = {
        // Position                          Normal             TexCoord
        { glm::vec3(-halfSize, 0.0f, -halfSize), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(-halfSize, 0.0f,  halfSize), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) },
        { glm::vec3( halfSize, 0.0f,  halfSize), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3( halfSize, 0.0f, -halfSize), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) }
    };

    // Define two triangles (using indices) that make up the quad.
    std::vector<unsigned int> indices = {
        0, 1, 2,  // first triangle
        0, 2, 3   // second triangle
    };

    // Prepare the texture vector.
    std::vector<Texture> textures;
    if (!texturePath.empty()) {
        Texture tileTexture;
        // Load the texture using your engine’s texture loader.
        // Here we assume texturePath is the complete path; if needed, you can pass a directory.
        tileTexture.id = loadTexture(texturePath.c_str(), "resources/textures");
        tileTexture.type = "texture_diffuse";  // Matches what your shader expects.
        tileTexture.path = texturePath;
        textures.push_back(tileTexture);
    }

    // Create a Mesh from the vertices, indices, and texture(s).
    Mesh tileMesh(vertices, indices, textures);

    // Construct and return a Model using the created mesh.
    // (Assumes Model has a constructor that takes a Mesh.)
    Model tileModel(tileMesh);
    return tileModel;
}


inline Mesh createGroundMesh(const std::string& texPath, float width = 100.0f, float depth = 100.0f) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Calculate half dimensions.
    float halfWidth = width * 0.5f;
    float halfDepth = depth * 0.5f;

    // Define the four corners of the ground.
    // We place the ground centered at the origin on the XZ plane (Y = 0).
    glm::vec3 bottomLeft(-halfWidth, 0.0f, halfDepth);
    glm::vec3 topLeft(-halfWidth, 0.0f, -halfDepth);
    glm::vec3 topRight(halfWidth, 0.0f, -halfDepth);
    glm::vec3 bottomRight(halfWidth, 0.0f, halfDepth);

    // The ground faces upward.
    glm::vec3 normal(0.0f, 1.0f, 0.0f);

    // Texture coordinates map the full texture onto the quad.
    glm::vec2 texBL(0.0f, 0.0f); // bottom-left
    glm::vec2 texTL(0.0f, 1.0f); // top-left
    glm::vec2 texTR(1.0f, 1.0f); // top-right
    glm::vec2 texBR(1.0f, 0.0f); // bottom-right

    // Add vertices in counter-clockwise order.
    vertices.push_back({ bottomLeft, normal, texBL });
    vertices.push_back({ topLeft,    normal, texTL });
    vertices.push_back({ topRight,   normal, texTR });
    vertices.push_back({ bottomRight,normal, texBR });

    // Create two triangles using the 4 vertices:
    // Triangle 1: bottom-left, top-left, top-right.
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    // Triangle 2: bottom-left, top-right, bottom-right.
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);


    Texture groundTexture;
    groundTexture.id = loadTexture("ground_diffuse.jpg", "resources/textures/ground");
    if (groundTexture.id == 0) {
        std::cerr << "Failed to load ground texture!" << std::endl;
    }
    groundTexture.type = "texture_diffuse";
    groundTexture.path = "resources/textures/ground/ground_diffuse.jpg";

    // Create the Mesh.
    return Mesh(vertices, indices, std::vector{groundTexture});
}

