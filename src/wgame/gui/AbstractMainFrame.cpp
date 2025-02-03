/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/gui/AbstractMainFrame.hpp>

#include <iostream>
#include <stdexcept>


namespace wgame::gui {

AbstractMainFrame::AbstractMainFrame(const char * title, const wgame::geometry::Size & size, unsigned fps) :
	_running(false), _fps(fps) {
	initSDL(title, size);
}

AbstractMainFrame::~AbstractMainFrame() {
	SDL_GL_DestroyContext(_glContext);
	SDL_DestroyWindow(_mainFrame);
	SDL_Quit();
}

void AbstractMainFrame::initSDL(const char * title, const wgame::geometry::Size & size) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		throw std::runtime_error(std::string("Error SDL : ") + SDL_GetError());		
	}
	_mainFrame = SDL_CreateWindow(
		title,
		size.width, size.height,
		SDL_WINDOW_OPENGL
	);
	if (!_mainFrame) {
		SDL_Quit();
		throw std::runtime_error(std::string("Error creating window : ") + SDL_GetError());	
	}
	_glContext = SDL_GL_CreateContext(_mainFrame);
	if (!_glContext) {
		SDL_DestroyWindow(_mainFrame);
		SDL_Quit();
		throw std::runtime_error(std::string("Error creating GL context : ") + SDL_GetError());
	}
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		SDL_GL_DestroyContext(_glContext);
		SDL_DestroyWindow(_mainFrame);
		SDL_Quit();
		throw std::runtime_error("Error init GLEW");
	}
}

void AbstractMainFrame::run() {
	SDL_Event event;
	_running = true;
	while (_running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				_running = false;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		render();
		SDL_GL_SwapWindow(_mainFrame);
	}	
}

};
