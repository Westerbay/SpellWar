/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/graphics/TextureDrawer.hpp>


namespace wgame {

std::weak_ptr<TextureDrawer::TextureDrawerShader> TextureDrawer::_uniqueTextureShader;
std::weak_ptr<TextureDrawer::ParallaxDrawerShader> TextureDrawer::_uniqueParallaxShader;

TextureDrawer::TextureDrawer() {
    _textureShader = _uniqueTextureShader.lock();
    if (!_textureShader) {
        _textureShader = std::make_shared<TextureDrawerShader>();
        _uniqueTextureShader = _textureShader;
    }

    _parallalShader = _uniqueParallaxShader.lock();
    if (!_parallalShader) {
        _parallalShader = std::make_shared<ParallaxDrawerShader>();
        _uniqueParallaxShader = _parallalShader;
    }
}

void TextureDrawer::setCuboidData(
    const Cuboid & cuboid, 
    const std::vector<std::vector<Vector2D>> & texCoords
) {
    std::vector<std::vector<Point3D>> vertices = cuboid.getVerticesPerFace();
    std::vector<std::vector<Vector3D>> normals = cuboid.getNormalsPerFace();
    std::vector<std::vector<Vector3D>> tangents = cuboid.getTangentsPerFace();
    std::vector<std::vector<unsigned>> elements = cuboid.getElementsPerFace();
    for (int i = 0; i < 6; i ++) {
        _vaos[i].setVBO(VBO_VERTEX, vertices[i]);
        _vaos[i].setVBO(VBO_NORMAL, normals[i]);
        _vaos[i].setVBO(VBO_TEXCOORD_0, texCoords[i]);
        _vaos[i].setVBO(VBO_TANGENTS, tangents[i]);
        _vaos[i].setEBO(elements[i]);
    }
}

void TextureDrawer::draw(const std::vector<Texture2D *> & textures) {
    _textureShader -> bind();    
    _textureShader -> setUniform("colorSampler", 0);
    glActiveTexture(GL_TEXTURE0);  
    for (int i = 0; i < 6; i ++) {              
        textures[i] -> bind();
        _vaos[i].draw(DRAW_TRIANGLES);
        textures[i] -> unbind();
    }
    _textureShader -> unbind();
}

void TextureDrawer::draw(
    const std::vector<Texture2D *> & diffuses,
    const std::vector<Texture2D *> & normals,
    const std::vector<Texture2D *> & heights,
    float heightScale
) {
    _parallalShader -> bind();  
    _parallalShader -> setUniform("diffuseMap", 0);  
    _parallalShader -> setUniform("normalMap", 1);
    _parallalShader -> setUniform("depthMap", 2);   
    _parallalShader -> setUniform("heightScale", heightScale);  
    _parallalShader -> setUniform("model", Matrix4D(1.0f));
    for (int i = 0; i < 6; i ++) {    
        glActiveTexture(GL_TEXTURE0);                
        diffuses[i] -> bind();
        glActiveTexture(GL_TEXTURE1);                   
        normals[i] -> bind();
        glActiveTexture(GL_TEXTURE2);                
        heights[i] -> bind();
        _vaos[i].draw(DRAW_TRIANGLES);
        heights[i] -> unbind();
        normals[i] -> unbind();
        diffuses[i] -> unbind();
    }
    _parallalShader -> unbind();
}
 
TextureDrawer::TextureDrawerShader::TextureDrawerShader() : 
Shader(TEXTURE_DRAWER_VERTEX_SHADER_PATH, TEXTURE_DRAWER_FRAGMENT_SHADER_PATH) {}
 
TextureDrawer::ParallaxDrawerShader::ParallaxDrawerShader() :
Shader(PARALLAX_DRAWER_VERTEX_SHADER_PATH, PARALLAX_DRAWER_FRAGMENT_SHADER_PATH) {}

}
 
 