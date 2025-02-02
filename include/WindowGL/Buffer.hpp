/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#ifndef __BUFFER_GL_H__
#define __BUFFER_GL_H__

#include <WindowGL/OGLStateObject.hpp>
#include <WindowGL/AttributeProperties.hpp>

#include <vector>

class Buffer : public OGLStateObject {
public:
    Buffer(GLenum target);
    ~Buffer();
    template <typename T> void setData(const std::vector<T> & values);
    GLenum getComponentTypeOfAttribute() const;
    GLuint getNumberOfComponentsOfAttribute() const;
    GLsizei getNumberOfAttributes() const;
    void bind() const override;
    void unbind() const override;
private:
    GLuint _buffer;
    GLenum _target;
    GLenum _componentTypeOfAttribute;
    GLuint _numberOfComponentsOfAttribute;
    GLsizei _numberOfAttributes;
};

template <typename T> void Buffer::setData(const std::vector<T> & values) {
    AttributeProperties<T> attributeProperties;
    _componentTypeOfAttribute = attributeProperties.typeEnum;
    _numberOfComponentsOfAttribute = attributeProperties.components;
    _numberOfAttributes = values.size();
    bind();
    glBufferData(_target, sizeof(T) * values.size(), values.data(), GL_STATIC_DRAW);
    unbind();
}

#endif 
