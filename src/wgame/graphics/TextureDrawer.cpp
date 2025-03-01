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

void TextureDrawer::setCuboidData(
    const Cuboid & cuboid, 
    const std::vector<std::vector<Vector2D>> & texCoords
) {
    std::vector<std::vector<Point3D>> vertices = cuboid.getVerticesPerFace();
    std::vector<std::vector<Vector3D>> normals = cuboid.getNormalsPerFace();
    std::vector<std::vector<unsigned>> elements = cuboid.getElementsPerFace();
    for (int i = 0; i < 6; i ++) {
        _vaos[i].setVBO(VBO_VERTEX, vertices[i]);
        _vaos[i].setVBO(VBO_NORMAL, normals[i]);
        _vaos[i].setVBO(VBO_TEXCOORD_0, texCoords[i]);
        _vaos[i].setEBO(elements[i]);
    }
}

void TextureDrawer::draw(const std::vector<Texture2D *> & textures) {
    _shader -> bind();    
    _shader -> setUniform("hasHeight", false);
    _shader -> setUniform("colorSampler", 0);
    glActiveTexture(GL_TEXTURE0);  
    for (int i = 0; i < 6; i ++) {              
        textures[i] -> bind();
        _vaos[i].draw(DRAW_TRIANGLES);
        textures[i] -> unbind();
    }
    _shader -> unbind();
}
 
TextureDrawer::TextureDrawerShader::TextureDrawerShader() : 
Shader(TEXTURE_DRAWER_VERTEX_SHADER_PATH, TEXTURE_DRAWER_FRAGMENT_SHADER_PATH) {}
 
}
 
 