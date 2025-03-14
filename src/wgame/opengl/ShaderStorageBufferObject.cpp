/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/opengl/ShaderStorageBufferObject.hpp>


namespace wgame {
  
ShaderStorageBufferObject::ShaderStorageBufferObject() {
    glGenBuffers(1, &_buffer);    
}
 
void ShaderStorageBufferObject::configure(size_t size, GLenum usage) const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, usage);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
 
void ShaderStorageBufferObject::setBindingPoint(GLuint bindingPoint) const {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, _buffer);
}
 
ShaderStorageBufferObject::~ShaderStorageBufferObject() {
    glDeleteBuffers(1, &_buffer);
}
 
void ShaderStorageBufferObject::setData(const void * data, GLsizeiptr size, GLintptr offset) const {
    bind();
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
    unbind();
}
 
void ShaderStorageBufferObject::bind() const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _buffer);
}
 
void ShaderStorageBufferObject::unbind() const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
  
}
 