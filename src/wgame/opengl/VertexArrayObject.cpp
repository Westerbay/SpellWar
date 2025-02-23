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

void VertexArrayObject::setVBO(
    unsigned vboIndex,
    const void * data, 
    GLsizei size, 
    GLenum componentType, 
    GLuint numberOfComponent, 
    GLuint count,
    GLboolean normalized
) {
    bind();
    _vbos[vboIndex].setData(data, size, componentType, numberOfComponent, count);
    encapsulateVBO(vboIndex, normalized);
    unbind();
}

void VertexArrayObject::encapsulateVBO(unsigned vboIndex, GLboolean normalized) {
    VertexBufferObject * vbo = _vbos + vboIndex;
    vbo -> bind();
    glEnableVertexAttribArray(vboIndex);
    GLuint numberOfComponent = vbo -> getNumberOfComponentsOfAttribute();
    GLenum type = vbo -> getComponentTypeOfAttribute();
    if (type == GL_DOUBLE || type == GL_FLOAT) {
        glVertexAttribPointer(
            vboIndex,
            numberOfComponent,
            type,
            normalized,
            0,
            nullptr
        );
    }
    else {
        glVertexAttribIPointer(
            vboIndex,
            numberOfComponent,
            type,
            0,
            nullptr
        );
    }    
    vbo -> unbind();
}

}
