#define TINYOBJLOADER_IMPLEMENTATION

#include "PointCloudSystem.h"
#include "tinyobj/tiny_obj_loader.h"  // include TinyObjLoader header
#include <iostream>

#include "components/Geometry.h"
#include "components/Renderable.h"
#include "components/Transform.h"
#include "core/Mediator.h"

extern Mediator gMediator;

void PointCloudSystem::Init() {

    loadPointCloudOBJ("C:\\Users\\Weiss\\Downloads\\output_cleaned2.obj", "0");
}

void PointCloudSystem::Update(float dt) {
    for(auto const& entity : mEntities) {
        // auto const& transform = gMediator.GetComponent<Transform>(entity);
        // auto const& renderable = gMediator.GetComponent<Renderable>(entity);
        // auto const& pointcloud = gMediator.GetComponent<PointCloudComponent>(entity);
        //

    }
}

void PointCloudSystem::createPointCloudEntity(const std::shared_ptr<PointCloud>& pointCloud) {
    auto entity = gMediator.CreateEntity();

    gMediator.AddComponent(entity, Geometry{ });
    gMediator.AddComponent(entity, Renderable{ .drawable = pointCloud});
    gMediator.AddComponent(entity, Transform{ });

}

bool PointCloudSystem::loadPointCloudOBJ(const std::string &filename, const std::string &id) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;
    // Load the OBJ file (we assume it contains only point data)
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str());
    if (!warn.empty())
        std::cout << "TinyObjLoader Warning: " << warn << std::endl;
    if (!err.empty())
        std::cerr << "TinyObjLoader Error: " << err << std::endl;
    if (!ret)
        return false;

    std::vector<Point> points;
    // Use the raw vertex positions as point positions.
    // Note: attrib.vertices is a flat array: x0,y0,z0, x1,y1,z1, ...
    for (size_t v = 0; v < attrib.vertices.size(); v += 3) {
        Point p;
        p.Position = glm::vec3(attrib.vertices[v], attrib.vertices[v+1], attrib.vertices[v+2]);
        p.Color = glm::vec3(1.0f); // Default white; you can extend this to load colors if available.
        points.push_back(p);
    }

    createPointCloudEntity(std::make_shared<PointCloud>(points));
    return true;
}
