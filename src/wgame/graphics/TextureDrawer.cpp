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
    std::vector<std::vector<Vector3D>> tangents = cuboid.getTangentsPerFace();
    std::vector<std::vector<unsigned>> elements = cuboid.getElementsPerFace();
    vaos.resize(6);
    for (size_t i = 0; i < vaos.size(); i ++) {
        vaos[i].setVBO(VBO_VERTEX, vertices[i]);
        vaos[i].setVBO(VBO_NORMAL, normals[i]);
        vaos[i].setVBO(VBO_TEXCOORD_0, texCoords[i]);
        vaos[i].setVBO(VBO_TANGENTS, tangents[i]);
        vaos[i].setEBO(elements[i]);
    }
}

void TextureDrawer::draw(
    const std::vector<Texture2D *> & textures, 
    const Matrix4D & model, 
    Mode mode
) {
    _shader -> bind();    
    _shader -> setUniform("model", model);
    _shader -> setUniform("activeLight", activeLight);
    _shader -> setUniform("drawMode", (int) mode);
    _shader -> setUniform("drawInstanced", false);
    _shader -> setUniform("diffuseMap", 0);
    _shader -> setUniform("activeParallaxMapping", false); 
    glActiveTexture(GL_TEXTURE0);  
    for (size_t i = 0; i < vaos.size(); i ++) {              
        textures[i] -> bind();
        vaos[i].draw(DRAW_TRIANGLES);
        textures[i] -> unbind();
    }
    _shader -> unbind();
}

void TextureDrawer::draw(
    const std::vector<Texture2D *> & diffuses,
    const std::vector<Texture2D *> & normals,
    const std::vector<Texture2D *> & heights,
    float heightScale,
    const Matrix4D & model, 
    Mode mode
) {
    _shader -> bind();  
    _shader -> setUniform("model", model);
    _shader -> setUniform("activeLight", activeLight);
    _shader -> setUniform("drawMode", (int) mode);
    _shader -> setUniform("drawInstanced", false);
    _shader -> setUniform("activeParallaxMapping", true);  
    _shader -> setUniform("diffuseMap", 0);  
    _shader -> setUniform("normalMap", 1);
    _shader -> setUniform("depthMap", 2);   
    _shader -> setUniform("heightScale", heightScale);  
    _shader -> setUniform("model", Matrix4D(1.0f));
    for (size_t i = 0; i < vaos.size(); i ++) {    
        glActiveTexture(GL_TEXTURE0);                
        diffuses[i] -> bind();
        glActiveTexture(GL_TEXTURE1);                   
        normals[i] -> bind();
        glActiveTexture(GL_TEXTURE2);                
        heights[i] -> bind();
        vaos[i].draw(DRAW_TRIANGLES);
        heights[i] -> unbind();
        normals[i] -> unbind();
        diffuses[i] -> unbind();
    }
    _shader -> unbind();
}
 
TextureDrawer::TextureDrawerShader::TextureDrawerShader() : 
Shader(TEXTURE_DRAWER_VERTEX_SHADER_PATH, TEXTURE_DRAWER_FRAGMENT_SHADER_PATH) {}
 
}
 
 