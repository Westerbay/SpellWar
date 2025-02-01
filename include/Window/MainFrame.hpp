/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#ifndef __MAIN_FRAME__
#define __MAIN_FRAME__

#include <SDL.h>
#include <GL/glew.h>

#include <string>

typedef struct {
	unsigned width;
	unsigned height;
} Size;

class MainFrame {
public:
	MainFrame(const char * title, const Size & size);
	~MainFrame();
	void run();
private:
	SDL_Window * _mainFrame;
	SDL_GLContext _glContext;
};

#endif

