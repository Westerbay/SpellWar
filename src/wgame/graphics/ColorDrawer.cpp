/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/graphics/ColorDrawer.hpp>


namespace wgame {

void ColorDrawer::drawCuboid(const Cuboid & cuboid, const ColorRGB & color) {
    _shader.bind();
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
    _vao.draw(DRAW_LINES);
    _shader.unbind();
}

void ColorDrawer::fillCuboid(const Cuboid & cuboid, const ColorRGB & color) {
    _shader.bind();
    std::vector<Point3D> vertices = cuboid.getVertices();
    std::vector<ColorRGB> colors = {
        color, color, color, color,
        color, color, color, color
    };
    std::vector<unsigned> elements = {
        0, 1, 2, 0, 2, 3,
        4, 7, 6, 4, 6, 5,
        1, 5, 6, 1, 6, 2,
        0, 4, 5, 0, 5, 1,
        0, 3, 7, 0, 7, 4,
        3, 2, 6, 3, 6, 7, 
    };
    _vao.setEBO(elements);
    _vao.setVBO(VBO_VERTEX, vertices);
    _vao.setVBO(VBO_COLOR, colors);
    _vao.draw(DRAW_TRIANGLES);
    _shader.unbind();
}

ColorDrawer::ColorDrawerShader::ColorDrawerShader() : 
Shader(COLOR_DRAWER_VERTEX_SHADER_PATH, COLOR_DRAWER_FRAGMENT_SHADER_PATH) {}

}

