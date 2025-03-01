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
    GLchar infoLog[SHADER_LOG_BUFFER_SIZE];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, SHADER_LOG_BUFFER_SIZE, NULL, infoLog);
        std::cerr << infoLog << std::endl;
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

bool Shader::bound() const {
 	GLint currentProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
	return _shader == (GLuint) currentProgram;
}

bool Shader::getUniformLocation(const std::string & name, GLuint & location) const {
	location = glGetUniformLocation(_shader, name.data());
	if (location == GL_INVALID_VALUE) {
		return false;
	}
	if (location == GL_INVALID_OPERATION) {
		return false;
	}
	return true;
}

template <> void Shader::uniformDispatcher(GLuint location, const bool & val) {
	glUniform1i(location, val);
}

template <> void Shader::uniformDispatcher(GLuint location, const int & val) {
	glUniform1i(location, val);
}

template <> void Shader::uniformDispatcher(GLuint location, const unsigned & val) {
	glUniform1ui(location, val);
}

template <> void Shader::uniformDispatcher(GLuint location, const float & val) {
	glUniform1f(location, val);
}

template <> void Shader::uniformDispatcher(GLuint location, const glm::vec2 & val) {
	glUniform2fv(location, 1, glm::value_ptr(val));
}

template <> void Shader::uniformDispatcher(GLuint location, const glm::vec3 & val) {
	glUniform3fv(location, 1, glm::value_ptr(val));
}

template <> void Shader::uniformDispatcher(GLuint location, const glm::vec4 & val) {
	glUniform4fv(location, 1, glm::value_ptr(val));
}

template <> void Shader::uniformDispatcher(GLuint location, const glm::mat2 & val) {
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

template <> void Shader::uniformDispatcher(GLuint location, const glm::mat3 & val) {
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

template <> void Shader::uniformDispatcher(GLuint location, const glm::mat4 & val) {
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

}
