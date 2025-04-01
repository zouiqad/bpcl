#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/Drawable.h"

class Model : public Drawable {
public:
    // Constructor for when we want to load a model from a file
    Model(const char *path) {
        loadModel(path);
    }

    // Constructor for when we want to create the mesh programatically
    Model(const Mesh& mesh) {
        mMeshes.push_back(mesh);
    }

    void draw(Shader &shader) const override;

private:
    std::vector<Mesh> mMeshes;
    std::string directory;

    std::vector<Texture> textures_loaded;

    void loadModel(std::string path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat,
                                              aiTextureType type,
                                              std::string typeName);
};

