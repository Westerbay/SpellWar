/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_TEXTURE_2D_H__
#define __WG_TEXTURE_2D_H__

#include "IObjectGL.hpp"
#include "../tools/Image.hpp"

#include <stdexcept>

#define INTERPOLATION_LINEAR GL_LINEAR
#define INTERPOLATION_NEAREST GL_NEAREST

#define REPEAT GL_REPEAT
#define MIRRORED_REPEAT GL_MIRRORED_REPEAT
#define CLAMP_TO_EDGE GL_CLAMP_TO_EDGE

#define TEXTURE_WRAP_S GL_TEXTURE_WRAP_S
#define TEXTURE_WRAP_T GL_TEXTURE_WRAP_T
#define TEXTURE_WRAP_R GL_TEXTURE_WRAP_R

#define TEXTURE_CUBE_MAP_POSITIVE_X GL_TEXTURE_CUBE_MAP_POSITIVE_X
#define TEXTURE_CUBE_MAP_NEGATIVE_X GL_TEXTURE_CUBE_MAP_NEGATIVE_X
#define TEXTURE_CUBE_MAP_POSITIVE_Y GL_TEXTURE_CUBE_MAP_POSITIVE_Y
#define TEXTURE_CUBE_MAP_NEGATIVE_Y GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
#define TEXTURE_CUBE_MAP_POSITIVE_Z GL_TEXTURE_CUBE_MAP_POSITIVE_Z
#define TEXTURE_CUBE_MAP_NEGATIVE_Z GL_TEXTURE_CUBE_MAP_NEGATIVE_Z

#define TEXTURE_2D GL_TEXTURE_2D
#define TEXTURE_CUBE_MAP GL_TEXTURE_CUBE_MAP

#define RGBA_CHANNELS 4
#define RGB_CHANNELS 3


namespace wgame {

typedef GLint InterpolationMode;
typedef GLint RepeatMode;

class Texture2D : public IObjectGL {
public:
    Texture2D(GLenum type = TEXTURE_2D);
    ~Texture2D();
    void setType(GLenum type);
    void setParameter(GLenum paramName, GLint value) const;
    void setInterpolationMode(InterpolationMode interpolation) const;
    void setRepeatMode(RepeatMode repeat) const;
    void setData(const Image & image, GLenum type = TEXTURE_2D, bool generateMipmap = true) const;
    void enableAnisotropicFiltering() const;
    void bind() const override;
    void unbind() const override;
private:
    GLuint _texture;
    GLenum _type;
};

}

#endif
