#include "Mesh.h"
#include <iostream>
#include <glm/ext/scalar_constants.hpp>

Mesh::Mesh (std::vector<Vertex> vertices,
            std::vector<unsigned int> indices,
            std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices  = indices;
    this->textures = textures;

    this->setup ();
}

Mesh::Mesh (std::vector<Vertex> vertices,
            std::vector<unsigned int> indices) {
    this->vertices = vertices;
    this->indices  = indices;

    this->setup ();
}

void Mesh::setup () {
    glGenVertexArrays (1, &VAO);
    glGenBuffers (1, &VBO);
    glGenBuffers (1, &EBO);

    glBindVertexArray (VAO);
    glBindBuffer (GL_ARRAY_BUFFER, VBO);

    glBufferData (GL_ARRAY_BUFFER, vertices.size () * sizeof (Vertex),
        &vertices[0], GL_STATIC_DRAW);

    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER,
        indices.size () * sizeof (unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*)0);

    // Vertex colors
    glEnableVertexAttribArray (1);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*)offsetof (Vertex, Color));

    // Vertex normals
    glEnableVertexAttribArray (2);
    glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex),
        (void*)offsetof (Vertex, Normal));

    // Vertex texture coords
    glEnableVertexAttribArray (3);
    glVertexAttribPointer (3, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex),
        (void*)offsetof (Vertex, TexCoords));

    glBindVertexArray (0);

    // Estimate normals
    this->estimateNormals();
}

void Mesh::draw (Shader& shader) const {
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;

    glUniform1i(glGetUniformLocation(shader.getID(), "uHasTexture"), false);
    for (unsigned int i = 0; i < textures.size (); i++) {
        glActiveTexture (GL_TEXTURE0 + i);
        // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse") number = std::to_string (diffuseNr++);
        else if (name == "texture_specular")
            number =
                std::to_string (specularNr++);
            // transfer unsigned int to string
        else if (name == "texture_normal") number = std::to_string (normalNr++);
            // transfer unsigned int to string
        else if (name == "texture_height") number = std::to_string (heightNr++);
        // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        shader.setUniform("uTexture", i);
        glUniform1i(glGetUniformLocation(shader.getID(), "uHasTexture"), true);


        // and finally bind the texture
        glBindTexture (GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    glBindVertexArray (VAO);
    glDrawElements (GL_TRIANGLES, static_cast<unsigned int> (indices.size ()),
        GL_UNSIGNED_INT, 0);
    glBindVertexArray (0);

    //  set everything back to defaults once configured
    glActiveTexture (GL_TEXTURE0);
}

void Mesh::estimateNormals() {
    // Reset normals to zero for all vertices.
    for (auto& vertex : vertices) {
        vertex.Normal = glm::vec3(0.0f);
    }

    // For each triangle, calculate its face normal and accumulate it for each vertex.
    // Assumes that 'indices' is a multiple of 3 (i.e., each triangle is defined by 3 indices).
    for (size_t i = 0; i < indices.size(); i += 3) {
        unsigned int i0 = indices[i];
        unsigned int i1 = indices[i + 1];
        unsigned int i2 = indices[i + 2];

        // Retrieve the positions of the triangle's vertices.
        const glm::vec3& p0 = vertices[i0].Position;
        const glm::vec3& p1 = vertices[i1].Position;
        const glm::vec3& p2 = vertices[i2].Position;

        // Compute the edge vectors.
        glm::vec3 edge1 = p1 - p0;
        glm::vec3 edge2 = p2 - p0;

        // Calculate the face normal (normalized).
        glm::vec3 faceNormal = glm::normalize(glm::cross(edge1, edge2));

        // Accumulate the face normal into each vertex's normal.
        vertices[i0].Normal += faceNormal;
        vertices[i1].Normal += faceNormal;
        vertices[i2].Normal += faceNormal;
    }

    // Normalize each vertex normal.
    for (auto& vertex : vertices) {
        vertex.Normal = glm::normalize(vertex.Normal);
    }

    // Update the VBO with the new normals.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
