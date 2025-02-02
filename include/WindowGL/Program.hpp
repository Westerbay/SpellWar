/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#ifndef __PROGRAM_GL_H__
#define __PROGRAM_GL_H__

#include <WindowGL/OGLStateObject.hpp>

class Program : public OGLStateObject {
public:
    Program(
        const char * vertexShaderFilePath, 
        const char * fragmentShaderFilePath
    );
    ~Program();
    void bind() const override;
    void unbind() const override;
private:
    GLuint compileShader(GLenum type, const char * filePath);
    GLuint _program;
};

#endif
