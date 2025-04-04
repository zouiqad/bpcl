#pragma once

struct BoundingBox {
    float minX, minY, minZ, maxX, maxY, maxZ;
    float size;
};

enum class GeometryType {
    MESH,
    POINT_CLOUD
};

enum class Cluster {
    NONE,
    BUILDING,
    VEGETATION
};

struct Geometry {
    BoundingBox boundingBox;
    GeometryType type;
    Cluster cluster;
};
