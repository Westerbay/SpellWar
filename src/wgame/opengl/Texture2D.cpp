/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/opengl/Texture2D.hpp>


namespace wgame {

Texture2D::Texture2D(GLenum type) {
    glGenTextures(1, &_texture);
    _type = type;
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &_texture);
}

void Texture2D::setType(GLenum type) {
    _type = type;
}

void Texture2D::setParameter(GLenum paramName, GLint value) const {
    bind();
    glTexParameteri(_type, paramName, value);
    unbind();
}

void Texture2D::setInterpolationMode(InterpolationMode interpolation) const {
    setParameter(GL_TEXTURE_MIN_FILTER, interpolation);
    setParameter(GL_TEXTURE_MAG_FILTER, interpolation);
}

void Texture2D::setRepeatMode(RepeatMode repeat) const {
    setParameter(GL_TEXTURE_WRAP_S, repeat);
    setParameter(GL_TEXTURE_WRAP_T, repeat);
}

void Texture2D::setData(const Image & image, GLenum type, bool generateMipmap) const {
    bind();
    GLint internalFormat;
    switch(image.getNumberOfChannels()) {
        case RGBA_CHANNELS:
            internalFormat = GL_RGBA;
            break;
        case RGB_CHANNELS:
            internalFormat = GL_RGB;
            break;
        case RED_CHANNELS:
            internalFormat = GL_RED;
            break;
        default:
            throw std::runtime_error("Texture2D : Unknown channel format");
    }
    glTexImage2D(
        type, 0, internalFormat, 
        image.getWidth(), image.getHeight(),
        0, internalFormat, 
        GL_UNSIGNED_BYTE, image.getData()
    );
    if (generateMipmap) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    unbind();
}

void Texture2D::enableAnisotropicFiltering() const {
    bind();
    GLfloat maxAniso = 1.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
    setParameter(GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint) maxAniso);  
    unbind(); 
}

void Texture2D::bind() const {
    glBindTexture(_type, _texture);
}

void Texture2D::unbind() const {
    glBindTexture(_type, 0);
}

}
