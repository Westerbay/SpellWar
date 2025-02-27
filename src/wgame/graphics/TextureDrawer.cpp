/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/graphics/TextureDrawer.hpp>


namespace wgame {

std::weak_ptr<TextureDrawer::TextureDrawerShader> TextureDrawer::_uniqueShader;
 
TextureDrawer::TextureDrawer() {
    _shader = _uniqueShader.lock();
    if (!_shader) {
        _shader = std::make_shared<TextureDrawerShader>();
        _uniqueShader = _shader;
    }
}

void TextureDrawer::setCuboidData(const Cuboid & cuboid) {
    _shader -> bind();
    _shader -> setUniform("colorSampler", 0);
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
        0, 2, 1,  0, 3, 2,  
        4, 5, 6,  4, 6, 7,  
        8, 9, 10,  8, 10, 11,  
        12, 14, 13,  12, 15, 14,  
        16, 18, 17,  16, 19, 18,  
        20, 21, 22,  20, 22, 23   
    };
     
    _vao.setEBO(elements);
    _vao.setVBO(VBO_VERTEX, vertices);
    _vao.setVBO(VBO_TEXCOORD_0, texCoords);
    _vao.setVBO(VBO_NORMAL, cuboid.getNormals());
    _shader -> unbind();
}

void TextureDrawer::setTexCoordFixed(const Cuboid & cuboid, const Vector2D & size) {
    std::vector<Point2D> texCoords;
    std::vector<Vector2D> faceSizes = {
        {cuboid.size.x, cuboid.size.y}, 
        {cuboid.size.x, cuboid.size.y}, 
        {cuboid.size.x, cuboid.size.z}, 
        {cuboid.size.z, cuboid.size.y}, 
        {cuboid.size.x, cuboid.size.z}, 
        {cuboid.size.z, cuboid.size.y}  
    };
    for (const Vector2D & faceSize : faceSizes) {
        float widthFace = faceSize.x;
        float heightFace = faceSize.y;
        texCoords.push_back({0.0f, 0.0f});
        texCoords.push_back({widthFace / size.x, 0.0f});
        texCoords.push_back({widthFace / size.x, heightFace / size.y});
        texCoords.push_back({0.0f, heightFace / size.y});
    }
    _vao.setVBO(VBO_TEXCOORD_0, texCoords);
}

void TextureDrawer::setTexCoordFlex(const Vector2D & uvScale) {
    std::vector<Point2D> texCoords = {
        {0, 0}, {uvScale.x, 0}, {uvScale.x, uvScale.y}, {0, uvScale.y}, 
        {0, 0}, {uvScale.x, 0}, {uvScale.x, uvScale.y}, {0, uvScale.y},
        {0, 0}, {uvScale.x, 0}, {uvScale.x, uvScale.y}, {0, uvScale.y},
        {0, 0}, {uvScale.x, 0}, {uvScale.x, uvScale.y}, {0, uvScale.y},
        {0, 0}, {uvScale.x, 0}, {uvScale.x, uvScale.y}, {0, uvScale.y},
        {0, 0}, {uvScale.x, 0}, {uvScale.x, uvScale.y}, {0, uvScale.y}
    };
    _vao.setVBO(VBO_TEXCOORD_0, texCoords);
}

void TextureDrawer::drawCuboid(const Cuboid & cuboid, const Texture2D & texture) {
    setCuboidData(cuboid);
    draw(texture);
}

void TextureDrawer::draw(const Texture2D & texture) {
    _shader -> bind();
    texture.bind();
    _vao.draw(DRAW_TRIANGLES);
    texture.unbind();
    _shader -> unbind();
}
 
TextureDrawer::TextureDrawerShader::TextureDrawerShader() : 
Shader(TEXTURE_DRAWER_VERTEX_SHADER_PATH, TEXTURE_DRAWER_FRAGMENT_SHADER_PATH) {}
 
}
 
 