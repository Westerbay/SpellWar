/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/gui/ColorDrawer.hpp>


namespace wgame {

void ColorDrawer::drawCuboid(const Cuboid & cuboid, const ColorRGB & color) {
    _shader.bind();
    std::vector<Point3D> vertices = cuboid.getVertices();
    std::vector<ColorRGB> colors = {
        color, color, color, color,
        color, color, color, color
    };
    std::vector<unsigned> elements = {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 4, 6, 7,
        1, 5, 6, 1, 6, 2,
        0, 1, 5, 0, 5, 4,
        0, 4, 7, 0, 7, 3,
        3, 2, 6, 3, 6, 7, 
    };
    _vao.setEBO(elements);
    _vao.setVBO(VBO_VERTEX, vertices);
    _vao.setVBO(VBO_COLOR, colors);
    _vao.draw(DRAW_TRIANGLES);
    _shader.unbind();
}

}

