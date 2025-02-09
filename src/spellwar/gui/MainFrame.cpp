/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/gui/MainFrame.hpp>
#include <iostream>

MainFrame::MainFrame(const char * title, const Size & size) :
    AbstractFrame(title, size) {
    setBackgroundColor(255, 255, 255);
}

void MainFrame::renderScene() {
    VertexArrayObject vao;
    std::vector<Point2D> coord = {
        {0.0f, 0.75f},
        {0.75f, -0.75f},
        {-0.75f, -0.75f}
    };

    std::vector<Point3D> color = {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 0.0f}
    };

    std::vector<unsigned> indexs = {
        0, 1, 2
    };
    Shader shader;
    displaySprites();
    vao.setEBO(indexs);
    vao.setVBO(VBO_COORD, coord);
    vao.setVBO(VBO_COLOR, color);
    shader.bind();
    vao.draw(DRAW_TRIANGLES);
    shader.unbind();
}

void MainFrame::renderHUD() {
}

