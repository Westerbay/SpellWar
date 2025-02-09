/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

 
#ifndef __ABSTRACT_FRAME_H__
#define __ABSTRACT_FRAME_H__

#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <wgame/geometry/Geometry.hpp>
#include <wgame/gui/SpriteGroup.hpp>

#include <string>
#include <atomic>
#include <thread>
#include <chrono>


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
	virtual void renderScene() = 0;
	virtual void renderHUD() = 0;
private:
	void initSDL(const char * title, const Size & size);
	SpriteGroup _group;
	SDL_Window * _mainFrame;
	SDL_GLContext _glContext;
	std::atomic<unsigned> _frameDelay;
	std::atomic<bool> _running;
};

}

#endif

