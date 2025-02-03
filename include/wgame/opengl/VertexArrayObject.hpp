/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include <wgame/opengl/BufferObject.hpp>

#include <vector>


namespace wgame::opengl {

class VertexArrayObject : public IObjectGL {
public:
    VertexArrayObject(unsigned numberOfBuffer);
    ~VertexArrayObject();
    template <typename T> 
    void setVBO(unsigned vboIndex, const std::vector<T> & values);
    template <typename T> 
    void setIBO(const std::vector<T> & values);
    void draw(GLenum mode) const;
    void bind() const override;
    void unbind() const override;
private:
    void encapsulateVBO(unsigned vboIndex) const;
    GLuint _array;
    BufferObject * _ibo;
    BufferObject ** _vbos;
    bool _isIBObound;
};


template <typename T> 
void VertexArrayObject::setVBO(unsigned vboIndex, const std::vector<T> & values) {
    bind();
    _vbos[vboIndex] -> setData(values);
    encapsulateVBO(vboIndex);
    unbind();
}

template <typename T> 
void VertexArrayObject::setIBO(const std::vector<T> & values) {
    bind();
    _ibo -> setData(values);
    unbind();
    _isIBObound = true;
}

}

#endif

