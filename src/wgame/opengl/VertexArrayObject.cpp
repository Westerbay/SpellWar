/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/opengl/VertexArrayObject.hpp>


namespace wgame {

VertexArrayObject::VertexArrayObject(unsigned numberOfBuffer) {
    _vbos = new BufferObject * [numberOfBuffer];
    for (unsigned i = 0; i < numberOfBuffer; i ++) {
        _vbos[i] = new BufferObject(GL_ARRAY_BUFFER);
    }
    _ibo = new BufferObject(GL_ELEMENT_ARRAY_BUFFER);
    _isIBObound = false;
    glGenVertexArrays(1, &_array);
}

VertexArrayObject::~VertexArrayObject() {
    delete _ibo;
    delete[] _vbos;
    glDeleteVertexArrays(1, &_array);
}

void VertexArrayObject::draw(GLenum mode) const {
    bind();
    if (_isIBObound) {
        _ibo -> bind();
        glDrawElements(
            mode,
            _ibo -> getNumberOfAttributes(),
            _ibo -> getComponentTypeOfAttribute(),
            nullptr
        );
        _ibo -> unbind();
    }
    else {
        glDrawArrays(mode, 0, _vbos[0] -> getNumberOfAttributes());
    }
    unbind();
}

void VertexArrayObject::bind() const {
    glBindVertexArray(_array);
}

void VertexArrayObject::unbind() const {
    glBindVertexArray(0);
}

void VertexArrayObject::encapsulateVBO(unsigned vboIndex) const {
    BufferObject * vbo = _vbos[vboIndex];
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
