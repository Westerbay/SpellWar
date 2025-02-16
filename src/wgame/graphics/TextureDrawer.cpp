/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/graphics/TextureDrawer.hpp>


namespace wgame {
 
void TextureDrawer::setDrawCuboidData(const Cuboid & cuboid) {
    _shader.bind();
    _shader.setUniform("colorSampler", 0);
    std::vector<Point3D> vertices = cuboid.getVertices();
    std::vector<Point2D> texCoords = {
        {0, 0}, {1, 0}, {1, 1}, {0, 1}, 
        {0, 0}, {1, 0}, {1, 1}, {0, 1},
        {0, 0}, {1, 0}, {1, 1}, {0, 1},
        {0, 0}, {1, 0}, {1, 1}, {0, 1},
        {0, 0}, {1, 0}, {1, 1}, {0, 1},
        {0, 0}, {1, 0}, {1, 1}, {0, 1}
    };
    std::vector<unsigned> elements = {
        0, 1, 2, 0, 2, 3, 
        4, 6, 5, 4, 7, 6, 
        8, 10, 9, 8, 11, 10, 
        12, 14, 13, 12, 15, 14, 
        16, 18, 17, 16, 19, 18, 
        20, 22, 21, 20, 23, 22
    };    
    _vao.setEBO(elements);
    _vao.setVBO(VBO_VERTEX, vertices);
    _vao.setVBO(VBO_TEXCOORD, texCoords);
    _shader.unbind();
}

void TextureDrawer::drawCuboid(const Cuboid & cuboid, const Texture2D & texture) {
    setDrawCuboidData(cuboid);
    draw(texture);
}

void TextureDrawer::draw(const Texture2D & texture) {
    _shader.bind();
    texture.bind();
    _vao.draw(DRAW_TRIANGLES);
    texture.unbind();
    _shader.unbind();
}
 
TextureDrawer::TextureDrawerShader::TextureDrawerShader() : 
Shader(TEXTURE_DRAWER_VERTEX_SHADER_PATH, TEXTURE_DRAWER_FRAGMENT_SHADER_PATH) {}
 
}
 
 