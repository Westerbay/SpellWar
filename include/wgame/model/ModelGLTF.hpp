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
    void drawModelMesh(const Shader & shader);
    virtual void draw(const Shader & shader) = 0;
protected:
    static std::string getFilePathExtension(const std::string & fileName);
    static int getVBOIndex(const std::string & key);
    template<typename T>
    void loadAccessor(const tinygltf::Model & model, const tinygltf::Accessor & accessor, const T*& pointer);
    void process(const tinygltf::Model & model);  
    void processNodes(
        const tinygltf::Model & model, 
        const tinygltf::Node & node
    );
    void processMesh(
        const tinygltf::Model & model, 
        const tinygltf::Mesh & mesh
    );    

    float _scale;    
    ModelMesh _modelMesh;    
};

template<typename T>
void ModelGLTF::loadAccessor(const tinygltf::Model & model, const tinygltf::Accessor & accessor, const T*& pointer) {
    const tinygltf::BufferView & view = model.bufferViews[accessor.bufferView];
    pointer = reinterpret_cast<const T *>(&(model.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]));
}

}

#endif
