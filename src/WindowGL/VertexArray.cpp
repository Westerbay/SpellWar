/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#include <WindowGL/VertexArray.hpp>

VertexArray::VertexArray(unsigned numberOfBuffer) {
    _buffers = new Buffer * [numberOfBuffer];
    for (unsigned i = 0; i < numberOfBuffer; i ++) {
        _buffers[i] = new Buffer(GL_ARRAY_BUFFER);
    }
    _ibo = new Buffer(GL_ELEMENT_ARRAY_BUFFER);
    _isIBObound = false;
    glGenVertexArrays(1, &_array);
}

VertexArray::~VertexArray() {
    delete _ibo;
    delete[] _buffers;
    glDeleteVertexArrays(1, &_array);
}

void VertexArray::draw(GLenum mode) const {
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
        glDrawArrays(mode, 0, _buffers[0] -> getNumberOfAttributes());
    }
    unbind();
}

void VertexArray::bind() const {
    glBindVertexArray(_array);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::encapsulateVBO(unsigned bufferIndex) const {
    Buffer * vbo = _buffers[bufferIndex];
    vbo -> bind();
    glEnableVertexAttribArray(bufferIndex);
    glVertexAttribPointer(
        bufferIndex,
        vbo -> getNumberOfComponentsOfAttribute(),
        vbo -> getComponentTypeOfAttribute(),
        GL_FALSE,
        0,
        nullptr
    );
    vbo -> unbind();
}
