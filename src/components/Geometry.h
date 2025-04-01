#pragma once

struct BoundingBox {
    float minX, minY, minZ, maxX, maxY, maxZ;
    float size;
};

enum class GeometryType {
    MESH,
    POINT_CLOUD
};

struct Geometry {
    BoundingBox boundingBox;
    GeometryType type;
};
