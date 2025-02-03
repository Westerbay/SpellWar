/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

 
#ifndef __ABSTRACT_MAIN_FRAME__
#define __ABSTRACT_MAIN_FRAME__

#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <wgame/geometry/Geometry.hpp>

#include <string>
#include <atomic>


#define DEFAULT_FPS 60


namespace wgame::gui {

class AbstractMainFrame {
public:
	AbstractMainFrame(const char * title, const wgame::geometry::Size & size, unsigned fps = DEFAULT_FPS);
	~AbstractMainFrame();
	void run();
	virtual void render() = 0;
private:
	void initSDL(const char * title, const wgame::geometry::Size & size);
	SDL_Window * _mainFrame;
	SDL_GLContext _glContext;
	unsigned _fps;
	std::atomic<bool> _running;
};

}

#endif

