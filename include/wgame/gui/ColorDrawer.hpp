/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __COLOR_DRAWER_H__
#define __COLOR_DRAWER_H__

#include "../opengl/VertexArrayObject.hpp"
#include "../opengl/Shader.hpp"
#include "../geometry/Cuboid.hpp"

#define VERTEX_SHADER_PATH "shaders/color.vert"
#define FRAGMENT_SHADER_PATH "shaders/color.frag"


namespace wgame {

class ColorDrawer {
public:
    void drawCuboid(const Cuboid & cuboid, const ColorRGB & color);
    class ColorShader : public Shader {
    public:
        ColorShader();
    };
private:
    VertexArrayObject _vao;
    ColorShader _shader;
};

}

#endif
