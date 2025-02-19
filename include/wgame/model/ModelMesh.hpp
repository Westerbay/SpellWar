/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __MODEL_MESH_H__
#define __MODEL_MESH_H__

#include <glad/gl.h>

#include "../geometry/Geometry.hpp"
#include "../opengl/VertexArrayObject.hpp"
#include "../opengl/Texture2D.hpp"
#include "../opengl/Shader.hpp"

#define MAX_NUMBER_OF_GPU_ARRAYS 10


namespace wgame {

struct TransformNode {
    Vector3D translation;
    Vector3D scale;
    Quaternion rotation;
    Matrix4D matrix;
};

struct ElementBufferInfo {
    int eboIndex;
    GLsizei countElement;   
    GLenum drawMode;    
    GLenum componentType;
    char * offsetElement;
};

struct VertexBufferInfo {
    int vboIndex;
    GLuint vboLocation;
    GLuint size;
    GLenum type;   
    GLboolean normalized;    
    GLsizei stride;
    const void * pointer;
};

struct ModelSubMeshInfo {
    Matrix4D nodeTransform;
    int textureID;
    ElementBufferInfo elementsInfo;
    std::vector<VertexBufferInfo> vboInfo;
};

class ModelMesh {
public:
    ModelMesh();
    ~ModelMesh();
    void setVBO(int vboIndex, GLsizei byteLength, const void * data);
    void setEBO(int eboIndex, GLsizei byteLength, const void * data);
    void setTexture0(int textureIndex, int width, int height, int numChannels, const void * data);
    void addSubMesh(const ModelSubMeshInfo & modelSubMeshinfo);
    void bind() const;
    void unbind() const;
    void draw(const Shader & shader) const;
private:
    GLuint _vao;    
    GLuint _ebos[MAX_NUMBER_OF_GPU_ARRAYS];
    GLuint _vbos[MAX_NUMBER_OF_GPU_ARRAYS]; 
    GLuint _textures[MAX_NUMBER_OF_GPU_ARRAYS]; 
    std::vector<ModelSubMeshInfo> _subMeshesInfo;
};

}

#endif