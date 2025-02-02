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

#include <string>

typedef struct {
	unsigned width;
	unsigned height;
} Size;

class AbstractMainFrame {
public:
	AbstractMainFrame(const char * title, const Size & size);
	~AbstractMainFrame();
	void run();
	virtual void renderLoop() = 0;
private:
	SDL_Window * _mainFrame;
	SDL_GLContext _glContext;
};

#endif

