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

void ColorDrawer::setDrawCuboidData(const Cuboid & cuboid, const ColorRGBA & color) {
    vaos.resize(1);
    std::vector<Point3D> vertices = cuboid.getVertices();
    std::vector<ColorRGBA> colors = {
        color, color, color, color,
        color, color, color, color
    };
    std::vector<unsigned> elements = {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4, 
        1, 5, 2, 6, 0, 4, 3, 7        
    };
    vaos[0].setEBO(elements);
    vaos[0].setVBO(VBO_VERTEX, vertices);
    vaos[0].setVBO(VBO_COLOR, colors);
}

void ColorDrawer::setFillCuboidData(
    const Cuboid & cuboid, 
    const std::vector<ColorRGBA> & colors
) {
    setFillCuboidData(cuboid);
    for (int i = 0; i < 6; i ++) {
        std::vector<ColorRGBA> vboColors = {colors[i], colors[i], colors[i], colors[i]};
        vaos[i].setVBO(VBO_COLOR, vboColors);
    }
}

void ColorDrawer::setFillCuboidData(
    const Cuboid & cuboid, 
    const std::vector<std::vector<ColorRGBA>> & colors
) {
    setFillCuboidData(cuboid);
    for (int i = 0; i < 6; i ++) {
        std::vector<ColorRGBA> vboColors = {colors[i][0], colors[i][1], colors[i][2], colors[i][3]};
        vaos[i].setVBO(VBO_COLOR, vboColors);
    }
}

void ColorDrawer::setFillSphereData(
    const Sphere & sphere, 
    const ColorRGBA & color, 
    unsigned int stacks, unsigned int slices
) {
    std::vector<Point3D> vertices;
    std::vector<Vector3D> normals;
    std::vector<unsigned> elements;

    sphere.generateSphere(elements, normals, vertices, stacks, slices);
    std::vector<ColorRGBA> colors(vertices.size(), color);

    vaos.resize(1);
    vaos[0].setEBO(elements);
    vaos[0].setVBO(VBO_VERTEX, vertices);
    vaos[0].setVBO(VBO_NORMAL, normals);
    vaos[0].setVBO(VBO_COLOR, colors);
}

void ColorDrawer::setFillCuboidData(const Cuboid & cuboid) {
    std::vector<std::vector<Point3D>> vertices = cuboid.getVerticesPerFace();
    std::vector<std::vector<Vector3D>> normals = cuboid.getNormalsPerFace();
    std::vector<std::vector<unsigned>> elements = cuboid.getElementsPerFace();    
    vaos.resize(6);
    for (int i = 0; i < 6; i ++) {
        vaos[i].setVBO(VBO_VERTEX, vertices[i]);
        vaos[i].setVBO(VBO_NORMAL, normals[i]);
        vaos[i].setEBO(elements[i]);
    }
}

void ColorDrawer::setFillCircleData(
    const Circle & circle, 
    const ColorRGBA & color, 
    unsigned int segments
) {
    std::vector<Point3D> vertices;
    std::vector<Vector3D> normals;
    std::vector<unsigned> elements;

    circle.generateCircle(elements, normals, vertices, segments);
    std::vector<ColorRGBA> colors(vertices.size(), color);

    vaos.resize(1);
    vaos[0].setEBO(elements);
    vaos[0].setVBO(VBO_VERTEX, vertices);
    vaos[0].setVBO(VBO_NORMAL, normals);
    vaos[0].setVBO(VBO_COLOR, colors);
}

void ColorDrawer::draw(const Matrix4D & model, Mode mode) {
    _shader -> bind();
    _shader -> setUniform("model", model);
    _shader -> setUniform("activeLight", activeLight);
    _shader -> setUniform("drawMode", (int) mode);
    _shader -> setUniform("drawInstanced", false);
    vaos[0].draw(DRAW_LINES);
    _shader -> unbind();
}

void ColorDrawer::fill(const Matrix4D & model, Mode mode) {
    _shader -> bind();
    _shader -> setUniform("model", model);
    _shader -> setUniform("activeLight", activeLight);
    _shader -> setUniform("drawMode", (int) mode);
    _shader -> setUniform("drawInstanced", false);
    for (VertexArrayObject & vao: vaos) {
        vao.draw(DRAW_TRIANGLES);
    }  
    _shader -> unbind();
}

ColorDrawer::ColorDrawerShader::ColorDrawerShader() : 
Shader(COLOR_DRAWER_VERTEX_SHADER_PATH, COLOR_DRAWER_FRAGMENT_SHADER_PATH) {}

}

