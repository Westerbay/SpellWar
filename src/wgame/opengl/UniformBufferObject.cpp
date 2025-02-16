/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/opengl/UniformBufferObject.hpp>


namespace wgame {
 
UniformBufferObject::UniformBufferObject(GLsizeiptr size, GLuint bindingPoint, GLenum usage) {
    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, _buffer);
    glBufferData(GL_UNIFORM_BUFFER, size, NULL, usage);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, _buffer);
}

UniformBufferObject::~UniformBufferObject() {
    glDeleteBuffers(1, &_buffer);
}

void UniformBufferObject::setData(const void * data, GLsizeiptr size, GLintptr offset) const {
    bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    unbind();
}

void UniformBufferObject::bind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, _buffer);
}

void UniformBufferObject::unbind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
 
}
