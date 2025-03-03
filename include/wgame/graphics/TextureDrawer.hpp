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

#include <memory>
 
#define TEXTURE_DRAWER_VERTEX_SHADER_PATH "shaders/textureDrawer.vert"
#define TEXTURE_DRAWER_FRAGMENT_SHADER_PATH "shaders/textureDrawer.frag"

#define PARALLAX_DRAWER_VERTEX_SHADER_PATH "shaders/parallaxMapping.vert"
#define PARALLAX_DRAWER_FRAGMENT_SHADER_PATH "shaders/parallaxMapping.frag"

#define DEFAULT_HEIGHT_SCALE_PARALLAX 0.1f
 
 
namespace wgame {
 
class TextureDrawer {
public:
    TextureDrawer();
    void setCuboidData(
        const Cuboid & cuboid, 
        const std::vector<std::vector<Vector2D>> & texCoords
    );
    void draw(const std::vector<Texture2D *> & textures);
    void draw(
        const std::vector<Texture2D *> & diffuses,
        const std::vector<Texture2D *> & normals,
        const std::vector<Texture2D *> & heights,
        float heightScale = DEFAULT_HEIGHT_SCALE_PARALLAX
    );
public:
    class TextureDrawerShader : public Shader {
    public:
        TextureDrawerShader();
    };
    class ParallaxDrawerShader : public Shader {
    public:
        ParallaxDrawerShader();
    };
private:
    static std::weak_ptr<TextureDrawerShader> _uniqueTextureShader;
    static std::weak_ptr<ParallaxDrawerShader> _uniqueParallaxShader;
    std::shared_ptr<TextureDrawerShader> _textureShader;
    std::shared_ptr<ParallaxDrawerShader> _parallalShader;
    VertexArrayObject _vaos[6];
};
 
}
 
#endif
 