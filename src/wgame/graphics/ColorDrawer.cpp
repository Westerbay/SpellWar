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
    _vao.setEBO(elements);
    _vao.setVBO(VBO_VERTEX, vertices);
    _vao.setVBO(VBO_COLOR, colors);
}

void ColorDrawer::setFillCuboidData(const Cuboid & cuboid, const ColorRGB & color) {
    std::vector<Point3D> vertices = cuboid.getVertices();
    std::vector<ColorRGB> colors;
    for (size_t i = 0; i < vertices.size(); i ++) {
        colors.push_back(color);
    }
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
    _vao.setVBO(VBO_COLOR, colors);
}

void ColorDrawer::drawCuboid(const Cuboid & cuboid, const ColorRGB & color) {
    setDrawCuboidData(cuboid, color);
    draw();
}

void ColorDrawer::fillCuboid(const Cuboid & cuboid, const ColorRGB & color) {
    setFillCuboidData(cuboid, color);
    fill();
}

void ColorDrawer::draw() {
    _shader -> bind();
    _vao.draw(DRAW_LINES);
    _shader -> unbind();
}

void ColorDrawer::fill() {
    _shader -> bind();
    _vao.draw(DRAW_TRIANGLES);
    _shader -> unbind();
}

ColorDrawer::ColorDrawerShader::ColorDrawerShader() : 
Shader(COLOR_DRAWER_VERTEX_SHADER_PATH, COLOR_DRAWER_FRAGMENT_SHADER_PATH) {}

}

