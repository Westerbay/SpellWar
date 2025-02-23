/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_VERTEX_ARRAY_H__
#define __WG_VERTEX_ARRAY_H__

#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"

#include <vector>

#define VBO_VERTEX 0
#define VBO_COLOR 1
#define VBO_NORMAL 2
#define VBO_TEXCOORD_0 3
#define VBO_TEXCOORD_1 4
#define VBO_JOINTS 5
#define VBO_WEIGHTS 6

#define NUMBER_OF_VBOS 7

#define DRAW_TRIANGLES GL_TRIANGLES
#define DRAW_LINES GL_LINES


namespace wgame {

class VertexArrayObject : public IObjectGL {
public:
    VertexArrayObject();
    ~VertexArrayObject();
    template <typename T> 
    void setVBO(unsigned vboIndex, const std::vector<T> & values, GLboolean normalized = GL_FALSE);
    void setVBO(
        unsigned vboIndex,
        const void * data, 
        GLsizei size, 
        GLenum componentType, 
        GLuint numberOfComponent, 
        GLuint count,
        GLboolean normalized = GL_FALSE
    );
    template <typename T> 
    void setEBO(const std::vector<T> & values);
    void draw(GLenum mode) const;
    void bind() const override;
    void unbind() const override;
private:
    void encapsulateVBO(unsigned vboIndex, GLboolean normalized);
    GLuint _array;
    ElementBufferObject _ebo;
    VertexBufferObject _vbos[NUMBER_OF_VBOS];
};


template <typename T> 
void VertexArrayObject::setVBO(unsigned vboIndex, const std::vector<T> & values, GLboolean normalized) {
    bind();
    _vbos[vboIndex].setData(values);
    encapsulateVBO(vboIndex, normalized);
    unbind();
}

template <typename T> 
void VertexArrayObject::setEBO(const std::vector<T> & values) {
    bind();
    _ebo.setData(values);
    unbind();
}

}

#endif

