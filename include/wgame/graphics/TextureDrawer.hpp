/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_TEXTURE_DRAWER_H__
#define __WG_TEXTURE_DRAWER_H__
 
#include "../opengl/VertexArrayObject.hpp"
#include "../opengl/Shader.hpp"
#include "../opengl/Texture2D.hpp"
#include "../geometry/Cuboid.hpp"
 
#define TEXTURE_DRAWER_VERTEX_SHADER_PATH "shaders/textureDrawer.vert"
#define TEXTURE_DRAWER_FRAGMENT_SHADER_PATH "shaders/textureDrawer.frag"
 
 
namespace wgame {
 
class TextureDrawer {
public:
    void setCuboidData(const Cuboid & cuboid);
    void setTexCoordFixed(const Cuboid & cuboid, const Vector2D & size);
    void setTexCoordFlex(const Vector2D & uvScale);
    void drawCuboid(const Cuboid & cuboid, const Texture2D & texture);
    void draw(const Texture2D & texture);
protected:
    class TextureDrawerShader : public Shader {
    public:
        TextureDrawerShader();
    };
private:
    TextureDrawerShader _shader;
    VertexArrayObject _vao;
};
 
}
 
#endif
 