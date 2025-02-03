/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/opengl/Program.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


namespace wgame::opengl {

Program::Program(
    const char * vertexShaderFilePath, 
    const char * fragmentShaderFilePath) {
    _program = glCreateProgram();
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderFilePath);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderFilePath);
    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fragmentShader);
    glLinkProgram(_program);
    glDetachShader(_program, vertexShader);
    glDetachShader(_program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Program::~Program() {
    glDeleteProgram(_program);
}

GLuint Program::compileShader(GLenum type, const char * filePath) {
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

void Program::bind() const {
    glUseProgram(_program);
}

void Program::unbind() const {
    glUseProgram(0);
}

}
