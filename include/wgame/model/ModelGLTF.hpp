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
#include "../opengl/Shader.hpp"
#include "ModelMesh.hpp"

#include <unordered_map>

#define MODEL_DRAWER_VERTEX_SHADER_PATH "shaders/modeldrawer.vert"
#define MODEL_DRAWER_FRAGMENT_SHADER_PATH "shaders/modeldrawer.frag"


namespace wgame {


class ModelGLTF {
public:
    ModelGLTF(const std::string & filename, float scale = 1.0f);    
    ~ModelGLTF();
    void draw();
protected:
    class ShaderModel : public Shader {
    public:
        ShaderModel(); 
    };
private:
    void process();
    Matrix4D getNodeTransform(const tinygltf::Node & node);
    void processNodes(const tinygltf::Node & node, Matrix4D matrix = Matrix4D(1.0f));
    void processMesh(const tinygltf::Mesh & mesh, Matrix4D matrix);
    tinygltf::Model _model;
    float _scale;
    ShaderModel _shader;
    std::vector<ModelMesh *> _meshes;
};

}

#endif
