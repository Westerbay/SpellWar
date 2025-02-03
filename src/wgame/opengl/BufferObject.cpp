/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/opengl/BufferObject.hpp>


namespace wgame::opengl {

BufferObject::BufferObject(GLenum target) : _target(target) {
    glGenBuffers(1, &_buffer);
}

BufferObject::~BufferObject() {
    glDeleteBuffers(1, &_buffer);
}

GLenum BufferObject::getComponentTypeOfAttribute() const {
    return _componentTypeOfAttribute;
}

GLuint BufferObject::getNumberOfComponentsOfAttribute() const {
    return _numberOfComponentsOfAttribute;
}

GLsizei BufferObject::getNumberOfAttributes() const {
    return _numberOfAttributes;
}

void BufferObject::bind() const {
    glBindBuffer(_target, _buffer);
}

void BufferObject::unbind() const {
    glBindBuffer(_target, 0);
}

}
