/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/opengl/VertexArrayObject.hpp>


namespace wgame {

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &_array);
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &_array);
}

void VertexArrayObject::draw(GLenum mode) const {
    bind();
    _ebo.bind();
    glDrawElements(
        mode,
        _ebo.getNumberOfAttributes(),
        _ebo.getComponentTypeOfAttribute(),
        nullptr
    );
    _ebo.unbind();
    unbind();
}

void VertexArrayObject::bind() const {
    glBindVertexArray(_array);
}

void VertexArrayObject::unbind() const {
    glBindVertexArray(0);
}

void VertexArrayObject::encapsulateVBO(unsigned vboIndex) {
    VertexBufferObject * vbo = _vbos + vboIndex;
    vbo -> bind();
    glEnableVertexAttribArray(vboIndex);
    glVertexAttribPointer(
        vboIndex,
        vbo -> getNumberOfComponentsOfAttribute(),
        vbo -> getComponentTypeOfAttribute(),
        GL_FALSE,
        0,
        nullptr
    );
    vbo -> unbind();
}

}
