/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#include <WindowGL/Buffer.hpp>

Buffer::Buffer(GLenum target) : _target(target) {
    glGenBuffers(1, &_buffer);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &_buffer);
}

GLenum Buffer::getComponentTypeOfAttribute() const {
    return _componentTypeOfAttribute;
}

GLuint Buffer::getNumberOfComponentsOfAttribute() const {
    return _numberOfComponentsOfAttribute;
}

GLsizei Buffer::getNumberOfAttributes() const {
    return _numberOfAttributes;
}

void Buffer::bind() const {
    glBindBuffer(_target, _buffer);
}

void Buffer::unbind() const {
    glBindBuffer(_target, 0);
}
