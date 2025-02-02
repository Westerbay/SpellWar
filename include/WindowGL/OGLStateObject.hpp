/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#ifndef __OGL_STATE_OBJECT_H__
#define __OGL_STATE_OBJECT_H__

#include <GL/glew.h>

class OGLStateObject {
public:
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual ~OGLStateObject() = default;
};

#endif
