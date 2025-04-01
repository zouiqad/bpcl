#include "PointCloud.h"
#include <glad/glad.h>
#include <iostream>
#include <cassert>

PointCloud::~PointCloud() {
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}

PointCloud::PointCloud(const std::vector<Point>& points) : points(points) {
    setup();
}

void PointCloud::setPoints(const std::vector<Point>& points) {
    this->points = points;
    setup();
}

const std::vector<Point>& PointCloud::getPoints() const {
    return points;
}

void PointCloud::setup() {
    // Clean up previous buffers if already created.
    if (VAO != 0) {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // Upload the point data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Point), points.data(), GL_STATIC_DRAW);

    // Vertex attribute for position (location 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);

    // Vertex attribute for color (location 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, Color));

    glBindVertexArray(0);
}

void PointCloud::draw(Shader &shader) const {
    // Bind the VAO and draw the points.
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(points.size()));
    glBindVertexArray(0);
}
