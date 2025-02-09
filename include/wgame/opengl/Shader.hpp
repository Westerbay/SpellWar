/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __SHADER_GL_H__
#define __SHADER_GL_H__

#include <wgame/opengl/IObjectGL.hpp>

#define DEFAULT_VERTEX_SHADER "shaders/default.v.glsl"
#define DEFAULT_FRAGMENT_SHADER "shaders/default.f.glsl"


namespace wgame {

class Shader : public IObjectGL {
public:
    Shader(
        const char * vertexShaderFilePath = DEFAULT_VERTEX_SHADER, 
        const char * fragmentShaderFilePath = DEFAULT_FRAGMENT_SHADER
    );
    ~Shader();
    void bind() const override;
    void unbind() const override;
private:
    GLuint compileShader(GLenum type, const char * filePath);
    GLuint _shader;
};

}

#endif

