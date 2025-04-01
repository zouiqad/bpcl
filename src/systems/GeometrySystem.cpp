#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobj/tiny_obj_loader.h"

#include <iostream>
#include <filesystem>
#include "GeometrySystem.h"
#include "components/Transform.h"
#include "components/Renderable.h"
#include "core/Mediator.h"
#include "graphics/Mesh.h"
#include "graphics/PointCloud.h"
#include "core/Logger.h"
#include "utils/MarchingCubes.h"

namespace fs = std::filesystem;

extern Mediator gMediator;

void GeometrySystem::Init() {
    // Log that we're starting batch loading of OBJ files.
    Event event(Events::Log::NEW_MESSAGE);
    event.SetParam<std::string>(Events::Log::MESSAGE, "[BATCH LOADING OBJ FILES...]");
    gMediator.SendEvent(event);

    // Define the directory to search.
    std::string directoryPath = "/home/zouiqad/Downloads/mesh";

    // Iterate over each file in the directory.
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        // Only process regular files with .obj extension.
        if (entry.is_regular_file() && entry.path().extension() == ".obj") {
            std::string filePath = entry.path().string();

            // Log the file being loaded.
            Event fileEvent(Events::Log::NEW_MESSAGE);
            fileEvent.SetParam<std::string>(Events::Log::MESSAGE, "[LOADING FILE: " + filePath + "]");
            gMediator.SendEvent(fileEvent);

            // Load the OBJ file as a point cloud.
            auto pc = loadOBJPointCloud(filePath);

            std::cout << "loaded file: " << filePath << std::endl;

            // Optionally reconstruct a mesh from the point cloud.
            auto mesh = reconstructMesh(pc);

            // Create a geometry entity from the mesh.
            createGeometry(mesh, GeometryType::MESH);
        }
    }

    // Log that batch loading is finished.
    event.SetParam<std::string>(Events::Log::MESSAGE, "[BATCH LOADING FINISHED.]");
    gMediator.SendEvent(event);
}

void GeometrySystem::Update(float dt) {
    // Update logic if needed.
}

Entity GeometrySystem::createGeometry(const std::shared_ptr<Drawable>& drawable, GeometryType type) {
    Entity entity = gMediator.CreateEntity();

    // Attach a Geometry component (if you have one), Transform, and Renderable.
    gMediator.AddComponent(entity, Geometry{ .type = type });
    gMediator.AddComponent(entity, Transform{ });
    gMediator.AddComponent(entity, Renderable{ .drawable = drawable });

    return entity;
}

// Loads an OBJ file as a Mesh (with faces/indices)
std::shared_ptr<Mesh> GeometrySystem::loadOBJMesh(const std::string& path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());
    if (!warn.empty())
        std::cout << "TinyObjLoader Warning: " << warn << std::endl;
    if (!err.empty()) {
        std::cerr << "TinyObjLoader Error: " << err << std::endl;
    }
    if (!ret)
        return std::shared_ptr<Mesh>();

    // For a mesh, we need vertices and indices.
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Loop over shapes and build vertex/index arrays.
    for (const auto& shape : shapes) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
            int fv = shape.mesh.num_face_vertices[f];
            // For each face vertex:
            for (size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                Vertex vertex = {};

                // Positions
                vertex.Position = glm::vec3(
                    attrib.vertices[3 * idx.vertex_index + 0],
                    attrib.vertices[3 * idx.vertex_index + 1],
                    attrib.vertices[3 * idx.vertex_index + 2]);

                // Normals (if available)
                if (idx.normal_index >= 0) {
                    vertex.Normal = glm::vec3(
                        attrib.normals[3 * idx.normal_index + 0],
                        attrib.normals[3 * idx.normal_index + 1],
                        attrib.normals[3 * idx.normal_index + 2]);
                } else {
                    vertex.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
                }

                // Texture coordinates (if available)
                if (idx.texcoord_index >= 0) {
                    vertex.TexCoords = glm::vec2(
                        attrib.texcoords[2 * idx.texcoord_index + 0],
                        attrib.texcoords[2 * idx.texcoord_index + 1]);
                } else {
                    vertex.TexCoords = glm::vec2(0.0f);
                }

                vertices.push_back(vertex);
                indices.push_back(static_cast<unsigned int>(vertices.size() - 1));
            }
            index_offset += fv;
        }
    }

    auto mesh = std::make_shared<Mesh>(vertices, indices);
    createGeometry(mesh, GeometryType::MESH);

    return mesh;
}

// Loads an OBJ file as a Point Cloud (ignoring face data)
std::shared_ptr<PointCloud> GeometrySystem::loadOBJPointCloud(const std::string& path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;  // Not used in point cloud mode
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());
    if (!warn.empty())
        std::cout << "TinyObjLoader Warning: " << warn << std::endl;
    if (!err.empty())
        std::cerr << "TinyObjLoader Error: " << err << std::endl;
    if (!ret)
        return std::shared_ptr<PointCloud>();

    std::vector<Vertex> points;
    // In point cloud mode, ignore indices and simply use every vertex.
    for (size_t v = 0; v < attrib.vertices.size(); v += 3) {
        Vertex vertex = {};
        vertex.Position = glm::vec3(
            attrib.vertices[v + 0],
            attrib.vertices[v + 1],
            attrib.vertices[v + 2]);
        // Default color; you might load per-vertex colors from elsewhere if available.
        vertex.Color = glm::vec3(1.0f);
        // TexCoords and normals can be left default or computed if needed.
        points.push_back(vertex);
    }

    auto pc = std::make_shared<PointCloud>(points);
    createGeometry(pc, GeometryType::POINT_CLOUD);

    return pc;
}

std::shared_ptr<Mesh> GeometrySystem::reconstructMesh(const std::shared_ptr<PointCloud>& pc) {
    auto vertices = pc->getVertices();

    std::vector<glm::vec3> positions;
    positions.reserve(vertices.size());

    std::transform(vertices.begin(), vertices.end(), std::back_inserter(positions),
                   [](const Vertex& s) { return s.Position; });

    return MarchingCubes::reconstruct(positions, 1024);
}

