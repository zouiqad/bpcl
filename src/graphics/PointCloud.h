#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <vector>

#include "core/Drawable.h"

struct Point {
    glm::vec3 Position;
    glm::vec3 Color;
};

class PointCloud : public Drawable {
public:
    PointCloud() = default;
    ~PointCloud();

    // Constructor to load from a vector of points
    PointCloud(const std::vector<Point>& points);

    // Set or update the point data
    void setPoints(const std::vector<Point>& points);

    // Retrieve the point data (if needed)
    const std::vector<Point>& getPoints() const;

    // Draw the point cloud using the given shader.
    // Assumes shader is already bound.
    void draw(Shader &shader) const override;

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    std::vector<Point> points;

    // Upload the points to the GPU and setup vertex attributes.
    void setup();
};
