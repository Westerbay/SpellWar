/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __MODEL_H__
#define __MODEL_H__

#include <tinygltf/tiny_gltf.h>
#include <glad/gl.h>

#include "ModelMesh.hpp"

#include <unordered_map>

#define GLTF_EXT "gltf"
#define GLB_EXT "glb"

#define POSITION "POSITION"


namespace wgame {


class ModelGLTF {
public:
    ModelGLTF(const std::string & filename, float scale = 1.0f);    
    ~ModelGLTF();
    float getScaleFactor() const;
    std::vector<ModelMesh *> & getMeshes();
private:
    void process(const tinygltf::Model & model);
    Matrix4D getNodeTransform(const tinygltf::Node & node);
    void processNodes(
        const tinygltf::Model & model, 
        const tinygltf::Node & node, 
        Matrix4D matrix = Matrix4D(1.0f)
    );
    void processMesh(
        const tinygltf::Model & model, 
        const tinygltf::Mesh & mesh, Matrix4D matrix
    );
    float _scale;    
    std::vector<ModelMesh *> _meshes;
};

}

#endif
