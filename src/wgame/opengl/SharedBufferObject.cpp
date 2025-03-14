/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/opengl/SharedBufferObject.hpp>


namespace wgame {
   
SharedBufferObject::SharedBufferObject(GLenum type) {
    glGenBuffers(1, &_buffer);    
    _type = type;
}
  
void SharedBufferObject::configure(size_t size, GLenum usage) const {
    glBindBuffer(_type, _buffer);
    glBufferData(_type, size, NULL, usage);
    glBindBuffer(_type, 0);
}
  
void SharedBufferObject::setBindingPoint(GLuint bindingPoint) const {
    glBindBufferBase(_type, bindingPoint, _buffer);
}
  
SharedBufferObject::~SharedBufferObject() {
    glDeleteBuffers(1, &_buffer);
}
  
void SharedBufferObject::setData(const void * data, GLsizeiptr size, GLintptr offset) const {
    bind();
    glBufferSubData(_type, offset, size, data);
    unbind();
}
  
void SharedBufferObject::bind() const {
    glBindBuffer(_type, _buffer);
}
  
void SharedBufferObject::unbind() const {
    glBindBuffer(_type, 0);
}
   
}
  