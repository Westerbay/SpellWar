/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include <WindowGL/Buffer.hpp>

#include <vector>

class VertexArray : public OGLStateObject {
public:
    VertexArray(unsigned numberOfBuffer);
    ~VertexArray();
    template <typename T> void setVBO(unsigned bufferIndex, const std::vector<T> & values);
    template <typename T> void setIBO(const std::vector<T> & values);
    void draw(GLenum mode) const;
    void bind() const override;
    void unbind() const override;
private:
    void encapsulateVBO(unsigned bufferIndex) const;
    GLuint _array;
    Buffer * _ibo;
    Buffer ** _buffers;
    bool _isIBObound;
};


template <typename T> void VertexArray::setVBO(unsigned bufferIndex, const std::vector<T> & values) {
    bind();
    _buffers[bufferIndex] -> setData(values);
    encapsulateVBO(bufferIndex);
    unbind();
}

template <typename T> void VertexArray::setIBO(const std::vector<T> & values) {
    bind();
    _ibo -> setData(values);
    unbind();
    _isIBObound = true;
}

#endif
