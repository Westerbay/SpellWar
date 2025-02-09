/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/opengl/Shader.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


namespace wgame {

Shader::Shader(const char * vertexShaderFilePath, const char * fragmentShaderFilePath) {
    _shader = glCreateProgram();
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderFilePath);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderFilePath);
    glAttachShader(_shader, vertexShader);
    glAttachShader(_shader, fragmentShader);
    glLinkProgram(_shader);
    glDetachShader(_shader, vertexShader);
    glDetachShader(_shader, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(_shader);
}

GLuint Shader::compileShader(GLenum type, const char * filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        throw std::runtime_error("Cannot open shader files !");	
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    std::string shaderCode = shaderStream.str();
    const char * shaderSource = shaderCode.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        throw std::runtime_error("Cannot compile shader !");
    }   

    return shader;
}

void Shader::bind() const {
    glUseProgram(_shader);
}

void Shader::unbind() const {
    glUseProgram(0);
}

}
