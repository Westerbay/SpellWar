/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_FONT_DRAWER_H__
#define __WG_FONT_DRAWER_H__


#include "Drawer.hpp"
#include "../tools/Font.hpp"
#include "../tools/Util.hpp"
#include "../opengl/Texture2D.hpp"
#include "../geometry/Cuboid.hpp"

#define FONT_DRAWER_VERTEX_SHADER_PATH "shaders/fontDrawer.vert"
#define FONT_DRAWER_FRAGMENT_SHADER_PATH "shaders/fontDrawer.frag"


namespace wgame {

class FontDrawer : public Drawer {
public:
	FontDrawer();
	void setTextData(
		const Font & font, const String & text, 
		const Point3D & position, Hitbox & hitbox = Hitbox()
	);
	void draw(const Matrix4D & model = Matrix4D(1.0f), Mode mode = HUD);
public:
    class FontDrawerShader : public Shader {
    public:
		FontDrawerShader();
    };
private:
	Point2D toUV(
		const Font & font, unsigned char character,
		unsigned char xOff, unsigned char yOff
	);
private:	
	static std::weak_ptr<FontDrawerShader> _uniqueShader;
    std::shared_ptr<FontDrawerShader> _shader;
	Texture2D _texture;
	ColorRGB _color;
	ColorRGBA _fillColor;
};

}

#endif 
