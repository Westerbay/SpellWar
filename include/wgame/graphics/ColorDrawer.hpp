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
#include "../geometry/Sphere.hpp"

#include <memory>

#define COLOR_DRAWER_VERTEX_SHADER_PATH "shaders/colorDrawer.vert"
#define COLOR_DRAWER_FRAGMENT_SHADER_PATH "shaders/colorDrawer.frag"

#define LIGHT_VERTEX_SHADER_PATH "shaders/lightDrawer.vert"
#define LIGHT_FRAGMENT_SHADER_PATH "shaders/lightDrawer.frag"


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
    void setFillCuboidData(const Cuboid & cuboid);
    void setFillSphereData(
        const Sphere & sphere, 
        const ColorRGB & color, 
        unsigned int stacks, unsigned int slices
    );
    void setFillSphereData(
        const Sphere & sphere, 
        unsigned int stacks, 
        unsigned int slices
    );
    void draw(const Matrix4D & model = Matrix4D(1.0f));    
    void fill(const Matrix4D & model = Matrix4D(1.0f));
    void drawLight(const Matrix4D & model = Matrix4D(1.0f));
public:
    class ColorDrawerShader : public Shader {
    public:
        ColorDrawerShader();
    };
    class LightShader : public Shader {
    public:
        LightShader();
    };
private:
    static std::weak_ptr<ColorDrawerShader> _uniqueColorShader;
    static std::weak_ptr<LightShader> _uniqueLightShader;
    std::shared_ptr<ColorDrawerShader> _shaderColor;
    std::shared_ptr<LightShader> _shaderLight;
    VertexArrayObject _vaos[6];
};

}

#endif
