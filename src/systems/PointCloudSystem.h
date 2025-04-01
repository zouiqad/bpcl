#pragma once

#include <memory>

#include "graphics/PointCloud.h"
#include "graphics/Shader.h"
#include <string>
#include <unordered_map>

#include "core/System.h"
#include "core/Types.h"

class PointCloudSystem : public System {
public:

    // Retrieve a loaded point cloud by id.
    PointCloud* getPointCloud(const std::string &id);

    void Init();

    void Update(float dt);

private:
    bool loadPointCloudOBJ(const std::string &filename, const std::string &id);

    void createPointCloudEntity(const std::shared_ptr<PointCloud>& pointCloud);
};
