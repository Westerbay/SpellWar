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

#define COLOR_DRAWER_VERTEX_SHADER_PATH "shaders/colordrawer.vert"
#define COLOR_DRAWER_FRAGMENT_SHADER_PATH "shaders/colordrawer.frag"


namespace wgame {

class ColorDrawer {
public:
    void drawCuboid(const Cuboid & cuboid, const ColorRGB & color = ColorRGB(0.0f));
    void fillCuboid(const Cuboid & cuboid, const ColorRGB & color);
protected:
    class ColorDrawerShader : public Shader {
    public:
        ColorDrawerShader();
    };
private:
    ColorDrawerShader _shader;
    VertexArrayObject _vao;
};

}

#endif
