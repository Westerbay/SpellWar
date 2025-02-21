/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_UBO_H__
#define __WG_UBO_H__
 
#include "BufferObject.hpp"
 
 
namespace wgame {
 
class UniformBufferObject : public IObjectGL {
public:
    UniformBufferObject(GLsizeiptr size, GLuint bindingPoint, GLenum usage = GL_STATIC_DRAW);
    ~UniformBufferObject();
    void setData(const void * data, GLsizeiptr size, GLintptr offset = 0) const;
    void bind() const override;
    void unbind() const override;
private:
    GLuint _buffer;
};
 
}
 
#endif
 