#ifndef MARCHINGCUBES_H
#define MARCHINGCUBES_H

#include <vector>
#include <glm/glm.hpp>
#include "graphics/Mesh.h"
#include <memory>

class MarchingCubes {
public:
    static std::shared_ptr<Mesh> reconstruct(const std::vector<glm::vec3> &points,
                                             int gridResolution = 64);

private:
    static std::vector<float> buildOccupancyGrid(
        const std::vector<glm::vec3> &points,
        glm::vec3 &minBound,
        glm::vec3 &maxBound,
        int gridResolution);

    static void computeBoundingBox(const std::vector<glm::vec3> &points,
                                   glm::vec3 &minBound,
                                   glm::vec3 &maxBound);

    static void runMarchingCubes(const std::vector<float> &grid,
                                 const glm::vec3 &minBound,
                                 const glm::vec3 &maxBound,
                                 int gridResolution,
                                 std::vector<glm::vec3> &outVertices,
                                 std::vector<unsigned int> &outIndices);

    static float getGridValue(const std::vector<float> &grid,
                              int x,
                              int y,
                              int z,
                              int N);

    static glm::vec3 interpolateEdge(const glm::vec3 &p1,
                                     const glm::vec3 &p2,
                                     float valP1,
                                     float valP2,
                                     float isoLevel);

    static const int edgeTable[256];
    static const int triTable[256][16];
};

#endif
