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


namespace wgame {

struct TransformNode {
    Vector3D translation;
    Vector3D scale;
    Quaternion rotation;
    Matrix4D matrix;
};

struct ElementArrayBufferInfo {
    GLsizei countElement;   
    GLenum drawMode;    
    GLenum componentType;
    char * offsetElement;
};

class ModelMesh {
public:
    ModelMesh(
        ElementArrayBufferInfo elementsInfo,
        Matrix4D nodeTransform
    );
    ~ModelMesh();
    Matrix4D getTransformation() const;
    void setTexture0(int width, int height, int numChannels, const void * data);
    void setVBO(
        GLsizei byteLength, const void * data,
        GLuint vboIndex, GLint size, GLenum type,
        GLboolean normalized, GLsizei stride, const void * pointer
    );
    void setEBO(GLsizei byteLength, const void * data);
    void bind() const;
    void unbind() const;
    void draw() const;
private:
    ElementArrayBufferInfo _elementsInfo;   
    Matrix4D _nodeTransform;
    GLuint _texture0;
    GLuint _texture1;
    GLuint _vao;
    GLuint _ebo; 
    GLuint _vbos[NUMBER_OF_VBOS]; 
    std::vector<GLuint> _vboIndices;
};

}

#endif