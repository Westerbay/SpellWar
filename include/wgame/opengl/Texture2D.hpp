/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __TEXTURE_2D_H__
#define __TEXTURE_2D_H__

#include "IObjectGL.hpp"
#include "../tools/Image.hpp"

#include <stdexcept>

#define INTERPOLATION_LINEAR GL_LINEAR
#define INTERPOLATION_NEAREST GL_NEAREST

#define REPEAT GL_REPEAT
#define MIRRORED_REPEAT GL_MIRRORED_REPEAT
#define CLAMP_TO_EDGE GL_CLAMP_TO_EDGE

#define RGBA_CHANNELS 4
#define RGB_CHANNELS 3


namespace wgame {

typedef GLint InterpolationMode;
typedef GLint RepeatMode;

class Texture2D : public IObjectGL {
public:
    Texture2D();
    ~Texture2D();
    void setParameter(GLenum paramName, GLint value) const;
    void setInterpolationMode(InterpolationMode interpolation) const;
    void setRepeatMode(RepeatMode repeat) const;
    void setData(const Image & image) const;
    void enableAnisotropicFiltering() const;
    void bind() const override;
    void unbind() const override;
private:
    GLuint _texture;
};

}

#endif
