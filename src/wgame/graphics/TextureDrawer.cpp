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

void TextureDrawer::setCuboidDataWithSplit(
    const Cuboid & cuboid, 
    const std::vector<std::vector<Vector2D>> & texCoords,
    const Size & split
) {
    std::vector<std::vector<Point3D>> vertices = cuboid.getVerticesPerFace();
    std::vector<std::vector<Vector3D>> normals = cuboid.getNormalsPerFace();
    std::vector<std::vector<unsigned>> elements = cuboid.getElementsPerFace();
    
    for (int i = 0; i < 6; i ++) {
        std::vector<Point3D> verticesSplit;
        std::vector<Vector3D> normalsSplit;
        std::vector<Vector2D> texCoordsSplit;
        std::vector<unsigned> elementsSplit;

        const std::vector<Point3D> & verticesInFace = vertices[i];
        const std::vector<Vector3D> & normalsInFace = normals[i];
        const std::vector<Vector2D> & texCoordsInFace = texCoords[i];
        const std::vector<unsigned> & elementsInFace = elements[i];

        Vector3D width = verticesInFace[1] - verticesInFace[0];
        Vector3D height = verticesInFace[3] - verticesInFace[0];
        Vector3D widthSplit = width / (float) split.width;
        Vector3D heightSplit = height / (float) split.height;

        Vector2D texSizeX = texCoordsInFace[1] - texCoordsInFace[0];
        Vector2D texSizeY = texCoordsInFace[3] - texCoordsInFace[0];
        Vector2D texSizeXSplit = texSizeX / (float) split.width;
        Vector2D texSizeYSplit = texSizeY / (float) split.height;

        unsigned index = 0;
        for (float y = 0; y < (float) split.height; y ++) { 
            for (float x = 0; x < (float) split.width; x ++) {
                Point3D A = verticesInFace[0] + heightSplit * y + widthSplit * x;
                Point3D D = verticesInFace[0] + heightSplit * (y + 1) + widthSplit * x;
                Point3D B = A + widthSplit;
                Point3D C = D + widthSplit;
                verticesSplit.push_back(A);
                verticesSplit.push_back(B);
                verticesSplit.push_back(C);
                verticesSplit.push_back(D);
                for (int k = 0; k < 4; k ++) {
                    normalsSplit.push_back(normalsInFace[0]);
                }
                texCoordsSplit.push_back(texCoordsInFace[0] + texSizeYSplit * y + texSizeXSplit * x);
                texCoordsSplit.push_back(texCoordsInFace[0] + texSizeYSplit * y + texSizeXSplit * (x + 1));
                texCoordsSplit.push_back(texCoordsInFace[0] + texSizeYSplit * (y + 1) + texSizeXSplit * (x + 1));
                texCoordsSplit.push_back(texCoordsInFace[0] + texSizeYSplit * (y + 1) + texSizeXSplit * x);
                
                elementsSplit.push_back(index);
                elementsSplit.push_back(index + 1);
                elementsSplit.push_back(index + 2);

                elementsSplit.push_back(index);
                elementsSplit.push_back(index + 2);
                elementsSplit.push_back(index + 3);

                index += 4;
            }
        }

        _vaos[i].setVBO(VBO_VERTEX, verticesSplit);
        _vaos[i].setVBO(VBO_NORMAL, normalsSplit);
        _vaos[i].setVBO(VBO_TEXCOORD_0, texCoordsSplit);
        _vaos[i].setEBO(elementsSplit);
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

void TextureDrawer::drawHeight(
    const std::vector<Texture2D *> & textures, 
    const std::vector<Texture2D *> & heights
) {
    _shader -> bind();    
    _shader -> setUniform("colorSampler", 0);
    _shader -> setUniform("heightSampler", 1);
    _shader -> setUniform("hasHeight", true);
    for (int i = 0; i < 6; i ++) {
        glActiveTexture(GL_TEXTURE0);
        textures[i] -> bind();
        glActiveTexture(GL_TEXTURE1);
        heights[i] -> bind();
        _vaos[i].draw(DRAW_TRIANGLES);
        textures[i] -> unbind();
        heights[i] -> unbind();
    }
    _shader -> unbind();
}
 
TextureDrawer::TextureDrawerShader::TextureDrawerShader() : 
Shader(TEXTURE_DRAWER_VERTEX_SHADER_PATH, TEXTURE_DRAWER_FRAGMENT_SHADER_PATH) {}
 
}
 
 