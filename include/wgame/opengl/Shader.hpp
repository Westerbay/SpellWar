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
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>

#define SHADER_LOG_BUFFER_SIZE 1024

namespace wgame {

class Shader : public IObjectGL {
public:
    Shader(
        const char * vertexShaderFilePath, 
        const char * fragmentShaderFilePath
    );
    ~Shader();
    template <typename T> 
    void setUniform(const std::string & name, const T & val) const;
    void bind() const override;
    void unbind() const override;
    bool bound() const;
private:
	bool getUniformLocation(const std::string & name, GLuint & location) const;
    template <typename T> static void uniformDispatcher(GLuint location, const T & value);
    GLuint compileShader(GLenum type, const char * filePath);
    GLuint _shader;
};

template <typename T> 
void Shader::setUniform(const std::string & name, const T & val) const {
 	GLuint location;
 	if (getUniformLocation(name, location) && bound()) {
		uniformDispatcher<T>(location, val);
 	}
 	else if (!bound()) {
		throw std::runtime_error("Uniform was required but shader is not bound ! ");
	}
 	else {
		throw std::runtime_error("Uniform was required but does not exist ! ");
	}
}


}

#endif

