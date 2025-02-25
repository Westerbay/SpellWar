/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/model/ModelMesh.hpp>


namespace wgame {

ModelMesh::ModelMesh() {
    glGenVertexArrays(1, &_vao);
}

ModelMesh::~ModelMesh() {
    for (const auto & index: _ebos) {
        glDeleteBuffers(1, &index.second);
    }
    for (const auto & index: _vbos) {
        glDeleteBuffers(1, &index.second);
    }
    for (const auto & index: _textures) {
        glDeleteTextures(1, &index.second);
    }
    glDeleteVertexArrays(1, &_vao);
}

void ModelMesh::setVBO(int vboIndex, GLsizei byteLength, const void * data) {
    if (_vbos.find(vboIndex) != _vbos.end()) {
        return;
    }
    _vbos[vboIndex] = 0;
    glGenBuffers(1, &_vbos[vboIndex]);
    glBindBuffer(GL_ARRAY_BUFFER, _vbos[vboIndex]);
    glBufferData(GL_ARRAY_BUFFER, byteLength, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelMesh::setEBO(int eboIndex, GLsizei byteLength, const void * data) {
    if (_ebos.find(eboIndex) != _ebos.end()) {
        return;
    }
    _ebos[eboIndex] = 0;
    glGenBuffers(1, &_ebos[eboIndex]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebos[eboIndex]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteLength, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ModelMesh::setTexture0(
    int textureIndex, int width, int height, 
    int numChannels, const void * data,
    GLenum minFilter, GLenum magFilter,
    GLenum wrapS, GLenum wrapT, GLenum pixelType
) {
    if (_textures.find(textureIndex) != _textures.end()) {
        return;
    }
    _textures[textureIndex] = 0;
    glGenTextures(1, &_textures[textureIndex]);
    glBindTexture(GL_TEXTURE_2D, _textures[textureIndex]);
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
        pixelType, data
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ModelMesh::addSubMesh(const ModelSubMeshInfo & modelSubMeshinfo) {
    _subMeshesInfo.push_back(modelSubMeshinfo);
}

void ModelMesh::bind() const {
    glBindVertexArray(_vao);
}

void ModelMesh::unbind() const {
    glBindVertexArray(0);
}

void ModelMesh::draw() {
    bind();
    glActiveTexture(GL_TEXTURE0);
    for (const ModelSubMeshInfo & subMesh : _subMeshesInfo) {
        glBindTexture(GL_TEXTURE_2D, subMesh.textureID == -1 ? 0 : _textures[subMesh.textureID]);
        for (const VertexBufferInfo & vboInfo : subMesh.vboInfo) {
            glBindBuffer(GL_ARRAY_BUFFER, _vbos[vboInfo.vboIndex]);
            glEnableVertexAttribArray(vboInfo.vboLocation);
            if (vboInfo.vboLocation == VBO_JOINTS) {
                glVertexAttribIPointer(
                    vboInfo.vboLocation, vboInfo.size, 
                    vboInfo.type, vboInfo.stride, vboInfo.pointer
                ); 
            } else {
                glVertexAttribPointer(
                    vboInfo.vboLocation, vboInfo.size, 
                    vboInfo.type, vboInfo.normalized, 
                    vboInfo.stride, vboInfo.pointer
                );   
            }
            glBindBuffer(GL_ARRAY_BUFFER, 0);        
        }        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebos[subMesh.elementsInfo.eboIndex]);
        glDrawElements(
            subMesh.elementsInfo.drawMode, 
            subMesh.elementsInfo.countElement, 
            subMesh.elementsInfo.componentType, 
            subMesh.elementsInfo.offsetElement
        );
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }    
    unbind();
}

}
