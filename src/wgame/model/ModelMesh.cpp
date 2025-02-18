/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/model/ModelMesh.hpp>


namespace wgame {

ModelMesh::ModelMesh(
    ElementArrayBufferInfo elementsInfo,
    Matrix4D nodeTransform
) : _elementsInfo(elementsInfo), _nodeTransform(nodeTransform) {
    glGenVertexArrays(1, &_vao);
}

ModelMesh::~ModelMesh() {
    glDeleteBuffers(1, &_vao);
    glDeleteBuffers(1, &_ebo);
    for (int index : _vboIndices) {
        glDeleteBuffers(1, _vbos + index);
    }
}

Matrix4D ModelMesh::getTransformation() const {
    return _nodeTransform;
}

void ModelMesh::setVBO(
    GLsizei byteLength, const void * data,
    GLuint vboIndex, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, const void * pointer
) {
    glGenBuffers(1, _vbos + vboIndex);
    _vboIndices.push_back(vboIndex);
    glBindBuffer(GL_ARRAY_BUFFER, _vbos[vboIndex]);
    glBufferData(GL_ARRAY_BUFFER, byteLength, data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vboIndex);
    glVertexAttribPointer(
        vboIndex, size, type, normalized, stride, pointer
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelMesh::setEBO(GLsizei byteLength, const void * data) {
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteLength, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ModelMesh::bind() const {
    glBindVertexArray(_vao);
}

void ModelMesh::unbind() const {
    glBindVertexArray(0);
}

void ModelMesh::draw() const {
    bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glDrawElements(
        _elementsInfo.drawMode, 
        _elementsInfo.countElement, 
        _elementsInfo.componentType, 
        _elementsInfo.offsetElement
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    unbind();
}

}
