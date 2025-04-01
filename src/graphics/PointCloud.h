#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include "core/Types.h"
#include <vector>

#include "core/Drawable.h"


class PointCloud : public Drawable {
public:
    PointCloud() = default;
    ~PointCloud();

    // Constructor to load from a vector of points
    PointCloud(const std::vector<Vertex>& vertices);

    // Set or update the point data
    void setVertices(const std::vector<Vertex>& vertices);

    const std::vector<Vertex>& getVertices() const;

    // Draw the point cloud using the given shader.
    // Assumes shader is already bound.
    void draw(Shader &shader) const override;

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    std::vector<Vertex> points;

    // Upload the points to the GPU and setup vertex attributes.
    void setup();
};
