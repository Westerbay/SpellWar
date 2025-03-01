/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_MODEL_H__
#define __WG_MODEL_H__

#include <tinygltf/tiny_gltf.h>

#include "../tools/Util.hpp"
#include "ModelMesh.hpp"

#include <iostream>


#define GLTF_EXT "gltf"
#define GLB_EXT "glb"

#define POSITION "POSITION"
#define NORMAL "NORMAL"
#define TEXCOORD_0 "TEXCOORD_0"
#define JOINTS "JOINTS_0"
#define WEIGHTS "WEIGHTS_0"

#define BINDING_JOINT_MATRICES 2


namespace wgame {


class ModelGLTF {
public:
    ModelGLTF();
    virtual ~ModelGLTF() = default;
    void setTransform(const Matrix4D & transform);
    void drawModelMesh(const Shader & shader);
    void drawModelMeshInstanced(const Shader & shader, size_t numberOfInstance);
    virtual void draw(const Shader & shader) = 0;
    virtual void drawInstanced(const Shader & shader, size_t numberOfInstance) = 0;
protected:
    int getVBOIndex(const std::string & key);
    template<typename T>
    void loadAccessor(const tinygltf::Model & model, const tinygltf::Accessor & accessor, const T*& pointer);
    void process(const tinygltf::Model & model);  
    void processNodes(
        const tinygltf::Model & model, 
        const tinygltf::Node & node, Matrix4D transformParent
    );
    void processMesh(
        const tinygltf::Model & model, 
        const tinygltf::Mesh & mesh, Matrix4D transform
    );    
    Matrix4D getTransformNode(const tinygltf::Node & node) const;
private: 
    Matrix4D _transform;
    ModelMesh _modelMesh;    
};

template<typename T>
void ModelGLTF::loadAccessor(const tinygltf::Model & model, const tinygltf::Accessor & accessor, const T*& pointer) {
    const tinygltf::BufferView & view = model.bufferViews[accessor.bufferView];
    pointer = reinterpret_cast<const T *>(&(model.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]));
}

}

#endif
