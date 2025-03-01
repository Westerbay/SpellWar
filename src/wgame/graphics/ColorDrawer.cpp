/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/graphics/ColorDrawer.hpp>


namespace wgame {

std::weak_ptr<ColorDrawer::ColorDrawerShader> ColorDrawer::_uniqueShader;

ColorDrawer::ColorDrawer() {
    _shader = _uniqueShader.lock();
    if (!_shader) {
        _shader = std::make_shared<ColorDrawerShader>();
        _uniqueShader = _shader;
    }
}

void ColorDrawer::setDrawCuboidData(const Cuboid & cuboid, const ColorRGB & color) {
    std::vector<Point3D> vertices = cuboid.getVertices();
    std::vector<ColorRGB> colors = {
        color, color, color, color,
        color, color, color, color
    };
    std::vector<unsigned> elements = {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4, 
        1, 5, 2, 6, 0, 4, 3, 7        
    };
    _vaos[0].setEBO(elements);
    _vaos[0].setVBO(VBO_VERTEX, vertices);
    _vaos[0].setVBO(VBO_COLOR, colors);
}

void ColorDrawer::setFillCuboidData(
    const Cuboid & cuboid, 
    const std::vector<ColorRGB> & colors
) {
    std::vector<std::vector<Point3D>> vertices = cuboid.getVerticesPerFace();
    std::vector<std::vector<Vector3D>> normals = cuboid.getNormalsPerFace();
    std::vector<std::vector<unsigned>> elements = cuboid.getElementsPerFace();    
    for (int i = 0; i < 6; i ++) {
        std::vector<Vector3D> vboColors = {colors[i], colors[i], colors[i], colors[i]};
        _vaos[i].setVBO(VBO_VERTEX, vertices[i]);
        _vaos[i].setVBO(VBO_NORMAL, normals[i]);
        _vaos[i].setVBO(VBO_COLOR, vboColors);
        _vaos[i].setEBO(elements[i]);
    }
}

void ColorDrawer::draw() {
    _shader -> bind();
    _vaos[0].draw(DRAW_LINES);
    _shader -> unbind();
}

void ColorDrawer::fill() {
    _shader -> bind();
    for (VertexArrayObject & vao: _vaos) {
        vao.draw(DRAW_TRIANGLES);
    }  
    _shader -> unbind();
}

ColorDrawer::ColorDrawerShader::ColorDrawerShader() : 
Shader(COLOR_DRAWER_VERTEX_SHADER_PATH, COLOR_DRAWER_FRAGMENT_SHADER_PATH) {}

}

