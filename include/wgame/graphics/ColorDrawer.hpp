/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_COLOR_DRAWER_H__
#define __WG_COLOR_DRAWER_H__

#include "Drawer.hpp"
#include "../geometry/Cuboid.hpp"
#include "../geometry/Sphere.hpp"

#define COLOR_DRAWER_VERTEX_SHADER_PATH "shaders/colorDrawer.vert"
#define COLOR_DRAWER_FRAGMENT_SHADER_PATH "shaders/colorDrawer.frag"


namespace wgame {

class ColorDrawer : public Drawer {
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
    void setFillCuboidData(
        const Cuboid & cuboid, 
        const std::vector<std::vector<ColorRGB>> & colors
    );
    void setFillCuboidData(const Cuboid & cuboid);
    void setFillSphereData(
        const Sphere & sphere, 
        const ColorRGB & color, 
        unsigned int stacks, unsigned int slices
    );
    void setFillCircleData(
        const Circle & circle, 
        const ColorRGB & color, 
        unsigned int segments
    );
    void draw(const Matrix4D & model = Matrix4D(1.0f), Mode mode = WORLD);    
    void fill(const Matrix4D & model = Matrix4D(1.0f), Mode mode = WORLD);
public:
    class ColorDrawerShader : public Shader {
    public:
        ColorDrawerShader();
    };
private:
    static std::weak_ptr<ColorDrawerShader> _uniqueShader;
    std::shared_ptr<ColorDrawerShader> _shader;
};

}

#endif
