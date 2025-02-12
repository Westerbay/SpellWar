/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

 
#ifndef __ABSTRACT_FRAME_H__
#define __ABSTRACT_FRAME_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <wgame/geometry/Geometry.hpp>
#include <wgame/gui/SpriteGroup.hpp>

#include <string>
#include <atomic>
#include <thread>
#include <chrono>


#define GL_VERSION_USED 4
#define DEFAULT_FPS 60


namespace wgame {

class AbstractFrame {
public:
	AbstractFrame(const char * title, const Size & size, unsigned fps = DEFAULT_FPS);
	virtual ~AbstractFrame();
	void setFPS(unsigned fps);
	void setBackgroundColor(GLclampf red, GLclampf green, GLclampf blue);
	void start();
	void stop();
	void addSprite(Sprite * sprite);
	void removeSprite(Sprite * sprite);
	void displaySprites();
	virtual void renderWorld() = 0;
	virtual void renderHUD() = 0;
private:
	GLFWwindow * _frame;
	SpriteGroup _group;
	std::atomic<unsigned> _frameDelay;
	std::atomic<bool> _running;
};

}

#endif

