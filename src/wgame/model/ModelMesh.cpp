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
    _texture0 = 0;
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

void ModelMesh::setTexture0(int width, int height, int numChannels, const void * data) {
    glGenTextures(1, &_texture0);
    glBindTexture(GL_TEXTURE_2D, _texture0);
    GLint internalFormat;
    switch(numChannels) {
        case RGBA_CHANNELS:
            internalFormat = GL_RGBA;
            break;
        case RGB_CHANNELS:
            internalFormat = GL_RGB;
            break;
        default:
            throw std::runtime_error("Texture2D : Unknown channel format");
    }
    glTexImage2D(
        GL_TEXTURE_2D, 0, internalFormat, 
        width, height,
        0, internalFormat, 
        GL_UNSIGNED_BYTE, data
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, 0);
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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glDrawElements(
        _elementsInfo.drawMode, 
        _elementsInfo.countElement, 
        _elementsInfo.componentType, 
        _elementsInfo.offsetElement
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    unbind();
}

}
