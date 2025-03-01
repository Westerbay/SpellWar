/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_COLOR_DRAWER_H__
#define __WG_COLOR_DRAWER_H__

#include "../opengl/VertexArrayObject.hpp"
#include "../opengl/Shader.hpp"
#include "../geometry/Cuboid.hpp"

#include <memory>

#define COLOR_DRAWER_VERTEX_SHADER_PATH "shaders/colorDrawer.vert"
#define COLOR_DRAWER_FRAGMENT_SHADER_PATH "shaders/colorDrawer.frag"


namespace wgame {

class ColorDrawer {
public:
    ColorDrawer();
    void setDrawCuboidData(
        const Cuboid & cuboid, 
        const ColorRGB & colors
    );
    void setFillCuboidData(
        const Cuboid & cuboid, 
        const std::vector<ColorRGB> & colors
    );
    void draw();
    void fill();
public:
    class ColorDrawerShader : public Shader {
    public:
        ColorDrawerShader();
    };
private:
    static std::weak_ptr<ColorDrawerShader> _uniqueShader;
    std::shared_ptr<ColorDrawerShader> _shader;
    VertexArrayObject _vaos[6];
};

}

#endif
