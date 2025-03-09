/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_MODEL_MESH_H__
#define __WG_MODEL_MESH_H__

#include <glad/glad.h>

#include "../geometry/Geometry.hpp"
#include "../opengl/VertexArrayObject.hpp"
#include "../opengl/Texture2D.hpp"
#include "../opengl/Shader.hpp"

#include <unordered_map>
#include <stdexcept>

#define MAX_INSTANCED 1000


namespace wgame {

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
    int normalized;    
    GLsizei stride;
    const void * pointer;
};

struct ModelSubMeshInfo {
    int textureID;
    int normalMapID;
    int metallicRoughnessID;
    Vector4D baseColorFactor;
    float metallicFactor;
    float roughnessFactor;
    Matrix4D transform;
    ElementBufferInfo elementsInfo;
    std::vector<VertexBufferInfo> vboInfo;
};

class ModelMesh {
public:
    ModelMesh();
    ~ModelMesh();
    void setVBO(int vboIndex, GLsizei byteLength, const void * data);
    void setEBO(int eboIndex, GLsizei byteLength, const void * data);
    void setTexture(
        int textureIndex, int width, int height, 
        int numChannels, const void * data,
        GLenum minFilter, GLenum magFilter,
        GLenum wrapS, GLenum wrapT, GLenum pixelType
    );
    void addSubMesh(const ModelSubMeshInfo & modelSubMeshinfo);
    void bind() const;
    void unbind() const;
    void draw(const Shader & shader, const Matrix4D & transform);
    void draw(const Shader & shader, size_t numberOfInstance);
protected:
    void configureBuffers(const ModelSubMeshInfo & subMesh, const Shader & shader);
private:
    GLuint _vao; 
    std::unordered_map<int, GLuint> _ebos;
    std::unordered_map<int, GLuint> _vbos; 
    std::unordered_map<int, GLuint> _textures; 
    std::vector<ModelSubMeshInfo> _subMeshesInfo;
};

}

#endif