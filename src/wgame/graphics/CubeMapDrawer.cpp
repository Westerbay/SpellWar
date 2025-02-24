/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/graphics/CubeMapDrawer.hpp>


namespace wgame {

std::weak_ptr<CubeMapDrawer::CubeMapDrawerShader> CubeMapDrawer::_uniqueShader;

CubeMapDrawer::CubeMapDrawer() {

    _shader = _uniqueShader.lock();
    if (!_shader) {
        _shader = std::make_shared<CubeMapDrawerShader>();
        _uniqueShader = _shader;
    }

    _cube = Cuboid(Point3D(0.0f), Vector3D(2.0f, 2.0f, 2.0f));
    _texture.setType(TEXTURE_CUBE_MAP);
    _texture.setInterpolationMode(INTERPOLATION_LINEAR);
    _texture.setParameter(TEXTURE_WRAP_S, CLAMP_TO_EDGE);
    _texture.setParameter(TEXTURE_WRAP_T, CLAMP_TO_EDGE);
    _texture.setParameter(TEXTURE_WRAP_R, CLAMP_TO_EDGE);

    std::vector<unsigned> elements = {
        0, 2, 1, 0, 3, 2,  
        4, 5, 6, 4, 6, 7,  
        8, 9, 10, 8, 10, 11,  
        12, 14, 13, 12, 15, 14,  
        16, 18, 17, 16, 19, 18,  
        20, 21, 22, 20, 22, 23   
    };
    _vao.setEBO(elements);
    _vao.setVBO(VBO_VERTEX, _cube.getVertices());
}

void CubeMapDrawer::setFaces(
    const Image & imagePositiveX,
    const Image & imageNegativeX,
    const Image & imagePositiveY,
    const Image & imageNegativeY,
    const Image & imagePositiveZ,
    const Image & imageNegativeZ
) {
    _texture.setData(imagePositiveX, TEXTURE_CUBE_MAP_POSITIVE_X, false);
    _texture.setData(imageNegativeX, TEXTURE_CUBE_MAP_NEGATIVE_X, false);
    _texture.setData(imagePositiveY, TEXTURE_CUBE_MAP_POSITIVE_Y, false);
    _texture.setData(imageNegativeY, TEXTURE_CUBE_MAP_NEGATIVE_Y, false);
    _texture.setData(imagePositiveZ, TEXTURE_CUBE_MAP_POSITIVE_Z, false);
    _texture.setData(imageNegativeZ, TEXTURE_CUBE_MAP_NEGATIVE_Z, false);
}

void CubeMapDrawer::draw() const {
    _shader -> bind();
    glActiveTexture(GL_TEXTURE0);
    _texture.bind();
    _shader -> setUniform("skybox", 0);
    _vao.draw(DRAW_TRIANGLES);
    _texture.unbind();
    _shader -> unbind();
}

CubeMapDrawer::CubeMapDrawerShader::CubeMapDrawerShader() 
: Shader(CUBEMAP_VERTEX_SHADER, CUBEMAP_FRAGMENT_SHADER) {}

}
