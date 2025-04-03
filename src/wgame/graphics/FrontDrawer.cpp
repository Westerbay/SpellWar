/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/graphics/FontDrawer.hpp>


namespace wgame {

std::weak_ptr<FontDrawer::FontDrawerShader> FontDrawer::_uniqueShader;

FontDrawer::FontDrawer() : Drawer() {
	setActiveLight(false);	
	_shader = _uniqueShader.lock();
    if (!_shader) {
        _shader = std::make_shared<FontDrawerShader>();
        _uniqueShader = _shader;
    }
	vaos.resize(1);
}

void FontDrawer::setTextData(
	const Font & font, const String & text, 
	const Point3D & position
) {

	_texture.setData(font);
	_texture.setInterpolationMode(INTERPOLATION_NEAREST);

	_color = font.getColor();
	_fillColor = font.getFillColor();
	
	std::vector<Point3D> vertices;
	std::vector<Point2D> uvs;
	std::vector<unsigned> ebo;

	float x = position.x;
	float y = position.y;
	float z = position.z;
	unsigned k = 0;
	float ratioWH = font.getRowCharacterNumber() / (float) font.getColumnCharacterNumber();
	for (unsigned char c : text) {
		Point3D pos[4] = {
			Point3D(x, y, z), 
			Point3D(x + font.getSize(), y, z), 
			Point3D(x + font.getSize(), y + font.getSize() * ratioWH, z), 
			Point3D(x, y + font.getSize() * ratioWH, z)
		};
		Point2D uv[4] = {
			toUV(font, c, 0, 0), toUV(font, c, 1, 0), 
			toUV(font, c, 1, 1), toUV(font, c, 0, 1)
		};
		unsigned square[6] = {k, k + 2, k + 1, k, k + 3, k + 2};
		ebo.insert(ebo.end(), square, square + 6);
		vertices.insert(vertices.end(), pos, pos + 4);
		uvs.insert(uvs.end(), uv, uv + 4);
		x += font.getSize();
		k += 4;
	}
	vaos.front().setEBO(ebo);
	vaos.front().setVBO(VBO_VERTEX, vertices);
	vaos.front().setVBO(VBO_TEXCOORD_0, uvs);
}

void FontDrawer::draw(const Matrix4D & model, Mode mode) {
	_shader -> bind();

    _shader -> setUniform("model", model);
    _shader -> setUniform("activeLight", activeLight);
    _shader -> setUniform("drawMode", (int) mode);
    _shader -> setUniform("drawInstanced", false);
	_shader -> setUniform("fontSampler", 0);

	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	
	_shader -> setUniform("fontColor", _color);
	_shader -> setUniform("fillColor", _fillColor);
	vaos.front().draw(DRAW_TRIANGLES);

	_texture.unbind();
    _shader -> unbind();
}

Point2D FontDrawer::toUV(
	const Font & font, unsigned char character,
	unsigned char xOff, unsigned char yOff
) {
	unsigned char refChar = font.getReferencedCharacter();
	character -= refChar;
	unsigned char nbCharRow = font.getRowCharacterNumber();
	Point2D uv = Point2D(character % nbCharRow + xOff, character / nbCharRow + yOff);
	uv.x /= nbCharRow;
	uv.y /= font.getColumnCharacterNumber();
	return uv;
}

FontDrawer::FontDrawerShader::FontDrawerShader() : 
Shader(FONT_DRAWER_VERTEX_SHADER_PATH, FONT_DRAWER_FRAGMENT_SHADER_PATH) {}


} 

