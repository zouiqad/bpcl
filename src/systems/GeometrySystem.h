#pragma once
#include <memory>

#include "components/Geometry.h"
#include "core/Drawable.h"
#include "core/System.h"
#include "graphics/Mesh.h"
#include "graphics/PointCloud.h"


class GeometrySystem : public System {
public:

    void Init() override;
    void Update(float deltaTime) override;

private:
    std::shared_ptr<Mesh> loadOBJMesh(const std::string& path);
    std::shared_ptr<PointCloud> loadOBJPointCloud(const std::string& path);

    std::shared_ptr<Mesh> reconstructMesh(const std::shared_ptr<PointCloud>& pc);
    Entity createGeometry(const std::shared_ptr<Drawable>& drawable, GeometryType type);
};
