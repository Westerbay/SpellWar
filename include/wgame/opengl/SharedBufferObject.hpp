/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_SBO_H__
#define __WG_SBO_H__
   
#include "BufferObject.hpp"
   
   
namespace wgame {
   
class SharedBufferObject : public IObjectGL {
public:
    SharedBufferObject(GLenum type);
    ~SharedBufferObject();
    void configure(size_t size, GLenum usage = GL_STATIC_DRAW) const;
    void setBindingPoint(GLuint bindingPoint) const;
    void setData(const void * data, GLsizeiptr size, GLintptr offset = 0) const;
    void bind() const override;
    void unbind() const override;
private:
    GLuint _buffer;
    GLenum _type;
};
   
}
   
 #endif
   